
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
	
project "stbimage"
	language "C"
	kind "StaticLib"
	includedirs{
		"./"
	}
	files{
		"stbimage/*.h",
		"stbimage/*.c",
	}	
	
project "async"
	language "C++"
	kind "StaticLib"
	includedirs{
		"./"
	}
	files{
		"async/*.h",
		"async/*.cpp",
	}

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


project "gtest"
	language "C++"
	kind "StaticLib"
	files{
		"gtest/*.h",
		"gtest/*.cc",
	}
	
project "quickjs"
	language "C++"
	kind "StaticLib"
	defines{
		"CONFIG_BIGNUM"
	}
	includedirs{
		"quickjs/include",
	}
	files{
		"quickjs/include/*.h",
		"quickjs/src/*.c",
		"quickjs/*.h",
		"quickjs/*.cpp"
	}	
	
	
	
--include "libcef"