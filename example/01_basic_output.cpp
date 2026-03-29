#define TC_ENABLE_WIN32_CONSOLE_API  // 强制启用 Win32 Console API 宏（用于跨平台行为测试）
#include "../include/tc.hpp"

int main() {
    // 标准输出
    tc::print("Hello", " ", "World");  // 输出: Hello World
    tc::println("Hello", " ", "World"); // 输出: Hello World 并换行
    
    // 打印不同类型的值
    tc::println("整数: ", 42);
    tc::println("浮点数: ", 3.14159);
    tc::println("布尔值: ", true);
    
    // 链式输出
    tc::print().print("链式").print(" ").println("输出");
    
    // 流式输出
    tc::tout << "流式输出" << std::endl;
    tc::tout << "支持多种类型: " << 42 << ", " << 3.14 << std::endl;
    
    return 0;
}