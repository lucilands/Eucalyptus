#pragma once


#include <clog.h>
#include <stdio.h>
#include <stdint.h>

#include <string.h>
#include <errno.h>


namespace Eucalyptus {
    class FileReader {
        public:
            FileReader(const char *path) {
                m_file = fopen(path, "rb");
                if (m_file == NULL) {
                    clog(CLOG_ERROR, "Failed to open file %s:%s", path, strerror(errno));
                }
            }

            uint32_t ReadUInt32();
            char *ReadSTR(uint32_t size);

        private:
            FILE *m_file;
    };
}