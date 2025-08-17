#include "../include/tc.hpp"

int main() {
    // 清屏
    tc::printer().clear();
    
    // 移动光标
    tc::printer().moveCursor(10, 5);
    tc::println("在位置(10,5)打印");
    
    tc::printer().moveCursor(15, 10);
    tc::println("在位置(15,10)打印");
    
    // 相对移动
    tc::printer().moveCursor(tc::Printer::Direction::Up, 2);
    tc::println("上移2行");
    
    tc::printer().moveCursor(tc::Printer::Direction::Right, 5);
    tc::println("右移5列");
    
    // 隐藏/显示光标
    tc::println("\n\n光标将在3秒内隐藏...");
    tc::printer().hideCursor();
    tc::wait(3.0);
    tc::printer().showCursor();
    tc::println("光标已显示");
    
    return 0;
}