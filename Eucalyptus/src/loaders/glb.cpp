#include <Eucalyptus/loaders/glb.h>
#include <Eucalyptus/loaders/freader.h>

#include <nlohmann/json.hpp>

#include <string.h>
#include <clog.h>

#include <vector>
#include <sstream>
#include <iostream>

using json = nlohmann::json;

//TODO: Load multiple "nodes" into one mesh


#define GLB_IDENTIFIER 0x46546C67

const ClogLevel INVALID_CHUNK_IDENT = CLOG_REGISTER_LEVEL("GLB Loader error", CLOG_FATAL.color, 6);

namespace Eucalyptus {
    void FreeChunk(GLBChunk chunk) {
        if (chunk.type == GLBChunkType::JSON) free((void*)chunk.data.str);
        if (chunk.type == GLBChunkType::BIN)  free((void*)chunk.data.bin);
    }

    GLBChunk ReadChunk(FileReader reader) {
        uint32_t chunkLength = reader.ReadUInt32();
        uint32_t chunkType = reader.ReadUInt32();

        char chunkName[5];
        int shiftby = -8;
        for (int i = 0; i < 4; i++) {
            chunkName[i] = (chunkType >> (shiftby += 8)) & 0xFF;
        }
        chunkName[4] = 0;

        if (strcmp(chunkName, "JSON") == 0) {
            const char *data = reader.ReadSTR(chunkLength);
            return (GLBChunk) {
                GLBChunkType::JSON,
                chunkName,
                chunkLength,
                {.str = data}
            };
        }
        else if (strcmp(chunkName, "BIN") == 0) {
            unsigned char *data = reader.ReadBytes(chunkLength);
            return (GLBChunk) {
                GLBChunkType::BIN,
                chunkName,
                chunkLength,
                {.bin = data}
            };
        }
        else {
            clog(INVALID_CHUNK_IDENT, "Chunk identifier %s is invalid! Exiting...", chunkName);
            exit(1);
        }
    }

    Mesh LoadGLBmesh(const char *path) {
        clog(CLOG_TRACE, "Loading glTF mesh \"%s\"", path);
        FileReader GLB(path);
        uint32_t magic = GLB.ReadUInt32();
        uint32_t version = GLB.ReadUInt32();
        uint32_t length = GLB.ReadUInt32();

        if (magic != GLB_IDENTIFIER) {
            clog(CLOG_FATAL, "GLB File %s does not have a valid glTF header!", path);
            exit(1);
        }
        if (version < 2) {
            clog(CLOG_FATAL, "glTF versions lower than 2.0 are not supported yet");
            exit(1);
        }

        unsigned int len = 24;
        std::vector<GLBChunk> chunks;
        while (len < length) {
            chunks.push_back(ReadChunk(GLB));
            len += chunks[chunks.size()-1].len + 2;
        }
        
        json json_chunk;
        GLBChunk *bin_chunk;
        for (GLBChunk chunk : chunks) {
            if (chunk.type == GLBChunkType::JSON) {
                json_chunk = json::parse(chunk.data.str);
            }
            if (chunk.type == GLBChunkType::BIN) bin_chunk = &chunk;
        }

        //std::cout << json_chunk.dump(4) << std::endl;

        json accessors = json_chunk["accessors"];
        json buffer_views = json_chunk["bufferViews"];
        json buffers = json_chunk["buffers"];

        //std::cout << json_chunk["nodes"].dump(4) << std::endl;

        //std::cout << accessors.dump(4) << std::endl;
        //exit(0);

        for (json mesh : json_chunk["meshes"]) {
            std::vector<Vertex> vertices;
            std::vector<unsigned int> indices;
            json __m = mesh["primitives"];
            //std::cout << __m.dump(4) << std::endl;

            clog(CLOG_TRACE, "Locating glTF tables...");
            json accessor = accessors[__m[0]["attributes"]["POSITION"].get<unsigned int>()];
            clog(CLOG_DEBUG, "Located attributes/POSITION");
            json normal = accessors[__m[0]["attributes"]["NORMAL"].get<unsigned int>()];
            clog(CLOG_DEBUG, "Located attributes/NORMAL");
            json texcoord_0 = accessors[__m[0]["attributes"]["TEXCOORD_0"].get<unsigned int>()];
            clog(CLOG_DEBUG, "Located attributes/TEXCOORD_0");
            json scalar = accessors[__m[0]["indices"].get<unsigned int>()];
            clog(CLOG_DEBUG, "Located indices");

            clog(CLOG_TRACE, "Located all neccesary tables");

            clog(CLOG_TRACE, "Locating BufferViews...");
            json buffer_view = buffer_views[accessor["bufferView"].get<unsigned int>()];
            clog(CLOG_DEBUG, "Located attributes/POSITION/bufferView");
            json normal_buffer_view = buffer_views[normal["bufferView"].get<unsigned int>()];
            clog(CLOG_DEBUG, "Located attributes/NORMAL/bufferView");
            json scalar_buffer_view = buffer_views[scalar["bufferView"].get<unsigned int>()];
            clog(CLOG_DEBUG, "Located indices/bufferView");
            json texcoord_0_buffer_view = buffer_views[texcoord_0["bufferView"].get<unsigned int>()];
            clog(CLOG_DEBUG, "Located attributes/TEXCOORD_0/bufferView");

            //if (scalar["componentType"] == GL_UNSIGNED_SHORT) {std::cout << "scalar_componentType = GL_UNSIGNED_SHORT" << std::endl;}
            //std::cout << scalar.dump(4) << std::endl;
            unsigned short *scalar_segment = (unsigned short*)malloc(scalar_buffer_view["byteLength"].get<int>());
            unsigned int offset = scalar_buffer_view["byteOffset"].is_null() ? 0 : scalar_buffer_view["byteOffset"].get<unsigned int>();
            memcpy(scalar_segment, bin_chunk->data.bin + offset, scalar_buffer_view["byteLength"].get<int>());
            for (unsigned int i = 0; i < scalar_buffer_view["byteLength"].get<int>() / sizeof(unsigned short); i++) {
                //std::cout << "Scalar value " << i << ": " << scalar_segment[i] << std::endl;
                indices.push_back(scalar_segment[i]);
            }
            free(scalar_segment);

            //std::cout << accessor.dump(4) << std::endl;
            //if (accessor["componentType"] == GL_FLOAT) {std::cout << "componentType = GL_FLOAT" << std::endl;}
            //std::cout << texcoord_0.dump(4) << std::endl;

            std::vector<Vector3f> positions;
            std::vector<Vector2f> texcoords;
            std::vector<Vector3f> normals;

            if (strcmp(accessor["type"].get<std::string>().c_str(), "VEC3") == 0) {
                Vector3f *segment = (Vector3f*)malloc(buffer_view["byteLength"].get<int>());
                Vector3f *normal_segment = (Vector3f*)malloc(normal_buffer_view["byteLength"].get<int>());
                Vector2f *texcoord_0_segment = (Vector2f*)malloc(texcoord_0_buffer_view["byteLength"].get<int>());
                memcpy(segment, bin_chunk->data.bin + buffer_view["byteOffset"].get<int>(), buffer_view["byteLength"].get<int>());
                memcpy(normal_segment, bin_chunk->data.bin + normal_buffer_view["byteOffset"].get<int>(), normal_buffer_view["byteLength"].get<int>());
                memcpy(texcoord_0_segment, bin_chunk->data.bin + texcoord_0_buffer_view["byteOffset"].get<int>(), texcoord_0_buffer_view["byteLength"].get<int>());

                unsigned int pos_stride = buffer_view["byteStride"].is_null() ? 0 : buffer_view["byteStride"].get<unsigned int>();
                unsigned int normal_stride = normal_buffer_view["byteStride"].is_null() ? 0 : normal_buffer_view["byteStride"].get<unsigned int>();
                unsigned int texcoord_0_stride = texcoord_0_buffer_view["byteStride"].is_null() ? 0 : texcoord_0_buffer_view["byteStride"].get<unsigned int>();

                for (unsigned int i = 0; i < buffer_view["byteLength"].get<unsigned int>(); i+=sizeof(Vector3f) + pos_stride) {
                    positions.push_back(segment[i / sizeof(Vector3f)]);
                    //std::cout << val[0] << " " << val[1] << " " << val[2] << std::endl;
                }

                for (unsigned int i = normal["byteOffset"].is_null() ? 0 : normal["byteOffset"].get<unsigned int>(); i < normal_buffer_view["byteLength"].get<unsigned int>(); i+=sizeof(Vector3f) + normal_stride) {
                    //float *val = (float*)malloc(sizeof(float) * 3);
                    normals.push_back(normal_segment[i / sizeof(Vector3f)]);
                    //std::cout << val[0] << " " << val[1] << " " << val[2] << std::endl;
                }

                for (unsigned int i = 0; i < texcoord_0_buffer_view["byteLength"].get<unsigned int>(); i+=sizeof(Vector2f)) {
                    texcoords.push_back(texcoord_0_segment[i / sizeof(Vector2f)]);
                    //std::cout << val[0] << " " << val[1] << " " << val[2] << std::endl;
                }
                

                //unsigned int j = 0;
                //for (unsigned int i = 0; (i < buffer_view["byteLength"].get<int>() / sizeof(float)) && (j < texcoord_0_buffer_view["byteLength"].get<int>() / sizeof(float)); i+=3, j+=2) {
                    //vertices.push_back({{segment[i], segment[i+1], segment[i+2]}, {texcoord_0_segment[j], texcoord_0_segment[j+1]}, {normal_segment[i], normal_segment[i+1], normal_segment[i+2]}});
                //}
                free(segment);
                free(normal_segment);
                free(texcoord_0_segment);
            }

            //std::cout << positions.size() << " " << normals.size() << " " << texcoords.size() << std::endl;

            for (unsigned int i = 0; i < positions.size(); i++) {
                vertices.push_back({positions[i], texcoords[i], normals[i]});
            }
            for (GLBChunk c : chunks) FreeChunk(c);
            return Mesh(vertices, indices);
        }
        return Mesh({{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f}});
    }
}