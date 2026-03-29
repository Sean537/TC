#define TC_ENABLE_WIN32_CONSOLE_API  // 强制启用 Win32 Console API 宏（用于跨平台行为测试）
#include "../include/tc.hpp"

int main() {
    // 基本延时
    tc::println("等待1秒...");
    tc::wait(1.0);
    tc::println("等待完成");
    
    // 毫秒延时
    tc::println("等待500毫秒...");
    tc::tsleep(500).execute();
    tc::println("等待完成");
    
    // 流式延时
    tc::tout << "开始" << tc::tsleep(300) << "中间" << tc::tsleep(300) << "结束" << std::endl;
    
    // 延时流
    tc::println("延时流开始");
    tc::tsleep_stream << 800;
    tc::println("延时流结束");
    
    return 0;
}