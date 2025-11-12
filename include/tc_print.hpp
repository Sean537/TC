/*
 * tc_print.hpp - TC库打印功能模块
 * TC Print Functionality Module
 * 
 * 这个文件包含了TC库中所有与打印输出相关的功能，包括：
 * - Python风格的print和println函数
 * - 支持可变参数的打印函数
 * - 链式调用的PrintProxy类
 * - 多参数一次性打印支持
 * 
 * This file contains all print output related functionality in the TC library, including:
 * - Python-style print and println functions
 * - Variadic parameter print functions
 * - Chainable PrintProxy class
 * - Multi-parameter one-time print support
 * 
 * 版本 Version: 1.1.2 Beta
 * 作者 Author: 537 Studio
 * 许可 License: MIT
 */

#ifndef TC_PRINT_HPP
#define TC_PRINT_HPP

// 标准库包含 | Standard library includes
#include <iostream>       // 输入输出流 | Input/output streams
#include <initializer_list> // 初始化列表 | Initializer list
#ifdef _WIN32
#include <string>
#include <regex>
#include "tc_colors.hpp"
#endif

namespace tc {

/**
 * PrintProxy类 - 提供链式调用风格的打印功能
 * PrintProxy class - Provides chainable printing functionality
 * 
 * 这个类允许类似Python的链式打印操作，如：print("Hello").print(" ").println("World")
 * 支持任意数量和类型的参数，使用完美转发来保持参数的值类别。
 * 
 * This class allows Python-like chaining of print operations, e.g.: print("Hello").print(" ").println("World")
 * Supports any number and type of arguments, using perfect forwarding to preserve argument value categories.
 */
class PrintProxy {
public:
    /**
     * 无参数打印，返回自身引用以支持链式调用
     * No-argument print, returns self-reference for chaining
     * 
     * @return 对象自身引用 | Self reference
     */
    const PrintProxy& print() const { return *this; }
    
    /**
     * 可变参数模板打印，支持任意数量和类型的参数
     * Variadic template print, supports any number and type of arguments
     * 
     * 使用初始化列表技巧展开参数包，通过完美转发保持参数的原始类型。
     * Uses initializer list trick to expand parameter pack, preserving original types through perfect forwarding.
     * 
     * @param args 要打印的参数 | Arguments to print
     * @return 对象自身引用，支持链式调用 | Self reference for chaining
     */
    template<typename... Args>
    const PrintProxy& print(Args&&... args) const {
#ifndef _WIN32
        // 使用 C++17 折叠表达式替代 initializer_list 展开，减少运行时开销
        (std::cout << ... << std::forward<Args>(args));
#else
        auto process = [](const auto& arg) {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, tc::ColorWrapper> || std::is_same_v<T, tc::FontStyleWrapper>) {
                std::cout << arg;
            } else if constexpr (std::is_same_v<T, const char*> || std::is_same_v<T, char*>) {
                std::string s = arg ? std::string(arg) : std::string();
                // 映射常见 ANSI 到 Win32 行为
#if defined(_WIN32) && defined(TC_ENABLE_WIN32_CONSOLE_API)
                if (s == "\033[0m") { ColorController::setColor(ColorController::Color::RESET); return; }
                if (s == "\033[1m") { ColorController::setBold(true); return; }
                if (s == "\033[22m") { ColorController::setBold(false); return; }
                // 字体样式处理 - Windows控制台API不支持斜体、下划线、反色、删除线等样式，直接忽略
                if (s == "\033[3m") { return; }  // 斜体 - 不支持，忽略
                if (s == "\033[23m") { return; }   // 关闭斜体 - 不支持，忽略
                if (s == "\033[4m") { return; }   // 下划线 - 不支持，忽略
                if (s == "\033[24m") { return; }   // 关闭下划线 - 不支持，忽略
                if (s == "\033[7m") { return; }    // 反色 - 不支持，忽略
                if (s == "\033[27m") { return; }  // 关闭反色 - 不支持，忽略
                if (s == "\033[9m") { return; }   // 删除线 - 不支持，忽略
                if (s == "\033[29m") { return; }   // 关闭删除线 - 不支持，忽略
                // 前景色常量
                if (s == "\033[30m") { ColorController::setColor(ColorController::Color::BLACK); return; }
                if (s == "\033[31m") { ColorController::setColor(ColorController::Color::RED); return; }
                if (s == "\033[32m") { ColorController::setColor(ColorController::Color::GREEN); return; }
                if (s == "\033[33m") { ColorController::setColor(ColorController::Color::YELLOW); return; }
                if (s == "\033[34m") { ColorController::setColor(ColorController::Color::BLUE); return; }
                if (s == "\033[35m") { ColorController::setColor(ColorController::Color::MAGENTA); return; }
                if (s == "\033[36m") { ColorController::setColor(ColorController::Color::CYAN); return; }
                if (s == "\033[37m") { ColorController::setColor(ColorController::Color::WHITE); return; }
                if (s == "\033[90m") { ColorController::setColor(ColorController::Color::BRIGHT_BLACK); return; }
                if (s == "\033[91m") { ColorController::setColor(ColorController::Color::BRIGHT_RED); return; }
                if (s == "\033[92m") { ColorController::setColor(ColorController::Color::BRIGHT_GREEN); return; }
                if (s == "\033[93m") { ColorController::setColor(ColorController::Color::BRIGHT_YELLOW); return; }
                if (s == "\033[94m") { ColorController::setColor(ColorController::Color::BRIGHT_BLUE); return; }
                if (s == "\033[95m") { ColorController::setColor(ColorController::Color::BRIGHT_MAGENTA); return; }
                if (s == "\033[96m") { ColorController::setColor(ColorController::Color::BRIGHT_CYAN); return; }
                if (s == "\033[97m") { ColorController::setColor(ColorController::Color::BRIGHT_WHITE); return; }
                // 背景色常量
                if (s == "\033[40m") { ColorController::setBackground(ColorController::Color::BLACK); return; }
                if (s == "\033[41m") { ColorController::setBackground(ColorController::Color::RED); return; }
                if (s == "\033[42m") { ColorController::setBackground(ColorController::Color::GREEN); return; }
                if (s == "\033[43m") { ColorController::setBackground(ColorController::Color::YELLOW); return; }
                if (s == "\033[44m") { ColorController::setBackground(ColorController::Color::BLUE); return; }
                if (s == "\033[45m") { ColorController::setBackground(ColorController::Color::MAGENTA); return; }
                if (s == "\033[46m") { ColorController::setBackground(ColorController::Color::CYAN); return; }
                if (s == "\033[47m") { ColorController::setBackground(ColorController::Color::WHITE); return; }
#else
                if (s == "\033[0m") { std::cout << s; return; }
                if (s == "\033[1m") { std::cout << s; return; }
                if (s == "\033[22m") { std::cout << s; return; }
                // 字体样式处理 - 直接输出ANSI序列
                if (s == "\033[3m") { std::cout << s; return; }  // 斜体
                if (s == "\033[23m") { std::cout << s; return; }   // 关闭斜体
                if (s == "\033[4m") { std::cout << s; return; }   // 下划线
                if (s == "\033[24m") { std::cout << s; return; }   // 关闭下划线
                if (s == "\033[7m") { std::cout << s; return; }    // 反色
                if (s == "\033[27m") { std::cout << s; return; }  // 关闭反色
                if (s == "\033[9m") { std::cout << s; return; }   // 删除线
                if (s == "\033[29m") { std::cout << s; return; }   // 关闭删除线
                // 前景色常量 - 直接输出ANSI序列
                if (s == "\033[30m") { std::cout << s; return; }
                if (s == "\033[31m") { std::cout << s; return; }
                if (s == "\033[32m") { std::cout << s; return; }
                if (s == "\033[33m") { std::cout << s; return; }
                if (s == "\033[34m") { std::cout << s; return; }
                if (s == "\033[35m") { std::cout << s; return; }
                if (s == "\033[36m") { std::cout << s; return; }
                if (s == "\033[37m") { std::cout << s; return; }
                if (s == "\033[90m") { std::cout << s; return; }
                if (s == "\033[91m") { std::cout << s; return; }
                if (s == "\033[92m") { std::cout << s; return; }
                if (s == "\033[93m") { std::cout << s; return; }
                if (s == "\033[94m") { std::cout << s; return; }
                if (s == "\033[95m") { std::cout << s; return; }
                if (s == "\033[96m") { std::cout << s; return; }
                if (s == "\033[97m") { std::cout << s; return; }
                // 背景色常量 - 直接输出ANSI序列
                if (s == "\033[40m") { std::cout << s; return; }
                if (s == "\033[41m") { std::cout << s; return; }
                if (s == "\033[42m") { std::cout << s; return; }
                if (s == "\033[43m") { std::cout << s; return; }
                if (s == "\033[44m") { std::cout << s; return; }
                if (s == "\033[45m") { std::cout << s; return; }
                if (s == "\033[46m") { std::cout << s; return; }
                if (s == "\033[47m") { std::cout << s; return; }
#endif
                // 去除其它 ANSI 序列后输出文本
                s = std::regex_replace(s, std::regex("\x1B\\[[0-9;]*[A-Za-z]"), "");
                std::cout << s;
            } else if constexpr (std::is_same_v<T, tc::ColorWrapper> || std::is_same_v<T, tc::FontStyleWrapper>) {
                std::cout << arg;
            } else if constexpr (std::is_same_v<T, std::string>) {
                std::string s = arg;
#if defined(_WIN32) && defined(TC_ENABLE_WIN32_CONSOLE_API)
                if (s == "\033[0m") { ColorController::setColor(ColorController::Color::RESET); return; }
                if (s == "\033[1m") { ColorController::setBold(true); return; }
                if (s == "\033[22m") { ColorController::setBold(false); return; }
                // 前景色常量
                if (s == "\033[30m") { ColorController::setColor(ColorController::Color::BLACK); return; }
                if (s == "\033[31m") { ColorController::setColor(ColorController::Color::RED); return; }
                if (s == "\033[32m") { ColorController::setColor(ColorController::Color::GREEN); return; }
                if (s == "\033[33m") { ColorController::setColor(ColorController::Color::YELLOW); return; }
                if (s == "\033[34m") { ColorController::setColor(ColorController::Color::BLUE); return; }
                if (s == "\033[35m") { ColorController::setColor(ColorController::Color::MAGENTA); return; }
                if (s == "\033[36m") { ColorController::setColor(ColorController::Color::CYAN); return; }
                if (s == "\033[37m") { ColorController::setColor(ColorController::Color::WHITE); return; }
                if (s == "\033[90m") { ColorController::setColor(ColorController::Color::BRIGHT_BLACK); return; }
                if (s == "\033[91m") { ColorController::setColor(ColorController::Color::BRIGHT_RED); return; }
                if (s == "\033[92m") { ColorController::setColor(ColorController::Color::BRIGHT_GREEN); return; }
                if (s == "\033[93m") { ColorController::setColor(ColorController::Color::BRIGHT_YELLOW); return; }
                if (s == "\033[94m") { ColorController::setColor(ColorController::Color::BRIGHT_BLUE); return; }
                if (s == "\033[95m") { ColorController::setColor(ColorController::Color::BRIGHT_MAGENTA); return; }
                if (s == "\033[96m") { ColorController::setColor(ColorController::Color::BRIGHT_CYAN); return; }
                if (s == "\033[97m") { ColorController::setColor(ColorController::Color::BRIGHT_WHITE); return; }
                // 背景色常量
                if (s == "\033[40m") { ColorController::setBackground(ColorController::Color::BLACK); return; }
                if (s == "\033[41m") { ColorController::setBackground(ColorController::Color::RED); return; }
                if (s == "\033[42m") { ColorController::setBackground(ColorController::Color::GREEN); return; }
                if (s == "\033[43m") { ColorController::setBackground(ColorController::Color::YELLOW); return; }
                if (s == "\033[44m") { ColorController::setBackground(ColorController::Color::BLUE); return; }
                if (s == "\033[45m") { ColorController::setBackground(ColorController::Color::MAGENTA); return; }
                if (s == "\033[46m") { ColorController::setBackground(ColorController::Color::CYAN); return; }
                if (s == "\033[47m") { ColorController::setBackground(ColorController::Color::WHITE); return; }
#else
                if (s == "\033[0m") { std::cout << s; return; }
                if (s == "\033[1m") { std::cout << s; return; }
                if (s == "\033[22m") { std::cout << s; return; }
                // 前景色常量 - 直接输出ANSI序列
                if (s == "\033[30m") { std::cout << s; return; }
                if (s == "\033[31m") { std::cout << s; return; }
                if (s == "\033[32m") { std::cout << s; return; }
                if (s == "\033[33m") { std::cout << s; return; }
                if (s == "\033[34m") { std::cout << s; return; }
                if (s == "\033[35m") { std::cout << s; return; }
                if (s == "\033[36m") { std::cout << s; return; }
                if (s == "\033[37m") { std::cout << s; return; }
                if (s == "\033[90m") { std::cout << s; return; }
                if (s == "\033[91m") { std::cout << s; return; }
                if (s == "\033[92m") { std::cout << s; return; }
                if (s == "\033[93m") { std::cout << s; return; }
                if (s == "\033[94m") { std::cout << s; return; }
                if (s == "\033[95m") { std::cout << s; return; }
                if (s == "\033[96m") { std::cout << s; return; }
                if (s == "\033[97m") { std::cout << s; return; }
                // 背景色常量 - 直接输出ANSI序列
                if (s == "\033[40m") { std::cout << s; return; }
                if (s == "\033[41m") { std::cout << s; return; }
                if (s == "\033[42m") { std::cout << s; return; }
                if (s == "\033[43m") { std::cout << s; return; }
                if (s == "\033[44m") { std::cout << s; return; }
                if (s == "\033[45m") { std::cout << s; return; }
                if (s == "\033[46m") { std::cout << s; return; }
                if (s == "\033[47m") { std::cout << s; return; }
#endif
                s = std::regex_replace(s, std::regex("\x1B\\[[0-9;]*[A-Za-z]"), "");
                std::cout << s;
            } else {
                std::cout << arg;
            }
    };
#if defined(_WIN32)
    // 对每个参数调用 process，使用逗号折叠表达式展开
    (process(std::forward<Args>(args)), ...);
#endif
#endif
        return *this;
    }
    
    /**
     * 可变参数模板行打印，带换行符
     * Variadic template line print with newline
     * 
     * 打印所有参数后自动添加换行符。
     * Automatically adds newline after printing all arguments.
     * 
     * @param args 要打印的参数 | Arguments to print
     * @return 对象自身引用，支持链式调用 | Self reference for chaining
     */
    template<typename... Args>
    const PrintProxy& println(Args&&... args) const {
#ifndef _WIN32
    (std::cout << ... << std::forward<Args>(args));
#else
        print(std::forward<Args>(args)...);
#endif
#if defined(_WIN32) && defined(TC_ENABLE_WIN32_CONSOLE_API)
        // 使用tc::tout处理换行符，确保ANSI序列被正确处理
        tc::tout << std::endl;
#else
        std::cout << std::endl;
#endif
        return *this;
    }
};

/**
 * 全局print函数，返回PrintProxy实例以支持链式调用
 * Global print function, returns PrintProxy instance for chaining
 * 
 * 使用静态局部变量确保只有一个PrintProxy实例。
 * Uses static local variable to ensure only one PrintProxy instance.
 * 
 * @return PrintProxy实例引用 | PrintProxy instance reference
 */
inline const PrintProxy& print() { 
    static PrintProxy p; 
    return p; 
}

/**
 * 全局println函数，输出换行符并返回PrintProxy实例
 * Global println function, outputs newline and returns PrintProxy instance
 * 
 * @return PrintProxy实例引用 | PrintProxy instance reference
 */
inline const PrintProxy& println() { 
    static PrintProxy p; 
    std::cout << std::endl; 
    return p; 
}

/**
 * 全局print/println函数 - 支持一次性多参数打印
 * Global print/println functions - Support one-time multi-parameter printing
 * 
 * 这些函数提供了简单的接口来打印多个参数，类似于Python的print函数。
 * 使用可变参数模板和完美转发来支持任意类型和数量的参数。
 * 
 * These functions provide a simple interface to print multiple arguments, similar to Python's print function.
 * Uses variadic templates and perfect forwarding to support any type and number of arguments.
 */

/**
 * 全局print函数，一次性打印多个参数
 * Global print function, prints multiple arguments at once
 * 
 * @param args 要打印的参数 | Arguments to print
 */
template<typename... Args>
inline void print(Args&&... args) {
#ifndef _WIN32
    (std::cout << ... << std::forward<Args>(args));
#else
    static PrintProxy p;
    p.print(std::forward<Args>(args)...);
#endif
}

/**
 * 全局println函数，一次性打印多个参数并换行
 * Global println function, prints multiple arguments and adds newline
 * 
 * @param args 要打印的参数 | Arguments to print
 */
template<typename... Args>
inline void println(Args&&... args) {
#ifndef _WIN32
    (std::cout << ... << std::forward<Args>(args));
    std::cout << std::endl;
#else
    static PrintProxy p;
    p.println(std::forward<Args>(args)...);
#endif
}

} // namespace tc

#endif // TC_PRINT_HPP