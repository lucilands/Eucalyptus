#include <Eucalyptus/loaders/freader.h>





namespace Eucalyptus {
    uint32_t FileReader::ReadUInt32() {
        uint32_t ret;
        fread((char*)&ret, sizeof(uint32_t), 1, m_file);
        return ret;
    }

    char *FileReader::ReadSTR(uint32_t size) {
        char *ret = (char*)malloc(size+1);
        fread(ret, size, 1, m_file);
        ret[size] = 0;
        return ret;
    }
}