#include "../tc.hpp"
#include <vector>
#include <string>

void showSpinner(int seconds) {
    std::vector<std::string> frames = {"|", "/", "-", "\\"};
    int totalFrames = seconds * 10;
    
    tc::printer().hideCursor();
    
    for (int i = 0; i < totalFrames; ++i) {
        tc::print("\r", TCOLOR_CYAN, "加载中 ", frames[i % frames.size()], TCOLOR_RESET);
        tc::tsleep(100).execute();
    }
    
    tc::println("\r", TCOLOR_GREEN, "加载完成!    ", TCOLOR_RESET);
    tc::printer().showCursor();
}

void showBounce(int seconds) {
    std::string ball = "o";
    std::string empty = " ";
    int width = 20;
    int totalFrames = seconds * 20;
    int pos = 0;
    int dir = 1;
    
    tc::printer().hideCursor();
    
    for (int i = 0; i < totalFrames; ++i) {
        tc::print("\r[");
        for (int j = 0; j < width; ++j) {
            if (j == pos) {
                tc::print(TCOLOR_RED, ball, TCOLOR_RESET);
            } else {
                tc::print(empty);
            }
        }
        tc::print("]");
        
        pos += dir;
        if (pos == width - 1 || pos == 0) {
            dir = -dir;
        }
        
        tc::tsleep(50).execute();
    }
    
    tc::println("\n", TCOLOR_GREEN, "动画结束!", TCOLOR_RESET);
    tc::printer().showCursor();
}

int main() {
    tc::println("旋转加载动画:");
    showSpinner(3);
    
    tc::println("\n弹跳球动画:");
    showBounce(5);
    
    return 0;
}