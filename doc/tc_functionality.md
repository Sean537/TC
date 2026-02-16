# TC.hpp 功能详细概述

本文档提供TC库的完整功能概述，包含每个功能模块的详细说明和使用指南。

## 核心功能架构

TC.hpp 是一个现代化的 C++17 终端控制库，采用模块化设计，提供以下核心功能模块：

### 1. 输出控制模块
- **多参数打印**: `tc::print()` / `tc::println()`
- **流式输出**: `tc::tout` 全局输出流
- **链式控制**: `tc::printer()` 链式API

### 2. 颜色与样式模块
- **颜色宏**: `TCOLOR_*`, `BCOLOR_*`
- **字体样式**: `TFONT_*` 样式宏

### 3. 延时与等待模块
- **时间控制**: `tc::wait()`, `tc::tsleep()`
- **按键处理**: `tc::waitKey()`, `tc::isKeyPressed()`
- **流式延时**: `tc::tsleep_stream`

### 4. 终端控制模块
- **光标控制**: 移动、显示/隐藏
- **屏幕操作**: 清屏、获取尺寸
- **布局管理**: 绝对和相对定位

### 5. 进度条模块
- **进度显示**: `tc::ProgressBar` 类
- **自定义样式**: 字符、颜色、宽度可配置
- **状态管理**: 进度更新和完成处理

### 6. 系统功能模块
- **时间获取**: `tc::getSystemTime()`
- **系统检测**: `tc::systemCheck()`, `tc::getOSName()`
- **命令执行**: `tc::systemConsole()`

## 详细功能说明

### 输出控制功能

#### 多参数打印系统
- **设计理念**: 提供类似Python的print函数体验
- **技术实现**: 使用C++17变参模板和完美转发
- **优势**: 类型安全、零运行时开销、自动类型转换

```cpp
// 基本用法
tc::print("Hello", " ", "World");        // 不换行
tc::println("Hello", " ", "World");      // 自动换行

// 混合类型支持
tc::println("字符串:", "text", "数字:", 42, "浮点:", 3.14);
```

#### 流式输出对象
- **全局对象**: `extern std::ostream tout`
- **特性**: 支持所有标准流操作和TC扩展功能
- **扩展功能**: 颜色、样式、延时等流操作符

```cpp
// 标准流操作
tc::tout << "标准输出" << std::endl;

// TC扩展功能
tc::tout << TCOLOR_RED << "红色文本" << TCOLOR_RESET;
tc::tout << "前" << tc::tsleep(500) << "后" << std::endl;
```

#### 链式终端控制
- **设计模式**: 流畅接口(Fluent Interface)
- **优势**: 代码简洁、可读性强、支持方法链
- **内存管理**: 返回引用支持连续调用

```cpp
// 链式调用示例
tc::printer()
    .clear()                          // 清屏
    .hideCursor()                     // 隐藏光标  
    .moveCursor(10, 5)               // 移动光标
    .print("位置文本")                // 打印内容
    .showCursor();                    // 显示光标
```

### 颜色与样式功能

#### ANSI转义序列支持
- **标准兼容**: 支持标准ANSI ESC序列
- **颜色模型**: 支持16色基本颜色
- **样式丰富**: 粗体、斜体、下划线等基本样式

```cpp
// 标准颜色
tc::println(TCOLOR_RED, "红色", TCOLOR_GREEN, "绿色");

// 样式组合
tc::println(TCOLOR_WHITE, BCOLOR_BLUE, TFONT_BOLD, "白字蓝底粗体");
```

#### Win32控制台API支持
- **条件编译**: 通过 `TC_ENABLE_WIN32_CONSOLE_API` 宏启用
- **平台特性**: Windows专属控制台功能
- **兼容性**: 适配旧版Windows控制台

```cpp
// 启用Win32 API模式
#define TC_ENABLE_WIN32_CONSOLE_API
#include "tc.hpp"

// 此时使用Win32 API而非ANSI序列
```

### 延时与等待功能

#### 精确时间控制
- **时间单位**: 秒级(`wait`)和毫秒级(`tsleep`)
- **精度保证**: 使用系统高精度时钟
- **线程安全**: 支持多线程环境使用

```cpp
// 基本延时
tc::wait(1.5);          // 等待1.5秒
tc::tsleep(500);        // 等待500毫秒

// 流式延时
tc::tout << "前" << tc::tsleep(300) << "后" << std::endl;
```

#### 交互式按键处理
- **按键检测**: 实时检测按键状态
- **键码支持**: 字符键、功能键、方向键等
- **非阻塞模式**: 不阻塞程序执行

```cpp
// 等待特定按键
tc::waitKey('A');       // 等待A键
tc::waitKey(KEY_ESC);   // 等待ESC键

// 实时按键检测
if (tc::isKeyPressed(KEY_UP)) {
    tc::println("上方向键被按下");
}
```

### 终端控制功能

#### 光标精确定位
- **坐标系统**: 基于行列的终端坐标
- **移动方式**: 绝对定位和相对移动
- **边界处理**: 自动处理终端边界

```cpp
// 绝对定位
tc::printer().moveCursor(10, 5).print("(10,5)位置");

// 相对移动
tc::printer().moveCursor(Direction::Down, 2)  // 下移2行
             .moveCursor(Direction::Right, 5) // 右移5列
             .print("相对位置");
```

#### 终端尺寸自适应
- **动态获取**: 实时获取终端窗口尺寸
- **布局计算**: 支持居中、分栏等布局算法
- **响应式设计**: 适应不同终端尺寸

```cpp
// 获取终端尺寸
auto [width, height] = tc::printer().getSize();

// 居中显示
int centerX = width / 2;
int centerY = height / 2;
tc::printer().moveCursor(centerX - 5, centerY).print("居中文本");
```

### 进度条功能

#### 可视化进度显示
- **自定义样式**: 进度字符、颜色、宽度可配置
- **实时更新**: 支持动态进度更新
- **状态信息**: 可显示进度百分比和状态信息

```cpp
// 创建进度条
tc::ProgressBar bar(40, "█", "░", TCOLOR_GREEN);

// 更新进度
for (int i = 0; i <= 100; i++) {
    bar.show(i / 100.0, "处理中... " + std::to_string(i) + "%");
    tc::wait(0.01);
}

// 完成处理
bar.finish("处理完成!");
```

### 系统功能集成

#### 跨平台系统检测
- **操作系统识别**: 精确识别Windows、Linux、macOS等
- **版本检测**: 支持主要版本号识别
- **架构支持**: x86、x64、ARM等架构检测

```cpp
// 系统检测
int os = tc::systemCheck();
const char* osName = tc::getOSName(os);

// 版本信息
std::string version = tc::getOSVersionInfo();

tc::println("系统: ", osName);
tc::println("版本: ", version);
```

#### 时间日期处理
- **时间格式**: 支持年、月、日、时、分、秒
- **时间戳**: Unix时间戳支持
- **本地时间**: 自动处理时区转换

```cpp
// 获取各种时间信息
int year = tc::getSystemTime(SYS_YEAR);
int month = tc::getSystemTime(SYS_MONTH);
int timestamp = tc::getSystemTime();  // Unix时间戳

tc::println("当前时间: ", year, "-", month);
tc::println("时间戳: ", timestamp);
```

#### 系统命令执行
- **命令安全**: 安全的命令执行接口
- **输出重定向**: 支持命令输出捕获
- **错误处理**: 完善的错误处理机制

```cpp
// 执行系统命令
tc::systemConsole("echo Hello World");

// Windows特定命令
if (tc::systemCheck() == OS_WINDOWSNT11) {
    tc::systemConsole("dir");
} else {
    tc::systemConsole("ls -la");
}
```

## 跨平台兼容性

### 默认行为
- **所有平台**: 默认使用ANSI转义序列实现终端控制
- **现代终端**: 完全兼容支持ANSI的终端模拟器
- **标准兼容**: 遵循ECMA-48和ISO/IEC 6429标准

### Windows特殊支持
- **条件启用**: 通过 `TC_ENABLE_WIN32_CONSOLE_API` 宏启用Win32 API
- **兼容目标**: 适配Windows 10 1809以下版本的控制台
- **功能限制**: Win32 API对部分高级样式支持有限

### 平台特性适配
- **Linux/macOS**: 原生ANSI支持，功能完整
- **Windows**: 智能选择ANSI或Win32 API
- **终端检测**: 自动检测终端能力和特性支持

## 性能优化特性

### 零运行时开销
- **编译时优化**: 大量使用constexpr和模板元编程
- **内联函数**: 关键函数全部内联实现
- **内存效率**: 避免不必要的内存分配

### 资源管理
- **RAII原则**: 自动资源管理和释放
- **异常安全**: 所有操作保证异常安全
- **线程安全**: 关键操作线程安全

### 编译优化
- **头文件优化**: 最小化编译依赖
- **模板特化**: 针对不同平台的特化实现
- **条件编译**: 平台相关代码的条件编译

## 使用最佳实践

### 代码组织建议
```cpp
// 按功能模块组织代码
#include "tc.hpp"

// 输出控制
void setupOutput() {
    tc::printer().clear().hideCursor();
}

// 颜色样式
void displayColors() {
    tc::println(TCOLOR_RED, "错误信息", TCOLOR_RESET);
    tc::println(TCOLOR_GREEN, "成功信息", TCOLOR_RESET);
}

// 进度显示  
void showProgress() {
    tc::ProgressBar bar(30, "█", "░", TCOLOR_BLUE);
    // 进度更新逻辑
}
```

### 错误处理模式
```cpp
// 安全的系统命令执行
try {
    tc::systemConsole("some_command");
} catch (const std::exception& e) {
    tc::println(TCOLOR_RED, "命令执行失败: ", e.what(), TCOLOR_RESET);
}

// 终端尺寸安全检查
auto size = tc::printer().getSize();
if (size.first > 0 && size.second > 0) {
    // 安全的终端操作
}
```

### 性能优化技巧
```cpp
// 避免频繁的颜色重置
tc::tout << TCOLOR_RED;
// 多次红色输出
tc::tout << "错误1" << "错误2" << "错误3";
tc::tout << TCOLOR_RESET << std::endl;

// 批量操作减少函数调用
tc::printer()
    .moveCursor(10, 5)
    .print("内容1")
    .moveCursor(10, 6) 
    .print("内容2")
    .moveCursor(10, 7)
    .print("内容3");
```

TC.hpp 库经过精心设计，在保持功能丰富的同时，确保了高性能和跨平台兼容性。无论是简单的命令行工具还是复杂的终端应用，都能提供优秀的开发体验。