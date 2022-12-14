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
	includedirs{
		"third_party"
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



project "duijs"
	language "C++"
	kind "WindowedApp"
	includedirs{
		"./",
	}
	files{
		"binding/*.h",
		"binding/*.cpp",
		"utils/*.h",
		"utils/*.cpp",
		"main/*.h",
		"main/*.cpp",
	}

	links{
		"async",
		"stbimage",
		"quickjs",
		"duilib",
		"sqlite3",
		"cjsonpp",
		"network",
		"libcurl",
		"Gdiplus.lib",
	}


project "test"
	language "C++"
	kind "ConsoleApp"
	includedirs{
	}
	files{
		"test/*.h",
		"test/*.cpp",
	}
	links{
		"gtest",
		"async",
		"stbimage",
		"quickjs",
		"duilib",
		"sqlite3",
		"cjsonpp",
		"network",
		"libcurl",
		"Gdiplus.lib",	
	}
	