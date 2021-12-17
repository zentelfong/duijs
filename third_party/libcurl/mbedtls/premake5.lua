project "mbedtls"
	kind "StaticLib"
	language "C"
	includedirs{"include/"}
	files{"include/mbedtls/*.h","src/*.c"}