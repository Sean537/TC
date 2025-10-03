# TC Example Makefile

.PHONY: all cmake-debug cmake-release cmake-config xmake-examples clean

# CMake 构建目录
BUILD_DIR := build

# 例子列表
EXAMPLES := \
  01_basic_output \
  02_color_output \
  03_font_styles \
  04_delay_operations \
  05_progress_bar \
  06_cursor_control \
  07_terminal_size \
  08_key_wait \
  09_typewriter_effect \
  10_color_menu \
  11_animation_effects \
  12_system_info \
  13_file_loading_progress \
  14_color_logger \
  15_interactive_cli \
  16_snake_game \
  17_guess_number_game \
  18_game_menu \
  19_painting_game \
  20_terminal_printer_demo

# 默认目标：Release 构建所有示例
all: cmake-release

# 配置 CMake（可通过变量切换开关：WIN32_API=ON/OFF）
cmake-config:
	@if not exist "$(BUILD_DIR)" mkdir "$(BUILD_DIR)"
	@cmake -S . -B "$(BUILD_DIR)" -DTC_ENABLE_WIN32_CONSOLE_API=$(if $(WIN32_API),$(WIN32_API),OFF)

# Debug 构建（一次性构建所有示例）
cmake-debug: cmake-config
	@cmake --build "$(BUILD_DIR)" --config Debug

# Release 构建（一次性构建所有示例）
cmake-release: cmake-config
	@cmake --build "$(BUILD_DIR)" --config Release

# 使用 xmake 批量构建所有示例（需要已安装 xmake）
# 可通过 WIN32_API=ON 传入时，使用 xmake f --win32_console_api=y 开启宏
xmake-examples:
	@xmake f -m release $(if $(filter ON,$(WIN32_API)),--win32_console_api=y)
	@$(foreach ex,$(EXAMPLES), xmake build example-$(ex) & )

# 清理构建产物
clean:
	@cmake --build "$(BUILD_DIR)" --target clean --config Debug 2>NUL || true
	@cmake --build "$(BUILD_DIR)" --target clean --config Release 2>NUL || true
	@if exist "$(BUILD_DIR)" rmdir /S /Q "$(BUILD_DIR)" 2>NUL || true
	@if exist "bin\\examples" rmdir /S /Q "bin\\examples" 2>NUL || true