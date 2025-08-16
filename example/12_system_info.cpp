#include "../tc.hpp"
#include <string>

std::string getOSName(int osCode) {
    switch (osCode) {
        case OS_WINDOWSNT11: return "Windows 11";
        case OS_WINDOWSNT10: return "Windows 10";
        case OS_WINDOWSNT6: return "Windows Vista/7/8/8.1";
        case OS_WINDOWSNT5: return "Windows XP/2003";
        case OS_WINDOWSNT4: return "Windows NT 4.0";
        case OS_WINDOWSNT3: return "Windows NT 3.x";
        case OS_WIN95: return "Windows 95";
        case OS_WIN98: return "Windows 98";
        case OS_WINME: return "Windows ME";
        case OS_WINCE: return "Windows CE";
        case OS_WINDOWS: return "Windows (其他版本)";
        case OS_LINUX: return "Linux";
        case OS_ANDROID: return "Android";
        case OS_MACOS: return "macOS";
        case OS_IOS: return "iOS";
        case OS_BSD: return "BSD";
        case OS_UNIX: return "Unix";
        case OS_DOS: return "DOS";
        case OS_BEOS: return "BeOS";
        case OS_HAIKU: return "Haiku";
        case OS_AIX: return "AIX";
        case OS_SOLARIS: return "Solaris";
        case OS_MINIX: return "Minix";
        case OS_QNX: return "QNX";
        case OS_OS2: return "OS/2";
        default: return "未知系统";
    }
}

int main() {
    // 获取系统信息
    int osCode = tc::systemCheck();
    std::string osName = getOSName(osCode);
    
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
    
    tc::println(TCOLOR_YELLOW, "操作系统: ", TCOLOR_RESET, osName, " (代码: ", osCode, ")");
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
    tc::systemConsoleW("echo 当前目录内容:");
    tc::systemConsole("ls -la");
#endif
    
    return 0;
}