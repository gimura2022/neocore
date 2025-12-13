/* Permission to use, copy, modify, and/or distribute this software for
 * any purpose with or without fee is hereby granted.

 * THE SOFTWARE IS PROVIDED “AS IS” AND THE AUTHOR DISCLAIMS ALL
 * WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE
 * FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY
 * DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN
 * AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT
 * OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE. */

/* err.c - error messanges displaying */

/* define posix version as POSIX.1-2008 */
#define _POSIX_C_SOURCE 200809L

#include <stddef.h>
#include <stdarg.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>

#include "err.h"

/* invocation name */
const char* __neocore_invocation_name = NULL;

/* format buffer size */
#define BUF_SIZE 1024

/* print invocation name and format messange */
void vwarnx(const char* fmt, va_list args)
{
	char buf[BUF_SIZE + 1] = {0};

	vsnprintf(buf, BUF_SIZE, fmt, args);
	fprintf(stderr, "%s: %s\n", __neocore_invocation_name, buf);
}

/* print invocation name, format messange, and errno */
void vwarn(const char* fmt, va_list args)
{
	char buf[BUF_SIZE + 1] = {0};

	vsnprintf(buf, BUF_SIZE, fmt, args);
	warnx("%s: %s", buf, strerror(errno));
}

/* print invocation name, format messange, and errno */
void warn(const char* fmt, ...)
{
	va_list args;

	va_start(args, fmt);
	vwarn(fmt, args);
	va_end(args);
}

/* print invocation name and format messange */
void warnx(const char* fmt, ...)
{
	va_list args;

	va_start(args, fmt);
	vwarnx(fmt, args);
	va_end(args);
}

/* print invocation name, format messange and exit with code */
void verrx(int code, const char* fmt, va_list args)
{
	vwarnx(fmt, args);
	exit(code);
}

/* print invocation name, format messange, errno and exit with code */
void verr(int code, const char* fmt, va_list args)
{
	warnx(fmt, args);
	exit(code);
}

/* print invocation name, format messange, errno and exit with code */
void err(int code, const char* fmt, ...)
{
	va_list args;

	va_start(args, fmt);
	verr(code, fmt, args);
	va_end(args);
}

/* print invocation name, format messange and exit with code */
void errx(int code, const char* fmt, ...)
{
	va_list args;

	va_start(args, fmt);
	verrx(code, fmt, args);
	va_end(args);
}
