#pragma once

#include "../graphics/model.h"
#include "freader.h"
#include <Eucalyptus/internal.h>

namespace Eucalyptus {
    enum class GLBChunkType {
        JSON,
        BIN
    };

    union GLBChunkData {
        const unsigned char *bin;
        const char *str;
    };

    struct GLBChunk {
        GLBChunkType type;
        const char *ident;
        uint32_t len;
        const GLBChunkData data;
    };

    GLBChunk ReadChunk(FileReader reader);
    Mesh LoadGLBmesh(const char *path);
}