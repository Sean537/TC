# TC.hpp 功能文档

> TC.hpp 是一个现代化的 C++17 终端控制库，支持彩色输出、字体样式、延时、进度条、终端控制等，跨平台、零依赖、纯头文件。

## 目录

- [基本概述](#基本概述)
- [颜色与样式](#颜色与样式)
  - [前景色](#前景色)
  - [背景色](#背景色)
  - [字体样式](#字体样式)
  - [RGB颜色](#rgb颜色)
- [输出函数](#输出函数)
  - [标准输出](#标准输出)
  - [链式输出](#链式输出)
- [延时与等待](#延时与等待)
  - [延时函数](#延时函数)
  - [按键等待](#按键等待)
- [终端控制](#终端控制)
  - [光标控制](#光标控制)
  - [终端尺寸](#终端尺寸)
  - [清屏功能](#清屏功能)
- [进度条](#进度条)
- [系统相关API](#系统相关api)
  - [系统时间](#系统时间)
  - [系统命令](#系统命令)
  - [系统检测](#系统检测)
- [跨平台兼容性](#跨平台兼容性)
- [使用示例](#使用示例)

## 基本概述

TC.hpp 是一个跨平台的终端控制库，提供了丰富的终端操作功能，包括颜色输出、字体样式、光标控制、延时等。该库采用纯头文件设计，无需额外依赖，只需包含 `tc.hpp` 即可使用所有功能。

主要特点：
- 跨平台支持（Windows、Linux、macOS）
- 纯头文件，零依赖
- 现代 C++17 设计
- 丰富的终端控制功能
- 简洁易用的 API

## 颜色与样式

### 前景色

TC.hpp 提供了一系列前景色宏，可直接在代码中使用：

| 宏名 | 颜色 | ANSI代码 |
|------|------|----------|
| `TCOLOR_BLACK` | 黑色 | `\033[30m` |
| `TCOLOR_RED` | 红色 | `\033[31m` |
| `TCOLOR_GREEN` | 绿色 | `\033[32m` |
| `TCOLOR_YELLOW` | 黄色 | `\033[33m` |
| `TCOLOR_BLUE` | 蓝色 | `\033[34m` |
| `TCOLOR_MAGENTA` | 洋红 | `\033[35m` |
| `TCOLOR_CYAN` | 青色 | `\033[36m` |
| `TCOLOR_WHITE` | 白色 | `\033[37m` |
| `TCOLOR_DEFAULT` | 默认 | `\033[39m` |
| `TCOLOR_RESET` | 重置 | `\033[0m` |

使用示例：
```cpp
tc::println(TCOLOR_RED, "这是红色文本", TCOLOR_RESET);
```

### 背景色

背景色宏可以设置文本的背景颜色：

| 宏名 | 颜色 | ANSI代码 |
|------|------|----------|
| `BCOLOR_BLACK` | 黑色 | `\033[40m` |
| `BCOLOR_RED` | 红色 | `\033[41m` |
| `BCOLOR_GREEN` | 绿色 | `\033[42m` |
| `BCOLOR_YELLOW` | 黄色 | `\033[43m` |
| `BCOLOR_BLUE` | 蓝色 | `\033[44m` |
| `BCOLOR_MAGENTA` | 洋红 | `\033[45m` |
| `BCOLOR_CYAN` | 青色 | `\033[46m` |
| `BCOLOR_WHITE` | 白色 | `\033[47m` |
| `BCOLOR_DEFAULT` | 默认 | `\033[49m` |

使用示例：
```cpp
tc::println(TCOLOR_BLACK, BCOLOR_YELLOW, "黑字黄底", TCOLOR_RESET);
```

### 字体样式

TC.hpp 支持多种字体样式：

| 宏名 | 效果 | ANSI代码 | 兼容性 |
|------|------|----------|--------|
| `TFONT_BOLD` | 粗体/加粗 | `\033[1m` | Windows完全支持，其他终端大多支持 |
| `TFONT_FAINT` | 微弱/淡色 | `\033[2m` | Windows完全支持，其他终端部分支持 |
| `TFONT_ITALIC` | 斜体 | `\033[3m` | Windows完全支持，其他终端部分支持 |
| `TFONT_UNDERLINE` | 下划线 | `\033[4m` | Windows完全支持，其他终端大多支持 |
| `TFONT_BLINK_SLOW` | 慢速闪烁 | `\033[5m` | Windows完全支持，其他终端部分支持 |
| `TFONT_BLINK_FAST` | 快速闪烁 | `\033[6m` | Windows完全支持，其他终端很少支持 |
| `TFONT_REVERSE` | 反色 | `\033[7m` | Windows完全支持，其他终端大多支持 |
| `TFONT_CONCEAL` | 隐藏 | `\033[8m` | Windows完全支持，其他终端很少支持 |
| `TFONT_CROSSED` | 删除线 | `\033[9m` | Windows完全支持，其他终端部分支持 |
| `TFONT_RESET` | 全部重置 | `\033[0m` | Windows完全支持，其他终端大多支持 |

使用示例：
```cpp
tc::println(TFONT_BOLD, "粗体文本", TFONT_RESET);
tc::println(TFONT_UNDERLINE, "下划线文本", TFONT_RESET);
```

### RGB颜色

TC.hpp 支持 RGB 颜色设置：

```cpp
tc::println(TCOLOR_RGB(255, 0, 0), "自定义红色", TCOLOR_RESET);
```

## 输出函数

### 标准输出

TC.hpp 提供了类似 Python 的 print/println 函数：

```cpp
// 多参数打印
tc::print("Hello", " ", "World");  // 输出: Hello World
tc::println("Hello", " ", "World"); // 输出: Hello World 并换行

// 带颜色的打印
tc::println(TCOLOR_GREEN, "绿色文本", TCOLOR_RESET);
```

### 链式输出

TC.hpp 提供了流式输出接口：

```cpp
// 流式输出
tc::tout << TCOLOR_BLUE << "蓝色文本" << TCOLOR_RESET << std::endl;

// 链式 Printer API
tc::printer()
    .moveCursor(10, 5)
    .print("在位置(10,5)打印")
    .moveCursor(10, 6)
    .println("下一行");
```

## 延时与等待

### 延时函数

TC.hpp 提供了多种延时函数：

```cpp
// 等待指定秒数（支持小数）
tc::wait(1.5);  // 等待1.5秒

// 等待指定毫秒
tc::tsleep(1000);  // 等待1000毫秒

// 流式延时
tc::tout << "等待前" << tc::tsleep(500) << "等待后" << std::endl;

// 延时流
tc::tsleep_stream << 1000;  // 等待1000毫秒
```

### 按键等待

TC.hpp 提供了等待按键的功能：

```cpp
// 等待任意按键
tc::waitKey();

// 等待特定按键
tc::waitKey('A');  // 等待按下A键
tc::waitKey(KEY_ESC);  // 等待按下ESC键
```

常用特殊按键宏：

| 宏名 | 按键 |
|------|------|
| `KEY_ESC` | ESC键 |
| `KEY_SPACE` | 空格键 |
| `KEY_ENTER` | 回车键 |
| `KEY_TAB` | Tab键 |
| `KEY_BACKSPACE` | 退格键 |
| `KEY_UP` | 上方向键 |
| `KEY_DOWN` | 下方向键 |
| `KEY_LEFT` | 左方向键 |
| `KEY_RIGHT` | 右方向键 |
| `KEY_F1` ~ `KEY_F12` | F1-F12功能键 |

## 终端控制

### 光标控制

TC.hpp 提供了光标控制功能：

```cpp
// 移动光标到指定位置
tc::printer().moveCursor(10, 5);  // 移动到第5行，第10列

// 隐藏/显示光标
tc::printer().hideCursor();
tc::printer().showCursor();

// 相对移动光标
tc::printer().moveCursor(tc::Printer::Direction::Up, 2);  // 上移2行
tc::printer().moveCursor(tc::Printer::Direction::Right, 5);  // 右移5列
```

### 终端尺寸

获取终端窗口大小：

```cpp
auto size = tc::printer().getSize();
tc::println("终端大小: ", size.first, "x", size.second);  // 宽x高
```

### 清屏功能

清除终端内容：

```cpp
tc::printer().clear();  // 清屏并将光标移到左上角
```

## 进度条

TC.hpp 提供了简单易用的进度条功能：

```cpp
// 创建进度条（宽度30，填充字符"█"，未填充字符"░"，绿色）
tc::ProgressBar bar(30, "█", "░", TCOLOR_GREEN);

// 显示进度（0.0-1.0之间）
for (int i = 0; i <= 100; ++i) {
    bar.show(i / 100.0, "处理中...");
    tc::wait(0.02);  // 模拟处理时间
}

// 完成进度条
bar.finish("完成！");
```

## 系统相关API

### 系统时间

TC.hpp 提供了获取系统时间的功能：

```cpp
// 获取当前年份
int year = tc::getSystemTime(SYS_YEAR);

// 获取当前月份
int month = tc::getSystemTime(SYS_MONTH);

// 获取Unix时间戳
int timestamp = tc::getSystemTime();  // 默认返回时间戳
```

时间宏定义：

| 宏名 | 返回值 |
|------|--------|
| `SYS_YEAR` | 年份 |
| `SYS_MONTH` | 月份(1-12) |
| `SYS_DAY` | 日期(1-31) |
| `SYS_HOUR` | 小时(0-23) |
| `SYS_MINUTE` | 分钟(0-59) |
| `SYS_SECOND` | 秒(0-59) |
| `SYS_TIMESTAMP` | Unix时间戳 |

### 系统命令

执行系统命令：

```cpp
// 执行系统命令
tc::systemConsole("echo Hello World");
```

### 系统检测

TC.hpp 提供了检测当前操作系统的功能：

```cpp
// 获取当前操作系统类型
int os = tc::systemCheck();

// 根据返回值判断系统类型
switch (os) {
    case OS_WINDOWSNT11:
        tc::println("Windows 11");
        break;
    case OS_LINUX:
        tc::println("Linux");
        break;
    // 其他系统类型...
}
```

主要系统类型宏：

| 宏名 | 系统类型 |
|------|----------|
| `OS_WINDOWSNT11` | Windows 11 |
| `OS_WINDOWSNT10` | Windows 10 |
| `OS_WINDOWSNT6` | Windows Vista/7/8/8.1 |
| `OS_LINUX` | Linux |
| `OS_ANDROID` | Android |
| `OS_MACOS` | macOS |
| `OS_IOS` | iOS |
| `OS_BSD` | BSD |
| `OS_UNIX` | Unix-like |

## 跨平台兼容性

TC.hpp 在不同平台上的实现方式：

- **Windows**: 使用 Windows Console API（Win32 API）实现终端控制功能，不使用ANSI转义序列
- **Linux/macOS**: 使用 ANSI 转义序列和 POSIX API

库会自动检测平台并使用适当的实现，无需用户手动配置。所有颜色、字体样式和终端控制功能在Windows平台上都能完全支持，因为它们直接使用了原生的Win32 API，而不依赖于终端对ANSI转义序列的支持。

## 使用示例

完整示例程序：

```cpp
#include "tc.hpp"

int main() {
    // 清屏
    tc::printer().clear();
    
    // 标题
    tc::println(TCOLOR_CYAN, TFONT_BOLD, "TC.hpp 功能演示", TCOLOR_RESET);
    tc::println();
    
    // 颜色演示
    tc::println("=== 颜色演示 ===");
    tc::println(TCOLOR_RED, "红色文本", TCOLOR_RESET);
    tc::println(TCOLOR_GREEN, "绿色文本", TCOLOR_RESET);
    tc::println(TCOLOR_BLUE, "蓝色文本", TCOLOR_RESET);
    tc::println(TCOLOR_YELLOW, BCOLOR_BLUE, "黄字蓝底", TCOLOR_RESET);
    tc::println(TCOLOR_RGB(255, 128, 0), "自定义橙色", TCOLOR_RESET);
    tc::println();
    
    // 字体样式演示
    tc::println("=== 字体样式演示 ===");
    tc::println(TFONT_BOLD, "粗体文本", TCOLOR_RESET);
    tc::println(TFONT_UNDERLINE, "下划线文本", TCOLOR_RESET);
    tc::println(TFONT_ITALIC, "斜体文本", TCOLOR_RESET);
    tc::println(TFONT_CROSSED, "删除线文本", TCOLOR_RESET);
    tc::println();
    
    // 进度条演示
    tc::println("=== 进度条演示 ===");
    tc::ProgressBar bar(30, "█", "░", TCOLOR_GREEN);
    for (int i = 0; i <= 100; i += 10) {
        bar.show(i / 100.0, "处理中...");
        tc::wait(0.2);
    }
    bar.finish("完成！");
    tc::println();
    
    // 系统信息演示
    tc::println("=== 系统信息 ===");
    int year = tc::getSystemTime(SYS_YEAR);
    int month = tc::getSystemTime(SYS_MONTH);
    int day = tc::getSystemTime(SYS_DAY);
    tc::println("当前日期: ", year, "-", month, "-", day);
    
    int os = tc::systemCheck();
    tc::print("当前系统: ");
    switch (os) {
        case OS_WINDOWSNT11: tc::println("Windows 11"); break;
        case OS_WINDOWSNT10: tc::println("Windows 10"); break;
        case OS_LINUX: tc::println("Linux"); break;
        case OS_MACOS: tc::println("macOS"); break;
        default: tc::println("其他系统");
    }
    
    tc::println("\n按任意键退出...");
    tc::waitKey();
    
    return 0;
}
```

---

本文档提供了 TC.hpp 库的主要功能概述。更多详细信息和高级用法，请参考源代码中的注释和示例。