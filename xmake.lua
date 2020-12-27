set_languages("cxx17")

add_requires("mimalloc", {config = {rltgenrandom = true }})
add_requires("catch2")

target("TiltedCore")
    set_kind("static")
    add_files("Code/core/src/*.cpp")
    add_includedirs("Code/core/include/", {public = true})
    add_headerfiles("Code/core/include/*.hpp", {prefixdir = "TiltedCore"})
    add_packages("mimalloc")

target("Tests")
    set_kind("binary")
    add_files("Code/tests/src/*.cpp")
    add_deps("TiltedCore")
    add_packages("TiltedCore", "catch2")
    add_cxflags("-fPIC")
