/* Permission to use, copy, modify, and/or distribute this software for
 * any purpose with or without fee is hereby granted.

 * THE SOFTWARE IS PROVIDED “AS IS” AND THE AUTHOR DISCLAIMS ALL
 * WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE
 * FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY
 * DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN
 * AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT
 * OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE. */

/* true.c - return true value */

/* define posix version as POSIX.1-2008 */
#define _POSIX_C_SOURCE 200809L

#include <stdbool.h>
#include <stdio.h>
#include <getopt.h>

/* patch number */
#define PATCH "1"

/* usage message */
#define USAGE	"usage: true [--help | --version] OPTION...\n"		\
		"	--help		print this message and exit\n"	\
		"	--version	print version and exit\n"	\
		"	OPTIONS		any other options\n"		\
		"\n"							\
		"return true value\n"

/* entry point */
int neocore_main(int argc, char* argv[])
{
	int c, opt = 0;

	static const struct option options[] = {
		{ "help",	no_argument,	0,	'h' },
		{ "version",	no_argument,	0,	'v' },
		{ 0, 0, 0, 0 },
	};

	opterr = false;

	while ((c = getopt_long(argc, argv, "", options, &opt)) != -1) switch (c) {
	case 'h':
		fputs(USAGE, stdout);

		return 0;

	case 'v':
		puts("neocore true " NEOCORE_VERSION "+" PATCH);
		puts("written by gimura");

		return 0;

	default: break;
	}

	/* just return 0 exit code */
	return 0;
}
