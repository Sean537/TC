#include "../include/tc.hpp"

int main() {
    tc::println("按任意键继续...");
    tc::waitKey();
    tc::println("继续执行");
    
    tc::println("\n按 'A' 键继续...");
    tc::waitKey('A');
    tc::println("检测到 'A' 键");
    
    tc::println("\n按 ESC 键退出...");
    tc::waitKey(KEY_ESC);
    tc::println("检测到 ESC 键");
    
    tc::println("\n按方向键测试:");
    tc::println("按上方向键...");
    tc::waitKey(KEY_UP);
    tc::println("检测到上方向键");
    
    tc::println("按下方向键...");
    tc::waitKey(KEY_DOWN);
    tc::println("检测到下方向键");
    
    tc::println("按左方向键...");
    tc::waitKey(KEY_LEFT);
    tc::println("检测到左方向键");
    
    tc::println("按右方向键...");
    tc::waitKey(KEY_RIGHT);
    tc::println("检测到右方向键");
    
    return 0;
}