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
	kind "ConsoleApp"
	includedirs{
		"./"
	}
	files{
		"quickjs/*.h",
		"quickjs/*.cpp",
		"binding/*.h",
		"binding/*.cpp",
		"utils/*.h",
		"utils/*.cpp",
		"test/*.h",
		"test/*.cpp",
	}
	
	libdirs{
		"quickjs/lib"
	}
	
	links{
		"quickjs",
		"duilib",
		"Gdiplus.lib",
	}

