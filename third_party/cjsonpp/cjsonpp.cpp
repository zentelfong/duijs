#include "cjsonpp.h"
#include <string.h>

namespace cjsonpp {

typedef unsigned char u_char;
typedef unsigned int ngx_uint_t;
typedef int ngx_int_t;

#define NGX_OK 0
#define NGX_ERROR (-1)
#define BASE64_ENCODE_OUT_SIZE(s)	(((s) + 2) / 3 * 4)
#define BASE64_DECODE_OUT_SIZE(s)	(((s)) / 4 * 3)


struct ngx_str_t {
	size_t len;
	u_char* data;
};

static void
ngx_encode_base64_internal(ngx_str_t *dst, ngx_str_t *src, const u_char *basis,
	ngx_uint_t padding) {
	u_char         *d, *s;
	size_t          len;

	len = src->len;
	s = src->data;
	d = dst->data;

	while (len > 2) {
		*d++ = basis[(s[0] >> 2) & 0x3f];
		*d++ = basis[((s[0] & 3) << 4) | (s[1] >> 4)];
		*d++ = basis[((s[1] & 0x0f) << 2) | (s[2] >> 6)];
		*d++ = basis[s[2] & 0x3f];

		s += 3;
		len -= 3;
	}

	if (len) {
		*d++ = basis[(s[0] >> 2) & 0x3f];

		if (len == 1) {
			*d++ = basis[(s[0] & 3) << 4];
			if (padding) {
				*d++ = '=';
			}

		}
		else {
			*d++ = basis[((s[0] & 3) << 4) | (s[1] >> 4)];
			*d++ = basis[(s[1] & 0x0f) << 2];
		}

		if (padding) {
			*d++ = '=';
		}
	}

	dst->len = d - dst->data;
}

static void ngx_encode_base64(ngx_str_t *dst, ngx_str_t *src) {
	static u_char   basis64[] =
		"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

	ngx_encode_base64_internal(dst, src, basis64, 1);
}


static ngx_int_t
ngx_decode_base64_internal(ngx_str_t *dst, ngx_str_t *src, const u_char *basis) {
	size_t          len;
	u_char         *d, *s;

	for (len = 0; len < src->len; len++) {
		if (src->data[len] == '=') {
			break;
		}

		if (basis[src->data[len]] == 77) {
			return NGX_ERROR;
		}
	}

	if (len % 4 == 1) {
		return NGX_ERROR;
	}

	s = src->data;
	d = dst->data;

	while (len > 3) {
		*d++ = (u_char)(basis[s[0]] << 2 | basis[s[1]] >> 4);
		*d++ = (u_char)(basis[s[1]] << 4 | basis[s[2]] >> 2);
		*d++ = (u_char)(basis[s[2]] << 6 | basis[s[3]]);

		s += 4;
		len -= 4;
	}

	if (len > 1) {
		*d++ = (u_char)(basis[s[0]] << 2 | basis[s[1]] >> 4);
	}

	if (len > 2) {
		*d++ = (u_char)(basis[s[1]] << 4 | basis[s[2]] >> 2);
	}

	dst->len = d - dst->data;

	return NGX_OK;
}


static ngx_int_t ngx_decode_base64(ngx_str_t *dst, ngx_str_t *src) {
	static u_char   basis64[] = {
		77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77,
		77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77,
		77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 62, 77, 77, 77, 63,
		52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 77, 77, 77, 77, 77, 77,
		77,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14,
		15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 77, 77, 77, 77, 77,
		77, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
		41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 77, 77, 77, 77, 77,

		77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77,
		77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77,
		77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77,
		77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77,
		77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77,
		77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77,
		77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77,
		77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77
	};

	return ngx_decode_base64_internal(dst, src, basis64);
}


Json::Json(const uint8_t* s, size_t len) {
	size_t enlen = BASE64_ENCODE_OUT_SIZE(len) + 1;
	ngx_str_t src, dest;

	src.data = (u_char*)s;
	src.len = len;

	dest.data = (uint8_t*)cJSON_malloc(enlen);
	dest.len = enlen;
	ngx_encode_base64(&dest,&src);
	dest.data[dest.len] = '\0';
	json_ = cJSON_CreateRawFrom((char*)dest.data);
}

template<> std::vector<uint8_t> Json::to() const {
	std::vector<uint8_t> data;
	if (type() == kString || type() == kRaw) {
		ngx_str_t src, dest;

		src.data =(u_char*)json_->valuestring;
		src.len = strlen(json_->valuestring);

		size_t buflen = BASE64_DECODE_OUT_SIZE(src.len);
		data.resize(buflen);

		dest.data = data.data();
		dest.len = buflen;
		if (ngx_decode_base64(&dest, &src) == NGX_OK) {
			data.resize(dest.len);
		}
	}
	return data;
}




}//namespace
