#include "audio.h"



#ifdef EUCALYPTUS_PLATFORM_WINDOWS
#include <ios>
#include <fstream>
namespace Eucalyptus {
    AudioClip::AudioClip(const char *path) {
        std::ifstream f(path, std::ios::binary);

        f.seekg(0, std::ios::end);
        int lim = f.tellg();

        buffer = new BYTE[lim];
        f.seekg(0, std::ios::beg);

        f.read((char *)buffer, lim);

        f.close();
    }
    void AudioClip::play(bool loop, bool async) {
        int flags = SND_MEMORY;
        if (loop) { flags |= SND_LOOP; }
        if (async) { flags |= SND_ASYNC; }

        PlaySound((LPCSTR)buffer, NULL, flags);
    }
}
#else
#warning Eucalyptus sound only supports Windows
#endif