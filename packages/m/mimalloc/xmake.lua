add_repositories("my-repo .")

add_requires

package("mimalloc")

    set_homepage("https://github.com/microsoft/mimalloc")
    set_description("mimalloc (pronounced 'me-malloc') is a general purpose allocator with excellent performance characteristics.")

    set_urls("https://github.com/microsoft/mimalloc/archive/v$(version).zip")

    add_versions("1.6.7", "5a12aac020650876615a2ce3dd8adc8b208cdcee4d9e6bcfc33b3fbe307f0dbf")

    on_install(function (package)
        local configs = {}
        import("package.tools.cmake").install(package, configs)
    end)
