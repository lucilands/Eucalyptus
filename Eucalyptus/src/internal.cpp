#include "internal.h"



INITIALIZE_EASYLOGGINGPP;

namespace Eucalyptus {
    void InitLoggers() {
        el::Loggers::configureFromGlobal("logConfig.conf");
        el::Loggers::getLogger("Eucalyptus_INTERNAL");
    }
    el::Logger* _internalLogger(){
        return el::Loggers::getLogger("Eucalyptus_INTERNAL");
    }
}