# TC.hpp - ✨ 跨平台终端控制头文件库

[![C++17](https://img.shields.io/badge/C%2B%2B-17%2B-blue.svg)](https://en.cppreference.com/w/cpp/compiler_support)
[![平台](https://img.shields.io/badge/平台-Windows%20%7C%20Linux%20%7C%20macOS-lightgrey.svg)](#)
[![Header-Only](https://img.shields.io/badge/Header--Only-Yes-green.svg)](#)
[![MIT License](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

> 🚀 一个现代化的 C++17 终端控制库，支持彩色输出、字体样式、延时、进度条、终端控制等，跨平台、零依赖、纯头文件！

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

| 宏名                      | 效果             | ANSI码        | 兼容性说明 |
|---------------------------|------------------|---------------|------------|
| TFONT_BOLD                | 粗体/加粗        | \033[1m      | 大多数终端支持，Windows 10+ 支持 |
| TFONT_FAINT               | 微弱/淡色        | \033[2m      | 部分终端支持，Windows 10+ 支持有限 |
| TFONT_ITALIC              | 斜体             | \033[3m      | 部分终端支持，Windows 10+ 支持有限 |
| TFONT_UNDERLINE           | 下划线           | \033[4m      | 大多数终端支持，Windows 10+ 支持 |
| TFONT_BLINK_SLOW          | 慢速闪烁         | \033[5m      | 部分终端支持，Windows 10+ 支持有限 |
| TFONT_BLINK_FAST          | 快速闪烁         | \033[6m      | 很少终端支持，Windows 10+ 基本不支持 |
| TFONT_REVERSE             | 反色             | \033[7m      | 大多数终端支持，Windows 10+ 支持 |
| TFONT_CONCEAL             | 隐藏             | \033[8m      | 很少终端支持，Windows 10+ 基本不支持 |
| TFONT_CROSSED             | 删除线           | \033[9m      | 部分终端支持，Windows 10+ 支持有限 |
| TFONT_DEFAULT             | 默认字体         | \033[10m     | 很少终端支持，Windows 10+ 不支持 |
| TFONT_FRAKTUR             | Fraktur字体      | \033[20m     | 极少终端支持，实验性 |
| TFONT_DOUBLE_UNDERLINE    | 双下划线/粗体关闭| \033[21m     | 部分终端支持，Windows 10+ 支持有限 |
| TFONT_NORMAL              | 粗体/淡色关闭    | \033[22m     | 大多数终端支持，Windows 10+ 支持 |
| TFONT_NOT_ITALIC          | 关闭斜体/Fraktur | \033[23m     | 部分终端支持，Windows 10+ 支持有限 |
| TFONT_NO_UNDERLINE        | 关闭下划线       | \033[24m     | 大多数终端支持，Windows 10+ 支持 |
| TFONT_NO_BLINK            | 关闭闪烁         | \033[25m     | 很少终端支持，Windows 10+ 基本不支持 |
| TFONT_NO_REVERSE          | 关闭反色         | \033[27m     | 大多数终端支持，Windows 10+ 支持 |
| TFONT_REVEAL              | 关闭隐藏         | \033[28m     | 很少终端支持，Windows 10+ 基本不支持 |
| TFONT_NOT_CROSSED         | 关闭删除线       | \033[29m     | 部分终端支持，Windows 10+ 支持有限 |
| TFONT_THICK               | 粗体（别名）     | \033[1m      | 同TFONT_BOLD |
| TFONT_RESET               | 全部重置         | \033[0m      | 大多数终端支持，Windows 10+ 支持 |

> ⚠️ **兼容性说明**：
> - Linux/macOS 下主流终端（如 GNOME Terminal、iTerm2、Konsole、Alacritty 等）大多支持常用样式（粗体、下划线、反色、部分斜体/删除线）。
> - Windows 10 及以上原生终端支持大部分常用样式（粗体、下划线、反色），但对斜体、删除线、闪烁等支持有限。
> - 旧版 Windows CMD/PowerShell 仅支持极少数样式，建议升级或使用 Windows Terminal。
> - TFONT_FRAKTUR、TFONT_DEFAULT、TFONT_DOUBLE_UNDERLINE 等为扩展/实验性样式，极少终端支持。

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

