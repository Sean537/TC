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

```cpp
// 在非Windows平台上，这些宏会展开为ANSI转义序列
// 在Windows平台上，这些宏会被映射到对应的Windows Console API调用
#define TCOLOR_BLACK   // 黑色前景色
#define TCOLOR_RED     // 红色前景色
#define TCOLOR_GREEN   // 绿色前景色
#define TCOLOR_YELLOW  // 黄色前景色
#define TCOLOR_BLUE    // 蓝色前景色
#define TCOLOR_MAGENTA // 洋红前景色
#define TCOLOR_CYAN    // 青色前景色
#define TCOLOR_WHITE   // 白色前景色
#define TCOLOR_DEFAULT // 默认前景色
#define TCOLOR_RESET   // 重置所有颜色和样式
#define TCOLOR_RGB(r, g, b) tc::RGBColorWrapper(r, g, b)  // RGB颜色
```

#### 背景色宏

```cpp
// 在非Windows平台上，这些宏会展开为ANSI转义序列
// 在Windows平台上，这些宏会被映射到对应的Windows Console API调用
#define BCOLOR_BLACK   // 黑色背景色
#define BCOLOR_RED     // 红色背景色
#define BCOLOR_GREEN   // 绿色背景色
#define BCOLOR_YELLOW  // 黄色背景色
#define BCOLOR_BLUE    // 蓝色背景色
#define BCOLOR_MAGENTA // 洋红背景色
#define BCOLOR_CYAN    // 青色背景色
#define BCOLOR_WHITE   // 白色背景色
#define BCOLOR_DEFAULT // 默认背景色
```

### 字体样式宏

```cpp
// 在非Windows平台上，这些宏会展开为ANSI转义序列
// 在Windows平台上，这些宏会被映射到对应的Windows Console API调用
#define TFONT_BOLD        // 粗体/加粗
#define TFONT_FAINT       // 微弱/淡色
#define TFONT_ITALIC      // 斜体
#define TFONT_UNDERLINE   // 下划线
#define TFONT_BLINK_SLOW  // 慢速闪烁
#define TFONT_BLINK_FAST  // 快速闪烁
#define TFONT_REVERSE     // 反色
#define TFONT_CONCEAL     // 隐藏
#define TFONT_CROSSED     // 删除线
#define TFONT_DEFAULT     // 默认字体
#define TFONT_FRAKTUR     // Fraktur字体（部分终端支持）
#define TFONT_DOUBLE_UNDERLINE // 双下划线/粗体关闭
#define TFONT_NORMAL      // 粗体/淡色关闭
#define TFONT_NOT_ITALIC  // 关闭斜体/Fraktur
#define TFONT_NO_UNDERLINE // 关闭下划线
#define TFONT_NO_BLINK    // 关闭闪烁
#define TFONT_NO_REVERSE  // 关闭反色
#define TFONT_REVEAL      // 关闭隐藏
#define TFONT_NOT_CROSSED // 关闭删除线
#define TFONT_THICK       TFONT_BOLD   // 兼容别名
#define TFONT_RESET       // 全部重置
```

### 按键宏

```cpp
#define KEY_ESC      27
#define KEY_SPACE    32
#define KEY_ENTER    13
#define KEY_TAB       9
#define KEY_BACKSPACE 8
#define KEY_INSERT   0x2D
#define KEY_DELETE   0x2E
#define KEY_HOME     0x24
#define KEY_END      0x23
#define KEY_PAGEUP   0x21
#define KEY_PAGEDOWN 0x22
#define KEY_UP       0x26
#define KEY_DOWN     0x28
#define KEY_LEFT     0x25
#define KEY_RIGHT    0x27
#define KEY_F1       0x70
#define KEY_F2       0x71
#define KEY_F3       0x72
#define KEY_F4       0x73
#define KEY_F5       0x74
#define KEY_F6       0x75
#define KEY_F7       0x76
#define KEY_F8       0x77
#define KEY_F9       0x78
#define KEY_F10      0x79
#define KEY_F11      0x7A
#define KEY_F12      0x7B
```

### 系统相关宏

#### 系统时间宏

```cpp
#define SYS_YEAR   1
#define SYS_MONTH  2
#define SYS_DAY    3
#define SYS_HOUR   4
#define SYS_MINUTE 5
#define SYS_SECOND 6
#define SYS_TIMESTAMP 0
```

#### 操作系统类型宏

```cpp
#define OS_UNKNOWN      0
#define OS_WINDOWS      100
#define OS_WINDOWSNT3   103
#define OS_WINDOWSNT4   104
#define OS_WINDOWSNT5   105
#define OS_WINDOWSNT6   106
#define OS_WINDOWSNT10  110
#define OS_WINDOWSNT11  111
#define OS_WIN95        195
#define OS_WIN98        198
#define OS_WINME        199
#define OS_WINCE        120
#define OS_LINUX        200
#define OS_ANDROID      210
#define OS_MACOS        300
#define OS_IOS          310
#define OS_BSD          400
#define OS_UNIX         500
#define OS_DOS          600
#define OS_BEOS         700
#define OS_HAIKU        701
#define OS_AIX          800
#define OS_SOLARIS      810
#define OS_MINIX        820
#define OS_QNX          830
#define OS_VMS          840
#define OS_AMIGAOS      850
#define OS_MORPHOS      851
#define OS_FREEMINT     852
#define OS_HPUX         860
#define OS_IRIX         861
#define OS_SCO          862
#define OS_OPENVMS      863
#define OS_RISCOS       870
#define OS_OS2          900
#define OS_NEXTSTEP     910
```

## 命名空间 tc

### 输出函数

#### 标准输出函数

```cpp
// 无参数打印
inline const PrintProxy& print();
inline const PrintProxy& println();

// 多参数打印
template<typename... Args>
inline void print(Args&&... args);
template<typename... Args>
inline void println(Args&&... args);

// 全局输出对象
static TOut tout(std::cout);
```

#### 颜色函数

```cpp
// 带颜色的字符串
inline std::string colorize(const std::string& text, ColorController::Color color);
inline std::string red(const std::string& text);
inline std::string green(const std::string& text);
inline std::string blue(const std::string& text);
inline std::string yellow(const std::string& text);
```

### 延时函数

```cpp
// 等待指定秒数（支持小数）
inline void wait(double seconds);

// 等待指定毫秒
inline TSleep tsleep(int milliseconds);

// 延时流对象
static TSleepStream tsleep_stream;
```

### 按键等待函数

```cpp
// 等待任意按键
inline void waitKey();

// 等待特定按键
inline void waitKey(char key);
inline void waitKey(int key);
```

### 系统相关函数

```cpp
// 获取系统时间
inline int getSystemTime(int type = SYS_TIMESTAMP);

// 执行系统命令
inline int systemConsole(const char* cmd);
inline int systemConsole(const std::string& cmd);

// 检测系统类型
inline int systemCheck();
```

### 终端控制函数

```cpp
namespace terminal {
    // 清屏
    inline void clear();
    
    // 移动光标
    inline void moveCursor(int x, int y);
    
    // 获取终端尺寸
    inline std::pair<int, int> getSize();
}

// 创建 Printer 对象
inline Printer printer();
```

## 类参考

### PrintProxy 类

用于链式打印操作的代理类。

```cpp
class PrintProxy {
public:
    // 无参数打印
    const PrintProxy& print() const;
    
    // 多参数打印
    template<typename... Args>
    const PrintProxy& print(Args&&... args) const;
    
    // 多参数打印并换行
    template<typename... Args>
    const PrintProxy& println(Args&&... args) const;
};
```

### Printer 类

提供终端控制功能的类。

```cpp
class Printer {
public:
    // 清屏
    Printer& clear();
    
    // 移动光标到指定位置
    Printer& moveCursor(int x, int y);
    
    // 无参数打印
    Printer& print();
    
    // 多参数打印
    template<typename... Args>
    Printer& print(Args&&... args);
    
    // 多参数打印并换行
    template<typename... Args>
    Printer& println(Args&&... args);
    
    // 隐藏光标
    Printer& hideCursor();
    
    // 显示光标
    Printer& showCursor();
    
    // 方向枚举
    enum class Direction { Up, Down, Left, Right };
    
    // 按方向移动光标
    Printer& moveCursor(Direction dir, int n);
    
    // 获取终端尺寸
    std::pair<int,int> getSize();
};
```

### ColorController 类

控制终端颜色的静态类。

```cpp
class ColorController {
public:
    // 颜色枚举
    enum class Color {
        BLACK, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE,
        BRIGHT_BLACK, BRIGHT_RED, BRIGHT_GREEN, BRIGHT_YELLOW,
        BRIGHT_BLUE, BRIGHT_MAGENTA, BRIGHT_CYAN, BRIGHT_WHITE,
        RESET
    };
    
    // 设置颜色
    static void setColor(Color color);
    
    // 设置RGB颜色
    static void setRGBColor(int r, int g, int b);
    
    // 设置粗体
    static void setBold(bool enable);
};
```

### ColorWrapper 类

用于流式输出颜色的包装器类。

```cpp
class ColorWrapper {
public:
    // 构造函数
    explicit ColorWrapper(ColorController::Color color);
    
    // 输出运算符重载
    friend std::ostream& operator<<(std::ostream& os, const ColorWrapper& wrapper);
};
```

### RGBColorWrapper 类

用于流式输出RGB颜色的包装器类。

```cpp
class RGBColorWrapper {
public:
    // 构造函数
    RGBColorWrapper(int r, int g, int b);
    
    // 输出运算符重载
    friend std::ostream& operator<<(std::ostream& os, const RGBColorWrapper& wrapper);
};
```

### FontStyleWrapper 类

用于流式输出字体样式的包装器类。

```cpp
class FontStyleWrapper {
public:
    // 构造函数
    explicit FontStyleWrapper(bool enable);
    
    // 输出运算符重载
    friend std::ostream& operator<<(std::ostream& os, const FontStyleWrapper& wrapper);
};
```

### TSleep 类

用于延时操作的类。

```cpp
class TSleep {
public:
    // 构造函数
    explicit TSleep(int ms);
    
    // 执行延时
    void execute() const;
    
    // 输出运算符重载
    friend std::ostream& operator<<(std::ostream& os, const TSleep& sleep);
};
```

### TSleepStream 类

用于流式延时的类。

```cpp
class TSleepStream {
public:
    // 延时操作符
    void operator<<(int milliseconds) const;
};
```

### ProgressBar 类

进度条类。

```cpp
class ProgressBar {
public:
    // 构造函数
    ProgressBar(int width, std::string done = "#", std::string todo = "-", std::string color = TCOLOR_GREEN);
    
    // 显示进度
    void show(double progress, const std::string& msg = "Loading...");
    
    // 完成进度条
    void finish(std::string content = "Finished");
};
```

### TOut 类

自定义输出流类，支持链式输出和自定义类型。

```cpp
class TOut {
public:
    // 构造函数
    explicit TOut(std::ostream& os = std::cout);
    
    // 通用输出操作符
    template<typename T>
    TOut& operator<<(T&& value);
    
    // 特化处理TSleep
    TOut& operator<<(const TSleep& sleep);
    
    // 特化处理颜色包装器
    TOut& operator<<(const ColorWrapper& color);
    
    // 特化处理RGB颜色包装器
    TOut& operator<<(const RGBColorWrapper& color);
    
    // 特化处理字体样式包装器
    TOut& operator<<(const FontStyleWrapper& style);
    
    // 支持标准流操作符
    TOut& operator<<(std::ostream& (*manip)(std::ostream&));
    
    // 获取底层流
    std::ostream& stream();
};
```

### Win32Console 类

Windows平台下的控制台管理类。

```cpp
class Win32Console {
public:
    // 获取单例实例
    static Win32Console& getInstance();
    
    // 判断是否初始化
    bool isInitialized() const;
    
    // 设置颜色
    void setColor(WORD color);
    
    // 推入当前颜色到栈
    void pushColor(WORD color);
    
    // 弹出颜色栈并恢复
    void popColor();
    
    // 重置为原始颜色
    void resetColor();
    
    // 获取当前颜色
    WORD getCurrentColor() const;
    
    // 移动光标
    void moveCursor(int x, int y);
    
    // 清屏
    void clearScreen();
    
    // 获取终端尺寸
    std::pair<int, int> getConsoleSize() const;
    
    // RGB转16色近似
    WORD rgbToWin32Color(int r, int g, int b) const;
};
```

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

// 检测系统类型
int os = tc::systemCheck();
```

---

本文档提供了 TC.hpp 库的完整 API 参考。更多详细信息和高级用法，请参考源代码中的注释和示例。