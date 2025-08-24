/*
 * 02_color_output.cpp - 颜色功能示例
 * Color Functions Example
 * 
 * 这个示例展示了TC库中所有颜色控制功能的用法，
 * 包括全局颜色宏、ColorController类、颜色包装器类和便捷颜色函数。
 * 
 * This example demonstrates the usage of all color control features in the TC library,
 * including global color macros, ColorController class, color wrapper classes,
 * and convenient color functions.
 */

#include "../include/tc.hpp"
#include <iostream>
#include <string>

// 演示全局颜色宏
void demoGlobalMacros() {
    std::cout << TCOLOR_CYAN << "=== 全局颜色宏演示 ===" << TCOLOR_RESET << std::endl;
    
    // 前景色
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
    
    // 组合使用
    std::cout << TCOLOR_RED << BCOLOR_YELLOW << "红字黄底" << TCOLOR_RESET << std::endl;
    std::cout << TCOLOR_BLUE << BCOLOR_WHITE << "蓝字白底" << TCOLOR_RESET << std::endl;
    
    // 字体样式
    std::cout << TFONT_BOLD << "粗体文本" << TFONT_RESET << std::endl;
    std::cout << TFONT_UNDERLINE << "下划线文本" << TFONT_RESET << std::endl;
    std::cout << TFONT_ITALIC << "斜体文本" << TFONT_RESET << std::endl;
    std::cout << TFONT_BLINK_SLOW << "闪烁文本" << TFONT_RESET << std::endl;
    std::cout << TFONT_REVERSE << "反色文本" << TFONT_RESET << std::endl;
    
    // RGB颜色
    tc::println(TCOLOR_RGB(255, 128, 0), "橙色文本 (RGB: 255,128,0)", TCOLOR_RESET);
    tc::println(TCOLOR_RGB(128, 0, 255), "紫色文本 (RGB: 128,0,255)", TCOLOR_RESET);
    tc::println(TCOLOR_RGB(0, 255, 128), "薄荷绿文本 (RGB: 0,255,128)", TCOLOR_RESET);
    
    // 流式颜色输出
    tc::tout << TCOLOR_RED << "红色" << TCOLOR_GREEN << "绿色" 
             << TCOLOR_BLUE << "蓝色" << TCOLOR_RESET << std::endl;
    
    tc::wait(1);
}

// 演示ColorController类
void demoColorController() {
    std::cout << TCOLOR_CYAN << "=== ColorController类演示 ===" << TCOLOR_RESET << std::endl;
    
    // 设置颜色
    tc::ColorController::setColor(tc::ColorController::Color::RED);
    std::cout << "红色文本" << std::endl;
    
    tc::ColorController::setColor(tc::ColorController::Color::BRIGHT_GREEN);
    std::cout << "亮绿色文本" << std::endl;
    
    tc::ColorController::setColor(tc::ColorController::Color::BLUE);
    std::cout << "蓝色文本" << std::endl;
    
    // 设置RGB颜色
    tc::ColorController::setRGBColor(255, 128, 0);
    std::cout << "橙色文本 (RGB: 255,128,0)" << std::endl;
    
    // 设置粗体
    tc::ColorController::setBold(true);
    std::cout << "粗体文本" << std::endl;
    
    // 重置所有属性
    tc::ColorController::setColor(tc::ColorController::Color::RESET);
    std::cout << "正常文本" << std::endl;
    
    tc::wait(1);
}

// 演示颜色包装器类
void demoColorWrappers() {
    std::cout << TCOLOR_CYAN << "=== 颜色包装器类演示 ===" << TCOLOR_RESET << std::endl;
    
    // 使用ColorWrapper
    std::cout << tc::ColorWrapper(tc::ColorController::Color::RED) << "红色文本" 
              << tc::ColorWrapper(tc::ColorController::Color::RESET) << std::endl;
    
    // 使用RGBColorWrapper
    std::cout << tc::RGBColorWrapper(255, 128, 0) << "橙色文本" 
              << tc::ColorWrapper(tc::ColorController::Color::RESET) << std::endl;
    
    // 使用FontStyleWrapper
    std::cout << tc::FontStyleWrapper(true) << "粗体文本" 
              << tc::FontStyleWrapper(false) << std::endl;
    
    tc::wait(1);
}

// 演示便捷颜色函数
void demoColorFunctions() {
    std::cout << TCOLOR_CYAN << "=== 便捷颜色函数演示 ===" << TCOLOR_RESET << std::endl;
    
    // 使用colorize函数
    std::string coloredText = tc::colorize("彩色文本", tc::ColorController::Color::CYAN);
    std::cout << coloredText << std::endl;
    
    // 使用便捷颜色函数
    std::cout << tc::red("红色文本") << std::endl;
    std::cout << tc::green("绿色文本") << std::endl;
    std::cout << tc::blue("蓝色文本") << std::endl;
    std::cout << tc::yellow("黄色文本") << std::endl;
    
    // 组合使用
    std::string message = "重要提示";
    std::cout << tc::colorize(message, tc::ColorController::Color::BRIGHT_RED) << std::endl;
    
    tc::wait(1);
}

// 演示实际应用场景
void demoRealWorldUsage() {
    std::cout << TCOLOR_CYAN << "=== 实际应用场景演示 ===" << TCOLOR_RESET << std::endl;
    
    // 模拟日志输出
    std::cout << TCOLOR_GREEN << "[INFO] " << TCOLOR_RESET << "系统启动成功" << std::endl;
    std::cout << TCOLOR_YELLOW << "[WARN] " << TCOLOR_RESET << "磁盘空间不足" << std::endl;
    std::cout << TCOLOR_RED << "[ERROR] " << TCOLOR_RESET << "无法连接到服务器" << std::endl;
    
    // 模拟命令行界面
    std::cout << std::endl << TFONT_BOLD << "命令行菜单：" << TFONT_RESET << std::endl;
    std::cout << TCOLOR_CYAN << "1. " << TCOLOR_RESET << "查看文件" << std::endl;
    std::cout << TCOLOR_CYAN << "2. " << TCOLOR_RESET << "编辑文件" << std::endl;
    std::cout << TCOLOR_CYAN << "3. " << TCOLOR_RESET << "删除文件" << std::endl;
    std::cout << TCOLOR_CYAN << "0. " << TCOLOR_RESET << "退出" << std::endl;
    
    // 模拟代码高亮
    std::cout << std::endl << TFONT_BOLD << "代码高亮示例：" << TFONT_RESET << std::endl;
    std::cout << TCOLOR_BLUE << "int" << TCOLOR_RESET << " main() {" << std::endl;
    std::cout << "    " << TCOLOR_GREEN << "std::cout" << TCOLOR_RESET << " << " 
              << TCOLOR_YELLOW << "\"Hello, World!\"" << TCOLOR_RESET << " << " 
              << TCOLOR_GREEN << "std::endl" << TCOLOR_RESET << ";" << std::endl;
    std::cout << "    " << TCOLOR_BLUE << "return" << TCOLOR_RESET << " 0;" << std::endl;
    std::cout << "}" << std::endl;
    
    tc::wait(1);
}

int main() {
    // 清屏
    tc::terminal::clear();
    
    std::cout << TFONT_BOLD << "TC库颜色功能演示" << TFONT_RESET << std::endl;
    std::cout << "======================" << std::endl << std::endl;
    
    // 演示全局颜色宏
    demoGlobalMacros();
    std::cout << std::endl;
    
    // 演示ColorController类
    demoColorController();
    std::cout << std::endl;
    
    // 演示颜色包装器类
    demoColorWrappers();
    std::cout << std::endl;
    
    // 演示便捷颜色函数
    demoColorFunctions();
    std::cout << std::endl;
    
    // 演示实际应用场景
    demoRealWorldUsage();
    std::cout << std::endl;
    
    // 结束信息
    std::cout << TCOLOR_GREEN << "所有颜色功能演示完成！" << TCOLOR_RESET << std::endl;
    
    return 0;
}
