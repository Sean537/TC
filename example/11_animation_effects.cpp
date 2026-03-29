#define TC_ENABLE_WIN32_CONSOLE_API  // 强制启用 Win32 Console API 宏（用于跨平台行为测试）
#include "../include/tc.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <chrono>
#include <thread>

#ifndef _WIN32
#include <termios.h>
#include <unistd.h>
#endif

void showSpinner(int seconds) {
    std::vector<std::string> frames = {"|", "/", "-", "\\"};
    int totalFrames = seconds * 10;
    
    auto& printer = tc::printer().hideCursor();
    tc::terminal::flush();  // 确保光标隐藏立即生效
    
    for (int i = 0; i < totalFrames; ++i) {
        printer.print("\r", TCOLOR_CYAN, "加载中 ", frames[i % frames.size()], TCOLOR_RESET);
        tc::terminal::flush();
        tc::wait(0.1);
    }
    
    printer.print("\r", TCOLOR_GREEN, "加载完成!    ", TCOLOR_RESET)
           .println()
           .showCursor()
           .flush();
}

void showBounce(int seconds) {
    std::string ball = "o";
    std::string empty = " ";
    int width = 20;
    int totalFrames = seconds * 20;
    int pos = 0;
    int dir = 1;
    
    auto& printer = tc::printer().hideCursor();
    tc::terminal::flush();  // 确保光标隐藏立即生效
    
    for (int i = 0; i < totalFrames; ++i) {
        printer.print("\r[");
        for (int j = 0; j < width; ++j) {
            if (j == pos) {
                printer.print(TCOLOR_RED, ball, TCOLOR_RESET);
            } else {
                printer.print(empty);
            }
        }
        printer.print("]");
        tc::terminal::flush();  // 使用新的全局刷新函数
        
        pos += dir;
        if (pos == width - 1 || pos == 0) {
            dir = -dir;
        }
        
        tc::wait(0.05);
    }
    
    printer.println()
           .println(TCOLOR_GREEN, "动画结束!", TCOLOR_RESET)
           .showCursor();
    tc::terminal::flush();  // 确保所有更改立即生效
}

int main() {
    tc::println("旋转加载动画:");
    showSpinner(3);
    
    tc::println("\n弹跳球动画:");
    showBounce(5);
    
    return 0;
}