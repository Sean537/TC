#include "../tc.hpp"

int main() {
    // 基本颜色
    tc::println(TCOLOR_RED, "红色文本", TCOLOR_RESET);
    tc::println(TCOLOR_GREEN, "绿色文本", TCOLOR_RESET);
    tc::println(TCOLOR_BLUE, "蓝色文本", TCOLOR_RESET);
    tc::println(TCOLOR_YELLOW, "黄色文本", TCOLOR_RESET);
    tc::println(TCOLOR_MAGENTA, "洋红文本", TCOLOR_RESET);
    tc::println(TCOLOR_CYAN, "青色文本", TCOLOR_RESET);
    tc::println(TCOLOR_WHITE, "白色文本", TCOLOR_RESET);
    
    // 背景色
    tc::println(TCOLOR_BLACK, BCOLOR_RED, "黑字红底", TCOLOR_RESET);
    tc::println(TCOLOR_WHITE, BCOLOR_BLUE, "白字蓝底", TCOLOR_RESET);
    tc::println(TCOLOR_BLACK, BCOLOR_GREEN, "黑字绿底", TCOLOR_RESET);
    tc::println(TCOLOR_BLACK, BCOLOR_YELLOW, "黑字黄底", TCOLOR_RESET);
    
    // RGB颜色
    tc::println(TCOLOR_RGB(255, 128, 0), "橙色文本", TCOLOR_RESET);
    tc::println(TCOLOR_RGB(128, 0, 128), "紫色文本", TCOLOR_RESET);
    tc::println(TCOLOR_RGB(0, 128, 128), "青绿色文本", TCOLOR_RESET);
    
    // 流式颜色输出
    tc::tout << TCOLOR_RED << "红色" << TCOLOR_GREEN << "绿色" 
             << TCOLOR_BLUE << "蓝色" << TCOLOR_RESET << std::endl;
    
    return 0;
}