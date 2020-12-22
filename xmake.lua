set_languages("cxx17")

add_requires("mimalloc", "catch2")

target("TiltedCore")
    set_kind("static")
    add_files("Code/core/src/*.cpp")
    add_includedirs("Code/core/include/", {public = true})
    add_packages("mimalloc")

target("Tests")
    set_kind("binary")
    add_files("Code/tests/src/*.cpp")
    add_deps("TiltedCore")
    add_packages("TiltedCore", "catch2")
    add_cxflags("-fPIC")
