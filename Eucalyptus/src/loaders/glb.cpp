#include <Eucalyptus/loaders/glb.h>
#include <Eucalyptus/loaders/freader.h>

#include <string.h>
#include <clog.h>

#include <sstream>



namespace Eucalyptus {
    Mesh LoadGLBmesh(const char *path) {
        FileReader GLB(path);
        uint32_t magic = GLB.ReadUInt32();
        uint32_t version = GLB.ReadUInt32();
        uint32_t length = GLB.ReadUInt32();

        clog(CLOG_INFO, "Loading glb file \"%s\"\n\t- Magic: 0x%X\n\t- Version: %u\n\t- Length: %u", path, magic, version, length);

        uint32_t chunkLength = GLB.ReadUInt32();
        uint32_t chunkType = GLB.ReadUInt32();

        char chunkName[5];
        int shiftby = -8;
        for (int i = 0; i < 4; i++) {
            chunkName[i] = (chunkType >> (shiftby += 8)) & 0xFF;
        }
        chunkName[4] = 0;

        clog(CLOG_INFO, "Chunk %s\n\t- Length: %u", chunkName, chunkLength);
        if (strcmp(chunkName, "JSON") == 0) {
            char *data = GLB.ReadSTR(chunkLength);
            printf("%s\n", data);

            free(data);
        }


        return Eucalyptus::Prefabs::Cube;
    }
}