/*
 * tc_progress.hpp - TC库进度条模块
 * TC Progress Bar Module
 * 
 * 这个文件包含了TC库中的进度条功能，包括：
 * - 可自定义的文本进度条
 * - 支持自定义宽度、字符和颜色
 * - 实时进度显示和百分比
 * - 进度完成提示功能
 * 
 * This file contains progress bar functionality in the TC library, including:
 * - Customizable text progress bar
 * - Support for custom width, characters and colors
 * - Real-time progress display and percentage
 * - Progress completion notification
 * 
 * 版本 Version: 1.1.1 Beta
 * 作者 Author: 537 Studio
 * 许可 License: MIT
 */

#ifndef TC_PROGRESS_HPP
#define TC_PROGRESS_HPP

// 标准库包含 | Standard library includes
#include <iostream>  // 输入输出流 | Input/output streams
#include <string>    // 字符串类 | String class
#include "tc_colors.hpp" // TC颜色模块 | TC color module

namespace tc {

/**
 * 进度条类
 * Progress bar class
 * 
 * 这个类提供了一个可自定义的文本进度条，用于显示操作的进度。
 * 进度条可以自定义宽度、完成和未完成部分的字符，以及颜色。
 * 支持实时更新进度和显示自定义消息。
 * 
 * This class provides a customizable text progress bar for displaying operation progress.
 * The progress bar can be customized with width, characters for completed and uncompleted parts, and color.
 * Supports real-time progress updates and custom message display.
 */
class ProgressBar {
private:
    int width_;           // 进度条宽度（字符数） | Progress bar width (in characters)
    std::string done_;    // 已完成部分的字符 | Character for completed parts
    std::string todo_;    // 未完成部分的字符 | Character for uncompleted parts
    std::string color_;   // 进度条颜色（ANSI颜色代码） | Progress bar color (ANSI color code)
    
public:
    /**
     * 构造函数
     * Constructor
     * 
     * @param width 进度条宽度 | Progress bar width
     * @param done 已完成部分的字符，默认为"#" | Character for completed parts, defaults to "#"
     * @param todo 未完成部分的字符，默认为"-" | Character for uncompleted parts, defaults to "-"
     * @param color 进度条颜色，默认为绿色 | Progress bar color, defaults to green
     */
    ProgressBar(int width, std::string done = "#", std::string todo = "-", std::string color = TCOLOR_GREEN)
        : width_(width), done_(std::move(done)), todo_(std::move(todo)), color_(std::move(color)) {}
    
    /**
     * 显示进度条
     * Show progress bar
     * 
     * 根据当前进度值显示进度条，包括进度条本体、百分比和自定义消息。
     * 使用\r回车符实现在同一行更新进度显示。
     * 
     * Displays the progress bar based on current progress value, including progress bar body,
     * percentage and custom message. Uses \r carriage return for same-line progress updates.
     * 
     * @param progress 进度值(0.0-1.0) | Progress value (0.0-1.0)
     * @param msg 显示在进度条旁的消息 | Message to display next to the progress bar
     */
    void show(double progress, const std::string& msg = "Loading...") {
        // 计算已完成部分的位置 | Calculate position of completed part
        int pos = static_cast<int>(width_ * progress);
        
        // 输出进度条 | Output progress bar
        std::cout << "\r" << color_ << "["; // 回车并开始进度条 | Carriage return and start progress bar
        
        // 绘制进度条主体 | Draw progress bar body
        for (int i = 0; i < width_; ++i) {
            std::cout << (i < pos ? done_ : todo_); // 根据位置输出已完成或未完成字符 | Output completed or uncompleted character based on position
        }
        
        // 输出百分比和消息 | Output percentage and message
        std::cout << "] " << int(progress * 100) << "% " << msg << TCOLOR_RESET << std::flush;
    }
    
    /**
     * 完成进度条
     * Finish progress bar
     * 
     * 显示100%进度并换行，通常在操作完成时调用。
     * 这个函数会自动显示100%的进度并添加换行符。
     * 
     * Shows 100% progress and adds a newline, typically called when operation is complete.
     * This function automatically displays 100% progress and adds a newline character.
     * 
     * @param content 完成时显示的消息 | Message to display when finished
     */
    void finish(std::string content = "Finished") {
        show(1.0, content); // 显示100%进度 | Show 100% progress
        std::cout << std::endl; // 换行 | Add newline
    }
};

} // namespace tc

#endif // TC_PROGRESS_HPP