project "libcurl"
	language    "C"
	kind        "StaticLib"
	includedirs {
		"include", 
		"lib",
		"zlib/",
		"mbedtls/include"
	}
	defines{
		"BUILDING_LIBCURL", 
		"CURL_STATICLIB",
		"HTTP_ONLY",
		"CURL_HTTP_ONLY",
		"CURL_DISABLE_LDAP",
		"HAVE_ZLIB_H",
		"HAVE_LIBZ",
		"USE_MBEDTLS"
	}
	
	files {
		"include/**.h",
		"lib/**.h",
		"lib/**.c",
		"zlib/*.h",
		"zlib/*.c",
		"mbedtls/**.h",
		"mbedtls/**.c",
	}
