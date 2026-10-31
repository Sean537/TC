#define TC_ENABLE_WIN32_CONSOLE_API  // 强制启用 Win32 Console API 宏（用于跨平台行为测试）
#include "../include/tc.hpp"
#include <string>
#include <sstream>
#include <iomanip>

enum class LogLevel {
    DEBUG,
    INFO,
    WARNING,
    ERR,  // 改名以避免与Windows宏冲突
    CRITICAL
};

class Logger {
private:
    LogLevel minLevel_;
    
    std::string getCurrentTime() {
        std::stringstream ss;
        int hour = tc::getSystemTime(SYS_HOUR);
        int minute = tc::getSystemTime(SYS_MINUTE);
        int second = tc::getSystemTime(SYS_SECOND);
        
        ss << std::setfill('0') << std::setw(2) << hour << ":"
           << std::setfill('0') << std::setw(2) << minute << ":"
           << std::setfill('0') << std::setw(2) << second;
        
        return ss.str();
    }
    
public:
    Logger(LogLevel minLevel = LogLevel::DEBUG) : minLevel_(minLevel) {}
    
    void setLevel(LogLevel level) {
        minLevel_ = level;
    }
    
    template<typename... Args>
    void debug(Args&&... args) {
        if (minLevel_ <= LogLevel::DEBUG) {
            tc::print(TCOLOR_CYAN, "[DEBUG]   ", TCOLOR_RESET);
            tc::print("[", getCurrentTime(), "] ");
            tc::println(std::forward<Args>(args)...);
        }
    }
    
    template<typename... Args>
    void info(Args&&... args) {
        if (minLevel_ <= LogLevel::INFO) {
            tc::print(TCOLOR_GREEN, "[INFO]    ", TCOLOR_RESET);
            tc::print("[", getCurrentTime(), "] ");
            tc::println(std::forward<Args>(args)...);
        }
    }
    
    template<typename... Args>
    void warning(Args&&... args) {
        if (minLevel_ <= LogLevel::WARNING) {
            tc::print(TCOLOR_YELLOW, "[WARNING] ", TCOLOR_RESET);
            tc::print("[", getCurrentTime(), "] ");
            tc::println(std::forward<Args>(args)...);
        }
    }
    
    template<typename... Args>
    void error(Args&&... args) {
        if (minLevel_ <= LogLevel::ERR) {
            tc::print(TCOLOR_RED, "[ERROR]   ", TCOLOR_RESET);
            tc::print("[", getCurrentTime(), "] ");
            tc::println(std::forward<Args>(args)...);
        }
    }
    
    template<typename... Args>
    void critical(Args&&... args) {
        if (minLevel_ <= LogLevel::CRITICAL) {
            tc::print(TCOLOR_RED, TFONT_BOLD, "[CRITICAL]", TCOLOR_RESET, " ");
            tc::print("[", getCurrentTime(), "] ");
            tc::println(std::forward<Args>(args)...);
        }
    }
};

int main() {
    Logger logger;
    
    logger.debug("这是一条调试信息");
    logger.info("系统初始化完成");
    logger.warning("磁盘空间不足");
    logger.error("无法连接到数据库");
    logger.critical("系统崩溃，无法恢复");
    
    tc::println("\n设置日志级别为 WARNING:");
    logger.setLevel(LogLevel::WARNING);
    
    logger.debug("这条调试信息不会显示");
    logger.info("这条信息不会显示");
    logger.warning("这条警告会显示");
    logger.error("这条错误会显示");
    logger.critical("这条严重错误会显示");
    
    return 0;
}