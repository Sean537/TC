
# TC.hpp - ✨ Cross-platform Terminal Control Header Library

> 🚀 A modern C++17 terminal control library supporting color output, font styles, delay, progress bar, terminal control, cross-platform, header-only, and zero dependencies!

---

## ✨ Features

- 🖥️ Cross-platform: Windows / Unix-like terminals auto-adapt
- 🎨 Rich colors: Foreground, background, RGB, font styles
- 💡 Modern C++17, header-only, zero dependencies
- ⏱️ Delay and typewriter effect
- 📊 Progress bar, chainable API, terminal size/cursor control
- 🧩 Clean code style, easy to integrate

---

## 🚀 Quick Start

### 1. Include Header

```cpp
#include "tc.hpp"
```

### 2. Usage Example

```cpp
#include "tc.hpp"

int main() {
    // 🌈 Color & Style
    tc::tout << TCOLOR_GREEN << "Hello world!" << TCOLOR_RESET << std::endl;
    tc::tout << TFONT_BOLD << "Bold text" << TFONT_RESET << std::endl;
    tc::tout << TCOLOR_RGB(255,0,0) << "RGB Red" << TCOLOR_RESET << std::endl;

    // ⏱️ Delay output
    tc::tout << "Wait..." << std::endl;
    tc::tsleep(1000);
    tc::tout << "Done!" << std::endl;

    // 🖨️ Python-style print
    tc::print("Hello ", "world!\n");
    tc::println("Age: ", 25, ", Score: ", 95.5);

    // 🌈 Colorful print (multi-macro supported)
    tc::println(TCOLOR_RED, "Red text");
    tc::println(TCOLOR_GREEN, BCOLOR_YELLOW, "Green text, yellow background");
    tc::println(TCOLOR_BLUE, BCOLOR_WHITE, TFONT_BOLD, "Blue bold, white background");

    // 🖋️ Printer chainable API
    tc::printer()
        .moveCursor(10,5)
        .print("Move cursor to (10,5)")
        .println();

    // 📏 Terminal size
    auto size = tc::printer().getSize();
    tc::println("Terminal size: ", size.first, "x", size.second);

    // ⏳ Progress bar
    tc::ProgressBar bar(30, "█", "░", TCOLOR_GREEN);
    for (int i = 0; i <= 100; ++i) {
        bar.show(i / 100.0, "Processing...");
        tc::wait(0.02);
    }
    bar.finish();

    return 0;
}
```

---

## 🧩 Main APIs & Macros

### 🎨 Colors & Styles (global macros, use directly)

```cpp
// Foreground colors
TCOLOR_RED, TCOLOR_GREEN, TCOLOR_YELLOW, TCOLOR_BLUE, TCOLOR_MAGENTA, TCOLOR_CYAN, TCOLOR_WHITE, TCOLOR_RESET
// Background colors
BCOLOR_RED, BCOLOR_GREEN, BCOLOR_YELLOW, BCOLOR_BLUE, BCOLOR_MAGENTA, BCOLOR_CYAN, BCOLOR_WHITE, BCOLOR_DEFAULT
// Font styles
TFONT_BOLD, TFONT_FAINT, TFONT_ITALIC, TFONT_UNDERLINE, TFONT_BLINK_SLOW, TFONT_BLINK_FAST, TFONT_REVERSE, TFONT_CONCEAL, TFONT_CROSSED, TFONT_DEFAULT, TFONT_FRAKTUR, TFONT_DOUBLE_UNDERLINE, TFONT_NORMAL, TFONT_NOT_ITALIC, TFONT_NO_UNDERLINE, TFONT_NO_BLINK, TFONT_NO_REVERSE, TFONT_REVEAL, TFONT_NOT_CROSSED, TFONT_THICK, TFONT_RESET
// RGB
TCOLOR_RGB(r, g, b)
```

### Font Style Macros (TFONT_XXX)

| Macro Name                 | Effect             | ANSI Code     | Compatibility Notes |
|---------------------------|--------------------|---------------|--------------------|
| TFONT_BOLD                | Bold               | \033[1m      | Most terminals, Windows 10+ supported |
| TFONT_FAINT               | Faint/dim          | \033[2m      | Some terminals, limited on Windows 10+ |
| TFONT_ITALIC              | Italic             | \033[3m      | Some terminals, limited on Windows 10+ |
| TFONT_UNDERLINE           | Underline          | \033[4m      | Most terminals, Windows 10+ supported |
| TFONT_BLINK_SLOW          | Slow blink         | \033[5m      | Some terminals, limited on Windows 10+ |
| TFONT_BLINK_FAST          | Fast blink         | \033[6m      | Rarely supported, not on Windows 10+ |
| TFONT_REVERSE             | Reverse            | \033[7m      | Most terminals, Windows 10+ supported |
| TFONT_CONCEAL             | Conceal            | \033[8m      | Rarely supported, not on Windows 10+ |
| TFONT_CROSSED             | Strikethrough      | \033[9m      | Some terminals, limited on Windows 10+ |
| TFONT_DEFAULT             | Default font       | \033[10m     | Rarely supported, not on Windows 10+ |
| TFONT_FRAKTUR             | Fraktur font       | \033[20m     | Very rare, experimental |
| TFONT_DOUBLE_UNDERLINE    | Double underline/off bold | \033[21m | Some terminals, limited on Windows 10+ |
| TFONT_NORMAL              | Reset bold/faint   | \033[22m     | Most terminals, Windows 10+ supported |
| TFONT_NOT_ITALIC          | Not italic/Fraktur | \033[23m     | Some terminals, limited on Windows 10+ |
| TFONT_NO_UNDERLINE        | Not underlined     | \033[24m     | Most terminals, Windows 10+ supported |
| TFONT_NO_BLINK            | Not blinking       | \033[25m     | Rarely supported, not on Windows 10+ |
| TFONT_NO_REVERSE          | Not reversed       | \033[27m     | Most terminals, Windows 10+ supported |
| TFONT_REVEAL              | Reveal (not concealed) | \033[28m | Rarely supported, not on Windows 10+ |
| TFONT_NOT_CROSSED         | Not strikethrough  | \033[29m     | Some terminals, limited on Windows 10+ |
| TFONT_THICK               | Bold (alias)       | \033[1m      | Same as TFONT_BOLD |
| TFONT_RESET               | Reset all          | \033[0m      | Most terminals, Windows 10+ supported |

> ⚠️ **Compatibility Notes:**
> - Most Linux/macOS terminals (GNOME Terminal, iTerm2, Konsole, Alacritty, etc.) support common styles (bold, underline, reverse, some italic/strikethrough).
> - Windows 10+ native terminal supports most common styles (bold, underline, reverse), but italic, strikethrough, blink are limited.
> - Old Windows CMD/PowerShell support very few styles. Upgrade or use Windows Terminal is recommended.
> - TFONT_FRAKTUR, TFONT_DEFAULT, TFONT_DOUBLE_UNDERLINE are experimental/rarely supported.

Example: `tc::println(TCOLOR_RED, BCOLOR_YELLOW, TFONT_BOLD, "Red text, yellow background, bold")`

- `tc::tout`: stream output (supports color/style/delay)
- `tc::print(...)` / `tc::println(...)`: multi-argument print, supports color/style macros
- `tc::printer()`: chainable terminal control

### ⏱️ Delay & Wait

- `tc::tsleep(ms)` / `tc::tsleep_stream << ms`
- `tc::wait(seconds)`
- `tc::waitKey()`

### 📊 Progress Bar

- `tc::ProgressBar bar(width, doneChar, todoChar, color)`
- `bar.show(progress, msg)`
- `bar.finish()`

---

## 🛠️ Build

- Windows: `g++ -std=c++17 test.cpp -o test.exe`
- Linux/macOS: `g++ -std=c++17 -pthread test.cpp -o test`

---

## 📄 License

MIT

---

## 🌐 Contact

- 📥 Email: <wushaoquan666@outlook.com>
