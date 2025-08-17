#include "../include/tc.hpp"

int main() {
    // 获取终端尺寸
    auto size = tc::printer().getSize();
    tc::println("终端大小: ", size.first, "x", size.second);
    
    // 在终端中央打印文本
    int centerX = size.first / 2;
    int centerY = size.second / 2;
    
    tc::printer().moveCursor(centerX - 10, centerY);
    tc::println(TCOLOR_GREEN, "这是终端的中央位置", TCOLOR_RESET);
    
    // 在四个角落打印
    tc::printer().moveCursor(1, 1);
    tc::println(TCOLOR_RED, "左上角", TCOLOR_RESET);
    
    tc::printer().moveCursor(size.first - 6, 1);
    tc::println(TCOLOR_BLUE, "右上角", TCOLOR_RESET);
    
    tc::printer().moveCursor(1, size.second - 1);
    tc::println(TCOLOR_YELLOW, "左下角", TCOLOR_RESET);
    
    tc::printer().moveCursor(size.first - 6, size.second - 1);
    tc::println(TCOLOR_MAGENTA, "右下角", TCOLOR_RESET);
    
    // 在中间位置等待按键
    tc::printer().moveCursor(centerX - 10, centerY + 2);
    tc::println("按任意键继续...");
    tc::waitKey();
    
    return 0;
}