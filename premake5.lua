include("build/conanbuildinfo.premake")

workspace "NyetFlix"
    architecture "x64"
    configurations {"Release", "Debug"}

    conan_basic_setup()

    language "C++"
    cppdialect "C++latest"

    warnings "Extra"

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
        defines
        {
            "WINDOWS",
            "_SILENCE_CXX17_ITERATOR_BASE_CLASS_DEPRECATION_WARNING",   -- Supress deprecation warning from GRPC lib
            "_WIN32_WINNT=0x0A00"                                       -- Set windows target to Windows 10
        }

        resoptions
        {
            "/permissive-"      -- force ISO standard conformance TODO: check that this works
        }

        
    ---------------
    -- Main project
    project "NyetFlix"
        location "NyetFlix"
        kind "ConsoleApp"

        targetdir ("bin/%{prj.name}")
        objdir ("bin-int/%{prj.name}")

        includedirs
        {
            "Protobufs"
        }

        linkoptions { conan_exelinkflags }

        files
        {
            "%{prj.name}/src/**.h",
            "%{prj.name}/src/**.cpp",
            "Protobufs/**.cc",
        }

        dependson
        {
            "Protobufs"
        }

    
    ---------------
    -- Client for testing RPC
    project "TestClient"
        location "TestClient"
        kind "ConsoleApp"

        targetdir ("bin/%{prj.name}")
        objdir ("bin-int/%{prj.name}")

        includedirs
        {
            "Protobufs"
        }

        linkoptions { conan_exelinkflags }

        files
        {
            "%{prj.name}/src/**.h",
            "%{prj.name}/src/**.cpp",
            "Protobufs/**.cc",
        }

        dependson
        {
            "Protobufs"
        }

    ---------------
    -- All protocol buffers that we need to build
    project "Protobufs"
        location "Protobufs"
        kind "Utility"

        targetdir ("bin/%{prj.name}")
        objdir ("bin-int/%{prj.name}")

        files
        {
            "%{prj.name}/**.proto",
        }

    filter "system:windows"
        prebuildcommands
        {
            "protoc -I . --cpp_out=. nyetflix.proto",
            'protoc -I . --grpc_out=. --plugin=protoc-gen-grpc="C:/.conan/8b1347/1/bin/grpc_cpp_plugin.exe" nyetflix.proto' -- TODO: fix hard coded path to grpc_cpp_plugin
        }
	
    filter "system:macosx"
        prebuildcommands
        {
            "protoc -I . --cpp_out=. nyetflix.proto",
            'protoc -I . --grpc_out=. --plugin=protoc-gen-grpc="%{conan_rootpath_grpc}/bin/grpc_cpp_plugin" nyetflix.proto'
        }
