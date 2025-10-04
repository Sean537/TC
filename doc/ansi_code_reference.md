# TC库ANSI转义码支持参考

本文档提供TC库实际支持的ANSI转义码功能参考，基于TC库的实际实现。

## TC库实际支持的ANSI功能

### 基础颜色和样式支持

TC库支持以下基础的ANSI转义码：

| ANSI代码 | TC宏定义 | 功能 | 实际支持 |
|----------|----------|------|----------|
| `\033[0m` | `TCOLOR_RESET` | 重置所有样式 | ✅ 支持 |
| `\033[1m` | `TFONT_BOLD` | 粗体/加粗 | ✅ 支持 |
| `\033[4m` | `TFONT_UNDERLINE` | 下划线 | ✅ 支持 |
| `\033[7m` | `TFONT_REVERSE` | 反色 | ✅ 支持 |

### 标准前景色（文字颜色）

| ANSI代码 | TC宏定义 | 颜色 | 实际支持 |
|----------|----------|------|----------|
| `\033[30m` | `TCOLOR_BLACK` | 黑色 | ✅ 支持 |
| `\033[31m` | `TCOLOR_RED` | 红色 | ✅ 支持 |
| `\033[32m` | `TCOLOR_GREEN` | 绿色 | ✅ 支持 |
| `\033[33m` | `TCOLOR_YELLOW` | 黄色 | ✅ 支持 |
| `\033[34m` | `TCOLOR_BLUE` | 蓝色 | ✅ 支持 |
| `\033[35m` | `TCOLOR_MAGENTA` | 洋红 | ✅ 支持 |
| `\033[36m` | `TCOLOR_CYAN` | 青色 | ✅ 支持 |
| `\033[37m` | `TCOLOR_WHITE` | 白色 | ✅ 支持 |

### 标准背景色

| ANSI代码 | TC宏定义 | 颜色 | 实际支持 |
|----------|----------|------|----------|
| `\033[40m` | `BCOLOR_BLACK` | 黑色背景 | ✅ 支持 |
| `\033[41m` | `BCOLOR_RED` | 红色背景 | ✅ 支持 |
| `\033[42m` | `BCOLOR_GREEN` | 绿色背景 | ✅ 支持 |
| `\033[43m` | `BCOLOR_YELLOW` | 黄色背景 | ✅ 支持 |
| `\033[44m` | `BCOLOR_BLUE` | 蓝色背景 | ✅ 支持 |
| `\033[45m` | `BCOLOR_MAGENTA` | 洋红背景 | ✅ 支持 |
| `\033[46m` | `BCOLOR_CYAN` | 青色背景 | ✅ 支持 |
| `\033[47m` | `BCOLOR_WHITE` | 白色背景 | ✅ 支持 |

## TC库不支持的ANSI功能

以下ANSI功能在TC库中**不**支持：

### 不支持的样式
- `\033[2m` (TFONT_FAINT) - 微弱/淡色
- `\033[3m` (TFONT_ITALIC) - 斜体
- `\033[5m` (TFONT_BLINK_SLOW) - 慢速闪烁
- `\033[6m` (TFONT_BLINK_FAST) - 快速闪烁
- `\033[8m` (TFONT_CONCEAL) - 隐藏文本
- `\033[9m` (TFONT_CROSSED) - 删除线

### 不支持的亮色
- `\033[90m` - `\033[97m` (亮色前景色)
- `\033[100m` - `\033[107m` (亮色背景色)

### 不支持的256色和RGB模式
- `\033[38;5;<n>m` (256色前景色)
- `\033[48;5;<n>m` (256色背景色)
- `\033[38;2;<r>;<g>;<b>m` (RGB前景色)
- `\033[48;2;<r>;<g>;<b>m` (RGB背景色)

### 不支持的光标和屏幕控制
- 光标移动控制 (`\033[H`, `\033[A`, `\033[B`, 等)
- 光标可见性控制 (`\033[?25l`, `\033[?25h`)
- 屏幕清屏操作 (`\033[2J`, `\033[J`, `\033[K`, 等)
- 屏幕缓冲区控制 (`\033[?47h`, `\033[?47l`)

## TC库的ANSI实现策略

TC库采用简单的ANSI转义码实现策略：

```cpp
// TC库实际的颜色宏定义（来自tc_colors.hpp）
#define TCOLOR_RESET "\033[0m"
#define TCOLOR_BLACK "\033[30m"
#define TCOLOR_RED "\033[31m"
#define TCOLOR_GREEN "\033[32m"
#define TCOLOR_YELLOW "\033[33m"
#define TCOLOR_BLUE "\033[34m"
#define TCOLOR_MAGENTA "\033[35m"
#define TCOLOR_CYAN "\033[36m"
#define TCOLOR_WHITE "\033[37m"

#define BCOLOR_BLACK "\033[40m"
#define BCOLOR_RED "\033[41m"
#define BCOLOR_GREEN "\033[42m"
#define BCOLOR_YELLOW "\033[43m"
#define BCOLOR_BLUE "\033[44m"
#define BCOLOR_MAGENTA "\033[45m"
#define BCOLOR_CYAN "\033[46m"
#define BCOLOR_WHITE "\033[47m"

#define TFONT_BOLD "\033[1m"
#define TFONT_UNDERLINE "\033[4m"
#define TFONT_REVERSE "\033[7m"
```

## 使用示例

### 基础颜色使用
```cpp
#include "tc.hpp"

int main() {
    // 使用TC库的颜色宏
    tc::println(TCOLOR_RED, "红色文本", TCOLOR_RESET);
    tc::println(BCOLOR_GREEN, "绿色背景文本", TCOLOR_RESET);
    
    // 组合使用样式
    tc::println(TCOLOR_BLUE, TFONT_BOLD, "蓝色粗体文本", TCOLOR_RESET);
    
    return 0;
}
```

### 流式输出使用
```cpp
#include "tc.hpp"

int main() {
    // 使用全局输出流
    tc::tout << TCOLOR_RED << "红色流输出" << TCOLOR_RESET << std::endl;
    
    return 0;
}
```

## 兼容性说明

TC库专注于提供基础的ANSI转义码支持，适用于大多数现代终端环境。对于高级的终端控制功能，建议使用专门的终端控制库。

> 注意：TC库不支持高级的ANSI功能如光标控制、屏幕操作等，这些功能需要专门的终端控制库来实现。