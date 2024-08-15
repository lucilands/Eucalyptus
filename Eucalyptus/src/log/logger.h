#pragma once
#include "clog.h"


#ifdef EUCALYPTUS_ENABLE_LOGGING
#define _EUC_LOG_DEBUG(...) clog(CLOG_DEBUG, __VA_ARGS__)
#define _EUC_LOG_TRACE(...) clog(CLOG_TRACE, __VA_ARGS__)
#define _EUC_LOG_INFO(...) clog(CLOG_INFO, __VA_ARGS__)
#define _EUC_LOG_WARNING(...) clog(CLOG_WARNING, __VA_ARGS__)
#define _EUC_LOG_ERR(...) clog(CLOG_ERROR, __VA_ARGS__)
#define _EUC_LOG_FATAL(...) clog(CLOG_FATAL, __VA_ARGS__)
#else
#define _EUC_LOG_DEBUG(...)
#define _EUC_LOG_TRACE(...)
#define _EUC_LOG_INFO(...)
#define _EUC_LOG_WARNING(...)
#define _EUC_LOG_ERR(...)
#define _EUC_LOG_FATAL(...)
#endif