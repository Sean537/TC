# TC.hpp - ✨ Cross-Platform Terminal Control Header Library

[![C++17](https://img.shields.io/badge/C%2B%2B-17%2B-blue.svg)](https://en.cppreference.com/w/cpp/compiler_support)
[![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux%20%7C%20macOS-lightgrey.svg)]
[![Header-Only](https://img.shields.io/badge/Header--Only-Yes-green.svg)]
[![MIT License](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

> 🚀 A modern C++17 terminal control library supporting color output, font styles, delay, progress bar, terminal control, cross-platform, header-only, and zero dependencies!

---

## ✨ Features

- 🖥️ Cross-platform: Auto-adapts to Windows/Unix-like terminals
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

### 2. Main Usage Example

```cpp
#include "tc.hpp"

int main() {
    // 🌈 Color & Style
    tc::tout << TCOLOR_GREEN << "Hello world!" << TCOLOR_RESET << std::endl;
    tc::tout << TFONT_BOLD << "Bold text" << TFONT_RESET << std::endl;
    tc::tout << TCOLOR_RGB(255,0,0) << "RGB Red" << TCOLOR_RESET << std::endl;

    // ⏱️ Delayed output
    tc::tout << "Wait..." << std::endl;
    tc::tsleep(1000);
    tc::tout << "Done!" << std::endl;

    // 🖨️ Python-style print
    tc::print("Hello ", "world!\n");
    tc::println("Age: ", 25, ", Score: ", 95.5);

    // 🌈 Color print (multi-macro supported)
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

    // 🖥️ Run system command (e.g. clear screen)
    tc::systemConsole("echo TC systemConsole test");

    // 🕒 Get system time
    int year = tc::getSystemTime(SYS_YEAR);
    int month = tc::getSystemTime(SYS_MONTH);
    int day = tc::getSystemTime(SYS_DAY);
    int hour = tc::getSystemTime(SYS_HOUR);
    int minute = tc::getSystemTime(SYS_MINUTE);
    int second = tc::getSystemTime(SYS_SECOND);
    int timestamp = tc::getSystemTime(); // Unix timestamp by default
    tc::println("Current time: ", year, "-", month, "-", day, " ", hour, ":", minute, ":", second, " (Unix: ", timestamp, ")");

    // 🛡️ Detect system environment
    int os = tc::systemCheck();
    switch (os) {
    case OS_WINDOWSNT11:
        tc::println("System: Windows 11");
        break;
    case OS_WINDOWSNT10:
        tc::println("System: Windows 10");
        break;
    case OS_WINDOWSNT6:
        tc::println("System: Windows Vista/7/8/8.1");
        break;
    case OS_LINUX:
        tc::println("System: Linux");
        break;
    case OS_MACOS:
        tc::println("System: macOS");
        break;
    case OS_BEOS:
        tc::println("System: BeOS");
        break;
    case OS_OS2:
        tc::println("System: OS/2");
        break;
    case OS_NEXTSTEP:
        tc::println("System: NeXTSTEP");
        break;
    // ...more systems supported
    default:
        tc::println("Unknown or other system, code=", os);
    }

    return 0;
}
```

---

## 🧩 Main APIs & Macros

### 🎨 Color & Style (Global Macros)

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
>
> - Most Linux/macOS terminals (GNOME Terminal, iTerm2, Konsole, Alacritty, etc.) support common styles (bold, underline, reverse, some italic/strikethrough).
> - Windows 10+ native terminal supports most common styles (bold, underline, reverse), but italic, strikethrough, blink are limited.
> - Old Windows CMD/PowerShell support very few styles. Upgrade or use Windows Terminal is recommended.
> - TFONT_FRAKTUR, TFONT_DEFAULT, TFONT_DOUBLE_UNDERLINE are experimental/rarely supported.

Example: `tc::println(TCOLOR_RED, BCOLOR_YELLOW, TFONT_BOLD, "Red text, yellow background, bold")`

- `tc::tout`: Stream output (supports color/style/delay)
- `tc::print(...)` / `tc::println(...)`: Multi-argument print, supports color/style macros
- `tc::printer()`: Chainable terminal control

### ⏱️ Delay & Wait

- `tc::tsleep(ms)` / `tc::tsleep_stream << ms`
- `tc::wait(seconds)`
- `tc::waitKey()`

### 📊 Progress Bar

- `tc::ProgressBar bar(width, doneChar, todoChar, color)`
- `bar.show(progress, msg)`
- `bar.finish()`

### 🖥️ System Related API

- `tc::getSystemTime(int type = SYS_TIMESTAMP)`: Get current time (year, month, day, hour, minute, second, Unix timestamp)
- `tc::systemConsole(const char* or std::string)`: Run system command
- `tc::systemCheck()`: Detect current OS, returns one of the macros below

#### Supported System Macros

| Macro | Description |
|------|------|
| OS_WINDOWSNT11 | Windows 11 and above |
| OS_WINDOWSNT10 | Windows 10 |
| OS_WINDOWSNT6  | Windows Vista/7/8/8.1 |
| OS_WINDOWSNT5  | Windows 2000/XP/2003 |
| OS_WINDOWSNT4  | Windows NT 4.x |
| OS_WINDOWSNT3  | Windows NT 3.x |
| OS_WIN95       | Windows 95 |
| OS_WIN98       | Windows 98 |
| OS_WINME       | Windows Me |
| OS_WINCE       | Windows CE |
| OS_WINDOWS     | Other Windows |
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
| OS_UNKNOWN     | Unknown/Other |

#### Example

```cpp
int os = tc::systemCheck();
switch (os) {
    case OS_WINDOWSNT11: tc::println("Windows 11"); break;
    case OS_LINUX: tc::println("Linux"); break;
    // ... other systems ...
    default: tc::println("Unknown system, code=", os);
}
```

### ⏱️ Get System Time

| Macro | Description |
|------|------|
| SYS_YEAR      | Year |
| SYS_MONTH     | Month |
| SYS_DAY       | Day |
| SYS_HOUR      | Hour |
| SYS_MINUTE    | Minute |
| SYS_SECOND    | Second |
| SYS_TIMESTAMP | Unix timestamp (default) |

```cpp
int year = tc::getSystemTime(SYS_YEAR);
int timestamp = tc::getSystemTime(); // Unix timestamp
```

### ⌨️ waitKey

- `tc::waitKey()`: Wait for any key
- `tc::waitKey(char key)` / `tc::waitKey(int key)`: Wait for specific key (e.g. tc::waitKey('A'), tc::waitKey(KEY_ESC))

#### Common Special Key Macros

| Macro | Description |
|------|------|
| KEY_ESC      | ESC |
| KEY_SPACE    | Space |
| KEY_ENTER    | Enter |
| KEY_TAB      | Tab |
| KEY_BACKSPACE| Backspace |
| KEY_INSERT   | Insert |
| KEY_DELETE   | Delete |
| TC_KEY_HOME     | Home |
| KEY_END      | End |
| KEY_PAGEUP   | PageUp |
| KEY_PAGEDOWN | PageDown |
| KEY_UP       | Up arrow |
| KEY_DOWN     | Down arrow |
| KEY_LEFT     | Left arrow |
| KEY_RIGHT    | Right arrow |
| KEY_F1 ~ KEY_F12 | F1~F12 function keys |

```cpp
tc::waitKey(); // Wait for any key
// Wait for 'A' key
tc::waitKey('A');
// Wait for ESC key
tc::waitKey(KEY_ESC);
```

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
