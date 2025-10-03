# TC.hpp 使用示例

本文档提供TC库的实用示例，从基础到高级应用。

## 基础示例

### 1. 基本输出和颜色
```cpp
#include "tc.hpp"

int main() {
    // 标准输出
    tc::print("Hello", " ", "World");
    tc::println("Hello", " ", "World");
    
    // 颜色输出
    tc::println(TCOLOR_RED, "红色", TCOLOR_GREEN, "绿色", TCOLOR_BLUE, "蓝色", TCOLOR_RESET);
    
    // 背景色
    tc::println(TCOLOR_WHITE, BCOLOR_BLUE, "白字蓝底", TCOLOR_RESET);
    
    return 0;
}
```

### 2. 字体样式
```cpp
#include "tc.hpp"

int main() {
    tc::println(TFONT_BOLD, "粗体", TFONT_RESET);
    tc::println(TFONT_UNDERLINE, "下划线", TFONT_RESET); 
    tc::println(TFONT_ITALIC, "斜体", TFONT_RESET);
    tc::println(TFONT_CROSSED, "删除线", TFONT_RESET);
    
    // 组合样式
    tc::println(TCOLOR_RED, TFONT_BOLD, "红色粗体", TCOLOR_RESET);
    
    return 0;
}
```

### 3. 延时操作
```cpp
#include "tc.hpp"

int main() {
    tc::println("开始...");
    tc::wait(1.0);  // 等待1秒
    
    tc::println("等待500毫秒...");
    tc::tsleep(500).execute();
    
    // 流式延时
    tc::tout << "前" << tc::tsleep(300) << "中" << tc::tsleep(300) << "后" << std::endl;
    
    return 0;
}
```

## 中级示例

### 4. 进度条
```cpp
#include "tc.hpp"

int main() {
    tc::ProgressBar bar(30, "█", "░", TCOLOR_GREEN);
    
    // 模拟处理过程
    for (int i = 0; i <= 100; ++i) {
        bar.show(i / 100.0, "处理中...");
        tc::wait(0.02);
    }
    
    bar.finish("完成!");
    return 0;
}
```

### 5. 光标控制
```cpp
#include "tc.hpp"

int main() {
    tc::printer().clear();
    
    // 在指定位置打印
    tc::printer().moveCursor(10, 5).print("位置(10,5)");
    tc::printer().moveCursor(15, 8).print("位置(15,8)");
    
    // 隐藏光标
    tc::printer().hideCursor();
    tc::wait(2.0);
    tc::printer().showCursor();
    
    return 0;
}
```

### 6. 终端尺寸和居中显示
```cpp
#include "tc.hpp"

int main() {
    auto size = tc::printer().getSize();
    int centerX = size.first / 2;
    int centerY = size.second / 2;
    
    tc::printer().clear();
    tc::printer().moveCursor(centerX - 5, centerY);
    tc::println(TCOLOR_CYAN, "居中文本", TCOLOR_RESET);
    
    return 0;
}
```

## 高级示例

### 7. 打字机效果
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
    typewriter("这是一个打字机效果...");
    tc::print(TCOLOR_GREEN);
    typewriter("绿色打字机效果...", 30);
    tc::print(TCOLOR_RESET);
    
    return 0;
}
```

### 8. 彩色菜单系统
```cpp
#include "tc.hpp"
#include <vector>
#include <string>

int showMenu(const std::vector<std::string>& options) {
    tc::printer().clear();
    
    // 标题
    tc::println(TCOLOR_CYAN, TFONT_BOLD, "菜单系统", TCOLOR_RESET);
    tc::println();
    
    // 选项
    for (size_t i = 0; i < options.size(); ++i) {
        tc::println(TCOLOR_YELLOW, "[", i + 1, "] ", TCOLOR_RESET, options[i]);
    }
    tc::println(TCOLOR_YELLOW, "[0] ", TCOLOR_RESET, "退出");
    
    // 输入处理
    int choice;
    tc::print(TCOLOR_GREEN, "请选择: ", TCOLOR_RESET);
    std::cin >> choice;
    
    return choice;
}

int main() {
    std::vector<std::string> options = {"选项一", "选项二", "选项三"};
    
    int choice;
    do {
        choice = showMenu(options);
        
        tc::printer().clear();
        switch (choice) {
            case 1: tc::println("选择了选项一"); break;
            case 2: tc::println("选择了选项二"); break;
            case 3: tc::println("选择了选项三"); break;
            case 0: tc::println("退出"); break;
            default: tc::println("无效选择");
        }
        
        if (choice != 0) {
            tc::println("\n按任意键继续...");
            tc::waitKey();
        }
    } while (choice != 0);
    
    return 0;
}
```

### 9. 动画效果
```cpp
#include "tc.hpp"
#include <vector>

void spinner(int seconds) {
    std::vector<std::string> frames = {"|", "/", "-", "\\"};
    tc::printer().hideCursor();
    
    for (int i = 0; i < seconds * 10; ++i) {
        tc::print("\r", TCOLOR_CYAN, "加载中 ", frames[i % 4], TCOLOR_RESET);
        tc::tsleep(100).execute();
    }
    
    tc::println("\r", TCOLOR_GREEN, "完成!     ", TCOLOR_RESET);
    tc::printer().showCursor();
}

int main() {
    tc::println("显示旋转动画:");
    spinner(3);
    return 0;
}
```

## 实用案例

### 10. 文件加载模拟
```cpp
#include "tc.hpp"

void simulateFileLoad(const std::string& filename, int sizeKB) {
    tc::println(TCOLOR_CYAN, "加载文件: ", filename, TCOLOR_RESET);
    
    tc::ProgressBar bar(40, "█", "░", TCOLOR_GREEN);
    int totalBytes = sizeKB * 1024;
    int loaded = 0;
    
    while (loaded < totalBytes) {
        int chunk = std::min(1024 + rand() % 512, totalBytes - loaded);
        loaded += chunk;
        
        double progress = static_cast<double>(loaded) / totalBytes;
        std::string msg = "加载中... " + std::to_string(loaded/1024) + "/" + std::to_string(sizeKB) + " KB";
        bar.show(progress, msg);
        
        tc::wait(0.05);
    }
    
    bar.finish("加载完成!");
}

int main() {
    simulateFileLoad("document.txt", 50);
    simulateFileLoad("image.jpg", 2048);
    return 0;
}
```

### 11. 彩色日志系统
```cpp
#include "tc.hpp"
#include <string>

class Logger {
public:
    static void info(const std::string& msg) {
        tc::println(TCOLOR_GREEN, "[INFO] ", TCOLOR_RESET, msg);
    }
    
    static void warning(const std::string& msg) {
        tc::println(TCOLOR_YELLOW, "[WARN] ", TCOLOR_RESET, msg);
    }
    
    static void error(const std::string& msg) {
        tc::println(TCOLOR_RED, "[ERROR] ", TCOLOR_RESET, msg);
    }
};

int main() {
    Logger::info("系统启动");
    Logger::warning("磁盘空间不足");
    Logger::error("连接失败");
    return 0;
}
```

### 12. 交互式命令行
```cpp
#include "tc.hpp"
#include <string>
#include <map>
#include <functional>

class SimpleCLI {
    std::map<std::string, std::function<void()>> commands;
    
public:
    SimpleCLI() {
        commands["help"] = [this]() { showHelp(); };
        commands["time"] = []() { 
            tc::println("时间: ", tc::getSystemTime(SYS_HOUR), ":", 
                       tc::getSystemTime(SYS_MINUTE));
        };
        commands["clear"] = []() { tc::printer().clear(); };
    }
    
    void showHelp() {
        tc::println("可用命令: help, time, clear, exit");
    }
    
    void run() {
        tc::println(TCOLOR_CYAN, "简单CLI (输入help查看命令)", TCOLOR_RESET);
        
        std::string input;
        while (true) {
            tc::print(TCOLOR_GREEN, "> ", TCOLOR_RESET);
            std::getline(std::cin, input);
            
            if (input == "exit") break;
            
            if (commands.find(input) != commands.end()) {
                commands[input]();
            } else {
                tc::println(TCOLOR_RED, "未知命令: ", input, TCOLOR_RESET);
            }
        }
    }
};

int main() {
    SimpleCLI cli;
    cli.run();
    return 0;
}
```

### 13. 系统信息显示
```cpp
#include "tc.hpp"

int main() {
    tc::printer().clear();
    
    // 系统信息
    int os = tc::systemCheck();
    tc::println(TCOLOR_CYAN, "系统信息", TCOLOR_RESET);
    tc::println("操作系统: ", tc::getOSName(os));
    tc::println("时间: ", tc::getSystemTime(SYS_YEAR), "-",
                tc::getSystemTime(SYS_MONTH), "-", tc::getSystemTime(SYS_DAY));
    
    // 终端信息
    auto size = tc::printer().getSize();
    tc::println("终端尺寸: ", size.first, "x", size.second);
    
    return 0;
}
```

这些示例展示了TC库的各种功能，从基础的颜色输出到复杂的交互式应用。您可以根据需要修改和扩展这些示例。