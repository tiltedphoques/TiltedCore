#include <Filesystem.hpp>
#include <Platform.hpp>


#include <fstream>

#if TP_PLATFORM_WINDOWS
#include <windows.h>

EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#endif

namespace TiltedPhoques
{
    std::filesystem::path GetPath() noexcept
    {
        static std::once_flag bInitialized;
        static std::filesystem::path currentPath;

        std::call_once(bInitialized, []
        {
#if TP_PLATFORM_WINDOWS
            WCHAR dllPath[MAX_PATH] = { 0 };
            GetModuleFileNameW(nullptr, dllPath, std::size(dllPath));

            std::error_code ec;
            currentPath = std::filesystem::path(dllPath).parent_path();
#else
            currentPath = std::filesystem::current_path();
#endif
        });

        return currentPath;
    }

    String LoadFile(const std::filesystem::path& acPath) noexcept
    {
        std::ifstream file(acPath, std::ios::binary);
        file.seekg(0, std::ifstream::end);
        const size_t length = file.tellg();
        file.seekg(0, std::ifstream::beg);

        String content(length, '\0');
        file.read(content.data(), length);

        return content;
    }

    bool SaveFile(const std::filesystem::path& acPath, const String& acData) noexcept
    {
        std::ofstream out(acPath, std::ios::binary);
        if (!out.is_open())
            return false;

        out.write(acData.data(), acData.size());

        return true;
    }
}
