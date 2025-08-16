# TC.hpp 按键处理参考

本文档详细介绍了 TC.hpp 库中的按键处理功能，包括按键等待、按键检测和特殊按键处理。

## 目录

- [按键宏定义](#按键宏定义)
- [基本按键等待](#基本按键等待)
- [特殊按键处理](#特殊按键处理)
- [按键检测](#按键检测)
- [实时按键处理](#实时按键处理)
- [跨平台兼容性](#跨平台兼容性)
- [常见问题与解决方案](#常见问题与解决方案)
- [使用示例](#使用示例)

## 按键宏定义

TC.hpp 提供了一系列按键宏定义，方便在代码中使用：

```cpp
// 基本按键
#define KEY_ESC      27      // ESC键
#define KEY_SPACE    32      // 空格键
#define KEY_ENTER    13      // 回车键
#define KEY_TAB       9      // Tab键
#define KEY_BACKSPACE 8      // 退格键

// 功能键
#define KEY_INSERT   0x2D    // Insert键
#define KEY_DELETE   0x2E    // Delete键
#define KEY_HOME     0x24    // Home键
#define KEY_END      0x23    // End键
#define KEY_PAGEUP   0x21    // PageUp键
#define KEY_PAGEDOWN 0x22    // PageDown键

// 方向键
#define KEY_UP       0x26    // 上方向键
#define KEY_DOWN     0x28    // 下方向键
#define KEY_LEFT     0x25    // 左方向键
#define KEY_RIGHT    0x27    // 右方向键

// 功能键F1-F12
#define KEY_F1       0x70    // F1键
#define KEY_F2       0x71    // F2键
#define KEY_F3       0x72    // F3键
#define KEY_F4       0x73    // F4键
#define KEY_F5       0x74    // F5键
#define KEY_F6       0x75    // F6键
#define KEY_F7       0x76    // F7键
#define KEY_F8       0x77    // F8键
#define KEY_F9       0x78    // F9键
#define KEY_F10      0x79    // F10键
#define KEY_F11      0x7A    // F11键
#define KEY_F12      0x7B    // F12键
```

## 基本按键等待

TC.hpp 提供了三种形式的按键等待函数：

```cpp
// 等待任意按键
tc::waitKey();

// 等待特定字符键
tc::waitKey('A');  // 等待按下A键

// 等待特殊按键
tc::waitKey(KEY_ESC);  // 等待按下ESC键
tc::waitKey(KEY_ENTER);  // 等待按下回车键
```

## 特殊按键处理

TC.hpp 在 Windows 平台上对特殊按键（如方向键、功能键等）进行了特殊处理，确保它们能够正确识别。在 Windows 系统中，这些特殊按键通常会生成两个字符：一个前缀字符（0 或 224）和一个扩展键码。TC.hpp 的 `waitKey` 函数会自动处理这种情况，将扩展键码转换为对应的宏定义值。

```cpp
// Windows平台上的waitKey实现（简化版）
inline void waitKey(int key) { 
    int ch;
    do {
        ch = _getch();
        // 处理特殊键（方向键等）
        if (ch == 0 || ch == 224) {
            ch = _getch();
            // 将扩展键转换为我们定义的键码
            switch (ch) {
                case 72: ch = KEY_UP; break;    // 上方向键
                case 80: ch = KEY_DOWN; break;  // 下方向键
                case 75: ch = KEY_LEFT; break;  // 左方向键
                case 77: ch = KEY_RIGHT; break; // 右方向键
                // 其他特殊键...
            }
        }
    } while (ch != key);
}
```

## 按键检测

在游戏或交互式应用中，通常需要检测是否有按键按下，而不是等待按键。TC.hpp 可以与 `_kbhit()` 函数结合使用来实现这一功能：

```cpp
#include "tc.hpp"
#include <conio.h>  // 对于Windows平台，需要包含此头文件

void checkKeyPress() {
    if (_kbhit()) {  // 检查是否有按键按下
        int key = _getch();
        
        // 处理特殊键（方向键等）
        if (key == 0 || key == 224) {
            key = _getch();
            switch (key) {
                case 72: tc::println("上方向键被按下"); break;
                case 80: tc::println("下方向键被按下"); break;
                case 75: tc::println("左方向键被按下"); break;
                case 77: tc::println("右方向键被按下"); break;
                default: tc::println("其他特殊键: ", key);
            }
        } else {
            tc::println("普通键被按下: ", key, " (", (char)key, ")");
        }
    }
}
```

## 实时按键处理

在游戏循环中处理按键：

```cpp
#include "tc.hpp"
#include <conio.h>

int main() {
    tc::printer().clear();
    tc::println("使用方向键移动，按ESC退出");
    
    int x = 10, y = 10;
    bool running = true;
    
    tc::printer().hideCursor();
    
    while (running) {
        // 清除当前位置
        tc::printer().moveCursor(x, y);
        tc::print(" ");
        
        // 检查按键
        if (_kbhit()) {
            int key = _getch();
            
            // 处理ESC键
            if (key == KEY_ESC) {
                running = false;
                continue;
            }
            
            // 处理特殊键
            if (key == 0 || key == 224) {
                key = _getch();
                switch (key) {
                    case 72: y = (y > 1) ? y - 1 : y; break;  // 上
                    case 80: y = (y < 20) ? y + 1 : y; break; // 下
                    case 75: x = (x > 1) ? x - 1 : x; break;  // 左
                    case 77: x = (x < 30) ? x + 1 : x; break; // 右
                }
            }
        }
        
        // 绘制新位置
        tc::printer().moveCursor(x, y);
        tc::print(TCOLOR_GREEN, "@", TCOLOR_RESET);
        
        // 短暂延时
        tc::wait(0.05);
    }
    
    tc::printer().showCursor();
    tc::printer().moveCursor(1, 22);
    tc::println("程序结束");
    
    return 0;
}
```

## 跨平台兼容性

TC.hpp 的按键处理在不同平台上的实现方式：

- **Windows**: 使用 `_getch()` 函数捕获按键，并对扩展键进行特殊处理
- **Linux/macOS**: 使用 `termios` 库修改终端属性，实现无缓冲的按键捕获

库会自动检测平台并使用适当的实现，无需用户手动配置。

```cpp
// Linux/macOS平台上的waitKey实现（简化版）
#include <termios.h>
inline void waitKey() {
    termios oldt, newt;
    tcgetattr(0, &oldt);
    newt = oldt;
    newt.c_lflag &= ~ICANON;
    tcsetattr(0, TCSANOW, &newt);
    getchar();
    tcsetattr(0, TCSANOW, &oldt);
}
```

## 常见问题与解决方案

### 1. 方向键无法正确识别

如果方向键无法正确识别，可能是因为扩展键处理有问题。确保使用最新版本的 TC.hpp，其中包含了对扩展键的完整支持。

### 2. 功能键（F1-F12）无法正确识别

功能键在不同终端和平台上的行为可能不同。TC.hpp 已经对常见平台进行了适配，但如果遇到问题，可以使用以下代码来调试按键码：

```cpp
#include "tc.hpp"
#include <conio.h>

int main() {
    tc::println("按键测试 - 按任意键查看键码，按ESC退出");
    
    while (true) {
        int key = _getch();
        tc::print("按键码: ", key);
        
        if (key == 0 || key == 224) {
            key = _getch();
            tc::println(" (扩展键: ", key, ")");
        } else {
            tc::println();
            if (key == KEY_ESC) break;
        }
    }
    
    return 0;
}
```

### 3. 在Linux/macOS上使用_kbhit()

`_kbhit()` 是Windows特有的函数。在Linux/macOS上，可以使用以下替代方案：

```cpp
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

// Linux/macOS上的_kbhit()替代实现
int _kbhit() {
    struct termios oldt, newt;
    int ch;
    int oldf;
    
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
    
    ch = getchar();
    
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);
    
    if(ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }
    
    return 0;
}
```

## 使用示例

### 示例1：等待特定按键

```cpp
#include "tc.hpp"

int main() {
    tc::println("按键测试");
    tc::println("=======");
    
    tc::println("\n按 ESC 键退出...");
    tc::waitKey(KEY_ESC);
    tc::println("检测到 ESC 键");
    
    tc::println("\n按方向键测试:");
    tc::println("按上方向键...");
    tc::waitKey(KEY_UP);
    tc::println("检测到上方向键");
    
    tc::println("按下方向键...");
    tc::waitKey(KEY_DOWN);
    tc::println("检测到下方向键");
    
    tc::println("按左方向键...");
    tc::waitKey(KEY_LEFT);
    tc::println("检测到左方向键");
    
    tc::println("按右方向键...");
    tc::waitKey(KEY_RIGHT);
    tc::println("检测到右方向键");
    
    return 0;
}
```

### 示例2：实时按键控制

```cpp
#include "tc.hpp"
#include <conio.h>

int main() {
    tc::printer().clear();
    tc::println(TCOLOR_CYAN, "按键控制示例", TCOLOR_RESET);
    tc::println("使用方向键移动 '@'，按 ESC 退出");
    
    int x = 10, y = 5;
    bool running = true;
    
    tc::printer().hideCursor();
    
    // 绘制边界
    for (int i = 0; i < 20; ++i) {
        tc::printer().moveCursor(0, i);
        tc::print("#");
        tc::printer().moveCursor(30, i);
        tc::print("#");
    }
    
    for (int i = 0; i < 31; ++i) {
        tc::printer().moveCursor(i, 0);
        tc::print("#");
        tc::printer().moveCursor(i, 19);
        tc::print("#");
    }
    
    while (running) {
        // 清除当前位置
        tc::printer().moveCursor(x, y);
        tc::print(" ");
        
        // 检查按键
        if (_kbhit()) {
            int key = _getch();
            
            // 处理ESC键
            if (key == KEY_ESC) {
                running = false;
                continue;
            }
            
            // 处理特殊键
            if (key == 0 || key == 224) {
                key = _getch();
                switch (key) {
                    case 72: // 上
                        if (y > 1) y--;
                        break;
                    case 80: // 下
                        if (y < 18) y++;
                        break;
                    case 75: // 左
                        if (x > 1) x--;
                        break;
                    case 77: // 右
                        if (x < 29) x++;
                        break;
                }
            }
        }
        
        // 绘制新位置
        tc::printer().moveCursor(x, y);
        tc::print(TCOLOR_GREEN, "@", TCOLOR_RESET);
        
        // 显示坐标
        tc::printer().moveCursor(32, 5);
        tc::print("位置: (", x, ",", y, ")  ");
        
        // 短暂延时
        tc::wait(0.05);
    }
    
    tc::printer().showCursor();
    tc::printer().moveCursor(0, 21);
    tc::println("\n程序结束");
    
    return 0;
}
```

### 示例3：按键调试工具

```cpp
#include "tc.hpp"
#include <conio.h>
#include <string>

std::string getKeyName(int key) {
    switch (key) {
        case KEY_ESC: return "ESC";
        case KEY_SPACE: return "SPACE";
        case KEY_ENTER: return "ENTER";
        case KEY_TAB: return "TAB";
        case KEY_BACKSPACE: return "BACKSPACE";
        case KEY_INSERT: return "INSERT";
        case KEY_DELETE: return "DELETE";
        case KEY_HOME: return "HOME";
        case KEY_END: return "END";
        case KEY_PAGEUP: return "PAGE UP";
        case KEY_PAGEDOWN: return "PAGE DOWN";
        case KEY_UP: return "UP ARROW";
        case KEY_DOWN: return "DOWN ARROW";
        case KEY_LEFT: return "LEFT ARROW";
        case KEY_RIGHT: return "RIGHT ARROW";
        case KEY_F1: return "F1";
        case KEY_F2: return "F2";
        case KEY_F3: return "F3";
        case KEY_F4: return "F4";
        case KEY_F5: return "F5";
        case KEY_F6: return "F6";
        case KEY_F7: return "F7";
        case KEY_F8: return "F8";
        case KEY_F9: return "F9";
        case KEY_F10: return "F10";
        case KEY_F11: return "F11";
        case KEY_F12: return "F12";
        default: return "UNKNOWN";
    }
}

int main() {
    tc::printer().clear();
    tc::println(TCOLOR_CYAN, TFONT_BOLD, "按键调试工具", TCOLOR_RESET);
    tc::println(TCOLOR_CYAN, "==========", TCOLOR_RESET);
    tc::println("\n按任意键查看键码，按 ESC 键退出...\n");
    
    while (true) {
        int key = _getch();
        
        if (key == KEY_ESC) {
            tc::println(TCOLOR_YELLOW, "检测到 ESC 键，程序退出", TCOLOR_RESET);
            break;
        }
        
        tc::print(TCOLOR_GREEN, "按键码: ", TCOLOR_RESET, key);
        
        if (key == 0 || key == 224) {
            int extKey = _getch();
            tc::print(" (扩展键: ", extKey, ")");
            
            // 转换扩展键码为我们的键码
            int mappedKey = 0;
            switch (extKey) {
                case 72: mappedKey = KEY_UP; break;
                case 80: mappedKey = KEY_DOWN; break;
                case 75: mappedKey = KEY_LEFT; break;
                case 77: mappedKey = KEY_RIGHT; break;
                case 71: mappedKey = KEY_HOME; break;
                case 79: mappedKey = KEY_END; break;
                case 73: mappedKey = KEY_PAGEUP; break;
                case 81: mappedKey = KEY_PAGEDOWN; break;
                case 82: mappedKey = KEY_INSERT; break;
                case 83: mappedKey = KEY_DELETE; break;
                case 59: mappedKey = KEY_F1; break;
                case 60: mappedKey = KEY_F2; break;
                case 61: mappedKey = KEY_F3; break;
                case 62: mappedKey = KEY_F4; break;
                case 63: mappedKey = KEY_F5; break;
                case 64: mappedKey = KEY_F6; break;
                case 65: mappedKey = KEY_F7; break;
                case 66: mappedKey = KEY_F8; break;
                case 67: mappedKey = KEY_F9; break;
                case 68: mappedKey = KEY_F10; break;
                case 133: mappedKey = KEY_F11; break;
                case 134: mappedKey = KEY_F12; break;
            }
            
            if (mappedKey != 0) {
                tc::print(" -> TC键码: ", mappedKey, " (", getKeyName(mappedKey), ")");
            }
        } else if (key >= 32 && key <= 126) {
            // 可打印字符
            tc::print(" (字符: '", (char)key, "')");
        } else {
            // 检查是否是我们定义的键码
            std::string keyName = getKeyName(key);
            if (keyName != "UNKNOWN") {
                tc::print(" (", keyName, ")");
            }
        }
        
        tc::println();
    }
    
    return 0;
}
```

---

本文档提供了 TC.hpp 库中按键处理功能的详细参考。通过这些功能，您可以轻松实现各种交互式应用程序，如游戏、菜单系统和命令行界面。
