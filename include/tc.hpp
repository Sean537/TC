/*
 * tc.hpp - TC库主头文件
 * TC Library Main Header File
 * 
 * 版本 Version: 1.1.1 Beta
 * 
 * 这是TC（Terminal Control）库的主头文件，一个现代化的C++17终端控制库。
 * TC库提供了跨平台的终端颜色、样式、光标控制、进度条等功能，
 * 支持Windows/Linux/macOS，零依赖，纯头文件设计。
 * 
 * This is the main header file for the TC (Terminal Control) library, a modern C++17 terminal control library.
 * TC library provides cross-platform terminal colors, styles, cursor control, progress bars and other features,
 * supporting Windows/Linux/macOS with zero dependencies and header-only design.
 * 
 * 在线仓库 Online repository:
 * - https://github.com/Sean537/TC
 * - https://gitee.com/sean537/TC
 * 
 * 版权所有 Copyright (C) 2024-2025 537 Studio. All rights reserved.
 * 
 * 贡献者 Contributors:
 * - Sean537
 * - RabbitMax
 * - L.U.
 * 
 * 功能模块 Feature Modules:
 * - 颜色和样式控制 Color and style control (tc_colors.hpp)
 * - 打印输出功能 Print output functionality (tc_print.hpp)
 * - 等待和按键处理 Wait and key handling (tc_wait.hpp)
 * - 终端控制操作 Terminal control operations (tc_terminal.hpp)
 * - 流式输出和延时 Stream output and delay (tc_stream.hpp)
 * - 进度条显示 Progress bar display (tc_progress.hpp)
 * - 系统检测功能 System detection functionality (tc_system.hpp)
 * - 系统工具函数 System utility functions (tc_system_utils.hpp)
 * 
 * 许可证 License: MIT
 */

#ifndef TC_HPP
#define TC_HPP

/**
 * TC库版本号
 * TC library version number
 */
#define TC_VERSION "1.1.1 Beta"

/**
 * 包含所需的标准库头文件
 * Include required standard library headers
 * 
 * 这些标准库头文件提供了TC库运行所需的基础功能，包括：
 * - 输入输出流操作
 * - 字符串处理
 * - 线程和时间操作
 * - 智能指针和函数对象
 * - 模板元编程支持
 * 
 * These standard library headers provide the basic functionality required for TC library operation, including:
 * - Input/output stream operations
 * - String processing
 * - Thread and time operations
 * - Smart pointers and function objects
 * - Template metaprogramming support
 */
#include <iostream>    // 标准输入输出流 | Standard input/output streams
#include <string>      // 字符串类 | String class
#include <sstream>     // 字符串流 | String streams
#include <thread>      // 线程库 | Thread library
#include <chrono>      // 时间库 | Time library
#include <memory>      // 智能指针 | Smart pointers
#include <functional>  // 函数对象 | Function objects
#include <type_traits> // 类型特性 | Type traits
#include <stack>       // 栈容器 | Stack container

/**
 * 平台特定头文件包含
 * Platform-specific header includes
 * 
 * 根据编译平台包含相应的系统头文件，以支持平台特定的功能：
 * - Windows: Windows API、IO操作、文件控制
 * - Unix/Linux/macOS: POSIX API、系统IO控制
 * 
 * Include appropriate system headers based on compilation platform to support platform-specific features:
 * - Windows: Windows API, IO operations, file control
 * - Unix/Linux/macOS: POSIX API, system IO control
 */
#ifdef _WIN32 // Windows平台 | Windows platform
    #include <windows.h> // Windows API函数和数据类型 | Windows API functions and data types
    #include <io.h>      // Windows IO操作函数 | Windows IO operation functions
    #include <fcntl.h>   // 文件控制选项 | File control options
    #ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
        // 定义ANSI转义序列支持标志（如果未定义） | Define ANSI escape sequence support flag (if not defined)
        #define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
    #endif
#else // 非Windows平台（Unix/Linux/macOS等） | Non-Windows platforms (Unix/Linux/macOS etc.)
    #include <unistd.h>    // POSIX API，提供sleep等函数 | POSIX API providing functions like sleep
    #include <sys/ioctl.h> // 终端IO控制，用于获取终端大小 | Terminal IO control for getting terminal size
#endif

/**
 * 包含各功能模块
 * Include functional modules
 * 
 * TC库采用模块化设计，将不同功能分离到独立的头文件中，
 * 便于维护和理解。每个模块都有特定的职责和功能。
 * 
 * TC library uses modular design, separating different functions into independent header files
 * for easy maintenance and understanding. Each module has specific responsibilities and functions.
 */
#include "tc_colors.hpp"       // 颜色和样式相关功能 | Color and style related functionality
#include "tc_print.hpp"        // 打印功能 | Print functionality
#include "tc_wait.hpp"         // 等待和按键处理 | Wait and key handling
#include "tc_terminal.hpp"     // 终端控制 | Terminal control
#include "tc_stream.hpp"       // 流式输出和延时 | Stream output and delay
#include "tc_progress.hpp"     // 进度条 | Progress bar
#include "tc_system.hpp"       // 系统检测 | System detection
#include "tc_system_utils.hpp" // 系统工具 | System utilities

#endif // TC_HPP