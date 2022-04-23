include("build/conanbuildinfo.premake")

workspace "nyetflix"
    architecture "x64"
    configurations {"Release", "Debug"}

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


    ---------------
    -- Main project
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
            "src/**.cc", -- protobuf stuff
        }

    ---------------
    -- All protocol buffers that we need to build
    project "protobufs"
        location "protobufs"
        kind "Utility"

        targetdir ("bin/%{prj.name}")
        objdir ("bin-int/%{prj.name}")

        files
        {
            "protobufs/**.proto"
        }

        buildmessage 'Compiling protobuf definitions'

        prebuildcommands
        {
            "protoc -I . --cpp_out=../src nyetflix.proto",
            'protoc -I . --grpc_out=../src --plugin=protoc-gen-grpc="C:/.conan/8b1347/1/bin/grpc_cpp_plugin.exe" nyetflix.proto'
        }