set_project("TC")

add_rules("mode.debug", "mode.release")

rule("winapi")
    on_load(function (target)
        if is_plat("windows") then
            target:add("syslinks", "user32")
            target:add("syslinks", "Advapi32")
        end
    end)
rule_end()

target("TC-core")
    add_rules("winapi")
    set_languages("cxx17")
    set_kind("headeronly")
    set_warnings("all", "extra", "pedantic")

    add_includedirs("include", {public = true})
    add_headerfiles("include/(*.hpp)")

    add_defines("_CRT_SECURE_NO_WARNINGS")
    add_defines("NOMINMAX")

    if is_plat("windows") then
        add_cxflags("/utf-8", {force = true})
        add_cxxflags("/utf-8", {force = true})
    end
target_end()

function add_example(example_name)
    target("example-" .. example_name)
        add_rules("winapi")
        set_languages("cxx20")
        set_kind("binary")
        set_default(false)
        set_warnings("all", "extra", "pedantic")

        add_files("example/" .. example_name .. ".cpp")
        add_deps("TC-core")

        add_defines("_CRT_SECURE_NO_WARNINGS")
        add_defines("NOMINMAX")

        if is_plat("windows") then
            add_cxflags("/utf-8", {force = true})
            add_cxxflags("/utf-8", {force = true})
        end

        after_build(function (target)
            os.cp(target:targetfile(), "bin/examples/")
        end)
    target_end()
end

add_example("01_basic_output")
add_example("02_color_output")
add_example("03_font_styles")
add_example("04_delay_operations")
add_example("05_progress_bar")
add_example("06_cursor_control")
add_example("07_terminal_size")
add_example("08_key_wait")
add_example("09_typewriter_effect")
add_example("10_color_menu")
add_example("11_animation_effects")
add_example("12_system_info")
add_example("13_file_loading_progress")
add_example("14_color_logger")
add_example("15_interactive_cli")
add_example("16_snake_game")
add_example("17_guess_number_game")
add_example("18_game_menu")
add_example("19_painting_game")
add_example("20_terminal_printer_demo")
