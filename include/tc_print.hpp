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
 * 版本 Version: 1.0.1
 * 作者 Author: 537 Studio
 * 许可 License: MIT
 */

#ifndef TC_PRINT_HPP
#define TC_PRINT_HPP

// 标准库包含 | Standard library includes
#include <iostream>       // 输入输出流 | Input/output streams
#include <initializer_list> // 初始化列表 | Initializer list

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
        (void)std::initializer_list<int>{(std::cout << std::forward<Args>(args), 0)...}; 
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
        (void)std::initializer_list<int>{(std::cout << std::forward<Args>(args), 0)...}; 
        std::cout << std::endl; 
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
    (void)std::initializer_list<int>{(std::cout << std::forward<Args>(args), 0)...}; 
}

/**
 * 全局println函数，一次性打印多个参数并换行
 * Global println function, prints multiple arguments and adds newline
 * 
 * @param args 要打印的参数 | Arguments to print
 */
template<typename... Args>
inline void println(Args&&... args) { 
    (void)std::initializer_list<int>{(std::cout << std::forward<Args>(args), 0)...}; 
    std::cout << std::endl; 
}

} // namespace tc

#endif // TC_PRINT_HPP