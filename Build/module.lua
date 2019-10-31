premake.extensions.core = {}

function core_parent_path()
    local str = debug.getinfo(2, "S").source:sub(2)
    local dir =  str:match("(.*/)"):sub(0,-2)
    local index = string.find(dir, "/[^/]*$")
    return dir:sub(0, index)
end

function core_generate()
    if premake.extensions.core.generated == true then
        return
    end

    project ("Core")
        kind ("StaticLib")
        language ("C++")

        includedirs
        {
            premake.extensions.core.path .. "/Code/core/include/",
        }

        files
        {
            premake.extensions.core.path .. "/Code/core/include/**.hpp",
            premake.extensions.core.path .. "/Code/core/src/**.cpp",
        }

    premake.extensions.core.generated = true
end

premake.extensions.core.path = core_parent_path()
premake.extensions.core.generate = core_generate