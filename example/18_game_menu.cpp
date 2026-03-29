#define TC_ENABLE_WIN32_CONSOLE_API  // 强制启用 Win32 Console API 宏（用于跨平台行为测试）
#include "../include/tc.hpp"
#include <vector>
#include <string>

// 注意：这个示例需要包含其他游戏示例的代码才能完整运行
// 这里只展示菜单部分的实现

int main() {
    tc::printer().clear();
    
    std::vector<std::string> gameOptions = {
        "贪吃蛇",
        "猜数字"
    };
    
    int choice;
    do {
        tc::printer().clear();
        tc::println(TCOLOR_CYAN, TFONT_BOLD, "TC.hpp 游戏示例", TCOLOR_RESET);
        tc::println(TCOLOR_CYAN, "==============", TCOLOR_RESET);
        tc::println();
        
        tc::println(TCOLOR_YELLOW, "[1] ", TCOLOR_RESET, "贪吃蛇");
        tc::println(TCOLOR_YELLOW, "[2] ", TCOLOR_RESET, "猜数字");
        tc::println();
        tc::println(TCOLOR_YELLOW, "[0] ", TCOLOR_RESET, "退出");
        tc::println();
        
        tc::print(TCOLOR_GREEN, "请选择游戏 (0-2): ", TCOLOR_RESET);
        std::cin >> choice;
        
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            choice = -1;
            continue;
        }
        
        std::cin.ignore(10000, '\n'); // 清除输入缓冲区
        
        switch (choice) {
            case 1:
                tc::println(TCOLOR_GREEN, "启动贪吃蛇游戏...", TCOLOR_RESET);
                tc::println("(实际应用中，这里会调用贪吃蛇游戏的代码)");
                tc::println("\n按任意键返回菜单...");
                tc::waitKey();
                break;
            case 2:
                tc::println(TCOLOR_GREEN, "启动猜数字游戏...", TCOLOR_RESET);
                tc::println("(实际应用中，这里会调用猜数字游戏的代码)");
                tc::println("\n按任意键返回菜单...");
                tc::waitKey();
                break;
            case 0:
                tc::println(TCOLOR_GREEN, "谢谢使用!", TCOLOR_RESET);
                break;
            default:
                tc::println(TCOLOR_RED, "无效选择，请重试。", TCOLOR_RESET);
                tc::waitKey();
        }
    } while (choice != 0);
    
    return 0;
}