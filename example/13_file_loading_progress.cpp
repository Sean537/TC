#include "../tc.hpp"
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