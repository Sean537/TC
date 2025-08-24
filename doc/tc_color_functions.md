# TC库颜色控制功能详解

本文档详细说明了TC库中与颜色控制相关的各种接口和功能。TC库提供了多种方式来设置终端文本的颜色和样式，包括宏定义、颜色控制类和便捷函数。

## 目录

1. [概述](#概述)
2. [全局颜色宏](#全局颜色宏)
3. [ColorController类](#colorcontroller类)
4. [颜色包装器类](#颜色包装器类)
5. [便捷颜色函数](#便捷颜色函数)
6. [Windows平台特定功能](#windows平台特定功能)
7. [使用建议](#使用建议)
8. [示例代码](#示例代码)

## 概述

TC库提供了多种方式来控制终端文本的颜色和样式：

1. **全局颜色宏**：直接在流式输出中使用的ANSI颜色和样式宏。
2. **ColorController类**：提供统一的颜色和样式设置接口。
3. **颜色包装器类**：用于在流式输出中方便地设置颜色。
4. **便捷颜色函数**：返回已着色的字符串。
5. **Windows平台特定功能**：针对Windows控制台的特殊支持。

## 全局颜色宏

TC库定义了一系列全局宏，可以直接在流式输出中使用：

### 前景色宏

| 宏名称 | 描述 |
|--------|------|
| `TCOLOR_BLACK` | 黑色文本 |
| `TCOLOR_RED` | 红色文本 |
| `TCOLOR_GREEN` | 绿色文本 |
| `TCOLOR_YELLOW` | 黄色文本 |
| `TCOLOR_BLUE` | 蓝色文本 |
| `TCOLOR_MAGENTA` | 洋红色文本 |
| `TCOLOR_CYAN` | 青色文本 |
| `TCOLOR_WHITE` | 白色文本 |
| `TCOLOR_DEFAULT` | 默认前景色 |
| `TCOLOR_RESET` | 重置所有属性 |

### 背景色宏

| 宏名称 | 描述 |
|--------|------|
| `BCOLOR_BLACK` | 黑色背景 |
| `BCOLOR_RED` | 红色背景 |
| `BCOLOR_GREEN` | 绿色背景 |
| `BCOLOR_YELLOW` | 黄色背景 |
| `BCOLOR_BLUE` | 蓝色背景 |
| `BCOLOR_MAGENTA` | 洋红色背景 |
| `BCOLOR_CYAN` | 青色背景 |
| `BCOLOR_WHITE` | 白色背景 |
| `BCOLOR_DEFAULT` | 默认背景色 |

### 字体样式宏

| 宏名称 | 描述 |
|--------|------|
| `TFONT_BOLD` | 粗体/加粗文本 |
| `TFONT_FAINT` | 微弱/淡色文本 |
| `TFONT_ITALIC` | 斜体文本 |
| `TFONT_UNDERLINE` | 下划线文本 |
| `TFONT_BLINK_SLOW` | 慢速闪烁文本 |
| `TFONT_BLINK_FAST` | 快速闪烁文本 |
| `TFONT_REVERSE` | 反色（前景背景互换） |
| `TFONT_CONCEAL` | 隐藏文本 |
| `TFONT_CROSSED` | 删除线文本 |
| `TFONT_DEFAULT` | 默认字体 |
| `TFONT_RESET` | 全部重置（所有属性） |

### RGB颜色宏

| 宏名称 | 描述 |
|--------|------|
| `TCOLOR_RGB(r, g, b)` | 使用RGB值设置文本颜色 |

### 使用示例

```cpp
std::cout << TCOLOR_RED << "红色文本" << TCOLOR_RESET << std::endl;
std::cout << BCOLOR_BLUE << "蓝色背景" << TCOLOR_RESET << std::endl;
std::cout << TFONT_BOLD << "粗体文本" << TFONT_RESET << std::endl;
std::cout << TCOLOR_RGB(255, 128, 0) << "橙色文本" << TCOLOR_RESET << std::endl;
```

## ColorController类

`tc::ColorController`类提供了统一的颜色和样式设置接口，在不同平台上使用相应的实现。

### 颜色枚举

`tc::ColorController::Color`枚举定义了支持的所有颜色：

| 枚举值 | 描述 |
|--------|------|
| `BLACK` | 黑色 |
| `RED` | 红色 |
| `GREEN` | 绿色 |
| `YELLOW` | 黄色 |
| `BLUE` | 蓝色 |
| `MAGENTA` | 洋红色 |
| `CYAN` | 青色 |
| `WHITE` | 白色 |
| `BRIGHT_BLACK` | 亮黑色/灰色 |
| `BRIGHT_RED` | 亮红色 |
| `BRIGHT_GREEN` | 亮绿色 |
| `BRIGHT_YELLOW` | 亮黄色 |
| `BRIGHT_BLUE` | 亮蓝色 |
| `BRIGHT_MAGENTA` | 亮洋红色 |
| `BRIGHT_CYAN` | 亮青色 |
| `BRIGHT_WHITE` | 亮白色 |
| `RESET` | 重置为默认颜色 |

### 静态方法

| 方法名 | 描述 | 参数 | 返回值 |
|--------|------|------|--------|
| `setColor(Color color)` | 设置控制台文本颜色 | `color`: 要设置的颜色 | 无 |
| `setRGBColor(int r, int g, int b)` | 设置RGB颜色 | `r`, `g`, `b`: RGB分量(0-255) | 无 |
| `setBold(bool enable)` | 设置文本粗体样式 | `enable`: 是否启用粗体 | 无 |

### 使用示例

```cpp
// 设置红色文本
tc::ColorController::setColor(tc::ColorController::Color::RED);
std::cout << "红色文本" << std::endl;

// 设置RGB颜色
tc::ColorController::setRGBColor(255, 128, 0);
std::cout << "橙色文本" << std::endl;

// 设置粗体
tc::ColorController::setBold(true);
std::cout << "粗体文本" << std::endl;

// 重置颜色
tc::ColorController::setColor(tc::ColorController::Color::RESET);
```

## 颜色包装器类

TC库提供了几个包装器类，用于在流式输出中方便地设置颜色和样式。

### ColorWrapper类

`tc::ColorWrapper`类封装了颜色设置，便于在流式输出中使用。

```cpp
std::cout << tc::ColorWrapper(tc::ColorController::Color::RED) << "红色文本" 
          << tc::ColorWrapper(tc::ColorController::Color::RESET) << std::endl;
```

### RGBColorWrapper类

`tc::RGBColorWrapper`类封装了RGB颜色设置，便于在流式输出中使用。

```cpp
std::cout << tc::RGBColorWrapper(255, 128, 0) << "橙色文本" 
          << tc::ColorWrapper(tc::ColorController::Color::RESET) << std::endl;
```

### FontStyleWrapper类

`tc::FontStyleWrapper`类封装了字体样式设置（目前支持粗体），便于在流式输出中使用。

```cpp
std::cout << tc::FontStyleWrapper(true) << "粗体文本" 
          << tc::FontStyleWrapper(false) << std::endl;
```

## 便捷颜色函数

TC库提供了一系列便捷函数，用于为文本添加颜色，返回已着色的字符串。

| 函数名 | 描述 | 参数 | 返回值 |
|--------|------|------|--------|
| `colorize(text, color)` | 为文本添加指定颜色 | `text`: 要着色的文本<br>`color`: 要应用的颜色 | 带有颜色代码的字符串 |
| `red(text)` | 为文本添加红色 | `text`: 要着色的文本 | 红色文本字符串 |
| `green(text)` | 为文本添加绿色 | `text`: 要着色的文本 | 绿色文本字符串 |
| `blue(text)` | 为文本添加蓝色 | `text`: 要着色的文本 | 蓝色文本字符串 |
| `yellow(text)` | 为文本添加黄色 | `text`: 要着色的文本 | 黄色文本字符串 |

### 使用示例

```cpp
// 使用colorize函数
std::string coloredText = tc::colorize("彩色文本", tc::ColorController::Color::CYAN);
std::cout << coloredText << std::endl;

// 使用便捷颜色函数
std::cout << tc::red("红色文本") << std::endl;
std::cout << tc::green("绿色文本") << std::endl;
std::cout << tc::blue("蓝色文本") << std::endl;
std::cout << tc::yellow("黄色文本") << std::endl;
```

## Windows平台特定功能

在Windows平台上，TC库提供了额外的功能来支持Windows控制台。

### Win32Console类

`tc::Win32Console`类封装了Windows控制台API的操作，提供颜色设置、光标控制、清屏等功能。采用单例模式设计。

| 方法名 | 描述 | 参数 | 返回值 |
|--------|------|------|--------|
| `getInstance()` | 获取单例实例 | 无 | `Win32Console&`: 单例引用 |
| `isInitialized()` | 判断控制台是否成功初始化 | 无 | `bool`: 初始化状态 |
| `setColor(WORD color)` | 设置控制台文本颜色 | `color`: Windows控制台颜色属性 | 无 |
| `pushColor(WORD color)` | 保存当前颜色并设置新颜色 | `color`: 要设置的新颜色 | 无 |
| `popColor()` | 恢复之前保存的颜色 | 无 | 无 |
| `resetColor()` | 重置为原始控制台颜色 | 无 | 无 |
| `getCurrentColor()` | 获取当前控制台颜色 | 无 | `WORD`: 当前颜色属性 |
| `moveCursor(int x, int y)` | 移动控制台光标到指定位置 | `x`: 列坐标(从0开始)<br>`y`: 行坐标(从0开始) | 无 |
| `clearScreen()` | 清空控制台屏幕 | 无 | 无 |
| `getConsoleSize()` | 获取控制台窗口大小 | 无 | `std::pair<int, int>`: 包含宽度和高度的对组 |
| `rgbToWin32Color(int r, int g, int b)` | 将RGB颜色近似转换为Windows控制台16色 | `r`, `g`, `b`: RGB分量(0-255) | `WORD`: Windows控制台颜色属性 |

### win32_colors命名空间

`tc::win32_colors`命名空间定义了Windows控制台API使用的颜色常量。

| 常量名 | 描述 |
|--------|------|
| `BLACK` | 黑色 |
| `DARK_BLUE` | 深蓝色 |
| `DARK_GREEN` | 深绿色 |
| `DARK_CYAN` | 深青色 |
| `DARK_RED` | 深红色 |
| `DARK_MAGENTA` | 深洋红色 |
| `DARK_YELLOW` | 深黄色 |
| `GRAY` | 灰色 |
| `DARK_GRAY` | 深灰色 |
| `BLUE` | 蓝色 |
| `GREEN` | 绿色 |
| `CYAN` | 青色 |
| `RED` | 红色 |
| `MAGENTA` | 洋红色 |
| `YELLOW` | 黄色 |
| `WHITE` | 白色 |

### 使用示例

```cpp
#ifdef _WIN32
// 获取Win32Console单例
auto& console = tc::Win32Console::getInstance();

// 设置颜色
console.setColor(tc::win32_colors::RED);
std::cout << "红色文本" << std::endl;

// 保存当前颜色，设置新颜色，然后恢复
console.pushColor(tc::win32_colors::GREEN);
std::cout << "绿色文本" << std::endl;
console.popColor();
std::cout << "恢复之前的颜色" << std::endl;

// 清屏
console.clearScreen();

// 移动光标
console.moveCursor(10, 5);
std::cout << "在位置(10,5)" << std::endl;

// 获取控制台大小
auto [width, height] = console.getConsoleSize();
std::cout << "控制台大小: " << width << "x" << height << std::endl;
#endif
```

## 使用建议

1. **简单使用**：对于简单的颜色需求，使用全局颜色宏（如`TCOLOR_RED`）是最直接的方式。

2. **跨平台兼容**：使用`tc::ColorController`类或便捷颜色函数（如`tc::red()`）可以确保最佳的跨平台兼容性。

3. **流式输出**：在流式输出中，可以使用颜色包装器类（如`tc::ColorWrapper`）或全局颜色宏。

4. **字符串处理**：如果需要生成彩色字符串以便后续使用，使用便捷颜色函数（如`tc::colorize()`）。

5. **Windows特定功能**：在Windows平台上，如果需要更精细的控制，可以使用`tc::Win32Console`类。

## 示例代码

### 使用全局颜色宏

```cpp
#include "../include/tc.hpp"
#include <iostream>

int main() {
    std::cout << TCOLOR_RED << "红色文本" << TCOLOR_RESET << std::endl;
    std::cout << TCOLOR_GREEN << "绿色文本" << TCOLOR_RESET << std::endl;
    std::cout << TCOLOR_BLUE << "蓝色文本" << TCOLOR_RESET << std::endl;
    
    std::cout << BCOLOR_YELLOW << "黄色背景" << TCOLOR_RESET << std::endl;
    
    std::cout << TFONT_BOLD << "粗体文本" << TFONT_RESET << std::endl;
    std::cout << TFONT_UNDERLINE << "下划线文本" << TFONT_RESET << std::endl;
    
    std::cout << TCOLOR_RGB(255, 128, 0) << "橙色文本" << TCOLOR_RESET << std::endl;
    
    return 0;
}
```

### 使用ColorController类

```cpp
#include "../include/tc.hpp"
#include <iostream>

int main() {
    // 设置红色
    tc::ColorController::setColor(tc::ColorController::Color::RED);
    std::cout << "红色文本" << std::endl;
    
    // 设置亮绿色
    tc::ColorController::setColor(tc::ColorController::Color::BRIGHT_GREEN);
    std::cout << "亮绿色文本" << std::endl;
    
    // 设置RGB颜色
    tc::ColorController::setRGBColor(255, 128, 0);
    std::cout << "橙色文本" << std::endl;
    
    // 设置粗体
    tc::ColorController::setBold(true);
    std::cout << "粗体文本" << std::endl;
    
    // 重置所有属性
    tc::ColorController::setColor(tc::ColorController::Color::RESET);
    std::cout << "正常文本" << std::endl;
    
    return 0;
}
```

### 使用颜色包装器类

```cpp
#include "../include/tc.hpp"
#include <iostream>

int main() {
    // 使用ColorWrapper
    std::cout << tc::ColorWrapper(tc::ColorController::Color::RED) << "红色文本" 
              << tc::ColorWrapper(tc::ColorController::Color::RESET) << std::endl;
    
    // 使用RGBColorWrapper
    std::cout << tc::RGBColorWrapper(255, 128, 0) << "橙色文本" 
              << tc::ColorWrapper(tc::ColorController::Color::RESET) << std::endl;
    
    // 使用FontStyleWrapper
    std::cout << tc::FontStyleWrapper(true) << "粗体文本" 
              << tc::FontStyleWrapper(false) << std::endl;
    
    return 0;
}
```

### 使用便捷颜色函数

```cpp
#include "../include/tc.hpp"
#include <iostream>

int main() {
    // 使用colorize函数
    std::string coloredText = tc::colorize("彩色文本", tc::ColorController::Color::CYAN);
    std::cout << coloredText << std::endl;
    
    // 使用便捷颜色函数
    std::cout << tc::red("红色文本") << std::endl;
    std::cout << tc::green("绿色文本") << std::endl;
    std::cout << tc::blue("蓝色文本") << std::endl;
    std::cout << tc::yellow("黄色文本") << std::endl;
    
    return 0;
}
```

### 综合示例

```cpp
#include "../include/tc.hpp"
#include <iostream>
#include <string>

void demoGlobalMacros() {
    std::cout << "=== 全局颜色宏演示 ===" << std::endl;
    
    std::cout << TCOLOR_RED << "红色文本" << TCOLOR_RESET << std::endl;
    std::cout << BCOLOR_BLUE << "蓝色背景" << TCOLOR_RESET << std::endl;
    std::cout << TFONT_BOLD << "粗体文本" << TFONT_RESET << std::endl;
    std::cout << TCOLOR_RGB(255, 128, 0) << "橙色文本" << TCOLOR_RESET << std::endl;
    
    std::cout << TCOLOR_GREEN << "绿色" << TCOLOR_BLUE << "蓝色" << TCOLOR_RESET << std::endl;
    
    tc::wait(2);
}

void demoColorController() {
    std::cout << "=== ColorController类演示 ===" << std::endl;
    
    tc::ColorController::setColor(tc::ColorController::Color::RED);
    std::cout << "红色文本" << std::endl;
    
    tc::ColorController::setColor(tc::ColorController::Color::BRIGHT_GREEN);
    std::cout << "亮绿色文本" << std::endl;
    
    tc::ColorController::setRGBColor(255, 128, 0);
    std::cout << "橙色文本" << std::endl;
    
    tc::ColorController::setBold(true);
    std::cout << "粗体文本" << std::endl;
    
    tc::ColorController::setColor(tc::ColorController::Color::RESET);
    std::cout << "正常文本" << std::endl;
    
    tc::wait(2);
}

void demoColorFunctions() {
    std::cout << "=== 便捷颜色函数演示 ===" << std::endl;
    
    std::cout << tc::red("红色文本") << std::endl;
    std::cout << tc::green("绿色文本") << std::endl;
    std::cout << tc::blue("蓝色文本") << std::endl;
    std::cout << tc::yellow("黄色文本") << std::endl;
    
    std::string message = "重要提示";
    std::cout << tc::colorize(message, tc::ColorController::Color::BRIGHT_RED) << std::endl;
    
    tc::wait(2);
}

int main() {
    demoGlobalMacros();
    std::cout << std::endl;
    
    demoColorController();
    std::cout << std::endl;
    
    demoColorFunctions();
    std::cout << std::endl;
    
    std::cout << "所有颜色功能演示完成！" << std::endl;
    
    return 0;
}
```

通过以上示例，您可以清楚地了解TC库中各种颜色控制功能的使用方法和区别，从而根据具体需求选择合适的接口。
