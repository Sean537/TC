# TC.hpp API 参考手册

本文档提供了 TC.hpp 库的完整 API 参考，包括所有类、函数、宏和常量。

## 目录

- [全局宏](#全局宏)
  - [颜色宏](#颜色宏)
  - [字体样式宏](#字体样式宏)
  - [按键宏](#按键宏)
  - [系统相关宏](#系统相关宏)
- [命名空间 tc](#命名空间-tc)
  - [输出函数](#输出函数)
  - [延时函数](#延时函数)
  - [按键等待函数](#按键等待函数)
  - [系统相关函数](#系统相关函数)
  - [终端控制函数](#终端控制函数)
- [类参考](#类参考)
  - [PrintProxy 类](#printproxy-类)
  - [Printer 类](#printer-类)
  - [ColorController 类](#colorcontroller-类)
  - [ColorWrapper 类](#colorwrapper-类)
  - [RGBColorWrapper 类](#rgbcolorwrapper-类)
  - [FontStyleWrapper 类](#fontstylewrapper-类)
  - [TSleep 类](#tsleep-类)
  - [TSleepStream 类](#tsleepstream-类)
  - [ProgressBar 类](#progressbar-类)
  - [TOut 类](#tout-类)
  - [Win32Console 类](#win32console-类)

## 全局宏

### 颜色宏

#### 前景色宏

| 宏名称 | 描述 |
|--------|------|
| `TCOLOR_BLACK` | 黑色前景色 |
| `TCOLOR_RED` | 红色前景色 |
| `TCOLOR_GREEN` | 绿色前景色 |
| `TCOLOR_YELLOW` | 黄色前景色 |
| `TCOLOR_BLUE` | 蓝色前景色 |
| `TCOLOR_MAGENTA` | 洋红前景色 |
| `TCOLOR_CYAN` | 青色前景色 |
| `TCOLOR_WHITE` | 白色前景色 |
| `TCOLOR_DEFAULT` | 默认前景色 |
| `TCOLOR_RESET` | 重置所有颜色和样式 |
| `TCOLOR_RGB(r, g, b)` | RGB颜色 (0-255) |

> 在非Windows平台上，这些宏会展开为ANSI转义序列；在Windows平台上，这些宏会被映射到对应的Windows Console API调用。

#### 背景色宏

| 宏名称 | 描述 |
|--------|------|
| `BCOLOR_BLACK` | 黑色背景色 |
| `BCOLOR_RED` | 红色背景色 |
| `BCOLOR_GREEN` | 绿色背景色 |
| `BCOLOR_YELLOW` | 黄色背景色 |
| `BCOLOR_BLUE` | 蓝色背景色 |
| `BCOLOR_MAGENTA` | 洋红背景色 |
| `BCOLOR_CYAN` | 青色背景色 |
| `BCOLOR_WHITE` | 白色背景色 |
| `BCOLOR_DEFAULT` | 默认背景色 |

### 字体样式宏

| 宏名称 | 描述 |
|--------|------|
| `TFONT_BOLD` | 粗体/加粗 |
| `TFONT_FAINT` | 微弱/淡色 |
| `TFONT_ITALIC` | 斜体 |
| `TFONT_UNDERLINE` | 下划线 |
| `TFONT_BLINK_SLOW` | 慢速闪烁 |
| `TFONT_BLINK_FAST` | 快速闪烁 |
| `TFONT_REVERSE` | 反色 |
| `TFONT_CONCEAL` | 隐藏 |
| `TFONT_CROSSED` | 删除线 |
| `TFONT_DEFAULT` | 默认字体 |
| `TFONT_FRAKTUR` | Fraktur字体（部分终端支持） |
| `TFONT_DOUBLE_UNDERLINE` | 双下划线/粗体关闭 |
| `TFONT_NORMAL` | 粗体/淡色关闭 |
| `TFONT_NOT_ITALIC` | 关闭斜体/Fraktur |
| `TFONT_NO_UNDERLINE` | 关闭下划线 |
| `TFONT_NO_BLINK` | 关闭闪烁 |
| `TFONT_NO_REVERSE` | 关闭反色 |
| `TFONT_REVEAL` | 关闭隐藏 |
| `TFONT_NOT_CROSSED` | 关闭删除线 |
| `TFONT_THICK` | 粗体（TFONT_BOLD的别名） |
| `TFONT_RESET` | 全部重置 |

### 按键宏

| 宏名称 | 值 | 描述 |
|--------|-----|------|
| `KEY_ESC` | 27 | Escape键 |
| `KEY_SPACE` | 32 | 空格键 |
| `KEY_ENTER` | 13 | 回车键 |
| `KEY_TAB` | 9 | Tab键 |
| `KEY_BACKSPACE` | 8 | 退格键 |
| `KEY_INSERT` | 0x2D | Insert键 |
| `KEY_DELETE` | 0x2E | Delete键 |
| `KEY_HOME` | 0x24 | Home键 |
| `KEY_END` | 0x23 | End键 |
| `KEY_PAGEUP` | 0x21 | Page Up键 |
| `KEY_PAGEDOWN` | 0x22 | Page Down键 |
| `KEY_UP` | 0x26 | 上箭头键 |
| `KEY_DOWN` | 0x28 | 下箭头键 |
| `KEY_LEFT` | 0x25 | 左箭头键 |
| `KEY_RIGHT` | 0x27 | 右箭头键 |
| `KEY_F1` - `KEY_F12` | 0x70 - 0x7B | F1至F12功能键 |

### 系统相关宏

#### 系统时间宏

| 宏名称 | 值 | 描述 |
|--------|-----|------|
| `SYS_YEAR` | 1 | 年份 |
| `SYS_MONTH` | 2 | 月份(1-12) |
| `SYS_DAY` | 3 | 日期(1-31) |
| `SYS_HOUR` | 4 | 小时(0-23) |
| `SYS_MINUTE` | 5 | 分钟(0-59) |
| `SYS_SECOND` | 6 | 秒钟(0-59) |
| `SYS_TIMESTAMP` | 0 | Unix时间戳 |

#### 操作系统类型宏

##### Windows系列

| 宏名称 | 值 | 描述 |
|--------|-----|------|
| `OS_WINDOWS` | 100 | 通用Windows标识 |
| `OS_WINDOWSNT6` | 108 | Windows 7/8/8.1 (NT 6.x) |
| `OS_WINDOWSNT10` | 109 | Windows 10 (NT 10.0) |
| `OS_WINDOWSNT11` | 110 | Windows 11 (NT 10.0 build 22000+) |

##### Linux发行版

| 宏名称 | 值 | 描述 |
|--------|-----|------|
| `OS_LINUX` | 200 | 通用Linux标识 |
| `OS_UBUNTU` | 201 | Ubuntu Linux |
| `OS_DEBIAN` | 202 | Debian Linux |
| `OS_FEDORA` | 203 | Fedora Linux |
| `OS_CENTOS` | 204 | CentOS Linux |
| `OS_REDHAT` | 205 | Red Hat Enterprise Linux |
| `OS_SUSE` | 206 | SUSE/openSUSE Linux |
| `OS_ARCH` | 207 | Arch Linux |
| `OS_GENTOO` | 208 | Gentoo Linux |
| `OS_SLACKWARE` | 209 | Slackware Linux |
| `OS_ANDROID` | 210 | Android (基于Linux) |
| `OS_KALI` | 211 | Kali Linux |
| `OS_MINT` | 212 | Linux Mint |
| `OS_MANJARO` | 213 | Manjaro Linux |
| `OS_ALPINE` | 214 | Alpine Linux |
| `OS_RASPBIAN` | 215 | Raspbian |
| `OS_DEEPIN` | 216 | Deepin Linux |
| `OS_ELEMENTARY` | 217 | Elementary OS |
| `OS_ZORIN` | 218 | Zorin OS |
| `OS_POPOS` | 219 | Pop!_OS |
| `OS_CHROMEOS` | 220 | Chrome OS/Chromium OS |

##### Apple操作系统

| 宏名称 | 值 | 描述 |
|--------|-----|------|
| `OS_MACOS` | 300 | 通用macOS标识 |
| `OS_MACOS_HIGHSIERRA` | 324 | macOS 10.13 High Sierra (2017) |
| `OS_MACOS_MOJAVE` | 325 | macOS 10.14 Mojave (2018) |
| `OS_MACOS_CATALINA` | 326 | macOS 10.15 Catalina (2019) |
| `OS_MACOS_BIGSUR` | 327 | macOS 11 Big Sur (2020) |
| `OS_MACOS_MONTEREY` | 328 | macOS 12 Monterey (2021) |
| `OS_MACOS_VENTURA` | 329 | macOS 13 Ventura (2022) |
| `OS_MACOS_SONOMA` | 330 | macOS 14 Sonoma (2023) |
| `OS_MACOS_SEQUOIA` | 331 | macOS 15 Sequoia (2024) |
| `OS_MACOS_TAHOE` | 332 | macOS 26 Tahoe (2025) |

##### 其他Apple操作系统

| 宏名称 | 值 | 描述 |
|--------|-----|------|
| `OS_IOS` | 350 | iOS (iPhone/iPod touch) |
| `OS_IPADOS` | 351 | iPadOS (iPad) |
| `OS_WATCHOS` | 352 | watchOS (Apple Watch) |
| `OS_TVOS` | 353 | tvOS (Apple TV) |
| `OS_VISIONOS` | 354 | visionOS (Apple Vision Pro) |
| `OS_BRIDGEOS` | 355 | bridgeOS (Apple T2芯片) |
| `OS_AUDIOOS` | 356 | audioOS (HomePod) |

##### BSD系列

| 宏名称 | 值 | 描述 |
|--------|-----|------|
| `OS_BSD` | 400 | 通用BSD标识 |
| `OS_FREEBSD` | 404 | FreeBSD |

##### Unix系列

| 宏名称 | 值 | 描述 |
|--------|-----|------|
| `OS_UNIX` | 500 | 通用Unix标识 |

##### 新兴操作系统

| 宏名称 | 值 | 描述 |
|--------|-----|------|
| `OS_FUCHSIA` | 950 | Google Fuchsia |
| `OS_HARMONY` | 952 | Harmony OS |

##### 其他操作系统

| 宏名称 | 值 | 描述 |
|--------|-----|------|
| `OS_REACTOS` | 704 | ReactOS |

##### 未知操作系统

| 宏名称 | 值 | 描述 |
|--------|-----|------|
| `OS_UNKNOWN` | 0 | 无法识别的操作系统 |

## 命名空间 tc

### 输出函数

#### 标准输出函数

| 函数 | 描述 |
|------|------|
| `print()` | 无参数打印 |
| `println()` | 无参数打印并换行 |
| `print(Args&&... args)` | 多参数打印 |
| `println(Args&&... args)` | 多参数打印并换行 |
| `tout` | 全局输出对象 (TOut类型) |

#### 颜色函数

| 函数 | 描述 |
|------|------|
| `colorize(const std::string& text, ColorController::Color color)` | 返回带指定颜色的字符串 |
| `red(const std::string& text)` | 返回带红色的字符串 |
| `green(const std::string& text)` | 返回带绿色的字符串 |
| `blue(const std::string& text)` | 返回带蓝色的字符串 |
| `yellow(const std::string& text)` | 返回带黄色的字符串 |

### 延时函数

| 函数 | 描述 |
|------|------|
| `wait(double seconds)` | 等待指定秒数（支持小数） |
| `tsleep(int milliseconds)` | 等待指定毫秒，返回TSleep对象 |
| `tsleep_stream` | 延时流对象 (TSleepStream类型) |

### 按键等待函数

| 函数 | 描述 |
|------|------|
| `waitKey()` | 等待任意按键 |
| `waitKey(char key)` | 等待特定字符按键 |
| `waitKey(int key)` | 等待特定键码按键 |

### 系统相关函数

| 函数 | 描述 | 参数 | 返回值 |
|------|------|------|--------|
| `getSystemTime(int type = SYS_TIMESTAMP)` | 获取系统时间 | `type`: 时间类型常量 | 请求的时间值 |
| `systemConsole(const char* cmd)` | 执行系统命令(C字符串版本) | `cmd`: 要执行的命令 | 命令的退出状态 |
| `systemConsole(const std::string& cmd)` | 执行系统命令(C++字符串版本) | `cmd`: 要执行的命令 | 命令的退出状态 |
| `systemConsoleW(const wchar_t* cmd)` | 执行系统命令(宽字符版本，仅Windows平台可用) | `cmd`: 要执行的宽字符命令 | 命令的退出状态 |
| `systemCheck()` | 检测当前操作系统类型 | 无 | 操作系统类型代码 |
| `getOSName(int osCode)` | 获取操作系统名称 | `osCode`: 操作系统代码 | 操作系统名称字符串 |
| `getOSVersionInfo()` | 获取当前操作系统的详细版本信息 | 无 | 操作系统版本信息字符串 |

### 终端控制函数

| 函数 | 描述 | 参数 | 返回值 |
|------|------|------|--------|
| `terminal::clear()` | 清屏 | 无 | 无 |
| `terminal::moveCursor(int x, int y)` | 移动光标到指定位置 | `x`: 列坐标, `y`: 行坐标 | 无 |
| `terminal::getSize()` | 获取终端尺寸 | 无 | 包含宽度和高度的对组 |
| `printer()` | 创建Printer对象 | 无 | Printer对象 |

## 类参考

### PrintProxy 类

用于链式打印操作的代理类。

| 方法 | 描述 | 参数 | 返回值 |
|------|------|------|--------|
| `print()` | 无参数打印 | 无 | PrintProxy引用 |
| `print(Args&&... args)` | 多参数打印 | 任意类型参数 | PrintProxy引用 |
| `println(Args&&... args)` | 多参数打印并换行 | 任意类型参数 | PrintProxy引用 |

### Printer 类

提供终端控制功能的类。

| 方法 | 描述 | 参数 | 返回值 |
|------|------|------|--------|
| `clear()` | 清屏 | 无 | Printer引用 |
| `moveCursor(int x, int y)` | 移动光标到指定位置 | `x`: 列坐标, `y`: 行坐标 | Printer引用 |
| `print()` | 无参数打印 | 无 | Printer引用 |
| `print(Args&&... args)` | 多参数打印 | 任意类型参数 | Printer引用 |
| `println(Args&&... args)` | 多参数打印并换行 | 任意类型参数 | Printer引用 |
| `hideCursor()` | 隐藏光标 | 无 | Printer引用 |
| `showCursor()` | 显示光标 | 无 | Printer引用 |
| `moveCursor(Direction dir, int n)` | 按方向移动光标 | `dir`: 方向, `n`: 移动距离 | Printer引用 |
| `getSize()` | 获取终端尺寸 | 无 | 包含宽度和高度的对组 |

### ColorController 类

控制终端颜色的静态类。

| 方法 | 描述 | 参数 | 返回值 |
|------|------|------|--------|
| `setColor(Color color)` | 设置颜色 | `color`: 颜色枚举值 | 无 |
| `setRGBColor(int r, int g, int b)` | 设置RGB颜色 | `r,g,b`: RGB颜色值(0-255) | 无 |
| `setBold(bool enable)` | 设置粗体 | `enable`: 是否启用 | 无 |

### ColorWrapper 类

用于流式输出颜色的包装器类。

| 方法 | 描述 | 参数 | 返回值 |
|------|------|------|--------|
| `ColorWrapper(ColorController::Color color)` | 构造函数 | `color`: 颜色枚举值 | 无 |
| `operator<<` | 输出运算符重载 | `os`: 输出流, `wrapper`: 颜色包装器 | 输出流引用 |

### RGBColorWrapper 类

用于流式输出RGB颜色的包装器类。

| 方法 | 描述 | 参数 | 返回值 |
|------|------|------|--------|
| `RGBColorWrapper(int r, int g, int b)` | 构造函数 | `r,g,b`: RGB颜色值(0-255) | 无 |
| `operator<<` | 输出运算符重载 | `os`: 输出流, `wrapper`: RGB颜色包装器 | 输出流引用 |

### FontStyleWrapper 类

用于流式输出字体样式的包装器类。

| 方法 | 描述 | 参数 | 返回值 |
|------|------|------|--------|
| `FontStyleWrapper(bool enable)` | 构造函数 | `enable`: 是否启用 | 无 |
| `operator<<` | 输出运算符重载 | `os`: 输出流, `wrapper`: 字体样式包装器 | 输出流引用 |

### TSleep 类

用于延时操作的类。

| 方法 | 描述 | 参数 | 返回值 |
|------|------|------|--------|
| `TSleep(int ms)` | 构造函数 | `ms`: 毫秒数 | 无 |
| `execute()` | 执行延时 | 无 | 无 |
| `operator<<` | 输出运算符重载 | `os`: 输出流, `sleep`: 延时对象 | 输出流引用 |

### TSleepStream 类

用于流式延时的类。

| 方法 | 描述 | 参数 | 返回值 |
|------|------|------|--------|
| `operator<<(int milliseconds)` | 延时操作符 | `milliseconds`: 毫秒数 | 无 |

### ProgressBar 类

进度条类。

| 方法 | 描述 | 参数 | 返回值 |
|------|------|------|--------|
| `ProgressBar(int width, std::string done = "#", std::string todo = "-", std::string color = TCOLOR_GREEN)` | 构造函数 | `width`: 宽度, `done`: 已完成字符, `todo`: 未完成字符, `color`: 颜色 | 无 |
| `show(double progress, const std::string& msg = "Loading...")` | 显示进度 | `progress`: 进度值(0.0-1.0), `msg`: 消息 | 无 |
| `finish(std::string content = "Finished")` | 完成进度条 | `content`: 完成消息 | 无 |

### TOut 类

自定义输出流类，支持链式输出和自定义类型。

| 方法 | 描述 | 参数 | 返回值 |
|------|------|------|--------|
| `TOut(std::ostream& os = std::cout)` | 构造函数 | `os`: 输出流 | 无 |
| `operator<<(T&& value)` | 通用输出操作符 | `value`: 要输出的值 | TOut引用 |
| `operator<<(const TSleep& sleep)` | 特化处理TSleep | `sleep`: 延时对象 | TOut引用 |
| `operator<<(const ColorWrapper& color)` | 特化处理颜色包装器 | `color`: 颜色包装器 | TOut引用 |
| `operator<<(const RGBColorWrapper& color)` | 特化处理RGB颜色包装器 | `color`: RGB颜色包装器 | TOut引用 |
| `operator<<(const FontStyleWrapper& style)` | 特化处理字体样式包装器 | `style`: 字体样式包装器 | TOut引用 |
| `operator<<(std::ostream& (*manip)(std::ostream&))` | 支持标准流操作符 | `manip`: 流操作符 | TOut引用 |
| `stream()` | 获取底层流 | 无 | 输出流引用 |

### Win32Console 类

Windows平台下的控制台管理类。

| 方法 | 描述 | 参数 | 返回值 |
|------|------|------|--------|
| `getInstance()` | 获取单例实例 | 无 | Win32Console引用 |
| `isInitialized()` | 判断是否初始化 | 无 | 布尔值 |
| `setColor(WORD color)` | 设置颜色 | `color`: 颜色值 | 无 |
| `pushColor(WORD color)` | 推入当前颜色到栈 | `color`: 颜色值 | 无 |
| `popColor()` | 弹出颜色栈并恢复 | 无 | 无 |
| `resetColor()` | 重置为原始颜色 | 无 | 无 |
| `getCurrentColor()` | 获取当前颜色 | 无 | 颜色值 |
| `moveCursor(int x, int y)` | 移动光标 | `x`: 列坐标, `y`: 行坐标 | 无 |
| `clearScreen()` | 清屏 | 无 | 无 |
| `getConsoleSize()` | 获取终端尺寸 | 无 | 包含宽度和高度的对组 |
| `rgbToWin32Color(int r, int g, int b)` | RGB转16色近似 | `r,g,b`: RGB颜色值(0-255) | 颜色值 |

## 使用示例

### 基本输出

```cpp
// 标准输出
tc::print("Hello", " ", "World");
tc::println("Hello", " ", "World");

// 流式输出
tc::tout << "Hello World" << std::endl;

// 带颜色的输出
tc::println(TCOLOR_RED, "红色文本", TCOLOR_RESET);
tc::tout << TCOLOR_BLUE << "蓝色文本" << TCOLOR_RESET << std::endl;
```

### 延时操作

```cpp
// 等待1.5秒
tc::wait(1.5);

// 等待1000毫秒
tc::tsleep(1000).execute();

// 流式延时
tc::tout << "等待前" << tc::tsleep(500) << "等待后" << std::endl;

// 延时流
tc::tsleep_stream << 1000;
```

### 按键等待

```cpp
// 等待任意按键
tc::waitKey();

// 等待特定按键
tc::waitKey('A');
tc::waitKey(KEY_ESC);
```

### 终端控制

```cpp
// 清屏
tc::printer().clear();

// 移动光标
tc::printer().moveCursor(10, 5);

// 隐藏/显示光标
tc::printer().hideCursor();
tc::printer().showCursor();

// 获取终端尺寸
auto size = tc::printer().getSize();
```

### 进度条

```cpp
// 创建进度条
tc::ProgressBar bar(30, "█", "░", TCOLOR_GREEN);

// 显示进度
for (int i = 0; i <= 100; ++i) {
    bar.show(i / 100.0, "处理中...");
    tc::wait(0.02);
}

// 完成进度条
bar.finish("完成！");
```

### 系统相关

```cpp
// 获取系统时间
int year = tc::getSystemTime(SYS_YEAR);
int timestamp = tc::getSystemTime();

// 执行系统命令
tc::systemConsole("echo Hello World");

// 执行Unicode命令（Windows平台）
#ifdef _WIN32
tc::systemConsoleW(L"echo 你好世界");
#endif

// 检测系统类型
int os = tc::systemCheck();
const char* osName = tc::getOSName(os);
std::string osVersionInfo = tc::getOSVersionInfo();

// 显示系统信息
tc::println("当前系统: ", osName);
tc::println("系统版本: ", osVersionInfo);
```

---

本文档提供了 TC.hpp 库的完整 API 参考。更多详细信息和高级用法，请参考源代码中的注释和示例。
