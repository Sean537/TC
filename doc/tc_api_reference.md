# TC.hpp API 参考手册

本文档提供TC库的核心API参考，包含主要类、函数和宏定义。

## 核心命名空间：tc

### 输出函数
- `print(Args... args)` - 多参数打印
- `println(Args... args)` - 多参数打印并换行
- `tout` - 全局输出流对象

### 延时函数
- `wait(double seconds)` - 等待指定秒数
- `tsleep(int milliseconds)` - 等待指定毫秒
- `tsleep_stream` - 延时流对象

### 按键等待
- `waitKey()` - 等待任意按键
- `waitKey(char key)` - 等待特定字符
- `waitKey(int key)` - 等待特定键码

### 系统功能
- `getSystemTime(int type)` - 获取系统时间
- `systemConsole(const string& cmd)` - 执行系统命令
- `systemCheck()` - 检测操作系统
- `getOSName(int osCode)` - 获取系统名称

## Printer 类

链式终端控制接口：

```cpp
tc::printer()
    .clear()                    // 清屏
    .moveCursor(x, y)           // 移动光标
    .hideCursor()               // 隐藏光标
    .print("文本")              // 打印
    .flush();                   // 刷新缓冲区
```

### 主要方法
- `clear()` - 清屏
- `moveCursor(int x, int y)` - 绝对移动
- `moveCursor(Direction, int)` - 相对移动
- `hideCursor()/showCursor()` - 光标控制
- `print()/println()` - 打印
- `getSize()` - 获取终端尺寸
- `flush()` - 刷新缓冲区

## ProgressBar 类

进度条功能：

```cpp
tc::ProgressBar bar(width, doneChar, todoChar, color);
bar.show(progress, message);    // 显示进度
bar.finish(message);            // 完成进度条
```

## 主要颜色宏

### 前景色
- `TCOLOR_RED`, `TCOLOR_GREEN`, `TCOLOR_BLUE` 等
- `TCOLOR_RESET` - 重置所有属性

### 背景色  
- `BCOLOR_RED`, `BCOLOR_GREEN`, `BCOLOR_BLUE` 等

### 字体样式
- `TFONT_BOLD` - 粗体
- `TFONT_UNDERLINE` - 下划线
- `TFONT_ITALIC` - 斜体

### RGB颜色
- `TCOLOR_RGB(r, g, b)` - RGB前景色

## 按键宏定义

```cpp
KEY_ESC, KEY_ENTER, KEY_SPACE    // 基本键
KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT  // 方向键
KEY_F1 到 KEY_F12                // 功能键
KEY_INSERT, KEY_DELETE           // 编辑键
KEY_HOME, KEY_END, KEY_PAGEUP, KEY_PAGEDOWN  // 导航键
```

## 系统时间宏

```cpp
SYS_YEAR, SYS_MONTH, SYS_DAY     // 年月日
SYS_HOUR, SYS_MINUTE, SYS_SECOND // 时分秒
SYS_TIMESTAMP                    // Unix时间戳
```

## 操作系统宏

主要系统类型：
- `OS_WINDOWSNT11` - Windows 11
- `OS_WINDOWSNT10` - Windows 10  
- `OS_LINUX` - Linux
- `OS_MACOS` - macOS
- `OS_ANDROID` - Android

## 使用示例

### 基本输出
```cpp
tc::println("Hello", "World");
tc::tout << "流式输出" << std::endl;
```

### 颜色控制
```cpp
tc::println(TCOLOR_RED, "红色文本", TCOLOR_RESET);
std::cout << tc::red("红色字符串");
```

### 终端控制
```cpp
tc::printer()
    .clear()
    .moveCursor(10, 5)
    .print("位置文本")
    .moveCursor(Direction::Down, 2)
    .println("下移两行");
```

### 进度条
```cpp
tc::ProgressBar bar(40, "█", "░", TCOLOR_CYAN);
for (int i = 0; i <= 100; i++) {
    bar.show(i / 100.0, "处理中...");
    tc::wait(0.01);
}
bar.finish("完成");
```

> 完整API列表请参考源代码注释，此文档仅包含主要接口。