#pragma once
#include <stdint.h>

typedef unsigned char u_char;
typedef unsigned int ngx_uint_t;
typedef int ngx_int_t;

#define NGX_OK 0
#define NGX_ERROR (-1)

struct ngx_str_t {
	size_t len;
	u_char* data;
};

#define ngx_cpymem(dst, src, n)   (((u_char *) memcpy(dst, src, n)) + (n))
#define ngx_copy                  ngx_cpymem


ngx_uint_t ngx_escape_sql_str(u_char* dst, u_char* src, size_t size);

ngx_uint_t ngx_escape_json(u_char* dst, u_char* src, size_t size);

u_char* ngx_hex_dump(u_char* dst, u_char* src, size_t len);

void ngx_encode_base64(ngx_str_t* dst, ngx_str_t* src);
void ngx_encode_base64url(ngx_str_t* dst, ngx_str_t* src);

ngx_int_t ngx_decode_base64(ngx_str_t* dst, ngx_str_t* src);
ngx_int_t ngx_decode_base64url(ngx_str_t* dst, ngx_str_t* src);


#define BASE64_ENCODE_OUT_SIZE(s)	(((s) + 2) / 3 * 4)
#define BASE64_DECODE_OUT_SIZE(s)	(((s)) / 4 * 3)


