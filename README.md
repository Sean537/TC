 # TC.hpp - 跨平台终端控制库

[![C++17](https://img.shields.io/badge/C%2B%2B-17%2B-blue.svg)](https://en.cppreference.com/w/cpp/compiler_support)
[![跨平台](https://img.shields.io/badge/平台-Windows%20%7C%20Linux%20%7C%20macOS-lightgrey.svg)](#)
[![纯头文件](https://img.shields.io/badge/Header--Only-Yes-green.svg)](#)
[![MIT 许可证](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

一个现代化的 C++17 跨平台终端控制库，在 Windows 环境下使用原生 Win32 API，在 Unix/Linux 环境下使用 ANSI 转义序列，提供统一的编程接口。支持文本带颜色输出、等待时间输出等功能。

## ✨ 核心特性

- 🎨 **智能平台适配** - Windows 使用 Win32 API，Unix/Linux 使用 ANSI 转义序列
- 🔧 **现代 C++17** - 使用最新 C++ 特性，RAII 资源管理
- 📦 **纯头文件** - 无需编译，包含即用
- 💫 **流式语法** - 支持自然的流操作符语法
- 🌈 **丰富色彩** - 支持基本颜色、亮色和 RGB 颜色
- ⏱️ **延时控制** - 内置延时输出功能
- 🖥️ **终端控制** - 光标控制、屏幕清除、尺寸获取
- 🔄 **状态管理** - 自动颜色状态保存和恢复

## 🚀 快速开始

### 系统要求
- 支持 C++17 的编译器
- Windows: Win32 API 支持
- Unix/Linux: ANSI 终端支持

### 安装使用
下载 `tc.hpp` 文件并包含：

```cpp
#include "tc.hpp"
```

### 基础示例

```cpp
#include "tc.hpp"

int main() {
    // 基本颜色输出
    tc::tout << tc::TCOLOR_GREEN << "Hello world!" << tc::TCOLOR_RESET << std::endl;
    
    // 粗体文本
    tc::tout << tc::TFONT_THICK << 12345 << tc::TFONT_RESET << std::endl;
    
    // RGB 颜色
    tc::tout << TCOLOR_RGB(255, 255, 255) << "White Text" << tc::TCOLOR_RESET << std::endl;
    
    // 延时输出
    tc::tout << "Wait for 3 seconds…" << tc::tsleep(3000) << "Okay I'm here" << std::endl;
    
    // 延时流语法
    tsleep << 1000;  // 等待 1 秒
    
    return 0;
}
```

## 📖 API 参考

### 颜色控制

#### 基本颜色常量
```cpp
tc::TCOLOR_BLACK     // 黑色
tc::TCOLOR_RED       // 红色
tc::TCOLOR_GREEN     // 绿色
tc::TCOLOR_YELLOW    // 黄色
tc::TCOLOR_BLUE      // 蓝色
tc::TCOLOR_MAGENTA   // 洋红
tc::TCOLOR_CYAN      // 青色
tc::TCOLOR_WHITE     // 白色
tc::TCOLOR_RESET     // 重置颜色
```

#### RGB 颜色宏
```cpp
TCOLOR_RGB(r, g, b)  // RGB 颜色，r/g/b 取值 0-255
```

#### 字体样式常量
```cpp
tc::TFONT_THICK      // 粗体/加粗
tc::TFONT_BOLD       // 粗体（同 TFONT_THICK）
tc::TFONT_RESET      // 重置字体样式
```

### 输出流

#### TOut 类
```cpp
tc::tout             // 全局输出流对象
```

支持标准流操作符，自动处理颜色和样式：

```cpp
tc::tout << tc::TCOLOR_RED << "红色文本" << tc::TCOLOR_RESET;
tc::tout << tc::TFONT_BOLD << "粗体文本" << tc::TFONT_RESET;
```

### 延时控制

#### 延时函数
```cpp
tc::tsleep(int milliseconds)  // 返回延时对象，可用于流操作
```

#### 延时流操作符
```cpp
tsleep << 1000;  // 直接延时 1000 毫秒
```

### 终端控制

#### 屏幕控制
```cpp
tc::terminal::clear()                    // 清除屏幕
tc::terminal::moveCursor(int x, int y)   // 移动光标到指定位置
tc::terminal::getSize()                  // 获取终端尺寸，返回 std::pair<int, int>
```

#### 便利函数
```cpp
tc::red(const std::string& text)      // 返回红色文本字符串
tc::green(const std::string& text)    // 返回绿色文本字符串
tc::blue(const std::string& text)     // 返回蓝色文本字符串
tc::yellow(const std::string& text)   // 返回黄色文本字符串
```

## 🎨 代码使用示例

### 示例1：基础颜色演示

```cpp
#include "tc.hpp"
#include <iostream>

int main() {
    using namespace tc;
    
    tout << "=== 基础颜色演示 ===" << std::endl;
    
    // 基本颜色
    tout << TCOLOR_RED << "红色文本 " << TCOLOR_RESET;
    tout << TCOLOR_GREEN << "绿色文本 " << TCOLOR_RESET;
    tout << TCOLOR_BLUE << "蓝色文本 " << TCOLOR_RESET;
    tout << TCOLOR_YELLOW << "黄色文本 " << TCOLOR_RESET << std::endl;
    
    // 粗体样式
    tout << TFONT_BOLD << "这是粗体文本" << TFONT_RESET << std::endl;
    
    // 组合使用
    tout << TCOLOR_CYAN << TFONT_BOLD << "青色粗体文本" << TCOLOR_RESET << std::endl;
    
    return 0;
}
```

### 示例2：动态进度条

```cpp
#include "tc.hpp"

void showProgressBar(int current, int total, int width = 30) {
    using namespace tc;
    
    float progress = static_cast<float>(current) / total;
    int filled = static_cast<int>(progress * width);
    
    tout << "\r[";
    
    // 填充部分（绿色）
    for (int i = 0; i < filled; ++i) {
        tout << TCOLOR_GREEN << "█" << TCOLOR_RESET;
    }
    
    // 空白部分（灰色）
    for (int i = filled; i < width; ++i) {
        tout << "░";
    }
    
    tout << "] " << static_cast<int>(progress * 100) << "%";
    tout.stream().flush();
}

int main() {
    using namespace tc;
    
    tout << "进度条演示:" << std::endl;
    
    for (int i = 0; i <= 100; i += 2) {
        showProgressBar(i, 100);
        tsleep << 100;
    }
    
    tout << std::endl << TCOLOR_GREEN << "下载完成!" << TCOLOR_RESET << std::endl;
    
    return 0;
}
```

### 示例3：打字机效果

```cpp
#include "tc.hpp"
#include <string>

void typewriter(const std::string& text, int delay = 100) {
    using namespace tc;
    
    for (char c : text) {
        tout << TCOLOR_GREEN << c << TCOLOR_RESET;
        tout.stream().flush();
        tsleep << delay;
    }
}

int main() {
    using namespace tc;
    
    tout << TCOLOR_CYAN << "=== 打字机效果演示 ===" << TCOLOR_RESET << std::endl;
    
    typewriter("正在初始化系统", 150);
    
    // 添加动态点点点
    for (int i = 0; i < 5; ++i) {
        tout << TCOLOR_YELLOW << "." << TCOLOR_RESET;
        tout.stream().flush();
        tsleep << 300;
    }
    
    tout << std::endl;
    typewriter("系统初始化完成!", 100);
    tout << std::endl;
    
    return 0;
}
```

## 🔧 平台差异说明

### Windows 平台
- **实现方式**: 使用 Win32 API (`SetConsoleTextAttribute`, `SetConsoleCursorPosition` 等)
- **颜色支持**: 原生支持 16 色，RGB 颜色自动映射到最接近的标准颜色
- **性能**: 直接系统调用，性能优异
- **兼容性**: 支持 Windows 10+ 以及较老版本的 Windows

### Unix/Linux 平台
- **实现方式**: 使用 ANSI 转义序列
- **颜色支持**: 完整支持包括 RGB 在内的所有颜色
- **性能**: 基于字符串输出，性能良好
- **兼容性**: 支持所有现代终端

## 🛠️ 编译方法

### Windows
```bash
# 使用 MSVC
cl /std:c++17 example.cpp

# 使用 MinGW
g++ -std=c++17 example.cpp -o example.exe
```

### Linux/macOS
```bash
g++ -std=c++17 -pthread example.cpp -o example
```

### CMake 支持
```cmake
cmake_minimum_required(VERSION 3.10)
project(TCLibExample)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(example example.cpp)

# Windows 下链接必要的库
if(WIN32)
    target_link_libraries(example kernel32)
endif()

# Unix/Linux 下链接线程库
if(UNIX)
    find_package(Threads REQUIRED)
    target_link_libraries(example Threads::Threads)
endif()
```

## 📊 性能特点

- **零开销抽象**: 编译时确定平台，运行时无额外判断
- **RAII 管理**: 自动资源管理，无需手动清理
- **直接系统调用**: Windows 下直接调用 Win32 API
- **缓存优化**: 智能颜色状态管理，减少重复设置

## 🎯 设计原则

1. **跨平台统一**: 相同的 API，不同平台的最优实现
2. **现代 C++**: 充分利用C++特性
3. **性能优先**: 在保证易用性的前提下追求最佳性能
4. **RAII 设计**: 自动资源管理，防止状态泄露
5. **流式语法**: 自然直观的使用方式

## 📝 注意事项

### Windows 环境
- 某些较老的 Windows 版本可能不支持所有颜色特性
- RGB 颜色会自动映射到最接近的 16 色

### Unix/Linux 环境
- 需要终端支持 ANSI 转义序列
- 大多数现代终端都支持 RGB 颜色
- 某些嵌入式环境可能功能受限

### 编码问题
确保源文件保存为 UTF-8 编码，避免中文字符显示问题。

## 🤝 开发贡献

欢迎参与项目开发！您可以通过以下方式贡献：

### 提交 Issues
如果您发现了 bug 或有功能建议，请提交 Issue。提交时请包含：
- 详细的问题描述
- 复现步骤
- 您的系统环境信息
- 相关的代码示例

### 提交 Pull Request
我们欢迎代码贡献！提交 PR 时请：
- 遵循现有的代码风格
- 确保跨平台兼容性
- 添加适当的注释和文档
- 提供测试用例
- 在 PR 描述中详细说明您的更改

### 联系方式
如有任何问题或建议，可以通过以下方式联系：
- 📧 **邮箱**: [wushaoquan666@outlook.com](mailto:wushaoquan666@outlook.com)
- 💬 **Issues**: 在项目仓库中提交问题
- 🐛 **Bug 报告**: 请通过 Issues 或邮件报告
- 💡 **功能建议**: 通过 Issues 或邮件提出新功能想法

## 📄 许可证

本项目采用 MIT 许可证 - 详见 [LICENSE](LICENSE) 文件。