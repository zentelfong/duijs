solution "duijs"
	location ( "build" )
	configurations { "Debug", "Release" }
	platforms { "Win32", "Win64" }
	flags { "StaticRuntime" }
	defines { 
		"_WIN32","WIN32",
		"_CRT_SECURE_NO_WARNINGS",
		"UILIB_STATIC",
	}

filter { "platforms:Win32" }
    system "windows"
    architecture "x32"
	
filter { "platforms:Win64" }
    system "windows"
    architecture "x64"
	
filter "configurations:Debug"
	defines { "DEBUG" , "_DEBUG" }
	optimize "Debug"
	flags { "Symbols" }
	
filter "configurations:Release"
	defines { "NDEBUG" }
	optimize "Speed"
	flags { "OptimizeSpeed", "EnableSSE2"}

include "third_party"


project "duilib"
	language "C++"
	kind "StaticLib"
	includedirs{
		"duilib",
	}
	files{
		"duilib/**.h",
		"duilib/**.cpp",
	}

project "duijs"
	language "C++"
	kind "WindowedApp"
	includedirs{
		"./",
		"third_party"
	}
	files{
		"quickjs/*.h",
		"quickjs/*.cpp",
		"binding/*.h",
		"binding/*.cpp",
		"utils/*.h",
		"utils/*.cpp",
		"main/*.h",
		"main/*.cpp",
	}

	links{
		"async",
		"quickjs",
		"duilib",
		"sqlite3",
		"cjsonpp",
		"network",
		"libcurl.lib",
		"Gdiplus.lib",
	}

filter { "platforms:Win32" }
	libdirs{
		"quickjs/lib",
		"third_party/libcurl/lib"
	}

filter { "platforms:Win64" }
	libdirs{
		"quickjs/lib64",
		"third_party/libcurl/lib64"
	}


