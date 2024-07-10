/*
 * Copyright (C) 2024 Manfred Schlaegl <manfred.schlaegl@gmx.at>
 *
 * SPDX-License-Identifier: MIT
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <sys/time.h>

unsigned long long get_milliseconds(unsigned long long tstart)
{
	struct timeval  tv;
	gettimeofday(&tv, NULL);
	return ((tv.tv_sec) * 1000 + (tv.tv_usec) / 1000) - tstart;
}

void print_timestamp(unsigned long long tstart)
{
	unsigned long long tdiff_ms = get_milliseconds(tstart);
	unsigned long long tdiff_s = tdiff_ms / 1000;
	tdiff_ms = tdiff_ms - (tdiff_s * 1000);
	printf("%7llu.%03llu : ", tdiff_s, tdiff_ms);
	fflush(stdout);
}

int main(int argc, char **argv)
{
	unsigned long long tstart;
	int c;
	bool last_newline;


	if (argc > 1) {
		printf("Linetime V1.3 (C) 2024 Manfred Schlaegl <manfred.schlaegl@gmx.at>\n\n");
		printf("Usage examples:\n");
		printf("stdout:        $ <program to measure> | %s\n", argv[0]);
		printf("stdout+stderr: $ <program to measure> 2>&1 | %s\n", argv[0]);
		printf("\n");
		exit(0);
	}

	tstart = get_milliseconds(0);
	last_newline = true;
	while (1) {
		c = getchar();
		if (c == EOF) {
			break;
		}

		if (last_newline) {
			/* print timestamp at first received character on a new line */
			print_timestamp(tstart);
			last_newline = false;
		}

		if (c == '\n') {
			last_newline = true;
		}
		putchar(c);
		fflush(stdout);
	}
	/* print final timestamp after execution is complete */
	print_timestamp(tstart);
	printf("\n");
}
