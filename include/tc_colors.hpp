/*
 * tc_colors.hpp - TC库颜色和样式控制模块
 * TC Colors and Styles Control Module
 * 
 * 这个文件包含了TC库中所有与颜色和字体样式相关的功能，包括：
 * - ANSI颜色和样式宏定义
 * - 跨平台颜色控制类
 * - Windows控制台API封装
 * - RGB颜色支持
 * - 便利的颜色函数
 * 
 * This file contains all color and font style related functionality in the TC library, including:
 * - ANSI color and style macro definitions
 * - Cross-platform color control classes
 * - Windows Console API wrapper
 * - RGB color support
 * - Convenient color functions
 * 
 * 版本 Version: 1.1.2 Beta
 * 作者 Author: 537 Studio
 * 许可 License: MIT
 */

#ifndef TC_COLORS_HPP
#define TC_COLORS_HPP

// 标准库包含 | Standard library includes
#include <iostream>    // 输入输出流 | Input/output streams
#include <sstream>     // 字符串流 | String streams
#include <stack>       // 栈容器 | Stack container

// 平台特定包含 | Platform-specific includes
#ifdef _WIN32
    #include <windows.h>  // Windows API
#endif

// ===== 颜色宏定义（全局作用域） | Color macros (global scope) =====
#if defined(_WIN32) && defined(TC_ENABLE_WIN32_CONSOLE_API)
// 启用Win32 Console API时：使用包装器对象
#define TCOLOR_BLACK   tc::ColorWrapper(tc::ColorController::Color::BLACK)
#define TCOLOR_RED     tc::ColorWrapper(tc::ColorController::Color::RED)
#define TCOLOR_GREEN   tc::ColorWrapper(tc::ColorController::Color::GREEN)
#define TCOLOR_YELLOW  tc::ColorWrapper(tc::ColorController::Color::YELLOW)
#define TCOLOR_BLUE    tc::ColorWrapper(tc::ColorController::Color::BLUE)
#define TCOLOR_MAGENTA tc::ColorWrapper(tc::ColorController::Color::MAGENTA)
#define TCOLOR_CYAN    tc::ColorWrapper(tc::ColorController::Color::CYAN)
#define TCOLOR_WHITE   tc::ColorWrapper(tc::ColorController::Color::WHITE)
#define TCOLOR_DEFAULT tc::ColorWrapper(tc::ColorController::Color::RESET)
#define TCOLOR_RESET   tc::ColorWrapper(tc::ColorController::Color::RESET)

#define BCOLOR_BLACK   tc::ColorWrapper(tc::ColorController::Color::BLACK, true)
#define BCOLOR_RED     tc::ColorWrapper(tc::ColorController::Color::RED, true)
#define BCOLOR_GREEN   tc::ColorWrapper(tc::ColorController::Color::GREEN, true)
#define BCOLOR_YELLOW  tc::ColorWrapper(tc::ColorController::Color::YELLOW, true)
#define BCOLOR_BLUE    tc::ColorWrapper(tc::ColorController::Color::BLUE, true)
#define BCOLOR_MAGENTA tc::ColorWrapper(tc::ColorController::Color::MAGENTA, true)
#define BCOLOR_CYAN    tc::ColorWrapper(tc::ColorController::Color::CYAN, true)
#define BCOLOR_WHITE   tc::ColorWrapper(tc::ColorController::Color::WHITE, true)
#define BCOLOR_DEFAULT tc::ColorWrapper(tc::ColorController::Color::RESET, true)
#else
// 默认使用ANSI转义序列
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

#define BCOLOR_BLACK   "\033[40m"  // 黑色背景 | Black background
#define BCOLOR_RED     "\033[41m"  // 红色背景 | Red background
#define BCOLOR_GREEN   "\033[42m"  // 绿色背景 | Green background
#define BCOLOR_YELLOW  "\033[43m"  // 黄色背景 | Yellow background
#define BCOLOR_BLUE    "\033[44m"  // 蓝色背景 | Blue background
#define BCOLOR_MAGENTA "\033[45m"  // 洋红色背景 | Magenta background
#define BCOLOR_CYAN    "\033[46m"  // 青色背景 | Cyan background
#define BCOLOR_WHITE   "\033[47m"  // 白色背景 | White background
#define BCOLOR_DEFAULT "\033[49m"  // 默认背景色 | Default background color
#endif

// ===== 字体样式宏（全局作用域） | Font style macros (global scope) =====
#if defined(_WIN32) && defined(TC_ENABLE_WIN32_CONSOLE_API)
// 启用Win32 Console API时：使用包装器对象
#define TFONT_BOLD        tc::FontStyleWrapper(tc::FontStyleWrapper::BOLD)
#define TFONT_FAINT       tc::FontStyleWrapper(tc::FontStyleWrapper::FAINT)
#define TFONT_ITALIC      tc::FontStyleWrapper(tc::FontStyleWrapper::ITALIC)
#define TFONT_UNDERLINE   tc::FontStyleWrapper(tc::FontStyleWrapper::UNDERLINE)
#define TFONT_BLINK_SLOW  tc::FontStyleWrapper(tc::FontStyleWrapper::BLINK_SLOW)
#define TFONT_BLINK_FAST  tc::FontStyleWrapper(tc::FontStyleWrapper::BLINK_FAST)
#define TFONT_REVERSE     tc::FontStyleWrapper(tc::FontStyleWrapper::REVERSE)
#define TFONT_CONCEAL     tc::FontStyleWrapper(tc::FontStyleWrapper::CONCEAL)
#define TFONT_CROSSED     tc::FontStyleWrapper(tc::FontStyleWrapper::CROSSED)
#define TFONT_DEFAULT     tc::FontStyleWrapper(tc::FontStyleWrapper::DEFAULT)
#define TFONT_FRAKTUR     tc::FontStyleWrapper(tc::FontStyleWrapper::FRAKTUR)
#define TFONT_DOUBLE_UNDERLINE tc::FontStyleWrapper(tc::FontStyleWrapper::DOUBLE_UNDERLINE)
#define TFONT_NORMAL      tc::FontStyleWrapper(tc::FontStyleWrapper::NORMAL)
#define TFONT_NOT_ITALIC  tc::FontStyleWrapper(tc::FontStyleWrapper::NOT_ITALIC)
#define TFONT_NO_UNDERLINE tc::FontStyleWrapper(tc::FontStyleWrapper::NO_UNDERLINE)
#define TFONT_NO_BLINK    tc::FontStyleWrapper(tc::FontStyleWrapper::NO_BLINK)
#define TFONT_NO_REVERSE  tc::FontStyleWrapper(tc::FontStyleWrapper::NO_REVERSE)
#define TFONT_REVEAL      tc::FontStyleWrapper(tc::FontStyleWrapper::REVEAL)
#define TFONT_NOT_CROSSED tc::FontStyleWrapper(tc::FontStyleWrapper::NOT_CROSSED)
#define TFONT_THICK       TFONT_BOLD
#define TFONT_RESET       tc::FontStyleWrapper(tc::FontStyleWrapper::RESET)
#else
// 默认使用ANSI转义序列
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
#endif

namespace tc {

#ifdef _WIN32
/**
 * Windows颜色常量命名空间
 * Windows color constants namespace
 * 
 * 定义了Windows控制台API使用的颜色常量，这些常量对应于
 * Windows控制台的16色调色板。每个颜色由位标志组合而成。
 * 
 * Defines color constants used by the Windows Console API, these constants
 * correspond to the 16-color palette of the Windows console. Each color is
 * formed by combining bit flags.
 */
namespace win32_colors {
    constexpr WORD BLACK = 0;
    constexpr WORD DARK_BLUE = FOREGROUND_BLUE;
    constexpr WORD DARK_GREEN = FOREGROUND_GREEN;
    constexpr WORD DARK_CYAN = FOREGROUND_GREEN | FOREGROUND_BLUE;
    constexpr WORD DARK_RED = FOREGROUND_RED;
    constexpr WORD DARK_MAGENTA = FOREGROUND_RED | FOREGROUND_BLUE;
    constexpr WORD DARK_YELLOW = FOREGROUND_RED | FOREGROUND_GREEN;
    constexpr WORD GRAY = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
    constexpr WORD DARK_GRAY = FOREGROUND_INTENSITY;
    constexpr WORD BLUE = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
    constexpr WORD GREEN = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
    constexpr WORD CYAN = FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
    constexpr WORD RED = FOREGROUND_RED | FOREGROUND_INTENSITY;
    constexpr WORD MAGENTA = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
    constexpr WORD YELLOW = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
    constexpr WORD WHITE = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
}

/**
 * Windows控制台管理类
 * Windows Console Manager Class
 * 
 * 这个类封装了Windows控制台API的操作，提供颜色设置、光标控制、
 * 清屏等功能。采用单例模式设计，确保全局只有一个控制台管理实例。
 * 
 * This class encapsulates Windows Console API operations, providing functionality
 * for color setting, cursor control, screen clearing, etc. It uses the singleton
 * design pattern to ensure only one console manager instance exists globally.
 */
class Win32Console {
private:
    HANDLE hConsole_;                        // 控制台句柄 | Console handle
    CONSOLE_SCREEN_BUFFER_INFO originalInfo_; // 原始缓冲区信息 | Original buffer info
    std::stack<WORD> colorStack_;            // 颜色栈，用于保存和恢复颜色 | Color stack for saving/restoring colors
    bool initialized_ = false;               // 初始化标志 | Initialization flag

    /**
     * 私有构造函数，初始化控制台和UTF-8支持
     * Private constructor, initializes console and UTF-8 support
     * 
     * 单例模式的一部分，防止外部直接创建实例。
     * 设置UTF-8编码并尝试启用ANSI转义序列支持。
     * 
     * Part of singleton pattern, prevents direct instance creation from outside.
     * Sets UTF-8 encoding and tries to enable ANSI escape sequence support.
     */
    Win32Console() {
        // 获取标准输出句柄 | Get standard output handle
        hConsole_ = GetStdHandle(STD_OUTPUT_HANDLE);
        
        if (hConsole_ != INVALID_HANDLE_VALUE) {
            // 获取原始控制台信息 | Get original console information
            GetConsoleScreenBufferInfo(hConsole_, &originalInfo_);
            initialized_ = true;
            
            // 设置UTF-8编码支持 | Set UTF-8 encoding support
            SetConsoleOutputCP(CP_UTF8);  // 输出编码 | Output encoding
            SetConsoleCP(CP_UTF8);        // 输入编码 | Input encoding
            
            // 根据宏切换 ANSI 虚拟终端处理 | Toggle ANSI virtual terminal processing by macro
            DWORD dwMode = 0;
            if (GetConsoleMode(hConsole_, &dwMode)) {
#if defined(TC_ENABLE_WIN32_CONSOLE_API)
                // 禁用 ANSI，强制使用 Win32 API
                SetConsoleMode(hConsole_, dwMode & ~ENABLE_VIRTUAL_TERMINAL_PROCESSING);
#else
                // 默认启用 ANSI 虚拟终端处理（Win10 1809+ 支持）
                SetConsoleMode(hConsole_, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
#endif
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
    constexpr const char* ESC = "\033[";
    constexpr const char* RESET = "\033[0m";
    
    constexpr const char* BLACK = "\033[30m";
    constexpr const char* RED = "\033[31m";
    constexpr const char* GREEN = "\033[32m";
    constexpr const char* YELLOW = "\033[33m";
    constexpr const char* BLUE = "\033[34m";
    constexpr const char* MAGENTA = "\033[35m";
    constexpr const char* CYAN = "\033[36m";
    constexpr const char* WHITE = "\033[37m";
    
    constexpr const char* BRIGHT_BLACK = "\033[90m";
    constexpr const char* BRIGHT_RED = "\033[91m";
    constexpr const char* BRIGHT_GREEN = "\033[92m";
    constexpr const char* BRIGHT_YELLOW = "\033[93m";
    constexpr const char* BRIGHT_BLUE = "\033[94m";
    constexpr const char* BRIGHT_MAGENTA = "\033[95m";
    constexpr const char* BRIGHT_CYAN = "\033[96m";
    constexpr const char* BRIGHT_WHITE = "\033[97m";
    
    constexpr const char* BOLD = "\033[1m";
    constexpr const char* DIM = "\033[2m";
    constexpr const char* ITALIC = "\033[3m";
    constexpr const char* UNDERLINE = "\033[4m";
    constexpr const char* BLINK = "\033[5m";
    constexpr const char* REVERSE = "\033[7m";
    constexpr const char* STRIKETHROUGH = "\033[9m";
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
        auto& console = Win32Console::getInstance();
        WORD winColor;
        
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
                console.resetColor();
                return;
        }
        console.setColor(winColor);
#else
        const char* ansiColor;
        
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
                ansiColor = ansi::RESET;
                break;
        }
        std::cout << ansiColor;
#endif
    }

    /**
     * 设置背景颜色
     * Set background color
     * 
     * @param color 要设置的背景色 | Background color to set
     */
    static void setBackground(Color color) {
#ifdef _WIN32
        auto& console = Win32Console::getInstance();
        WORD bgColor = 0;
        
        switch (color) {
            case Color::BLACK: bgColor = 0; break;  // Windows中没有BACKGROUND_BLACK，使用0
            case Color::RED: bgColor = BACKGROUND_RED; break;
            case Color::GREEN: bgColor = BACKGROUND_GREEN; break;
            case Color::YELLOW: bgColor = BACKGROUND_RED | BACKGROUND_GREEN; break;
            case Color::BLUE: bgColor = BACKGROUND_BLUE; break;
            case Color::MAGENTA: bgColor = BACKGROUND_RED | BACKGROUND_BLUE; break;
            case Color::CYAN: bgColor = BACKGROUND_GREEN | BACKGROUND_BLUE; break;
            case Color::WHITE: bgColor = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE; break;
            case Color::BRIGHT_BLACK: bgColor = BACKGROUND_INTENSITY; break;
            case Color::BRIGHT_RED: bgColor = BACKGROUND_RED | BACKGROUND_INTENSITY; break;
            case Color::BRIGHT_GREEN: bgColor = BACKGROUND_GREEN | BACKGROUND_INTENSITY; break;
            case Color::BRIGHT_YELLOW: bgColor = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY; break;
            case Color::BRIGHT_BLUE: bgColor = BACKGROUND_BLUE | BACKGROUND_INTENSITY; break;
            case Color::BRIGHT_MAGENTA: bgColor = BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_INTENSITY; break;
            case Color::BRIGHT_CYAN: bgColor = BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY; break;
            case Color::BRIGHT_WHITE: bgColor = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY; break;
            case Color::RESET:
            default:
                console.resetColor();
                return;
        }
        
        // 获取当前前景色并组合背景色
        WORD currentColor = console.getCurrentColor();
        WORD newColor = (currentColor & 0x0F) | bgColor;  // 保留前景色，设置背景色
        console.setColor(newColor);
#else
        const char* ansiBgColor;
        
        switch (color) {
            case Color::BLACK: ansiBgColor = "\033[40m"; break;
            case Color::RED: ansiBgColor = "\033[41m"; break;
            case Color::GREEN: ansiBgColor = "\033[42m"; break;
            case Color::YELLOW: ansiBgColor = "\033[43m"; break;
            case Color::BLUE: ansiBgColor = "\033[44m"; break;
            case Color::MAGENTA: ansiBgColor = "\033[45m"; break;
            case Color::CYAN: ansiBgColor = "\033[46m"; break;
            case Color::WHITE: ansiBgColor = "\033[47m"; break;
            case Color::BRIGHT_BLACK: ansiBgColor = "\033[100m"; break;
            case Color::BRIGHT_RED: ansiBgColor = "\033[101m"; break;
            case Color::BRIGHT_GREEN: ansiBgColor = "\033[102m"; break;
            case Color::BRIGHT_YELLOW: ansiBgColor = "\033[103m"; break;
            case Color::BRIGHT_BLUE: ansiBgColor = "\033[104m"; break;
            case Color::BRIGHT_MAGENTA: ansiBgColor = "\033[105m"; break;
            case Color::BRIGHT_CYAN: ansiBgColor = "\033[106m"; break;
            case Color::BRIGHT_WHITE: ansiBgColor = "\033[107m"; break;
            case Color::RESET:
            default:
                ansiBgColor = "\033[49m";
                break;
        }
        std::cout << ansiBgColor;
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
        auto& console = Win32Console::getInstance();
        WORD winColor = console.rgbToWin32Color(r, g, b);
        console.setColor(winColor);
#else
        std::cout << "\033[38;2;" << r << ";" << g << ";" << b << "m";
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
        auto& console = Win32Console::getInstance();
        WORD currentColor = console.getCurrentColor();
        if (enable) {
            console.setColor(currentColor | FOREGROUND_INTENSITY);
        } else {
            console.setColor(currentColor & ~FOREGROUND_INTENSITY);
        }
#else
        if (enable) {
            std::cout << ansi::BOLD;
        } else {
            std::cout << ansi::RESET;
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
    bool isBackground_;            // 是否为背景色 | Whether this is a background color
    
public:
    /**
     * 构造函数
     * Constructor
     * 
     * @param color 要使用的颜色 | Color to use
     * @param isBackground 是否为背景色 | Whether this is a background color
     */
    explicit ColorWrapper(ColorController::Color color, bool isBackground = false) : color_(color), isBackground_(isBackground) {}
    
    /**
     * 转换为字符串操作符，使对象可以用于字符串连接
     * Conversion to string operator, allowing the object to be used in string concatenation
     * 
     * @return 对应的ANSI转义序列字符串 | Corresponding ANSI escape sequence string
     */
    operator std::string() const {
#if defined(_WIN32) && defined(TC_ENABLE_WIN32_CONSOLE_API)
        // Windows 且启用宏：返回空字符串，因为使用Win32 API
        return "";
#else
        // 非 Windows：返回ANSI转义序列
        const char* ansiCode;
        if (isBackground_) {
            switch (color_) {
                case ColorController::Color::BLACK: ansiCode = "\033[40m"; break;
                case ColorController::Color::RED: ansiCode = "\033[41m"; break;
                case ColorController::Color::GREEN: ansiCode = "\033[42m"; break;
                case ColorController::Color::YELLOW: ansiCode = "\033[43m"; break;
                case ColorController::Color::BLUE: ansiCode = "\033[44m"; break;
                case ColorController::Color::MAGENTA: ansiCode = "\033[45m"; break;
                case ColorController::Color::CYAN: ansiCode = "\033[46m"; break;
                case ColorController::Color::WHITE: ansiCode = "\033[47m"; break;
                case ColorController::Color::BRIGHT_BLACK: ansiCode = "\033[100m"; break;
                case ColorController::Color::BRIGHT_RED: ansiCode = "\033[101m"; break;
                case ColorController::Color::BRIGHT_GREEN: ansiCode = "\033[102m"; break;
                case ColorController::Color::BRIGHT_YELLOW: ansiCode = "\033[103m"; break;
                case ColorController::Color::BRIGHT_BLUE: ansiCode = "\033[104m"; break;
                case ColorController::Color::BRIGHT_MAGENTA: ansiCode = "\033[105m"; break;
                case ColorController::Color::BRIGHT_CYAN: ansiCode = "\033[106m"; break;
                case ColorController::Color::BRIGHT_WHITE: ansiCode = "\033[107m"; break;
                case ColorController::Color::RESET: ansiCode = "\033[49m"; break;
                default: ansiCode = "\033[49m"; break;
            }
        } else {
            switch (color_) {
                case ColorController::Color::BLACK: ansiCode = "\033[30m"; break;
                case ColorController::Color::RED: ansiCode = "\033[31m"; break;
                case ColorController::Color::GREEN: ansiCode = "\033[32m"; break;
                case ColorController::Color::YELLOW: ansiCode = "\033[33m"; break;
                case ColorController::Color::BLUE: ansiCode = "\033[34m"; break;
                case ColorController::Color::MAGENTA: ansiCode = "\033[35m"; break;
                case ColorController::Color::CYAN: ansiCode = "\033[36m"; break;
                case ColorController::Color::WHITE: ansiCode = "\033[37m"; break;
                case ColorController::Color::BRIGHT_BLACK: ansiCode = "\033[90m"; break;
                case ColorController::Color::BRIGHT_RED: ansiCode = "\033[91m"; break;
                case ColorController::Color::BRIGHT_GREEN: ansiCode = "\033[92m"; break;
                case ColorController::Color::BRIGHT_YELLOW: ansiCode = "\033[93m"; break;
                case ColorController::Color::BRIGHT_BLUE: ansiCode = "\033[94m"; break;
                case ColorController::Color::BRIGHT_MAGENTA: ansiCode = "\033[95m"; break;
                case ColorController::Color::BRIGHT_CYAN: ansiCode = "\033[96m"; break;
                case ColorController::Color::BRIGHT_WHITE: ansiCode = "\033[97m"; break;
                case ColorController::Color::RESET: ansiCode = "\033[0m"; break;
                default: ansiCode = "\033[0m"; break;
            }
        }
        return std::string(ansiCode);
#endif
    }

    /**
     * 输出流操作符重载，使对象可以直接用于流式输出
     * Output stream operator overload, allowing the object to be used directly in stream output
     * 
     * @param os 输出流 | Output stream
     * @param wrapper 颜色包装器对象 | Color wrapper object
     * @return 输出流引用，用于链式调用 | Output stream reference for chaining
     */
    friend std::ostream& operator<<(std::ostream& os, const ColorWrapper& wrapper) {
#if defined(_WIN32) && defined(TC_ENABLE_WIN32_CONSOLE_API)
        // Windows 且启用宏：调用 Win32 API，不输出 ANSI
        if (wrapper.isBackground_) {
            ColorController::setBackground(wrapper.color_);
        } else {
            ColorController::setColor(wrapper.color_);
        }
        return os;
#else
        // 非 Windows：使用 ANSI 转义序列
        const char* ansiCode;
        if (wrapper.isBackground_) {
            switch (wrapper.color_) {
                case ColorController::Color::BLACK: ansiCode = "\033[40m"; break;
                case ColorController::Color::RED: ansiCode = "\033[41m"; break;
                case ColorController::Color::GREEN: ansiCode = "\033[42m"; break;
                case ColorController::Color::YELLOW: ansiCode = "\033[43m"; break;
                case ColorController::Color::BLUE: ansiCode = "\033[44m"; break;
                case ColorController::Color::MAGENTA: ansiCode = "\033[45m"; break;
                case ColorController::Color::CYAN: ansiCode = "\033[46m"; break;
                case ColorController::Color::WHITE: ansiCode = "\033[47m"; break;
                case ColorController::Color::BRIGHT_BLACK: ansiCode = "\033[100m"; break;
                case ColorController::Color::BRIGHT_RED: ansiCode = "\033[101m"; break;
                case ColorController::Color::BRIGHT_GREEN: ansiCode = "\033[102m"; break;
                case ColorController::Color::BRIGHT_YELLOW: ansiCode = "\033[103m"; break;
                case ColorController::Color::BRIGHT_BLUE: ansiCode = "\033[104m"; break;
                case ColorController::Color::BRIGHT_MAGENTA: ansiCode = "\033[105m"; break;
                case ColorController::Color::BRIGHT_CYAN: ansiCode = "\033[106m"; break;
                case ColorController::Color::BRIGHT_WHITE: ansiCode = "\033[107m"; break;
                case ColorController::Color::RESET:
                default:
                    ansiCode = "\033[49m";
                    break;
            }
        } else {
            switch (wrapper.color_) {
                case ColorController::Color::BLACK: ansiCode = "\033[30m"; break;
                case ColorController::Color::RED: ansiCode = "\033[31m"; break;
                case ColorController::Color::GREEN: ansiCode = "\033[32m"; break;
                case ColorController::Color::YELLOW: ansiCode = "\033[33m"; break;
                case ColorController::Color::BLUE: ansiCode = "\033[34m"; break;
                case ColorController::Color::MAGENTA: ansiCode = "\033[35m"; break;
                case ColorController::Color::CYAN: ansiCode = "\033[36m"; break;
                case ColorController::Color::WHITE: ansiCode = "\033[37m"; break;
                case ColorController::Color::BRIGHT_BLACK: ansiCode = "\033[90m"; break;
                case ColorController::Color::BRIGHT_RED: ansiCode = "\033[91m"; break;
                case ColorController::Color::BRIGHT_GREEN: ansiCode = "\033[92m"; break;
                case ColorController::Color::BRIGHT_YELLOW: ansiCode = "\033[93m"; break;
                case ColorController::Color::BRIGHT_BLUE: ansiCode = "\033[94m"; break;
                case ColorController::Color::BRIGHT_MAGENTA: ansiCode = "\033[95m"; break;
                case ColorController::Color::BRIGHT_CYAN: ansiCode = "\033[96m"; break;
                case ColorController::Color::BRIGHT_WHITE: ansiCode = "\033[97m"; break;
                case ColorController::Color::RESET:
                default:
                    ansiCode = "\033[0m";
                    break;
            }
        }
        return os << ansiCode;
#endif
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
#if defined(_WIN32) && defined(TC_ENABLE_WIN32_CONSOLE_API)
        // Windows 且启用宏：调用 Win32 API，不输出 ANSI
        ColorController::setRGBColor(wrapper.r_, wrapper.g_, wrapper.b_);
        return os;
#else
        std::ostringstream ansiCode;
        ansiCode << "\033[38;2;" << wrapper.r_ << ";" << wrapper.g_ << ";" << wrapper.b_ << "m";
        return os << ansiCode.str();
#endif
    }
};

/**
 * 字体样式包装器类
 * Font style wrapper class
 * 
 * 这个类封装了字体样式设置，便于在流式输出中使用。
 * 例如：std::cout << FontStyleWrapper(FontStyleWrapper::BOLD) << "粗体文本" << FontStyleWrapper(FontStyleWrapper::RESET);
 * 
 * This class encapsulates font style settings for easy use in stream output.
 * Example: std::cout << FontStyleWrapper(FontStyleWrapper::BOLD) << "Bold text" << FontStyleWrapper(FontStyleWrapper::RESET);
 */
class FontStyleWrapper {
public:
    /**
     * 字体样式枚举
     * Font style enumeration
     */
    enum Style {
        BOLD = 1,        // 粗体 | Bold
        FAINT = 2,       // 淡色 | Faint
        ITALIC = 3,      // 斜体 | Italic
        UNDERLINE = 4,   // 下划线 | Underline
        BLINK_SLOW = 5,  // 慢速闪烁 | Slow blink
        BLINK_FAST = 6,  // 快速闪烁 | Fast blink
        REVERSE = 7,     // 反色 | Reverse
        CONCEAL = 8,     // 隐藏 | Conceal
        CROSSED = 9,     // 删除线 | Crossed out
        DEFAULT = 10,    // 默认字体 | Default font
        FRAKTUR = 20,    // Fraktur字体 | Fraktur font
        DOUBLE_UNDERLINE = 21, // 双下划线 | Double underline
        NORMAL = 22,     // 正常强度 | Normal intensity
        NOT_ITALIC = 23, // 非斜体 | Not italic
        NO_UNDERLINE = 24, // 无下划线 | No underline
        NO_BLINK = 25,   // 无闪烁 | No blink
        NO_REVERSE = 27, // 无反色 | No reverse
        REVEAL = 28,     // 显示 | Reveal
        NOT_CROSSED = 29, // 无删除线 | Not crossed
        RESET = 0        // 重置 | Reset
    };
    
private:
    Style style_; // 字体样式 | Font style
    
public:
    /**
     * 构造函数
     * Constructor
     * 
     * @param style 字体样式 | Font style
     */
    explicit FontStyleWrapper(Style style) : style_(style) {}
    
    /**
     * 输出流操作符重载，使对象可以直接用于流式输出
     * Output stream operator overload, allowing the object to be used directly in stream output
     * 
     * @param os 输出流 | Output stream
     * @param wrapper 字体样式包装器对象 | Font style wrapper object
     * @return 输出流引用，用于链式调用 | Output stream reference for chaining
     */
    friend std::ostream& operator<<(std::ostream& os, const FontStyleWrapper& wrapper) {
#if defined(_WIN32) && defined(TC_ENABLE_WIN32_CONSOLE_API)
        // Windows 且启用宏：调用 Win32 API
        switch (wrapper.style_) {
            case BOLD: ColorController::setBold(true); break;
            case RESET: ColorController::setColor(ColorController::Color::RESET); break;
            // Windows控制台API不支持其他字体样式，直接输出ANSI序列
            case ITALIC: os << "\033[3m"; break;
            case UNDERLINE: os << "\033[4m"; break;
            case REVERSE: os << "\033[7m"; break;
            case CROSSED: os << "\033[9m"; break;
            default: break;
        }
        return os;
#else
        // 默认使用ANSI序列
        switch (wrapper.style_) {
            case BOLD: return os << "\033[1m";
            case ITALIC: return os << "\033[3m";
            case UNDERLINE: return os << "\033[4m";
            case REVERSE: return os << "\033[7m";
            case CROSSED: return os << "\033[9m";
            case RESET: return os << "\033[0m";
            default: return os << "\033[0m";
        }
#endif
    }
};

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
 * 为文本添加RGB颜色
 * Add RGB color to text
 * 
 * @param text 要着色的文本 | Text to colorize
 * @param r 红色分量(0-255) | Red component (0-255)
 * @param g 绿色分量(0-255) | Green component (0-255)
 * @param b 蓝色分量(0-255) | Blue component (0-255)
 * @return 带有RGB颜色代码的字符串 | String with RGB color codes
 */
inline std::string colorizeRGB(const std::string& text, int r, int g, int b) {
    std::ostringstream oss;
    // 添加RGB颜色代码，文本，然后重置颜色 | Add RGB color code, text, then reset color
    oss << RGBColorWrapper(r, g, b) << text << ColorWrapper(ColorController::Color::RESET);
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

/**
 * 为文本添加青色
 * Add cyan color to text
 * 
 * @param text 要着色的文本 | Text to colorize
 * @return 青色文本字符串 | Cyan text string
 */
inline std::string cyan(const std::string& text) {
    return colorize(text, ColorController::Color::CYAN);
}

/**
 * 为文本添加洋红色
 * Add magenta color to text
 * 
 * @param text 要着色的文本 | Text to colorize
 * @return 洋红色文本字符串 | Magenta text string
 */
inline std::string magenta(const std::string& text) {
    return colorize(text, ColorController::Color::MAGENTA);
}

/**
 * 为文本添加白色
 * Add white color to text
 * 
 * @param text 要着色的文本 | Text to colorize
 * @return 白色文本字符串 | White text string
 */
inline std::string white(const std::string& text) {
    return colorize(text, ColorController::Color::WHITE);
}

/**
 * 为文本添加亮红色
 * Add bright red color to text
 * 
 * @param text 要着色的文本 | Text to colorize
 * @return 亮红色文本字符串 | Bright red text string
 */
inline std::string brightRed(const std::string& text) {
    return colorize(text, ColorController::Color::BRIGHT_RED);
}

/**
 * 为文本添加亮绿色
 * Add bright green color to text
 * 
 * @param text 要着色的文本 | Text to colorize
 * @return 亮绿色文本字符串 | Bright green text string
 */
inline std::string brightGreen(const std::string& text) {
    return colorize(text, ColorController::Color::BRIGHT_GREEN);
}

/**
 * 为文本添加亮蓝色
 * Add bright blue color to text
 * 
 * @param text 要着色的文本 | Text to colorize
 * @return 亮蓝色文本字符串 | Bright blue text string
 */
inline std::string brightBlue(const std::string& text) {
    return colorize(text, ColorController::Color::BRIGHT_BLUE);
}

/**
 * 为文本添加亮黄色
 * Add bright yellow color to text
 * 
 * @param text 要着色的文本 | Text to colorize
 * @return 亮黄色文本字符串 | Bright yellow text string
 */
inline std::string brightYellow(const std::string& text) {
    return colorize(text, ColorController::Color::BRIGHT_YELLOW);
}

} // namespace tc

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

#endif // TC_COLORS_HPP