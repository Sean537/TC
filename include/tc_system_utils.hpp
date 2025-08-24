/*
 * tc_system_utils.hpp - TC库系统工具模块
 * TC System Utilities Module
 * 
 * 这个文件包含了TC库中的系统工具功能，包括：
 * - 系统时间获取功能
 * - 系统命令执行功能
 * - 跨平台系统操作支持
 * - 时间相关常量定义
 * - 按键状态检测功能
 * - 按键码常量定义
 * 
 * This file contains system utility functionality in the TC library, including:
 * - System time retrieval functionality
 * - System command execution functionality
 * - Cross-platform system operation support
 * - Time-related constant definitions
 * - Key state detection functionality
 * - Key code constant definitions
 * 
 * 版本 Version: 1.1.1 Beta
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
    #include <conio.h>   // Windows控制台输入输出函数 | Windows console I/O functions
#else
    #include <termios.h> // 终端IO设置 | Terminal I/O settings
    #include <unistd.h>  // POSIX API | POSIX API
    #include <fcntl.h>   // 文件控制定义 | File control definitions
    #include <sys/ioctl.h> // I/O控制 | I/O control
#endif

/**
 * 按键常量定义，用于isKeyPressed和waitKey函数
 * Key constants for isKeyPressed and waitKey functions
 * 
 * 这些常量定义了常用的特殊按键的键码值，可以用于isKeyPressed和waitKey函数
 * 来检测或等待特定的按键输入。这些值在不同平台上可能有所不同。
 * 
 * These constants define key code values for common special keys, which can be used
 * with the isKeyPressed and waitKey functions to detect or wait for specific key input.
 * These values may vary across different platforms.
 */
// 基本控制键 | Basic control keys
#define KEY_ESC      27    // Escape键 | Escape key
#define KEY_SPACE    32    // 空格键 | Space key
#define KEY_ENTER    13    // 回车键 | Enter key
#define KEY_TAB       9    // Tab键 | Tab key
#define KEY_BACKSPACE 8    // 退格键 | Backspace key

// 编辑键 | Editing keys
#ifdef _WIN32
#define KEY_INSERT   0x52  // Insert键 | Insert key
#define KEY_DELETE   0x53  // Delete键 | Delete key
#define KEY_HOME     0x47  // Home键 | Home key
#define KEY_END      0x4F  // End键 | End key
#define KEY_PAGEUP   0x49  // Page Up键 | Page Up key
#define KEY_PAGEDOWN 0x51  // Page Down键 | Page Down key
#else
#define KEY_INSERT   0x2D  // Insert键 | Insert key
#define KEY_DELETE   0x2E  // Delete键 | Delete key
#define KEY_HOME     0x24  // Home键 | Home key
#define KEY_END      0x23  // End键 | End key
#define KEY_PAGEUP   0x21  // Page Up键 | Page Up key
#define KEY_PAGEDOWN 0x22  // Page Down键 | Page Down key
#endif

// 方向键 | Arrow keys
#ifdef _WIN32
#define KEY_UP       72  // 上箭头键 | Up arrow key
#define KEY_DOWN     80  // 下箭头键 | Down arrow key
#define KEY_LEFT     75  // 左箭头键 | Left arrow key
#define KEY_RIGHT    77  // 右箭头键 | Right arrow key
#else
#define KEY_UP       0x26  // 上箭头键 | Up arrow key
#define KEY_DOWN     0x28  // 下箭头键 | Down arrow key
#define KEY_LEFT     0x25  // 左箭头键 | Left arrow key
#define KEY_RIGHT    0x27  // 右箭头键 | Right arrow key
#endif

// 功能键 | Function keys
#ifdef _WIN32
#define KEY_F1       0x3B  // F1功能键 | F1 function key
#define KEY_F2       0x3C  // F2功能键 | F2 function key
#define KEY_F3       0x3D  // F3功能键 | F3 function key
#define KEY_F4       0x3E  // F4功能键 | F4 function key
#define KEY_F5       0x3F  // F5功能键 | F5 function key
#define KEY_F6       0x40  // F6功能键 | F6 function key
#define KEY_F7       0x41  // F7功能键 | F7 function key
#define KEY_F8       0x42  // F8功能键 | F8 function key
#define KEY_F9       0x43  // F9功能键 | F9 function key
#define KEY_F10      0x44  // F10功能键 | F10 function key
#define KEY_F11      0x85  // F11功能键 | F11 function key
#define KEY_F12      0x86  // F12功能键 | F12 function key
#else
#define KEY_F1       0x70  // F1功能键 | F1 function key
#define KEY_F2       0x71  // F2功能键 | F2 function key
#define KEY_F3       0x72  // F3功能键 | F3 function key
#define KEY_F4       0x73  // F4功能键 | F4 function key
#define KEY_F5       0x74  // F5功能键 | F5 function key
#define KEY_F6       0x75  // F6功能键 | F6 function key
#define KEY_F7       0x76  // F7功能键 | F7 function key
#define KEY_F8       0x77  // F8功能键 | F8 function key
#define KEY_F9       0x78  // F9功能键 | F9 function key
#define KEY_F10      0x79  // F10功能键 | F10 function key
#define KEY_F11      0x7A  // F11功能键 | F11 function key
#define KEY_F12      0x7B  // F12功能键 | F12 function key
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

/**
 * 检查指定按键是否被按下
 * Check if a specific key is pressed
 * 
 * 这个函数检查指定的按键是否当前被按下。
 * 可以使用字符或按键码常量作为参数。
 * 
 * This function checks if a specific key is currently pressed.
 * Can use either a character or key code constant as parameter.
 * 
 * @param key 要检查的按键（字符或按键码常量） | Key to check (character or key code constant)
 * @return 如果按键被按下返回true，否则返回false | Returns true if key is pressed, false otherwise
 */
#ifdef _WIN32
inline bool isKeyPressed(int key) {
    // Windows平台使用GetAsyncKeyState API
    // Windows platform uses GetAsyncKeyState API
    
    // 对于一些特殊键，需要进行转换
    // For some special keys, conversion is needed
    switch(key) {
        case KEY_UP:    return (GetAsyncKeyState(VK_UP) & 0x8000) != 0;
        case KEY_DOWN:  return (GetAsyncKeyState(VK_DOWN) & 0x8000) != 0;
        case KEY_LEFT:  return (GetAsyncKeyState(VK_LEFT) & 0x8000) != 0;
        case KEY_RIGHT: return (GetAsyncKeyState(VK_RIGHT) & 0x8000) != 0;
        case KEY_ENTER: return (GetAsyncKeyState(VK_RETURN) & 0x8000) != 0;
        case KEY_ESC:   return (GetAsyncKeyState(VK_ESCAPE) & 0x8000) != 0;
        case KEY_SPACE: return (GetAsyncKeyState(VK_SPACE) & 0x8000) != 0;
        case KEY_TAB:   return (GetAsyncKeyState(VK_TAB) & 0x8000) != 0;
        case KEY_BACKSPACE: return (GetAsyncKeyState(VK_BACK) & 0x8000) != 0;
        default:        return (GetAsyncKeyState(key) & 0x8000) != 0;
    }
}

// 字符版本重载
// Character version overload
inline bool isKeyPressed(char key) {
    return isKeyPressed(static_cast<int>(key));
}
#else
// 非Windows平台实现
// Non-Windows platform implementation
inline bool isKeyPressed(int key) {
    struct termios oldt, newt;
    int ch;
    int oldf;
    
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
    
    ch = getchar();
    
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);
    
    if(ch != EOF) {
        ungetc(ch, stdin);
        return (ch == key);
    }
    
    return false;
}

// 字符版本重载
// Character version overload
inline bool isKeyPressed(char key) {
    return isKeyPressed(static_cast<int>(key));
}
#endif

} // namespace tc

#endif // TC_SYSTEM_UTILS_HPP
