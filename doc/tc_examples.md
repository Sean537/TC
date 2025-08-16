# TC.hpp 使用示例

本文档提供了一系列 TC.hpp 库的使用示例，从基础到高级，帮助您快速掌握库的各种功能。

## 目录

- [基础示例](#基础示例)
  - [基本输出](#基本输出)
  - [颜色输出](#颜色输出)
  - [字体样式](#字体样式)
  - [延时操作](#延时操作)
- [中级示例](#中级示例)
  - [进度条](#进度条)
  - [光标控制](#光标控制)
  - [终端尺寸](#终端尺寸)
  - [按键等待](#按键等待)
- [高级示例](#高级示例)
  - [打字机效果](#打字机效果)
  - [彩色菜单](#彩色菜单)
  - [动画效果](#动画效果)
  - [系统信息](#系统信息)
- [实用案例](#实用案例)
  - [文件加载进度](#文件加载进度)
  - [彩色日志系统](#彩色日志系统)
  - [交互式命令行界面](#交互式命令行界面)
  - [游戏示例](#游戏示例)

## 基础示例

### 基本输出

```cpp
#include "tc.hpp"

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
```

### 颜色输出

```cpp
#include "tc.hpp"

int main() {
    // 基本颜色
    tc::println(TCOLOR_RED, "红色文本", TCOLOR_RESET);
    tc::println(TCOLOR_GREEN, "绿色文本", TCOLOR_RESET);
    tc::println(TCOLOR_BLUE, "蓝色文本", TCOLOR_RESET);
    tc::println(TCOLOR_YELLOW, "黄色文本", TCOLOR_RESET);
    tc::println(TCOLOR_MAGENTA, "洋红文本", TCOLOR_RESET);
    tc::println(TCOLOR_CYAN, "青色文本", TCOLOR_RESET);
    tc::println(TCOLOR_WHITE, "白色文本", TCOLOR_RESET);
    
    // 背景色
    tc::println(TCOLOR_BLACK, BCOLOR_RED, "黑字红底", TCOLOR_RESET);
    tc::println(TCOLOR_WHITE, BCOLOR_BLUE, "白字蓝底", TCOLOR_RESET);
    tc::println(TCOLOR_BLACK, BCOLOR_GREEN, "黑字绿底", TCOLOR_RESET);
    tc::println(TCOLOR_BLACK, BCOLOR_YELLOW, "黑字黄底", TCOLOR_RESET);
    
    // RGB颜色
    tc::println(TCOLOR_RGB(255, 128, 0), "橙色文本", TCOLOR_RESET);
    tc::println(TCOLOR_RGB(128, 0, 128), "紫色文本", TCOLOR_RESET);
    tc::println(TCOLOR_RGB(0, 128, 128), "青绿色文本", TCOLOR_RESET);
    
    // 流式颜色输出
    tc::tout << TCOLOR_RED << "红色" << TCOLOR_GREEN << "绿色" 
             << TCOLOR_BLUE << "蓝色" << TCOLOR_RESET << std::endl;
    
    return 0;
}
```

### 字体样式

```cpp
#include "tc.hpp"

int main() {
    // 基本样式
    tc::println(TFONT_BOLD, "粗体文本", TFONT_RESET);
    tc::println(TFONT_UNDERLINE, "下划线文本", TFONT_RESET);
    tc::println(TFONT_ITALIC, "斜体文本", TFONT_RESET);
    tc::println(TFONT_CROSSED, "删除线文本", TFONT_RESET);
    tc::println(TFONT_REVERSE, "反色文本", TFONT_RESET);
    
    // 组合样式
    tc::println(TFONT_BOLD, TFONT_UNDERLINE, "粗体下划线文本", TFONT_RESET);
    tc::println(TFONT_ITALIC, TFONT_CROSSED, "斜体删除线文本", TFONT_RESET);
    
    // 样式与颜色组合
    tc::println(TCOLOR_RED, TFONT_BOLD, "红色粗体文本", TCOLOR_RESET);
    tc::println(TCOLOR_BLUE, TFONT_UNDERLINE, "蓝色下划线文本", TCOLOR_RESET);
    tc::println(TCOLOR_GREEN, BCOLOR_YELLOW, TFONT_BOLD, "绿字黄底粗体", TCOLOR_RESET);
    
    return 0;
}
```

### 延时操作

```cpp
#include "tc.hpp"

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
```

## 中级示例

### 进度条

```cpp
#include "tc.hpp"

int main() {
    // 基本进度条
    tc::ProgressBar bar1(30, "#", "-", TCOLOR_GREEN);
    for (int i = 0; i <= 100; ++i) {
        bar1.show(i / 100.0, "处理中...");
        tc::wait(0.02);
    }
    bar1.finish("完成！");
    
    // 自定义进度条
    tc::println("\n自定义进度条:");
    tc::ProgressBar bar2(40, "█", "░", TCOLOR_CYAN);
    for (int i = 0; i <= 100; ++i) {
        bar2.show(i / 100.0, "加载中...");
        tc::wait(0.01);
    }
    bar2.finish("加载完成！");
    
    // 模拟文件下载进度条
    tc::println("\n模拟下载:");
    tc::ProgressBar bar3(50, "▓", "▒", TCOLOR_BLUE);
    for (int i = 0; i <= 100; ++i) {
        bar3.show(i / 100.0, "下载中... " + std::to_string(i) + "%");
        tc::wait(0.03);
    }
    bar3.finish("下载完成！");
    
    return 0;
}
```

### 光标控制

```cpp
#include "tc.hpp"

int main() {
    // 清屏
    tc::printer().clear();
    
    // 移动光标
    tc::printer().moveCursor(10, 5);
    tc::println("在位置(10,5)打印");
    
    tc::printer().moveCursor(15, 10);
    tc::println("在位置(15,10)打印");
    
    // 相对移动
    tc::printer().moveCursor(tc::Printer::Direction::Up, 2);
    tc::println("上移2行");
    
    tc::printer().moveCursor(tc::Printer::Direction::Right, 5);
    tc::println("右移5列");
    
    // 隐藏/显示光标
    tc::println("\n\n光标将在3秒内隐藏...");
    tc::printer().hideCursor();
    tc::wait(3.0);
    tc::printer().showCursor();
    tc::println("光标已显示");
    
    return 0;
}
```

### 终端尺寸

```cpp
#include "tc.hpp"

int main() {
    // 获取终端尺寸
    auto size = tc::printer().getSize();
    tc::println("终端大小: ", size.first, "x", size.second);
    
    // 在终端中央打印文本
    int centerX = size.first / 2;
    int centerY = size.second / 2;
    
    tc::printer().moveCursor(centerX - 10, centerY);
    tc::println(TCOLOR_GREEN, "这是终端的中央位置", TCOLOR_RESET);
    
    // 在四个角落打印
    tc::printer().moveCursor(1, 1);
    tc::println(TCOLOR_RED, "左上角", TCOLOR_RESET);
    
    tc::printer().moveCursor(size.first - 6, 1);
    tc::println(TCOLOR_BLUE, "右上角", TCOLOR_RESET);
    
    tc::printer().moveCursor(1, size.second - 1);
    tc::println(TCOLOR_YELLOW, "左下角", TCOLOR_RESET);
    
    tc::printer().moveCursor(size.first - 6, size.second - 1);
    tc::println(TCOLOR_MAGENTA, "右下角", TCOLOR_RESET);
    
    // 在中间位置等待按键
    tc::printer().moveCursor(centerX - 10, centerY + 2);
    tc::println("按任意键继续...");
    tc::waitKey();
    
    return 0;
}
```

### 按键等待

```cpp
#include "tc.hpp"

int main() {
    tc::println("按任意键继续...");
    tc::waitKey();
    tc::println("继续执行");
    
    tc::println("\n按 'A' 键继续...");
    tc::waitKey('A');
    tc::println("检测到 'A' 键");
    
    tc::println("\n按 ESC 键退出...");
    tc::waitKey(KEY_ESC);
    tc::println("检测到 ESC 键");
    
    tc::println("\n按方向键测试:");
    tc::println("按上方向键...");
    tc::waitKey(KEY_UP);
    tc::println("检测到上方向键");
    
    tc::println("按下方向键...");
    tc::waitKey(KEY_DOWN);
    tc::println("检测到下方向键");
    
    tc::println("按左方向键...");
    tc::waitKey(KEY_LEFT);
    tc::println("检测到左方向键");
    
    tc::println("按右方向键...");
    tc::waitKey(KEY_RIGHT);
    tc::println("检测到右方向键");
    
    return 0;
}
```

## 高级示例

### 打字机效果

```cpp
#include "tc.hpp"
#include <string>

void typewriter(const std::string& text, int delay_ms = 50) {
    for (char c : text) {
        tc::print(c);
        tc::tsleep(delay_ms).execute();
    }
    tc::println();
}

int main() {
    // 基本打字机效果
    typewriter("这是一个打字机效果的演示...");
    
    // 彩色打字机效果
    tc::print(TCOLOR_GREEN);
    typewriter("这是绿色的打字机效果...", 70);
    tc::print(TCOLOR_RESET);
    
    // 带样式的打字机效果
    tc::print(TCOLOR_YELLOW, TFONT_BOLD);
    typewriter("这是黄色粗体的打字机效果...", 30);
    tc::print(TCOLOR_RESET);
    
    // 变速打字机效果
    tc::print(TCOLOR_CYAN);
    std::string text = "这是变速的打字机效果...";
    for (char c : text) {
        tc::print(c);
        int delay = (c == ' ' || c == '.') ? 200 : 40;
        tc::tsleep(delay).execute();
    }
    tc::println(TCOLOR_RESET);
    
    return 0;
}
```

### 彩色菜单

```cpp
#include "tc.hpp"
#include <vector>
#include <string>

int showMenu(const std::vector<std::string>& options, const std::string& title = "菜单") {
    tc::printer().clear();
    
    // 显示标题
    tc::println(TCOLOR_CYAN, TFONT_BOLD, title, TCOLOR_RESET);
    tc::println(TCOLOR_CYAN, std::string(title.length(), '='), TCOLOR_RESET);
    tc::println();
    
    // 显示选项
    for (size_t i = 0; i < options.size(); ++i) {
        tc::println(TCOLOR_YELLOW, "[", i + 1, "] ", TCOLOR_RESET, options[i]);
    }
    
    tc::println();
    tc::println(TCOLOR_YELLOW, "[0] ", TCOLOR_RESET, "退出");
    tc::println();
    
    // 获取用户输入
    int choice = -1;
    while (choice < 0 || choice > static_cast<int>(options.size())) {
        tc::print(TCOLOR_GREEN, "请选择 (0-", options.size(), "): ", TCOLOR_RESET);
        std::cin >> choice;
        
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            choice = -1;
        }
    }
    
    return choice;
}

int main() {
    std::vector<std::string> mainOptions = {
        "选项一",
        "选项二",
        "选项三",
        "选项四"
    };
    
    int choice;
    do {
        choice = showMenu(mainOptions, "彩色菜单示例");
        
        tc::printer().clear();
        switch (choice) {
            case 1:
                tc::println(TCOLOR_GREEN, "您选择了选项一", TCOLOR_RESET);
                break;
            case 2:
                tc::println(TCOLOR_BLUE, "您选择了选项二", TCOLOR_RESET);
                break;
            case 3:
                tc::println(TCOLOR_MAGENTA, "您选择了选项三", TCOLOR_RESET);
                break;
            case 4:
                tc::println(TCOLOR_YELLOW, "您选择了选项四", TCOLOR_RESET);
                break;
            case 0:
                tc::println(TCOLOR_RED, "退出程序", TCOLOR_RESET);
                break;
        }
        
        if (choice != 0) {
            tc::println("\n按任意键返回菜单...");
            tc::waitKey();
        }
    } while (choice != 0);
    
    return 0;
}
```

### 动画效果

```cpp
#include "tc.hpp"
#include <vector>
#include <string>

void showSpinner(int seconds) {
    std::vector<std::string> frames = {"|", "/", "-", "\\"};
    int totalFrames = seconds * 10;
    
    tc::printer().hideCursor();
    
    for (int i = 0; i < totalFrames; ++i) {
        tc::print("\r", TCOLOR_CYAN, "加载中 ", frames[i % frames.size()], TCOLOR_RESET);
        tc::tsleep(100).execute();
    }
    
    tc::println("\r", TCOLOR_GREEN, "加载完成!    ", TCOLOR_RESET);
    tc::printer().showCursor();
}

void showBounce(int seconds) {
    std::string ball = "o";
    std::string empty = " ";
    int width = 20;
    int totalFrames = seconds * 20;
    int pos = 0;
    int dir = 1;
    
    tc::printer().hideCursor();
    
    for (int i = 0; i < totalFrames; ++i) {
        tc::print("\r[");
        for (int j = 0; j < width; ++j) {
            if (j == pos) {
                tc::print(TCOLOR_RED, ball, TCOLOR_RESET);
            } else {
                tc::print(empty);
            }
        }
        tc::print("]");
        
        pos += dir;
        if (pos == width - 1 || pos == 0) {
            dir = -dir;
        }
        
        tc::tsleep(50).execute();
    }
    
    tc::println("\n", TCOLOR_GREEN, "动画结束!", TCOLOR_RESET);
    tc::printer().showCursor();
}

int main() {
    tc::println("旋转加载动画:");
    showSpinner(3);
    
    tc::println("\n弹跳球动画:");
    showBounce(5);
    
    return 0;
}
```

### 系统信息

```cpp
#include "tc.hpp"
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
    tc::systemConsole("echo 当前目录内容:");
    tc::systemConsole("dir");
#else
    tc::systemConsole("echo 当前目录内容:");
    tc::systemConsole("ls -la");
#endif
    
    return 0;
}
```

## 实用案例

### 文件加载进度

```cpp
#include "tc.hpp"
#include <fstream>
#include <vector>
#include <string>
#include <thread>

void simulateFileLoading(const std::string& filename, int fileSize) {
    tc::println(TCOLOR_CYAN, "开始加载文件: ", filename, TCOLOR_RESET);
    
    tc::ProgressBar bar(40, "█", "░", TCOLOR_GREEN);
    
    // 模拟文件加载
    int loadedSize = 0;
    while (loadedSize < fileSize) {
        // 模拟加载一部分
        int chunk = std::min(fileSize / 50 + rand() % 100, fileSize - loadedSize);
        loadedSize += chunk;
        
        // 更新进度条
        double progress = static_cast<double>(loadedSize) / fileSize;
        std::string msg = "加载中... " + std::to_string(loadedSize) + "/" + std::to_string(fileSize) + " 字节";
        bar.show(progress, msg);
        
        // 模拟加载延迟
        tc::wait(0.05);
    }
    
    bar.finish("文件加载完成!");
}

int main() {
    std::vector<std::pair<std::string, int>> files = {
        {"document.txt", 1024 * 10},      // 10 KB
        {"image.jpg", 1024 * 1024 * 2},   // 2 MB
        {"video.mp4", 1024 * 1024 * 15}   // 15 MB
    };
    
    for (const auto& file : files) {
        simulateFileLoading(file.first, file.second);
        tc::println();
    }
    
    tc::println(TCOLOR_GREEN, TFONT_BOLD, "所有文件加载完成!", TCOLOR_RESET);
    
    return 0;
}
```

### 彩色日志系统

```cpp
#include "tc.hpp"
#include <string>
#include <sstream>
#include <iomanip>

enum class LogLevel {
    DEBUG,
    INFO,
    WARNING,
    ERROR,
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
        if (minLevel_ <= LogLevel::ERROR) {
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
```

### 交互式命令行界面

```cpp
#include "tc.hpp"
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
```

### 游戏示例

```cpp
#include "tc.hpp"
#include <vector>
#include <string>
#include <random>
#include <algorithm>
#include <thread>
#include <chrono>

// 简单的贪吃蛇游戏
class SnakeGame {
private:
    int width_, height_;
    int score_ = 0;
    bool gameOver_ = false;
    
    // 蛇的方向
    enum class Direction { UP, DOWN, LEFT, RIGHT };
    Direction dir_ = Direction::RIGHT;
    
    // 蛇身和食物位置
    struct Point {
        int x, y;
        bool operator==(const Point& other) const {
            return x == other.x && y == other.y;
        }
    };
    
    std::vector<Point> snake_;
    Point food_;
    std::mt19937 rng_;
    
    // 生成随机食物
    void generateFood() {
        std::uniform_int_distribution<int> distX(1, width_ - 2);
        std::uniform_int_distribution<int> distY(1, height_ - 2);
        
        food_ = {distX(rng_), distY(rng_)};
        
        // 确保食物不在蛇身上
        while (std::find(snake_.begin(), snake_.end(), food_) != snake_.end()) {
            food_ = {distX(rng_), distY(rng_)};
        }
    }
    
    // 绘制游戏界面
    void draw() {
        tc::printer().clear();
        
        // 绘制上边界
        for (int x = 0; x < width_; ++x) {
            tc::printer().moveCursor(x, 0);
            tc::print(TCOLOR_CYAN, "#", TCOLOR_RESET);
        }
        
        // 绘制下边界
        for (int x = 0; x < width_; ++x) {
            tc::printer().moveCursor(x, height_ - 1);
            tc::print(TCOLOR_CYAN, "#", TCOLOR_RESET);
        }
        
        // 绘制左右边界
        for (int y = 0; y < height_; ++y) {
            tc::printer().moveCursor(0, y);
            tc::print(TCOLOR_CYAN, "#", TCOLOR_RESET);
            tc::printer().moveCursor(width_ - 1, y);
            tc::print(TCOLOR_CYAN, "#", TCOLOR_RESET);
        }
        
        // 绘制蛇
        for (const auto& p : snake_) {
            tc::printer().moveCursor(p.x, p.y);
            tc::print(TCOLOR_GREEN, "O", TCOLOR_RESET);
        }
        
        // 绘制蛇头
        tc::printer().moveCursor(snake_.front().x, snake_.front().y);
        tc::print(TCOLOR_YELLOW, "@", TCOLOR_RESET);
        
        // 绘制食物
        tc::printer().moveCursor(food_.x, food_.y);
        tc::print(TCOLOR_RED, "*", TCOLOR_RESET);
        
        // 绘制分数
        tc::printer().moveCursor(width_ + 2, 1);
        tc::println(TCOLOR_CYAN, "贪吃蛇游戏", TCOLOR_RESET);
        tc::printer().moveCursor(width_ + 2, 3);
        tc::println(TCOLOR_YELLOW, "分数: ", score_, TCOLOR_RESET);
        tc::printer().moveCursor(width_ + 2, 5);
        tc::println("方向键: 移动");
        tc::printer().moveCursor(width_ + 2, 6);
        tc::println("ESC键: 退出");
        
        // 如果游戏结束，显示提示
        if (gameOver_) {
            tc::printer().moveCursor(width_ / 2 - 5, height_ / 2);
            tc::println(TCOLOR_RED, TFONT_BOLD, "游戏结束!", TCOLOR_RESET);
            tc::printer().moveCursor(width_ / 2 - 10, height_ / 2 + 1);
            tc::println(TCOLOR_YELLOW, "按任意键退出...", TCOLOR_RESET);
        }
    }
    
    // 处理输入
    void handleInput() {
        if (_kbhit()) {
            int key = _getch();
            if (key == 224) { // 方向键前缀
                key = _getch();
                switch (key) {
                    case 72: // 上
                        if (dir_ != Direction::DOWN) dir_ = Direction::UP;
                        break;
                    case 80: // 下
                        if (dir_ != Direction::UP) dir_ = Direction::DOWN;
                        break;
                    case 75: // 左
                        if (dir_ != Direction::RIGHT) dir_ = Direction::LEFT;
                        break;
                    case 77: // 右
                        if (dir_ != Direction::LEFT) dir_ = Direction::RIGHT;
                        break;
                }
            } else if (key == 27) { // ESC
                gameOver_ = true;
            }
        }
    }
    
    // 更新游戏状态
    void update() {
        if (gameOver_) return;
        
        // 根据方向移动蛇头
        Point newHead = snake_.front();
        switch (dir_) {
            case Direction::UP:
                newHead.y--;
                break;
            case Direction::DOWN:
                newHead.y++;
                break;
            case Direction::LEFT:
                newHead.x--;
                break;
            case Direction::RIGHT:
                newHead.x++;
                break;
        }
        
        // 检查是否撞墙
        if (newHead.x <= 0 || newHead.x >= width_ - 1 || 
            newHead.y <= 0 || newHead.y >= height_ - 1) {
            gameOver_ = true;
            return;
        }
        
        // 检查是否撞到自己
        for (size_t i = 1; i < snake_.size(); ++i) {
            if (newHead == snake_[i]) {
                gameOver_ = true;
                return;
            }
        }
        
        // 移动蛇
        snake_.insert(snake_.begin(), newHead);
        
        // 检查是否吃到食物
        if (newHead == food_) {
            score_ += 10;
            generateFood();
        } else {
            snake_.pop_back(); // 如果没吃到食物，移除尾部
        }
    }
    
public:
    SnakeGame(int width = 30, int height = 20) 
        : width_(width), height_(height), rng_(std::random_device()()) {
        // 初始化蛇
        snake_.push_back({width_ / 2, height_ / 2});
        snake_.push_back({width_ / 2 - 1, height_ / 2});
        snake_.push_back({width_ / 2 - 2, height_ / 2});
        
        // 生成第一个食物
        generateFood();
    }
    
    void run() {
        tc::printer().hideCursor();
        
        while (!gameOver_) {
            handleInput();
            update();
            draw();
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        
        draw(); // 最后一次绘制，显示游戏结束
        tc::printer().showCursor();
        tc::waitKey(); // 等待按键退出
    }
};

// 简单的猜数字游戏
void guessNumberGame() {
    tc::printer().clear();
    tc::println(TCOLOR_CYAN, TFONT_BOLD, "猜数字游戏", TCOLOR_RESET);
    tc::println(TCOLOR_CYAN, "==========", TCOLOR_RESET);
    tc::println();
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1, 100);
    
    int secretNumber = distrib(gen);
    int guess;
    int attempts = 0;
    
    tc::println("我想了一个1到100之间的数字。");
    
    while (true) {
        tc::print(TCOLOR_GREEN, "请猜一个数字: ", TCOLOR_RESET);
        std::cin >> guess;
        
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            tc::println(TCOLOR_RED, "请输入一个有效的数字!", TCOLOR_RESET);
            continue;
        }
        
        attempts++;
        
        if (guess < secretNumber) {
            tc::println(TCOLOR_BLUE, "太小了! 再试一次。", TCOLOR_RESET);
        } else if (guess > secretNumber) {
            tc::println(TCOLOR_YELLOW, "太大了! 再试一次。", TCOLOR_RESET);
        } else {
            tc::println();
            tc::println(TCOLOR_GREEN, TFONT_BOLD, "恭喜! 你猜对了!", TCOLOR_RESET);
            tc::println("秘密数字是: ", secretNumber);
            tc::println("你用了 ", attempts, " 次尝试。");
            break;
        }
    }
    
    tc::println();
    tc::println("按任意键返回...");
    tc::waitKey();
}

int main() {
    tc::printer().clear();
    
    std::vector<std::string> gameOptions = {
        "贪吃蛇",
        "猜数字"
    };
    
    int choice;
    do {
        tc::printer().clear();
        tc::println(TCOLOR_CYAN, TFONT_BOLD, "TC.hpp 游戏示例", TCOLOR_RESET);
        tc::println(TCOLOR_CYAN, "==============", TCOLOR_RESET);
        tc::println();
        
        tc::println(TCOLOR_YELLOW, "[1] ", TCOLOR_RESET, "贪吃蛇");
        tc::println(TCOLOR_YELLOW, "[2] ", TCOLOR_RESET, "猜数字");
        tc::println();
        tc::println(TCOLOR_YELLOW, "[0] ", TCOLOR_RESET, "退出");
        tc::println();
        
        tc::print(TCOLOR_GREEN, "请选择游戏 (0-2): ", TCOLOR_RESET);
        std::cin >> choice;
        
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            choice = -1;
            continue;
        }
        
        std::cin.ignore(10000, '\n'); // 清除输入缓冲区
        
        switch (choice) {
            case 1: {
                SnakeGame game;
                game.run();
                break;
            }
            case 2:
                guessNumberGame();
                break;
            case 0:
                tc::println(TCOLOR_GREEN, "谢谢使用!", TCOLOR_RESET);
                break;
            default:
                tc::println(TCOLOR_RED, "无效选择，请重试。", TCOLOR_RESET);
                tc::waitKey();
        }
    } while (choice != 0);
    
    return 0;
}
