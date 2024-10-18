#include <Eucalyptus/loaders/freader.h>
#include <clog.h>




namespace Eucalyptus {
    FileReader::FileReader(const char *path) {
        m_file = fopen(path, "rb");
        if (m_file == NULL) {
            clog(CLOG_ERROR, "Failed to open file %s:%s", path, strerror(errno));
        }
    }

    uint32_t FileReader::ReadUInt32() {
        uint32_t ret;
        fread((char*)&ret, sizeof(uint32_t), 1, m_file);
        return ret;
    }

    const char *FileReader::ReadSTR(uint32_t size) {
        char *ret = (char*)malloc(size+1);
        fread(ret, size, 1, m_file);
        ret[size] = 0;
        return ret;
    }

    unsigned char *FileReader::ReadBytes(uint32_t size) {
        unsigned char *ret = (unsigned char *)malloc(size);
        fread(ret, size, 1, m_file);
        return ret;
    }
}