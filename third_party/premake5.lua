
project "sqlite3"
	language "C"
	kind "StaticLib"
	files{
		"sqlite3/*.h",
		"sqlite3/*.c",
	}


project "cjsonpp"
	language "C++"
	kind "StaticLib"
	files{
		"cjsonpp/*.h",
		"cjsonpp/*.c",
		"cjsonpp/*.cpp",
	}
	
	
project "network"
	language "C++"
	kind "StaticLib"
	includedirs{
		"./libcurl/include",
	}
	files{
		"network/*.h",
		"network/*.cpp",
	}
	
	
include "libcef"