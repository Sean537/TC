# TC库API参考手册

本文档提供TC库的完整API参考，采用灵活的表格格式，便于快速查阅和使用。

## 快速导航

- [输出函数](#输出函数)
- [延时函数](#延时函数)
- [按键处理](#按键处理)
- [系统功能](#系统功能)
- [Printer类](#printer类)
- [ProgressBar类](#progressbar类)
- [宏定义参考](#宏定义参考)

## 输出函数

| 函数 | 原定义 | 功能 | 返回值 | 示例 |
|------|--------|------|--------|------|
| `tc::print(Args... args)` | `template<typename... Args> void print(Args&&... args)` | 多参数打印，不换行 | `void` | `tc::print("Hello", " ", "World");` |
| `tc::println(Args... args)` | `template<typename... Args> void println(Args&&... args)` | 多参数打印并换行 | `void` | `tc::println("Hello World");` |
| `tc::tout` | `extern std::ostream tout;` | 全局输出流对象，支持颜色/样式/延时 | `std::ostream&` | `tc::tout << TCOLOR_RED << "红色文本";` |

## 延时函数

| 函数 | 原定义 | 功能 | 返回值 | 示例 |
|------|--------|------|--------|------|
| `tc::wait(double seconds)` | `void wait(double seconds)` | 等待指定秒数 | `void` | `tc::wait(1.5);` |
| `tc::tsleep(int milliseconds)` | `SleepStream tsleep(int milliseconds)` | 等待指定毫秒数，返回延时流对象 | `SleepStream` | `tc::tsleep(1000);` |
| `tc::tsleep_stream` | `extern SleepStream tsleep_stream;` | 延时流对象，用于流式延时操作 | `SleepStream&` | `tc::tsleep_stream << 500;` |

## 按键处理

| 函数 | 原定义 | 功能 | 返回值 | 示例 |
|------|--------|------|--------|------|
| `tc::waitKey()` | `void waitKey()` | 等待任意按键 | `void` | `tc::waitKey();` |
| `tc::waitKey(char key)` | `void waitKey(char key)` | 等待特定字符按键 | `void` | `tc::waitKey('A');` |
| `tc::waitKey(int key)` | `void waitKey(int key)` | 等待特定键码 | `void` | `tc::waitKey(KEY_ESC);` |
| `tc::isKeyPressed(char key)` | `bool isKeyPressed(char key)` | 检测指定字符按键是否被按下 | `bool` | `tc::isKeyPressed('A');` |
| `tc::isKeyPressed(int key)` | `bool isKeyPressed(int key)` | 检测指定键码是否被按下 | `bool` | `tc::isKeyPressed(KEY_UP);` |

## 系统功能

| 函数 | 原定义 | 功能 | 返回值 | 示例 |
|------|--------|------|--------|------|
| `tc::getSystemTime(int type)` | `int getSystemTime(int type = SYS_TIMESTAMP)` | 获取系统时间 | `int` | `tc::getSystemTime(SYS_YEAR);` |
| `tc::systemConsole(const std::string& cmd)` | `void systemConsole(const std::string& cmd)` | 执行系统命令 | `void` | `tc::systemConsole("echo Hello");` |
| `tc::systemConsoleW(const wchar_t* cmd)` | `void systemConsoleW(const wchar_t* cmd)` | 执行系统命令（宽字符版本） | `void` | `tc::systemConsoleW(L"echo");` |
| `tc::systemCheck()` | `int systemCheck()` | 检测当前操作系统 | `int` | `tc::systemCheck();` |
| `tc::getOSName(int osCode)` | `const char* getOSName(int osCode)` | 根据操作系统代码返回操作系统名称 | `const char*` | `tc::getOSName(tc::systemCheck());` |
| `tc::getOSVersionInfo()` | `std::string getOSVersionInfo()` | 获取当前操作系统的详细版本信息 | `std::string` | `tc::getOSVersionInfo();` |

## Printer类

### 构造函数
- **原定义**: `Printer()`
- **功能**: 创建Printer对象
- **返回值**: `Printer`对象

### 主要方法

| 方法 | 原定义 | 功能 | 返回值 | 示例 |
|------|--------|------|--------|------|
| `Printer::clear()` | `Printer& clear()` | 清屏 | `Printer&` | `tc::printer().clear();` |
| `Printer::moveCursor(int x, int y)` | `Printer& moveCursor(int x, int y)` | 移动光标到绝对位置 | `Printer&` | `tc::printer().moveCursor(10, 5);` |
| `Printer::moveCursor(Direction dir, int n)` | `Printer& moveCursor(Direction dir, int n)` | 相对移动光标 | `Printer&` | `tc::printer().moveCursor(Direction::Down, 2);` |
| `Printer::hideCursor()` | `Printer& hideCursor()` | 隐藏光标 | `Printer&` | `tc::printer().hideCursor();` |
| `Printer::showCursor()` | `Printer& showCursor()` | 显示光标 | `Printer&` | `tc::printer().showCursor();` |
| `Printer::print(Args... args)` | `template<typename... Args> Printer& print(Args&&... args)` | 打印内容，不换行 | `Printer&` | `tc::printer().print("Hello");` |
| `Printer::println(Args... args)` | `template<typename... Args> Printer& println(Args&&... args)` | 打印内容并换行 | `Printer&` | `tc::printer().println("Hello");` |
| `Printer::getSize()` | `std::pair<int, int> getSize()` | 获取终端尺寸 | `std::pair<int, int>` | `tc::printer().getSize();` |
| `Printer::flush()` | `Printer& flush()` | 刷新缓冲区 | `Printer&` | `tc::printer().flush();` |

## ProgressBar类

### 构造函数
- **原定义**: `ProgressBar(int width, const std::string& doneChar, const std::string& todoChar, int color)`
- **功能**: 创建进度条对象
- **参数**:
  - `width`: 进度条宽度
  - `doneChar`: 已完成部分字符
  - `todoChar`: 未完成部分字符
  - `color`: 进度条颜色
- **示例**: `tc::ProgressBar bar(30, "█", "░", TCOLOR_GREEN);`

### 主要方法

| 方法 | 原定义 | 功能 | 返回值 | 示例 |
|------|--------|------|--------|------|
| `ProgressBar::show(double progress, const std::string& message)` | `void show(double progress, const std::string& message = "")` | 显示进度 | `void` | `bar.show(0.75, "处理中");` |
| `ProgressBar::finish(const std::string& message)` | `void finish(const std::string& message = "")` | 完成进度条 | `void` | `bar.finish("完成");` |

## 宏定义参考

### 按键宏
```cpp
KEY_ESC, KEY_ENTER, KEY_SPACE, KEY_TAB, KEY_BACKSPACE
KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT
KEY_F1 到 KEY_F12
KEY_INSERT, KEY_DELETE, KEY_HOME, KEY_END, KEY_PAGEUP, KEY_PAGEDOWN
```

### 时间宏
```cpp
SYS_YEAR, SYS_MONTH, SYS_DAY
SYS_HOUR, SYS_MINUTE, SYS_SECOND
SYS_TIMESTAMP  // Unix时间戳
```

### 系统宏
```cpp
OS_WINDOWSNT11, OS_WINDOWSNT10, OS_WINDOWSNT6
OS_LINUX, OS_UBUNTU, OS_DEBIAN, OS_FEDORA
OS_MACOS, OS_IOS, OS_ANDROID
OS_UNKNOWN  // 未知系统
```

### 颜色和样式宏
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

> 完整源代码和更多细节请参考TC.hpp头文件注释。