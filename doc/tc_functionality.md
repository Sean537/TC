# TC.hpp 功能文档

> TC.hpp 是一个现代化的 C++17 终端控制库，支持彩色输出、字体样式、延时、进度条、终端控制等，跨平台、零依赖、纯头文件。

## 目录
- [快速开始](#快速开始)
- [颜色与样式](#颜色与样式)
- [输出控制](#输出控制)
- [延时与等待](#延时与等待)
- [终端控制](#终端控制)
- [进度条](#进度条)
- [系统功能](#系统功能)
- [按键处理](#按键处理)
- [跨平台兼容性](#跨平台兼容性)

## 快速开始

```cpp
#include "tc.hpp"

int main() {
    // 基本输出
    tc::println("Hello World");
    
    // 颜色输出
    tc::println(TCOLOR_RED, "红色文本", TCOLOR_RESET);
    
    // 延时
    tc::wait(1.0);
    
    return 0;
}
```

## 颜色与样式

### 基本颜色
```cpp
tc::println(TCOLOR_RED, "红色", TCOLOR_RESET);
tc::println(TCOLOR_GREEN, "绿色", TCOLOR_RESET);
tc::println(TCOLOR_BLUE, "蓝色", TCOLOR_RESET);
```

### 背景色
```cpp
tc::println(TCOLOR_WHITE, BCOLOR_BLUE, "白字蓝底", TCOLOR_RESET);
```

### 字体样式
```cpp
tc::println(TFONT_BOLD, "粗体", TFONT_RESET);
tc::println(TFONT_UNDERLINE, "下划线", TFONT_RESET);
```

### RGB颜色
```cpp
tc::println(TCOLOR_RGB(255, 128, 0), "橙色", TCOLOR_RESET);
```

## 输出控制

### 标准输出
```cpp
tc::print("Hello", " ", "World");      // 不换行
tc::println("Hello", " ", "World");   // 换行
```

### 流式输出
```cpp
tc::tout << "流式" << "输出" << std::endl;
```

## 延时与等待

### 基本延时
```cpp
tc::wait(1.5);           // 秒级延时
tc::tsleep(1000);        // 毫秒级延时
```

### 按键等待
```cpp
tc::waitKey();           // 等待任意键
tc::waitKey('A');        // 等待特定键
tc::waitKey(KEY_ESC);    // 等待ESC键
```

## 终端控制

### 光标控制
```cpp
tc::printer().clear();                   // 清屏
tc::printer().moveCursor(10, 5);         // 移动光标
tc::printer().hideCursor().showCursor(); // 隐藏/显示光标
```

### 获取终端尺寸
```cpp
auto size = tc::printer().getSize();
tc::println("终端: ", size.first, "x", size.second);
```

## 进度条

```cpp
tc::ProgressBar bar(30, "█", "░", TCOLOR_GREEN);
for (int i = 0; i <= 100; ++i) {
    bar.show(i / 100.0, "处理中...");
    tc::wait(0.02);
}
bar.finish("完成!");
```

## 系统功能

### 系统时间
```cpp
int year = tc::getSystemTime(SYS_YEAR);
int timestamp = tc::getSystemTime();  // Unix时间戳
```

### 系统检测
```cpp
int os = tc::systemCheck();
switch (os) {
    case OS_WINDOWSNT11: tc::println("Windows 11"); break;
    case OS_LINUX: tc::println("Linux"); break;
    case OS_MACOS: tc::println("macOS"); break;
}
```

### 系统命令
```cpp
tc::systemConsole("echo Hello World");
```

## 按键处理

支持所有标准按键和特殊按键：

```cpp
// 方向键
tc::waitKey(KEY_UP);
tc::waitKey(KEY_DOWN);

// 功能键  
tc::waitKey(KEY_F1);

// 实时检测
if (_kbhit()) {
    int key = _getch();
    // 处理按键...
}
```

## 跨平台兼容性

TC.hpp 自动处理平台差异：
- **Windows**：使用 Win32 Console API
- **Linux/macOS**：使用 ANSI 转义序列

所有功能在不同平台上表现一致。

## 完整示例

```cpp
#include "tc.hpp"

int main() {
    tc::printer().clear();
    
    // 颜色演示
    tc::println(TCOLOR_CYAN, "TC.hpp 演示", TCOLOR_RESET);
    tc::println(TCOLOR_RED, "红色", TCOLOR_GREEN, "绿色", TCOLOR_BLUE, "蓝色", TCOLOR_RESET);
    
    // 进度条
    tc::ProgressBar bar(30, "█", "░", TCOLOR_GREEN);
    for (int i = 0; i <= 100; i += 10) {
        bar.show(i / 100.0, "加载中...");
        tc::wait(0.1);
    }
    bar.finish("完成!");
    
    // 系统信息
    tc::println("系统: ", tc::getOSName(tc::systemCheck()));
    tc::println("时间: ", tc::getSystemTime(SYS_YEAR), "-", 
                tc::getSystemTime(SYS_MONTH), "-", tc::getSystemTime(SYS_DAY));
    
    tc::println("按任意键退出...");
    tc::waitKey();
    
    return 0;
}
```

> 更多详细API参考请查看代码注释，示例代码请参考 `example/` 目录。