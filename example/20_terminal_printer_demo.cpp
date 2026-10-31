/*
 * 20_terminal_printer_demo.cpp - 终端控制与Printer链式类示例
 * Terminal Control and Printer Chain Class Example
 * 
 * 这个示例展示了如何使用TC库的terminal命名空间和Printer链式类
 * 来控制终端，包括清屏、移动光标、获取终端大小等功能。
 * 
 * This example demonstrates how to use the TC library's terminal namespace
 * and Printer chain class to control the terminal, including clearing the screen,
 * moving the cursor, getting terminal size, etc.
 */
#define TC_ENABLE_WIN32_CONSOLE_API  // 强制启用 Win32 Console API 宏（用于跨平台行为测试）

#include "../include/tc.hpp"
#include <iostream>
#include <string>

// 使用terminal命名空间演示
void demoTerminalNamespace() {
    std::cout << TCOLOR_CYAN << "=== tc::terminal命名空间演示 ===" << TCOLOR_RESET << std::endl;
    tc::wait(1);
    
    // 清屏
    tc::terminal::clear();
    std::cout << "已清屏" << std::endl;
    tc::wait(1);
    
    // 移动光标到指定位置
    tc::terminal::moveCursor(20, 10);
    std::cout << "移动到位置(20,10)" << std::endl;
    tc::wait(1);
    
    // 获取终端大小
    auto [width, height] = tc::terminal::getSize();
    tc::terminal::moveCursor(1, height - 2);
    std::cout << "终端大小: " << width << "x" << height << std::endl;
    tc::wait(2);
}

// 使用Printer链式类演示
void demoPrinterClass() {
    std::cout << TCOLOR_MAGENTA << "=== tc::Printer链式类演示 ===" << TCOLOR_RESET << std::endl;
    tc::wait(1);
    
    // 创建Printer对象
    auto p = tc::printer();
    
    // 链式调用多个方法
    p.clear()
     .hideCursor()
     .moveCursor(10, 5)
     .print(TCOLOR_GREEN).print("位置(10,5)").print(TCOLOR_RESET)
     .println()
     .moveCursor(tc::Printer::Direction::Down, 2)
     .println("向下移动了2行")
     .moveCursor(tc::Printer::Direction::Right, 5)
     .println("向右移动了5格")
     .moveCursor(1, 10)
     .print("在第10行: ")
     .print(TCOLOR_YELLOW).print("黄色文本").print(TCOLOR_RESET)
     .println()
     .showCursor();
    
    // 获取终端大小
    auto [width, height] = p.getSize();
    p.moveCursor(1, height - 2)
     .println("终端大小: ", width, "x", height);
    
    tc::wait(2);
}

// 演示相对光标移动
void demoRelativeCursorMovement() {
    std::cout << TCOLOR_GREEN << "=== 相对光标移动演示 ===" << TCOLOR_RESET << std::endl;
    tc::wait(1);
    
    auto p = tc::printer();
    p.clear()
     .moveCursor(10, 5)
     .print("起始位置");
    
    // 向各个方向移动
    p.moveCursor(tc::Printer::Direction::Down, 2)
     .print("↓ 向下2行");
    
    p.moveCursor(tc::Printer::Direction::Right, 10)
     .print("→ 向右10格");
    
    p.moveCursor(tc::Printer::Direction::Up, 1)
     .print("↑ 向上1行");
    
    p.moveCursor(tc::Printer::Direction::Left, 5)
     .print("← 向左5格");
    
    // 移动到底部
    auto [width, height] = p.getSize();
    p.moveCursor(1, height - 2)
     .println("相对光标移动可以更方便地创建复杂的终端界面");
    
    tc::wait(2);
}

// 演示无闪烁更新
void demoFlickerFreeUpdate() {
    std::cout << TCOLOR_YELLOW << "=== 无闪烁更新演示 ===" << TCOLOR_RESET << std::endl;
    tc::wait(1);
    
    auto p = tc::printer();
    p.clear()
     .hideCursor()
     .moveCursor(10, 5)
     .println("这是一个无闪烁更新的演示");
    
    // 在固定位置更新计数器
    p.moveCursor(10, 7)
     .print("计数: ");
    
    // 记住计数器的位置
    int counterX = 17;
    int counterY = 7;
    
    // 更新计数器而不清屏
    for (int i = 0; i <= 10; i++) {
        p.moveCursor(counterX, counterY)
         .print("    ") // 清除之前的数字
         .moveCursor(counterX, counterY)
         .print(i);
        
        tc::wait(0.5);
    }
    
    p.moveCursor(10, 9)
     .println("演示完成，没有屏幕闪烁！")
     .showCursor();
    
    tc::wait(2);
}

int main() {
    // 演示terminal命名空间
    demoTerminalNamespace();
    
    // 演示Printer链式类
    demoPrinterClass();
    
    // 演示相对光标移动
    demoRelativeCursorMovement();
    
    // 演示无闪烁更新
    demoFlickerFreeUpdate();
    
    // 清屏并显示结束信息
    tc::terminal::clear();
    std::cout << TCOLOR_GREEN << "所有演示完成！" << TCOLOR_RESET << std::endl;
    
    return 0;
}