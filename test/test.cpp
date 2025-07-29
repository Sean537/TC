#include "../tc.hpp"

int main(){
    // 基本颜色输出
    tc::tout << tc::TCOLOR_GREEN << "Hello world!" << tc::TCOLOR_RESET << std::endl;
    
    // 粗体文本
    tc::tout << tc::TFONT_THICK << 12345 << tc::TFONT_RESET << std::endl;
    
    // RGB 颜色
    tc::tout << TCOLOR_RGB(255, 255, 255) << "White Text" << tc::TCOLOR_RESET << std::endl;
    
    // 延时输出
    tc::tout << "Wait for 3 seconds…" << tc::tsleep(3000) << "Okay I'm here" << std::endl;
    
    // 延时流语法
    tc::tout << "1, ";
    tc::tsleep_stream << 1000;  // 等待 1 秒
    tc::tout << "2";
    
    return 0;
}