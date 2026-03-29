#define TC_ENABLE_WIN32_CONSOLE_API  // 强制启用 Win32 Console API 宏（用于跨平台行为测试）
#include "../include/tc.hpp"
#include <vector>
#include <string>
#include <iostream>

#ifndef _WIN32
#include <termios.h>
#include <unistd.h>
#endif

int showMenu(const std::vector<std::string>& options, const std::string& title = "菜单") {
    tc::printer().clear();
    
    // 显示标题
    tc::println(TCOLOR_CYAN, TFONT_BOLD, title, TCOLOR_RESET);
    tc::println(TCOLOR_CYAN, std::string(title.length(), '='), TCOLOR_RESET);
    tc::println();
    
    // 显示选项
    for (size_t i = 0; i < options.size(); ++i) {
        tc::println(TCOLOR_YELLOW, "[", i + 1, "] ", TCOLOR_RESET, options[i]);
    }
    
    tc::println();
    tc::println(TCOLOR_YELLOW, "[0] ", TCOLOR_RESET, "退出");
    tc::println();
    
    // 获取用户输入
    int choice = -1;
    std::string input;
    
    while (true) {
        tc::print(TCOLOR_GREEN, "请选择 (0-", options.size(), "): ", TCOLOR_RESET);
        std::cout.flush();  // 确保提示立即显示
        
        std::getline(std::cin, input);
        
        // 转换输入为数字
        try {
            if (input.empty()) {
                continue;
            }
            choice = std::stoi(input);
            if (choice >= 0 && choice <= static_cast<int>(options.size())) {
                break;
            }
        } catch (...) {
            choice = -1;
        }
    }
    
    return choice;
}

int main() {
    // 设置输入模式
#ifndef _WIN32
    termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~ICANON;
    newt.c_lflag &= ~ECHO;
#endif

    std::vector<std::string> mainOptions = {
        "选项一",
        "选项二",
        "选项三",
        "选项四"
    };
    
    int choice;
    do {
        choice = showMenu(mainOptions, "彩色菜单示例");
        
        tc::printer().clear();
        switch (choice) {
            case 1:
                tc::println(TCOLOR_GREEN, "您选择了选项一", TCOLOR_RESET);
                break;
            case 2:
                tc::println(TCOLOR_BLUE, "您选择了选项二", TCOLOR_RESET);
                break;
            case 3:
                tc::println(TCOLOR_MAGENTA, "您选择了选项三", TCOLOR_RESET);
                break;
            case 4:
                tc::println(TCOLOR_YELLOW, "您选择了选项四", TCOLOR_RESET);
                break;
            case 0:
                tc::println(TCOLOR_RED, "退出程序", TCOLOR_RESET);
                break;
        }
        
        if (choice != 0) {
            tc::println("\n按任意键返回菜单...");
            tc::waitKey();
        }
    } while (choice != 0);
    
#ifndef _WIN32
    // 恢复终端设置
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
#endif

    return 0;
}