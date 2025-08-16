# TC.hpp 快速入门指南

> TC.hpp 是一个现代化的 C++17 终端控制库，支持彩色输出、字体样式、延时、进度条、终端控制等，跨平台、零依赖、纯头文件。

## 目录

- [安装](#安装)
- [基本用法](#基本用法)
- [颜色输出](#颜色输出)
- [字体样式](#字体样式)
- [延时与等待](#延时与等待)
- [进度条](#进度条)
- [终端控制](#终端控制)
- [系统相关功能](#系统相关功能)
- [编译说明](#编译说明)
- [常见问题](#常见问题)

## 安装

TC.hpp 是一个纯头文件库，无需安装，只需将 `tc.hpp` 文件复制到您的项目中，然后包含它即可：

```cpp
#include "tc.hpp"
```

## 基本用法

### 标准输出

TC.hpp 提供了类似 Python 的 print/println 函数：

```cpp
// 多参数打印
tc::print("Hello", " ", "World");  // 输出: Hello World
tc::println("Hello", " ", "World"); // 输出: Hello World 并换行

// 打印不同类型的值
tc::println("年龄: ", 25, ", 分数: ", 95.5);
```

### 流式输出

TC.hpp 还提供了流式输出接口：

```cpp
// 流式输出
tc::tout << "Hello World" << std::endl;
```

## 颜色输出

### 使用颜色宏

```cpp
// 红色文本
tc::println(TCOLOR_RED, "红色文本", TCOLOR_RESET);

// 绿色文本，黄色背景
tc::println(TCOLOR_GREEN, BCOLOR_YELLOW, "绿色文字，黄色背景", TCOLOR_RESET);

// 蓝色粗体，白色背景
tc::println(TCOLOR_BLUE, BCOLOR_WHITE, TFONT_BOLD, "蓝色粗体，白色背景", TCOLOR_RESET);
```

### 流式颜色输出

```cpp
tc::tout << TCOLOR_RED << "红色文本" << TCOLOR_RESET << std::endl;
```

### RGB 颜色

```cpp
tc::println(TCOLOR_RGB(255, 0, 0), "自定义红色", TCOLOR_RESET);
tc::tout << TCOLOR_RGB(0, 255, 0) << "自定义绿色" << TCOLOR_RESET << std::endl;
```

## 字体样式

```cpp
// 粗体
tc::println(TFONT_BOLD, "粗体文本", TFONT_RESET);

// 下划线
tc::println(TFONT_UNDERLINE, "下划线文本", TFONT_RESET);

// 斜体
tc::println(TFONT_ITALIC, "斜体文本", TFONT_RESET);

// 删除线
tc::println(TFONT_CROSSED, "删除线文本", TFONT_RESET);

// 组合样式
tc::println(TFONT_BOLD, TFONT_UNDERLINE, "粗体下划线文本", TFONT_RESET);
```

## 延时与等待

### 延时函数

```cpp
// 等待指定秒数（支持小数）
tc::wait(1.5);  // 等待1.5秒

// 等待指定毫秒
tc::tsleep(1000).execute();  // 等待1000毫秒

// 流式延时
tc::tout << "等待前" << tc::tsleep(500) << "等待后" << std::endl;

// 延时流
tc::tsleep_stream << 1000;  // 等待1000毫秒
```

### 按键等待

```cpp
// 等待任意按键
tc::println("按任意键继续...");
tc::waitKey();

// 等待特定按键
tc::println("按 A 键继续...");
tc::waitKey('A');

// 等待ESC键
tc::println("按 ESC 键退出...");
tc::waitKey(KEY_ESC);
```

## 进度条

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

## 终端控制

### 光标控制

```cpp
// 清屏
tc::printer().clear();

// 移动光标到指定位置
tc::printer().moveCursor(10, 5);  // 移动到第5行，第10列
tc::println("在位置(10,5)打印");

// 隐藏/显示光标
tc::printer().hideCursor();
tc::wait(1.0);  // 光标隐藏1秒
tc::printer().showCursor();

// 相对移动光标
tc::printer().moveCursor(tc::Printer::Direction::Up, 2);  // 上移2行
tc::printer().moveCursor(tc::Printer::Direction::Right, 5);  // 右移5列
```

### 终端尺寸

```cpp
// 获取终端窗口大小
auto size = tc::printer().getSize();
tc::println("终端大小: ", size.first, "x", size.second);  // 宽x高
```

## 系统相关功能

### 系统时间

```cpp
// 获取当前年份
int year = tc::getSystemTime(SYS_YEAR);

// 获取当前月份
int month = tc::getSystemTime(SYS_MONTH);

// 获取当前日期
int day = tc::getSystemTime(SYS_DAY);

// 获取当前时间
tc::println("当前日期: ", 
    tc::getSystemTime(SYS_YEAR), "-", 
    tc::getSystemTime(SYS_MONTH), "-", 
    tc::getSystemTime(SYS_DAY), " ", 
    tc::getSystemTime(SYS_HOUR), ":", 
    tc::getSystemTime(SYS_MINUTE), ":", 
    tc::getSystemTime(SYS_SECOND));

// 获取Unix时间戳
int timestamp = tc::getSystemTime();  // 默认返回时间戳
tc::println("Unix时间戳: ", timestamp);
```

### 系统命令

```cpp
// 执行系统命令
tc::systemConsole("echo Hello World");
```

### 系统检测

```cpp
// 获取当前操作系统类型
int os = tc::systemCheck();

// 根据返回值判断系统类型
switch (os) {
    case OS_WINDOWSNT11:
        tc::println("Windows 11");
        break;
    case OS_WINDOWSNT10:
        tc::println("Windows 10");
        break;
    case OS_LINUX:
        tc::println("Linux");
        break;
    case OS_MACOS:
        tc::println("macOS");
        break;
    default:
        tc::println("其他系统, code=", os);
}
```

## 编译说明

TC.hpp 需要 C++17 或更高版本的编译器支持。

### Windows

```bash
g++ -std=c++17 your_program.cpp -o your_program.exe
```

### Linux/macOS

```bash
g++ -std=c++17 -pthread your_program.cpp -o your_program
```

## 常见问题

### 1. Windows 下颜色显示问题

TC.hpp 在 Windows 平台上使用 Windows Console API（Win32 API）实现终端控制功能，而不使用 ANSI 转义序列，因此能够在所有 Windows 版本上正常工作，包括旧版 CMD。如果您遇到颜色显示问题，请确保您的终端支持彩色输出。

### 2. 某些字体样式不生效

不同终端对 ANSI 转义序列的支持程度不同。例如，斜体、删除线等在某些终端可能不受支持。请参考 [ANSI 转义码参考](ansi_code_reference.md) 了解兼容性详情。

### 3. 编译错误

确保您的编译器支持 C++17 标准，并且正确包含了 tc.hpp 文件。

### 4. 在 Linux/macOS 下编译时出现线程相关错误

在 Linux/macOS 下编译时，需要添加 `-pthread` 选项以支持线程功能：

```bash
g++ -std=c++17 -pthread your_program.cpp -o your_program
```

---

更多详细信息，请参考：
- [TC.hpp 功能文档](tc_functionality.md)
- [TC.hpp API 参考手册](tc_api_reference.md)
- [ANSI 转义码参考](ansi_code_reference.md)