#include "error.h"



namespace Eucalyptus {
    void printerr(Error err, const char* pend = ""){
        fprintf(stderr, "%s%s", err.ToString().c_str(), pend);
    }
    void fprinterr(FILE* stream, Error err, const char* pend = ""){
        fprintf(stream, "%s%s", err.ToString().c_str(), pend);
    }
    std::string strerr(Error err){
        return err.ToString().c_str();
    }

    std::ostream& operator<<(std::ostream& os, Error err) {
        return os<<err.ToString();
    }
}