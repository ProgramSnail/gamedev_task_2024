add_requires("libx11")

add_rules("mode.debug", "mode.release")

set_languages("c++20")

target("game")
    set_kind("binary")
    add_includedirs("include")
    -- add_includedirs(os.dirs(path.join(os.scriptdir(), "include/**")))
    add_files("src/**.cpp")
    add_packages("libx11")
    set_warnings("allextra")
    set_rundir("$(projectdir)")
