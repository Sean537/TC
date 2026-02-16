# TC 库 ANSI 转义码支持与兼容性参考

本文档基于源码实现梳理出 TC 的实际功能与兼容性情况。请注意：
- “库支持”指 TC 具备输出或映射该功能的能力（有宏/接口或可直出 ANSI 序列）；“是否可见/效果如何”由“终端”决定。
- Windows 下存在两条实现路径：
  - 默认（未定义 TC_ENABLE_WIN32_CONSOLE_API）：颜色/样式走 ANSI 转义，TC 在 Win32Console 中启用虚拟终端处理（VT / ENABLE_VIRTUAL_TERMINAL_PROCESSING）以让 ANSI 生效；光标/清屏等“终端控制”统一走 Win32 API。
  - 定义 TC_ENABLE_WIN32_CONSOLE_API：颜色/样式走 Win32 API，Win32Console 会关闭 VT；tc::tout / tc::print 会解析常见 ANSI 颜色序列并映射到 Win32 行为。此路径在样式维度（斜体/下划线/反色/闪烁等）与 ANSI 路径不等价，部分样式被忽略。
- Windows 上 TC 在构造 Win32Console 时设置控制台代码页为 UTF-8（SetConsoleOutputCP/SetConsoleCP），但 MSVC 的窄流与终端字体/控制台宿主仍可能影响中文显示，必要时请结合 setlocale/_setmode 或 wcout。

## 实现路径总览

- 颜色/样式
  - 未定义 TC_ENABLE_WIN32_CONSOLE_API：TCOLOR_*/BCOLOR_*/TFONT_* 直接输出 ANSI；RGB 使用 38;2;r;g;b。Win10 1809+ 需 VT 才能正确渲染。
  - 定义 TC_ENABLE_WIN32_CONSOLE_API：上述宏为包装器，经 ColorController/Win32Console 走 Win32 API；tc::tout / tc::print 在 Windows 分支会识别若干 ANSI 序列并转为 Win32 行为（主要是颜色/重置/粗体），不支持的样式将被忽略。
- 终端控制（清屏/光标）始终：Windows 用 Win32 API（通过 Win32Console），非 Windows 输出 ANSI。
- 256 色与真彩：库侧可直接输出 ANSI（38;5;n / 48;5;n / 38;2;r;g;b / 48;2;r;g;b）；是否呈现取决于终端能力。

## 功能矩阵（按类别）

说明：
- ANSI兼容 指“典型现代终端在启用 ANSI/VT 条件下的渲染情况”；Win32兼容 指“定义 TC_ENABLE_WIN32_CONSOLE_API、走 Win32 API 时的表现”。  
- 条目中的“库侧”描述 TC 如何输出/映射该能力。

### 1) 颜色与样式

| 功能项 | ANSI示例 | TC 封装/库侧 | ANSI兼容 | Win32兼容 | 备注 |
|---|---|---|---|---|---|
| 重置 | \033[0m | TCOLOR_RESET / TFONT_RESET | 广泛支持 | 映射为重置颜色 | Windows 下通过 API 重置属性 |
| 粗体 | \033[1m | TFONT_BOLD | 广泛支持 | 通过强度位近似 | Win32 使用 FOREGROUND_INTENSITY 近似 |
| 下划线 | \033[4m | TFONT_UNDERLINE | 多数现代终端支持 | 通常不渲染 | Win32 路径被忽略（不生效） |
| 反色 | \033[7m | TFONT_REVERSE | 多数现代终端支持 | 通常不渲染 | Win32 路径被忽略（不生效） |
| 斜体 | \033[3m | 可直出 ANSI | 终端差异较大 | 不渲染 | Win32 路径被忽略 |
| 微弱 | \033[2m | 可直出 ANSI | 终端差异较大 | 不渲染 | Win32 路径被忽略 |
| 闪烁 | \033[5m/\033[6m | 可直出 ANSI | 多数终端关闭或不渲染 | 不渲染 | 不建议依赖 |
| 隐藏 | \033[8m | 可直出 ANSI | 多数终端支持 | 不渲染 | Win32 路径被忽略 |
| 删除线 | \033[9m | 可直出 ANSI | 终端差异较大 | 不渲染 | Win32 路径被忽略 |
| 标准前景色 | \033[30..37m | TCOLOR_* | 广泛支持 | 可映射近似色 | Win32 颜色为 16 色 |
| 标准背景色 | \033[40..47m | BCOLOR_* | 广泛支持 | 可映射近似色 | 同上 |
| 亮色前景 | \033[90..97m | 可直出 ANSI | 现代终端良好 | 近似映射 | Win32 仍受 16 色限制 |
| 亮色背景 | \033[100..107m | 可直出 ANSI | 现代终端良好 | 近似映射 | 同上 |
| 256 色 | 38;5;n / 48;5;n | 可直出 ANSI | 终端普遍支持 | 需 ANSI+VT；近似 | Win32 路径不原生支持 |
| RGB 真彩 | 38;2;r;g;b / 48;2;r;g;b | TCOLOR_RGB(r,g,b) (ANSI) | 取决终端与主题 | 需 ANSI+VT；近似 | Win32 路径以 16 色近似 |

注：定义 TC_ENABLE_WIN32_CONSOLE_API 后，tc::tout 与 tc::print 对常见 ANSI 颜色/重置/粗体会尝试做解析映射；其余样式多被忽略。

### 2) 光标与屏幕控制

| 功能项 | ANSI示例 | TC 封装/库侧 | ANSI兼容 | Win32兼容 | 备注 |
|---|---|---|---|---|---|
| 清屏 | \033[2J | tc::terminal::clear() / tc::Printer::clear() | 现代终端支持 | Win32 API 清屏 | Windows 一律走 API |
| 光标定位 | \033[y;xH | tc::terminal::moveCursor(x,y) / Printer::moveCursor | 现代终端支持 | Win32 API 定位 | Windows 一律走 API（0 基转换） |
| 光标显隐 | \033[?25l / \033[?25h | tc::Printer::hideCursor/showCursor | 现代终端支持 | Win32 API 显隐 | Windows 一律走 API |
| 获取尺寸 | — | tc::terminal::getSize() | ioctl TIOCGWINSZ | Win32 API 查询 | 无通用 ANSI |

## 使用示例

基础颜色（ANSI 路径）：
```cpp
#include "tc.hpp"
int main() {
    tc::println(TCOLOR_RED, "红色文本", TCOLOR_RESET);
    tc::println(BCOLOR_GREEN, "绿色背景", TCOLOR_RESET);
    tc::tout << TCOLOR_BLUE << "蓝色流式输出" << TCOLOR_RESET << std::endl;
    return 0;
}
```

Windows 控制台建议初始化（仅示意，按需使用）：
```cpp
#ifdef _WIN32
#include <windows.h>
static void init_console_utf8_vt() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    if (h != INVALID_HANDLE_VALUE) {
        DWORD m = 0;
        if (GetConsoleMode(h, &m)) SetConsoleMode(h, m | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
    }
}
#endif

int main() {
#ifdef _WIN32
    init_console_utf8_vt();
#endif
    // ...
}
```

## 兼容性要点与排障

- Windows
  - 默认路径（未定义 TC_ENABLE_WIN32_CONSOLE_API）：依赖 VT 渲染 ANSI。建议使用 Windows Terminal 或新版 PowerShell/ConHost；在旧环境可能无法渲染斜体/闪烁/真彩。
  - 定义 TC_ENABLE_WIN32_CONSOLE_API：关闭 VT，颜色/重置/粗体通过 Win32 API 映射；斜体/下划线/反色/删除线等样式多数不生效。
  - 代码页与中文：TC 会将控制台设为 UTF-8，但 MSVC 窄流/宿主控制台仍可能导致乱码；必要时 setlocale(LC_ALL,".UTF-8")、_setmode(stdout,_O_U8TEXT) 并使用 wcout。
- 非 Windows
  - 大多数现代终端对 ANSI/256 色/RGB 支持良好；极少数简化终端可能不支持某些样式或真彩。
- 若期望“尽可能一致的样式呈现”，优先走 ANSI 路径并使用现代终端；Win32 路径更偏向“保守兼容”。

## 关键实现摘录（便于对照）

- 未定义 TC_ENABLE_WIN32_CONSOLE_API：TCOLOR_*/BCOLOR_*/TFONT_* 直接输出 ANSI；RGB 使用 \033[38;2;r;g;b m。
- 定义 TC_ENABLE_WIN32_CONSOLE_API：上述宏为包装器，经 ColorController/Win32Console 使用 Win32 API；Win32Console 构造时关闭 VT；tc::tout / tc::print 会解析若干 ANSI 并映射到 Win32（颜色/重置/粗体），多数样式被忽略。
- 终端控制（清屏/光标）在 Windows 始终走 Win32 API，非 Windows 输出 ANSI。