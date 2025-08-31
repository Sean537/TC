# TC.hpp - ✨ 跨平台终端控制头文件库

[![C++17](https://img.shields.io/badge/C%2B%2B-17%2B-blue.svg)](https://en.cppreference.com/w/cpp/compiler_support)
![平台](https://img.shields.io/badge/平台-Windows%20%7C%20Linux%20%7C%20macOS-lightgrey.svg)
![Header-Only](https://img.shields.io/badge/Header--Only-Yes-green.svg)
[![MIT License](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

> 🚀 一个现代化的 C++17 终端控制库，旨在用最简单的语法解决开发过程中会遇到的各种问题。目前功能包括终端彩色输出、延时、进度条、基础控制、系统信息检测、获取时间等，跨平台、零依赖、纯头文件！

---

## ✨ 主要特性

- 🖥️ 跨平台：Windows/类Unix终端自动适配
- 🎨 丰富色彩：支持前景色、背景色、RGB、字体样式
- 💡 现代C++17，纯头文件，零依赖
- ⏱️ 延时与打字机特效
- 📊 进度条、链式API、终端尺寸/光标控制
- 🧩 代码风格简洁，易于集成

---

## 🚀 快速上手

### 1. 引入头文件

```cpp
#include "tc.hpp"
```

### 2. 主要用法示例

```cpp
#include "tc.hpp"

int main() {
    // 🌈 颜色与样式
    tc::tout << TCOLOR_GREEN << "Hello world!" << TCOLOR_RESET << std::endl;
    tc::tout << TFONT_BOLD << "粗体文本" << TFONT_RESET << std::endl;
    tc::tout << TCOLOR_RGB(255,0,0) << "RGB红" << TCOLOR_RESET << std::endl;
    std::cout << tc::red("红色文本") << std::endl;

    // ⏱️ 延时输出
    tc::tout << "Wait..." << std::endl;
    tc::tsleep(1000);
    tc::tout << "Done!" << std::endl;

    // 🖨️ Python风格打印
    tc::print("Hello ", "world!\n");
    tc::println("年龄: ", 25, ", 分数: ", 95.5);
    tc::println(TCOLOR_RED, "红色文本");
    tc::println(TCOLOR_GREEN, BCOLOR_YELLOW, "绿色文字，黄色背景");
    tc::println(TCOLOR_BLUE, BCOLOR_WHITE, TFONT_BOLD, "蓝色粗体，白色背景");

    // 🖋️ Printer链式API
    tc::printer()
        .clear()    // 清屏
        .moveCursor(10,5)
        .print("移动光标到(10,5)")
        .hideCursor()   // 隐藏光标
        .moveCursor(tc::Printer::Direction::Down, 2) // 相对移动（向下2行）
        .println("在(10,7)")
        .println() // 换行
        .showCursor();  // 显示光标

    // 📏 终端尺寸
    auto size = tc::printer().getSize();
    tc::println("终端大小: ", size.first, "x", size.second);

    // ⏳ 进度条
    tc::ProgressBar bar(30, "█", "░", TCOLOR_GREEN);
    for (int i = 0; i <= 100; ++i) {
        bar.show(i / 100.0, "处理中...");
        tc::wait(0.02);
    }
    bar.finish();

    // 🖥️ 执行系统命令
    tc::systemConsole("echo TC systemConsole test");

    // 🕒 获取系统时间
    int year = tc::getSystemTime(SYS_YEAR);
    int month = tc::getSystemTime(SYS_MONTH);
    int day = tc::getSystemTime(SYS_DAY);
    int hour = tc::getSystemTime(SYS_HOUR);
    int minute = tc::getSystemTime(SYS_MINUTE);
    int second = tc::getSystemTime(SYS_SECOND);
    int timestamp = tc::getSystemTime(); // 默认Unix时间戳
    tc::println("当前时间: ", year, "-", month, "-", day, " ", hour, ":", minute, ":", second, " (Unix: ", timestamp, ")");

    // 🛡️ 检查系统环境
    int os = tc::systemCheck();
    const char* osName = tc::getOSName(os);
    std::string osVersionInfo = tc::getOSVersionInfo();

    tc::println("当前系统: ", osName);
    tc::println("系统版本: ", osVersionInfo);

    return 0;
}
```

---

## 🧩 主要API与宏

### 🎨 颜色与样式

#### 全局颜色宏（直接用）

```cpp
// 前景色
TCOLOR_RED, TCOLOR_GREEN, TCOLOR_YELLOW, TCOLOR_BLUE, TCOLOR_MAGENTA, TCOLOR_CYAN, TCOLOR_WHITE, TCOLOR_RESET
// 背景色
BCOLOR_RED, BCOLOR_GREEN, BCOLOR_YELLOW, BCOLOR_BLUE, BCOLOR_MAGENTA, BCOLOR_CYAN, BCOLOR_WHITE, BCOLOR_DEFAULT
// 字体样式
TFONT_BOLD, TFONT_FAINT, TFONT_ITALIC, TFONT_UNDERLINE, TFONT_BLINK_SLOW, TFONT_BLINK_FAST, TFONT_REVERSE, TFONT_CONCEAL, TFONT_CROSSED, TFONT_DEFAULT, TFONT_FRAKTUR, TFONT_DOUBLE_UNDERLINE, TFONT_NORMAL, TFONT_NOT_ITALIC, TFONT_NO_UNDERLINE, TFONT_NO_BLINK, TFONT_NO_REVERSE, TFONT_REVEAL, TFONT_NOT_CROSSED, TFONT_THICK, TFONT_RESET
// RGB
TCOLOR_RGB(r, g, b)
```

#### 颜色控制类（ColorController）

```cpp
// 设置颜色
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

#### 便捷颜色函数

> ⚠ 注意：便捷颜色函数本质上是在字符串头尾添加 ANSI 转义序列，最好不要在输出上滥用，并且部分终端不支持 ANSI 转移序列。想要做文本带颜色输出，推荐移步其它方法。

```cpp
// 基本颜色函数
std::string coloredText = tc::colorize("彩色文本", tc::ColorController::Color::CYAN);
std::cout << coloredText << std::endl;

// RGB颜色函数
std::string rgbText = tc::colorizeRGB("RGB颜色文本", 255, 128, 0);
std::cout << rgbText << std::endl;

// 标准颜色函数
std::cout << tc::red("红色文本") << std::endl;
std::cout << tc::green("绿色文本") << std::endl;
std::cout << tc::blue("蓝色文本") << std::endl;
std::cout << tc::yellow("黄色文本") << std::endl;
std::cout << tc::cyan("青色文本") << std::endl;
std::cout << tc::magenta("洋红色文本") << std::endl;
std::cout << tc::white("白色文本") << std::endl;

// 亮色函数
std::cout << tc::brightRed("亮红色文本") << std::endl;
std::cout << tc::brightGreen("亮绿色文本") << std::endl;
std::cout << tc::brightBlue("亮蓝色文本") << std::endl;
std::cout << tc::brightYellow("亮黄色文本") << std::endl;
```

### 字体样式宏（TFONT_XXX）

| 宏名                      | 效果             | 兼容性说明 |
|---------------------------|------------------|------------|
| TFONT_BOLD                | 粗体/加粗        | 所有平台完全支持 |
| TFONT_FAINT               | 微弱/淡色        | Windows完全支持，其他终端部分支持 |
| TFONT_ITALIC              | 斜体             | Windows完全支持，其他终端部分支持 |
| TFONT_UNDERLINE           | 下划线           | 所有平台完全支持 |
| TFONT_BLINK_SLOW          | 慢速闪烁         | Windows完全支持，其他终端部分支持 |
| TFONT_BLINK_FAST          | 快速闪烁         | Windows完全支持，其他终端很少支持 |
| TFONT_REVERSE             | 反色             | 所有平台完全支持 |
| TFONT_CONCEAL             | 隐藏             | Windows完全支持，其他终端很少支持 |
| TFONT_CROSSED             | 删除线           | Windows完全支持，其他终端部分支持 |
| TFONT_DEFAULT             | 默认字体         | Windows完全支持，其他终端很少支持 |
| TFONT_FRAKTUR             | Fraktur字体      | Windows完全支持，其他终端极少支持 |
| TFONT_DOUBLE_UNDERLINE    | 双下划线/粗体关闭| Windows完全支持，其他终端部分支持 |
| TFONT_NORMAL              | 粗体/淡色关闭    | 所有平台完全支持 |
| TFONT_NOT_ITALIC          | 关闭斜体/Fraktur | Windows完全支持，其他终端部分支持 |
| TFONT_NO_UNDERLINE        | 关闭下划线       | 所有平台完全支持 |
| TFONT_NO_BLINK            | 关闭闪烁         | Windows完全支持，其他终端很少支持 |
| TFONT_NO_REVERSE          | 关闭反色         | 所有平台完全支持 |
| TFONT_REVEAL              | 关闭隐藏         | Windows完全支持，其他终端很少支持 |
| TFONT_NOT_CROSSED         | 关闭删除线       | Windows完全支持，其他终端部分支持 |
| TFONT_THICK               | 粗体（别名）     | 同TFONT_BOLD |
| TFONT_RESET               | 全部重置         | 所有平台完全支持 |

> ⚠️ **兼容性说明**：
>
> - TC.hpp 在 Windows 平台上使用 Windows Console API（Win32 API）实现终端控制功能，而不使用 ANSI 转义序列，因此所有字体样式在 Windows 平台上都能完全支持，不受终端对 ANSI 转义序列支持程度的限制。
> - Linux/macOS 下使用 ANSI 转义序列实现，主流终端（如 GNOME Terminal、iTerm2、Konsole、Alacritty 等）大多支持常用样式（粗体、下划线、反色、部分斜体/删除线）。
> - TFONT_FRAKTUR、TFONT_DEFAULT、TFONT_DOUBLE_UNDERLINE 等为扩展/实验性样式，在非 Windows 平台上支持度较低。

用法示例：`tc::println(TCOLOR_RED, BCOLOR_YELLOW, TFONT_BOLD, "红字黄底粗体")`

### 🖥️ 终端控制

#### tc::terminal命名空间

```cpp
// 清空屏幕
tc::terminal::clear();

// 移动光标到指定位置
tc::terminal::moveCursor(10, 5);
std::cout << "这是位置(10,5)" << std::endl;

// 获取终端大小
auto [width, height] = tc::terminal::getSize();
std::cout << "终端大小: " << width << "x" << height << std::endl;
```

#### tc::Printer链式类

```cpp
// 创建Printer对象并执行一系列操作
tc::printer()
    .clear()                                  // 清屏
    .hideCursor()                             // 隐藏光标
    .moveCursor(10, 5)                        // 移动到绝对位置
    .println("这是位置(10,5)")                 // 打印并换行
    .moveCursor(tc::Printer::Direction::Down, 2) // 相对移动（向下2行）
    .println("向下移动了2行")
    .moveCursor(1, 10)                        // 移动到第10行开头
    .print("在第10行: ")                       // 打印不换行
    .print("继续在同一行打印")
    .println()                                // 换行
    .showCursor();                            // 显示光标
```

### 🔤 输出与打印

- `tc::tout`：流式输出（支持颜色/样式/延时）
- `tc::print(...)` / `tc::println(...)`：多参数打印，支持颜色/样式宏

### ⏱️ 延时与等待

- `tc::tsleep(ms)` / `tc::tsleep_stream << ms`
- `tc::wait(seconds)`
- `tc::waitKey()`

### 📊 进度条

- `tc::ProgressBar bar(width, doneChar, todoChar, color)`
- `bar.show(progress, msg)`
- `bar.finish()`

### 🖥️ 系统相关API

- `tc::getSystemTime(int type = SYS_TIMESTAMP)`：获取当前时间（年、月、日、时、分、秒、Unix时间戳）
- `tc::systemConsole(const char* 或 std::string)`：执行系统命令
- `tc::systemConsoleW(const wchar_t*)`：执行系统命令（宽字符版本，仅Windows平台可用，支持Unicode命令）
- `tc::systemCheck()`：检测当前操作系统，返回操作系统代码
- `tc::getOSName(int osCode)`：根据操作系统代码返回操作系统名称
- `tc::getOSVersionInfo()`：获取当前操作系统的详细版本信息

#### 支持的系统宏

| 类别 | 宏名 | 说明 |
|------|------|------|
| **Windows系列** | OS_WINDOWS | 通用Windows标识 |
| | OS_WINDOWSNT6 | Windows 7/8/8.1 (NT 6.x) |
| | OS_WINDOWSNT10 | Windows 10 (NT 10.0) |
| | OS_WINDOWSNT11 | Windows 11 (NT 10.0 build 22000+) |
| **Linux发行版** | OS_LINUX | 通用Linux标识 |
| | OS_UBUNTU | Ubuntu Linux |
| | OS_DEBIAN | Debian Linux |
| | OS_FEDORA | Fedora Linux |
| | OS_CENTOS | CentOS Linux |
| | OS_REDHAT | Red Hat Enterprise Linux |
| | OS_SUSE | SUSE/openSUSE Linux |
| | OS_ARCH | Arch Linux |
| | OS_GENTOO | Gentoo Linux |
| | OS_SLACKWARE | Slackware Linux |
| | OS_ANDROID | Android (基于Linux) |
| | OS_KALI | Kali Linux |
| | OS_MINT | Linux Mint |
| | OS_MANJARO | Manjaro Linux |
| | OS_ALPINE | Alpine Linux |
| | OS_RASPBIAN | Raspbian |
| | OS_DEEPIN | Deepin Linux |
| | OS_ELEMENTARY | Elementary OS |
| | OS_ZORIN | Zorin OS |
| | OS_POPOS | Pop!_OS |
| | OS_CHROMEOS | Chrome OS/Chromium OS |
| **Apple操作系统** | OS_MACOS | 通用macOS标识 |
| | OS_MACOS_HIGHSIERRA | macOS 10.13 High Sierra (2017) |
| | OS_MACOS_MOJAVE | macOS 10.14 Mojave (2018) |
| | OS_MACOS_CATALINA | macOS 10.15 Catalina (2019) |
| | OS_MACOS_BIGSUR | macOS 11 Big Sur (2020) |
| | OS_MACOS_MONTEREY | macOS 12 Monterey (2021) |
| | OS_MACOS_VENTURA | macOS 13 Ventura (2022) |
| | OS_MACOS_SONOMA | macOS 14 Sonoma (2023) |
| | OS_MACOS_SEQUOIA | macOS 15 Sequoia (2024) |
| | OS_MACOS_TAHOE | macOS 26 Tahoe (2025) |
| **其他Apple操作系统** | OS_IOS | iOS (iPhone/iPod touch) |
| | OS_IPADOS | iPadOS (iPad) |
| | OS_WATCHOS | watchOS (Apple Watch) |
| | OS_TVOS | tvOS (Apple TV) |
| | OS_VISIONOS | visionOS (Apple Vision Pro) |
| | OS_BRIDGEOS | bridgeOS (Apple T2芯片) |
| | OS_AUDIOOS | audioOS (HomePod) |
| **BSD系列** | OS_BSD | 通用BSD标识 |
| | OS_FREEBSD | FreeBSD |
| **Unix系列** | OS_UNIX | 通用Unix标识 |
| **新兴操作系统** | OS_FUCHSIA | Google Fuchsia |
| | OS_HARMONYOS | Harmony OS |
| **其它操作系统** | OS_REACTOS | ReactOS |
| **未知操作系统** | OS_UNKNOWN | 无法识别的操作系统 |

#### 用法示例

```cpp
// 获取系统信息
int osCode = tc::systemCheck();
const char* osName = tc::getOSName(osCode);
std::string osVersionInfo = tc::getOSVersionInfo();

// 显示系统信息
tc::println("操作系统: ", osName);
tc::println("系统版本: ", osVersionInfo);

// 根据系统类型执行不同操作
switch (osCode) {
    case OS_WINDOWSNT11:
        tc::println("Windows 11系统特定操作");
        break;
    case OS_UBUNTU:
        tc::println("Ubuntu系统特定操作");
        break;
    case OS_MACOS:
        tc::println("macOS系统特定操作");
        break;
    // ... 其他系统 ...
    default:
        tc::println("未知系统操作");
}
```

### ⏱️ 获取系统时间

| 宏名 | 说明 |
|------|------|
| SYS_YEAR      | 年 |
| SYS_MONTH     | 月 |
| SYS_DAY       | 日 |
| SYS_HOUR      | 时 |
| SYS_MINUTE    | 分 |
| SYS_SECOND    | 秒 |
| SYS_TIMESTAMP | Unix时间戳（默认） |

```cpp
int year = tc::getSystemTime(SYS_YEAR);
int timestamp = tc::getSystemTime(); // Unix时间戳
```

### ⌨️ 按键处理

#### waitKey - 等待按键

- `tc::waitKey()`：等待任意按键
- `tc::waitKey(char key)` / `tc::waitKey(int key)`：等待特定按键（如 tc::waitKey('A')、tc::waitKey(KEY_ESC)）

```cpp
tc::waitKey(); // 等待任意键
// 等待按下A键
tc::waitKey('A');
// 等待ESC键
tc::waitKey(KEY_ESC);
```

#### isKeyPressed - 检测按键状态

- `tc::isKeyPressed(char key)` / `tc::isKeyPressed(int key)`：检测指定按键是否被按下

```cpp
// 检测ESC键是否被按下
if (tc::isKeyPressed(KEY_ESC)) {
    std::cout << "ESC键被按下" << std::endl;
}

// 检测方向键
if (tc::isKeyPressed(KEY_UP)) {
    std::cout << "上方向键被按下" << std::endl;
}

// 检测字母键
if (tc::isKeyPressed('A') || tc::isKeyPressed('a')) {
    std::cout << "A键被按下" << std::endl;
}
```

#### 常用特殊按键宏

| 宏名 | 说明 |
|------|------|
| KEY_ESC      | ESC |
| KEY_SPACE    | 空格 |
| KEY_ENTER    | 回车 |
| KEY_TAB      | Tab |
| KEY_BACKSPACE| 退格 |
| KEY_INSERT   | Insert |
| KEY_DELETE   | Delete |
| KEY_HOME     | Home |
| KEY_END      | End |
| KEY_PAGEUP   | PageUp |
| KEY_PAGEDOWN | PageDown |
| KEY_UP       | 上方向键 |
| KEY_DOWN     | 下方向键 |
| KEY_LEFT     | 左方向键 |
| KEY_RIGHT    | 右方向键 |
| KEY_F1 ~ KEY_F12 | F1~F12 功能键 |

---

## 🛠️ 编译

- Windows: `g++ -std=c++17 test.cpp -o test.exe`
- Linux/macOS: `g++ -std=c++17 -pthread test.cpp -o test`

如果安装了构建工具 [xmake](https://xmake.io/)，可以使用命令 `xmake -a` 一键构建所有 example，输出的可执行文件位于 `bin/examples` 下。

---

## 📄 协议

MIT

---

## 🌐 联系

- 📥 电子邮件：<wushaoquan666@outlook.com>
