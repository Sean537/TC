/*
 * tc_terminal.hpp - TC库终端控制模块
 * TC Terminal Control Module
 * 
 * 这个文件包含了TC库中所有与终端控制相关的功能，包括：
 * - Printer类，提供链式终端控制接口
 * - 终端清屏、光标移动、尺寸获取
 * - 跨平台终端操作支持
 * - terminal命名空间的便利函数
 * 
 * This file contains all terminal control related functionality in the TC library, including:
 * - Printer class providing chainable terminal control interface
 * - Terminal clearing, cursor movement, size retrieval
 * - Cross-platform terminal operation support
 * - Convenient functions in terminal namespace
 * 
 * 版本 Version: 1.1.2
 * 作者 Author: 537 Studio
 * 许可 License: MIT
 */

#ifndef TC_TERMINAL_HPP
#define TC_TERMINAL_HPP

// 标准库包含 | Standard library includes
#include <iostream>  // 输入输出流 | Input/output streams
#include <utility>   // 实用工具，如std::pair | Utility tools like std::pair
#include <type_traits>  // 类型特征 | Type traits
#include <cstring>      // C字符串操作 | C string operations
#include <string>       // C++字符串 | C++ string
#include "tc_print.hpp"

// 平台特定包含 | Platform-specific includes
#ifdef _WIN32
    #include <windows.h>     // Windows API
    #include "tc_colors.hpp" // TC颜色模块 | TC color module
#else
    #include <sys/ioctl.h>   // 系统输入输出控制 | System I/O control
    #include <unistd.h>      // POSIX API
#endif

namespace tc {

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
     * flush函数 - 刷新终端输出缓冲区
     * flush function - Flushes the terminal output buffer
     * 
     * @return Printer对象的引用，支持链式调用 | Reference to Printer object for chaining
     */
    Printer& flush() {
        std::cout.flush();
        return *this;
    }
    /**
     * 清屏并将光标移动到左上角
     * Clear screen and move cursor to top-left corner
     * 
     * @return 对象自身引用，支持链式调用 | Self reference for chaining
     */
    Printer& clear() {
#ifdef _WIN32
        // Windows：使用 Win32 API 清屏
        Win32Console::getInstance().clearScreen();
        return *this;
#else
        std::cout << "\033[2J\033[H"; // ANSI清屏和光标定位序列 | ANSI clear screen and cursor positioning sequence
        return *this;
#endif
    }
    
    /**
     * 将光标移动到指定坐标
     * Move cursor to specified coordinates
     * 
     * @param x 列坐标（从1开始） | Column coordinate (1-based)
     * @param y 行坐标（从1开始） | Row coordinate (1-based)
     * @return 对象自身引用，支持链式调用 | Self reference for chaining
     */
    Printer& moveCursor(int x, int y) {
#ifdef _WIN32
        // Windows：使用 Win32 API，注意 0 基坐标
        Win32Console::getInstance().moveCursor(x - 1, y - 1);
        return *this;
#else
        std::cout << "\033[" << y << ";" << x << "H"; // ANSI光标定位序列 | ANSI cursor positioning sequence
        return *this;
#endif
    }
    
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
        bool needsFlush = false;
        auto check = [&needsFlush](const auto& arg) {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, const char*> || std::is_same_v<T, char*>) {
                needsFlush |= (std::strchr(arg, '\r') != nullptr);
            } else if constexpr (std::is_same_v<T, std::string>) {
                needsFlush |= (arg.find('\r') != std::string::npos);
            } else if constexpr (std::is_same_v<T, char>) {
                needsFlush |= (arg == '\r');
            }
        };
        (check(std::forward<Args>(args)), ...);
        
        // 使用打印 helper 以保持与 tc_print 的行为一致（处理平台和特殊类型）
        (tc::detail::print_one(std::forward<Args>(args)), ...);
        if (needsFlush) {
            flush();
        }
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
        (tc::detail::print_one(std::forward<Args>(args)), ...);
        std::cout << std::endl;  // endl 自带 flush
        return *this; 
    }
    
    /**
     * 隐藏光标
     * Hide cursor
     * 
     * @return 对象自身引用，支持链式调用 | Self reference for chaining
     */
    Printer& hideCursor() {
#ifdef _WIN32
        // Windows：隐藏光标
        HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO info;
        if (GetConsoleCursorInfo(h, &info)) {
            info.bVisible = FALSE;
            SetConsoleCursorInfo(h, &info);
        }
        flush();  // 立即刷新以确保光标状态更新
        return *this;
#else
        std::cout << "\033[?25l"; // ANSI隐藏光标序列 | ANSI hide cursor sequence
        flush();  // 立即刷新以确保光标状态更新
        return *this;
#endif
    }
    
    /**
     * 显示光标
     * Show cursor
     * 
     * @return 对象自身引用，支持链式调用 | Self reference for chaining
     */
    Printer& showCursor() {
#ifdef _WIN32
        // Windows：显示光标
        HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO info;
        if (GetConsoleCursorInfo(h, &info)) {
            info.bVisible = TRUE;
            SetConsoleCursorInfo(h, &info);
        }
        flush();  // 立即刷新以确保光标状态更新
        return *this;
#else
        std::cout << "\033[?25h"; // ANSI显示光标序列 | ANSI show cursor sequence
        flush();  // 立即刷新以确保光标状态更新
        return *this;
#endif
    }
    
    /**
     * 光标移动方向枚举
     * Cursor movement direction enum
     */
    enum class Direction { 
        Up,    // 向上 | Upward
        Down,  // 向下 | Downward
        Left,  // 向左 | Leftward
        Right  // 向右 | Rightward
    };
    
    /**
     * 按指定方向移动光标
     * Move cursor in specified direction
     * 
     * @param dir 移动方向 | Movement direction
     * @param n 移动步数 | Number of steps to move
     * @return 对象自身引用，支持链式调用 | Self reference for chaining
     */
    Printer& moveCursor(Direction dir, int n) {
#ifdef _WIN32
        // Windows：相对移动光标
        HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        if (GetConsoleScreenBufferInfo(h, &csbi)) {
            SHORT x = csbi.dwCursorPosition.X;
            SHORT y = csbi.dwCursorPosition.Y;
            switch(dir) {
                case Direction::Up:    y = (y - n) < 0 ? 0 : y - n; break;
                case Direction::Down:  y = y + n; break;
                case Direction::Right: x = x + n; break;
                case Direction::Left:  x = (x - n) < 0 ? 0 : x - n; break;
            }
            COORD coord = {x, y};
            SetConsoleCursorPosition(h, coord);
        }
        return *this;
#else
        switch(dir) {
            case Direction::Up: std::cout << "\033[" << n << "A"; break;     // 向上移动 | Move up
            case Direction::Down: std::cout << "\033[" << n << "B"; break;   // 向下移动 | Move down
            case Direction::Right: std::cout << "\033[" << n << "C"; break;  // 向右移动 | Move right
            case Direction::Left: std::cout << "\033[" << n << "D"; break;   // 向左移动 | Move left
        }
        return *this;
#endif
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

/**
 * 终端控制函数命名空间
 * Terminal control functions namespace
 * 
 * 这个命名空间提供了一组用于控制终端的函数，如清屏、移动光标、获取终端尺寸和刷新输出缓冲区。
 * 这些函数在不同平台上使用相应的实现，提供统一的接口。
 * 
 * This namespace provides a set of functions for terminal control, such as clearing the screen,
 * moving the cursor, getting terminal size, and flushing output buffer. These functions use
 * the appropriate implementation on different platforms, providing a unified interface.
 */
namespace terminal {
    /**
     * 刷新终端输出缓冲区
     * Flush terminal output buffer
     * 
     * 确保所有待输出的内容立即显示在终端上。在动画效果、实时更新或需要立即显示的场景下特别有用。
     * Ensures all pending output is immediately displayed on the terminal.
     * Particularly useful for animations, real-time updates, or when immediate display is required.
     */
    inline void flush() {
        std::cout.flush();
    }
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

} // namespace tc

#endif // TC_TERMINAL_HPP