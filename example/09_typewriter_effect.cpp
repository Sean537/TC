#include "../include/tc.hpp"
#include <string>

void typewriter(const std::string& text, int delay_ms = 50) {
    for (char c : text) {
        tc::print(c);
        tc::tsleep(delay_ms).execute();
    }
    tc::println();
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
        int delay = (c == ' ' || c == '.') ? 200 : 40;
        tc::tsleep(delay).execute();
    }
    tc::println(TCOLOR_RESET);
    
    return 0;
}