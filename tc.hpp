/*
tc.hpp
Version 1.0.1

This file is part of TC, a C++ terminal color and style library.

Online repository:
- https://github.com/Sean537/TC
- https://gitee.com/sean537/TC

Copyright (C) 2024-2025 537 Studio. All rights reserved.

Contributors:
- Sean537
- RabbitMax
- L.U.

Menu:
- 头文件保护与包含的标准库 Header file protection with included standard libraries
- ANCI前景色宏定义 ANCI Foreground Macro Definition (TCOLOR_XXX)
- ANSI背景色宏定义 ANSI Background Macro Definition (BCOLOR_XXX)
- ANSI字体样式宏定义 ANSI Font Style Macros (TFONT_XXX)
- tc命名空间开始与print/println函数 tc namespace starts with the print/println function
- wait/waitKey函数与按键常量定义 wait/waitKey function and key constant definition Wait/waitKey function and key constant definition
- Printer类定义 Printer class definition
- Windows平台相关代码 Windows platform related code
  - win32_colors命名空间 win32_colors namespace
  - Win32Console类 Win32Console class
- 非Windows平台ANSI转义序列定义 Non-Windows platform ANSI escape sequence definition ANSI escape sequence definition ANSI escape sequence definition
- 跨平台颜色控制类 ColorController
- 颜色包装器类与RGB颜色支持 RGBColorWrapper class and RGB color support
- 自定义输出流类与延时操作 Custom output stream class and delay operation
- 终端控制函数与便利颜色函数 Terminal control function and convenience color function
- 进度条类 ProgressBar
- tc命名空间结束 tc namespace ends
- 系统相关API与全局宏 System-related APIs and global macros
  - getSystemTime函数
  - systemConsole函数
  - 系统环境宏定义
  - systemCheck函数
*/

#ifndef TC_HPP // 头文件保护，防止重复包含 | Header guard, prevent multiple inclusion
#define TC_HPP

#define TC_VERSION "1.0.1" // 版本号定义 | Version number definition

// 包含所需的标准库头文件 | Include required standard library headers
#include <iostream>    // 标准输入输出流，用于控制台输出 | Standard IO stream for console output
#include <string>      // 字符串类，用于文本处理 | String class for text processing
#include <sstream>     // 字符串流，用于字符串格式化 | String stream for string formatting
#include <thread>      // 线程库，用于延时操作 | Thread library for delay operations
#include <chrono>      // 时间相关功能，用于计时 | Time-related functionality for timing
#include <memory>      // 智能指针，用于资源管理 | Smart pointers for resource management
#include <functional>  // 函数对象，用于回调函数 | Function objects for callbacks
#include <type_traits> // 类型特性，用于模板元编程 | Type traits for template metaprogramming
#include <stack>       // 栈容器，用于颜色状态管理 | Stack container for color state management

// 平台特定头文件包含 | Platform-specific header includes
#ifdef _WIN32 // Windows平台特定代码 | Windows platform specific code
    #include <windows.h> // Windows API函数和数据类型 | Windows API functions and data types
    #include <io.h>      // Windows IO操作函数，如_setmode | Windows IO operation functions like _setmode
    #include <fcntl.h>   // 文件控制选项，如O_BINARY | File control options like O_BINARY
    #ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING // 如果未定义虚拟终端处理宏 | If virtual terminal processing macro is not defined
        #define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004 // 定义ANSI转义序列支持标志 | Define ANSI escape sequence support flag
    #endif
#else // 非Windows平台（Unix/Linux/macOS等） | Non-Windows platforms (Unix/Linux/macOS etc.)
    #include <unistd.h>    // POSIX API，提供sleep等函数 | POSIX API providing functions like sleep
    #include <sys/ioctl.h> // 终端IO控制，用于获取终端大小 | Terminal IO control for getting terminal size
#endif

// ===== ANSI前景色宏定义（全局作用域） | ANSI foreground color macros (global scope) =====
// 这些宏定义了ANSI转义序列，用于设置文本颜色 | These macros define ANSI escape sequences for text colors
#define TCOLOR_BLACK   "\033[30m"  // 黑色文本 | Black text
#define TCOLOR_RED     "\033[31m"  // 红色文本 | Red text
#define TCOLOR_GREEN   "\033[32m"  // 绿色文本 | Green text
#define TCOLOR_YELLOW  "\033[33m"  // 黄色文本 | Yellow text
#define TCOLOR_BLUE    "\033[34m"  // 蓝色文本 | Blue text
#define TCOLOR_MAGENTA "\033[35m"  // 洋红色文本 | Magenta text
#define TCOLOR_CYAN    "\033[36m"  // 青色文本 | Cyan text
#define TCOLOR_WHITE   "\033[37m"  // 白色文本 | White text
#define TCOLOR_DEFAULT "\033[39m"  // 默认前景色 | Default foreground color
#define TCOLOR_RESET   "\033[0m"   // 重置所有属性 | Reset all attributes
#define TCOLOR_RGB(r, g, b) tc::RGBColorWrapper(r, g, b) // RGB自定义颜色 | Custom RGB color

// ===== ANSI背景色宏定义（全局作用域） | ANSI background color macros (global scope) =====
// 这些宏定义了ANSI转义序列，用于设置背景颜色 | These macros define ANSI escape sequences for background colors
#define BCOLOR_BLACK   "\033[40m"  // 黑色背景 | Black background
#define BCOLOR_RED     "\033[41m"  // 红色背景 | Red background
#define BCOLOR_GREEN   "\033[42m"  // 绿色背景 | Green background
#define BCOLOR_YELLOW  "\033[43m"  // 黄色背景 | Yellow background
#define BCOLOR_BLUE    "\033[44m"  // 蓝色背景 | Blue background
#define BCOLOR_MAGENTA "\033[45m"  // 洋红色背景 | Magenta background
#define BCOLOR_CYAN    "\033[46m"  // 青色背景 | Cyan background
#define BCOLOR_WHITE   "\033[47m"  // 白色背景 | White background
#define BCOLOR_DEFAULT "\033[49m"  // 默认背景色 | Default background color
// ===== ANSI字体样式宏（全局作用域） | ANSI font style macros (global scope) =====
// 这些宏定义了ANSI转义序列，用于设置文本样式 | These macros define ANSI escape sequences for text styles
#define TFONT_BOLD        "\033[1m"   // 粗体/加粗文本 | Bold text
#define TFONT_FAINT       "\033[2m"   // 微弱/淡色文本 | Faint/dim text
#define TFONT_ITALIC      "\033[3m"   // 斜体文本 | Italic text
#define TFONT_UNDERLINE   "\033[4m"   // 下划线文本 | Underlined text
#define TFONT_BLINK_SLOW  "\033[5m"   // 慢速闪烁文本 | Slow blinking text
#define TFONT_BLINK_FAST  "\033[6m"   // 快速闪烁文本 | Rapid blinking text
#define TFONT_REVERSE     "\033[7m"   // 反色（前景背景互换） | Reversed colors (swap fg/bg)
#define TFONT_CONCEAL     "\033[8m"   // 隐藏文本 | Concealed/hidden text
#define TFONT_CROSSED     "\033[9m"   // 删除线文本 | Crossed-out text
#define TFONT_DEFAULT     "\033[10m"  // 默认字体 | Default font
#define TFONT_FRAKTUR     "\033[20m"  // Fraktur字体（部分终端支持） | Fraktur font (limited support)
#define TFONT_DOUBLE_UNDERLINE "\033[21m" // 双下划线/粗体关闭 | Double underline/bold off
#define TFONT_NORMAL      "\033[22m"  // 粗体/淡色关闭 | Normal intensity (not bold/faint)
#define TFONT_NOT_ITALIC  "\033[23m"  // 关闭斜体/Fraktur | Not italic/fraktur
#define TFONT_NO_UNDERLINE "\033[24m" // 关闭下划线 | Underline off
#define TFONT_NO_BLINK    "\033[25m"  // 关闭闪烁 | Blink off
#define TFONT_NO_REVERSE  "\033[27m"  // 关闭反色 | Reverse off
#define TFONT_REVEAL      "\033[28m"  // 关闭隐藏 | Conceal off
#define TFONT_NOT_CROSSED "\033[29m"  // 关闭删除线 | Crossed-out off
#define TFONT_THICK       TFONT_BOLD  // 兼容别名（粗体） | Compatible alias for bold
#define TFONT_RESET       "\033[0m"   // 全部重置（所有属性） | Reset all attributes

// 用法示例 | Usage example: tc::println(TCOLOR_RED, BCOLOR_YELLOW, TFONT_BOLD, "红字黄底粗体 | Bold red text on yellow background")

namespace tc { // 主命名空间，包含所有TC库功能 | Main namespace containing all TC library functionality

// ========== print/println 函数 | print/println functions ========== //
/**
 * PrintProxy类 - 提供链式调用风格的打印功能
 * PrintProxy class - Provides chainable printing functionality
 * 
 * 这个类允许类似Python的链式打印操作，如：print("Hello").print(" ").println("World")
 * This class allows Python-like chaining of print operations, e.g.: print("Hello").print(" ").println("World")
 */
class PrintProxy {
public:
    // 无参数打印，返回自身引用以支持链式调用 | No-argument print, returns self-reference for chaining
    const PrintProxy& print() const { return *this; }
    
    // 可变参数模板打印，支持任意数量和类型的参数 | Variadic template print, supports any number and type of arguments
    template<typename... Args>
    const PrintProxy& print(Args&&... args) const { 
        // 使用初始化列表技巧展开参数包 | Using initializer list trick to expand parameter pack
        (void)std::initializer_list<int>{(std::cout << std::forward<Args>(args), 0)...}; 
        return *this; 
    }
    
    // 可变参数模板行打印，带换行符 | Variadic template line print with newline
    template<typename... Args>
    const PrintProxy& println(Args&&... args) const { 
        (void)std::initializer_list<int>{(std::cout << std::forward<Args>(args), 0)...}; 
        std::cout << std::endl; 
        return *this; 
    }
};

// 全局print函数，返回PrintProxy实例以支持链式调用 | Global print function, returns PrintProxy instance for chaining
inline const PrintProxy& print() { static PrintProxy p; return p; }

// 全局println函数，输出换行符并返回PrintProxy实例 | Global println function, outputs newline and returns PrintProxy instance
inline const PrintProxy& println() { static PrintProxy p; std::cout << std::endl; return p; }

/**
 * 全局print/println函数 - 支持一次性多参数打印
 * Global print/println functions - Support one-time multi-parameter printing
 * 
 * 这些函数提供了简单的接口来打印多个参数，类似于Python的print函数
 * These functions provide a simple interface to print multiple arguments, similar to Python's print function
 */
// 全局print函数，一次性打印多个参数 | Global print function, prints multiple arguments at once
template<typename... Args>
inline void print(Args&&... args) { 
    (void)std::initializer_list<int>{(std::cout << std::forward<Args>(args), 0)...}; 
}

// 全局println函数，一次性打印多个参数并换行 | Global println function, prints multiple arguments and adds newline
template<typename... Args>
inline void println(Args&&... args) { 
    (void)std::initializer_list<int>{(std::cout << std::forward<Args>(args), 0)...}; 
    std::cout << std::endl; 
}

// ========== wait/waitKey 函数 | wait/waitKey functions ========== //
/**
 * wait函数 - 暂停程序执行指定的秒数
 * wait function - Pauses program execution for specified seconds
 * 
 * @param seconds 等待的秒数，支持小数 | Number of seconds to wait, supports decimals
 */
inline void wait(double seconds) { 
    // 将秒转换为毫秒并暂停线程 | Convert seconds to milliseconds and pause thread
    std::this_thread::sleep_for(std::chrono::milliseconds((int)(seconds*1000))); 
}

#ifdef _WIN32 // Windows平台实现 | Windows platform implementation
#include <conio.h> // 控制台输入输出函数 | Console input/output functions

/**
 * waitKey函数 - 等待任意按键按下
 * waitKey function - Waits for any key press
 */
inline void waitKey() { _getch(); } // 使用_getch()获取按键，不回显 | Use _getch() to get key without echo

/**
 * waitKey函数 - 等待指定字符按键按下
 * waitKey function - Waits for specific character key press
 * 
 * @param key 等待的字符按键 | Character key to wait for
 */
inline void waitKey(char key) { 
    while (_getch() != key) {} // 循环直到按下指定键 | Loop until specified key is pressed
}

/**
 * waitKey函数 - 等待指定键码按键按下
 * waitKey function - Waits for specific key code press
 * 
 * @param key 等待的键码 | Key code to wait for
 */
inline void waitKey(int key) { 
    while (_getch() != key) {} // 循环直到按下指定键码 | Loop until specified key code is pressed
}

#else // 非Windows平台实现 | Non-Windows platform implementation
#include <termios.h> // 终端IO设置 | Terminal IO settings

/**
 * waitKey函数 - 等待任意按键按下（Unix/Linux/macOS版本）
 * waitKey function - Waits for any key press (Unix/Linux/macOS version)
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
inline void waitKey(int key) { waitKey((char)key); } // 转换为字符并调用字符版本 | Convert to char and call char version
#endif
// 按键常量定义，用于waitKey函数 | Key constants for waitKey function
#define KEY_ESC      27    // Escape键 | Escape key
#define KEY_SPACE    32    // 空格键 | Space key
#define KEY_ENTER    13    // 回车键 | Enter key
#define KEY_TAB       9    // Tab键 | Tab key
#define KEY_BACKSPACE 8    // 退格键 | Backspace key
#define KEY_INSERT   0x2D  // Insert键 | Insert key
#define KEY_DELETE   0x2E  // Delete键 | Delete key
#define KEY_HOME     0x24  // Home键 | Home key
#define KEY_END      0x23  // End键 | End key
#define KEY_PAGEUP   0x21  // Page Up键 | Page Up key
#define KEY_PAGEDOWN 0x22  // Page Down键 | Page Down key
#define KEY_UP       0x26  // 上箭头键 | Up arrow key
#define KEY_DOWN     0x28  // 下箭头键 | Down arrow key
#define KEY_LEFT     0x25  // 左箭头键 | Left arrow key
#define KEY_RIGHT    0x27  // 右箭头键 | Right arrow key
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

// ========== Printer类 - 终端打印和控制 | Printer class - Terminal printing and control ========== //
/**
 * Printer类 - 提供终端控制和打印功能的链式接口
 * Printer class - Provides a chainable interface for terminal control and printing
 * 
 * 这个类封装了终端控制操作，如清屏、移动光标、显示/隐藏光标等，
 * 并提供链式调用接口，使得多个操作可以连续执行。
 * 
 * This class encapsulates terminal control operations such as clearing screen,
 * moving cursor, showing/hiding cursor, etc., and provides a chainable interface
 * allowing multiple operations to be executed in sequence.
 */
class Printer {
public:
    /**
     * 清屏并将光标移动到左上角
     * Clear screen and move cursor to top-left corner
     * 
     * @return 对象自身引用，支持链式调用 | Self reference for chaining
     */
    Printer& clear() { std::cout << "\033[2J\033[H"; return *this; }
    
    /**
     * 将光标移动到指定坐标
     * Move cursor to specified coordinates
     * 
     * @param x 列坐标（从1开始） | Column coordinate (1-based)
     * @param y 行坐标（从1开始） | Row coordinate (1-based)
     * @return 对象自身引用，支持链式调用 | Self reference for chaining
     */
    Printer& moveCursor(int x, int y) { std::cout << "\033[" << y << ";" << x << "H"; return *this; }
    
    /**
     * 无参数打印函数
     * No-argument print function
     * 
     * @return 对象自身引用，支持链式调用 | Self reference for chaining
     */
    Printer& print() { return *this; }
    
    /**
     * 可变参数打印函数
     * Variadic print function
     * 
     * @param args 要打印的参数 | Arguments to print
     * @return 对象自身引用，支持链式调用 | Self reference for chaining
     */
    template<typename... Args>
    Printer& print(Args&&... args) { 
        (void)std::initializer_list<int>{(std::cout << std::forward<Args>(args), 0)...}; 
        return *this; 
    }
    
    /**
     * 可变参数打印函数，带换行
     * Variadic print function with newline
     * 
     * @param args 要打印的参数 | Arguments to print
     * @return 对象自身引用，支持链式调用 | Self reference for chaining
     */
    template<typename... Args>
    Printer& println(Args&&... args) { 
        (void)std::initializer_list<int>{(std::cout << std::forward<Args>(args), 0)...}; 
        std::cout << std::endl; 
        return *this; 
    }
    
    /**
     * 隐藏光标
     * Hide cursor
     * 
     * @return 对象自身引用，支持链式调用 | Self reference for chaining
     */
    Printer& hideCursor() { std::cout << "\033[?25l"; return *this; }
    
    /**
     * 显示光标
     * Show cursor
     * 
     * @return 对象自身引用，支持链式调用 | Self reference for chaining
     */
    Printer& showCursor() { std::cout << "\033[?25h"; return *this; }
    
    /**
     * 光标移动方向枚举
     * Cursor movement direction enum
     */
    enum class Direction { Up, Down, Left, Right };
    
    /**
     * 按指定方向移动光标
     * Move cursor in specified direction
     * 
     * @param dir 移动方向 | Movement direction
     * @param n 移动步数 | Number of steps to move
     * @return 对象自身引用，支持链式调用 | Self reference for chaining
     */
    Printer& moveCursor(Direction dir, int n) {
        switch(dir) {
            case Direction::Up: std::cout << "\033[" << n << "A"; break;     // 向上移动 | Move up
            case Direction::Down: std::cout << "\033[" << n << "B"; break;   // 向下移动 | Move down
            case Direction::Right: std::cout << "\033[" << n << "C"; break;  // 向右移动 | Move right
            case Direction::Left: std::cout << "\033[" << n << "D"; break;   // 向左移动 | Move left
        }
        return *this;
    }
    
    /**
     * 获取终端窗口大小
     * Get terminal window size
     * 
     * @return 包含宽度和高度的对组 | Pair containing width and height
     */
    std::pair<int,int> getSize() {
#ifdef _WIN32
        // Windows平台实现 | Windows platform implementation
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        int cols = 80, rows = 25;  // 默认值 | Default values
        HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
        if (GetConsoleScreenBufferInfo(h, &csbi)) {
            // 计算实际窗口大小 | Calculate actual window size
            cols = csbi.srWindow.Right - csbi.srWindow.Left + 1;
            rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
        }
        return {cols, rows};
#else
        // Unix/Linux/macOS平台实现 | Unix/Linux/macOS platform implementation
        struct winsize size;
        if (ioctl(1, TIOCGWINSZ, &size) == 0)
            return {size.ws_col, size.ws_row};
        return {80, 25};  // 默认值 | Default values
#endif
    }
};

/**
 * 创建并返回一个Printer对象
 * Create and return a Printer object
 * 
 * @return 新的Printer对象 | New Printer object
 */
inline Printer printer() { return Printer(); }

#ifdef _WIN32 // Windows平台特定代码 | Windows platform specific code

/**
 * Windows颜色常量映射命名空间
 * Windows color constant mapping namespace
 * 
 * 这个命名空间定义了Windows控制台API的颜色常量，将它们映射为更易用的名称，
 * 便于与ANSI颜色代码保持一致的跨平台接口。
 * 
 * This namespace defines color constants for the Windows Console API, mapping them
 * to more user-friendly names, facilitating a consistent cross-platform interface
 * with ANSI color codes.
 */
namespace win32_colors {
    constexpr WORD BLACK = 0;                                                  // 黑色前景色 | Black foreground
    constexpr WORD DARK_BLUE = FOREGROUND_BLUE;                                // 深蓝前景色 | Dark blue foreground
    constexpr WORD DARK_GREEN = FOREGROUND_GREEN;                              // 深绿前景色 | Dark green foreground
    constexpr WORD DARK_CYAN = FOREGROUND_GREEN | FOREGROUND_BLUE;             // 深青前景色 | Dark cyan foreground
    constexpr WORD DARK_RED = FOREGROUND_RED;                                  // 深红前景色 | Dark red foreground
    constexpr WORD DARK_MAGENTA = FOREGROUND_RED | FOREGROUND_BLUE;            // 深洋红前景色 | Dark magenta foreground
    constexpr WORD DARK_YELLOW = FOREGROUND_RED | FOREGROUND_GREEN;            // 深黄前景色 | Dark yellow foreground
    constexpr WORD GRAY = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE; // 灰色前景色 | Gray foreground
    constexpr WORD DARK_GRAY = FOREGROUND_INTENSITY;                           // 深灰前景色 | Dark gray foreground
    constexpr WORD BLUE = FOREGROUND_BLUE | FOREGROUND_INTENSITY;              // 亮蓝前景色 | Bright blue foreground
    constexpr WORD GREEN = FOREGROUND_GREEN | FOREGROUND_INTENSITY;            // 亮绿前景色 | Bright green foreground
    constexpr WORD CYAN = FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;  // 亮青前景色 | Bright cyan foreground
    constexpr WORD RED = FOREGROUND_RED | FOREGROUND_INTENSITY;                // 亮红前景色 | Bright red foreground
    constexpr WORD MAGENTA = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY; // 亮洋红前景色 | Bright magenta foreground
    constexpr WORD YELLOW = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY; // 亮黄前景色 | Bright yellow foreground
    constexpr WORD WHITE = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY; // 白色前景色 | White foreground
}

/**
 * Windows控制台管理类
 * Windows console manager class
 * 
 * 这个类封装了Windows控制台API的操作，提供颜色设置、光标控制、清屏等功能。
 * 采用单例模式设计，确保全局只有一个控制台管理实例。
 * 
 * This class encapsulates Windows Console API operations, providing functionality
 * for color setting, cursor control, screen clearing, etc. It uses the singleton
 * design pattern to ensure only one console manager instance exists globally.
 */
class Win32Console {
private:
    HANDLE hConsole_;                        // 控制台句柄 | Console handle
    CONSOLE_SCREEN_BUFFER_INFO originalInfo_; // 原始缓冲区信息，用于恢复初始状态 | Original buffer info for restoring initial state
    std::stack<WORD> colorStack_;            // 颜色栈，用于保存和恢复颜色设置 | Color stack for saving and restoring color settings
    bool initialized_ = false;               // 初始化标志，指示控制台是否成功初始化 | Initialization flag indicating if console was successfully initialized

    /**
     * 私有构造函数，初始化控制台和UTF-8支持
     * Private constructor, initializes console and UTF-8 support
     * 
     * 单例模式的一部分，防止外部直接创建实例
     * Part of singleton pattern, prevents direct instance creation from outside
     */
    Win32Console() {
        // 获取标准输出句柄 | Get standard output handle
        hConsole_ = GetStdHandle(STD_OUTPUT_HANDLE);
        
        if (hConsole_ != INVALID_HANDLE_VALUE) {
            // 获取原始控制台信息 | Get original console information
            GetConsoleScreenBufferInfo(hConsole_, &originalInfo_);
            initialized_ = true;
            
            // 设置UTF-8编码支持 | Set UTF-8 encoding support
            SetConsoleOutputCP(CP_UTF8);  // 输出编码设为UTF-8 | Set output encoding to UTF-8
            SetConsoleCP(CP_UTF8);        // 输入编码设为UTF-8 | Set input encoding to UTF-8
            
            // 尝试启用ANSI转义序列处理 | Try to enable ANSI escape sequence processing
            DWORD dwMode = 0;
            if (GetConsoleMode(hConsole_, &dwMode)) {
                SetConsoleMode(hConsole_, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
            }
        }
    }

public:
    /**
     * 获取单例实例
     * Get singleton instance
     * 
     * @return Win32Console的单例引用 | Singleton reference to Win32Console
     */
    static Win32Console& getInstance() {
        static Win32Console instance;  // 静态局部变量保证线程安全的单例 | Static local variable ensures thread-safe singleton
        return instance;
    }

    /**
     * 判断控制台是否成功初始化
     * Check if console was successfully initialized
     * 
     * @return 初始化状态 | Initialization status
     */
    bool isInitialized() const { return initialized_; }

    /**
     * 设置控制台文本颜色
     * Set console text color
     * 
     * @param color Windows控制台颜色属性 | Windows console color attribute
     */
    void setColor(WORD color) {
        if (initialized_) {
            SetConsoleTextAttribute(hConsole_, color);
        }
    }

    /**
     * 保存当前颜色并设置新颜色
     * Save current color and set new color
     * 
     * @param color 要设置的新颜色 | New color to set
     */
    void pushColor(WORD color) {
        if (initialized_) {
            // 获取当前颜色并保存到栈中 | Get current color and save to stack
            CONSOLE_SCREEN_BUFFER_INFO info;
            GetConsoleScreenBufferInfo(hConsole_, &info);
            colorStack_.push(info.wAttributes);
            
            // 设置新颜色 | Set new color
            setColor(color);
        }
    }

    /**
     * 恢复之前保存的颜色
     * Restore previously saved color
     */
    void popColor() {
        if (initialized_ && !colorStack_.empty()) {
            // 从栈中弹出颜色并设置 | Pop color from stack and set it
            setColor(colorStack_.top());
            colorStack_.pop();
        }
    }

    /**
     * 重置为原始控制台颜色
     * Reset to original console color
     */
    void resetColor() {
        if (initialized_) {
            setColor(originalInfo_.wAttributes);
        }
    }

    /**
     * 获取当前控制台颜色
     * Get current console color
     * 
     * @return 当前颜色属性 | Current color attribute
     */
    WORD getCurrentColor() const {
        if (initialized_) {
            CONSOLE_SCREEN_BUFFER_INFO info;
            GetConsoleScreenBufferInfo(hConsole_, &info);
            return info.wAttributes;
        }
        return win32_colors::WHITE;  // 默认返回白色 | Default to white
    }

    /**
     * 移动控制台光标到指定位置
     * Move console cursor to specified position
     * 
     * @param x 列坐标（从0开始） | Column coordinate (0-based)
     * @param y 行坐标（从0开始） | Row coordinate (0-based)
     */
    void moveCursor(int x, int y) {
        if (initialized_) {
            // 创建坐标并设置光标位置 | Create coordinates and set cursor position
            COORD coord = {static_cast<SHORT>(x), static_cast<SHORT>(y)};
            SetConsoleCursorPosition(hConsole_, coord);
        }
    }

    /**
     * 清空控制台屏幕
     * Clear console screen
     */
    void clearScreen() {
        if (initialized_) {
            // 获取当前缓冲区信息 | Get current buffer info
            CONSOLE_SCREEN_BUFFER_INFO info;
            GetConsoleScreenBufferInfo(hConsole_, &info);
            
            DWORD written;
            COORD topLeft = {0, 0};
            
            // 用空格填充整个缓冲区 | Fill entire buffer with spaces
            FillConsoleOutputCharacter(hConsole_, ' ', 
                info.dwSize.X * info.dwSize.Y, topLeft, &written);
                
            // 用当前属性填充整个缓冲区 | Fill entire buffer with current attributes
            FillConsoleOutputAttribute(hConsole_, info.wAttributes,
                info.dwSize.X * info.dwSize.Y, topLeft, &written);
                
            // 将光标移回左上角 | Move cursor back to top-left
            SetConsoleCursorPosition(hConsole_, topLeft);
        }
    }

    /**
     * 获取控制台窗口大小
     * Get console window size
     * 
     * @return 包含宽度和高度的对组 | Pair containing width and height
     */
    std::pair<int, int> getConsoleSize() const {
        if (initialized_) {
            CONSOLE_SCREEN_BUFFER_INFO info;
            GetConsoleScreenBufferInfo(hConsole_, &info);
            // 计算可见窗口大小 | Calculate visible window size
            return {info.srWindow.Right - info.srWindow.Left + 1,
                   info.srWindow.Bottom - info.srWindow.Top + 1};
        }
        return {80, 25};  // 默认大小 | Default size
    }

    /**
     * 将RGB颜色近似转换为Windows控制台16色
     * Approximate RGB color to Windows console 16-color
     * 
     * @param r 红色分量(0-255) | Red component (0-255)
     * @param g 绿色分量(0-255) | Green component (0-255)
     * @param b 蓝色分量(0-255) | Blue component (0-255)
     * @return Windows控制台颜色属性 | Windows console color attribute
     */
    WORD rgbToWin32Color(int r, int g, int b) const {
        // 简单的RGB到16色映射算法 | Simple RGB to 16-color mapping algorithm
        bool isRed = r > 128;    // 红色分量是否足够高 | Is red component high enough
        bool isGreen = g > 128;  // 绿色分量是否足够高 | Is green component high enough
        bool isBlue = b > 128;   // 蓝色分量是否足够高 | Is blue component high enough
        bool isBright = (r + g + b) > 384;  // 整体亮度是否足够高 | Is overall brightness high enough
        
        WORD color = 0;
        // 根据各分量设置对应的位 | Set corresponding bits based on components
        if (isRed) color |= FOREGROUND_RED;
        if (isGreen) color |= FOREGROUND_GREEN;
        if (isBlue) color |= FOREGROUND_BLUE;
        if (isBright) color |= FOREGROUND_INTENSITY;
        
        // 如果结果为0（黑色），返回白色作为默认值 | If result is 0 (black), return white as default
        return color ? color : win32_colors::WHITE;
    }

    /**
     * 析构函数，重置控制台颜色
     * Destructor, resets console color
     */
    ~Win32Console() {
        if (initialized_) {
            resetColor();  // 恢复原始颜色 | Restore original color
        }
    }
};

#else // 非Windows平台（Unix/Linux/macOS等） | Non-Windows platforms (Unix/Linux/macOS etc.)

/**
 * ANSI转义序列命名空间
 * ANSI escape sequence namespace
 * 
 * 这个命名空间为非Windows平台定义了ANSI转义序列常量，
 * 用于控制终端文本颜色和样式。
 * 
 * This namespace defines ANSI escape sequence constants for non-Windows platforms,
 * used to control terminal text colors and styles.
 */
namespace ansi {
    // 基础转义序列 | Basic escape sequences
    constexpr const char* ESC = "\033[";     // ANSI转义序列前缀 | ANSI escape sequence prefix
    constexpr const char* RESET = "\033[0m"; // 重置所有属性 | Reset all attributes
    
    // 基本前景色 | Basic foreground colors
    constexpr const char* BLACK = "\033[30m";   // 黑色文本 | Black text
    constexpr const char* RED = "\033[31m";     // 红色文本 | Red text
    constexpr const char* GREEN = "\033[32m";   // 绿色文本 | Green text
    constexpr const char* YELLOW = "\033[33m";  // 黄色文本 | Yellow text
    constexpr const char* BLUE = "\033[34m";    // 蓝色文本 | Blue text
    constexpr const char* MAGENTA = "\033[35m"; // 洋红色文本 | Magenta text
    constexpr const char* CYAN = "\033[36m";    // 青色文本 | Cyan text
    constexpr const char* WHITE = "\033[37m";   // 白色文本 | White text
    
    // 亮色前景色 | Bright foreground colors
    constexpr const char* BRIGHT_BLACK = "\033[90m";   // 亮黑/灰色文本 | Bright black/gray text
    constexpr const char* BRIGHT_RED = "\033[91m";     // 亮红色文本 | Bright red text
    constexpr const char* BRIGHT_GREEN = "\033[92m";   // 亮绿色文本 | Bright green text
    constexpr const char* BRIGHT_YELLOW = "\033[93m";  // 亮黄色文本 | Bright yellow text
    constexpr const char* BRIGHT_BLUE = "\033[94m";    // 亮蓝色文本 | Bright blue text
    constexpr const char* BRIGHT_MAGENTA = "\033[95m"; // 亮洋红色文本 | Bright magenta text
    constexpr const char* BRIGHT_CYAN = "\033[96m";    // 亮青色文本 | Bright cyan text
    constexpr const char* BRIGHT_WHITE = "\033[97m";   // 亮白色文本 | Bright white text
    
    // 文本样式 | Text styles
    constexpr const char* BOLD = "\033[1m";         // 粗体文本 | Bold text
    constexpr const char* DIM = "\033[2m";          // 暗淡文本 | Dim text
    constexpr const char* ITALIC = "\033[3m";       // 斜体文本 | Italic text
    constexpr const char* UNDERLINE = "\033[4m";    // 下划线文本 | Underlined text
    constexpr const char* BLINK = "\033[5m";        // 闪烁文本 | Blinking text
    constexpr const char* REVERSE = "\033[7m";      // 反色文本 | Reversed text
    constexpr const char* STRIKETHROUGH = "\033[9m"; // 删除线文本 | Strikethrough text
}
#endif

/**
 * 跨平台颜色控制类
 * Cross-platform color controller class
 * 
 * 这个类提供了统一的颜色和样式设置接口，在不同平台上使用相应的实现。
 * 在Windows上使用Win32Console API，在其他平台上使用ANSI转义序列。
 * 
 * This class provides a unified interface for color and style settings,
 * using the appropriate implementation on different platforms.
 * On Windows it uses the Win32Console API, on other platforms it uses ANSI escape sequences.
 */
class ColorController {
public:
    /**
     * 颜色枚举，定义了支持的所有颜色
     * Color enumeration defining all supported colors
     */
    enum class Color {
        BLACK,        // 黑色 | Black
        RED,          // 红色 | Red
        GREEN,        // 绿色 | Green
        YELLOW,       // 黄色 | Yellow
        BLUE,         // 蓝色 | Blue
        MAGENTA,      // 洋红色 | Magenta
        CYAN,         // 青色 | Cyan
        WHITE,        // 白色 | White
        BRIGHT_BLACK, // 亮黑色/灰色 | Bright black/gray
        BRIGHT_RED,   // 亮红色 | Bright red
        BRIGHT_GREEN, // 亮绿色 | Bright green
        BRIGHT_YELLOW,// 亮黄色 | Bright yellow
        BRIGHT_BLUE,  // 亮蓝色 | Bright blue
        BRIGHT_MAGENTA,// 亮洋红色 | Bright magenta
        BRIGHT_CYAN,  // 亮青色 | Bright cyan
        BRIGHT_WHITE, // 亮白色 | Bright white
        RESET         // 重置为默认颜色 | Reset to default color
    };

    /**
     * 设置控制台文本颜色
     * Set console text color
     * 
     * @param color 要设置的颜色 | Color to set
     */
    static void setColor(Color color) {
#ifdef _WIN32
        // Windows平台实现 | Windows platform implementation
        auto& console = Win32Console::getInstance(); // 获取Win32控制台单例 | Get Win32Console singleton
        WORD winColor;
        
        // 将颜色枚举映射到Windows控制台颜色 | Map color enum to Windows console color
        switch (color) {
            case Color::BLACK: winColor = win32_colors::BLACK; break;
            case Color::RED: winColor = win32_colors::DARK_RED; break;
            case Color::GREEN: winColor = win32_colors::DARK_GREEN; break;
            case Color::YELLOW: winColor = win32_colors::DARK_YELLOW; break;
            case Color::BLUE: winColor = win32_colors::DARK_BLUE; break;
            case Color::MAGENTA: winColor = win32_colors::DARK_MAGENTA; break;
            case Color::CYAN: winColor = win32_colors::DARK_CYAN; break;
            case Color::WHITE: winColor = win32_colors::GRAY; break;
            case Color::BRIGHT_BLACK: winColor = win32_colors::DARK_GRAY; break;
            case Color::BRIGHT_RED: winColor = win32_colors::RED; break;
            case Color::BRIGHT_GREEN: winColor = win32_colors::GREEN; break;
            case Color::BRIGHT_YELLOW: winColor = win32_colors::YELLOW; break;
            case Color::BRIGHT_BLUE: winColor = win32_colors::BLUE; break;
            case Color::BRIGHT_MAGENTA: winColor = win32_colors::MAGENTA; break;
            case Color::BRIGHT_CYAN: winColor = win32_colors::CYAN; break;
            case Color::BRIGHT_WHITE: winColor = win32_colors::WHITE; break;
            case Color::RESET: 
            default: 
                console.resetColor(); // 重置为原始颜色 | Reset to original color
                return;
        }
        console.setColor(winColor); // 应用颜色设置 | Apply color setting
#else
        // 非Windows平台实现 | Non-Windows platform implementation
        const char* ansiColor;
        
        // 将颜色枚举映射到ANSI转义序列 | Map color enum to ANSI escape sequence
        switch (color) {
            case Color::BLACK: ansiColor = ansi::BLACK; break;
            case Color::RED: ansiColor = ansi::RED; break;
            case Color::GREEN: ansiColor = ansi::GREEN; break;
            case Color::YELLOW: ansiColor = ansi::YELLOW; break;
            case Color::BLUE: ansiColor = ansi::BLUE; break;
            case Color::MAGENTA: ansiColor = ansi::MAGENTA; break;
            case Color::CYAN: ansiColor = ansi::CYAN; break;
            case Color::WHITE: ansiColor = ansi::WHITE; break;
            case Color::BRIGHT_BLACK: ansiColor = ansi::BRIGHT_BLACK; break;
            case Color::BRIGHT_RED: ansiColor = ansi::BRIGHT_RED; break;
            case Color::BRIGHT_GREEN: ansiColor = ansi::BRIGHT_GREEN; break;
            case Color::BRIGHT_YELLOW: ansiColor = ansi::BRIGHT_YELLOW; break;
            case Color::BRIGHT_BLUE: ansiColor = ansi::BRIGHT_BLUE; break;
            case Color::BRIGHT_MAGENTA: ansiColor = ansi::BRIGHT_MAGENTA; break;
            case Color::BRIGHT_CYAN: ansiColor = ansi::BRIGHT_CYAN; break;
            case Color::BRIGHT_WHITE: ansiColor = ansi::BRIGHT_WHITE; break;
            case Color::RESET: 
            default: 
                ansiColor = ansi::RESET; // 重置所有属性 | Reset all attributes
                break;
        }
        std::cout << ansiColor; // 输出ANSI转义序列 | Output ANSI escape sequence
#endif
    }

    /**
     * 设置RGB颜色
     * Set RGB color
     * 
     * @param r 红色分量(0-255) | Red component (0-255)
     * @param g 绿色分量(0-255) | Green component (0-255)
     * @param b 蓝色分量(0-255) | Blue component (0-255)
     */
    static void setRGBColor(int r, int g, int b) {
#ifdef _WIN32
        // Windows平台实现 - 将RGB近似映射到16色 | Windows platform implementation - approximate RGB to 16 colors
        auto& console = Win32Console::getInstance();
        WORD winColor = console.rgbToWin32Color(r, g, b); // RGB转16色近似 | RGB to 16-color approximation
        console.setColor(winColor);
#else
        // 非Windows平台实现 - 使用真彩色ANSI序列 | Non-Windows platform implementation - use true color ANSI sequence
        std::cout << "\033[38;2;" << r << ";" << g << ";" << b << "m"; // ANSI 24位真彩色 | ANSI 24-bit true color
#endif
    }

    /**
     * 设置文本粗体样式
     * Set text bold style
     * 
     * @param enable 是否启用粗体 | Whether to enable bold
     */
    static void setBold(bool enable) {
#ifdef _WIN32
        // Windows平台实现 - 使用高亮度模拟粗体 | Windows platform implementation - simulate bold with high intensity
        auto& console = Win32Console::getInstance();
        WORD currentColor = console.getCurrentColor();
        if (enable) {
            // 设置高亮位来模拟粗体 | Set intensity bit to simulate bold
            console.setColor(currentColor | FOREGROUND_INTENSITY);
        } else {
            // 清除高亮位 | Clear intensity bit
            console.setColor(currentColor & ~FOREGROUND_INTENSITY);
        }
#else
        // 非Windows平台实现 - 使用ANSI粗体序列 | Non-Windows platform implementation - use ANSI bold sequence
        if (enable) {
            std::cout << ansi::BOLD; // 启用粗体 | Enable bold
        } else {
            std::cout << ansi::RESET; // 重置样式 | Reset style
        }
#endif
    }
};

/**
 * 颜色包装器类
 * Color wrapper class
 * 
 * 这个类封装了颜色设置，便于在流式输出中使用。
 * 例如：std::cout << ColorWrapper(ColorController::Color::RED) << "红色文本" << ColorWrapper(ColorController::Color::RESET);
 * 
 * This class encapsulates color settings for easy use in stream output.
 * Example: std::cout << ColorWrapper(ColorController::Color::RED) << "Red text" << ColorWrapper(ColorController::Color::RESET);
 */
class ColorWrapper {
private:
    ColorController::Color color_; // 存储的颜色枚举值 | Stored color enumeration value
    
public:
    /**
     * 构造函数
     * Constructor
     * 
     * @param color 要使用的颜色 | Color to use
     */
    explicit ColorWrapper(ColorController::Color color) : color_(color) {}
    
    /**
     * 输出流操作符重载，使对象可以直接用于流式输出
     * Output stream operator overload, allowing the object to be used directly in stream output
     * 
     * @param os 输出流 | Output stream
     * @param wrapper 颜色包装器对象 | Color wrapper object
     * @return 输出流引用，用于链式调用 | Output stream reference for chaining
     */
    friend std::ostream& operator<<(std::ostream& os, const ColorWrapper& wrapper) {
        ColorController::setColor(wrapper.color_); // 应用颜色设置 | Apply color setting
        return os;
    }
};

/**
 * RGB颜色包装器类
 * RGB color wrapper class
 * 
 * 这个类封装了RGB颜色设置，便于在流式输出中使用。
 * 例如：std::cout << RGBColorWrapper(255, 0, 0) << "红色文本" << ColorWrapper(ColorController::Color::RESET);
 * 
 * This class encapsulates RGB color settings for easy use in stream output.
 * Example: std::cout << RGBColorWrapper(255, 0, 0) << "Red text" << ColorWrapper(ColorController::Color::RESET);
 */
class RGBColorWrapper {
private:
    int r_, g_, b_; // RGB颜色分量 | RGB color components
    
public:
    /**
     * 构造函数
     * Constructor
     * 
     * @param r 红色分量(0-255) | Red component (0-255)
     * @param g 绿色分量(0-255) | Green component (0-255)
     * @param b 蓝色分量(0-255) | Blue component (0-255)
     */
    RGBColorWrapper(int r, int g, int b) : r_(r), g_(g), b_(b) {}
    
    /**
     * 输出流操作符重载，使对象可以直接用于流式输出
     * Output stream operator overload, allowing the object to be used directly in stream output
     * 
     * @param os 输出流 | Output stream
     * @param wrapper RGB颜色包装器对象 | RGB color wrapper object
     * @return 输出流引用，用于链式调用 | Output stream reference for chaining
     */
    friend std::ostream& operator<<(std::ostream& os, const RGBColorWrapper& wrapper) {
        ColorController::setRGBColor(wrapper.r_, wrapper.g_, wrapper.b_); // 应用RGB颜色设置 | Apply RGB color setting
        return os;
    }
};

/**
 * 字体样式包装器类
 * Font style wrapper class
 * 
 * 这个类封装了字体样式设置（目前支持粗体），便于在流式输出中使用。
 * 例如：std::cout << FontStyleWrapper(true) << "粗体文本" << FontStyleWrapper(false);
 * 
 * This class encapsulates font style settings (currently supports bold) for easy use in stream output.
 * Example: std::cout << FontStyleWrapper(true) << "Bold text" << FontStyleWrapper(false);
 */
class FontStyleWrapper {
private:
    bool enable_; // 是否启用样式 | Whether to enable the style
    
public:
    /**
     * 构造函数
     * Constructor
     * 
     * @param enable 是否启用样式 | Whether to enable the style
     */
    explicit FontStyleWrapper(bool enable) : enable_(enable) {}
    
    /**
     * 输出流操作符重载，使对象可以直接用于流式输出
     * Output stream operator overload, allowing the object to be used directly in stream output
     * 
     * @param os 输出流 | Output stream
     * @param wrapper 字体样式包装器对象 | Font style wrapper object
     * @return 输出流引用，用于链式调用 | Output stream reference for chaining
     */
    friend std::ostream& operator<<(std::ostream& os, const FontStyleWrapper& wrapper) {
        ColorController::setBold(wrapper.enable_); // 应用粗体样式设置 | Apply bold style setting
        return os;
    }
};

/**
 * 延时操作类
 * Sleep operation class
 * 
 * 这个类封装了延时操作，便于在流式输出中使用。
 * 例如：std::cout << "等待开始" << TSleep(1000) << "等待结束";
 * 
 * This class encapsulates sleep operations for easy use in stream output.
 * Example: std::cout << "Wait starts" << TSleep(1000) << "Wait ends";
 */
class TSleep {
private:
    int milliseconds_; // 延时的毫秒数 | Milliseconds to sleep
    
public:
    /**
     * 构造函数
     * Constructor
     * 
     * @param ms 延时的毫秒数 | Milliseconds to sleep
     */
    explicit TSleep(int ms) : milliseconds_(ms) {}
    
    /**
     * 执行延时操作
     * Execute sleep operation
     */
    void execute() const {
        // 使用标准库的线程休眠功能 | Use standard library thread sleep functionality
        std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds_));
    }
    
    /**
     * 输出流操作符重载，使对象可以直接用于流式输出
     * Output stream operator overload, allowing the object to be used directly in stream output
     * 
     * @param os 输出流 | Output stream
     * @param sleep 延时操作对象 | Sleep operation object
     * @return 输出流引用，用于链式调用 | Output stream reference for chaining
     */
    friend std::ostream& operator<<(std::ostream& os, const TSleep& sleep) {
        sleep.execute(); // 执行延时 | Execute sleep
        return os;
    }
};

// 全局颜色常量，便于直接使用 | Global color constants for easy use
// 注意：这些常量已在文件顶部定义为宏 | Note: These constants are already defined as macros at the top of the file

/**
 * RGB颜色宏，便于流式创建RGB颜色
 * RGB color macro for easy creation of RGB colors in stream
 * 
 * 这个宏允许直接在流式输出中使用RGB颜色
 * 例如：std::cout << TCOLOR_RGB(255, 0, 0) << "红色文本" << TCOLOR_RESET;
 * 
 * This macro allows direct use of RGB colors in stream output
 * Example: std::cout << TCOLOR_RGB(255, 0, 0) << "Red text" << TCOLOR_RESET;
 * 
 * @param r 红色分量(0-255) | Red component (0-255)
 * @param g 绿色分量(0-255) | Green component (0-255)
 * @param b 蓝色分量(0-255) | Blue component (0-255)
 * @return RGBColorWrapper对象 | RGBColorWrapper object
 */
#define TCOLOR_RGB(r, g, b) tc::RGBColorWrapper(r, g, b)

/**
 * 自定义输出流类
 * Custom output stream class
 * 
 * 这个类提供了增强的输出流功能，支持链式输出和自定义类型。
 * 它可以处理颜色、RGB颜色、字体样式和延时操作等特殊类型。
 * 
 * This class provides enhanced output stream functionality, supporting chain output and custom types.
 * It can handle special types like colors, RGB colors, font styles, and sleep operations.
 */
class TOut {
private:
    std::ostream& os_; // 底层输出流引用 | Reference to underlying output stream
    
public:
    /**
     * 构造函数
     * Constructor
     * 
     * @param os 底层输出流，默认为标准输出 | Underlying output stream, defaults to standard output
     */
    explicit TOut(std::ostream& os = std::cout) : os_(os) {
#ifdef _WIN32
        // 确保Windows控制台已初始化 | Ensure Windows console is initialized
        Win32Console::getInstance();
#endif
    }
    
    /**
     * 通用输出操作符，处理任意类型的值
     * Generic output operator, handles values of any type
     * 
     * @param value 要输出的值 | Value to output
     * @return 自身引用，用于链式调用 | Self reference for chaining
     */
    template<typename T>
    TOut& operator<<(T&& value) {
        os_ << std::forward<T>(value); // 转发值到底层流 | Forward value to underlying stream
        return *this;
    }
    
    /**
     * 特化的输出操作符，处理延时操作
     * Specialized output operator for sleep operations
     * 
     * @param sleep 延时操作对象 | Sleep operation object
     * @return 自身引用，用于链式调用 | Self reference for chaining
     */
    TOut& operator<<(const TSleep& sleep) {
        sleep.execute(); // 执行延时 | Execute sleep
        return *this;
    }
    
    /**
     * 特化的输出操作符，处理颜色包装器
     * Specialized output operator for color wrappers
     * 
     * @param color 颜色包装器对象 | Color wrapper object
     * @return 自身引用，用于链式调用 | Self reference for chaining
     */
    TOut& operator<<(const ColorWrapper& color) {
        os_ << color; // 应用颜色设置 | Apply color setting
        return *this;
    }
    
    /**
     * 特化的输出操作符，处理RGB颜色包装器
     * Specialized output operator for RGB color wrappers
     * 
     * @param color RGB颜色包装器对象 | RGB color wrapper object
     * @return 自身引用，用于链式调用 | Self reference for chaining
     */
    TOut& operator<<(const RGBColorWrapper& color) {
        os_ << color; // 应用RGB颜色设置 | Apply RGB color setting
        return *this;
    }
    
    /**
     * 特化的输出操作符，处理字体样式包装器
     * Specialized output operator for font style wrappers
     * 
     * @param style 字体样式包装器对象 | Font style wrapper object
     * @return 自身引用，用于链式调用 | Self reference for chaining
     */
    TOut& operator<<(const FontStyleWrapper& style) {
        os_ << style; // 应用字体样式设置 | Apply font style setting
        return *this;
    }
    
    /**
     * 支持标准流操作符，如std::endl
     * Support for standard stream manipulators like std::endl
     * 
     * @param manip 流操作符函数 | Stream manipulator function
     * @return 自身引用，用于链式调用 | Self reference for chaining
     */
    TOut& operator<<(std::ostream& (*manip)(std::ostream&)) {
        os_ << manip; // 应用流操作符 | Apply stream manipulator
        return *this;
    }
    
    /**
     * 获取底层输出流
     * Get underlying output stream
     * 
     * @return 底层输出流引用 | Reference to underlying output stream
     */
    std::ostream& stream() { return os_; }
};

/**
 * 全局输出流对象，类似std::cout但具有增强功能
 * Global output stream object, similar to std::cout but with enhanced features
 * 
 * 这个对象可以用于所有标准输出操作，并支持颜色、样式和延时等特殊功能。
 * 例如：tc::tout << TCOLOR_RED << "红色文本" << TCOLOR_RESET << std::endl;
 * 
 * This object can be used for all standard output operations and supports special features
 * like colors, styles, and sleep operations.
 * Example: tc::tout << TCOLOR_RED << "Red text" << TCOLOR_RESET << std::endl;
 */
static TOut tout(std::cout);

/**
 * 创建延时操作对象
 * Create sleep operation object
 * 
 * @param milliseconds 延时的毫秒数 | Milliseconds to sleep
 * @return TSleep对象，可用于流式输出 | TSleep object that can be used in stream output
 */
inline TSleep tsleep(int milliseconds) {
    return TSleep(milliseconds);
}

/**
 * 延时流操作符类
 * Sleep stream operator class
 * 
 * 这个类提供了另一种延时语法，使用左移操作符。
 * 例如：tc::tsleep_stream << 1000; // 延时1秒
 * 
 * This class provides an alternative sleep syntax using the left shift operator.
 * Example: tc::tsleep_stream << 1000; // Sleep for 1 second
 */
class TSleepStream {
public:
    /**
     * 左移操作符重载，执行延时操作
     * Left shift operator overload, executes sleep operation
     * 
     * @param milliseconds 延时的毫秒数 | Milliseconds to sleep
     */
    void operator<<(int milliseconds) const {
        std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
    }
};

/**
 * 全局延时流对象
 * Global sleep stream object
 * 
 * 用于执行流式延时操作。
 * 例如：tc::tsleep_stream << 1000; // 延时1秒
 * 
 * Used for stream-style sleep operations.
 * Example: tc::tsleep_stream << 1000; // Sleep for 1 second
 */
static TSleepStream tsleep_stream;

/**
 * 终端控制函数命名空间
 * Terminal control functions namespace
 * 
 * 这个命名空间提供了一组用于控制终端的函数，如清屏、移动光标和获取终端尺寸。
 * 这些函数在不同平台上使用相应的实现，提供统一的接口。
 * 
 * This namespace provides a set of functions for terminal control, such as clearing the screen,
 * moving the cursor, and getting terminal size. These functions use the appropriate implementation
 * on different platforms, providing a unified interface.
 */
namespace terminal {
    /**
     * 清空终端屏幕
     * Clear terminal screen
     * 
     * 清除终端中的所有内容并将光标移动到左上角。
     * Clears all content in the terminal and moves the cursor to the top-left corner.
     */
    inline void clear() {
#ifdef _WIN32
        // Windows平台实现 | Windows platform implementation
        Win32Console::getInstance().clearScreen();
#else
        // 非Windows平台实现 | Non-Windows platform implementation
        std::cout << "\033[2J\033[H"; // ANSI清屏序列 | ANSI clear screen sequence
#endif
    }
    
    /**
     * 移动光标到指定位置
     * Move cursor to specified position
     * 
     * @param x 列坐标（从1开始） | Column coordinate (1-based)
     * @param y 行坐标（从1开始） | Row coordinate (1-based)
     */
    inline void moveCursor(int x, int y) {
#ifdef _WIN32
        // Windows平台实现 | Windows platform implementation
        Win32Console::getInstance().moveCursor(x - 1, y - 1); // Win32API是0基索引 | Win32 API is 0-based
#else
        // 非Windows平台实现 | Non-Windows platform implementation
        std::cout << "\033[" << y << ";" << x << "H"; // ANSI光标定位序列 | ANSI cursor positioning sequence
#endif
    }
    
    /**
     * 获取终端窗口大小
     * Get terminal window size
     * 
     * @return 包含宽度和高度的对组 | Pair containing width and height
     */
    inline std::pair<int, int> getSize() {
#ifdef _WIN32
        // Windows平台实现 | Windows platform implementation
        return Win32Console::getInstance().getConsoleSize();
#else
        // 非Windows平台实现 | Non-Windows platform implementation
        struct winsize w;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        return {w.ws_col, w.ws_row};
#endif
    }
}

/**
 * 便利的颜色函数
 * Convenient color functions
 * 
 * 这些函数提供了简单的方式来为文本添加颜色，返回已着色的字符串。
 * 这些函数不会直接输出到终端，而是返回可以存储或进一步处理的字符串。
 * 
 * These functions provide a simple way to add color to text, returning the colored string.
 * They don't output directly to the terminal but return a string that can be stored or further processed.
 */

/**
 * 为文本添加指定颜色
 * Add specified color to text
 * 
 * @param text 要着色的文本 | Text to colorize
 * @param color 要应用的颜色 | Color to apply
 * @return 带有颜色代码的字符串 | String with color codes
 */
inline std::string colorize(const std::string& text, ColorController::Color color) {
    std::ostringstream oss;
    // 添加颜色代码，文本，然后重置颜色 | Add color code, text, then reset color
    oss << ColorWrapper(color) << text << ColorWrapper(ColorController::Color::RESET);
    return oss.str();
}

/**
 * 为文本添加红色
 * Add red color to text
 * 
 * @param text 要着色的文本 | Text to colorize
 * @return 红色文本字符串 | Red text string
 */
inline std::string red(const std::string& text) {
    return colorize(text, ColorController::Color::RED);
}

/**
 * 为文本添加绿色
 * Add green color to text
 * 
 * @param text 要着色的文本 | Text to colorize
 * @return 绿色文本字符串 | Green text string
 */
inline std::string green(const std::string& text) {
    return colorize(text, ColorController::Color::GREEN);
}

/**
 * 为文本添加蓝色
 * Add blue color to text
 * 
 * @param text 要着色的文本 | Text to colorize
 * @return 蓝色文本字符串 | Blue text string
 */
inline std::string blue(const std::string& text) {
    return colorize(text, ColorController::Color::BLUE);
}

/**
 * 为文本添加黄色
 * Add yellow color to text
 * 
 * @param text 要着色的文本 | Text to colorize
 * @return 黄色文本字符串 | Yellow text string
 */
inline std::string yellow(const std::string& text) {
    return colorize(text, ColorController::Color::YELLOW);
}

// ========== 进度条类 | Progress bar class ========== //
/**
 * 进度条类
 * Progress bar class
 * 
 * 这个类提供了一个可自定义的文本进度条，用于显示操作的进度。
 * 进度条可以自定义宽度、完成和未完成部分的字符，以及颜色。
 * 
 * This class provides a customizable text progress bar for displaying operation progress.
 * The progress bar can be customized with width, characters for completed and uncompleted parts, and color.
 */
class ProgressBar {
private:
    int width_;           // 进度条宽度（字符数） | Progress bar width (in characters)
    std::string done_;    // 已完成部分的字符 | Character for completed parts
    std::string todo_;    // 未完成部分的字符 | Character for uncompleted parts
    std::string color_;   // 进度条颜色（ANSI颜色代码） | Progress bar color (ANSI color code)
    
public:
    /**
     * 构造函数
     * Constructor
     * 
     * @param width 进度条宽度 | Progress bar width
     * @param done 已完成部分的字符，默认为"#" | Character for completed parts, defaults to "#"
     * @param todo 未完成部分的字符，默认为"-" | Character for uncompleted parts, defaults to "-"
     * @param color 进度条颜色，默认为绿色 | Progress bar color, defaults to green
     */
    ProgressBar(int width, std::string done = "#", std::string todo = "-", std::string color = TCOLOR_GREEN)
        : width_(width), done_(std::move(done)), todo_(std::move(todo)), color_(std::move(color)) {}
    
    /**
     * 显示进度条
     * Show progress bar
     * 
     * @param progress 进度值(0.0-1.0) | Progress value (0.0-1.0)
     * @param msg 显示在进度条旁的消息 | Message to display next to the progress bar
     */
    void show(double progress, const std::string& msg = "Loading...") {
        // 计算已完成部分的位置 | Calculate position of completed part
        int pos = static_cast<int>(width_ * progress);
        
        // 输出进度条 | Output progress bar
        std::cout << "\r" << color_ << "["; // 回车并开始进度条 | Carriage return and start progress bar
        
        // 绘制进度条主体 | Draw progress bar body
        for (int i = 0; i < width_; ++i) {
            std::cout << (i < pos ? done_ : todo_); // 根据位置输出已完成或未完成字符 | Output completed or uncompleted character based on position
        }
        
        // 输出百分比和消息 | Output percentage and message
        std::cout << "] " << int(progress * 100) << "% " << msg << TCOLOR_RESET << std::flush;
    }
    
    /**
     * 完成进度条
     * Finish progress bar
     * 
     * 显示100%进度并换行
     * Shows 100% progress and adds a newline
     * 
     * @param content 完成时显示的消息 | Message to display when finished
     */
    void finish(std::string content = "Finished") {
        show(1.0, content); // 显示100%进度 | Show 100% progress
        std::cout << std::endl; // 换行 | Add newline
    }
};


} // namespace tc 结束 | End of namespace tc

// ===== 系统相关API及全局宏 | System-related APIs and global macros =====
/**
 * 系统相关功能部分
 * System-related functionality section
 * 
 * 这部分提供了与系统交互的功能，如获取系统时间、执行系统命令等。
 * This section provides functionality for interacting with the system,
 * such as getting system time, executing system commands, etc.
 */
#include <ctime>    // 时间相关函数 | Time-related functions
#include <cstdlib>  // 系统函数，如system() | System functions like system()
#include <cstring>  // 字符串处理函数 | String handling functions
#ifdef _WIN32
    #include <windows.h> // Windows特定API | Windows-specific API
#endif

// --- 系统时间常量 | System time constants ---
/**
 * 系统时间常量，用于getSystemTime函数
 * System time constants for getSystemTime function
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
     * 
     * This function returns various components of the current system time,
     * such as year, month, day, etc., or returns the Unix timestamp
     * (seconds since January 1, 1970).
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
}

// --- systemConsole 函数 | systemConsole functions ---
namespace tc {
    /**
     * 执行系统命令（C字符串版本）
     * Execute system command (C string version)
     * 
     * 这个函数使用系统的命令处理器执行指定的命令。
     * This function executes the specified command using the system's command processor.
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
     * This function is an overloaded version of systemConsole that accepts C++ strings.
     * 
     * @param cmd 要执行的命令 | Command to execute
     * @return 命令的退出状态 | Exit status of the command
     */
    inline int systemConsole(const std::string& cmd) {
        return std::system(cmd.c_str());
    }
    
    /**
     * 执行系统命令（宽字符版本）
     * Execute system command (wide character version)
     * 
     * 这个函数是systemConsole的宽字符版本，用于支持Unicode命令。
     * 在Windows上直接使用_wsystem，在其他平台上将宽字符转换为UTF-8。
     * 
     * This function is a wide character version of systemConsole for Unicode command support.
     * On Windows it uses _wsystem directly, on other platforms it converts wide characters to UTF-8.
     * 
     * @param cmd 要执行的宽字符命令 | Wide character command to execute
     * @return 命令的退出状态 | Exit status of the command
     */
    inline int systemConsoleW(const wchar_t* cmd) {
        #ifdef _WIN32
            // Windows平台直接使用宽字符系统调用 | Windows platform uses wide character system call directly
            return _wsystem(cmd);
        #else
            // 非Windows平台需要转换为UTF-8 | Non-Windows platforms need conversion to UTF-8
            #include <locale>
            #include <codecvt>
            std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
            std::string utf8_cmd = converter.to_bytes(cmd);
            return system(utf8_cmd.c_str());
        #endif
    }
}

// --- 系统环境宏定义 | System environment macro definitions ---
/**
 * 操作系统类型常量
 * Operating system type constants
 * 
 * 这些宏定义了各种操作系统的标识符，用于systemCheck函数的返回值。
 * 每个操作系统类型都有一个唯一的数字代码。
 * 
 * These macros define identifiers for various operating systems,
 * used as return values for the systemCheck function.
 * Each OS type has a unique numeric code.
 */

// 未知操作系统 | Unknown operating system
#define OS_UNKNOWN      0    // 无法识别的操作系统 | Unrecognized operating system

// Windows系列 | Windows family
#define OS_WINDOWS      100  // 通用Windows标识 | Generic Windows identifier
#define OS_WINDOWSNT3   103  // Windows NT 3.x
#define OS_WINDOWSNT4   104  // Windows NT 4.0
#define OS_WINDOWSNT5   105  // Windows 2000/XP/2003 (NT 5.x)
#define OS_WINDOWSNT6   106  // Windows Vista/7/8/8.1 (NT 6.x)
#define OS_WINDOWSNT10  110  // Windows 10 (NT 10.0)
#define OS_WINDOWSNT11  111  // Windows 11 (NT 10.0 build 22000+)
#define OS_WIN95        195  // Windows 95
#define OS_WIN98        198  // Windows 98
#define OS_WINME        199  // Windows ME
#define OS_WINCE        120  // Windows CE

// Linux发行版 | Linux distributions
#define OS_LINUX        200  // 通用Linux标识 | Generic Linux identifier
#define OS_UBUNTU       201  // Ubuntu Linux
#define OS_DEBIAN       202  // Debian Linux
#define OS_FEDORA       203  // Fedora Linux
#define OS_CENTOS       204  // CentOS Linux
#define OS_REDHAT       205  // Red Hat Enterprise Linux
#define OS_SUSE         206  // SUSE/openSUSE Linux
#define OS_ARCH         207  // Arch Linux
#define OS_GENTOO       208  // Gentoo Linux
#define OS_SLACKWARE    209  // Slackware Linux
#define OS_ANDROID      210  // Android (基于Linux | Based on Linux)
#define OS_KALI         211  // Kali Linux
#define OS_MINT         212  // Linux Mint
#define OS_MANJARO      213  // Manjaro Linux
#define OS_ALPINE       214  // Alpine Linux
#define OS_RASPBIAN     215  // Raspbian
#define OS_DEEPIN       216  // Deepin Linux
#define OS_ELEMENTARY   217  // Elementary OS
#define OS_ZORIN        218  // Zorin OS
#define OS_POPOS        219  // Pop!_OS
#define OS_CHROMEOS     220  // Chrome OS/Chromium OS

// Apple操作系统 | Apple operating systems
// 现代macOS和Mac OS X版本 | Modern macOS and Mac OS X versions
#define OS_MACOS        300  // 通用macOS标识 | Generic macOS identifier
#define OS_MACOS_SONOMA 301  // macOS 14 Sonoma (2023)
#define OS_MACOS_VENTURA 302 // macOS 13 Ventura (2022)
#define OS_MACOS_MONTEREY 303 // macOS 12 Monterey (2021)
#define OS_MACOS_BIGSUR 304  // macOS 11 Big Sur (2020)
#define OS_MACOS_CATALINA 305 // macOS 10.15 Catalina (2019)
#define OS_MACOS_MOJAVE 306  // macOS 10.14 Mojave (2018)
#define OS_MACOS_HIGHSIERRA 307 // macOS 10.13 High Sierra (2017)
#define OS_MACOS_SIERRA 308  // macOS 10.12 Sierra (2016)
#define OS_OSX_ELCAPITAN 309 // OS X 10.11 El Capitan (2015)
#define OS_OSX_YOSEMITE 310  // OS X 10.10 Yosemite (2014)
#define OS_OSX_MAVERICKS 311 // OS X 10.9 Mavericks (2013)
#define OS_OSX_MOUNTAINLION 312 // OS X 10.8 Mountain Lion (2012)
#define OS_OSX_LION     313  // Mac OS X 10.7 Lion (2011)
#define OS_OSX_SNOWLEOPARD 314 // Mac OS X 10.6 Snow Leopard (2009)
#define OS_OSX_LEOPARD  315  // Mac OS X 10.5 Leopard (2007)
#define OS_OSX_TIGER    316  // Mac OS X 10.4 Tiger (2005)
#define OS_OSX_PANTHER  317  // Mac OS X 10.3 Panther (2003)
#define OS_OSX_JAGUAR   318  // Mac OS X 10.2 Jaguar (2002)
#define OS_OSX_PUMA     319  // Mac OS X 10.1 Puma (2001)
#define OS_OSX_CHEETAH  320  // Mac OS X 10.0 Cheetah (2001)
#define OS_OSX_BETA     321  // Mac OS X Public Beta (2000)

// 经典Macintosh系统 | Classic Macintosh systems
#define OS_MACOS9       330  // Mac OS 9 (1999)
#define OS_MACOS8       331  // Mac OS 8 (1997)
#define OS_MACOS7       332  // System 7 (1991)
#define OS_MACOS6       333  // System 6 (1988)
#define OS_MACOS5       334  // System 5 (1987)
#define OS_MACOS4       335  // System 4 (1987)
#define OS_MACOS3       336  // System 3 (1986)
#define OS_MACOS2       337  // System 2 (1985)
#define OS_MACOS1       338  // System 1 (1984)

// 其他Apple操作系统 | Other Apple operating systems
#define OS_IOS          350  // iOS (iPhone/iPod touch)
#define OS_IPADOS       351  // iPadOS (iPad)
#define OS_WATCHOS      352  // watchOS (Apple Watch)
#define OS_TVOS         353  // tvOS (Apple TV)
#define OS_VISIONOS     354  // visionOS (Apple Vision Pro)
#define OS_BRIDGEOS     355  // bridgeOS (Apple T2芯片 | Apple T2 chip)
#define OS_AUDIOOS      356  // audioOS (HomePod)

// BSD系列 | BSD family
#define OS_BSD          400  // 通用BSD标识 | Generic BSD identifier
#define OS_DRAGONFLY    401  // DragonFly BSD
#define OS_NETBSD       402  // NetBSD
#define OS_OPENBSD      403  // OpenBSD
#define OS_FREEBSD      404  // FreeBSD

// Unix系列 | Unix family
#define OS_UNIX         500  // 通用Unix标识 | Generic Unix identifier
#define OS_HURD         501  // GNU Hurd
#define OS_XENIX        502  // Xenix

// DOS和其他系统 | DOS and other systems
#define OS_DOS          600  // DOS
#define OS_PLAN9        601  // Plan 9
#define OS_INFERNO      602  // Inferno

// BeOS系列 | BeOS family
#define OS_BEOS         700  // BeOS
#define OS_HAIKU        701  // Haiku
#define OS_SYLLABLE     702  // Syllable
#define OS_MENUETOS     703  // MenuetOS
#define OS_REACTOS      704  // ReactOS
#define OS_KOLIBRIOS    705  // KolibriOS

// 商业Unix系统 | Commercial Unix systems
#define OS_AIX          800  // IBM AIX
#define OS_SOLARIS      810  // Oracle Solaris
#define OS_MINIX        820  // MINIX
#define OS_QNX          830  // QNX
#define OS_VMS          840  // VMS
#define OS_ZOS          841  // IBM z/OS
#define OS_OS400        842  // IBM OS/400
#define OS_TPF          843  // IBM TPF

// 其他操作系统 | Other operating systems
#define OS_AMIGAOS      850  // AmigaOS
#define OS_MORPHOS      851  // MorphOS
#define OS_FREEMINT     852  // FreeMiNT
#define OS_HPUX         860  // HP-UX
#define OS_IRIX         861  // IRIX
#define OS_SCO          862  // SCO
#define OS_OPENVMS      863  // OpenVMS
#define OS_RISCOS       870  // RISC OS
#define OS_OS2          900  // OS/2
#define OS_NEXTSTEP     910  // NeXTSTEP

// 嵌入式操作系统 | Embedded operating systems
#define OS_NUTTX        920  // NuttX
#define OS_ZEPHYR       921  // Zephyr
#define OS_CONTIKI      922  // Contiki
#define OS_RIOT         923  // RIOT

// 新兴操作系统 | Emerging operating systems
#define OS_FUCHSIA      950  // Google Fuchsia
#define OS_REDOX        951  // Redox OS
#define OS_HARMONY      952  // Harmony OS
#define OS_XJ380        953  // XJ380

// 嵌入式/实时操作系统 | Embedded/Real-time operating systems
#define OS_VXWORKS      1000 // VxWorks
#define OS_RTEMS        1001 // RTEMS
#define OS_FREERTOS     1002 // FreeRTOS
#define OS_THREADX      1003 // ThreadX
#define OS_INTEGRITY    1004 // INTEGRITY
#define OS_NUCLEUS      1005 // Nucleus RTOS
#define OS_UCOSII       1006 // μC/OS-II
#define OS_UCOSIII      1007 // μC/OS-III
#define OS_PSOS         1008 // pSOS
#define OS_ECOS         1009 // eCos

// --- systemCheck 函数 | systemCheck function ---
/**
 * 系统检测相关功能
 * System detection functionality
 */
#include <string>     // 字符串处理 | String processing
#include <algorithm>  // 算法函数 | Algorithm functions

namespace tc {
    /**
     * 检测当前操作系统类型
     * Detect current operating system type
     * 
     * 这个函数通过各种平台特定的API和检测方法，
     * 识别当前运行的操作系统类型和版本。
     * 
     * This function identifies the current operating system type and version
     * through various platform-specific APIs and detection methods.
     * 
     * @return 操作系统类型代码（如OS_WINDOWS, OS_LINUX等） | Operating system type code (e.g., OS_WINDOWS, OS_LINUX, etc.)
     */
    inline int systemCheck() {
#if defined(_WIN32) || defined(_WIN64)
        // 检测ReactOS (基于Windows NT的开源操作系统)
        char buf[256] = {0};
        DWORD size = sizeof(buf);
        if (RegGetValueA(HKEY_LOCAL_MACHINE, "SOFTWARE\\ReactOS", "Version", RRF_RT_REG_SZ, NULL, buf, &size) == ERROR_SUCCESS) {
            return OS_REACTOS;
        }

        // 优先用RtlGetVersion获取真实主版本号
        typedef LONG (WINAPI *RtlGetVersionPtr)(PRTL_OSVERSIONINFOW);
        HMODULE hMod = ::GetModuleHandleW(L"ntdll.dll");
        if (hMod) {
            RtlGetVersionPtr fx = (RtlGetVersionPtr)::GetProcAddress(hMod, "RtlGetVersion");
            if (fx) {
                RTL_OSVERSIONINFOW rovi = {0};
                rovi.dwOSVersionInfoSize = sizeof(rovi);
                if (fx(&rovi) == 0) {
                    // 细分Windows主版本号
                    if (rovi.dwMajorVersion == 3)  return OS_WINDOWSNT3;
                    if (rovi.dwMajorVersion == 4)  return OS_WINDOWSNT4;
                    if (rovi.dwMajorVersion == 5)  return OS_WINDOWSNT5;
                    if (rovi.dwMajorVersion == 6)  return OS_WINDOWSNT6;
                    if (rovi.dwMajorVersion == 10) {
                        // Win10/11区分：Win11为10.0.22000及以上
                        if (rovi.dwBuildNumber >= 22000) return OS_WINDOWSNT11;
                        else return OS_WINDOWSNT10;
                    }
                    if (rovi.dwMajorVersion > 10) return OS_WINDOWS; // 未来主版本
                }
            }
        }
        // 兼容老方案
        OSVERSIONINFOEX osvi = {0};
        osvi.dwOSVersionInfoSize = sizeof(osvi);
        if (GetVersionEx((OSVERSIONINFO*)&osvi)) {
            if (osvi.dwMajorVersion == 3)  return OS_WINDOWSNT3;
            if (osvi.dwMajorVersion == 4)  return OS_WINDOWSNT4;
            if (osvi.dwMajorVersion == 5)  return OS_WINDOWSNT5;
            if (osvi.dwMajorVersion == 6)  return OS_WINDOWSNT6;
            if (osvi.dwMajorVersion == 10) {
                if (osvi.dwBuildNumber >= 22000) return OS_WINDOWSNT11;
                else return OS_WINDOWSNT10;
            }
            if (osvi.dwMajorVersion > 10) return OS_WINDOWSNT11;
            // 9x系列
            if (osvi.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS) {
                if (osvi.dwMinorVersion == 0) return OS_WIN95;
                if (osvi.dwMinorVersion == 10) return OS_WIN98;
                if (osvi.dwMinorVersion == 90) return OS_WINME;
            }
            // CE
            #ifdef VER_PLATFORM_WIN32_CE
                if (osvi.dwPlatformId == VER_PLATFORM_WIN32_CE) return OS_WINCE;
            #endif
        }
    return OS_WINDOWS;

#elif defined(__ANDROID__)
        return OS_ANDROID;

#elif defined(__HAIKU__)
        return OS_HAIKU;

#elif defined(__SYLLABLE__)
        return OS_SYLLABLE;

#elif defined(__REACTOS__)
        return OS_REACTOS;

#elif defined(__kolibri__) || defined(__KOLIBRI__)
        return OS_KOLIBRIOS;

#elif defined(_AIX) || defined(__AIX__)
        return OS_AIX;

#elif defined(__sun) && defined(__SVR4)
        return OS_SOLARIS;

#elif defined(__minix)
        return OS_MINIX;

#elif defined(__QNX__) || defined(__QNXNTO__)
        return OS_QNX;

#elif defined(__INTEGRITY)
        return OS_INTEGRITY;

#elif defined(__VMS) || defined(__VMS__)
        return OS_VMS;

#elif defined(__MVS__) || defined(__HOS_MVS__) || defined(__TOS_MVS__)
        return OS_ZOS;

#elif defined(__OS400__)
        return OS_OS400;

#elif defined(__amigaos__)
        return OS_AMIGAOS;

#elif defined(__MORPHOS__)
        return OS_MORPHOS;

#elif defined(__MINT__)
        return OS_FREEMINT;

#elif defined(__hpux) || defined(__hpux__)
        return OS_HPUX;

#elif defined(__sgi)
        return OS_IRIX;

#elif defined(__SCO_VERSION__)
        return OS_SCO;

#elif defined(__OPENVMS)
        return OS_OPENVMS;

#elif defined(__riscos) || defined(__riscos__)
        return OS_RISCOS;

#elif defined(__APPLE__)
    #include <TargetConditionals.h>
    // 检测苹果各种操作系统
    #if defined(TARGET_OS_VISION) && TARGET_OS_VISION
        return OS_VISIONOS;  // visionOS (Apple Vision Pro)
    #elif defined(TARGET_OS_BRIDGE) && TARGET_OS_BRIDGE
        return OS_BRIDGEOS;  // bridgeOS (Apple T2芯片)
    #elif defined(TARGET_OS_WATCH) && TARGET_OS_WATCH
        return OS_WATCHOS;   // watchOS (Apple Watch)
    #elif defined(TARGET_OS_TV) && TARGET_OS_TV
        return OS_TVOS;      // tvOS (Apple TV)
    #elif defined(TARGET_OS_MACCATALYST) && TARGET_OS_MACCATALYST
        return OS_MACOS;     // Mac Catalyst (iPad应用运行在Mac上)
    #elif TARGET_OS_IPHONE
        // iOS设备进一步区分
        #if defined(TARGET_OS_IOS) && TARGET_OS_IOS
            // 检测是否为iPadOS (iOS 13+的iPad)
            #if defined(UI_USER_INTERFACE_IDIOM)
                if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad) {
                    // iOS 13及以上的iPad被认为运行iPadOS
                    #if defined(__IPHONE_OS_VERSION_MIN_REQUIRED) && __IPHONE_OS_VERSION_MIN_REQUIRED >= 130000
                        return OS_IPADOS;
                    #endif
                }
            #endif
            return OS_IOS;   // iOS (iPhone/iPod touch)
        #endif
        return OS_IOS;       // 默认iOS
    #elif defined(TARGET_OS_OSX) && TARGET_OS_OSX
        // macOS版本检测
        #include <sys/sysctl.h>
        char str[256];
        size_t size = sizeof(str);
        int ret = sysctlbyname("kern.osrelease", str, &size, NULL, 0);
        
        if (ret == 0) {
            // 解析内核版本号，格式为: 22.5.0 (macOS 13.4 Ventura)
            int kernel_major = 0;
            sscanf(str, "%d", &kernel_major);
            
            // 根据Darwin内核版本映射到macOS版本
            // 参考: https://en.wikipedia.org/wiki/Darwin_(operating_system)
            switch (kernel_major) {
                case 23: return OS_MACOS_SONOMA;     // macOS 14 Sonoma (Darwin 23.x)
                case 22: return OS_MACOS_VENTURA;    // macOS 13 Ventura (Darwin 22.x)
                case 21: return OS_MACOS_MONTEREY;   // macOS 12 Monterey (Darwin 21.x)
                case 20: return OS_MACOS_BIGSUR;     // macOS 11 Big Sur (Darwin 20.x)
                case 19: return OS_MACOS_CATALINA;   // macOS 10.15 Catalina (Darwin 19.x)
                case 18: return OS_MACOS_MOJAVE;     // macOS 10.14 Mojave (Darwin 18.x)
                case 17: return OS_MACOS_HIGHSIERRA; // macOS 10.13 High Sierra (Darwin 17.x)
                case 16: return OS_MACOS_SIERRA;     // macOS 10.12 Sierra (Darwin 16.x)
                case 15: return OS_OSX_ELCAPITAN;    // OS X 10.11 El Capitan (Darwin 15.x)
                case 14: return OS_OSX_YOSEMITE;     // OS X 10.10 Yosemite (Darwin 14.x)
                case 13: return OS_OSX_MAVERICKS;    // OS X 10.9 Mavericks (Darwin 13.x)
                case 12: return OS_OSX_MOUNTAINLION; // OS X 10.8 Mountain Lion (Darwin 12.x)
                case 11: return OS_OSX_LION;         // Mac OS X 10.7 Lion (Darwin 11.x)
                case 10: return OS_OSX_SNOWLEOPARD;  // Mac OS X 10.6 Snow Leopard (Darwin 10.x)
                case 9:  return OS_OSX_LEOPARD;      // Mac OS X 10.5 Leopard (Darwin 9.x)
                case 8:  return OS_OSX_TIGER;        // Mac OS X 10.4 Tiger (Darwin 8.x)
                case 7:  return OS_OSX_PANTHER;      // Mac OS X 10.3 Panther (Darwin 7.x)
                case 6:  return OS_OSX_JAGUAR;       // Mac OS X 10.2 Jaguar (Darwin 6.x)
                case 5:  return OS_OSX_PUMA;         // Mac OS X 10.1 Puma (Darwin 5.x)
                case 4:  return OS_OSX_CHEETAH;      // Mac OS X 10.0 Cheetah (Darwin 4.x)
                case 1:
                case 2:
                case 3:  return OS_OSX_BETA;         // Mac OS X Public Beta/Server (Darwin 1.x-3.x)
                default:
                    // 检查是否为经典Mac OS (非Darwin内核)
                    // 这部分在现代系统上不会执行，仅为完整性保留
                    if (kernel_major == 0) {
                        // 尝试获取系统版本
                        ret = sysctlbyname("kern.osversion", str, &size, NULL, 0);
                        if (ret == 0) {
                            int os_version = 0;
                            sscanf(str, "%d", &os_version);
                            
                            // 经典Mac OS版本
                            if (os_version >= 9) return OS_MACOS9;
                            else if (os_version >= 8) return OS_MACOS8;
                            else if (os_version >= 7) return OS_MACOS7;
                            else if (os_version >= 6) return OS_MACOS6;
                            else if (os_version >= 5) return OS_MACOS5;
                            else if (os_version >= 4) return OS_MACOS4;
                            else if (os_version >= 3) return OS_MACOS3;
                            else if (os_version >= 2) return OS_MACOS2;
                            else if (os_version >= 1) return OS_MACOS1;
                        }
                    }
                    return OS_MACOS; // 默认macOS
            }
        }
        
        // 如果sysctlbyname失败，尝试使用Gestalt API (仅适用于旧版Mac OS)
        #if defined(MAC_OS_X_VERSION_MIN_REQUIRED) && MAC_OS_X_VERSION_MIN_REQUIRED < MAC_OS_X_VERSION_10_8
        #include <CoreServices/CoreServices.h>
        SInt32 gestaltVersion;
        if (Gestalt(gestaltSystemVersion, &gestaltVersion) == noErr) {
            // Gestalt返回的版本格式为: 0x0ABC，其中A=主版本，B=次版本，C=修订版本
            int major = (gestaltVersion >> 8) & 0xF;
            
            switch (major) {
                case 9: return OS_MACOS9;
                case 8: return OS_MACOS8;
                case 7: return OS_MACOS7;
                case 6: return OS_MACOS6;
                case 5: return OS_MACOS5;
                case 4: return OS_MACOS4;
                case 3: return OS_MACOS3;
                case 2: return OS_MACOS2;
                case 1: return OS_MACOS1;
                default: break;
            }
        }
        #endif
        
        return OS_MACOS;     // 默认macOS
    #elif defined(TARGET_OS_EMBEDDED) && TARGET_OS_EMBEDDED
        // 可能是HomePod的audioOS
        return OS_AUDIOOS;   // audioOS (HomePod)
    #else
        return OS_MACOS;     // 默认macOS
    #endif

#elif defined(__DragonFly__)
        return OS_DRAGONFLY;

#elif defined(__NetBSD__)
        return OS_NETBSD;

#elif defined(__OpenBSD__)
        return OS_OPENBSD;

#elif defined(__FreeBSD__)
        return OS_FREEBSD;

#elif defined(__GNU__) || defined(__gnu_hurd__)
        return OS_HURD;

#elif defined(__CYGWIN__)
        return OS_UNIX; // Cygwin是类Unix环境

#elif defined(__XENIX__)
        return OS_XENIX;

#elif defined(__PLAN9__)
        return OS_PLAN9;

#elif defined(__INFERNO__)
        return OS_INFERNO;

#elif defined(__Fuchsia__)
        return OS_FUCHSIA;

#elif defined(__redox__)
        return OS_REDOX;

#elif defined(__HARMONY_OS__) || defined(HARMONY_OS)
        return OS_HARMONY;

#elif defined(__VXWORKS__)
        return OS_VXWORKS;

#elif defined(__RTEMS__)
        return OS_RTEMS;

#elif defined(__FreeRTOS__)
        return OS_FREERTOS;

#elif defined(__ThreadX__) || defined(TX_INCLUDE_USER_DEFINE_FILE)
        return OS_THREADX;

#elif defined(__NUCLEUS__)
        return OS_NUCLEUS;

#elif defined(__UCOS_II__)
        return OS_UCOSII;

#elif defined(__UCOS_III__)
        return OS_UCOSIII;

#elif defined(__PSOS__)
        return OS_PSOS;

#elif defined(__ECOS__)
        return OS_ECOS;

#elif defined(__NUTTX__)
        return OS_NUTTX;

#elif defined(ZEPHYR_VERSION_CODE)
        return OS_ZEPHYR;

#elif defined(CONTIKI)
        return OS_CONTIKI;

#elif defined(RIOT_VERSION)
        return OS_RIOT;

#elif defined(__XJ380__)
        return OS_XJ380;

#elif defined(__linux__)
        // 检查是否为特定Linux发行版
        #ifdef __ANDROID__
            return OS_ANDROID; // 再次检查Android
        #else
            // 通过读取/etc/os-release文件来识别具体的Linux发行版
            FILE* fp = fopen("/etc/os-release", "r");
            if (fp) {
                char line[256];
                std::string id, name;
                
                while (fgets(line, sizeof(line), fp)) {
                    if (strncmp(line, "ID=", 3) == 0) {
                        id = line + 3;
                        // 移除引号和换行符
                        id.erase(std::remove(id.begin(), id.end(), '"'), id.end());
                        id.erase(std::remove(id.begin(), id.end(), '\n'), id.end());
                    }
                    else if (strncmp(line, "NAME=", 5) == 0) {
                        name = line + 5;
                        // 移除引号和换行符
                        name.erase(std::remove(name.begin(), name.end(), '"'), name.end());
                        name.erase(std::remove(name.begin(), name.end(), '\n'), name.end());
                    }
                }
                fclose(fp);
                
                // 根据ID或NAME识别发行版
                if (!id.empty()) {
                    if (id == "ubuntu" || name.find("Ubuntu") != std::string::npos)
                        return OS_UBUNTU;
                    else if (id == "debian" || name.find("Debian") != std::string::npos)
                        return OS_DEBIAN;
                    else if (id == "fedora" || name.find("Fedora") != std::string::npos)
                        return OS_FEDORA;
                    else if (id == "centos" || name.find("CentOS") != std::string::npos)
                        return OS_CENTOS;
                    else if (id == "rhel" || name.find("Red Hat") != std::string::npos)
                        return OS_REDHAT;
                    else if (id == "opensuse" || id == "suse" || name.find("SUSE") != std::string::npos)
                        return OS_SUSE;
                    else if (id == "arch" || name.find("Arch") != std::string::npos)
                        return OS_ARCH;
                    else if (id == "gentoo" || name.find("Gentoo") != std::string::npos)
                        return OS_GENTOO;
                    else if (id == "slackware" || name.find("Slackware") != std::string::npos)
                        return OS_SLACKWARE;
                    else if (id == "kali" || name.find("Kali") != std::string::npos)
                        return OS_KALI;
                    else if (id == "linuxmint" || name.find("Linux Mint") != std::string::npos)
                        return OS_MINT;
                    else if (id == "manjaro" || name.find("Manjaro") != std::string::npos)
                        return OS_MANJARO;
                    else if (id == "alpine" || name.find("Alpine") != std::string::npos)
                        return OS_ALPINE;
                    else if (id == "raspbian" || name.find("Raspbian") != std::string::npos)
                        return OS_RASPBIAN;
                    else if (id == "deepin" || name.find("Deepin") != std::string::npos)
                        return OS_DEEPIN;
                    else if (id == "elementary" || name.find("Elementary") != std::string::npos)
                        return OS_ELEMENTARY;
                    else if (id == "zorin" || name.find("Zorin") != std::string::npos)
                        return OS_ZORIN;
                    else if (id == "pop" || name.find("Pop!_OS") != std::string::npos)
                        return OS_POPOS;
                    else if (id == "chromeos" || name.find("Chrome OS") != std::string::npos)
                        return OS_CHROMEOS;
                }
            }
            
            // 尝试其他方法检测发行版
            // 检查是否为Kali Linux
            if (access("/etc/kali-release", F_OK) != -1)
                return OS_KALI;
            // 检查是否为Ubuntu
            else if (access("/etc/lsb-release", F_OK) != -1) {
                FILE* fp = fopen("/etc/lsb-release", "r");
                if (fp) {
                    char line[256];
                    while (fgets(line, sizeof(line), fp)) {
                        if (strstr(line, "DISTRIB_ID=Ubuntu"))
                            return OS_UBUNTU;
                    }
                    fclose(fp);
                }
            }
            // 检查是否为Debian
            else if (access("/etc/debian_version", F_OK) != -1)
                return OS_DEBIAN;
            // 检查是否为Fedora
            else if (access("/etc/fedora-release", F_OK) != -1)
                return OS_FEDORA;
            // 检查是否为CentOS
            else if (access("/etc/centos-release", F_OK) != -1)
                return OS_CENTOS;
            // 检查是否为Red Hat
            else if (access("/etc/redhat-release", F_OK) != -1)
                return OS_REDHAT;
            
            // 默认返回通用Linux
            return OS_LINUX;
        #endif

#elif defined(__unix__) || defined(__unix)
        // 通用Unix检测
        #if defined(__FreeBSD__)
            return OS_FREEBSD;
        #elif defined(__NetBSD__)
            return OS_NETBSD;
        #elif defined(__OpenBSD__)
            return OS_OPENBSD;
        #elif defined(__DragonFly__)
            return OS_DRAGONFLY;
        #else
            return OS_UNIX;
        #endif

#elif defined(__MSDOS__) || defined(_MSDOS) || defined(__DOS__)
        return OS_DOS;

#elif defined(__BEOS__)
        return OS_BEOS;

#elif defined(__OS2__) || defined(_OS2) || defined(OS2)
        return OS_OS2;

#elif defined(__NeXT__)
        return OS_NEXTSTEP;

#else
    // 尝试通过uname等系统调用进一步识别
    #if defined(_POSIX_VERSION)
        return OS_UNIX; // POSIX兼容系统
    #else
        return OS_UNKNOWN;
    #endif
#endif
    } // systemCheck

    /**
     * 获取操作系统名称
     * Get operating system name
     * 
     * 根据操作系统代码返回对应的操作系统名称。
     * Returns the corresponding operating system name based on the OS code.
     * 
     * @param osCode 操作系统代码（由systemCheck函数返回） | Operating system code (returned by systemCheck function)
     * @return 操作系统名称字符串 | Operating system name string
     */
    inline const char* getOSName(int osCode) {
        switch(osCode) {
            // 未知操作系统 | Unknown operating system
            case OS_UNKNOWN: return "Unknown OS";
            
            // Windows系列 | Windows family
            case OS_WINDOWS: return "Windows";
            case OS_WINDOWSNT3: return "Windows NT 3.x";
            case OS_WINDOWSNT4: return "Windows NT 4.0";
            case OS_WINDOWSNT5: return "Windows 2000/XP/2003";
            case OS_WINDOWSNT6: return "Windows Vista/7/8/8.1";
            case OS_WINDOWSNT10: return "Windows 10";
            case OS_WINDOWSNT11: return "Windows 11";
            case OS_WIN95: return "Windows 95";
            case OS_WIN98: return "Windows 98";
            case OS_WINME: return "Windows ME";
            case OS_WINCE: return "Windows CE";
            
            // Linux发行版 | Linux distributions
            case OS_LINUX: return "Linux";
            case OS_UBUNTU: return "Ubuntu Linux";
            case OS_DEBIAN: return "Debian Linux";
            case OS_FEDORA: return "Fedora Linux";
            case OS_CENTOS: return "CentOS Linux";
            case OS_REDHAT: return "Red Hat Enterprise Linux";
            case OS_SUSE: return "SUSE/openSUSE Linux";
            case OS_ARCH: return "Arch Linux";
            case OS_GENTOO: return "Gentoo Linux";
            case OS_SLACKWARE: return "Slackware Linux";
            case OS_KALI: return "Kali Linux";
            case OS_MINT: return "Linux Mint";
            case OS_MANJARO: return "Manjaro Linux";
            case OS_ALPINE: return "Alpine Linux";
            case OS_RASPBIAN: return "Raspbian";
            case OS_DEEPIN: return "Deepin Linux";
            case OS_ELEMENTARY: return "Elementary OS";
            case OS_ZORIN: return "Zorin OS";
            case OS_POPOS: return "Pop!_OS";
            case OS_CHROMEOS: return "Chrome OS/Chromium OS";
            case OS_ANDROID: return "Android";
            
            // macOS和Mac OS X版本 | macOS and Mac OS X versions
            case OS_MACOS: return "macOS";
            case OS_MACOS_SONOMA: return "macOS 14 Sonoma";
            case OS_MACOS_VENTURA: return "macOS 13 Ventura";
            case OS_MACOS_MONTEREY: return "macOS 12 Monterey";
            case OS_MACOS_BIGSUR: return "macOS 11 Big Sur";
            case OS_MACOS_CATALINA: return "macOS 10.15 Catalina";
            case OS_MACOS_MOJAVE: return "macOS 10.14 Mojave";
            case OS_MACOS_HIGHSIERRA: return "macOS 10.13 High Sierra";
            case OS_MACOS_SIERRA: return "macOS 10.12 Sierra";
            case OS_OSX_ELCAPITAN: return "OS X 10.11 El Capitan";
            case OS_OSX_YOSEMITE: return "OS X 10.10 Yosemite";
            case OS_OSX_MAVERICKS: return "OS X 10.9 Mavericks";
            case OS_OSX_MOUNTAINLION: return "OS X 10.8 Mountain Lion";
            case OS_OSX_LION: return "Mac OS X 10.7 Lion";
            case OS_OSX_SNOWLEOPARD: return "Mac OS X 10.6 Snow Leopard";
            case OS_OSX_LEOPARD: return "Mac OS X 10.5 Leopard";
            case OS_OSX_TIGER: return "Mac OS X 10.4 Tiger";
            case OS_OSX_PANTHER: return "Mac OS X 10.3 Panther";
            case OS_OSX_JAGUAR: return "Mac OS X 10.2 Jaguar";
            case OS_OSX_PUMA: return "Mac OS X 10.1 Puma";
            case OS_OSX_CHEETAH: return "Mac OS X 10.0 Cheetah";
            case OS_OSX_BETA: return "Mac OS X Public Beta";
            
            // 经典Macintosh系统 | Classic Macintosh systems
            case OS_MACOS9: return "Mac OS 9";
            case OS_MACOS8: return "Mac OS 8";
            case OS_MACOS7: return "System 7";
            case OS_MACOS6: return "System 6";
            case OS_MACOS5: return "System 5";
            case OS_MACOS4: return "System 4";
            case OS_MACOS3: return "System 3";
            case OS_MACOS2: return "System 2";
            case OS_MACOS1: return "System 1";
            
            // 其他Apple操作系统 | Other Apple operating systems
            case OS_IOS: return "iOS";
            case OS_IPADOS: return "iPadOS";
            case OS_WATCHOS: return "watchOS";
            case OS_TVOS: return "tvOS";
            case OS_VISIONOS: return "visionOS";
            case OS_BRIDGEOS: return "bridgeOS";
            case OS_AUDIOOS: return "audioOS";
            
            // BSD系列 | BSD family
            case OS_BSD: return "BSD";
            case OS_DRAGONFLY: return "DragonFly BSD";
            case OS_NETBSD: return "NetBSD";
            case OS_OPENBSD: return "OpenBSD";
            case OS_FREEBSD: return "FreeBSD";
            
            // 其他操作系统 | Other operating systems
            case OS_UNIX: return "UNIX";
            case OS_HURD: return "GNU Hurd";
            case OS_XENIX: return "Xenix";
            case OS_DOS: return "DOS";
            case OS_PLAN9: return "Plan 9";
            case OS_INFERNO: return "Inferno";
            case OS_BEOS: return "BeOS";
            case OS_HAIKU: return "Haiku";
            case OS_SYLLABLE: return "Syllable";
            case OS_MENUETOS: return "MenuetOS";
            case OS_REACTOS: return "ReactOS";
            case OS_KOLIBRIOS: return "KolibriOS";
            case OS_AIX: return "AIX";
            case OS_SOLARIS: return "Solaris";
            case OS_MINIX: return "MINIX";
            case OS_QNX: return "QNX";
            case OS_VMS: return "VMS";
            case OS_ZOS: return "z/OS";
            case OS_OS400: return "OS/400";
            case OS_TPF: return "TPF";
            case OS_AMIGAOS: return "AmigaOS";
            case OS_MORPHOS: return "MorphOS";
            case OS_FREEMINT: return "FreeMiNT";
            case OS_HPUX: return "HP-UX";
            case OS_IRIX: return "IRIX";
            case OS_SCO: return "SCO";
            case OS_OPENVMS: return "OpenVMS";
            case OS_RISCOS: return "RISC OS";
            case OS_OS2: return "OS/2";
            case OS_NEXTSTEP: return "NeXTSTEP";
            
            // 嵌入式/实时操作系统 | Embedded/Real-time operating systems
            case OS_NUTTX: return "NuttX";
            case OS_ZEPHYR: return "Zephyr";
            case OS_CONTIKI: return "Contiki";
            case OS_RIOT: return "RIOT";
            case OS_VXWORKS: return "VxWorks";
            case OS_RTEMS: return "RTEMS";
            case OS_FREERTOS: return "FreeRTOS";
            case OS_THREADX: return "ThreadX";
            case OS_INTEGRITY: return "INTEGRITY";
            case OS_NUCLEUS: return "Nucleus RTOS";
            case OS_UCOSII: return "μC/OS-II";
            case OS_UCOSIII: return "μC/OS-III";
            case OS_PSOS: return "pSOS";
            case OS_ECOS: return "eCos";
            
            // 新兴操作系统 | Emerging operating systems
            case OS_FUCHSIA: return "Google Fuchsia";
            case OS_REDOX: return "Redox OS";
            case OS_HARMONY: return "Harmony OS";
            case OS_XJ380: return "XJ380";
        
            // 默认情况 | Default case
            default: return "Unknown OS";
        }
    }
} // namespace tc

#endif // TC_HPP