/* Permission to use, copy, modify, and/or distribute this software for
 * any purpose with or without fee is hereby granted.

 * THE SOFTWARE IS PROVIDED “AS IS” AND THE AUTHOR DISCLAIMS ALL
 * WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE
 * FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY
 * DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN
 * AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT
 * OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE. */

/* wc.c - display bytes, words, lines and chars count */

/* define posix version as POSIX.1-2008 */
#define _POSIX_C_SOURCE 200809L

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <getopt.h>
#include <sys/stat.h>

#include "err.h"

/* patch number */
#define PATCH "0"

/* check file is directory */
static bool is_dir(const char* path)
{
	struct stat statbuf;

	if (stat(path, &statbuf) != 0)
		return false;

	return S_ISDIR(statbuf.st_mode);
}

/* check is specified path is stdin */
static bool is_stdin(const char* path)
{
	if (path == NULL)
		return true;

	if (!strcmp(path, "-"))
		return true;

	return false;
}

/* formatting flags */
static bool display_bytes = false;
static bool display_lines = false;
static bool display_chars = false;
static bool display_words = false;

/* format lines, words, bytes and chars count for file */
static void print_stat(	size_t bytes,
			size_t lines,
			size_t chars,
			size_t words,
			const char* path)
{
	if (display_lines) printf("%zu ", lines);
	if (display_words) printf("%zu ", words);
	if (display_bytes) printf("%zu ", bytes);
	if (display_chars) printf("%zu ", chars);

	if (path == NULL) goto done;

	printf("%s", path);

done:
	putc('\n', stdout);
}

/* exit status */
static int exit_status = 0;

/* get stream by path */
static FILE* get_stream(const char* path)
{
	FILE* file;

	if (is_stdin(path))
		return stdin;

	if ((file = fopen(path, "r")) == NULL) {
		warn("%s", path);

		exit_status = 1;

		return NULL;
	}

	if (is_dir(path)) {
		warnx("%s: is a directory", path);
		fclose(file);

		exit_status = 1;

		return NULL;
	}

	return file;
}

/* read lines, words, bytes and chars count for file */
static void get_stat(	size_t* bytes,
		     	size_t* lines,
		     	size_t* chars,
		     	size_t* words,
		     	const char* path)
{
	bool word = false;
	FILE* file;
	char c;

	if ((file = get_stream(path)) == NULL)
		return;

	while (fread(&c, sizeof(char), 1, file) > 0) {
		if (isgraph(c)) {
			(*chars)++;

			if (!word) (*words)++;
			word = true;
		}

		if (c == '\n')	(*lines)++;
		if (isspace(c))	word = false;

		(*bytes)++;
	}

	fclose(file);
}

/* total sizes */
static size_t bytes_total = 0;
static size_t lines_total = 0;
static size_t chars_total = 0;
static size_t words_total = 0;

/* process file */
static void process(const char* path)
{
	size_t bytes = 0, lines = 0, chars = 0, words = 0;

	get_stat(&bytes, &lines, &chars, &words, path);

	bytes_total += bytes;
	lines_total += lines;
	chars_total += chars;
	words_total += words;

	print_stat(bytes, lines, chars, words, path);
}

/* usage text */
#define USAGE_SMALL	"usage: wc [OPTION]\n"
#define USAGE		"	-c	--bytes			display number of bytes\n"		\
			"	-l	--lines			display number of lines\n"		\
			"	-m	--chars			display number of charecters\n"		\
			"	-w	--words			display number of words\n"		\
			"		--help			print this message and exit\n"		\
			"		--version		print version and exit\n"		\
			"\n"										\
			"display number of words, lines, and bytes or charecters\n"

/* print usage */
static void usage(FILE* stream, bool small)
{
	fputs(small ? USAGE_SMALL : USAGE_SMALL USAGE, stream);
}

/* entry point */
int neocore_main(int argc, char* argv[])
{
	int c, opt = 0;

	static const struct option options[] = {
		{ "bytes",		no_argument,	0,	'c' },
		{ "lines",		no_argument,	0,	'l' },
		{ "chars",		no_argument,	0,	'm' },
		{ "words",		no_argument,	0,	'w' },
		{ "help",		no_argument,	0,	'h' },
		{ "version",		no_argument,	0,	'v' },
		{ 0, 0, 0, 0 },
	};

	opterr = false;

	while ((c = getopt_long(argc, argv, "clmw", options, &opt)) != -1) switch (c) {
	/* formatting flags */
	case 'c': display_bytes = true; break;
	case 'l': display_lines = true; break;
	case 'm': display_chars = true; break;
	case 'w': display_words = true; break;

	/* --version */
	case 'v':
		puts("neocore wc " NEOCORE_VERSION "+" PATCH);
		puts("written by gimura");

		return 0;

	/* --help */
	case 'h':
		usage(stdout, false);
		return 0;

	/* invalid argument */
	case '?':
		warnx("invalid argument");
		usage(stderr, true);

		return 1;
	}

	if (!display_bytes
			&& !display_lines
			&& !display_chars
			&& !display_words)
		display_lines = display_words = display_bytes = true;

	size_t arg = optind;

	do process(argv[arg]); while (++arg < argc);

	if (arg - optind > 1)
		print_stat(bytes_total, lines_total, chars_total, words_total, "total");

	return exit_status;
}
