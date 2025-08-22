#include "../include/tc.hpp"
#include <string>

int main() {
    // 获取系统信息
    int osCode = tc::systemCheck();
    const char* osName = tc::getOSName(osCode);
    std::string osVersionInfo = tc::getOSVersionInfo();

    // 获取当前时间
    int year = tc::getSystemTime(SYS_YEAR);
    int month = tc::getSystemTime(SYS_MONTH);
    int day = tc::getSystemTime(SYS_DAY);
    int hour = tc::getSystemTime(SYS_HOUR);
    int minute = tc::getSystemTime(SYS_MINUTE);
    int second = tc::getSystemTime(SYS_SECOND);
    int timestamp = tc::getSystemTime();
    
    // 获取终端尺寸
    auto termSize = tc::printer().getSize();
    
    // 显示系统信息
    tc::println(TCOLOR_CYAN, TFONT_BOLD, "系统信息", TCOLOR_RESET);
    tc::println(TCOLOR_CYAN, "=========", TCOLOR_RESET);
    
    tc::println(TCOLOR_YELLOW, "操作系统: ", TCOLOR_RESET, osName, " (代码: ", osCode, "版本信息：", osVersionInfo, ")");
    tc::println(TCOLOR_YELLOW, "当前时间: ", TCOLOR_RESET, 
                year, "-", month < 10 ? "0" : "", month, "-", day < 10 ? "0" : "", day, " ",
                hour < 10 ? "0" : "", hour, ":", minute < 10 ? "0" : "", minute, ":", second < 10 ? "0" : "", second);
    tc::println(TCOLOR_YELLOW, "Unix时间戳: ", TCOLOR_RESET, timestamp);
    tc::println(TCOLOR_YELLOW, "终端尺寸: ", TCOLOR_RESET, termSize.first, "x", termSize.second);
    
    // 执行系统命令
    tc::println("\n", TCOLOR_CYAN, TFONT_BOLD, "系统命令输出", TCOLOR_RESET);
    tc::println(TCOLOR_CYAN, "===========", TCOLOR_RESET);
    
#ifdef _WIN32
    tc::systemConsoleW(L"echo 当前目录内容:");
    tc::systemConsole("dir");
#else
    tc::systemConsole("echo 当前目录内容:");
    tc::systemConsole("ls -la");
#endif
    
    return 0;
}