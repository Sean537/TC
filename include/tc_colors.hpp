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
 * 版本 Version: 1.1.3
 * 作者 Author: 537 Studio
 * 许可 License: MIT
 */

#ifndef TC_COLORS_HPP
#define TC_COLORS_HPP

// 标准库包含 | Standard library includes
#include <iostream>    // 输入输出流 | Input/output streams
#include <sstream>     // 字符串流 | String streams
#include <stack>       // 栈容器 | Stack container
#include <string>      // 字符串 | String
#include <regex>       // 正则表达式 | Regular expressions

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
 */
class Win32Console {
private:
    HANDLE hConsole_;                        // 控制台句柄 | Console handle
    CONSOLE_SCREEN_BUFFER_INFO originalInfo_; // 原始缓冲区信息 | Original buffer info
    std::stack<WORD> colorStack_;            // 颜色栈，用于保存和恢复颜色 | Color stack for saving/restoring colors
    bool initialized_ = false;               // 初始化标志 | Initialization flag
    bool vtEnabled_ = false;                 // 虚拟终端处理是否启用 | Whether VT processing is enabled

    Win32Console() {
        hConsole_ = GetStdHandle(STD_OUTPUT_HANDLE);
        
        if (hConsole_ != INVALID_HANDLE_VALUE) {
            GetConsoleScreenBufferInfo(hConsole_, &originalInfo_);
            initialized_ = true;
            
            // 设置UTF-8编码支持 | Set UTF-8 encoding support
            SetConsoleOutputCP(CP_UTF8);
            SetConsoleCP(CP_UTF8);
            
            DWORD dwMode = 0;
            if (GetConsoleMode(hConsole_, &dwMode)) {
#if defined(TC_ENABLE_WIN32_CONSOLE_API)
                // 强制禁用 ANSI 虚拟终端处理 | Force disable ANSI VT processing
                SetConsoleMode(hConsole_, dwMode & ~ENABLE_VIRTUAL_TERMINAL_PROCESSING);
                vtEnabled_ = false;
#else
                // 尝试启用 ANSI 虚拟终端处理（Win10 1809+ 支持）
                if (SetConsoleMode(hConsole_, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING)) {
                    vtEnabled_ = true;
                } else {
                    vtEnabled_ = false;
                }
#endif
            }
        }
    }

public:
    static Win32Console& getInstance() {
        static Win32Console instance;
        return instance;
    }

    bool isInitialized() const { return initialized_; }
    bool isVTEnabled() const { return vtEnabled_; }

    void setColor(WORD color) {
        if (initialized_) {
            SetConsoleTextAttribute(hConsole_, color);
        }
    }

    void pushColor(WORD color) {
        if (initialized_) {
            CONSOLE_SCREEN_BUFFER_INFO info;
            GetConsoleScreenBufferInfo(hConsole_, &info);
            colorStack_.push(info.wAttributes);
            setColor(color);
        }
    }

    void popColor() {
        if (initialized_ && !colorStack_.empty()) {
            setColor(colorStack_.top());
            colorStack_.pop();
        }
    }

    void resetColor() {
        if (initialized_) {
            setColor(originalInfo_.wAttributes);
        }
    }

    WORD getCurrentColor() const {
        if (initialized_) {
            CONSOLE_SCREEN_BUFFER_INFO info;
            GetConsoleScreenBufferInfo(hConsole_, &info);
            return info.wAttributes;
        }
        return win32_colors::WHITE;
    }

    void moveCursor(int x, int y) {
        if (initialized_) {
            COORD coord = {static_cast<SHORT>(x), static_cast<SHORT>(y)};
            SetConsoleCursorPosition(hConsole_, coord);
        }
    }

    void clearScreen() {
        if (initialized_) {
            CONSOLE_SCREEN_BUFFER_INFO info;
            GetConsoleScreenBufferInfo(hConsole_, &info);
            DWORD written;
            COORD topLeft = {0, 0};
            FillConsoleOutputCharacter(hConsole_, ' ', info.dwSize.X * info.dwSize.Y, topLeft, &written);
            FillConsoleOutputAttribute(hConsole_, info.wAttributes, info.dwSize.X * info.dwSize.Y, topLeft, &written);
            SetConsoleCursorPosition(hConsole_, topLeft);
        }
    }

    std::pair<int, int> getConsoleSize() const {
        if (initialized_) {
            CONSOLE_SCREEN_BUFFER_INFO info;
            GetConsoleScreenBufferInfo(hConsole_, &info);
            return {info.srWindow.Right - info.srWindow.Left + 1,
                   info.srWindow.Bottom - info.srWindow.Top + 1};
        }
        return {80, 25};
    }

    WORD rgbToWin32Color(int r, int g, int b) const {
        bool isRed = r > 128;
        bool isGreen = g > 128;
        bool isBlue = b > 128;
        bool isBright = (r + g + b) > 384;
        WORD color = 0;
        if (isRed) color |= FOREGROUND_RED;
        if (isGreen) color |= FOREGROUND_GREEN;
        if (isBlue) color |= FOREGROUND_BLUE;
        if (isBright) color |= FOREGROUND_INTENSITY;
        return color ? color : win32_colors::WHITE;
    }

    ~Win32Console() {
        if (initialized_) {
            resetColor();
        }
    }
};
#endif

/**
 * 跨平台颜色控制类
 * Cross-platform color controller class
 */
class ColorController {
public:
    enum class Color {
        BLACK, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE,
        BRIGHT_BLACK, BRIGHT_RED, BRIGHT_GREEN, BRIGHT_YELLOW,
        BRIGHT_BLUE, BRIGHT_MAGENTA, BRIGHT_CYAN, BRIGHT_WHITE,
        RESET
    };

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
            case Color::RESET: default: console.resetColor(); return;
        }
        console.setColor(winColor);
#else
        const char* ansiColor;
        switch (color) {
            case Color::BLACK: ansiColor = "\033[30m"; break;
            case Color::RED: ansiColor = "\033[31m"; break;
            case Color::GREEN: ansiColor = "\033[32m"; break;
            case Color::YELLOW: ansiColor = "\033[33m"; break;
            case Color::BLUE: ansiColor = "\033[34m"; break;
            case Color::MAGENTA: ansiColor = "\033[35m"; break;
            case Color::CYAN: ansiColor = "\033[36m"; break;
            case Color::WHITE: ansiColor = "\033[37m"; break;
            case Color::BRIGHT_BLACK: ansiColor = "\033[90m"; break;
            case Color::BRIGHT_RED: ansiColor = "\033[91m"; break;
            case Color::BRIGHT_GREEN: ansiColor = "\033[92m"; break;
            case Color::BRIGHT_YELLOW: ansiColor = "\033[93m"; break;
            case Color::BRIGHT_BLUE: ansiColor = "\033[94m"; break;
            case Color::BRIGHT_MAGENTA: ansiColor = "\033[95m"; break;
            case Color::BRIGHT_CYAN: ansiColor = "\033[96m"; break;
            case Color::BRIGHT_WHITE: ansiColor = "\033[97m"; break;
            case Color::RESET: default: ansiColor = "\033[0m"; break;
        }
        std::cout << ansiColor;
#endif
    }

    static void setBackground(Color color) {
#ifdef _WIN32
        auto& console = Win32Console::getInstance();
        WORD bgColor = 0;
        switch (color) {
            case Color::BLACK: bgColor = 0; break;
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
            case Color::RESET: default: console.resetColor(); return;
        }
        WORD currentColor = console.getCurrentColor();
        console.setColor((currentColor & 0x0F) | bgColor);
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
            case Color::RESET: default: ansiBgColor = "\033[49m"; break;
        }
        std::cout << ansiBgColor;
#endif
    }

    static void setRGBColor(int r, int g, int b) {
#ifdef _WIN32
        auto& console = Win32Console::getInstance();
        console.setColor(console.rgbToWin32Color(r, g, b));
#else
        std::cout << "\033[38;2;" << r << ";" << g << ";" << b << "m";
#endif
    }

    static void setBold(bool enable) {
#ifdef _WIN32
        auto& console = Win32Console::getInstance();
        WORD current = console.getCurrentColor();
        console.setColor(enable ? (current | FOREGROUND_INTENSITY) : (current & ~FOREGROUND_INTENSITY));
#else
        std::cout << (enable ? "\033[1m" : "\033[22m");
#endif
    }
};

/**
 * 颜色包装器类
 * Color wrapper class
 */
class ColorWrapper {
private:
    ColorController::Color color_;
    bool isBackground_;
    
public:
    explicit ColorWrapper(ColorController::Color color, bool isBackground = false) : color_(color), isBackground_(isBackground) {}
    
    operator std::string() const {
#if defined(_WIN32)
        auto& console = Win32Console::getInstance();
        if (console.isVTEnabled()) {
            // VT模式下返回正常ANSI
            goto return_ansi;
        }
#if defined(TC_ENABLE_WIN32_CONSOLE_API)
        // Win32 API 模式下，无法通过字符串携带颜色信息，返回空以保证文本纯净
        return "";
#endif
#endif

return_ansi:
        const char* code;
        if (isBackground_) {
            switch (color_) {
                case ColorController::Color::BLACK: code = "\033[40m"; break;
                case ColorController::Color::RED: code = "\033[41m"; break;
                case ColorController::Color::GREEN: code = "\033[42m"; break;
                case ColorController::Color::YELLOW: code = "\033[43m"; break;
                case ColorController::Color::BLUE: code = "\033[44m"; break;
                case ColorController::Color::MAGENTA: code = "\033[45m"; break;
                case ColorController::Color::CYAN: code = "\033[46m"; break;
                case ColorController::Color::WHITE: code = "\033[47m"; break;
                case ColorController::Color::BRIGHT_BLACK: code = "\033[100m"; break;
                case ColorController::Color::BRIGHT_RED: code = "\033[101m"; break;
                case ColorController::Color::BRIGHT_GREEN: code = "\033[102m"; break;
                case ColorController::Color::BRIGHT_YELLOW: code = "\033[103m"; break;
                case ColorController::Color::BRIGHT_BLUE: code = "\033[104m"; break;
                case ColorController::Color::BRIGHT_MAGENTA: code = "\033[105m"; break;
                case ColorController::Color::BRIGHT_CYAN: code = "\033[106m"; break;
                case ColorController::Color::BRIGHT_WHITE: code = "\033[107m"; break;
                default: code = "\033[49m"; break;
            }
        } else {
            switch (color_) {
                case ColorController::Color::BLACK: code = "\033[30m"; break;
                case ColorController::Color::RED: code = "\033[31m"; break;
                case ColorController::Color::GREEN: code = "\033[32m"; break;
                case ColorController::Color::YELLOW: code = "\033[33m"; break;
                case ColorController::Color::BLUE: code = "\033[34m"; break;
                case ColorController::Color::MAGENTA: code = "\033[35m"; break;
                case ColorController::Color::CYAN: code = "\033[36m"; break;
                case ColorController::Color::WHITE: code = "\033[37m"; break;
                case ColorController::Color::BRIGHT_BLACK: code = "\033[90m"; break;
                case ColorController::Color::BRIGHT_RED: code = "\033[91m"; break;
                case ColorController::Color::BRIGHT_GREEN: code = "\033[92m"; break;
                case ColorController::Color::BRIGHT_YELLOW: code = "\033[93m"; break;
                case ColorController::Color::BRIGHT_BLUE: code = "\033[94m"; break;
                case ColorController::Color::BRIGHT_MAGENTA: code = "\033[95m"; break;
                case ColorController::Color::BRIGHT_CYAN: code = "\033[96m"; break;
                case ColorController::Color::BRIGHT_WHITE: code = "\033[97m"; break;
                case ColorController::Color::RESET: default: code = "\033[0m"; break;
            }
        }
        return std::string(code);
    }

    friend std::ostream& operator<<(std::ostream& os, const ColorWrapper& wrapper) {
#if defined(_WIN32)
        auto& console = Win32Console::getInstance();
        if (!console.isVTEnabled()) {
#if defined(TC_ENABLE_WIN32_CONSOLE_API)
            if (wrapper.isBackground_) ColorController::setBackground(wrapper.color_);
            else ColorController::setColor(wrapper.color_);
            return os;
#else
            // 非VT环境且未开启API模式：过滤ANSI以保障文本输出
            return os;
#endif
        }
#endif
        return os << (std::string)wrapper;
    }
};

/**
 * RGB颜色包装器类
 * RGB color wrapper class
 */
class RGBColorWrapper {
private:
    int r_, g_, b_;
public:
    RGBColorWrapper(int r, int g, int b) : r_(r), g_(g), b_(b) {}
    friend std::ostream& operator<<(std::ostream& os, const RGBColorWrapper& wrapper) {
#if defined(_WIN32)
        auto& console = Win32Console::getInstance();
        if (!console.isVTEnabled()) {
#if defined(TC_ENABLE_WIN32_CONSOLE_API)
            ColorController::setRGBColor(wrapper.r_, wrapper.g_, wrapper.b_);
            return os;
#else
            return os;
#endif
        }
#endif
        return os << "\033[38;2;" << wrapper.r_ << ";" << wrapper.g_ << ";" << wrapper.b_ << "m";
    }
};

/**
 * 字体样式包装器类
 * Font style wrapper class
 */
class FontStyleWrapper {
public:
    enum Style {
        BOLD, FAINT, ITALIC, UNDERLINE, BLINK_SLOW, BLINK_FAST, REVERSE, CONCEAL, CROSSED,
        DEFAULT, FRAKTUR, DOUBLE_UNDERLINE, NORMAL, NOT_ITALIC, NO_UNDERLINE, NO_BLINK,
        NO_REVERSE, REVEAL, NOT_CROSSED, RESET
    };
private:
    Style style_;
public:
    explicit FontStyleWrapper(Style style) : style_(style) {}
    friend std::ostream& operator<<(std::ostream& os, const FontStyleWrapper& wrapper) {
#if defined(_WIN32)
        auto& console = Win32Console::getInstance();
        if (!console.isVTEnabled()) {
#if defined(TC_ENABLE_WIN32_CONSOLE_API)
            if (wrapper.style_ == BOLD) ColorController::setBold(true);
            else if (wrapper.style_ == NORMAL || wrapper.style_ == RESET) ColorController::setBold(false);
            if (wrapper.style_ == RESET) console.resetColor();
            return os;
#else
            return os;
#endif
        }
#endif
        const char* code;
        switch (wrapper.style_) {
            case BOLD: code = "\033[1m"; break;
            case FAINT: code = "\033[2m"; break;
            case ITALIC: code = "\033[3m"; break;
            case UNDERLINE: code = "\033[4m"; break;
            case BLINK_SLOW: code = "\033[5m"; break;
            case BLINK_FAST: code = "\033[6m"; break;
            case REVERSE: code = "\033[7m"; break;
            case CONCEAL: code = "\033[8m"; break;
            case CROSSED: code = "\033[9m"; break;
            case DEFAULT: code = "\033[10m"; break;
            case FRAKTUR: code = "\033[20m"; break;
            case DOUBLE_UNDERLINE: code = "\033[21m"; break;
            case NORMAL: code = "\033[22m"; break;
            case NOT_ITALIC: code = "\033[23m"; break;
            case NO_UNDERLINE: code = "\033[24m"; break;
            case NO_BLINK: code = "\033[25m"; break;
            case NO_REVERSE: code = "\033[27m"; break;
            case REVEAL: code = "\033[28m"; break;
            case NOT_CROSSED: code = "\033[29m"; break;
            case RESET: default: code = "\033[0m"; break;
        }
        return os << code;
    }
};

/**
 * 颜色应用辅助函数
 */
inline std::string colorize(const std::string& text, ColorController::Color color) {
    return (std::string)ColorWrapper(color) + text + (std::string)ColorWrapper(ColorController::Color::RESET);
}

inline std::string colorizeRGB(const std::string& text, int r, int g, int b) {
#if defined(_WIN32) && defined(TC_ENABLE_WIN32_CONSOLE_API)
    if (!Win32Console::getInstance().isVTEnabled()) return text;
#endif
    std::stringstream ss;
    ss << "\033[38;2;" << r << ";" << g << ";" << b << "m" << text << "\033[0m";
    return ss.str();
}

inline std::string red(const std::string& text) { return colorize(text, ColorController::Color::RED); }
inline std::string green(const std::string& text) { return colorize(text, ColorController::Color::GREEN); }
inline std::string blue(const std::string& text) { return colorize(text, ColorController::Color::BLUE); }
inline std::string yellow(const std::string& text) { return colorize(text, ColorController::Color::YELLOW); }
inline std::string cyan(const std::string& text) { return colorize(text, ColorController::Color::CYAN); }
inline std::string magenta(const std::string& text) { return colorize(text, ColorController::Color::MAGENTA); }
inline std::string white(const std::string& text) { return colorize(text, ColorController::Color::WHITE); }
inline std::string brightRed(const std::string& text) { return colorize(text, ColorController::Color::BRIGHT_RED); }
inline std::string brightGreen(const std::string& text) { return colorize(text, ColorController::Color::BRIGHT_GREEN); }
inline std::string brightBlue(const std::string& text) { return colorize(text, ColorController::Color::BRIGHT_BLUE); }
inline std::string brightYellow(const std::string& text) { return colorize(text, ColorController::Color::BRIGHT_YELLOW); }

} // namespace tc

#define TCOLOR_RGB(r, g, b) tc::RGBColorWrapper(r, g, b)

#endif // TC_COLORS_HPP
