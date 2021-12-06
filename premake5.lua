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
		"third_party/quickjs/*.h",
		"third_party/quickjs/*.cpp",
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
		"libcurl.lib",
		"Gdiplus.lib",
	}

filter { "platforms:Win32" }
	libdirs{
		"third_party/quickjs/lib",
		"third_party/libcurl/lib"
	}

filter { "platforms:Win64" }
	libdirs{
		"third_party/quickjs/lib64",
		"third_party/libcurl/lib64"
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
	
