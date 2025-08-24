/*
 * 19_key_press_detection.cpp - 按键检测示例
 * Key Press Detection Example
 * 
 * 这个示例展示了如何使用TC库的isKeyPressed函数来检测按键状态，
 * 并创建一个简单的交互式绘图程序。用户可以使用方向键移动光标，
 * 使用空格键绘制或擦除，使用ESC键退出。
 * 
 * This example demonstrates how to use the TC library's isKeyPressed function
 * to detect key states and create a simple interactive drawing program.
 * Users can move the cursor with arrow keys, draw or erase with space key,
 * and exit with ESC key.
 */

#include "../include/tc.hpp"
#include <iostream>
#include <vector>
#include <string>

// 画布大小 | Canvas size
const int WIDTH = 40;
const int HEIGHT = 20;

// 绘图符号 | Drawing symbols
const char CURSOR = 'O';
const char DRAWN = '#';
const char EMPTY = ' ';

// 绘图状态 | Drawing state
struct DrawingState {
    int x = WIDTH / 2;
    int y = HEIGHT / 2;
    std::vector<std::string> canvas;
    bool drawing = false;
    
    DrawingState() {
        // 初始化空白画布 | Initialize empty canvas
        canvas.resize(HEIGHT, std::string(WIDTH, EMPTY));
    }
};

// 绘制画布 | Draw canvas
void drawCanvas(const DrawingState& state) {
    tc::terminal::clear();
    
    std::cout << "简易绘图程序 | Simple Drawing Program" << std::endl;
    std::cout << "使用方向键移动，空格键绘制/擦除，ESC键退出" << std::endl;
    std::cout << "Use arrow keys to move, space to draw/erase, ESC to exit" << std::endl << std::endl;
    
    // 绘制顶部边框 | Draw top border
    std::cout << "+";
    for (int i = 0; i < WIDTH; i++) std::cout << "-";
    std::cout << "+" << std::endl;
    
    // 绘制画布内容 | Draw canvas content
    for (int y = 0; y < HEIGHT; y++) {
        std::cout << "|";
        for (int x = 0; x < WIDTH; x++) {
            if (x == state.x && y == state.y) {
                // 绘制光标 | Draw cursor
                std::cout << TCOLOR_CYAN << CURSOR << TCOLOR_RESET;
            } else {
                // 绘制画布内容 | Draw canvas content
                if (state.canvas[y][x] == DRAWN) {
                    std::cout << TCOLOR_YELLOW << DRAWN << TCOLOR_RESET;
                } else {
                    std::cout << EMPTY;
                }
            }
        }
        std::cout << "|" << std::endl;
    }
    
    // 绘制底部边框 | Draw bottom border
    std::cout << "+";
    for (int i = 0; i < WIDTH; i++) std::cout << "-";
    std::cout << "+" << std::endl;
    
    // 显示当前状态 | Show current state
    std::cout << "位置 | Position: (" << state.x << ", " << state.y << ")  ";
    std::cout << "模式 | Mode: " << (state.drawing ? "绘制 | Drawing" : "移动 | Moving") << std::endl;
}

int main() {
    DrawingState state;
    bool running = true;
    
    // 隐藏光标 | Hide cursor
    std::cout << "\033[?25l";  // ANSI隐藏光标序列
    
    // 显示初始画布 | Show initial canvas
    drawCanvas(state);
    
    // 主循环 | Main loop
    while (running) {
        // 检测按键 | Detect key presses
        if (tc::isKeyPressed(KEY_ESC)) {
            running = false;
        }
        
        if (tc::isKeyPressed(KEY_UP) && state.y > 0) {
            state.y--;
            drawCanvas(state);
            tc::wait(0.1); // 防止移动过快 | Prevent too fast movement
        }
        
        if (tc::isKeyPressed(KEY_DOWN) && state.y < HEIGHT - 1) {
            state.y++;
            drawCanvas(state);
            tc::wait(0.1);
        }
        
        if (tc::isKeyPressed(KEY_LEFT) && state.x > 0) {
            state.x--;
            drawCanvas(state);
            tc::wait(0.1);
        }
        
        if (tc::isKeyPressed(KEY_RIGHT) && state.x < WIDTH - 1) {
            state.x++;
            drawCanvas(state);
            tc::wait(0.1);
        }
        
        if (tc::isKeyPressed(KEY_SPACE)) {
            // 切换当前位置的绘制状态 | Toggle drawing state at current position
            if (state.canvas[state.y][state.x] == EMPTY) {
                state.canvas[state.y][state.x] = DRAWN;
            } else {
                state.canvas[state.y][state.x] = EMPTY;
            }
            drawCanvas(state);
            tc::wait(0.2); // 防止一次按键多次触发 | Prevent multiple triggers from one key press
        }
        
        // 切换绘制模式 | Toggle drawing mode
        if (tc::isKeyPressed('d') || tc::isKeyPressed('D')) {
            state.drawing = !state.drawing;
            drawCanvas(state);
            tc::wait(0.2);
        }
        
        // 如果处于绘制模式，自动在当前位置绘制 | If in drawing mode, automatically draw at current position
        if (state.drawing && state.canvas[state.y][state.x] == EMPTY) {
            state.canvas[state.y][state.x] = DRAWN;
            drawCanvas(state);
        }
        
        tc::wait(0.01); // 减少CPU使用率 | Reduce CPU usage
    }
    
    // 显示光标 | Show cursor
    std::cout << "\033[?25h";  // ANSI显示光标序列
    tc::terminal::clear();
    
    std::cout << "感谢使用简易绘图程序！" << std::endl;
    std::cout << "Thank you for using the Simple Drawing Program!" << std::endl;
    
    return 0;
}
