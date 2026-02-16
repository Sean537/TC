#include "../include/tc.hpp"
#include <vector>
#include <string>
#include <random>
#include <algorithm>
#include <thread>
#include <chrono>

#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#endif

// 跨平台按键检测
inline int kbhit() {
#ifdef _WIN32
    return _kbhit();
#else
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if(ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }
    return 0;
#endif
}

inline int getch() {
#ifdef _WIN32
    return _getch();
#else
    int ch;
    struct termios oldt, newt;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
#endif
}

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
    Point last_tail_{-1, -1};
    Point food_;
    std::mt19937 rng_;

    // 生成随机食物
    void generateFood() {
        std::uniform_int_distribution<int> distX(2, width_ - 2);
        std::uniform_int_distribution<int> distY(2, height_ - 2);

        food_ = {distX(rng_), distY(rng_)};

        // 确保食物不在蛇身上
        while (std::find(snake_.begin(), snake_.end(), food_) != snake_.end()) {
            food_ = {distX(rng_), distY(rng_)};
        }
    }

    // 绘制游戏界面
    void draw() {
        tc::printer().moveCursor(0, 0);

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

        //清除旧的尾巴
        if(last_tail_.x != -1 && last_tail_.y != -1){
            tc::printer().moveCursor(last_tail_.x, last_tail_.y);
            tc::print(" ", TCOLOR_RESET);
        }else{
            tc::printer().moveCursor(snake_.back().x, snake_.back().y);
            tc::print(" ", TCOLOR_RESET);
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
        if (kbhit()) {
            int key = getch();
#ifdef _WIN32
            if (key == 224) { // 方向键前缀
                key = getch();
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
            }
#else
            if (key == 27) {  // ESC 序列开始
                if (getch() == '[') {
                    key = getch();
                    switch (key) {
                        case 'A': // 上
                            if (dir_ != Direction::DOWN) dir_ = Direction::UP;
                            break;
                        case 'B': // 下
                            if (dir_ != Direction::UP) dir_ = Direction::DOWN;
                            break;
                        case 'D': // 左
                            if (dir_ != Direction::RIGHT) dir_ = Direction::LEFT;
                            break;
                        case 'C': // 右
                            if (dir_ != Direction::LEFT) dir_ = Direction::RIGHT;
                            break;
                    }
                }
            }
#endif
            if (key == 27) { // ESC 键
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
        if (newHead.x <= 1 || newHead.x >= width_ - 1 ||
            newHead.y <= 1 || newHead.y >= height_ - 1) {
            gameOver_ = true;
            return;
        }

        // 检查是否撞到自己
        for (const auto& segment : snake_) {
            if (newHead == segment) {
                gameOver_ = true;
                return;
            }
        }

        // 移动蛇
        snake_.insert(snake_.begin(), newHead);

        // 检查是否吃到食物
        if (newHead == food_) {
            score_ += 10;
            last_tail_ = {-1, -1};
            generateFood();
        } else {
            last_tail_ = snake_.back();
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
        tc::printer().clear();

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

int main() {
    tc::printer().clear();
    tc::println(TCOLOR_CYAN, TFONT_BOLD, "贪吃蛇游戏", TCOLOR_RESET);
    tc::println(TCOLOR_CYAN, "==========", TCOLOR_RESET);
    tc::println();
    tc::println("使用方向键控制蛇的移动，按ESC键退出游戏。");
    tc::println("按任意键开始游戏...");
    tc::waitKey();

    SnakeGame game;
    game.run();

    tc::terminal::clear();
    return 0;
}
