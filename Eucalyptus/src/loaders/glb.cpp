#include <Eucalyptus/loaders/glb.h>
#include <Eucalyptus/loaders/freader.h>

#include <string.h>
#include <clog.h>

#include <sstream>



#define GLB_IDENTIFIER 0x46546C67

const ClogLevel INVALID_CHUNK_IDENT = CLOG_REGISTER_LEVEL("GLB: Invalid Chunk Identifier", CLOG_FATAL.color, 6);

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
            const unsigned char *data = reader.ReadBytes(chunkLength);
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

        GLBChunk chunk = ReadChunk(GLB);
        GLBChunk chunk1 = ReadChunk(GLB);
        
        EUC_TODO;

        FreeChunk(chunk);
        FreeChunk(chunk1);
        return Eucalyptus::Prefabs::Cube;
    }
}