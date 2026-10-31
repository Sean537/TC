#define TC_ENABLE_WIN32_CONSOLE_API  // 强制启用 Win32 Console API 宏（用于跨平台行为测试）
#include "../include/tc.hpp"
#include <iostream>
#include <string>

int main() {
    std::cout << "按键等待测试\n";
    std::cout << "=============\n\n";

    std::cout << "按任意键继续...\n";
    tc::waitKey();
    std::cout << "继续执行\n\n";
    
    std::cout << "按 'A' 键继续...\n";
    tc::waitKey('A');
    std::cout << "检测到 'A' 键\n\n";
    
    // 基本控制键测试
    std::cout << "按 ESC 键继续...\n";
    tc::waitKey(KEY_ESC);
    std::cout << "检测到 ESC 键\n\n";
    
    std::cout << "按空格键继续...\n";
    tc::waitKey(KEY_SPACE);
    std::cout << "检测到空格键\n\n";
    
    std::cout << "按回车键继续...\n";
    tc::waitKey(KEY_ENTER);
    std::cout << "检测到回车键\n\n";
    
    std::cout << "按Tab键继续...\n";
    tc::waitKey(KEY_TAB);
    std::cout << "检测到Tab键\n\n";
    
    std::cout << "按Backspace键继续...\n";
    tc::waitKey(KEY_BACKSPACE);
    std::cout << "检测到Backspace键\n\n";
    
    // 编辑键测试
    std::cout << "按Insert键继续...\n";
    tc::waitKey(KEY_INSERT);
    std::cout << "检测到Insert键\n\n";
    
    std::cout << "按Delete键继续...\n";
    tc::waitKey(KEY_DELETE);
    std::cout << "检测到Delete键\n\n";
    
    std::cout << "按Home键继续...\n";
    tc::waitKey(KEY_HOME);
    std::cout << "检测到Home键\n\n";
    
    std::cout << "按End键继续...\n";
    tc::waitKey(KEY_END);
    std::cout << "检测到End键\n\n";
    
    std::cout << "按Page Up键继续...\n";
    tc::waitKey(KEY_PAGEUP);
    std::cout << "检测到Page Up键\n\n";
    
    std::cout << "按Page Down键继续...\n";
    tc::waitKey(KEY_PAGEDOWN);
    std::cout << "检测到Page Down键\n\n";
    
    // 方向键测试
    std::cout << "按方向键测试:\n";
    std::cout << "按上方向键...\n";
    tc::waitKey(KEY_UP);
    std::cout << "检测到上方向键\n\n";
    
    std::cout << "按下方向键...\n";
    tc::waitKey(KEY_DOWN);
    std::cout << "检测到下方向键\n\n";
    
    std::cout << "按左方向键...\n";
    tc::waitKey(KEY_LEFT);
    std::cout << "检测到左方向键\n\n";
    
    std::cout << "按右方向键...\n";
    tc::waitKey(KEY_RIGHT);
    std::cout << "检测到右方向键\n\n";
    
    // 功能键测试
    
    // 可能会触发开发环境的帮助窗口
    /*
    std::cout << "按F1键继续...\n";
    tc::waitKey(KEY_F1);
    std::cout << "检测到F1键\n\n";
    */

    std::cout << "按F2键继续...\n";
    tc::waitKey(KEY_F2);
    std::cout << "检测到F2键\n\n";
    
    // 可能会触发控制台搜索功能
    /*
    std::cout << "按F3键继续...\n";
    tc::waitKey(KEY_F3);
    std::cout << "检测到F3键\n\n";
    */

    std::cout << "按F4键继续...\n";
    tc::waitKey(KEY_F4);
    std::cout << "检测到F4键\n\n";
    
    // 可能会触发VS Code的调试窗口
    /*
    std::cout << "按F5键继续...\n";
    tc::waitKey(KEY_F5);
    std::cout << "检测到F5键\n\n";
    */
    
    std::cout << "按F6键继续...\n";
    tc::waitKey(KEY_F6);
    std::cout << "检测到F6键\n\n";
    
    std::cout << "按F7键继续...\n";
    tc::waitKey(KEY_F7);
    std::cout << "检测到F7键\n\n";
    
    std::cout << "按F8键继续...\n";
    tc::waitKey(KEY_F8);
    std::cout << "检测到F8键\n\n";
    
    std::cout << "按F9键继续...\n";
    tc::waitKey(KEY_F9);
    std::cout << "检测到F9键\n\n";
    
    // 可能会触发窗口焦点
    /*
    std::cout << "按F10键继续...\n";
    tc::waitKey(KEY_F10);
    std::cout << "检测到F10键\n\n";
    */

    // 可能会触发控制台窗口全屏
    /*
    std::cout << "按F11键继续...\n";
    tc::waitKey(KEY_F11);
    std::cout << "检测到F11键\n\n";
    */

    std::cout << "按F12键继续...\n";
    tc::waitKey(KEY_F12);
    std::cout << "检测到F12键\n\n";
    
    std::cout << "所有按键测试完成！按任意键退出...\n";
    tc::waitKey();
    
    return 0;
}