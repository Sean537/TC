/*
 * tc_print.hpp - TC库打印功能模块
 * TC Print Functionality Module
 * 
 * 这个文件包含了TC库中所有与打印输出相关的功能，包括：
 * - Python风格的print和println函数
 * - 支持可变参数的打印函数
 * - 链式调用的PrintProxy类
 * 
 * 版本 Version: 1.1.3 Beta
 * 作者 Author: 537 Studio
 * 许可 License: MIT
 */

#ifndef TC_PRINT_HPP
#define TC_PRINT_HPP

// 标准库包含 | Standard library includes
#include <iostream>
#include <initializer_list>
#include <string>
#include <type_traits>
#include "tc_stream.hpp"

namespace tc {

namespace detail {
    template<typename T>
    inline void print_one(T&& arg) {
        // 使用 tc::tout 统一处理 ANSI 过滤和 Win32 映射逻辑
        tc::tout << std::forward<T>(arg);
    }
} // namespace detail

/**
 * PrintProxy类 - 提供链式调用风格的打印功能
 */
class PrintProxy {
public:
    template<typename... Args>
    PrintProxy& print(Args&&... args) {
        (detail::print_one(std::forward<Args>(args)), ...);
        return *this;
    }

    template<typename... Args>
    PrintProxy& println(Args&&... args) {
        (detail::print_one(std::forward<Args>(args)), ...);
        std::cout << std::endl;
        return *this;
    }
};

/**
 * Python风格的打印函数
 */
template<typename... Args>
inline void print(Args&&... args) {
    (detail::print_one(std::forward<Args>(args)), ...);
}

inline PrintProxy print() {
    return PrintProxy();
}

template<typename... Args>
inline void println(Args&&... args) {
    (detail::print_one(std::forward<Args>(args)), ...);
    std::cout << std::endl;
}

/**
 * 返回一个PrintProxy对象用于链式调用
 */
inline PrintProxy printProxy() {
    return PrintProxy();
}

} // namespace tc

#endif // TC_PRINT_HPP
