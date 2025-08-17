/*
 * tc_wait.hpp - TC库等待和按键处理模块
 * TC Wait and Key Handling Module
 * 
 * 这个文件包含了TC库中所有与等待和按键处理相关的功能，包括：
 * - 时间延迟函数
 * - 跨平台按键等待功能
 * - 特定按键等待支持
 * - 常用按键常量定义
 * 
 * This file contains all wait and key handling related functionality in the TC library, including:
 * - Time delay functions
 * - Cross-platform key waiting functionality
 * - Specific key waiting support
 * - Common key constant definitions
 * 
 * 版本 Version: 1.0.1
 * 作者 Author: 537 Studio
 * 许可 License: MIT
 */

#ifndef TC_WAIT_HPP
#define TC_WAIT_HPP

// 标准库包含 | Standard library includes
#include <thread>  // 线程库，用于延时操作 | Thread library for delay operations
#include <chrono>  // 时间相关功能 | Time-related functionality

// 平台特定包含 | Platform-specific includes
#ifdef _WIN32
    #include <conio.h>    // Windows控制台输入输出函数 | Windows console I/O functions
#else
    #include <termios.h>  // 终端IO设置 | Terminal I/O settings
    #include <unistd.h>   // POSIX API | POSIX API
#endif

/**
 * 按键常量定义，用于waitKey函数
 * Key constants for waitKey function
 * 
 * 这些常量定义了常用的特殊按键的键码值，可以用于waitKey函数
 * 来等待特定的按键输入。这些值在不同平台上可能有所不同。
 * 
 * These constants define key code values for common special keys, which can be used
 * with the waitKey function to wait for specific key input. These values may vary
 * across different platforms.
 */
// 基本控制键 | Basic control keys
#define KEY_ESC      27    // Escape键 | Escape key
#define KEY_SPACE    32    // 空格键 | Space key
#define KEY_ENTER    13    // 回车键 | Enter key
#define KEY_TAB       9    // Tab键 | Tab key
#define KEY_BACKSPACE 8    // 退格键 | Backspace key

// 编辑键 | Editing keys
#define KEY_INSERT   0x2D  // Insert键 | Insert key
#define KEY_DELETE   0x2E  // Delete键 | Delete key
#define KEY_HOME     0x24  // Home键 | Home key
#define KEY_END      0x23  // End键 | End key
#define KEY_PAGEUP   0x21  // Page Up键 | Page Up key
#define KEY_PAGEDOWN 0x22  // Page Down键 | Page Down key

// 方向键 | Arrow keys
#define KEY_UP       0x26  // 上箭头键 | Up arrow key
#define KEY_DOWN     0x28  // 下箭头键 | Down arrow key
#define KEY_LEFT     0x25  // 左箭头键 | Left arrow key
#define KEY_RIGHT    0x27  // 右箭头键 | Right arrow key

// 功能键 | Function keys
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

namespace tc {

/**
 * 等待函数 - 暂停程序执行指定的秒数
 * Wait function - Pauses program execution for specified seconds
 * 
 * 这个函数使用C++11的线程库来实现跨平台的精确延时。
 * 支持小数秒数，内部转换为毫秒进行延时。
 * 
 * This function uses C++11 thread library to implement cross-platform precise delay.
 * Supports decimal seconds, internally converted to milliseconds for delay.
 * 
 * @param seconds 等待的秒数，支持小数 | Number of seconds to wait, supports decimals
 */
inline void wait(double seconds) { 
    // 将秒转换为毫秒并暂停线程 | Convert seconds to milliseconds and pause thread
    std::this_thread::sleep_for(std::chrono::milliseconds((int)(seconds*1000))); 
}

#ifdef _WIN32 // Windows平台实现 | Windows platform implementation

/**
 * waitKey函数 - 等待任意按键按下（Windows版本）
 * waitKey function - Waits for any key press (Windows version)
 * 
 * 使用Windows特有的_getch()函数，不需要按回车键即可获取按键输入。
 * Uses Windows-specific _getch() function, no need to press Enter to get key input.
 */
inline void waitKey() { 
    _getch(); // 使用_getch()获取按键，不回显 | Use _getch() to get key without echo
}

/**
 * waitKey函数 - 等待指定字符按键按下（Windows版本）
 * waitKey function - Waits for specific character key press (Windows version)
 * 
 * @param key 等待的字符按键 | Character key to wait for
 */
inline void waitKey(char key) { 
    while (_getch() != key) {} // 循环直到按下指定键 | Loop until specified key is pressed
}

/**
 * waitKey函数 - 等待指定键码按键按下（Windows版本）
 * waitKey function - Waits for specific key code press (Windows version)
 * 
 * @param key 等待的键码 | Key code to wait for
 */
inline void waitKey(int key) { 
    while (_getch() != key) {} // 循环直到按下指定键码 | Loop until specified key code is pressed
}

#else // 非Windows平台实现 | Non-Windows platform implementation

/**
 * waitKey函数 - 等待任意按键按下（Unix/Linux/macOS版本）
 * waitKey function - Waits for any key press (Unix/Linux/macOS version)
 * 
 * 使用termios来设置终端为非规范模式，允许立即读取按键输入。
 * Uses termios to set terminal to non-canonical mode for immediate key reading.
 */
inline void waitKey() {
    termios oldt, newt; // 终端设置结构体 | Terminal settings structures
    tcgetattr(0, &oldt); // 获取当前终端设置 | Get current terminal settings
    newt = oldt;
    newt.c_lflag &= ~ICANON; // 禁用规范模式，允许立即读取按键 | Disable canonical mode for immediate key reading
    tcsetattr(0, TCSANOW, &newt); // 应用新设置 | Apply new settings
    getchar(); // 读取一个字符 | Read one character
    tcsetattr(0, TCSANOW, &oldt); // 恢复原始设置 | Restore original settings
}

/**
 * waitKey函数 - 等待指定字符按键按下（Unix/Linux/macOS版本）
 * waitKey function - Waits for specific character key press (Unix/Linux/macOS version)
 * 
 * @param key 等待的字符按键 | Character key to wait for
 */
inline void waitKey(char key) {
    termios oldt, newt; // 终端设置结构体 | Terminal settings structures
    tcgetattr(0, &oldt); // 获取当前终端设置 | Get current terminal settings
    newt = oldt;
    newt.c_lflag &= ~ICANON; // 禁用规范模式，允许立即读取按键 | Disable canonical mode for immediate key reading
    tcsetattr(0, TCSANOW, &newt); // 应用新设置 | Apply new settings
    int ch;
    do { ch = getchar(); } while (ch != key); // 循环直到按下指定键 | Loop until specified key is pressed
    tcsetattr(0, TCSANOW, &oldt); // 恢复原始设置 | Restore original settings
}

/**
 * waitKey函数 - 等待指定键码按键按下（Unix/Linux/macOS版本）
 * waitKey function - Waits for specific key code press (Unix/Linux/macOS version)
 * 
 * @param key 等待的键码 | Key code to wait for
 */
inline void waitKey(int key) { 
    waitKey((char)key); // 转换为字符并调用字符版本 | Convert to char and call char version
}

#endif

} // namespace tc

#endif // TC_WAIT_HPP