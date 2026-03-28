# TC.hpp -  ✨ Cross-platform terminal control (headeronly)

[![C++17](https://img.shields.io/badge/C%2B%2B-17%2B-blue.svg)](https://en.cppreference.com/w/cpp/compiler_support)
![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux%20%7C%20macOS-lightgrey.svg)
![Header-Only](https://img.shields.io/badge/Header--Only-Yes-green.svg)
[![MIT License](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

 🚀 TC.hpp is a modern C++17 headeronly library for terminal control. It provides colors (including RGB), font styles, cursor/terminal control, progress bars, delays/typewriter effects, system info and time utilities  crossplatform and zero dependencies.

---

## ✨ Highlights

- Crossplatform (Windows / Linux / macOS)
- Rich color support (foreground, background, RGB)
- Font styles and effects (bold, underline, reverse, etc.)
- Progress bars, chainable Printer API, terminal size & cursor control
- Headeronly, C++17, zero external dependencies

> ⚠️ **Important (ANSI vs Win32)**
>
> By default TC.hpp uses ANSI escape sequences on all platforms for colors and cursor control.
> If you need Win32 Console API behavior on Windows (recommended for very old Windows versions < 10/1809), define `TC_ENABLE_WIN32_CONSOLE_API`.
> Warning: Win32 API mode has compatibility limitations for certain font styles (italic, blink, crossed, etc.).
>
> If you enable Win32 mode and your code prints ANSIwrapped strings via convenience functions, use `tc::tout` / `tc::print` / `tc::println` instead of `std::cout` to avoid raw escape codes appearing in the console.

---

## Quick start

1. Include the header:

```cpp
#include "tc.hpp"
```

2. Example usage:

```cpp
#include "tc.hpp"

int main() {
    // 🌈 colors & styles
    tc::tout << TCOLOR_GREEN << "Hello world!" << TCOLOR_RESET << std::endl;
    tc::tout << TFONT_BOLD << "Bold text" << TFONT_RESET << std::endl;
    tc::tout << TCOLOR_RGB(255,0,0) << "RGB Red" << TCOLOR_RESET << std::endl;
    std::cout << tc::red("Red text") << std::endl;

    // ⏱️ delay
    tc::tout << "Wait..." << std::endl;
    tc::tsleep(1000);
    tc::tout << "Done!" << std::endl;

    // 🖨️ Python-style printing
    tc::print("Hello ", "world!\n");
    tc::println("Age:", 25, ", Score:", 95.5);

    // 🖋️ Printer chain API
    tc::printer()
        .clear()
        .moveCursor(10,5)
        .print("Move cursor to (10,5)")
        .hideCursor()
        .moveCursor(tc::Printer::Direction::Down, 2)
        .println("At (10,7)")
        .showCursor();

    // 📏 terminal size
    auto size = tc::printer().getSize();
    tc::println("Terminal size: ", size.first, "x", size.second);

    // ⏳ progress bar
    tc::ProgressBar bar(30, "", "", TCOLOR_GREEN);
    for (int i = 0; i <= 100; ++i) {
        bar.show(i / 100.0, "Processing...");
        tc::wait(0.02);
    }
    bar.finish();

    // 🖥️ run system command
    tc::systemConsole("echo TC systemConsole test");

    // 🕒 get system time
    int year = tc::getSystemTime(SYS_YEAR);
    int month = tc::getSystemTime(SYS_MONTH);
    int day = tc::getSystemTime(SYS_DAY);
    int hour = tc::getSystemTime(SYS_HOUR);
    int minute = tc::getSystemTime(SYS_MINUTE);
    int second = tc::getSystemTime(SYS_SECOND);
    int timestamp = tc::getSystemTime(); // Unix timestamp (default)
    tc::println("Now time: ", year, "-", month, "-", day, " ", hour, ":", minute, ":", second, " (Unix: ", timestamp, ")");

    // 🛡️ check system environment
    int os = tc::systemCheck();
    const char* osName = tc::getOSName(os);
    std::string osVersionInfo = tc::getOSVersionInfo();

    tc::println("Current system: ", osName);
    tc::println("System version: ", osVersionInfo);

    return 0;
}
```

---

## 🧩 Main APIs & macros

### 🎨 Color & style

#### Global color/style macros

```cpp
// Frontground color
TCOLOR_RED, TCOLOR_GREEN, TCOLOR_YELLOW, TCOLOR_BLUE, TCOLOR_MAGENTA, TCOLOR_CYAN, TCOLOR_WHITE, TCOLOR_RESET
// Background color
BCOLOR_RED, BCOLOR_GREEN, BCOLOR_YELLOW, BCOLOR_BLUE, BCOLOR_MAGENTA, BCOLOR_CYAN, BCOLOR_WHITE, BCOLOR_DEFAULT
// Font styles
TFONT_BOLD, TFONT_FAINT, TFONT_ITALIC, TFONT_UNDERLINE, TFONT_BLINK_SLOW, TFONT_BLINK_FAST, TFONT_REVERSE, TFONT_CONCEAL, TFONT_CROSSED, TFONT_DEFAULT, TFONT_FRAKTUR, TFONT_DOUBLE_UNDERLINE, TFONT_NORMAL, TFONT_NOT_ITALIC, TFONT_NO_UNDERLINE, TFONT_NO_BLINK, TFONT_NO_REVERSE, TFONT_REVEAL, TFONT_NOT_CROSSED, TFONT_THICK, TFONT_RESET
// RGB
TCOLOR_RGB(r, g, b)
```

#### Color Controller (ColorController)

```cpp
// Set color
tc::ColorController::setColor(tc::ColorController::Color::RED);
std::cout << "Red text" << std::endl;

// Set RGB color
tc::ColorController::setRGBColor(255, 128, 0);
std::cout << "Orange text" << std::endl;

// Set bold
tc::ColorController::setBold(true);
std::cout << "Bold text" << std::endl;

// Reset color
tc::ColorController::setColor(tc::ColorController::Color::RESET);
```

#### Convenient color functions

> ⚠ Note: the convenience color functions simply wrap strings with ANSI escape sequences. Some terminals do not support ANSI sequences or support them only partially (for example, older cmd.exe). Unless you do not need to support such terminals, avoid overusing these helpers in output.
>
> If you enabled the `TC_ENABLE_WIN32_CONSOLE_API` macro, use `tc::tout` instead of `std::cout` when printing values returned by these functions. That prevents raw ANSI escape codes from appearing on Windows; otherwise the escape sequences may be printed as literal characters.

```cpp
// Basic color functions
std::string coloredText = tc::colorize("Colored text", tc::ColorController::Color::CYAN);
std::cout << coloredText << std::endl;

// RGB color functions
std::string rgbText = tc::colorizeRGB("RGB colored text", 255, 128, 0);
std::cout << rgbText << std::endl;

// Standard color helpers
std::cout << tc::red("Red text") << std::endl;
std::cout << tc::green("Green text") << std::endl;
std::cout << tc::blue("Blue text") << std::endl;
std::cout << tc::yellow("Yellow text") << std::endl;
std::cout << tc::cyan("Cyan text") << std::endl;
std::cout << tc::magenta("Magenta text") << std::endl;
std::cout << tc::white("White text") << std::endl;

// Bright variants
std::cout << tc::brightRed("Bright red text") << std::endl;
std::cout << tc::brightGreen("Bright green text") << std::endl;
std::cout << tc::brightBlue("Bright blue text") << std::endl;
std::cout << tc::brightYellow("Bright yellow text") << std::endl;
```

### Font style macros (TFONT_XXX)

| Macro Name                 | Effect             | Compatibility Notes |
|---------------------------|--------------------|--------------------|
| TFONT_BOLD                | Bold               | Full ANSI support, full Win32 support |
| TFONT_FAINT               | Faint / Dim        | Partial ANSI support, not supported on Win32 |
| TFONT_ITALIC              | Italic             | Partial ANSI support, not supported on Win32 |
| TFONT_UNDERLINE           | Underline          | Widely supported by ANSI, not supported on Win32 |
| TFONT_BLINK_SLOW          | Slow blink         | Partial ANSI support, not supported on Win32 |
| TFONT_BLINK_FAST          | Fast blink         | Rarely supported by ANSI, not supported on Win32 |
| TFONT_REVERSE             | Reverse            | Widely supported by ANSI, not supported on Win32 |
| TFONT_CONCEAL             | Conceal            | Rarely supported by ANSI, not supported on Win32 |
| TFONT_CROSSED             | Strikethrough      | Partial ANSI support, not supported on Win32 |
| TFONT_DEFAULT             | Default font       | Rarely supported by ANSI, not supported on Win32 |
| TFONT_FRAKTUR             | Fraktur font       | Very rarely supported by ANSI, not supported on Win32 |
| TFONT_DOUBLE_UNDERLINE    | Double underline / turn off bold | Partial ANSI support, not supported on Win32 |
| TFONT_NORMAL              | Reset bold / faint | Widely supported by ANSI, full Win32 support |
| TFONT_NOT_ITALIC          | Disable italic / Fraktur | Partial ANSI support, not supported on Win32 |
| TFONT_NO_UNDERLINE        | Disable underline  | Widely supported by ANSI, not supported on Win32 |
| TFONT_NO_BLINK            | Disable blink      | Rarely supported by ANSI, not supported on Win32 |
| TFONT_NO_REVERSE          | Disable reverse    | Widely supported by ANSI, not supported on Win32 |
| TFONT_REVEAL              | Reveal (undo conceal) | Rarely supported by ANSI, not supported on Win32 |
| TFONT_NOT_CROSSED         | Disable strikethrough | Partial ANSI support, not supported on Win32 |
| TFONT_THICK               | Thick / Bold (alias) | Same as TFONT_BOLD |
| TFONT_RESET               | Reset all styles   | Fully supported on all platforms |

> ⚠️ Compatibility notes:
>
> - By default TC.hpp uses ANSI escape sequences on all platforms to implement terminal control features.
> - If `TC_ENABLE_WIN32_CONSOLE_API` is defined, Windows will use the Win32 Console API; however, Win32 mode may not support some font styles (italic, blink, strikethrough, etc.).
> - Linux/macOS always use ANSI escape sequences; support depends on the terminal emulator. Common styles (bold, underline, reverse) are widely supported; some terminals support italic/strikethrough; advanced styles such as blink/conceal are seldom supported.
> - Experimental/extended styles such as `TFONT_FRAKTUR`, `TFONT_DEFAULT`, `TFONT_DOUBLE_UNDERLINE` have low support on most terminals.

Usage example: `tc::println(TCOLOR_RED, BCOLOR_YELLOW, TFONT_BOLD, "Red text, yellow background, bold")`

### 🖥️ Terminal control

#### tc::terminal namespace

```cpp
// Clear screen
tc::terminal::clear();

// Move cursor to specified position
tc::terminal::moveCursor(10, 5);
std::cout << "This is position (10,5)" << std::endl;

// Get terminal size
auto [width, height] = tc::terminal::getSize();
std::cout << "Terminal size: " << width << "x" << height << std::endl;
```

#### tc::Printer (chainable class)

```cpp
// Create a Printer object and perform a sequence of operations
tc::printer()
    .clear()                                  // clear screen
    .hideCursor()                             // hide cursor
    .moveCursor(10, 5)                        // move to absolute position
    .println("This is position (10,5)")     // print and newline
    .moveCursor(tc::Printer::Direction::Down, 2) // relative move (down 2 lines)
    .println("Moved down 2 lines")
    .moveCursor(1, 10)                        // move to the beginning of line 10
    .print("At line 10: ")                  // print without newline
    .print("Continue printing on same line")
    .println()                                // newline
    .showCursor();                            // show cursor
```

### 🔤 Output & print

- `tc::tout`: stream-like output (supports colors/styles/delay)
- `tc::print(...)` / `tc::println(...)`: multi-argument printing with style macros

### ⏱️ Delay & wait

- `tc::tsleep(ms)` / `tc::tsleep_stream << ms`
- `tc::wait(seconds)`
- `tc::waitKey()`

### 📊 Progress bar

- `tc::ProgressBar bar(width, doneChar, todoChar, color)`
- `bar.show(progress, msg)`
- `bar.finish()`

### 🖥️ System-related API

- `tc::getSystemTime(int type = SYS_TIMESTAMP)`: get current time (year, month, day, hour, minute, second, Unix timestamp)
- `tc::systemConsole(const char* or std::string)`: execute a system command
- `tc::systemConsoleW(const wchar_t*)`: execute a system command (wide-char, Windows only; supports Unicode commands)
- `tc::systemCheck()`: detect the current operating system and return an OS code
- `tc::getOSName(int osCode)`: return the OS name for the given code
- `tc::getOSVersionInfo()`: get detailed OS version information

#### Supported system macros

| Category | Macro | Description |
|------|------|------|
| **Windows family** | OS_WINDOWS | Generic Windows identifier |
| | OS_WINDOWSNT6 | Windows 7/8/8.1 (NT 6.x) |
| | OS_WINDOWSNT10 | Windows 10 (NT 10.0) |
| | OS_WINDOWSNT11 | Windows 11 (NT 10.0 build 22000+) |
| **Linux distributions** | OS_LINUX | Generic Linux identifier |
| | OS_UBUNTU | Ubuntu Linux |
| | OS_DEBIAN | Debian Linux |
| | OS_FEDORA | Fedora Linux |
| | OS_CENTOS | CentOS Linux |
| | OS_REDHAT | Red Hat Enterprise Linux |
| | OS_SUSE | SUSE / openSUSE Linux |
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
| | OS_CHROMEOS | Chrome OS / Chromium OS |
| **Apple operating systems** | OS_MACOS | Generic macOS identifier |
| | OS_MACOS_HIGHSIERRA | macOS 10.13 High Sierra (2017) |
| | OS_MACOS_MOJAVE | macOS 10.14 Mojave (2018) |
| | OS_MACOS_CATALINA | macOS 10.15 Catalina (2019) |
| | OS_MACOS_BIGSUR | macOS 11 Big Sur (2020) |
| | OS_MACOS_MONTEREY | macOS 12 Monterey (2021) |
| | OS_MACOS_VENTURA | macOS 13 Ventura (2022) |
| | OS_MACOS_SONOMA | macOS 14 Sonoma (2023) |
| | OS_MACOS_SEQUOIA | macOS 15 Sequoia (2024) |
| | OS_MACOS_TAHOE | macOS 26 Tahoe (2025) |
| **Other Apple OS** | OS_IOS | iOS (iPhone / iPod touch) |
| | OS_IPADOS | iPadOS (iPad) |
| | OS_WATCHOS | watchOS (Apple Watch) |
| | OS_TVOS | tvOS (Apple TV) |
| | OS_VISIONOS | visionOS (Apple Vision Pro) |
| | OS_BRIDGEOS | bridgeOS (Apple T2 chip) |
| | OS_AUDIOOS | audioOS (HomePod) |
| **BSD family** | OS_BSD | Generic BSD identifier |
| | OS_FREEBSD | FreeBSD |
| **Unix family** | OS_UNIX | Generic Unix identifier |
| **Emerging OS** | OS_FUCHSIA | Google Fuchsia |
| | OS_HARMONYOS | Harmony OS |
| **Other OS** | OS_REACTOS | ReactOS |
| **Unknown** | OS_UNKNOWN | Unrecognized operating system |

#### Example usage

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

### ⏱️ Get system time

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

### ⌨️ Key handling

#### waitKey - wait for key

- `tc::waitKey()`: wait for any key
- `tc::waitKey(char key)` / `tc::waitKey(int key)`: wait for a specific key (e.g. `tc::waitKey('A')`, `tc::waitKey(KEY_ESC)`)

```cpp
tc::waitKey(); // wait for any key
// wait for 'A'
tc::waitKey('A');
// wait for ESC
tc::waitKey(KEY_ESC);
```

#### isKeyPressed - check key state

- `tc::isKeyPressed(char key)` / `tc::isKeyPressed(int key)`: check if the specified key is pressed

```cpp
// Check if ESC key is pressed
if (tc::isKeyPressed(KEY_ESC)) {
    std::cout << "ESC key is pressed" << std::endl;
}

// Check arrow keys
if (tc::isKeyPressed(KEY_UP)) {
    std::cout << "Up arrow key is pressed" << std::endl;
}

// Check letter keys
if (tc::isKeyPressed('A') || tc::isKeyPressed('a')) {
    std::cout << "A key is pressed" << std::endl;
}
```

#### Common special key macros

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

---

## Build

- Windows:  g++ -std=c++17 test.cpp -o test.exe
- Linux/macOS:  g++ -std=c++17 -pthread test.cpp -o test

If you use [xmake](https://xmake.io/): `xmake -a` builds all examples (output: `bin/examples`).

---

## License

MIT

---

## Contact

- Email: <wushaoquan666@outlook.com>
