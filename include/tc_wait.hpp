/*
 * tc_wait.hpp - TC库等待和按键处理模块
 * TC Wait and Key Handling Module
 * 
 * 这个文件包含了TC库中所有与等待和按键处理相关的功能，包括：
 * - 时间延迟函数
 * - 跨平台按键等待功能
 * - 特定按键等待支持
 * 
 * This file contains all wait and key handling related functionality in the TC library, including:
 * - Time delay functions
 * - Cross-platform key waiting functionality
 * - Specific key waiting support
 * 
 * 版本 Version: 1.1.2
 * 作者 Author: 537 Studio
 * 许可 License: MIT
 */

#ifndef TC_WAIT_HPP
#define TC_WAIT_HPP

// 标准库包含 | Standard library includes
#include <thread>  // 线程库，用于延时操作 | Thread library for delay operations
#include <chrono>  // 时间相关功能 | Time-related functionality

// 引入系统工具模块，获取按键码定义 | Include system utils module for key code definitions
#include "tc_system_utils.hpp"
#include <vector>
#include <string>

// 平台特定包含 | Platform-specific includes
#ifdef _WIN32
    #include <conio.h>    // Windows控制台输入输出函数 | Windows console I/O functions
#else
    #include <termios.h>  // 终端IO设置 | Terminal I/O settings
    #include <unistd.h>   // POSIX API | POSIX API
#endif

namespace tc {

/**
 * 等待函数 - 暂停程序执行指定的秒数
 * Wait function - Pauses program execution for specified seconds
 * 
 * 这个函数使用C++11的线程库来实现跨平台的精确延时。
 * 支持小数秒数，内部转换为毫秒进行延时。
 * 
 * This function uses C++11 thread library to implement cross-platform precise delay.
 * Supports decimal seconds, internally converted to milliseconds for delay.
 * 
 * @param seconds 等待的秒数，支持小数 | Number of seconds to wait, supports decimals
 */
inline void wait(double seconds) { 
    // 将秒转换为毫秒并暂停线程 | Convert seconds to milliseconds and pause thread
    std::this_thread::sleep_for(std::chrono::milliseconds((int)(seconds*1000))); 
}

#ifdef _WIN32 // Windows平台实现 | Windows platform implementation

/**
 * waitKey函数 - 等待任意按键按下（Windows版本）
 * waitKey function - Waits for any key press (Windows version)
 * 
 * 使用Windows特有的_getch()函数，不需要按回车键即可获取按键输入。
 * Uses Windows-specific _getch() function, no need to press Enter to get key input.
 */
inline void waitKey() { 
    _getch(); // 使用_getch()获取按键，不回显 | Use _getch() to get key without echo
}

/**
 * waitKey函数 - 等待指定字符按键按下（Windows版本）
 * waitKey function - Waits for specific character key press (Windows version)
 * 
 * @param key 等待的字符按键 | Character key to wait for
 */
inline void waitKey(char key) { 
    while (_getch() != key) {} // 循环直到按下指定键 | Loop until specified key is pressed
}

/**
 * waitKey函数 - 等待指定键码按键按下（Windows版本）
 * waitKey function - Waits for specific key code press (Windows version)
 * 
 * @param key 等待的键码 | Key code to wait for
 */
inline void waitKey(int key) { 
    while (_getch() != key) {} // 循环直到按下指定键码 | Loop until specified key code is pressed
}

#else // 非Windows平台实现 | Non-Windows platform implementation

/**
 * waitKey函数 - 等待任意按键按下（Unix/Linux/macOS版本）
 * waitKey function - Waits for any key press (Unix/Linux/macOS version)
 * 
 * 使用termios来设置终端为非规范模式，允许立即读取按键输入。
 * Uses termios to set terminal to non-canonical mode for immediate key reading.
 */
inline void waitKey() {
    termios oldt, newt; // 终端设置结构体 | Terminal settings structures
    tcgetattr(0, &oldt); // 获取当前终端设置 | Get current terminal settings
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO); // 禁用规范模式和回显，允许立即读取按键且不回显 | Disable canonical mode and echo
    tcsetattr(0, TCSANOW, &newt); // 应用新设置 | Apply new settings
    getchar(); // 读取一个字符 | Read one character
    tcsetattr(0, TCSANOW, &oldt); // 恢复原始设置 | Restore original settings
}

/**
 * waitKey函数 - 等待指定字符按键按下（Unix/Linux/macOS版本）
 * waitKey function - Waits for specific character key press (Unix/Linux/macOS version)
 * 
 * @param key 等待的字符按键 | Character key to wait for
 */
inline void waitKey(char key) {
    termios oldt, newt; // 终端设置结构体 | Terminal settings structures
    tcgetattr(0, &oldt); // 获取当前终端设置 | Get current terminal settings
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO); // 禁用规范模式和回显，允许立即读取按键且不回显 | Disable canonical mode and echo
    tcsetattr(0, TCSANOW, &newt); // 应用新设置 | Apply new settings
    int ch;
    do { ch = getchar(); } while (ch != key); // 循环直到按下指定键 | Loop until specified key is pressed
    tcsetattr(0, TCSANOW, &oldt); // 恢复原始设置 | Restore original settings
}

/**
 * waitKey函数 - 等待指定键码按键按下（Unix/Linux/macOS版本）
 * waitKey function - Waits for specific key code press (Unix/Linux/macOS version)
 * 
 * @param key 等待的键码 | Key code to wait for
 */
inline void waitKey(int key) { 
    termios oldt, newt;
    tcgetattr(0, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(0, TCSANOW, &newt);
    std::vector<int> seq;
    while (true) {
        int ch = getchar();
        if (ch == 27) {
            if (key == 27) break; // 直接检测 ESC 键
            // ESC 序列
            seq.clear();
            seq.push_back(ch);
            ch = getchar();
            if (ch == '[') {
                seq.push_back(ch);
                ch = getchar();
                seq.push_back(ch);
                // 收集完整的ESC序列
                std::string fullSeq;
                fullSeq = "\x1b[";  // ESC [
                fullSeq += (char)seq[2];  // 第三个字符

                // 继续读取直到遇到结束符号（如 '~'）或字母
                while (true) {
                    ch = getchar();
                    fullSeq += (char)ch;
                    if (ch == '~' || (ch >= 'A' && ch <= 'Z')) {
                        break;
                    }
                }

                // 方向键 (ESC [ A/B/C/D)
                if (fullSeq == "\x1b[A" && key == 'A') break;  // 上
                if (fullSeq == "\x1b[B" && key == 'B') break;  // 下
                if (fullSeq == "\x1b[C" && key == 'C') break;  // 右
                if (fullSeq == "\x1b[D" && key == 'D') break;  // 左

                // Home/End (ESC [ H/F)
                if (fullSeq == "\x1b[H" && key == KEY_HOME) break;
                if (fullSeq == "\x1b[F" && key == KEY_END) break;

                // 功能键 F5-F8 (ESC [ 1 5/6/7/8 ~)
                if (fullSeq == "\x1b[15~" && key == 15) break;  // F5
                if (fullSeq == "\x1b[17~" && key == 17) break;  // F6
                if (fullSeq == "\x1b[18~" && key == 18) break;  // F7
                if (fullSeq == "\x1b[19~" && key == 19) break;  // F8

                // 功能键 F9-F12 (ESC [ 2 0/1/3/4 ~)
                if (fullSeq == "\x1b[20~" && key == 20) break;  // F9
                if (fullSeq == "\x1b[21~" && key == 21) break;  // F10
                if (fullSeq == "\x1b[23~" && key == 23) break;  // F11
                if (fullSeq == "\x1b[24~" && key == 24) break;  // F12

                // Insert/Delete/PageUp/PageDown
                if (fullSeq == "\x1b[2~" && key == KEY_INSERT) break;
                if (fullSeq == "\x1b[3~" && key == KEY_DELETE) break;
                if (fullSeq == "\x1b[5~" && key == KEY_PAGEUP) break;
                if (fullSeq == "\x1b[6~" && key == KEY_PAGEDOWN) break;

                // Home/End 另一种序列
                if (fullSeq == "\x1b[1~" && key == KEY_HOME) break;
                if (fullSeq == "\x1b[4~" && key == KEY_END) break;
            } else if (ch == 'O') {  // ESC O P-S 序列（F1-F4）或 ESC O H/F（Home/End）
                ch = getchar();
                if ((ch >= 'P' && ch <= 'S') && ch == key) break;  // F1-F4
                if (key == KEY_HOME && ch == 'H') break;  // Home
                if (key == KEY_END && ch == 'F') break;   // End
            }
        } else if (ch == key) {
            break;
        }
    }
    tcsetattr(0, TCSANOW, &oldt);
}


#endif

} // namespace tc

#endif // TC_WAIT_HPP