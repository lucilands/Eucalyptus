#pragma once
#include "easylogging++.h"



#ifdef EUCALYPTUS_ENABLE_LOGGING
#define _EUC_LOG_INFO(...) _internalLogger()->info(__VA_ARGS__)
#define _EUC_LOG_ERR(...) _internalLogger()->error(__VA_ARGS__)
#define _EUC_LOG_FATAL(...) _internalLogger()->fatal(__VA_ARGS__)
#else
#define _EUC_LOG_INFO(...)
#define _EUC_LOG_ERR(...)
#define _EUC_LOG_FATAL(...)
#endif

namespace Eucalyptus{
    void InitLoggers();
    el::Logger* _internalLogger();

}
extern bool _GLINIT;
extern bool _EUCINIT;