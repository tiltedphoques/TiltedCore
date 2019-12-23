premake.extensions.core = {}

function core_parent_path()
    local str = debug.getinfo(2, "S").source:sub(2)
    local dir =  str:match("(.*/)"):sub(0,-2)
    local index = string.find(dir, "/[^/]*$")
    return dir:sub(0, index)
end

function core_generate()
    if premake.extensions.core.core_generated == true then
        return
    end

    project ("Core")
        kind ("StaticLib")
        language ("C++")

        includedirs
        {
            premake.extensions.core.path .. "/Code/core/include/",
            premake.extensions.core.path .. "/ThirdParty/mimalloc/include/",
        }

        files
        {
            premake.extensions.core.path .. "/Code/core/include/**.hpp",
            premake.extensions.core.path .. "/Code/core/src/**.cpp",
        }

        links
        {
            "mimalloc"
        }

    premake.extensions.core.core_generated = true
end

function mimalloc_generate()
    if premake.extensions.core.mimalloc_generated == true then
        return
    end

    project ("mimalloc")
        kind ("StaticLib")
        language ("C")

        includedirs
        {
            premake.extensions.core.path .. "/ThirdParty/mimalloc/include/",
        }

        files
        {
            premake.extensions.core.path .. "/ThirdParty/mimalloc/include/**.h",
            premake.extensions.core.path .. "/ThirdParty/mimalloc/src/alloc.c",
            premake.extensions.core.path .. "/ThirdParty/mimalloc/src/alloc-aligned.c",
            premake.extensions.core.path .. "/ThirdParty/mimalloc/src/heap.c",
            premake.extensions.core.path .. "/ThirdParty/mimalloc/src/init.c",
            premake.extensions.core.path .. "/ThirdParty/mimalloc/src/memory.c",
            premake.extensions.core.path .. "/ThirdParty/mimalloc/src/options.c",
            premake.extensions.core.path .. "/ThirdParty/mimalloc/src/os.c",
            premake.extensions.core.path .. "/ThirdParty/mimalloc/src/page.c",
            premake.extensions.core.path .. "/ThirdParty/mimalloc/src/segment.c",
            premake.extensions.core.path .. "/ThirdParty/mimalloc/src/static.c",
            premake.extensions.core.path .. "/ThirdParty/mimalloc/src/stats.c",
        }

    premake.extensions.core.mimalloc_generated = true
end

function core_generate_all()
    if premake.extensions.core.generated == true then
        return
    end

    mimalloc_generate()
    core_generate()

    premake.extensions.core.generated = true
end

premake.extensions.core.path = core_parent_path()
premake.extensions.core.generate = core_generate_all