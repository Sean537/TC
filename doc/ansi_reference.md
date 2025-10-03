# ANSI 转义码参考与平台兼容性

本文档整合了TC库中使用的ANSI转义码参考和跨平台兼容性信息。

## ANSI 转义码参考

### 基本格式
ANSI 转义序列格式：`\033[<参数>m`

### 文本样式控制
| 代码 | 效果 | 兼容性 |
|------|------|--------|
| `\033[0m` | 重置所有样式 | 所有终端 |
| `\033[1m` | 粗体 | 大多数终端 |
| `\033[3m` | 斜体 | 部分终端 |
| `\033[4m` | 下划线 | 大多数终端 |
| `\033[7m` | 反色 | 大多数终端 |

### 颜色控制
- **前景色**：`\033[30-37m`（标准色），`\033[90-97m`（亮色）
- **背景色**：`\033[40-47m`（标准色），`\033[100-107m`（亮色）
- **RGB颜色**：`\033[38;2;<r>;<g>;<b>m`（前景），`\033[48;2;<r>;<g>;<b>m`（背景）

## 跨平台兼容性

### Windows 平台支持
- **默认行为**：使用 ANSI 转义序列（Windows 10 1809+ 原生支持）
- **兼容模式**：定义 `TC_ENABLE_WIN32_CONSOLE_API` 宏可强制使用 Win32 Console API
- **启用方式**：
  - xmake: `xmake f --win32_console_api=y`
  - CMake: `-DTC_ENABLE_WIN32_CONSOLE_API=ON`
  - Makefile: `make WIN32_API=ON`

### 平台差异
- **Windows**：使用 Win32 API 实现，完全支持所有功能
- **Linux/macOS**：使用 ANSI 转义序列，兼容性取决于终端

## 在 TC.hpp 中的使用

TC库封装了平台差异，提供统一接口：

```cpp
// 跨平台颜色输出
tc::println(TCOLOR_RED, "红色文本", TCOLOR_RESET);
tc::println(TCOLOR_RGB(255, 128, 0), "橙色文本", TCOLOR_RESET);

// 终端控制
tc::printer().moveCursor(10, 5).print("在指定位置打印");
```

> 注意：便捷颜色函数（如 `tc::red()`）始终返回ANSI字符串，便于跨平台一致性。