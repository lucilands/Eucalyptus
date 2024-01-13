#pragma once
#include <stdio.h>
#include <cstdarg>
#include <string>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <stdlib.h>


std::string euc_fmt(const char *c, ...);
std::string euc_fmt(std::string c, ...);
std::string get_time();

#ifdef EUCALYPTUS_ENABLE_LOGGING
#define _EUC_LOG_INFO(...) printf("%s - [INFO]: %s\n", get_time().c_str(), euc_fmt(__VA_ARGS__).c_str())
#define _EUC_LOG_WARNING(...) printf("%s - [WARNING]: %s\n", get_time().c_str(), euc_fmt(__VA_ARGS__).c_str())
#define _EUC_LOG_ERR(...) printf("%s - [ERROR]: %s\n", get_time().c_str(), euc_fmt(__VA_ARGS__).c_str())
#define _EUC_LOG_FATAL(...) printf("%s - [FATAL]: %s\n", get_time().c_str(), euc_fmt(__VA_ARGS__).c_str()); exit(1)
#else
#define _EUC_LOG_INFO(...)
#define _EUC_LOG_WARNING(...)
#define _EUC_LOG_ERR(...)
#define _EUC_LOG_FATAL(...)
#endif

