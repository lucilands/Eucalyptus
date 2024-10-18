#include <Eucalyptus/loaders/glb.h>
#include <Eucalyptus/loaders/freader.h>

#include <nlohmann/json.hpp>

#include <string.h>
#include <clog.h>

#include <vector>
#include <sstream>
#include <iostream>

using json = nlohmann::json;


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

        clog(CLOG_INFO, "Chunk %s\n\t- Length: %u", chunkName, chunkLength);
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
        FileReader GLB(path);
        uint32_t magic = GLB.ReadUInt32();
        uint32_t version = GLB.ReadUInt32();
        uint32_t length = GLB.ReadUInt32();

        clog(CLOG_INFO, "Loading glb file \"%s\"\n\t- Magic: 0x%X\n\t- Version: %u\n\t- Length: %u", path, magic, version, length);
        if (magic != GLB_IDENTIFIER) {
            clog(CLOG_FATAL, "GLB File %s does not have a valid glTF header!", path);
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

            json accessor = accessors[__m[0]["attributes"]["POSITION"].get<unsigned int>()];
            json texcoord_0 = accessors[__m[0]["attributes"]["TEXCOORD_0"].get<unsigned int>()];
            json scalar = accessors[__m[0]["indices"].get<unsigned int>()];

            json buffer_view = buffer_views[accessor["bufferView"].get<unsigned int>()];
            json scalar_buffer_view = buffer_views[scalar["bufferView"].get<unsigned int>()];
            json texcoord_0_buffer_view = buffer_views[texcoord_0["bufferView"].get<unsigned int>()];

            //if (scalar["componentType"] == GL_UNSIGNED_SHORT) {std::cout << "scalar_componentType = GL_UNSIGNED_SHORT" << std::endl;}
            unsigned short *scalar_segment = (unsigned short*)malloc(scalar_buffer_view["byteLength"].get<int>());
            memcpy(scalar_segment, bin_chunk->data.bin + scalar_buffer_view["byteOffset"].get<int>(), scalar_buffer_view["byteLength"].get<int>());
            for (unsigned int i = 0; i < scalar_buffer_view["byteLength"].get<int>() / sizeof(unsigned short); i++) {
                //std::cout << "Scalar value " << i << ": " << scalar_segment[i] << std::endl;
                indices.push_back(scalar_segment[i]);
            }
            free(scalar_segment);

            //std::cout << accessor.dump(4) << std::endl;
            //if (accessor["componentType"] == GL_FLOAT) {std::cout << "componentType = GL_FLOAT" << std::endl;}
            if (strcmp(accessor["type"].get<std::string>().c_str(), "VEC3") == 0) {
                float *segment = (float*)malloc(buffer_view["byteLength"].get<int>());
                float *texcoord_0_segment = (float*)malloc(texcoord_0_buffer_view["byteLength"].get<int>());
                memcpy(segment, bin_chunk->data.bin + buffer_view["byteOffset"].get<int>(), buffer_view["byteLength"].get<int>());
                memcpy(texcoord_0_segment, bin_chunk->data.bin + texcoord_0_buffer_view["byteOffset"].get<int>(), texcoord_0_buffer_view["byteLength"].get<int>());

                unsigned int j = 0;
                for (unsigned int i = 0; (i < buffer_view["byteLength"].get<int>() / sizeof(float)) && (j < texcoord_0_buffer_view["byteLength"].get<int>() / sizeof(float)); i+=3, j+=2) {
                    vertices.push_back({{segment[i], segment[i+1], segment[i+2]}, {texcoord_0_segment[j], texcoord_0_segment[j+1]}});
                    //std::cout << "VEC3 X=" << vert.position.x << " Y=" << vert.position.y << " Z=" << vert.position.z << std::endl;
                }
                free(segment);
            }

/*
            accessor = accessors[__m[0]["attributes"]["POSITION"].get<unsigned int>()];
            buffer_view = buffer_views[accessor["bufferView"].get<unsigned int>()];
            if (strcmp(accessor["type"].get<std::string>().c_str(), "VEC2") == 0) {
                float *segment = (float*)malloc(buffer_view["byteLength"].get<int>());
                memcpy(segment, bin_chunk->data.bin + buffer_view["byteOffset"].get<int>(), buffer_view["byteLength"].get<int>());
                for (unsigned int i = 0; i < buffer_view["byteLength"].get<int>() / sizeof(float); i+=2) {
                    std::cout << "VEC2 X=" << segment[i] << " Y=" << segment[i+1] << std::endl;
                    vertices.push_back((Vertex) {{segment[i], segment[i+1], 0.0f}, {0.0f, 0.0f}});
                }
                free(segment);
            }
*/
            std::cout << "Expected length: " << accessor["count"] << "\nActual lenght: " << vertices.size() << std::endl;
            return Mesh(vertices, indices);
        }
/*
        for (json accessor : accessors) {
            if (accessor.type() == json::value_t::object) {
                json buffer_view = buffer_views[accessor["bufferView"].get<int>()];
                //std::cout << buffer_view.dump(4) << std::endl;
                if (strcmp(accessor["type"].get<std::string>().c_str(), "VEC3")) {
                    float *segment = (float*)malloc(buffer_view["byteLength"].get<int>());
                    memcpy(segment, bin_chunk->data.bin + buffer_view["byteOffset"].get<int>(), buffer_view["byteLength"].get<int>());
                    for (unsigned int i = 0; i < buffer_view["byteLength"].get<int>() / sizeof(float); i+=3)
                    std::cout << "VEC3: X=" << segment[i] << " Y=" << segment[i+1] << " Z=" << segment[i+2] << std::endl;
                    free(segment);
                }
            }
        }
*/
        for (GLBChunk c : chunks) FreeChunk(c);
        return Eucalyptus::Prefabs::Cube;
    }
}