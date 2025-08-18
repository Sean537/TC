# TC.hpp - ✨ 跨平台开发库

[![C++17](https://img.shields.io/badge/C%2B%2B-17%2B-blue.svg)](https://en.cppreference.com/w/cpp/compiler_support)
[![平台](https://img.shields.io/badge/平台-Windows%20%7C%20Linux%20%7C%20macOS-lightgrey.svg)]
[![Header-Only](https://img.shields.io/badge/Header--Only-Yes-green.svg)]
[![MIT License](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

> 🚀 一个现代化的 C++17 开发库，旨在用最简单的语法解决开发过程中会遇到的各种问题。目前功能包括终端彩色输出、延时、进度条、终端控制、系统信息检测、获取时间等，跨平台、零依赖、纯头文件！

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

    // ⏱️ 延时输出
    tc::tout << "Wait..." << std::endl;
    tc::tsleep(1000);
    tc::tout << "Done!" << std::endl;

    // 🖨️ Python风格打印
    tc::print("Hello ", "world!\n");
    tc::println("年龄: ", 25, ", 分数: ", 95.5);

    // 🌈 彩色打印（支持多参数宏）
    tc::println(TCOLOR_RED, "红色文本");
    tc::println(TCOLOR_GREEN, BCOLOR_YELLOW, "绿色文字，黄色背景");
    tc::println(TCOLOR_BLUE, BCOLOR_WHITE, TFONT_BOLD, "蓝色粗体，白色背景");

    // 🖋️ Printer链式API
    tc::printer()
        .moveCursor(10,5)
        .print("移动光标到(10,5)")
        .println();

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

    // 🖥️ 执行系统命令（如清屏）
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
    switch (os) {
        case OS_WINDOWSNT11:
            tc::println("当前系统: Windows 11");
            break;
        case OS_WINDOWSNT10:
            tc::println("当前系统: Windows 10");
            break;
        case OS_WINDOWSNT6:
            tc::println("当前系统: Windows Vista/7/8/8.1");
            break;
        case OS_LINUX:
            tc::println("当前系统: Linux");
            break;
        case OS_MACOS:
            tc::println("当前系统: macOS");
            break;
        case OS_BEOS:
            tc::println("当前系统: BeOS");
            break;
        case OS_OS2:
            tc::println("当前系统: OS/2");
            break;
        case OS_NEXTSTEP:
            tc::println("当前系统: NeXTSTEP");
            break;
        // ...有更多系统的支持
        default:
            tc::println("未知或其他系统, code=", os);
    }

    return 0;
}
```

---

## 🧩 主要API与宏

### 🎨 颜色与样式（全局宏，直接用）

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

- `tc::tout`：流式输出（支持颜色/样式/延时）
- `tc::print(...)` / `tc::println(...)`：多参数打印，支持颜色/样式宏
- `tc::printer()`：链式终端控制

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
- `tc::systemCheck()`：检测当前操作系统，返回下表宏之一

#### 支持的系统宏

| 宏名 | 说明 |
|------|------|
| OS_WINDOWSNT11 | Windows 11 及更高 |
| OS_WINDOWSNT10 | Windows 10 |
| OS_WINDOWSNT6  | Windows Vista/7/8/8.1 |
| OS_WINDOWSNT5  | Windows 2000/XP/2003 |
| OS_WINDOWSNT4  | Windows NT 4.x |
| OS_WINDOWSNT3  | Windows NT 3.x |
| OS_WIN95       | Windows 95 |
| OS_WIN98       | Windows 98 |
| OS_WINME       | Windows Me |
| OS_WINCE       | Windows CE |
| OS_WINDOWS     | 其他Windows |
| OS_LINUX       | Linux |
| OS_ANDROID     | Android |
| OS_MACOS       | macOS |
| OS_IOS         | iOS |
| OS_BSD         | BSD |
| OS_UNIX        | Unix-like |
| OS_DOS         | MS-DOS |
| OS_BEOS        | BeOS |
| OS_HAIKU       | Haiku |
| OS_AIX         | IBM AIX |
| OS_SOLARIS     | Solaris |
| OS_MINIX       | Minix |
| OS_QNX         | QNX |
| OS_VMS         | VMS/OpenVMS |
| OS_AMIGAOS     | AmigaOS |
| OS_MORPHOS     | MorphOS |
| OS_FREEMINT    | FreeMiNT |
| OS_HPUX        | HP-UX |
| OS_IRIX        | SGI IRIX |
| OS_SCO         | SCO UnixWare/OpenServer |
| OS_OPENVMS     | OpenVMS |
| OS_RISCOS      | RISC OS |
| OS_OS2         | IBM OS/2 |
| OS_NEXTSTEP    | NeXTSTEP |
| OS_UNKNOWN     | 未知/其他 |

#### 用法示例

```cpp
int os = tc::systemCheck();
switch (os) {
    case OS_WINDOWSNT11: tc::println("Windows 11"); break;
    case OS_LINUX: tc::println("Linux"); break;
    // ... 其他系统 ...
    default: tc::println("未知系统, code=", os);
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

### ⌨️ waitKey

- `tc::waitKey()`：等待任意按键
- `tc::waitKey(char key)` / `tc::waitKey(int key)`：等待特定按键（如 tc::waitKey('A')、tc::waitKey(KEY_ESC)）

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

```cpp
tc::waitKey(); // 等待任意键
// 等待按下A键
tc::waitKey('A');
// 等待ESC键
tc::waitKey(KEY_ESC);
```

---

## 🛠️ 编译

- Windows: `g++ -std=c++17 test.cpp -o test.exe`
- Linux/macOS: `g++ -std=c++17 -pthread test.cpp -o test`

---

## 📄 协议

MIT

---

## 🌐 联系

- 📥 电子邮件：<wushaoquan666@outlook.com>
