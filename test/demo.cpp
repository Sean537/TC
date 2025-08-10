#include "../tc.hpp"

int main() {
    tc::tout << TCOLOR_GREEN << "Hello, world!\n" << TCOLOR_RESET;
    tc::println(TCOLOR_YELLOW, "Welcome to the ", TFONT_BOLD, "TC.hpp", TFONT_RESET);
    tc::print(TCOLOR_BLUE, "Are you ready?\n");
    tc::ProgressBar bar(50, "█", "░", TCOLOR_GREEN);
    for (int i = 0; i <= 100; ++i){
        bar.show(i / 100.0, "Loading...");
        tc::wait(0.05);
    }
    bar.finish();
    return 0;
}