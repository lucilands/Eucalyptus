#include "logger.h"

#ifdef EUCALYPTUS_ENABLE_LOGGING
std::string get_time() {
    std::time_t t = std::time(0);
    std::tm *ltm = std::localtime(&t);

    std::stringstream ss;
    ss << std::setfill('0') << std::setw(2) << ltm->tm_hour << ":"
       << std::setfill('0') << std::setw(2) << ltm->tm_min << ":"
       << std::setfill('0') << std::setw(2) << ltm->tm_sec;

    return ss.str();
}

std::string euc_fmt(const char *c, ...) {
    std::stringstream outss;
    va_list lst;
    va_start(lst, c);
    while(*c != '\0') {
        if(*c != '%') {
            outss << *c << '\a';
            c++;
            continue;
        }

        c++;

        if(*c == '\0') {
            break;
        }

        switch(*c) {
            case 's': outss << va_arg(lst, char *); break;
            case 'c': outss << va_arg(lst, int); break;
            case 'd': outss << std::to_string(va_arg(lst, double)); break;
            case 'i': outss << std::to_string(va_arg(lst, int)); break;
        }
        c++;
    }
    va_end(lst);
    return outss.str();
}
std::string euc_fmt(std::string c1, ...) {
    std::stringstream outss;
    const char *c = c1.c_str();
    va_list lst;
    va_start(lst, c1);
    while(*c != '\0') {
        if(*c != '%') {
            outss << *c << '\a';
            c++;
            continue;
        }

        c++;

        if(*c == '\0') {
            break;
        }

        switch(*c) {
            case 's': outss << va_arg(lst, char *); break;
            case 'c': outss << va_arg(lst, int); break;
            case 'd': outss << std::to_string(va_arg(lst, double)); break;
            case 'i': outss << std::to_string(va_arg(lst, int)); break;
        }
        c++;
    }
    va_end(lst);
    return outss.str();
}
#endif