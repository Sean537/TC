#define TC_ENABLE_WIN32_CONSOLE_API  // 强制启用 Win32 Console API 宏（用于跨平台行为测试）
#include "../include/tc.hpp"
#include <random>

int main() {
    tc::printer().clear();
    tc::println(TCOLOR_CYAN, TFONT_BOLD, "猜数字游戏", TCOLOR_RESET);
    tc::println(TCOLOR_CYAN, "==========", TCOLOR_RESET);
    tc::println();
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1, 100);
    
    int secretNumber = distrib(gen);
    int guess;
    int attempts = 0;
    
    tc::println("我想了一个1到100之间的数字。");
    
    while (true) {
        tc::print(TCOLOR_GREEN, "请猜一个数字: ", TCOLOR_RESET);
        std::cin >> guess;
        
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            tc::println(TCOLOR_RED, "请输入一个有效的数字!", TCOLOR_RESET);
            continue;
        }
        
        attempts++;
        
        if (guess < secretNumber) {
            tc::println(TCOLOR_BLUE, "太小了! 再试一次。", TCOLOR_RESET);
        } else if (guess > secretNumber) {
            tc::println(TCOLOR_YELLOW, "太大了! 再试一次。", TCOLOR_RESET);
        } else {
            tc::println();
            tc::println(TCOLOR_GREEN, TFONT_BOLD, "恭喜! 你猜对了!", TCOLOR_RESET);
            tc::println("秘密数字是: ", secretNumber);
            tc::println("你用了 ", attempts, " 次尝试。");
            break;
        }
    }
    
    tc::println();
    tc::println("按任意键退出...");
    tc::waitKey();
    
    return 0;
}