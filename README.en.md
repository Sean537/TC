# TC.hpp - ✨ Cross-Platform Terminal Control Header Library

[![C++17](https://img.shields.io/badge/C%2B%2B-17%2B-blue.svg)](https://en.cppreference.com/w/cpp/compiler_support)
![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux%20%7C%20macOS-lightgrey.svg)
![Header-Only](https://img.shields.io/badge/Header--Only-Yes-green.svg)
[![MIT License](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

> 🚀 A modern C++17 terminal control library designed to solve various problems encountered during development with the simplest syntax. Current features include terminal color output, delay, progress bar, terminal control, system information detection, time acquisition, etc. Cross-platform, header-only, and zero dependencies!

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
    const char* osName = tc::getOSName(os);
    std::string osVersionInfo = tc::getOSVersionInfo();
    
    tc::println("Current system: ", osName);
    tc::println("System version: ", osVersionInfo);

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

| Macro Name                 | Effect             | Compatibility Notes |
|---------------------------|--------------------|--------------------|
| TFONT_BOLD                | Bold               | Fully supported on all platforms |
| TFONT_FAINT               | Faint/dim          | Fully supported on Windows, partially on other terminals |
| TFONT_ITALIC              | Italic             | Fully supported on Windows, partially on other terminals |
| TFONT_UNDERLINE           | Underline          | Fully supported on all platforms |
| TFONT_BLINK_SLOW          | Slow blink         | Fully supported on Windows, partially on other terminals |
| TFONT_BLINK_FAST          | Fast blink         | Fully supported on Windows, rarely on other terminals |
| TFONT_REVERSE             | Reverse            | Fully supported on all platforms |
| TFONT_CONCEAL             | Conceal            | Fully supported on Windows, rarely on other terminals |
| TFONT_CROSSED             | Strikethrough      | Fully supported on Windows, partially on other terminals |
| TFONT_DEFAULT             | Default font       | Fully supported on Windows, rarely on other terminals |
| TFONT_FRAKTUR             | Fraktur font       | Fully supported on Windows, very rarely on other terminals |
| TFONT_DOUBLE_UNDERLINE    | Double underline/off bold | Fully supported on Windows, partially on other terminals |
| TFONT_NORMAL              | Reset bold/faint   | Fully supported on all platforms |
| TFONT_NOT_ITALIC          | Not italic/Fraktur | Fully supported on Windows, partially on other terminals |
| TFONT_NO_UNDERLINE        | Not underlined     | Fully supported on all platforms |
| TFONT_NO_BLINK            | Not blinking       | Fully supported on Windows, rarely on other terminals |
| TFONT_NO_REVERSE          | Not reversed       | Fully supported on all platforms |
| TFONT_REVEAL              | Reveal (not concealed) | Fully supported on Windows, rarely on other terminals |
| TFONT_NOT_CROSSED         | Not strikethrough  | Fully supported on Windows, partially on other terminals |
| TFONT_THICK               | Bold (alias)       | Same as TFONT_BOLD |
| TFONT_RESET               | Reset all          | Fully supported on all platforms |

> ⚠️ **Compatibility Notes:**
>
> - TC.hpp uses Windows Console API (Win32 API) on Windows platforms instead of ANSI escape sequences, so all font styles are fully supported on Windows, regardless of terminal's ANSI escape sequence support.
> - On Linux/macOS, ANSI escape sequences are used. Most terminals (GNOME Terminal, iTerm2, Konsole, Alacritty, etc.) support common styles (bold, underline, reverse, some italic/strikethrough).
> - TFONT_FRAKTUR, TFONT_DEFAULT, TFONT_DOUBLE_UNDERLINE are experimental/rarely supported on non-Windows platforms.

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
- `tc::systemConsoleW(const wchar_t*)`: Run system command (wide character version, Windows platform only, supports Unicode commands)
- `tc::systemCheck()`: Detect current operating system, returns an OS code
- `tc::getOSName(int osCode)`: Returns the operating system name based on the OS code
- `tc::getOSVersionInfo()`: Get detailed version information of the current operating system

#### Supported System Macros

| Category | Macro | Description |
|------|------|------|
| **Windows Family** | OS_WINDOWS | Generic Windows identifier |
| | OS_WINDOWSNT6 | Windows 7/8/8.1 (NT 6.x) |
| | OS_WINDOWSNT10 | Windows 10 (NT 10.0) |
| | OS_WINDOWSNT11 | Windows 11 (NT 10.0 build 22000+) |
| **Linux Distributions** | OS_LINUX | Generic Linux identifier |
| | OS_UBUNTU | Ubuntu Linux |
| | OS_DEBIAN | Debian Linux |
| | OS_FEDORA | Fedora Linux |
| | OS_CENTOS | CentOS Linux |
| | OS_REDHAT | Red Hat Enterprise Linux |
| | OS_SUSE | SUSE/openSUSE Linux |
| | OS_ARCH | Arch Linux |
| | OS_GENTOO | Gentoo Linux |
| | OS_SLACKWARE | Slackware Linux |
| | OS_ANDROID | Android (Linux-based) |
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
| **Apple Operating Systems** | OS_MACOS | Generic macOS identifier |
| | OS_MACOS_HIGHSIERRA | macOS 10.13 High Sierra (2017) |
| | OS_MACOS_MOJAVE | macOS 10.14 Mojave (2018) |
| | OS_MACOS_CATALINA | macOS 10.15 Catalina (2019) |
| | OS_MACOS_BIGSUR | macOS 11 Big Sur (2020) |
| | OS_MACOS_MONTEREY | macOS 12 Monterey (2021) |
| | OS_MACOS_VENTURA | macOS 13 Ventura (2022) |
| | OS_MACOS_SONOMA | macOS 14 Sonoma (2023) |
| | OS_MACOS_SEQUOIA | macOS 15 Sequoia (2024) |
| | OS_MACOS_TAHOE | macOS 26 Tahoe (2025) |
| **Other Apple Operating Systems** | OS_IOS | iOS (iPhone/iPod touch) |
| | OS_IPADOS | iPadOS (iPad) |
| | OS_WATCHOS | watchOS (Apple Watch) |
| | OS_TVOS | tvOS (Apple TV) |
| | OS_VISIONOS | visionOS (Apple Vision Pro) |
| | OS_BRIDGEOS | bridgeOS (Apple T2 chip) |
| | OS_AUDIOOS | audioOS (HomePod) |
| **BSD Family** | OS_BSD | Generic BSD identifier |
| | OS_FREEBSD | FreeBSD |
| **Unix Family** | OS_UNIX | Generic Unix identifier |
| **Emerging Operating Systems** | OS_FUCHSIA | Google Fuchsia |
| | OS_HARMONYOS | Harmony OS |
| **Other Operating Systems** | OS_REACTOS | ReactOS |
| **Unknown Operating System** | OS_UNKNOWN | Unrecognized operating system |

#### Example Usage

```cpp
// Get system information
int osCode = tc::systemCheck();
const char* osName = tc::getOSName(osCode);
std::string osVersionInfo = tc::getOSVersionInfo();

// Display system information
tc::println("Operating System: ", osName);
tc::println("System Version: ", osVersionInfo);

// Perform different operations based on system type
switch (osCode) {
    case OS_WINDOWSNT11:
        tc::println("Windows 11 specific operations");
        break;
    case OS_UBUNTU:
        tc::println("Ubuntu specific operations");
        break;
    case OS_MACOS:
        tc::println("macOS specific operations");
        break;
    // ... other systems ...
    default:
        tc::println("Unknown system operations");
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
| KEY_HOME     | Home |
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