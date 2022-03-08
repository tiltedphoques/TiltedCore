set_languages("cxx17")

set_xmakever("2.5.1")

add_requires("mimalloc", "hopscotch-map", "catch2")
add_requireconfs("mimalloc", {configs = {rltgenrandom = true}})

add_rules("mode.debug","mode.releasedbg", "mode.release")
add_rules("plugin.vsxmake.autoupdate")

if is_mode("release") then
    add_defines("NDEBUG")
    set_optimize("fastest")
end

option("cxx_allocator_override")
    add_defines("TPCORE_CXX_ALLOCATOR_OVERRIDE")

target("TiltedCore")
    set_kind("static")
    add_files("Code/core/src/*.cpp")
    add_includedirs("Code/core/include/", {public = true})
    add_headerfiles("Code/core/include/*.hpp", {prefixdir = "TiltedCore"})
    add_packages("mimalloc", "hopscotch-map")

target("Tests")
    set_kind("binary")
    add_files("Code/tests/src/*.cpp")
    add_deps("TiltedCore")
    add_packages("TiltedCore", "catch2", "hopscotch-map")
    add_cxflags("-fPIC")
