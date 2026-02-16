cmake_minimum_required(VERSION 3.16)
project(TC LANGUAGES CXX)

# 开关：在 Windows 上启用 Win32 Console API（禁用 ANSI，便捷函数保留 ANSI）
option(TC_ENABLE_WIN32_CONSOLE_API "Use Win32 Console API on Windows (disable ANSI escapes, keep convenient color functions ANSI)" OFF)
if (WIN32 AND TC_ENABLE_WIN32_CONSOLE_API)
    add_compile_definitions(TC_ENABLE_WIN32_CONSOLE_API)
endif()
# Global C++17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Header-only core library
add_library(TC-core INTERFACE)
target_include_directories(TC-core INTERFACE "${CMAKE_SOURCE_DIR}/include")
target_compile_definitions(TC-core INTERFACE _CRT_SECURE_NO_WARNINGS NOMINMAX)

# Warnings and UTF-8 (match xmake: all/extra/pedantic, MSVC /utf-8)
target_compile_options(TC-core INTERFACE
    $<$<CXX_COMPILER_ID:MSVC>:/W4>
    $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:-Wall -Wextra -Wpedantic>
    $<$<CXX_COMPILER_ID:AppleClang>:-Wall -Wextra -Wpedantic>
    $<$<CXX_COMPILER_ID:MSVC>:/utf-8>
)

# Windows system links (user32, advapi32)
if(WIN32)
    target_link_libraries(TC-core INTERFACE user32 advapi32)
endif()

# Where to copy built examples (align with xmake's bin/examples/)
set(EXAMPLE_OUTPUT_DIR "${CMAKE_SOURCE_DIR}/bin/examples")

function(add_example example_name)
    add_executable(example-${example_name} "example/${example_name}.cpp")



    target_link_libraries(example-${example_name} PRIVATE TC-core)
    target_compile_definitions(example-${example_name} PRIVATE _CRT_SECURE_NO_WARNINGS NOMINMAX)

    # Warnings and UTF-8 for examples
    target_compile_options(example-${example_name} PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:/W4>
        $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:-Wall -Wextra -Wpedantic>
        $<$<CXX_COMPILER_ID:AppleClang>:-Wall -Wextra -Wpedantic>
        $<$<CXX_COMPILER_ID:MSVC>:/utf-8>
    )

    # Post-build: ensure dir and copy executable
    add_custom_command(TARGET example-${example_name} POST_BUILD
        COMMAND "${CMAKE_COMMAND}" -E make_directory "${EXAMPLE_OUTPUT_DIR}"
        COMMAND "${CMAKE_COMMAND}" -E copy_if_different "$<TARGET_FILE:example-${example_name}>" "${EXAMPLE_OUTPUT_DIR}/"
        VERBATIM
    )
endfunction()

# Add all examples (one-step build builds all)
add_example(01_basic_output)
add_example(02_color_output)
add_example(03_font_styles)
add_example(04_delay_operations)
add_example(05_progress_bar)
add_example(06_cursor_control)
add_example(07_terminal_size)
add_example(08_key_wait)
add_example(09_typewriter_effect)
add_example(10_color_menu)
add_example(11_animation_effects)
add_example(12_system_info)
add_example(13_file_loading_progress)
add_example(14_color_logger)
add_example(15_interactive_cli)
add_example(16_snake_game)
add_example(17_guess_number_game)
add_example(18_game_menu)
add_example(19_painting_game)
add_example(20_terminal_printer_demo)