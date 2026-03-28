/*
 * tc_stream.hpp - TC库流式输出和延时模块
 * TC Stream Output and Delay Module
 * 
 * 这个文件包含了TC库中的流式输出和延时功能，包括：
 * - 增强的输出流类（TOut）
 * - 延时操作类（TSleep）
 * - 流式延时操作类（TSleepStream）
 * - 支持颜色和样式的流式输出
 * 
 * 版本 Version: 1.1.3
 * 作者 Author: 537 Studio
 * 许可 License: MIT
 */

#ifndef TC_STREAM_HPP
#define TC_STREAM_HPP

// 标准库包含 | Standard library includes
#include <iostream>  // 输入输出流 | Input/output streams
#include <thread>    // 线程库 | Thread library
#include <chrono>    // 时间库 | Time library
#include <string>    // 字符串 | String
#include <regex>     // 正则表达式 | Regular expressions
#include "tc_colors.hpp" // TC颜色模块 | TC color module

namespace tc {

/**
 * 延时操作类
 * Sleep operation class
 */
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

/**
 * 自定义输出流类
 * Custom output stream class
 */
class TOut {
private:
    std::ostream& os_;
    
public:
    explicit TOut(std::ostream& os = std::cout) : os_(os) {
#ifdef _WIN32
        Win32Console::getInstance();
#endif
    }
    
    template<typename T>
    TOut& operator<<(T&& value) {
        if constexpr (std::is_convertible_v<T, std::string> || std::is_same_v<std::decay_t<T>, std::string>) {
            std::ostringstream oss;
            oss << std::forward<T>(value);
            std::string s = oss.str();
            
#if defined(_WIN32)
            auto& console = Win32Console::getInstance();
            if (!console.isVTEnabled()) {
                // 不支持 ANSI 的环境：解析并处理序列
                size_t pos = 0;
                std::regex ansi_regex("\x1B\\[[0-9;]*[mK]"); // 匹配颜色和清行序列
                std::smatch match;
                
                std::string current = s;
                while (std::regex_search(current, match, ansi_regex)) {
                    // 输出序列前的文本
                    os_ << match.prefix().str();
                    
#if defined(TC_ENABLE_WIN32_CONSOLE_API)
                    // 只有在开启 API 模式时才尝试解析并映射
                    processANSISequence(match.str());
#endif
                    // 继续搜索剩余部分
                    current = match.suffix().str();
                }
                os_ << current;
                return *this;
            }
#endif
            os_ << s;
        } else {
            os_ << std::forward<T>(value);
        }
        return *this;
    }
    
    void processANSISequence(const std::string& s) {
        // 只有开启了 TC_ENABLE_WIN32_CONSOLE_API 才会通过 operator<< 调用此函数
        if (s == "\033[0m") { tc::ColorController::setColor(tc::ColorController::Color::RESET); return; }
        if (s == "\033[1m") { tc::ColorController::setBold(true); return; }
        if (s == "\033[22m") { tc::ColorController::setBold(false); return; }
        
        // 前景色
        if (s == "\033[30m") { tc::ColorController::setColor(tc::ColorController::Color::BLACK); return; }
        if (s == "\033[31m") { tc::ColorController::setColor(tc::ColorController::Color::RED); return; }
        if (s == "\033[32m") { tc::ColorController::setColor(tc::ColorController::Color::GREEN); return; }
        if (s == "\033[33m") { tc::ColorController::setColor(tc::ColorController::Color::YELLOW); return; }
        if (s == "\033[34m") { tc::ColorController::setColor(tc::ColorController::Color::BLUE); return; }
        if (s == "\033[35m") { tc::ColorController::setColor(tc::ColorController::Color::MAGENTA); return; }
        if (s == "\033[36m") { tc::ColorController::setColor(tc::ColorController::Color::CYAN); return; }
        if (s == "\033[37m") { tc::ColorController::setColor(tc::ColorController::Color::WHITE); return; }
        if (s == "\033[90m") { tc::ColorController::setColor(tc::ColorController::Color::BRIGHT_BLACK); return; }
        if (s == "\033[91m") { tc::ColorController::setColor(tc::ColorController::Color::BRIGHT_RED); return; }
        if (s == "\033[92m") { tc::ColorController::setColor(tc::ColorController::Color::BRIGHT_GREEN); return; }
        if (s == "\033[93m") { tc::ColorController::setColor(tc::ColorController::Color::BRIGHT_YELLOW); return; }
        if (s == "\033[94m") { tc::ColorController::setColor(tc::ColorController::Color::BRIGHT_BLUE); return; }
        if (s == "\033[95m") { tc::ColorController::setColor(tc::ColorController::Color::BRIGHT_MAGENTA); return; }
        if (s == "\033[96m") { tc::ColorController::setColor(tc::ColorController::Color::BRIGHT_CYAN); return; }
        if (s == "\033[97m") { tc::ColorController::setColor(tc::ColorController::Color::BRIGHT_WHITE); return; }
        
        // 背景色
        if (s == "\033[40m") { tc::ColorController::setBackground(tc::ColorController::Color::BLACK); return; }
        if (s == "\033[41m") { tc::ColorController::setBackground(tc::ColorController::Color::RED); return; }
        if (s == "\033[42m") { tc::ColorController::setBackground(tc::ColorController::Color::GREEN); return; }
        if (s == "\033[43m") { tc::ColorController::setBackground(tc::ColorController::Color::YELLOW); return; }
        if (s == "\033[44m") { tc::ColorController::setBackground(tc::ColorController::Color::BLUE); return; }
        if (s == "\033[45m") { tc::ColorController::setBackground(tc::ColorController::Color::MAGENTA); return; }
        if (s == "\033[46m") { tc::ColorController::setBackground(tc::ColorController::Color::CYAN); return; }
        if (s == "\033[47m") { tc::ColorController::setBackground(tc::ColorController::Color::WHITE); return; }
        if (s == "\033[100m") { tc::ColorController::setBackground(tc::ColorController::Color::BRIGHT_BLACK); return; }
        if (s == "\033[101m") { tc::ColorController::setBackground(tc::ColorController::Color::BRIGHT_RED); return; }
        if (s == "\033[102m") { tc::ColorController::setBackground(tc::ColorController::Color::BRIGHT_GREEN); return; }
        if (s == "\033[103m") { tc::ColorController::setBackground(tc::ColorController::Color::BRIGHT_YELLOW); return; }
        if (s == "\033[104m") { tc::ColorController::setBackground(tc::ColorController::Color::BRIGHT_BLUE); return; }
        if (s == "\033[105m") { tc::ColorController::setBackground(tc::ColorController::Color::BRIGHT_MAGENTA); return; }
        if (s == "\033[106m") { tc::ColorController::setBackground(tc::ColorController::Color::BRIGHT_CYAN); return; }
        if (s == "\033[107m") { tc::ColorController::setBackground(tc::ColorController::Color::BRIGHT_WHITE); return; }
    }
    
    TOut& operator<<(const TSleep& sleep) {
        sleep.execute();
        return *this;
    }
    
    TOut& operator<<(const ColorWrapper& color) {
        os_ << color;
        return *this;
    }
    
    TOut& operator<<(const RGBColorWrapper& color) {
        os_ << color;
        return *this;
    }
    
    TOut& operator<<(const FontStyleWrapper& style) {
        os_ << style;
        return *this;
    }
    
    TOut& operator<<(std::ostream& (*manip)(std::ostream&)) {
        os_ << manip;
        return *this;
    }
    
    std::ostream& stream() { return os_; }
};

static TOut tout(std::cout);

inline TSleep tsleep(int milliseconds) {
    return TSleep(milliseconds);
}

class TSleepStream {
public:
    void operator<<(int milliseconds) const {
        std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
    }
};

static TSleepStream tsleep_stream;

} // namespace tc

#endif // TC_STREAM_HPP
