#ifndef LOG_HPP
#define LOG_HPP

#include <cstdio>
#include <string>
#include <iostream>

#define ERROR_PREFIX "\033[1;31m\[ERROR]\033[0m "
#define WARNING_PREFIX "\033[1;33m\[WARNING]\033[0m "
#define LOG_PREFIX "\033[1;37m\[LOG]\033[0m "

#define LOG_MACRO(PREFIX, STREAM) std::cout << PREFIX << STREAM << std::endl
#define LOG_ERROR(STREAM) LOG_MACRO(ERROR_PREFIX, STREAM)
#define LOG_WARNING(STREAM) LOG_MACRO(WARNING_PREFIX, STREAM)
#define LOG(STREAM) LOG_MACRO(LOG_PREFIX, STREAM)

#endif