#define TC_ENABLE_WIN32_CONSOLE_API  // 强制启用 Win32 Console API 宏（用于跨平台行为测试）
#include "../include/tc.hpp"
#include <string>

void typewriter(const std::string& text, int delay_ms = 50) {
    for (char c : text) {
        tc::print(c);
        std::cout.flush();  // 立即刷新输出
        tc::wait(delay_ms / 1000.0);  // 将毫秒转换为秒
    }
    tc::println();
    std::cout.flush();
}

int main() {
    // 基本打字机效果
    typewriter("这是一个打字机效果的演示...");
    
    // 彩色打字机效果
    tc::print(TCOLOR_GREEN);
    typewriter("这是绿色的打字机效果...", 70);
    tc::print(TCOLOR_RESET);
    
    // 带样式的打字机效果
    tc::print(TCOLOR_YELLOW, TFONT_BOLD);
    typewriter("这是黄色粗体的打字机效果...", 30);
    tc::print(TCOLOR_RESET);
    
    // 变速打字机效果
    tc::print(TCOLOR_CYAN);
    std::string text = "这是变速的打字机效果...";
    for (char c : text) {
        tc::print(c);
        std::cout.flush();  // 立即刷新输出
        int delay = (c == ' ' || c == '.') ? 200 : 40;
        tc::wait(delay / 1000.0);  // 将毫秒转换为秒
    }
    tc::println();
    tc::print(TCOLOR_RESET);
    std::cout.flush();
    
    return 0;
}