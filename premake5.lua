include("build/conanbuildinfo.premake")

workspace "nyetflix"
    architecture "x64"
    configurations {"Debug", "Release"}

    conan_basic_setup()

    language "C++"
    cppdialect "C++20"

    filter "configurations:Debug"
        -- Add preprocessor definition DEBUG to compiler
        defines {"DEBUG"}
        -- Enable debugging symbols
        symbols "On"
    
    filter "configurations:Release"
        defines {"RELEASE"}
        -- Turn on dat optimization
        optimize "On"

    filter "system:windows"
        defines {"WINDOWS"}


project "nyetflix"
    location "src"
    kind "ConsoleApp"

    targetdir ("bin/%{prj.name}")
    objdir ("bin-int/%{prj.name}")

    linkoptions { conan_exelinkflags }

    files
    {
        "src/**.h",
        "src/**.cpp",
    }
