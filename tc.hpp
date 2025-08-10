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

*/

#ifndef TC_HPP // 头文件保护，防止重复包含 Header guard, prevent multiple inclusion
#define TC_HPP

#define TC_VERSION "1.0.1" // 版本号 Version number

#include <iostream> // 标准输入输出流 Standard IO stream
#include <string>    // 字符串 String
#include <sstream>   // 字符串流 String stream
#include <thread>    // 线程 Thread
#include <chrono>    // 时间相关 Chrono
#include <memory>    // 智能指针 Smart pointer
#include <functional>// 函数对象 Function object
#include <type_traits>// 类型特性 Type traits
#include <stack>     // 栈 Stack

#ifdef _WIN32 // Windows平台分支 Windows platform branch
    #include <windows.h> // Windows API
    #include <io.h>      // IO操作 IO operations
    #include <fcntl.h>   // 文件控制 File control
    #ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING // 启用虚拟终端处理宏 Enable virtual terminal processing macro
        #define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
    #endif
#else // 非Windows平台 Non-Windows platform
    #include <unistd.h>  // Unix标准函数 Unix standard functions
    #include <sys/ioctl.h> // 终端IO控制 Terminal IO control
#endif

// ===== ANSI前景色/背景色/字体样式宏（全局作用域，支持TCOLOR_XXX、BCOLOR_XXX、TFONT_XXX） =====
#define TCOLOR_BLACK   "\033[30m"
#define TCOLOR_RED     "\033[31m"
#define TCOLOR_GREEN   "\033[32m"
#define TCOLOR_YELLOW  "\033[33m"
#define TCOLOR_BLUE    "\033[34m"
#define TCOLOR_MAGENTA "\033[35m"
#define TCOLOR_CYAN    "\033[36m"
#define TCOLOR_WHITE   "\033[37m"
#define TCOLOR_DEFAULT "\033[39m"
#define TCOLOR_RESET   "\033[0m"
#define TCOLOR_RGB(r, g, b) tc::RGBColorWrapper(r, g, b)
#define BCOLOR_BLACK   "\033[40m"
#define BCOLOR_RED     "\033[41m"
#define BCOLOR_GREEN   "\033[42m"
#define BCOLOR_YELLOW  "\033[43m"
#define BCOLOR_BLUE    "\033[44m"
#define BCOLOR_MAGENTA "\033[45m"
#define BCOLOR_CYAN    "\033[46m"
#define BCOLOR_WHITE   "\033[47m"
#define BCOLOR_DEFAULT "\033[49m"
// ===== ANSI字体样式宏（全局作用域，直接用） =====
#define TFONT_BOLD        "\033[1m"   // 粗体/加粗
#define TFONT_FAINT       "\033[2m"   // 微弱/淡色
#define TFONT_ITALIC      "\033[3m"   // 斜体
#define TFONT_UNDERLINE   "\033[4m"   // 下划线
#define TFONT_BLINK_SLOW  "\033[5m"   // 慢速闪烁
#define TFONT_BLINK_FAST  "\033[6m"   // 快速闪烁
#define TFONT_REVERSE     "\033[7m"   // 反色
#define TFONT_CONCEAL     "\033[8m"   // 隐藏
#define TFONT_CROSSED     "\033[9m"   // 删除线
#define TFONT_DEFAULT     "\033[10m"  // 默认字体
#define TFONT_FRAKTUR     "\033[20m"  // Fraktur字体（部分终端支持）
#define TFONT_DOUBLE_UNDERLINE "\033[21m" // 双下划线/粗体关闭
#define TFONT_NORMAL      "\033[22m"  // 粗体/淡色关闭
#define TFONT_NOT_ITALIC  "\033[23m"  // 关闭斜体/Fraktur
#define TFONT_NO_UNDERLINE "\033[24m" // 关闭下划线
#define TFONT_NO_BLINK    "\033[25m"  // 关闭闪烁
#define TFONT_NO_REVERSE  "\033[27m"  // 关闭反色
#define TFONT_REVEAL      "\033[28m"  // 关闭隐藏
#define TFONT_NOT_CROSSED "\033[29m"  // 关闭删除线
#define TFONT_THICK       TFONT_BOLD   // 兼容别名
#define TFONT_RESET       "\033[0m"   // 全部重置
// 用法示例：tc::println(TCOLOR_RED, BCOLOR_YELLOW, TFONT_BOLD, "红字黄底粗体")

namespace tc { // 主命名空间 Main namespace

// ========== print/println ========== //
// 链式print/println类，兼容Python风格
// 链式print/println类，兼容Python风格
class PrintProxy {
public:
    const PrintProxy& print() const { return *this; }
    template<typename... Args>
    const PrintProxy& print(Args&&... args) const { (void)std::initializer_list<int>{(std::cout << std::forward<Args>(args), 0)...}; return *this; }
    template<typename... Args>
    const PrintProxy& println(Args&&... args) const { (void)std::initializer_list<int>{(std::cout << std::forward<Args>(args), 0)...}; std::cout << std::endl; return *this; }
};
inline const PrintProxy& print() { static PrintProxy p; return p; }
inline const PrintProxy& println() { static PrintProxy p; std::cout << std::endl; return p; }

// 支持一次性多参数打印的print/println
template<typename... Args>
inline void print(Args&&... args) { (void)std::initializer_list<int>{(std::cout << std::forward<Args>(args), 0)...}; }
template<typename... Args>
inline void println(Args&&... args) { (void)std::initializer_list<int>{(std::cout << std::forward<Args>(args), 0)...}; std::cout << std::endl; }

// ========== wait/waitKey ========== //
inline void wait(double seconds) { std::this_thread::sleep_for(std::chrono::milliseconds((int)(seconds*1000))); }
#ifdef _WIN32
#include <conio.h>
inline void waitKey() { _getch(); }
inline void waitKey(char key) { while (_getch() != key) {} }
inline void waitKey(int key) { while (_getch() != key) {} }
#else
#include <termios.h>
inline void waitKey() {
    termios oldt, newt;
    tcgetattr(0, &oldt);
    newt = oldt;
    newt.c_lflag &= ~ICANON;
    tcsetattr(0, TCSANOW, &newt);
    getchar();
    tcsetattr(0, TCSANOW, &oldt);
}
inline void waitKey(char key) {
    termios oldt, newt;
    tcgetattr(0, &oldt);
    newt = oldt;
    newt.c_lflag &= ~ICANON;
    tcsetattr(0, TCSANOW, &newt);
    int ch;
    do { ch = getchar(); } while (ch != key);
    tcsetattr(0, TCSANOW, &oldt);
}
inline void waitKey(int key) { waitKey((char)key); }
#endif
#define KEY_ESC      27
#define KEY_SPACE    32
#define KEY_ENTER    13
#define KEY_TAB       9
#define KEY_BACKSPACE 8
#define KEY_INSERT   0x2D
#define KEY_DELETE   0x2E
#define KEY_HOME     0x24
#define KEY_END      0x23
#define KEY_PAGEUP   0x21
#define KEY_PAGEDOWN 0x22
#define KEY_UP       0x26
#define KEY_DOWN     0x28
#define KEY_LEFT     0x25
#define KEY_RIGHT    0x27
#define KEY_F1       0x70
#define KEY_F2       0x71
#define KEY_F3       0x72
#define KEY_F4       0x73
#define KEY_F5       0x74
#define KEY_F6       0x75
#define KEY_F7       0x76
#define KEY_F8       0x77
#define KEY_F9       0x78
#define KEY_F10      0x79
#define KEY_F11      0x7A
#define KEY_F12      0x7B

// ========== Printer类 ========== //
class Printer {
public:
    Printer& clear() { std::cout << "\033[2J\033[H"; return *this; }
    Printer& moveCursor(int x, int y) { std::cout << "\033[" << y << ";" << x << "H"; return *this; }
    Printer& print() { return *this; }
    template<typename... Args>
    Printer& print(Args&&... args) { (void)std::initializer_list<int>{(std::cout << std::forward<Args>(args), 0)...}; return *this; }
    template<typename... Args>
    Printer& println(Args&&... args) { (void)std::initializer_list<int>{(std::cout << std::forward<Args>(args), 0)...}; std::cout << std::endl; return *this; }
    Printer& hideCursor() { std::cout << "\033[?25l"; return *this; }
    Printer& showCursor() { std::cout << "\033[?25h"; return *this; }
    enum class Direction { Up, Down, Left, Right };
    Printer& moveCursor(Direction dir, int n) {
        switch(dir) {
            case Direction::Up: std::cout << "\033[" << n << "A"; break;
            case Direction::Down: std::cout << "\033[" << n << "B"; break;
            case Direction::Right: std::cout << "\033[" << n << "C"; break;
            case Direction::Left: std::cout << "\033[" << n << "D"; break;
        }
        return *this;
    }
    std::pair<int,int> getSize() {
#ifdef _WIN32
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        int cols = 80, rows = 25;
        HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
        if (GetConsoleScreenBufferInfo(h, &csbi)) {
            cols = csbi.srWindow.Right - csbi.srWindow.Left + 1;
            rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
        }
        return {cols, rows};
#else
        struct winsize size;
        if (ioctl(1, TIOCGWINSZ, &size) == 0)
            return {size.ws_col, size.ws_row};
        return {80, 25};
#endif
    }
};
inline Printer printer() { return Printer(); }










#ifdef _WIN32 // Windows平台分支 Windows platform branch

// Windows 颜色常量映射，便于跨平台统一接口
// Windows color constant mapping for cross-platform interface
namespace win32_colors {
    constexpr WORD BLACK = 0; // 黑色 Black
    constexpr WORD DARK_BLUE = FOREGROUND_BLUE; // 深蓝 Dark blue
    constexpr WORD DARK_GREEN = FOREGROUND_GREEN; // 深绿 Dark green
    constexpr WORD DARK_CYAN = FOREGROUND_GREEN | FOREGROUND_BLUE; // 深青 Dark cyan
    constexpr WORD DARK_RED = FOREGROUND_RED; // 深红 Dark red
    constexpr WORD DARK_MAGENTA = FOREGROUND_RED | FOREGROUND_BLUE; // 深洋红 Dark magenta
    constexpr WORD DARK_YELLOW = FOREGROUND_RED | FOREGROUND_GREEN; // 深黄 Dark yellow
    constexpr WORD GRAY = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE; // 灰色 Gray
    constexpr WORD DARK_GRAY = FOREGROUND_INTENSITY; // 深灰 Dark gray
    constexpr WORD BLUE = FOREGROUND_BLUE | FOREGROUND_INTENSITY; // 亮蓝 Bright blue
    constexpr WORD GREEN = FOREGROUND_GREEN | FOREGROUND_INTENSITY; // 亮绿 Bright green
    constexpr WORD CYAN = FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY; // 亮青 Bright cyan
    constexpr WORD RED = FOREGROUND_RED | FOREGROUND_INTENSITY; // 亮红 Bright red
    constexpr WORD MAGENTA = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY; // 亮洋红 Bright magenta
    constexpr WORD YELLOW = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY; // 亮黄 Bright yellow
    constexpr WORD WHITE = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY; // 白色 White
}

// Windows 控制台管理类，封装颜色/光标/清屏等操作
// Windows console manager, encapsulates color/cursor/clear screen etc.
class Win32Console {
private:
    HANDLE hConsole_; // 控制台句柄 Console handle
    CONSOLE_SCREEN_BUFFER_INFO originalInfo_; // 原始缓冲区信息 Original buffer info
    std::stack<WORD> colorStack_; // 颜色栈 Color stack
    bool initialized_ = false; // 初始化标志 Initialization flag

    // 构造函数，初始化控制台和UTF-8支持
    // Constructor, initialize console and UTF-8 support
    Win32Console() {
        hConsole_ = GetStdHandle(STD_OUTPUT_HANDLE); // 获取标准输出句柄 Get standard output handle
        if (hConsole_ != INVALID_HANDLE_VALUE) {
            GetConsoleScreenBufferInfo(hConsole_, &originalInfo_); // 获取原始信息 Get original info
            initialized_ = true;
            // 设置UTF-8支持 Set UTF-8 support
            SetConsoleOutputCP(CP_UTF8);
            SetConsoleCP(CP_UTF8);
            // 尝试启用ANSI处理 Try enable ANSI processing
            DWORD dwMode = 0;
            if (GetConsoleMode(hConsole_, &dwMode)) {
                SetConsoleMode(hConsole_, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
            }
        }
    }

public:
    // 单例获取实例 Get singleton instance
    static Win32Console& getInstance() {
        static Win32Console instance;
        return instance;
    }

    // 判断是否初始化 Is initialized
    bool isInitialized() const { return initialized_; }

    // 设置颜色 Set color
    void setColor(WORD color) {
        if (initialized_) {
            SetConsoleTextAttribute(hConsole_, color);
        }
    }

    // 推入当前颜色到栈 Push current color to stack
    void pushColor(WORD color) {
        if (initialized_) {
            CONSOLE_SCREEN_BUFFER_INFO info;
            GetConsoleScreenBufferInfo(hConsole_, &info);
            colorStack_.push(info.wAttributes);
            setColor(color);
        }
    }

    // 弹出颜色栈并恢复 Pop color stack and restore
    void popColor() {
        if (initialized_ && !colorStack_.empty()) {
            setColor(colorStack_.top());
            colorStack_.pop();
        }
    }

    // 重置为原始颜色 Reset to original color
    void resetColor() {
        if (initialized_) {
            setColor(originalInfo_.wAttributes);
        }
    }

    // 获取当前颜色 Get current color
    WORD getCurrentColor() const {
        if (initialized_) {
            CONSOLE_SCREEN_BUFFER_INFO info;
            GetConsoleScreenBufferInfo(hConsole_, &info);
            return info.wAttributes;
        }
        return win32_colors::WHITE;
    }

    // 移动光标 Move cursor
    void moveCursor(int x, int y) {
        if (initialized_) {
            COORD coord = {static_cast<SHORT>(x), static_cast<SHORT>(y)};
            SetConsoleCursorPosition(hConsole_, coord);
        }
    }

    // 清屏 Clear screen
    void clearScreen() {
        if (initialized_) {
            CONSOLE_SCREEN_BUFFER_INFO info;
            GetConsoleScreenBufferInfo(hConsole_, &info);
            DWORD written;
            COORD topLeft = {0, 0};
            FillConsoleOutputCharacter(hConsole_, ' ', 
                info.dwSize.X * info.dwSize.Y, topLeft, &written);
            FillConsoleOutputAttribute(hConsole_, info.wAttributes,
                info.dwSize.X * info.dwSize.Y, topLeft, &written);
            SetConsoleCursorPosition(hConsole_, topLeft);
        }
    }

    // 获取终端尺寸 Get console size
    std::pair<int, int> getConsoleSize() const {
        if (initialized_) {
            CONSOLE_SCREEN_BUFFER_INFO info;
            GetConsoleScreenBufferInfo(hConsole_, &info);
            return {info.srWindow.Right - info.srWindow.Left + 1,
                   info.srWindow.Bottom - info.srWindow.Top + 1};
        }
        return {80, 25}; // 默认值 Default value
    }

    // RGB转16色近似 Approximate RGB to 16 color
    WORD rgbToWin32Color(int r, int g, int b) const {
        // 简单的RGB到16色映射 Simple RGB to 16 color mapping
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

    // 析构函数，重置颜色 Destructor, reset color
    ~Win32Console() {
        if (initialized_) {
            resetColor();
        }
    }
};

// 非Windows平台：ANSI转义序列定义
// Non-Windows platform: ANSI escape sequence definitions
#else
namespace ansi {
    constexpr const char* ESC = "\033["; // 转义前缀 Escape prefix
    constexpr const char* RESET = "\033[0m"; // 重置 Reset
    // 基本颜色 Basic colors
    constexpr const char* BLACK = "\033[30m"; // 黑色 Black
    constexpr const char* RED = "\033[31m"; // 红色 Red
    constexpr const char* GREEN = "\033[32m"; // 绿色 Green
    constexpr const char* YELLOW = "\033[33m"; // 黄色 Yellow
    constexpr const char* BLUE = "\033[34m"; // 蓝色 Blue
    constexpr const char* MAGENTA = "\033[35m"; // 洋红 Magenta
    constexpr const char* CYAN = "\033[36m"; // 青色 Cyan
    constexpr const char* WHITE = "\033[37m"; // 白色 White
    // 亮色 Bright colors
    constexpr const char* BRIGHT_BLACK = "\033[90m"; // 亮黑 Bright black
    constexpr const char* BRIGHT_RED = "\033[91m"; // 亮红 Bright red
    constexpr const char* BRIGHT_GREEN = "\033[92m"; // 亮绿 Bright green
    constexpr const char* BRIGHT_YELLOW = "\033[93m"; // 亮黄 Bright yellow
    constexpr const char* BRIGHT_BLUE = "\033[94m"; // 亮蓝 Bright blue
    constexpr const char* BRIGHT_MAGENTA = "\033[95m"; // 亮洋红 Bright magenta
    constexpr const char* BRIGHT_CYAN = "\033[96m"; // 亮青 Bright cyan
    constexpr const char* BRIGHT_WHITE = "\033[97m"; // 亮白 Bright white
    // 文本样式 Text styles
    constexpr const char* BOLD = "\033[1m"; // 粗体 Bold
    constexpr const char* DIM = "\033[2m"; // 暗淡 Dim
    constexpr const char* ITALIC = "\033[3m"; // 斜体 Italic
    constexpr const char* UNDERLINE = "\033[4m"; // 下划线 Underline
    constexpr const char* BLINK = "\033[5m"; // 闪烁 Blink
    constexpr const char* REVERSE = "\033[7m"; // 反色 Reverse
    constexpr const char* STRIKETHROUGH = "\033[9m"; // 删除线 Strikethrough
}
#endif

// 跨平台颜色控制类，统一颜色/样式设置接口
// Cross-platform color controller, unified color/style interface
class ColorController {
public:
    // 颜色枚举 Color enum
    enum class Color {
        BLACK, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE,
        BRIGHT_BLACK, BRIGHT_RED, BRIGHT_GREEN, BRIGHT_YELLOW,
        BRIGHT_BLUE, BRIGHT_MAGENTA, BRIGHT_CYAN, BRIGHT_WHITE,
        RESET
    };

    // 设置控制台颜色 Set console color
    static void setColor(Color color) {
#ifdef _WIN32
        auto& console = Win32Console::getInstance(); // 获取Win32控制台实例 Get Win32 console instance
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
                console.resetColor(); // 重置颜色 Reset color
                return;
        }
        console.setColor(winColor); // 设置颜色 Set color
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
                ansiColor = ansi::RESET; // 重置 Reset
                break;
        }
        std::cout << ansiColor; // 输出ANSI序列 Output ANSI sequence
#endif
    }

    // 设置RGB颜色 Set RGB color
    static void setRGBColor(int r, int g, int b) {
#ifdef _WIN32
        auto& console = Win32Console::getInstance();
        WORD winColor = console.rgbToWin32Color(r, g, b); // RGB转16色 RGB to 16 color
        console.setColor(winColor);
#else
        std::cout << "\033[38;2;" << r << ";" << g << ";" << b << "m"; // ANSI 24位色 ANSI 24bit color
#endif
    }

    // 设置粗体 Set bold
    static void setBold(bool enable) {
#ifdef _WIN32
        // Windows下用高亮实现粗体 Use intensity for bold on Windows
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

// 颜色包装器类，便于流式输出颜色
// Color wrapper class, for stream color output
class ColorWrapper {
private:
    ColorController::Color color_; // 颜色枚举 Color enum
public:
    explicit ColorWrapper(ColorController::Color color) : color_(color) {} // 构造函数 Constructor
    // 友元输出重载，设置颜色 Friend output overload, set color
    friend std::ostream& operator<<(std::ostream& os, const ColorWrapper& wrapper) {
        ColorController::setColor(wrapper.color_); // 设置颜色 Set color
        return os;
    }
};

// RGB颜色包装器类，支持RGB流式输出
// RGB color wrapper class, support RGB stream output
class RGBColorWrapper {
private:
    int r_, g_, b_; // RGB分量 RGB components
public:
    RGBColorWrapper(int r, int g, int b) : r_(r), g_(g), b_(b) {} // 构造函数 Constructor
    // 友元输出重载，设置RGB颜色 Friend output overload, set RGB color
    friend std::ostream& operator<<(std::ostream& os, const RGBColorWrapper& wrapper) {
        ColorController::setRGBColor(wrapper.r_, wrapper.g_, wrapper.b_); // 设置RGB Set RGB
        return os;
    }
};

// 字体样式包装器类，支持粗体等样式
// Font style wrapper class, support bold etc.
class FontStyleWrapper {
private:
    bool enable_; // 是否启用 Enable flag
public:
    explicit FontStyleWrapper(bool enable) : enable_(enable) {} // 构造函数 Constructor
    // 友元输出重载，设置粗体 Friend output overload, set bold
    friend std::ostream& operator<<(std::ostream& os, const FontStyleWrapper& wrapper) {
        ColorController::setBold(wrapper.enable_); // 设置粗体 Set bold
        return os;
    }
};

// 延时操作类，支持流式延时
// Sleep operation class, support stream sleep
class TSleep {
private:
    int milliseconds_; // 毫秒数 Milliseconds
public:
    explicit TSleep(int ms) : milliseconds_(ms) {} // 构造函数 Constructor
    void execute() const { // 执行延时 Execute sleep
        std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds_));
    }
    // 友元输出重载，流式延时 Friend output overload, stream sleep
    friend std::ostream& operator<<(std::ostream& os, const TSleep& sleep) {
        sleep.execute();
        return os;
    }
};

// 全局颜色常量，便于直接使用 Global color constants, easy to use

// RGB颜色宏，便于流式创建RGB颜色
// RGB color macro, easy to create RGB color in stream
#define TCOLOR_RGB(r, g, b) tc::RGBColorWrapper(r, g, b)

// 自定义输出流类，支持链式输出和自定义类型
// Custom output stream class, support chain output and custom types
class TOut {
private:
    std::ostream& os_; // 底层输出流 Underlying output stream
public:
    explicit TOut(std::ostream& os = std::cout) : os_(os) {
#ifdef _WIN32
        Win32Console::getInstance(); // 确保Windows控制台初始化 Ensure Windows console initialized
#endif
    }
    // 通用输出操作符 Generic output operator
    template<typename T>
    TOut& operator<<(T&& value) {
        os_ << std::forward<T>(value);
        return *this;
    }
    // 特化处理TSleep Specialize for TSleep
    TOut& operator<<(const TSleep& sleep) {
        sleep.execute();
        return *this;
    }
    // 特化处理颜色包装器 Specialize for ColorWrapper
    TOut& operator<<(const ColorWrapper& color) {
        os_ << color;
        return *this;
    }
    // 特化处理RGB颜色包装器 Specialize for RGBColorWrapper
    TOut& operator<<(const RGBColorWrapper& color) {
        os_ << color;
        return *this;
    }
    // 特化处理字体样式包装器 Specialize for FontStyleWrapper
    TOut& operator<<(const FontStyleWrapper& style) {
        os_ << style;
        return *this;
    }
    // 支持标准流操作符 Support standard stream manipulators
    TOut& operator<<(std::ostream& (*manip)(std::ostream&)) {
        os_ << manip;
        return *this;
    }
    // 获取底层流 Get underlying stream
    std::ostream& stream() { return os_; }
};

// 全局 tout 对象，类似 std::cout
// Global tout object, like std::cout
static TOut tout(std::cout);

// 延时函数，返回TSleep对象
// Sleep function, return TSleep object
inline TSleep tsleep(int milliseconds) {
    return TSleep(milliseconds);
}

// 延时流操作符类，支持 tc::tsleep_stream << 3000
// Sleep stream operator class, support tc::tsleep_stream << 3000
class TSleepStream {
public:
    void operator<<(int milliseconds) const {
        std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
    }
};

// 全局延时流对象 Global sleep stream object
static TSleepStream tsleep_stream;

// 终端控制函数 Terminal control functions
namespace terminal {
    // 清屏函数 Clear screen
    inline void clear() {
#ifdef _WIN32
        Win32Console::getInstance().clearScreen();
#else
        std::cout << "\033[2J\033[H";
#endif
    }
    // 移动光标 Move cursor
    inline void moveCursor(int x, int y) {
#ifdef _WIN32
        Win32Console::getInstance().moveCursor(x, y);
#else
        std::cout << "\033[" << y << ";" << x << "H";
#endif
    }
    // 获取终端尺寸 Get terminal size
    inline std::pair<int, int> getSize() {
#ifdef _WIN32
        return Win32Console::getInstance().getConsoleSize();
#else
        struct winsize w;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        return {w.ws_col, w.ws_row};
#endif
    }
}

// 便利的颜色函数，返回带颜色的字符串
// Convenient color functions, return colored string
inline std::string colorize(const std::string& text, ColorController::Color color) {
    std::ostringstream oss;
    oss << ColorWrapper(color) << text << ColorWrapper(ColorController::Color::RESET);
    return oss.str();
}
inline std::string red(const std::string& text) {
    return colorize(text, ColorController::Color::RED);
}
inline std::string green(const std::string& text) {
    return colorize(text, ColorController::Color::GREEN);
}
inline std::string blue(const std::string& text) {
    return colorize(text, ColorController::Color::BLUE);
}
inline std::string yellow(const std::string& text) {
    return colorize(text, ColorController::Color::YELLOW);
}

// ========== 进度条 ========== //
class ProgressBar {
    int width_;
    std::string done_, todo_;
    std::string color_;
public:
    ProgressBar(int width, std::string done = "#", std::string todo = "-", std::string color = TCOLOR_GREEN)
        : width_(width), done_(std::move(done)), todo_(std::move(todo)), color_(std::move(color)) {}
    void show(double progress, const std::string& msg = "Loading...") {
        int pos = static_cast<int>(width_ * progress);
        std::cout << "\r" << color_ << "[";
        for (int i = 0; i < width_; ++i) std::cout << (i < pos ? done_ : todo_);
        std::cout << "] " << int(progress * 100) << "% " << msg << TCOLOR_RESET << std::flush;
    }
    void finish(std::string content = "Finished") {
        show(1.0, content);
        std::cout << std::endl;
    }
};


} // namespace tc

// ===== 系统相关API及全局宏 =====
#include <ctime>
#include <cstdlib>
#include <cstring>
#ifdef _WIN32
    #include <windows.h>
#endif

// --- getSystemTime ---
#define SYS_YEAR   1
#define SYS_MONTH  2
#define SYS_DAY    3
#define SYS_HOUR   4
#define SYS_MINUTE 5
#define SYS_SECOND 6
#define SYS_TIMESTAMP 0
namespace tc {
    inline int getSystemTime(int type = SYS_TIMESTAMP) {
        std::time_t t = std::time(nullptr);
        std::tm* tm_ptr;
#ifdef _WIN32
        std::tm tm_buf;
        localtime_s(&tm_buf, &t);
        tm_ptr = &tm_buf;
#else
        tm_ptr = std::localtime(&t);
#endif
        switch(type) {
            case SYS_YEAR:   return tm_ptr->tm_year + 1900;
            case SYS_MONTH:  return tm_ptr->tm_mon + 1;
            case SYS_DAY:    return tm_ptr->tm_mday;
            case SYS_HOUR:   return tm_ptr->tm_hour;
            case SYS_MINUTE: return tm_ptr->tm_min;
            case SYS_SECOND: return tm_ptr->tm_sec;
            default:         return static_cast<int>(t);
        }
    }
}

// --- systemConsole ---
namespace tc {
    inline int systemConsole(const char* cmd) {
        return std::system(cmd);
    }
    inline int systemConsole(const std::string& cmd) {
        return std::system(cmd.c_str());
    }
}

// --- 系统环境宏定义 ---
#define OS_UNKNOWN      0
#define OS_WINDOWS      100
#define OS_WINDOWSNT3   103
#define OS_WINDOWSNT4   104
#define OS_WINDOWSNT5   105
#define OS_WINDOWSNT6   106
#define OS_WINDOWSNT10  110
#define OS_WINDOWSNT11  111
#define OS_WIN95        195
#define OS_WIN98        198
#define OS_WINME        199
#define OS_WINCE        120
#define OS_LINUX        200
#define OS_ANDROID      210
#define OS_MACOS        300
#define OS_IOS          310
#define OS_BSD          400
#define OS_UNIX         500
#define OS_DOS          600
#define OS_BEOS         700
#define OS_HAIKU        701
#define OS_AIX          800
#define OS_SOLARIS      810
#define OS_MINIX        820
#define OS_QNX          830
#define OS_VMS          840
#define OS_AMIGAOS      850
#define OS_MORPHOS      851
#define OS_FREEMINT     852
#define OS_HPUX         860
#define OS_IRIX         861
#define OS_SCO          862
#define OS_OPENVMS      863
#define OS_RISCOS       870
#define OS_OS2          900
#define OS_NEXTSTEP     910

// --- systemCheck ---
#include <string>
namespace tc {
    inline int systemCheck() {
#if defined(_WIN32) || defined(_WIN64)
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
                    if (rovi.dwMajorVersion > 10) return OS_WINDOWSNT11; // 未来主版本
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
            return OS_WINDOWS;
        }
        return OS_WINDOWS;
#elif defined(__ANDROID__)
        return OS_ANDROID;
#elif defined(__HAIKU__)
        return OS_HAIKU;
#elif defined(_AIX) || defined(__AIX__)
        return OS_AIX;
#elif defined(__sun) && defined(__SVR4)
        return OS_SOLARIS;
#elif defined(__minix)
        return OS_MINIX;
#elif defined(__QNX__)
        return OS_QNX;
#elif defined(__VMS) || defined(__VMS__)
        return OS_VMS;
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
#elif defined(__riscos)
        return OS_RISCOS;
#elif defined(__APPLE__)
    #include <TargetConditionals.h>
    #if TARGET_OS_IPHONE
        return OS_IOS;
    #else
        return OS_MACOS;
    #endif
#elif defined(__linux__)
        return OS_LINUX;
#elif defined(__unix__)
        return OS_UNIX;
#elif defined(__FreeBSD__)
        return OS_BSD;
#elif defined(__MSDOS__) || defined(_MSDOS) || defined(__DOS__)
        return OS_DOS;
#elif defined(__BEOS__)
        return OS_BEOS;
#elif defined(__OS2__)
        return OS_OS2;
#elif defined(__NeXT__)
        return OS_NEXTSTEP;
#else
        return OS_UNKNOWN;
#endif
    }
}

#endif // TC_HPP