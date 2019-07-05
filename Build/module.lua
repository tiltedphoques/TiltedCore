function CreateCoreProject(basePath)
    project ("Core")
        kind ("StaticLib")
        language ("C++")

        includedirs
        {
            basePath .. "/Code/core/include/",
        }

        files
        {
            basePath .. "/Code/core/include/**.h",
            basePath .. "/Code/core/src/**.cpp",
        }

        filter { "architecture:*86" }
            libdirs { "lib/x32" }
            targetdir ("lib/x32")

        filter { "architecture:*64" }
            libdirs { "lib/x64" }
            targetdir ("lib/x64")
            
        filter {}
end
