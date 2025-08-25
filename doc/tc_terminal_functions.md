# TC库终端控制功能详解

本文档详细说明了TC库中与终端控制相关的功能，包括基本终端控制、缓冲区管理和链式操作接口。TC库提供了多种方式来控制终端输出和显示，使开发者能够创建更加丰富和响应迅速的终端应用程序。

## 目录

1. [概述](#概述)
2. [tc::terminal命名空间](#tcterminal命名空间)
3. [tc::Printer链式函数类](#tcprinter链式函数类)
4. [缓冲区控制](#缓冲区控制)
5. [功能对比](#功能对比)
6. [使用建议](#使用建议)
7. [示例代码](#示例代码)

## 概述

TC库提供了两种不同风格的终端控制接口：

1. **tc::terminal命名空间**：提供了一系列独立的函数，每个函数执行特定的终端操作。这种风格适合简单、直接的终端控制需求。

2. **tc::Printer链式函数类**：提供了一个对象式的接口，支持链式调用，可以将多个终端操作连接在一起。这种风格适合复杂的、多步骤的终端控制序列。

## tc::terminal命名空间

`tc::terminal`命名空间包含了一系列用于基本终端控制的函数。这些函数设计简单直接，每次调用执行一个特定的终端操作。

### 可用函数

| 函数名 | 描述 | 参数 | 返回值 |
|--------|------|------|--------|
| `clear()` | 清空终端屏幕并将光标移动到左上角 | 无 | 无 |
| `moveCursor(int x, int y)` | 将光标移动到指定坐标 | `x`: 列坐标(从1开始)<br>`y`: 行坐标(从1开始) | 无 |
| `getSize()` | 获取终端窗口大小 | 无 | `std::pair<int, int>`: 包含宽度和高度的对组 |
| `flush()` | 刷新终端输出缓冲区 | 无 | 无 |

### 使用示例

```cpp
// 基本终端控制
tc::terminal::clear();
tc::terminal::moveCursor(5, 3);

// 获取终端大小
auto [width, height] = tc::terminal::getSize();
tc::println("终端宽度: ", width, ", 高度: ", height);

// 使用刷新功能
tc::print("\r加载中...");
tc::terminal::flush();  // 确保立即显示
```

## 缓冲区控制

TC库提供了两种方式来控制终端输出的缓冲，使开发者能够精确控制内容何时显示在屏幕上。这在创建动画效果、实时更新界面或需要即时反馈的交互式应用程序中特别有用。

### 全局刷新函数

`tc::terminal::flush()` 函数会立即刷新终端的输出缓冲区，确保所有待显示的内容立即出现在屏幕上。

```cpp
// 使用全局刷新函数
tc::print("\r处理中...");
tc::terminal::flush();  // 立即显示
tc::wait(1.0);
```

### Printer类的刷新方法

`tc::Printer` 类提供了 `flush()` 方法，支持链式调用：

```cpp
// 使用Printer的刷新方法
tc::printer()
    .print("\r第一步...")
    .flush()
    .print("\r第二步...")
    .flush();
```

### 自动刷新场景

某些操作会自动触发刷新：

1. 使用 `\r` 进行回车时
2. 使用 `println` 函数时
3. 某些终端控制操作（如移动光标）后

```cpp
// 自动刷新示例
tc::print("\r自动刷新");     // 含\r会自动刷新
tc::println("自动刷新");    // println自动刷新
tc::printer().moveCursor(0, 0).print("位置更新");  // 移动光标后自动刷新
```

### 应用场景

缓冲区控制在以下场景特别有用：

1. **动画效果**
   ```cpp
   tc::printer().hideCursor().flush();
   for (int i = 0; i < 100; i++) {
       tc::print("\r进度: ", i, "%");
       tc::terminal::flush();
       tc::wait(0.05);
   }
   tc::printer().showCursor().flush();
   ```

2. **实时更新界面**
   ```cpp
   // 更新状态显示
   void updateStatus(const std::string& status) {
       tc::print("\r当前状态: ", status);
       tc::terminal::flush();
   }
   ```

3. **交互式应用**
   ```cpp
   // 即时响应的命令提示符
   tc::printer()
       .print("> ")
       .flush();  // 确保提示符立即显示
   std::string command;
   std::getline(std::cin, command);
   ```

## tc::Printer链式函数类

`tc::Printer`类提供了一个链式调用接口，允许将多个终端操作连接在一起执行。这种风格特别适合需要执行一系列连续操作的场景。

### 创建Printer对象

使用`tc::printer()`函数可以创建一个新的`Printer`对象：

```cpp
auto p = tc::printer();
```

### 可用方法

| 方法名 | 描述 | 参数 | 返回值 |
|--------|------|------|--------|
| `clear()` | 清空终端屏幕并将光标移动到左上角 | 无 | `Printer&`: 对象自身引用 |
| `moveCursor(int x, int y)` | 将光标移动到指定坐标 | `x`: 列坐标(从1开始)<br>`y`: 行坐标(从1开始) | `Printer&`: 对象自身引用 |
| `moveCursor(Direction dir, int n)` | 按指定方向移动光标 | `dir`: 移动方向<br>`n`: 移动步数 | `Printer&`: 对象自身引用 |
| `print()` | 无参数打印函数 | 无 | `Printer&`: 对象自身引用 |
| `print(Args&&... args)` | 可变参数打印函数 | `args`: 要打印的参数 | `Printer&`: 对象自身引用 |
| `println(Args&&... args)` | 可变参数打印函数，带换行 | `args`: 要打印的参数 | `Printer&`: 对象自身引用 |
| `hideCursor()` | 隐藏光标 | 无 | `Printer&`: 对象自身引用 |
| `showCursor()` | 显示光标 | 无 | `Printer&`: 对象自身引用 |
| `getSize()` | 获取终端窗口大小 | 无 | `std::pair<int, int>`: 包含宽度和高度的对组 |

### 方向枚举

`tc::Printer::Direction`枚举定义了光标移动的方向：

| 枚举值 | 描述 |
|--------|------|
| `Direction::Up` | 向上移动 |
| `Direction::Down` | 向下移动 |
| `Direction::Left` | 向左移动 |
| `Direction::Right` | 向右移动 |

### 使用示例

```cpp
// 创建Printer对象
auto p = tc::printer();

// 链式调用多个方法
p.clear()
 .hideCursor()
 .moveCursor(5, 3)
 .print("位置(5,3)")
 .moveCursor(tc::Printer::Direction::Down, 2)
 .println("向下移动了2行")
 .showCursor();

// 获取终端大小
auto [width, height] = p.getSize();
p.moveCursor(1, height - 1)
 .println("终端宽度: ", width, ", 高度: ", height);
```

## 功能对比

下表比较了`tc::terminal`命名空间和`tc::Printer`类的功能：

| 功能 | tc::terminal | tc::Printer |
|------|--------------|-------------|
| 清屏 | ✓ | ✓ |
| 移动光标到绝对位置 | ✓ | ✓ |
| 移动光标到相对位置 | ✗ | ✓ |
| 获取终端大小 | ✓ | ✓ |
| 隐藏/显示光标 | ✗ | ✓ |
| 打印文本 | ✗ | ✓ |
| 链式调用 | ✗ | ✓ |

## 使用建议

1. **简单操作**：对于简单的、独立的终端控制操作，使用`tc::terminal`命名空间中的函数。例如，只需清屏或移动光标一次。

2. **复杂序列**：对于需要执行多个连续操作的场景，使用`tc::Printer`类的链式调用接口。例如，需要清屏、移动光标、打印文本、再移动光标等一系列操作。

3. **打印功能**：如果需要在终端控制操作中包含打印功能，使用`tc::Printer`类，它提供了`print`和`println`方法。

4. **相对移动**：如果需要相对于当前位置移动光标，使用`tc::Printer`类的`moveCursor(Direction, int)`方法。

## 示例代码

### 使用tc::terminal命名空间

```cpp
#include "../include/tc.hpp"
#include <iostream>

int main() {
    // 清屏
    tc::terminal::clear();
    
    // 移动光标并打印
    tc::terminal::moveCursor(10, 5);
    std::cout << "这是位置(10,5)" << std::endl;
    
    // 获取终端大小
    auto [width, height] = tc::terminal::getSize();
    tc::terminal::moveCursor(1, height - 1);
    std::cout << "终端大小: " << width << "x" << height << std::endl;
    
    return 0;
}
```

### 使用tc::Printer链式函数

```cpp
#include "../include/tc.hpp"
#include <iostream>

int main() {
    // 创建Printer对象并执行一系列操作
    tc::printer()
        .clear()
        .hideCursor()
        .moveCursor(10, 5)
        .println("这是位置(10,5)")
        .moveCursor(tc::Printer::Direction::Down, 2)
        .println("向下移动了2行")
        .moveCursor(1, 10)
        .print("在第10行: ")
        .print("继续在同一行打印")
        .println()
        .showCursor();
    
    return 0;
}
```

### 综合示例

```cpp
#include "../include/tc.hpp"
#include <iostream>
#include <string>

void demoTerminal() {
    std::cout << "=== tc::terminal命名空间演示 ===" << std::endl;
    tc::wait(1);
    
    tc::terminal::clear();
    std::cout << "已清屏" << std::endl;
    tc::wait(1);
    
    tc::terminal::moveCursor(20, 10);
    std::cout << "移动到位置(20,10)" << std::endl;
    tc::wait(1);
    
    auto [width, height] = tc::terminal::getSize();
    tc::terminal::moveCursor(1, height - 2);
    std::cout << "终端大小: " << width << "x" << height << std::endl;
    tc::wait(2);
}

void demoPrinter() {
    std::cout << "=== tc::Printer链式函数演示 ===" << std::endl;
    tc::wait(1);
    
    auto p = tc::printer();
    
    p.clear()
     .println("已清屏")
     .wait(1)
     
     .moveCursor(20, 10)
     .println("移动到位置(20,10)")
     .wait(1)
     
     .moveCursor(tc::Printer::Direction::Left, 5)
     .println("向左移动5格")
     .wait(1)
     
     .hideCursor()
     .println("光标已隐藏")
     .wait(1)
     
     .showCursor()
     .println("光标已显示")
     .wait(1);
    
    auto [width, height] = p.getSize();
    p.moveCursor(1, height - 2)
     .println("终端大小: ", width, "x", height);
    
    tc::wait(2);
}

int main() {
    demoTerminal();
    tc::terminal::clear();
    tc::wait(1);
    demoPrinter();
    
    return 0;
}
```

通过以上示例，您可以清楚地了解`tc::terminal`命名空间和`tc::Printer`类的使用方法和区别，从而根据具体需求选择合适的接口。