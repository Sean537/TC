#include "../tc.hpp"

int main() {
    // 1. 基本颜色输出
    tc::tout << TCOLOR_GREEN << "Hello world!" << TCOLOR_RESET << std::endl;
    tc::tout << TCOLOR_RED << "红色" << TCOLOR_RESET << std::endl;
    tc::tout << TCOLOR_YELLOW << "黄色" << TCOLOR_RESET << std::endl;
    tc::tout << TCOLOR_BLUE << "蓝色" << TCOLOR_RESET << std::endl;

    // 2. 粗体/字体样式
    tc::tout << TFONT_BOLD << "粗体文本" << TFONT_RESET << std::endl;
    tc::tout << TFONT_THICK << "加粗文本" << TFONT_RESET << std::endl;

    // 3. RGB 颜色
    tc::tout << TCOLOR_RGB(255, 0, 0) << "RGB红" << TCOLOR_RESET << std::endl;
    tc::tout << TCOLOR_RGB(0, 255, 0) << "RGB绿" << TCOLOR_RESET << std::endl;
    tc::tout << TCOLOR_RGB(0, 0, 255) << "RGB蓝" << TCOLOR_RESET << std::endl;

    // 4. 延时输出
    tc::tout << "Wait for 1 second..." << std::endl;
    tc::tsleep(1000);
    tc::tout << "Done!" << std::endl;

    // 5. 延时流语法
    tc::tout << "A";
    tc::tsleep_stream << 500;
    tc::tout << "B" << std::endl;

    // 6. 基本打印
    tc::print("Hello ", "world!\n");
    tc::println("单行打印");
    tc::println("年龄: ", 25, ", 分数: ", 95.5);

    // 7. 彩色输出（print/println）
    tc::println(TCOLOR_RED, "红色文本");
    tc::println(TCOLOR_GREEN, BCOLOR_YELLOW, "绿色文字，黄色背景");
    tc::println(TCOLOR_BLUE, BCOLOR_WHITE, TFONT_BOLD, "蓝色粗体，白色背景");

    // 8. Printer类
    tc::printer()
        .print("Printer类输出")
        .println("，支持链式");
    tc::printer()
        .moveCursor(10, 5)
        .print("移动光标到(10,5)")
        .println();
    tc::printer().hideCursor();
    tc::printer().showCursor();
    auto size = tc::printer().getSize();
    tc::println("终端大小: ", size.first, "x", size.second);

    // 9. 等待
    tc::tout << "等待1.5秒后继续..." << std::endl;
    tc::wait(1.5);
    tc::tout << "继续执行" << std::endl;

    // 10. 等待按键
    tc::tout << "请按任意键继续..." << std::endl;
    tc::waitKey();

    // 11. 进度条示例
    tc::tout << "进度条示例:" << std::endl;
    tc::ProgressBar bar(50, "█", "░", TCOLOR_GREEN);

    for (int i = 0; i <= 100; ++i) {
        bar.show(i / 100.0, "处理中...");
        tc::wait(0.05);
    }
    bar.finish();
    return 0;
}