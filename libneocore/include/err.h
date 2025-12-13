/* Permission to use, copy, modify, and/or distribute this software for
 * any purpose with or without fee is hereby granted.

 * THE SOFTWARE IS PROVIDED “AS IS” AND THE AUTHOR DISCLAIMS ALL
 * WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE
 * FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY
 * DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN
 * AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT
 * OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE. */

/* err.h - error messanges displaying */

#ifndef _err_h
#define _err_h

#include <stdarg.h>

/* invocation name */
extern const char* __neocore_invocation_name;

/* print invocation name, format messange, and errno */
void warn(const char* fmt, ...);

/* print invocation name and format messange */
void warnx(const char* fmt, ...);

/* print invocation name, format messange, and errno */
void vwarn(const char* fmt, va_list args);

/* print invocation name and format messange */
void vwarnx(const char* fmt, va_list args);

/* print invocation name, format messange, errno and exit with code */
void err(int code, const char* fmt, ...);

/* print invocation name, format messange and exit with code */
void errx(int code, const char* fmt, ...);

/* print invocation name, format messange, errno and exit with code */
void verr(int code, const char* fmt, va_list args);

/* print invocation name, format messange and exit with code */
void verrx(int code, const char* fmt, va_list args);

#endif
