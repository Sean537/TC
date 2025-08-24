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
 * 版本 Version: 1.1.1 Beta
 * 作者 Author: 537 Studio
 * 许可 License: MIT
 */

#ifndef TC_TERMINAL_HPP
#define TC_TERMINAL_HPP

// 标准库包含 | Standard library includes
#include <iostream>  // 输入输出流 | Input/output streams
#include <utility>   // 实用工具，如std::pair | Utility tools like std::pair

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
     * 清屏并将光标移动到左上角
     * Clear screen and move cursor to top-left corner
     * 
     * @return 对象自身引用，支持链式调用 | Self reference for chaining
     */
    Printer& clear() { 
        std::cout << "\033[2J\033[H"; // ANSI清屏和光标定位序列 | ANSI clear screen and cursor positioning sequence
        return *this; 
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
        std::cout << "\033[" << y << ";" << x << "H"; // ANSI光标定位序列 | ANSI cursor positioning sequence
        return *this; 
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
    Printer& hideCursor() { 
        std::cout << "\033[?25l"; // ANSI隐藏光标序列 | ANSI hide cursor sequence
        return *this; 
    }
    
    /**
     * 显示光标
     * Show cursor
     * 
     * @return 对象自身引用，支持链式调用 | Self reference for chaining
     */
    Printer& showCursor() { 
        std::cout << "\033[?25h"; // ANSI显示光标序列 | ANSI show cursor sequence
        return *this; 
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

} // namespace tc

#endif // TC_TERMINAL_HPP