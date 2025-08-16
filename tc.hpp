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
    inline int systemConsoleW(const wchar_t* cmd) {
        #ifdef _WIN32
            return _wsystem(cmd);
        #else
            // 在非Windows平台上，需要将宽字符转换为UTF-8
            std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
            std::string utf8_cmd = converter.to_bytes(cmd);
            return system(utf8_cmd.c_str());
        #endif
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
// --- Linux发行版 ---
#define OS_LINUX        200  // 通用Linux
#define OS_UBUNTU       201  // Ubuntu
#define OS_DEBIAN       202  // Debian
#define OS_FEDORA       203  // Fedora
#define OS_CENTOS       204  // CentOS
#define OS_REDHAT       205  // Red Hat Enterprise Linux
#define OS_SUSE         206  // SUSE/openSUSE
#define OS_ARCH         207  // Arch Linux
#define OS_GENTOO       208  // Gentoo
#define OS_SLACKWARE    209  // Slackware
#define OS_ANDROID      210  // Android (基于Linux)
#define OS_KALI         211  // Kali Linux
#define OS_MINT         212  // Linux Mint
#define OS_MANJARO      213  // Manjaro
#define OS_ALPINE       214  // Alpine Linux
#define OS_RASPBIAN     215  // Raspbian
#define OS_DEEPIN       216  // Deepin
#define OS_ELEMENTARY   217  // Elementary OS
#define OS_ZORIN        218  // Zorin OS
#define OS_POPOS        219  // Pop!_OS
#define OS_CHROMEOS     220  // Chrome OS/Chromium OS

// --- Apple操作系统 ---
// 现代macOS和Mac OS X版本
#define OS_MACOS        300  // 通用macOS标识
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

// 经典Macintosh系统
#define OS_MACOS9       330  // Mac OS 9 (1999)
#define OS_MACOS8       331  // Mac OS 8 (1997)
#define OS_MACOS7       332  // System 7 (1991)
#define OS_MACOS6       333  // System 6 (1988)
#define OS_MACOS5       334  // System 5 (1987)
#define OS_MACOS4       335  // System 4 (1987)
#define OS_MACOS3       336  // System 3 (1986)
#define OS_MACOS2       337  // System 2 (1985)
#define OS_MACOS1       338  // System 1 (1984)

// 其他Apple操作系统
#define OS_IOS          350  // iOS
#define OS_IPADOS       351  // iPadOS
#define OS_WATCHOS      352  // watchOS
#define OS_TVOS         353  // tvOS
#define OS_VISIONOS     354  // visionOS (Apple Vision Pro)
#define OS_BRIDGEOS     355  // bridgeOS (Apple T2芯片)
#define OS_AUDIOOS      356  // audioOS (HomePod)
#define OS_BSD          400
#define OS_DRAGONFLY    401  // DragonFly BSD
#define OS_NETBSD       402  // NetBSD
#define OS_OPENBSD      403  // OpenBSD
#define OS_FREEBSD      404  // FreeBSD (已有BSD，这是更具体的)
#define OS_UNIX         500
#define OS_HURD         501  // GNU Hurd
#define OS_XENIX        502  // Xenix
#define OS_DOS          600
#define OS_PLAN9        601  // Plan 9
#define OS_INFERNO      602  // Inferno
#define OS_BEOS         700
#define OS_HAIKU        701
#define OS_SYLLABLE     702  // Syllable
#define OS_MENUETOS     703  // MenuetOS
#define OS_REACTOS      704  // ReactOS
#define OS_KOLIBRIOS    705  // KolibriOS
#define OS_AIX          800
#define OS_SOLARIS      810
#define OS_MINIX        820
#define OS_QNX          830
#define OS_VMS          840
#define OS_ZOS          841  // z/OS
#define OS_OS400        842  // OS/400
#define OS_TPF          843  // TPF
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
#define OS_NUTTX        920  // NuttX
#define OS_ZEPHYR       921  // Zephyr
#define OS_CONTIKI      922  // Contiki
#define OS_RIOT         923  // RIOT
#define OS_FUCHSIA      950  // Google Fuchsia
#define OS_REDOX        951  // Redox OS
#define OS_HARMONY      952  // Harmony OS
// --- 嵌入式/实时操作系统 ---
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

// --- systemCheck ---
#include <string>
#include <algorithm>

namespace tc {
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

    // 获取操作系统名称
    inline const char* getOSName(int osCode) {
        switch(osCode) {
            case OS_UNKNOWN: return "Unknown OS";
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
            
            // Linux发行版
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
            
            // macOS和Mac OS X版本
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
            
            // 经典Macintosh系统
            case OS_MACOS9: return "Mac OS 9";
            case OS_MACOS8: return "Mac OS 8";
            case OS_MACOS7: return "System 7";
            case OS_MACOS6: return "System 6";
            case OS_MACOS5: return "System 5";
            case OS_MACOS4: return "System 4";
            case OS_MACOS3: return "System 3";
            case OS_MACOS2: return "System 2";
            case OS_MACOS1: return "System 1";
            
            // 其他Apple操作系统
            case OS_IOS: return "iOS";
            case OS_IPADOS: return "iPadOS";
            case OS_WATCHOS: return "watchOS";
            case OS_TVOS: return "tvOS";
            case OS_VISIONOS: return "visionOS";
            case OS_BRIDGEOS: return "bridgeOS";
            case OS_AUDIOOS: return "audioOS";
            
            // BSD系列
            case OS_BSD: return "BSD";
            case OS_DRAGONFLY: return "DragonFly BSD";
            case OS_NETBSD: return "NetBSD";
            case OS_OPENBSD: return "OpenBSD";
            case OS_FREEBSD: return "FreeBSD";
            
            // 其他操作系统
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
            
            // 嵌入式/实时操作系统
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
            
            // 新兴操作系统
            case OS_FUCHSIA: return "Google Fuchsia";
            case OS_REDOX: return "Redox OS";
            case OS_HARMONY: return "Harmony OS";
        
            default: return "Unknown OS";
        }
    }
} // namespace tc

#endif // TC_HPP