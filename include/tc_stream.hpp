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
 * This file contains stream output and delay functionality in the TC library, including:
 * - Enhanced output stream class (TOut)
 * - Delay operation class (TSleep)
 * - Stream-style delay operation class (TSleepStream)
 * - Stream output with color and style support
 * 
 * 版本 Version: 1.1.1
 * 作者 Author: 537 Studio
 * 许可 License: MIT
 */

#ifndef TC_STREAM_HPP
#define TC_STREAM_HPP

// 标准库包含 | Standard library includes
#include <iostream>  // 输入输出流 | Input/output streams
#include <thread>    // 线程库 | Thread library
#include <chrono>    // 时间库 | Time library
#include "tc_colors.hpp" // TC颜色模块 | TC color module

namespace tc {

/**
 * 延时操作类
 * Sleep operation class
 * 
 * 这个类封装了延时操作，便于在流式输出中使用。
 * 可以直接用于流式输出，如：std::cout << "等待开始" << TSleep(1000) << "等待结束";
 * 
 * This class encapsulates sleep operations for easy use in stream output.
 * Can be used directly in stream output, e.g.: std::cout << "Wait starts" << TSleep(1000) << "Wait ends";
 */
class TSleep {
private:
    int milliseconds_; // 延时的毫秒数 | Milliseconds to sleep
    
public:
    /**
     * 构造函数
     * Constructor
     * 
     * @param ms 延时的毫秒数 | Milliseconds to sleep
     */
    explicit TSleep(int ms) : milliseconds_(ms) {}
    
    /**
     * 执行延时操作
     * Execute sleep operation
     */
    void execute() const {
        // 使用标准库的线程休眠功能 | Use standard library thread sleep functionality
        std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds_));
    }
    
    /**
     * 输出流操作符重载，使对象可以直接用于流式输出
     * Output stream operator overload, allowing the object to be used directly in stream output
     * 
     * @param os 输出流 | Output stream
     * @param sleep 延时操作对象 | Sleep operation object
     * @return 输出流引用，用于链式调用 | Output stream reference for chaining
     */
    friend std::ostream& operator<<(std::ostream& os, const TSleep& sleep) {
        sleep.execute(); // 执行延时 | Execute sleep
        return os;
    }
};

/**
 * 自定义输出流类
 * Custom output stream class
 * 
 * 这个类提供了增强的输出流功能，支持链式输出和自定义类型。
 * 它可以处理颜色、RGB颜色、字体样式和延时操作等特殊类型。
 * 
 * This class provides enhanced output stream functionality, supporting chain output and custom types.
 * It can handle special types like colors, RGB colors, font styles, and sleep operations.
 */
class TOut {
private:
    std::ostream& os_; // 底层输出流引用 | Reference to underlying output stream
    
public:
    /**
     * 构造函数
     * Constructor
     * 
     * @param os 底层输出流，默认为标准输出 | Underlying output stream, defaults to standard output
     */
    explicit TOut(std::ostream& os = std::cout) : os_(os) {
#ifdef _WIN32
        // 确保Windows控制台已初始化 | Ensure Windows console is initialized
        Win32Console::getInstance();
#endif
    }
    
    /**
     * 通用输出操作符，处理任意类型的值
     * Generic output operator, handles values of any type
     * 
     * 使用完美转发来保持参数的原始类型和值类别。
     * Uses perfect forwarding to preserve original type and value category of arguments.
     * 
     * @param value 要输出的值 | Value to output
     * @return 自身引用，用于链式调用 | Self reference for chaining
     */
    template<typename T>
    TOut& operator<<(T&& value) {
        os_ << std::forward<T>(value); // 转发值到底层流 | Forward value to underlying stream
        return *this;
    }
    
    /**
     * 特化的输出操作符，处理延时操作
     * Specialized output operator for sleep operations
     * 
     * @param sleep 延时操作对象 | Sleep operation object
     * @return 自身引用，用于链式调用 | Self reference for chaining
     */
    TOut& operator<<(const TSleep& sleep) {
        sleep.execute(); // 执行延时 | Execute sleep
        return *this;
    }
    
    /**
     * 特化的输出操作符，处理颜色包装器
     * Specialized output operator for color wrappers
     * 
     * @param color 颜色包装器对象 | Color wrapper object
     * @return 自身引用，用于链式调用 | Self reference for chaining
     */
    TOut& operator<<(const ColorWrapper& color) {
        os_ << color; // 应用颜色设置 | Apply color setting
        return *this;
    }
    
    /**
     * 特化的输出操作符，处理RGB颜色包装器
     * Specialized output operator for RGB color wrappers
     * 
     * @param color RGB颜色包装器对象 | RGB color wrapper object
     * @return 自身引用，用于链式调用 | Self reference for chaining
     */
    TOut& operator<<(const RGBColorWrapper& color) {
        os_ << color; // 应用RGB颜色设置 | Apply RGB color setting
        return *this;
    }
    
    /**
     * 特化的输出操作符，处理字体样式包装器
     * Specialized output operator for font style wrappers
     * 
     * @param style 字体样式包装器对象 | Font style wrapper object
     * @return 自身引用，用于链式调用 | Self reference for chaining
     */
    TOut& operator<<(const FontStyleWrapper& style) {
        os_ << style; // 应用字体样式设置 | Apply font style setting
        return *this;
    }
    
    /**
     * 支持标准流操作符，如std::endl
     * Support for standard stream manipulators like std::endl
     * 
     * @param manip 流操作符函数 | Stream manipulator function
     * @return 自身引用，用于链式调用 | Self reference for chaining
     */
    TOut& operator<<(std::ostream& (*manip)(std::ostream&)) {
        os_ << manip; // 应用流操作符 | Apply stream manipulator
        return *this;
    }
    
    /**
     * 获取底层输出流
     * Get underlying output stream
     * 
     * @return 底层输出流引用 | Reference to underlying output stream
     */
    std::ostream& stream() { return os_; }
};

/**
 * 全局输出流对象，类似std::cout但具有增强功能
 * Global output stream object, similar to std::cout but with enhanced features
 * 
 * 这个对象可以用于所有标准输出操作，并支持颜色、样式和延时等特殊功能。
 * 例如：tc::tout << TCOLOR_RED << "红色文本" << TCOLOR_RESET << std::endl;
 * 
 * This object can be used for all standard output operations and supports special features
 * like colors, styles, and sleep operations.
 * Example: tc::tout << TCOLOR_RED << "Red text" << TCOLOR_RESET << std::endl;
 */
static TOut tout(std::cout);

/**
 * 创建延时操作对象
 * Create sleep operation object
 * 
 * @param milliseconds 延时的毫秒数 | Milliseconds to sleep
 * @return TSleep对象，可用于流式输出 | TSleep object that can be used in stream output
 */
inline TSleep tsleep(int milliseconds) {
    return TSleep(milliseconds);
}

/**
 * 延时流操作符类
 * Sleep stream operator class
 * 
 * 这个类提供了另一种延时语法，使用左移操作符。
 * 例如：tc::tsleep_stream << 1000; // 延时1秒
 * 
 * This class provides an alternative sleep syntax using the left shift operator.
 * Example: tc::tsleep_stream << 1000; // Sleep for 1 second
 */
class TSleepStream {
public:
    /**
     * 左移操作符重载，执行延时操作
     * Left shift operator overload, executes sleep operation
     * 
     * @param milliseconds 延时的毫秒数 | Milliseconds to sleep
     */
    void operator<<(int milliseconds) const {
        std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
    }
};

/**
 * 全局延时流对象
 * Global sleep stream object
 * 
 * 用于执行流式延旲操作。
 * 例如：tc::tsleep_stream << 1000; // 延时1秒
 * 
 * Used for stream-style sleep operations.
 * Example: tc::tsleep_stream << 1000; // Sleep for 1 second
 */
static TSleepStream tsleep_stream;

} // namespace tc

#endif // TC_STREAM_HPP