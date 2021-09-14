solution "duijs"
	location ( "build" )
	configurations { "Debug", "Release" }
	defines { 
		"_WIN32","WIN32",
		"_CRT_SECURE_NO_WARNINGS",
		"UILIB_STATIC",
	}

filter "configurations:Debug"
	defines { "DEBUG" , "_DEBUG" }
	optimize "Debug"
	
filter "configurations:Release"
	defines { "NDEBUG" }
	optimize "Speed"
	vectorextensions "SSE2"	

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
	
	libdirs{
		"quickjs/lib",
		"third_party/libcurl",
	}
	
	links{
		"quickjs",
		"duilib",
		"sqlite3",
		"cjsonpp",
		"libcurl.lib",
		"Gdiplus.lib",
	}

