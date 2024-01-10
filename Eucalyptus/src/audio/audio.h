#pragma once

#include "api.h"


#define EUC_AUDIO_BUFFER_CAPACITY 1024

// Platform specific imports
#ifdef EUCALYPTUS_PLATFORM_WINDOWS
    #include <windows.h>
#endif

namespace Eucalyptus {
    class _EUCAPI AudioClip {
    public:
        AudioClip(const char *path);
        void play(bool loop = false, bool async = true);
    private:
        BYTE* buffer;
    };
}