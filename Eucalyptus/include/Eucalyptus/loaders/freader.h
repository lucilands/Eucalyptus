#pragma once


#include <stdio.h>
#include <stdint.h>

#include <string.h>
#include <errno.h>


namespace Eucalyptus {
    class FileReader {
        public:
            FileReader(const char *path);

            uint32_t ReadUInt32();
            const char *ReadSTR(uint32_t size);
            unsigned char *ReadBytes(uint32_t size);

        private:
            FILE *m_file;
    };
}