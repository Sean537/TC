# TC.hpp 详细使用示例

本文档提供TC库的完整使用示例，涵盖从基础到高级的各种应用场景。

## 基础输出示例

### 1. 基本打印函数

#### `tc::print()` 和 `tc::println()`
```cpp
#include "tc.hpp"

int main() {
    // 基本打印
    tc::print("Hello");           // 输出: Hello
    tc::print(" World");          // 输出: Hello World
    tc::println();                // 换行
    
    // 多参数打印
    tc::println("姓名:", "张三", "年龄:", 25);
    // 输出: 姓名:张三 年龄:25
    
    // 混合类型参数
    tc::println("数字:", 42, "浮点数:", 3.14, "布尔:", true);
    // 输出: 数字:42 浮点数:3.14 布尔:1
    
    return 0;
}
```

#### `tc::tout` 流式输出
```cpp
#include "tc.hpp"

int main() {
    // 标准流式输出
    tc::tout << "Hello" << " " << "World" << std::endl;
    
    // 支持所有标准流操作
    tc::tout << std::setw(10) << "格式化" << std::endl;
    tc::tout << std::fixed << std::setprecision(2) << 3.14159 << std::endl;
    
    return 0;
}
```

### 2. 颜色和样式示例

#### 基本颜色使用
```cpp
#include "tc.hpp"

int main() {
    // 前景色
    tc::println(TCOLOR_RED, "红色文本", TCOLOR_RESET);
    tc::println(TCOLOR_GREEN, "绿色文本", TCOLOR_RESET);
    tc::println(TCOLOR_BLUE, "蓝色文本", TCOLOR_RESET);
    
    // 背景色
    tc::println(TCOLOR_WHITE, BCOLOR_RED, "白字红底", TCOLOR_RESET);
    tc::println(TCOLOR_BLACK, BCOLOR_YELLOW, "黑字黄底", TCOLOR_RESET);
    
    return 0;
}
```

#### 字体样式组合
```cpp
#include "tc.hpp"

int main() {
    // 单个样式
    tc::println(TFONT_BOLD, "粗体文本", TFONT_RESET);
    tc::println(TFONT_UNDERLINE, "下划线", TFONT_RESET);
    tc::println(TFONT_ITALIC, "斜体", TFONT_RESET);
    
    // 样式组合
    tc::println(TCOLOR_RED, TFONT_BOLD, "红色粗体", TCOLOR_RESET);
    tc::println(TCOLOR_GREEN, TFONT_UNDERLINE, "绿色下划线", TCOLOR_RESET);
    tc::println(TCOLOR_BLUE, TFONT_BOLD, TFONT_UNDERLINE, "蓝色粗体下划线", TCOLOR_RESET);
    
    // 复杂组合
    tc::println(TCOLOR_WHITE, BCOLOR_BLUE, TFONT_BOLD, "白字蓝底粗体", TCOLOR_RESET);
    
    return 0;
}
```

### 3. 延时操作示例

#### 基本延时
```cpp
#include "tc.hpp"

int main() {
    tc::println("开始执行...");
    
    // 秒级延时
    tc::wait(1.5);  // 等待1.5秒
    tc::println("1.5秒后");
    
    // 毫秒级延时
    tc::tsleep(500).execute();  // 等待500毫秒
    tc::println("500毫秒后");
    
    return 0;
}
```

#### 流式延时
```cpp
#include "tc.hpp"

int main() {
    // 流式延时操作
    tc::tout << "开始" << tc::tsleep(1000) 
             << "1秒后" << tc::tsleep(500)
             << "500毫秒后" << std::endl;
             
    // 打字机效果
    std::string text = "这是一个打字机效果示例";
    for (char c : text) {
        tc::tout << c << tc::tsleep(50);
    }
    tc::tout << std::endl;
    
    return 0;
}
```

## 中级功能示例

### 4. 进度条应用

#### 基本进度条
```cpp
#include "tc.hpp"

int main() {
    // 创建进度条
    tc::ProgressBar bar(30, "█", "░", TCOLOR_GREEN);
    
    // 模拟处理过程
    for (int i = 0; i <= 100; i += 5) {
        double progress = i / 100.0;
        bar.show(progress, "处理中... " + std::to_string(i) + "%");
        tc::wait(0.1);
    }
    
    bar.finish("处理完成!");
    return 0;
}
```

#### 文件下载模拟
```cpp
#include "tc.hpp"
#include <random>

void simulateDownload(const std::string& filename, int sizeMB) {
    tc::println(TCOLOR_CYAN, "下载: ", filename, " (", sizeMB, "MB)", TCOLOR_RESET);
    
    tc::ProgressBar bar(40, "█", "░", TCOLOR_BLUE);
    int totalBytes = sizeMB * 1024 * 1024;
    int downloaded = 0;
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(50000, 200000);
    
    while (downloaded < totalBytes) {
        int chunk = std::min(dis(gen), totalBytes - downloaded);
        downloaded += chunk;
        
        double progress = static_cast<double>(downloaded) / totalBytes;
        int percent = static_cast<int>(progress * 100);
        int downloadedMB = downloaded / (1024 * 1024);
        
        std::string msg = "下载中... " + std::to_string(downloadedMB) + 
                         "/" + std::to_string(sizeMB) + "MB (" + 
                         std::to_string(percent) + "%)";
        
        bar.show(progress, msg);
        tc::wait(0.05);
    }
    
    bar.finish("下载完成!");
}

int main() {
    simulateDownload("document.pdf", 5);
    simulateDownload("video.mp4", 50);
    return 0;
}
```

### 5. 终端控制示例

#### 光标控制
```cpp
#include "tc.hpp"

int main() {
    // 清屏
    tc::printer().clear();
    
    // 在指定位置打印
    tc::printer().moveCursor(10, 5).print("位置(10,5)");
    tc::printer().moveCursor(20, 8).print("位置(20,8)");
    
    // 相对移动
    tc::printer().moveCursor(tc::Printer::Direction::Down, 2)
                 .print("向下移动2行");
                 
    tc::printer().moveCursor(tc::Printer::Direction::Right, 5)
                 .print("向右移动5列");
    
    // 光标显示控制
    tc::printer().hideCursor();
    tc::wait(2.0);
    tc::printer().showCursor();
    
    return 0;
}
```

#### 终端尺寸和布局
```cpp
#include "tc.hpp"

void drawBox(int x, int y, int width, int height, const std::string& title) {
    // 获取终端尺寸
    auto termSize = tc::printer().getSize();
    
    // 绘制边框
    tc::printer().moveCursor(x, y).print("┌" + std::string(width - 2, '─') + "┐");
    
    for (int i = 1; i < height - 1; ++i) {
        tc::printer().moveCursor(x, y + i).print("│");
        tc::printer().moveCursor(x + width - 1, y + i).print("│");
    }
    
    tc::printer().moveCursor(x, y + height - 1).print("└" + std::string(width - 2, '─') + "┘");
    
    // 标题
    if (!title.empty()) {
        tc::printer().moveCursor(x + 2, y).print(TCOLOR_CYAN, title, TCOLOR_RESET);
    }
}

int main() {
    tc::printer().clear();
    
    auto size = tc::printer().getSize();
    tc::println("终端尺寸: ", size.first, "x", size.second);
    
    // 绘制多个框
    drawBox(5, 3, 30, 10, "窗口1");
    drawBox(40, 3, 30, 10, "窗口2");
    
    // 在框内显示内容
    tc::printer().moveCursor(7, 5).print("这是窗口1的内容");
    tc::printer().moveCursor(42, 5).print("这是窗口2的内容");
    
    return 0;
}
```

### 6. 系统功能示例

#### 系统信息获取
```cpp
#include "tc.hpp"

int main() {
    // 获取系统信息
    int osCode = tc::systemCheck();
    const char* osName = tc::getOSName(osCode);
    std::string versionInfo = tc::getOSVersionInfo();
    
    tc::println(TCOLOR_CYAN, "=== 系统信息 ===", TCOLOR_RESET);
    tc::println("操作系统: ", osName);
    tc::println("版本信息: ", versionInfo);
    
    // 获取时间信息
    tc::println(TCOLOR_CYAN, "=== 时间信息 ===", TCOLOR_RESET);
    tc::println("当前时间: ", 
                tc::getSystemTime(SYS_YEAR), "-",
                tc::getSystemTime(SYS_MONTH), "-",
                tc::getSystemTime(SYS_DAY), " ",
                tc::getSystemTime(SYS_HOUR), ":",
                tc::getSystemTime(SYS_MINUTE), ":",
                tc::getSystemTime(SYS_SECOND));
    
    tc::println("Unix时间戳: ", tc::getSystemTime());
    
    return 0;
}
```

#### 系统命令执行
```cpp
#include "tc.hpp"

int main() {
    tc::println(TCOLOR_CYAN, "=== 系统命令测试 ===", TCOLOR_RESET);
    
    // 执行系统命令
    tc::systemConsole("echo Hello from system command");
    
    // 根据不同系统执行不同命令
    int os = tc::systemCheck();
    if (os == OS_WINDOWSNT11 || os == OS_WINDOWSNT10) {
        tc::systemConsole("dir");  // Windows
    } else {
        tc::systemConsole("ls -la");  // Linux/macOS
    }
    
    return 0;
}
```

## 高级应用示例

### 7. 交互式应用

#### 彩色菜单系统
```cpp
#include "tc.hpp"
#include <vector>
#include <string>

class MenuSystem {
    std::vector<std::string> options;
    
public:
    MenuSystem(const std::vector<std::string>& opts) : options(opts) {}
    
    int show() {
        tc::printer().clear();
        
        // 标题
        tc::println(TCOLOR_CYAN, TFONT_BOLD, "=== 菜单系统 ===", TCOLOR_RESET);
        tc::println();
        
        // 显示选项
        for (size_t i = 0; i < options.size(); ++i) {
            tc::println(TCOLOR_YELLOW, "[", i + 1, "] ", TCOLOR_RESET, options[i]);
        }
        tc::println(TCOLOR_YELLOW, "[0] ", TCOLOR_RESET, "退出");
        tc::println();
        
        // 获取用户输入
        int choice;
        tc::print(TCOLOR_GREEN, "请选择 (0-", options.size(), "): ", TCOLOR_RESET);
        std::cin >> choice;
        
        return choice;
    }
};

int main() {
    std::vector<std::string> menuItems = {
        "查看系统信息",
        "显示当前时间", 
        "测试颜色输出",
        "演示进度条"
    };
    
    MenuSystem menu(menuItems);
    int choice;
    
    do {
        choice = menu.show();
        
        tc::printer().clear();
        switch (choice) {
            case 1:
                tc::println("系统: ", tc::getOSName(tc::systemCheck()));
                break;
            case 2:
                tc::println("时间: ", tc::getSystemTime(SYS_HOUR), ":", 
                           tc::getSystemTime(SYS_MINUTE));
                break;
            case 3:
                tc::println(TCOLOR_RED, "红色", TCOLOR_GREEN, "绿色", 
                           TCOLOR_BLUE, "蓝色", TCOLOR_RESET);
                break;
            case 4: {
                tc::ProgressBar bar(30, "█", "░", TCOLOR_GREEN);
                for (int i = 0; i <= 100; i += 10) {
                    bar.show(i / 100.0, "演示中...");
                    tc::wait(0.2);
                }
                bar.finish();
                break;
            }
            case 0:
                tc::println("再见!");
                break;
            default:
                tc::println(TCOLOR_RED, "无效选择!", TCOLOR_RESET);
        }
        
        if (choice != 0) {
            tc::println("\n按任意键继续...");
            tc::waitKey();
        }
    } while (choice != 0);
    
    return 0;
}
```

#### 实时按键检测
```cpp
#include "tc.hpp"

int main() {
    tc::printer().clear();
    tc::println(TCOLOR_CYAN, "按键检测演示 (按ESC退出)", TCOLOR_RESET);
    
    tc::printer().hideCursor();
    
    while (true) {
        // 检测方向键
        if (tc::isKeyPressed(KEY_UP)) {
            tc::printer().moveCursor(10, 5).print(TCOLOR_GREEN, "↑ 上", TCOLOR_RESET);
        }
        if (tc::isKeyPressed(KEY_DOWN)) {
            tc::printer().moveCursor(10, 6).print(TCOLOR_GREEN, "↓ 下", TCOLOR_RESET);
        }
        if (tc::isKeyPressed(KEY_LEFT)) {
            tc::printer().moveCursor(10, 7).print(TCOLOR_GREEN, "← 左", TCOLOR_RESET);
        }
        if (tc::isKeyPressed(KEY_RIGHT)) {
            tc::printer().moveCursor(10, 8).print(TCOLOR_GREEN, "→ 右", TCOLOR_RESET);
        }
        
        // 检测ESC键退出
        if (tc::isKeyPressed(KEY_ESC)) {
            break;
        }
        
        tc::tsleep(50).execute();
    }
    
    tc::printer().showCursor();
    tc::printer().clear();
    tc::println("演示结束");
    
    return 0;
}
```

### 8. 动画效果

#### 旋转加载动画
```cpp
#include "tc.hpp"
#include <vector>

class Spinner {
    std::vector<std::string> frames;
    int currentFrame;
    
public:
    Spinner() : frames{"|", "/", "-", "\\"}, currentFrame(0) {}
    
    void update() {
        tc::print("\r", TCOLOR_CYAN, "加载中 ", frames[currentFrame], TCOLOR_RESET);
        currentFrame = (currentFrame + 1) % frames.size();
    }
    
    void finish(const std::string& message = "完成") {
        tc::println("\r", TCOLOR_GREEN, message, TCOLOR_RESET, "     ");
    }
};

int main() {
    Spinner spinner;
    tc::printer().hideCursor();
    
    // 模拟长时间操作
    for (int i = 0; i < 50; ++i) {
        spinner.update();
        tc::tsleep(100).execute();
    }
    
    spinner.finish("处理完成");
    tc::printer().showCursor();
    
    return 0;
}
```

#### 进度动画
```cpp
#include "tc.hpp"

void progressAnimation(int durationSeconds) {
    tc::printer().hideCursor();
    
    for (int i = 0; i <= 100; ++i) {
        int barWidth = 30;
        int filled = (i * barWidth) / 100;
        int empty = barWidth - filled;
        
        tc::print("\r", TCOLOR_CYAN, "[", TCOLOR_RESET);
        tc::print(TCOLOR_GREEN, std::string(filled, '='));
        tc::print(std::string(empty, ' '));
        tc::print(TCOLOR_CYAN, "] ", TCOLOR_RESET);
        tc::print(i, "%");
        
        tc::tsleep((durationSeconds * 1000) / 100).execute();
    }
    
    tc::println("\r", TCOLOR_GREEN, "完成!     ", TCOLOR_RESET);
    tc::printer().showCursor();
}

int main() {
    tc::println("进度动画演示 (3秒):");
    progressAnimation(3);
    return 0;
}
```

### 9. 实用工具类

#### 彩色日志系统
```cpp
#include "tc.hpp"
#include <string>
#include <chrono>
#include <iomanip>

class Logger {
public:
    static void debug(const std::string& msg) {
        log("DEBUG", msg, TCOLOR_BLUE);
    }
    
    static void info(const std::string& msg) {
        log("INFO", msg, TCOLOR_GREEN);
    }
    
    static void warning(const std::string& msg) {
        log("WARN", msg, TCOLOR_YELLOW);
    }
    
    static void error(const std::string& msg) {
        log("ERROR", msg, TCOLOR_RED);
    }
    
private:
    static void log(const std::string& level, const std::string& msg, int color) {
        auto now = std::chrono::system_clock::now();
        auto time_t = std::chrono::system_clock::to_time_t(now);
        
        tc::tout << "[";
        tc::tout << std::put_time(std::localtime(&time_t), "%H:%M:%S");
        tc::tout << "] ";
        tc::tout << color << "[" << level << "]" << TCOLOR_RESET << " ";
        tc::tout << msg << std::endl;
    }
};

int main() {
    Logger::info("应用程序启动");
    Logger::debug("调试信息");
    Logger::warning("磁盘空间不足");
    Logger::error("连接超时");
    
    return 0;
}
```

#### 命令行参数解析
```cpp
#include "tc.hpp"
#include <vector>
#include <string>
#include <map>

class CommandLineParser {
    std::map<std::string, std::function<void()>> commands;
    
public:
    void addCommand(const std::string& name, const std::function<void()>& func) {
        commands[name] = func;
    }
    
    void run() {
        std::string input;
        
        while (true) {
            tc::print(TCOLOR_GREEN, "> ", TCOLOR_RESET);
            std::getline(std::cin, input);
            
            if (input == "exit" || input == "quit") {
                break;
            }
            
            if (commands.find(input) != commands.end()) {
                commands[input]();
            } else {
                tc::println(TCOLOR_RED, "未知命令: '", input, "'", TCOLOR_RESET);
                tc::println("可用命令: ");
                for (const auto& cmd : commands) {
                    tc::println("  ", cmd.first);
                }
            }
        }
    }
};

int main() {
    CommandLineParser parser;
    
    parser.addCommand("time", []() {
        tc::println("当前时间: ", tc::getSystemTime(SYS_HOUR), ":", 
                   tc::getSystemTime(SYS_MINUTE));
    });
    
    parser.addCommand("clear", []() {
        tc::printer().clear();
    });
    
    parser.addCommand("system", []() {
        tc::println("系统: ", tc::getOSName(tc::systemCheck()));
    });
    
    parser.run();
    
    return 0;
}
```

这些示例展示了TC库的强大功能，从简单的文本输出到复杂的交互式应用。您可以根据具体需求选择合适的示例进行修改和扩展。