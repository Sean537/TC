/*
tc.hpp

Copyright (C) 2024-2025 RabbitMax and Sean537. All rights reserved.
*/

#ifndef TC_HPP
#define TC_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <thread>
#include <chrono>
#include <memory>
#include <functional>
#include <type_traits>
#include <stack>

#ifdef _WIN32
    #include <windows.h>
    #include <io.h>
    #include <fcntl.h>
    #ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
        #define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
    #endif
#else
    #include <unistd.h>
    #include <sys/ioctl.h>
#endif

namespace tc {

#ifdef _WIN32
// Windows 颜色映射
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

// Windows 控制台管理器
class Win32Console {
private:
    HANDLE hConsole_;
    CONSOLE_SCREEN_BUFFER_INFO originalInfo_;
    std::stack<WORD> colorStack_;
    bool initialized_ = false;

    Win32Console() {
        hConsole_ = GetStdHandle(STD_OUTPUT_HANDLE);
        if (hConsole_ != INVALID_HANDLE_VALUE) {
            GetConsoleScreenBufferInfo(hConsole_, &originalInfo_);
            initialized_ = true;
            
            // 设置 UTF-8 支持
            SetConsoleOutputCP(CP_UTF8);
            SetConsoleCP(CP_UTF8);
            
            // 尝试启用 ANSI 处理（用于某些高级功能）
            DWORD dwMode = 0;
            if (GetConsoleMode(hConsole_, &dwMode)) {
                SetConsoleMode(hConsole_, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
            }
        }
    }

public:
    static Win32Console& getInstance() {
        static Win32Console instance;
        return instance;
    }

    bool isInitialized() const { return initialized_; }

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
            
            FillConsoleOutputCharacter(hConsole_, ' ', 
                info.dwSize.X * info.dwSize.Y, topLeft, &written);
            FillConsoleOutputAttribute(hConsole_, info.wAttributes,
                info.dwSize.X * info.dwSize.Y, topLeft, &written);
            
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
        return {80, 25}; // 默认值
    }

    // RGB 颜色近似（转换为最接近的 16 色）
    WORD rgbToWin32Color(int r, int g, int b) const {
        // 简单的 RGB 到 16 色映射
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

#else
// ANSI 转义序列（非 Windows 系统）
namespace ansi {
    constexpr const char* ESC = "\033[";
    constexpr const char* RESET = "\033[0m";
    
    // 基本颜色
    constexpr const char* BLACK = "\033[30m";
    constexpr const char* RED = "\033[31m";
    constexpr const char* GREEN = "\033[32m";
    constexpr const char* YELLOW = "\033[33m";
    constexpr const char* BLUE = "\033[34m";
    constexpr const char* MAGENTA = "\033[35m";
    constexpr const char* CYAN = "\033[36m";
    constexpr const char* WHITE = "\033[37m";
    
    // 亮色
    constexpr const char* BRIGHT_BLACK = "\033[90m";
    constexpr const char* BRIGHT_RED = "\033[91m";
    constexpr const char* BRIGHT_GREEN = "\033[92m";
    constexpr const char* BRIGHT_YELLOW = "\033[93m";
    constexpr const char* BRIGHT_BLUE = "\033[94m";
    constexpr const char* BRIGHT_MAGENTA = "\033[95m";
    constexpr const char* BRIGHT_CYAN = "\033[96m";
    constexpr const char* BRIGHT_WHITE = "\033[97m";
    
    // 文本样式
    constexpr const char* BOLD = "\033[1m";
    constexpr const char* DIM = "\033[2m";
    constexpr const char* ITALIC = "\033[3m";
    constexpr const char* UNDERLINE = "\033[4m";
    constexpr const char* BLINK = "\033[5m";
    constexpr const char* REVERSE = "\033[7m";
    constexpr const char* STRIKETHROUGH = "\033[9m";
}
#endif

// 跨平台颜色控制类
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

    static void setRGBColor(int r, int g, int b) {
#ifdef _WIN32
        auto& console = Win32Console::getInstance();
        WORD winColor = console.rgbToWin32Color(r, g, b);
        console.setColor(winColor);
#else
        std::cout << "\033[38;2;" << r << ";" << g << ";" << b << "m";
#endif
    }

    static void setBold(bool enable) {
#ifdef _WIN32
        // Windows 控制台的"粗体"通过亮度实现
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

// 颜色包装器类
class ColorWrapper {
private:
    ColorController::Color color_;
    
public:
    explicit ColorWrapper(ColorController::Color color) : color_(color) {}
    
    friend std::ostream& operator<<(std::ostream& os, const ColorWrapper& wrapper) {
        ColorController::setColor(wrapper.color_);
        return os;
    }
};

// RGB 颜色包装器类
class RGBColorWrapper {
private:
    int r_, g_, b_;
    
public:
    RGBColorWrapper(int r, int g, int b) : r_(r), g_(g), b_(b) {}
    
    friend std::ostream& operator<<(std::ostream& os, const RGBColorWrapper& wrapper) {
        ColorController::setRGBColor(wrapper.r_, wrapper.g_, wrapper.b_);
        return os;
    }
};

// 字体样式包装器类
class FontStyleWrapper {
private:
    bool enable_;
    
public:
    explicit FontStyleWrapper(bool enable) : enable_(enable) {}
    
    friend std::ostream& operator<<(std::ostream& os, const FontStyleWrapper& wrapper) {
        ColorController::setBold(wrapper.enable_);
        return os;
    }
};

// 延时操作类
class TSleep {
private:
    int milliseconds_;

public:
    explicit TSleep(int ms) : milliseconds_(ms) {}

    void execute() const {
        std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds_));
    }

    friend std::ostream& operator<<(std::ostream& os, const TSleep& sleep) {
        sleep.execute();
        return os;
    }
};

// 全局颜色常量
static const ColorWrapper TCOLOR_BLACK(ColorController::Color::BLACK);
static const ColorWrapper TCOLOR_RED(ColorController::Color::RED);
static const ColorWrapper TCOLOR_GREEN(ColorController::Color::GREEN);
static const ColorWrapper TCOLOR_YELLOW(ColorController::Color::YELLOW);
static const ColorWrapper TCOLOR_BLUE(ColorController::Color::BLUE);
static const ColorWrapper TCOLOR_MAGENTA(ColorController::Color::MAGENTA);
static const ColorWrapper TCOLOR_CYAN(ColorController::Color::CYAN);
static const ColorWrapper TCOLOR_WHITE(ColorController::Color::WHITE);
static const ColorWrapper TCOLOR_RESET(ColorController::Color::RESET);

// 字体样式常量
static const FontStyleWrapper TFONT_THICK(true);
static const FontStyleWrapper TFONT_BOLD(true);
static const FontStyleWrapper TFONT_RESET(false);

// RGB 颜色宏
#define TCOLOR_RGB(r, g, b) tc::RGBColorWrapper(r, g, b)

// 自定义输出流类
class TOut {
private:
    std::ostream& os_;

public:
    explicit TOut(std::ostream& os = std::cout) : os_(os) {
#ifdef _WIN32
        // 确保 Windows 控制台已初始化
        Win32Console::getInstance();
#endif
    }

    // 通用输出操作符
    template<typename T>
    TOut& operator<<(T&& value) {
        os_ << std::forward<T>(value);
        return *this;
    }

    // 特化处理 TSleep
    TOut& operator<<(const TSleep& sleep) {
        sleep.execute();
        return *this;
    }

    // 特化处理颜色包装器
    TOut& operator<<(const ColorWrapper& color) {
        color << os_;
        return *this;
    }

    TOut& operator<<(const RGBColorWrapper& color) {
        color << os_;
        return *this;
    }

    TOut& operator<<(const FontStyleWrapper& style) {
        style << os_;
        return *this;
    }

    // 支持标准流操作符
    TOut& operator<<(std::ostream& (*manip)(std::ostream&)) {
        os_ << manip;
        return *this;
    }

    // 获取底层流
    std::ostream& stream() { return os_; }
};

// 全局 tout 对象
static TOut tout(std::cout);

// 延时函数
inline TSleep tsleep(int milliseconds) {
    return TSleep(milliseconds);
}

// 延时流操作符 - 支持 tc::tsleep << 3000 语法
class TSleepStream {
public:
    void operator<<(int milliseconds) const {
        std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
    }
};

static TSleepStream tsleep_stream;

// 终端控制函数
namespace terminal {
    inline void clear() {
#ifdef _WIN32
        Win32Console::getInstance().clearScreen();
#else
        std::cout << "\033[2J\033[H";
#endif
    }

    inline void moveCursor(int x, int y) {
#ifdef _WIN32
        Win32Console::getInstance().moveCursor(x, y);
#else
        std::cout << "\033[" << y << ";" << x << "H";
#endif
    }

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

// 便利的颜色函数
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

} // namespace tc

// 为了支持示例中的语法，我们需要重新定义 tsleep
#define tsleep tc::tsleep_stream

#endif // TC_HPP
