/* Permission to use, copy, modify, and/or distribute this software for
 * any purpose with or without fee is hereby granted.

 * THE SOFTWARE IS PROVIDED “AS IS” AND THE AUTHOR DISCLAIMS ALL
 * WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE
 * FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY
 * DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN
 * AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT
 * OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE. */

/* uname.c - return system name */

/* define posix version as POSIX.1-2008 */
#define _POSIX_C_SOURCE 200809L

#include <stdbool.h>
#include <stdio.h>
#include <getopt.h>
#include <sys/utsname.h>

#include "err.h"

/* patch number */
#define PATCH "3"

/* formatting settings */
static bool sysname	= false;
static bool nodename	= false;
static bool release	= false;
static bool version	= false;
static bool machine	= false;

/* display system info */
static void display(void)
{
	struct utsname info;

	if (uname(&info) < 0)
		err(1, "uname");

	if (sysname)	printf("%s ", info.sysname);
	if (nodename)	printf("%s ", info.nodename);
	if (release)	printf("%s ", info.release);
	if (version)	printf("%s ", info.version);
	if (machine)	printf("%s ", info.machine);

	putc('\n', stdout);
}

/* usage text */
#define USAGE_SMALL	"usage: uname [OPTION]\n"
#define USAGE		"	-s	--kernel		display system name (set by default)\n"	\
			"	-n	--nodename		display node name\n"			\
			"	-r	--kernel-release	display release\n"			\
			"	-v	--kernel-version	display version\n"			\
			"	-m	--arch			display machine\n"			\
			"	-a	--all			display all\n"				\
			"		--help			print this message and exit\n"		\
			"		--version		print version and exit\n"		\
			"\n"										\
			"return system information\n"

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
		{ "kernel",		no_argument,	0,	's' },
		{ "nodename",		no_argument,	0,	'n' },
		{ "kernel-release",	no_argument,	0,	'r' },
		{ "kernel-version",	no_argument,	0,	'v' },
		{ "arch",		no_argument,	0,	'm' },
		{ "all",		no_argument,	0,	'a' },
		{ "help",		no_argument,	0,	'h' },
		{ "version",		no_argument,	0,	'V' },
		{ 0, 0, 0, 0 },
	};

	opterr = false;

	while ((c = getopt_long(argc, argv, "snrvma", options, &opt)) != -1) switch (c) {
	/* formatting flags */
	case 's': sysname = true; break;
	case 'n': nodename = true; break;
	case 'r': release = true; break;
	case 'v': version = true; break;
	case 'm': machine = true; break;

	/* --all */
	case 'a':
		sysname = true;
		nodename = true;
		release = true;
		version = true;
		machine = true;

		break;

	/* --version */
	case 'V':
		puts("neocore uname " NEOCORE_VERSION "+" PATCH);
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

	/* if other formatting options doesn't enabled enable system name */
	if (!nodename && !release && !version && !machine)
		sysname = true;

	display();

	return 0;
}
