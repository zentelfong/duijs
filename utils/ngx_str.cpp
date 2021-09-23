#include "ngx_str.h"

ngx_uint_t
ngx_escape_sql_str(u_char* dst, u_char* src, size_t size)
{
	if (dst == NULL) {
		/* find the number of chars to be escaped */
		size_t n = 0;
		size_t ns = size;
		while (size) {
			/* the highest bit of all the UTF-8 chars
			* is always 1 */
			if ((*src & 0x80) == 0) {
				switch (*src) {
				case '\'':
				//case '/':
				//case '[':
				//case ']':
				//case '%':
				//case '&':
				//case '_':
				//case '(':
				//case ')':
					n++;
					break;
				default:
					break;
				}
			}
			src++;
			size--;
		}

		return (ngx_uint_t)(n + ns);
	}

	u_char* sdst = dst;
	while (size) {
		if ((*src & 0x80) == 0) {
			switch (*src) {
			case '\'':
				*dst++ = '\'';
				*dst++ = '\'';
				break;

			//case '/':
			//	*dst++ = '/';
			//	*dst++ = '/';
			//	break;
			//case '[':
			//	*dst++ = '/';
			//	*dst++ = '[';
			//	break;

			//case ']':
			//	*dst++ = '/';
			//	*dst++ = ']';
			//	break;

			//case '%':
			//	*dst++ = '/';
			//	*dst++ = '%';
			//	break;

			//case '&':
			//	*dst++ = '/';
			//	*dst++ = '&';
			//	break;

			//case '_':
			//	*dst++ = '/';
			//	*dst++ = '_';
			//	break;
			//case '(':
			//	*dst++ = '/';
			//	*dst++ = '(';
			//	break;
			//case ')':
			//	*dst++ = '/';
			//	*dst++ = ')';
			//	break;
			default:
				*dst++ = *src;
				break;
			}
		}
		else {
			*dst++ = *src;
		}
		src++;
		size--;
	} /* while (size) */

	return (ngx_uint_t) (dst - sdst);
}


ngx_uint_t
ngx_escape_json(u_char* dst, u_char* src, size_t size)
{
	u_char      ch;
	size_t  len;

	if (dst == NULL) {
		len = 0;
		size_t ns = size;
		while (size) {
			ch = *src++;

			if (ch == '\\' || ch == '"') {
				len++;

			}
			else if (ch <= 0x1f) {

				switch (ch) {
				case '\n':
				case '\r':
				case '\t':
				case '\b':
				case '\f':
					len++;
					break;

				default:
					len += sizeof("\\u001F") - 2;
				}
			}

			size--;
		}

		return (ngx_uint_t)(len + ns);
	}

	u_char* sdst = dst;
	while (size) {
		ch = *src++;

		if (ch > 0x1f) {

			if (ch == '\\' || ch == '"') {
				*dst++ = '\\';
			}

			*dst++ = ch;

		}
		else {
			*dst++ = '\\';

			switch (ch) {
			case '\n':
				*dst++ = 'n';
				break;

			case '\r':
				*dst++ = 'r';
				break;

			case '\t':
				*dst++ = 't';
				break;

			case '\b':
				*dst++ = 'b';
				break;

			case '\f':
				*dst++ = 'f';
				break;

			default:
				*dst++ = 'u'; *dst++ = '0'; *dst++ = '0';
				*dst++ = '0' + (ch >> 4);

				ch &= 0xf;

				*dst++ = (ch < 10) ? ('0' + ch) : ('A' + ch - 10);
			}
		}

		size--;
	}

	return (ngx_uint_t)(dst - sdst);
}


u_char*
ngx_hex_dump(u_char* dst, u_char* src, size_t len)
{
	static u_char  hex[] = "0123456789abcdef";

	while (len--) {
		*dst++ = hex[*src >> 4];
		*dst++ = hex[*src++ & 0xf];
	}

	return dst;
}


static void
ngx_encode_base64_internal(ngx_str_t* dst, ngx_str_t* src, const u_char* basis,
	ngx_uint_t padding)
{
	u_char* d, * s;
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


void
ngx_encode_base64(ngx_str_t* dst, ngx_str_t* src)
{
	static u_char   basis64[] =
		"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

	ngx_encode_base64_internal(dst, src, basis64, 1);
}


void
ngx_encode_base64url(ngx_str_t* dst, ngx_str_t* src)
{
	static u_char   basis64[] =
		"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_";

	ngx_encode_base64_internal(dst, src, basis64, 0);
}

static ngx_int_t
ngx_decode_base64_internal(ngx_str_t* dst, ngx_str_t* src, const u_char* basis)
{
	size_t          len;
	u_char* d, * s;

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


ngx_int_t
ngx_decode_base64(ngx_str_t* dst, ngx_str_t* src)
{
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


ngx_int_t
ngx_decode_base64url(ngx_str_t* dst, ngx_str_t* src)
{
	static u_char   basis64[] = {
		77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77,
		77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77,
		77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 62, 77, 77,
		52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 77, 77, 77, 77, 77, 77,
		77,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14,
		15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 77, 77, 77, 77, 63,
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
