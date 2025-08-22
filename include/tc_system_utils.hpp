/*
 * tc_system_utils.hpp - TC库系统工具模块
 * TC System Utilities Module
 * 
 * 这个文件包含了TC库中的系统工具功能，包括：
 * - 系统时间获取功能
 * - 系统命令执行功能
 * - 跨平台系统操作支持
 * - 时间相关常量定义
 * 
 * This file contains system utility functionality in the TC library, including:
 * - System time retrieval functionality
 * - System command execution functionality
 * - Cross-platform system operation support
 * - Time-related constant definitions
 * 
 * 版本 Version: 1.1.0
 * 作者 Author: 537 Studio
 * 许可 License: MIT
 */

#ifndef TC_SYSTEM_UTILS_HPP
#define TC_SYSTEM_UTILS_HPP

// 标准库包含 | Standard library includes
#include <ctime>    // 时间相关函数 | Time-related functions
#include <cstdlib>  // 系统函数，如system() | System functions like system()
#include <string>   // 字符串类 | String class

// 平台特定包含 | Platform-specific includes
#ifdef _WIN32
    #include <windows.h> // Windows API
#endif

/**
 * 系统时间常量，用于getSystemTime函数
 * System time constants for getSystemTime function
 * 
 * 这些常量定义了getSystemTime函数可以返回的不同时间组件。
 * 默认情况下返回Unix时间戳（自1970年1月1日起的秒数）。
 * 
 * These constants define different time components that the getSystemTime function can return.
 * By default, it returns Unix timestamp (seconds since January 1, 1970).
 */
#define SYS_YEAR     1  // 年份 | Year
#define SYS_MONTH    2  // 月份(1-12) | Month (1-12)
#define SYS_DAY      3  // 日期(1-31) | Day (1-31)
#define SYS_HOUR     4  // 小时(0-23) | Hour (0-23)
#define SYS_MINUTE   5  // 分钟(0-59) | Minute (0-59)
#define SYS_SECOND   6  // 秒钟(0-59) | Second (0-59)
#define SYS_TIMESTAMP 0  // Unix时间戳 | Unix timestamp

namespace tc {

/**
 * 获取系统时间
 * Get system time
 * 
 * 这个函数返回当前系统时间的各个组成部分，如年、月、日等，
 * 或者返回Unix时间戳（自1970年1月1日起的秒数）。
 * 在Windows平台上使用线程安全的localtime_s函数。
 * 
 * This function returns various components of the current system time,
 * such as year, month, day, etc., or returns the Unix timestamp
 * (seconds since January 1, 1970).
 * On Windows platform, uses thread-safe localtime_s function.
 * 
 * @param type 时间类型常量，默认为时间戳 | Time type constant, defaults to timestamp
 *             可选值：SYS_YEAR, SYS_MONTH, SYS_DAY, SYS_HOUR, SYS_MINUTE, SYS_SECOND, SYS_TIMESTAMP
 *             Possible values: SYS_YEAR, SYS_MONTH, SYS_DAY, SYS_HOUR, SYS_MINUTE, SYS_SECOND, SYS_TIMESTAMP
 * @return 请求的时间值 | Requested time value
 */
inline int getSystemTime(int type = SYS_TIMESTAMP) {
    // 获取当前时间的时间戳 | Get current time timestamp
    std::time_t t = std::time(nullptr);
    std::tm* tm_ptr;
    
#ifdef _WIN32
    // Windows平台使用线程安全版本 | Windows platform uses thread-safe version
    std::tm tm_buf;
    localtime_s(&tm_buf, &t);
    tm_ptr = &tm_buf;
#else
    // 非Windows平台使用标准版本 | Non-Windows platform uses standard version
    // 注意：在某些系统上，localtime可能不是线程安全的 | Note: On some systems, localtime may not be thread-safe
    tm_ptr = std::localtime(&t);
#endif
    
    // 根据请求的类型返回相应的时间值 | Return appropriate time value based on requested type
    switch(type) {
        case SYS_YEAR:   return tm_ptr->tm_year + 1900;  // 年份（tm_year是从1900年开始的） | Year (tm_year is years since 1900)
        case SYS_MONTH:  return tm_ptr->tm_mon + 1;      // 月份（tm_mon范围是0-11） | Month (tm_mon range is 0-11)
        case SYS_DAY:    return tm_ptr->tm_mday;         // 日期 | Day of month
        case SYS_HOUR:   return tm_ptr->tm_hour;         // 小时 | Hour
        case SYS_MINUTE: return tm_ptr->tm_min;          // 分钟 | Minute
        case SYS_SECOND: return tm_ptr->tm_sec;          // 秒钟 | Second
        default:         return static_cast<int>(t);     // 默认返回时间戳 | Default returns timestamp
    }
}

/**
 * 执行系统命令（C字符串版本）
 * Execute system command (C string version)
 * 
 * 这个函数使用系统的命令处理器执行指定的命令。
 * 命令在当前系统的默认shell中执行。
 * 
 * This function executes the specified command using the system's command processor.
 * The command is executed in the current system's default shell.
 * 
 * @param cmd 要执行的命令 | Command to execute
 * @return 命令的退出状态 | Exit status of the command
 */
inline int systemConsole(const char* cmd) {
    return std::system(cmd);
}

/**
 * 执行系统命令（C++字符串版本）
 * Execute system command (C++ string version)
 * 
 * 这个函数是systemConsole的重载版本，接受C++字符串。
 * 内部将std::string转换为C字符串后调用系统函数。
 * 
 * This function is an overloaded version of systemConsole that accepts C++ strings.
 * Internally converts std::string to C string before calling system function.
 * 
 * @param cmd 要执行的命令 | Command to execute
 * @return 命令的退出状态 | Exit status of the command
 */
inline int systemConsole(const std::string& cmd) {
    return std::system(cmd.c_str());
}

#ifdef _WIN32
/**
 * 执行系统命令（宽字符版本）
 * Execute system command (wide character version)
 * 
 * 这个函数是systemConsole的宽字符版本，用于支持Unicode命令。
 * 仅在Windows平台上可用，直接使用_wsystem函数。
 * 
 * This function is a wide character version of systemConsole for Unicode command support.
 * Only available on Windows platform, directly uses _wsystem function.
 * 
 * @param cmd 要执行的宽字符命令 | Wide character command to execute
 * @return 命令的退出状态 | Exit status of the command
 */
inline int systemConsoleW(const wchar_t* cmd) {
    return _wsystem(cmd);
}
#endif

} // namespace tc

#endif // TC_SYSTEM_UTILS_HPP