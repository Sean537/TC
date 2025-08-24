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
    int prevX = WIDTH / 2;
    int prevY = HEIGHT / 2;
    std::vector<std::string> canvas;
    bool drawing = false;
    bool firstDraw = true;
    
    DrawingState() {
        // 初始化空白画布 | Initialize empty canvas
        canvas.resize(HEIGHT, std::string(WIDTH, EMPTY));
    }
};

// 初始化绘图界面 | Initialize drawing interface
void initDrawingInterface() {
    auto p = tc::printer();
    
    // 隐藏光标 | Hide cursor
    p.hideCursor();
    
    // 清屏并绘制初始界面 | Clear screen and draw initial interface
    p.clear()
     .println("简易绘图程序 | Simple Drawing Program")
     .println("使用方向键移动，空格键绘制/擦除，D键切换绘制模式，ESC键退出")
     .println("Use arrow keys to move, space to draw/erase, D to toggle drawing mode, ESC to exit")
     .println();
    
    // 绘制顶部边框 | Draw top border
    p.print("+");
    for (int i = 0; i < WIDTH; i++) p.print("-");
    p.println("+");
    
    // 绘制空白画布 | Draw empty canvas
    for (int y = 0; y < HEIGHT; y++) {
        p.print("|");
        for (int x = 0; x < WIDTH; x++) {
            p.print(" ");
        }
        p.println("|");
    }
    
    // 绘制底部边框 | Draw bottom border
    p.print("+");
    for (int i = 0; i < WIDTH; i++) p.print("-");
    p.println("+");
    
    // 绘制状态行 | Draw status line
    p.println("位置 | Position: (0, 0)  模式 | Mode: 移动 | Moving");
}

// 更新画布上的特定位置 | Update specific position on canvas
void updateCanvasPosition(const DrawingState& state, int x, int y) {
    // 计算实际屏幕坐标（考虑边框和标题） | Calculate actual screen coordinates (considering borders and title)
    int screenX = x + 2; // +1 for border, +1 for 1-based indexing
    int screenY = y + 5; // +4 for title and header, +1 for 1-based indexing
    
    auto p = tc::printer();
    p.moveCursor(screenX, screenY);
    
    if (x == state.x && y == state.y) {
        // 绘制光标 | Draw cursor
        p.print(TCOLOR_CYAN).print(CURSOR).print(TCOLOR_RESET);
    } else {
        // 绘制画布内容 | Draw canvas content
        if (state.canvas[y][x] == DRAWN) {
            p.print(TCOLOR_YELLOW).print(DRAWN).print(TCOLOR_RESET);
        } else {
            p.print(EMPTY);
        }
    }
}

// 更新状态信息 | Update status information
void updateStatusInfo(const DrawingState& state) {
    auto p = tc::printer();
    
    // 移动到状态行 | Move to status line
    p.moveCursor(1, HEIGHT + 7);
    
    // 清除整行 | Clear entire line
    p.print("\033[2K");
    
    // 显示新状态 | Show new status
    p.print("位置 | Position: (")
     .print(state.x)
     .print(", ")
     .print(state.y)
     .print(")  模式 | Mode: ")
     .print(state.drawing ? "绘制 | Drawing" : "移动 | Moving");
}

int main() {
    DrawingState state;
    bool running = true;
    
    // 初始化绘图界面 | Initialize drawing interface
    initDrawingInterface();
    
    // 绘制初始光标位置 | Draw initial cursor position
    updateCanvasPosition(state, state.x, state.y);
    updateStatusInfo(state);
    
    // 主循环 | Main loop
    while (running) {
        // 检测按键 | Detect key presses
        if (tc::isKeyPressed(KEY_ESC)) {
            running = false;
        }
        
        if (tc::isKeyPressed(KEY_UP) && state.y > 1) {
            state.prevX = state.x;
            state.prevY = state.y;
            state.y--;
            
            // 更新前一个位置和当前位置 | Update previous and current positions
            updateCanvasPosition(state, state.prevX, state.prevY);
            updateCanvasPosition(state, state.x, state.y);
            updateStatusInfo(state);
            
            tc::wait(0.1); // 防止移动过快 | Prevent too fast movement
        }
        
        if (tc::isKeyPressed(KEY_DOWN) && state.y < HEIGHT) {
            state.prevX = state.x;
            state.prevY = state.y;
            state.y++;
            
            // 更新前一个位置和当前位置 | Update previous and current positions
            updateCanvasPosition(state, state.prevX, state.prevY);
            updateCanvasPosition(state, state.x, state.y);
            updateStatusInfo(state);
            
            tc::wait(0.1);
        }
        
        if (tc::isKeyPressed(KEY_LEFT) && state.x > 0) {
            state.prevX = state.x;
            state.prevY = state.y;
            state.x--;
            
            // 更新前一个位置和当前位置 | Update previous and current positions
            updateCanvasPosition(state, state.prevX, state.prevY);
            updateCanvasPosition(state, state.x, state.y);
            updateStatusInfo(state);
            
            tc::wait(0.1);
        }
        
        if (tc::isKeyPressed(KEY_RIGHT) && state.x < WIDTH - 1) {
            state.prevX = state.x;
            state.prevY = state.y;
            state.x++;
            
            // 更新前一个位置和当前位置 | Update previous and current positions
            updateCanvasPosition(state, state.prevX, state.prevY);
            updateCanvasPosition(state, state.x, state.y);
            updateStatusInfo(state);
            
            tc::wait(0.1);
        }
        
        if (tc::isKeyPressed(KEY_SPACE)) {
            // 切换当前位置的绘制状态 | Toggle drawing state at current position
            if (state.canvas[state.y][state.x] == EMPTY) {
                state.canvas[state.y][state.x] = DRAWN;
            } else {
                state.canvas[state.y][state.x] = EMPTY;
            }
            
            // 更新当前位置 | Update current position
            updateCanvasPosition(state, state.x, state.y);
            
            tc::wait(0.2); // 防止一次按键多次触发 | Prevent multiple triggers from one key press
        }
        
        // 切换绘制模式 | Toggle drawing mode
        if (tc::isKeyPressed('d') || tc::isKeyPressed('D')) {
            state.drawing = !state.drawing;
            updateStatusInfo(state);
            tc::wait(0.2);
        }
        
        // 如果处于绘制模式，自动在当前位置绘制 | If in drawing mode, automatically draw at current position
        if (state.drawing && state.canvas[state.y][state.x] == EMPTY) {
            state.canvas[state.y][state.x] = DRAWN;
            updateCanvasPosition(state, state.x, state.y);
        }
        
        tc::wait(0.01); // 减少CPU使用率 | Reduce CPU usage
    }
    
    // 清屏并显示退出信息 | Clear screen and show exit message
    auto p = tc::printer();
    p.clear()
     .showCursor()
     .println("感谢使用简易绘图程序！")
     .println("Thank you for using the Simple Drawing Program!");
    
    return 0;
}
