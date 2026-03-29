#define TC_ENABLE_WIN32_CONSOLE_API  // 强制启用 Win32 Console API 宏（用于跨平台行为测试）
#include "../include/tc.hpp"
#include <string>
#include <vector>
#include <map>
#include <functional>

class CLI {
private:
    std::string prompt_;
    std::map<std::string, std::pair<std::function<void(const std::vector<std::string>&)>, std::string>> commands_;
    bool running_ = true;
    
    std::vector<std::string> splitCommand(const std::string& input) {
        std::vector<std::string> parts;
        std::string part;
        bool inQuotes = false;
        
        for (char c : input) {
            if (c == '"') {
                inQuotes = !inQuotes;
            } else if (c == ' ' && !inQuotes) {
                if (!part.empty()) {
                    parts.push_back(part);
                    part.clear();
                }
            } else {
                part += c;
            }
        }
        
        if (!part.empty()) {
            parts.push_back(part);
        }
        
        return parts;
    }
    
public:
    CLI(const std::string& prompt = "> ") : prompt_(prompt) {
        // 添加内置命令
        addCommand("help", [this](const std::vector<std::string>& args) {
            tc::println(TCOLOR_CYAN, TFONT_BOLD, "可用命令:", TCOLOR_RESET);
            for (const auto& cmd : commands_) {
                tc::println(TCOLOR_YELLOW, cmd.first, TCOLOR_RESET, " - ", cmd.second.second);
            }
        }, "显示帮助信息");
        
        addCommand("exit", [this](const std::vector<std::string>& args) {
            tc::println(TCOLOR_GREEN, "再见!", TCOLOR_RESET);
            running_ = false;
        }, "退出程序");
        
        addCommand("clear", [](const std::vector<std::string>& args) {
            tc::printer().clear();
        }, "清屏");
    }
    
    void addCommand(const std::string& name, 
                   std::function<void(const std::vector<std::string>&)> handler,
                   const std::string& description) {
        commands_[name] = {handler, description};
    }
    
    void run() {
        tc::println(TCOLOR_GREEN, TFONT_BOLD, "交互式命令行界面", TCOLOR_RESET);
        tc::println("输入 'help' 获取帮助，输入 'exit' 退出");
        
        while (running_) {
            tc::print(TCOLOR_CYAN, prompt_, TCOLOR_RESET);
            
            std::string input;
            std::getline(std::cin, input);
            
            if (input.empty()) continue;
            
            std::vector<std::string> parts = splitCommand(input);
            std::string cmd = parts[0];
            
            if (commands_.find(cmd) != commands_.end()) {
                // 提取参数
                std::vector<std::string> args(parts.begin() + 1, parts.end());
                
                try {
                    commands_[cmd].first(args);
                } catch (const std::exception& e) {
                    tc::println(TCOLOR_RED, "错误: ", e.what(), TCOLOR_RESET);
                }
            } else {
                tc::println(TCOLOR_RED, "未知命令: ", cmd, TCOLOR_RESET);
                tc::println("输入 'help' 获取可用命令列表");
            }
        }
    }
};

int main() {
    CLI cli("TC> ");
    
    // 添加自定义命令
    cli.addCommand("echo", [](const std::vector<std::string>& args) {
        for (const auto& arg : args) {
            tc::print(arg, " ");
        }
        tc::println();
    }, "回显参数");
    
    cli.addCommand("color", [](const std::vector<std::string>& args) {
        if (args.empty()) {
            tc::println(TCOLOR_RED, "用法: color <颜色名> <文本>", TCOLOR_RESET);
            return;
        }
        
        std::string color = args[0];
        std::string text = args.size() > 1 ? args[1] : "彩色文本测试";
        
        if (color == "red") {
            tc::println(TCOLOR_RED, text, TCOLOR_RESET);
        } else if (color == "green") {
            tc::println(TCOLOR_GREEN, text, TCOLOR_RESET);
        } else if (color == "blue") {
            tc::println(TCOLOR_BLUE, text, TCOLOR_RESET);
        } else if (color == "yellow") {
            tc::println(TCOLOR_YELLOW, text, TCOLOR_RESET);
        } else if (color == "cyan") {
            tc::println(TCOLOR_CYAN, text, TCOLOR_RESET);
        } else if (color == "magenta") {
            tc::println(TCOLOR_MAGENTA, text, TCOLOR_RESET);
        } else {
            tc::println(TCOLOR_RED, "未知颜色: ", color, TCOLOR_RESET);
        }
    }, "使用指定颜色显示文本");
    
    cli.addCommand("time", [](const std::vector<std::string>& args) {
        tc::println("当前时间: ", 
            tc::getSystemTime(SYS_YEAR), "-", 
            tc::getSystemTime(SYS_MONTH), "-", 
            tc::getSystemTime(SYS_DAY), " ", 
            tc::getSystemTime(SYS_HOUR), ":", 
            tc::getSystemTime(SYS_MINUTE), ":", 
            tc::getSystemTime(SYS_SECOND));
    }, "显示当前时间");
    
    cli.run();
    
    return 0;
}