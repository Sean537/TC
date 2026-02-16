// #define TC_ENABLE_WIN32_CONSOLE_API  // 在 Windows 上强制启用 Windows 控制台 API，并禁用 ANSI 转义序列（不影响便捷颜色函数和其它平台）
#include "../include/tc.hpp"

int main() {
    // 基本样式
    tc::println(TFONT_BOLD, "粗体文本", TFONT_RESET);
    tc::println(TFONT_UNDERLINE, "下划线文本", TFONT_RESET);
    tc::println(TFONT_ITALIC, "斜体文本", TFONT_RESET);
    tc::println(TFONT_CROSSED, "删除线文本", TFONT_RESET);
    tc::println(TFONT_REVERSE, "反色文本", TFONT_RESET);
    
    // 组合样式
    tc::println(TFONT_BOLD, TFONT_UNDERLINE, "粗体下划线文本", TFONT_RESET);
    tc::println(TFONT_ITALIC, TFONT_CROSSED, "斜体删除线文本", TFONT_RESET);
    
    // 样式与颜色组合
    tc::println(TCOLOR_RED, TFONT_BOLD, "红色粗体文本", TCOLOR_RESET);
    tc::println(TCOLOR_BLUE, TFONT_UNDERLINE, "蓝色下划线文本", TCOLOR_RESET);
    tc::println(TCOLOR_GREEN, BCOLOR_YELLOW, TFONT_BOLD, "绿字黄底粗体", TCOLOR_RESET);
    
    return 0;
}