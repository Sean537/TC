#include "../tc.hpp"

int main() {
    // 基本进度条
    tc::ProgressBar bar1(30, "#", "-", TCOLOR_GREEN);
    for (int i = 0; i <= 100; ++i) {
        bar1.show(i / 100.0, "处理中...");
        tc::wait(0.02);
    }
    bar1.finish("完成！");
    
    // 自定义进度条
    tc::println("\n自定义进度条:");
    tc::ProgressBar bar2(40, "█", "░", TCOLOR_CYAN);
    for (int i = 0; i <= 100; ++i) {
        bar2.show(i / 100.0, "加载中...");
        tc::wait(0.01);
    }
    bar2.finish("加载完成！");
    
    // 模拟文件下载进度条
    tc::println("\n模拟下载:");
    tc::ProgressBar bar3(50, "▓", "▒", TCOLOR_BLUE);
    for (int i = 0; i <= 100; ++i) {
        bar3.show(i / 100.0, "下载中... " + std::to_string(i) + "%");
        tc::wait(0.03);
    }
    bar3.finish("下载完成！");
    
    return 0;
}