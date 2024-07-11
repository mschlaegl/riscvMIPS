/*
 * Copyright (C) 2024 Manfred Schlaegl <manfred.schlaegl@gmx.at>
 *
 * SPDX-License-Identifier: MIT
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <float.h>

unsigned long long get_time_ms()
{
	struct timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	return (ts.tv_sec * 1000L + (ts.tv_nsec / 1000000L));
}

unsigned long long get_instr_count()
{
#ifdef __riscv
#if __riscv_xlen == 32
	/* RV32 */
	uint32_t tmp, minstreth, minstret;
	asm volatile ("csrr %0, instreth" : "=r" (tmp));
	do {
		minstreth = tmp;
		asm volatile ("csrr %0, instret" : "=r" (minstret));

		/* re-read on overrun of instret */
		asm volatile ("csrr %0, instreth" : "=r" (tmp));
	} while (tmp != minstreth);
	return (uint64_t)minstreth << 32 | minstret;

#elif __riscv_xlen == 64
	/* RV64 */
	uint64_t minstret;
	asm volatile ("csrr %0, instret" : "=r" (minstret));
	return minstret;

#else /* __riscv_xlen */
	/* not supported yet */
	return 0;
#endif

#else /* __riscv */
	/* not supported yet */
	return 0;
#endif
}

static unsigned long long istart, tstart, ilast, tlast;
static double mips_cur, mips_avg, mips_min, mips_max;

void MIPS_start()
{
	mips_min = DBL_MAX;
	tstart = get_time_ms();
	istart = get_instr_count();
	tlast = tstart;
	ilast = istart;
}

void MIPS_print()
{
	unsigned long long icur = get_instr_count();
	unsigned long long tcur = get_time_ms();

	unsigned long long tdiff_abs = tcur - tstart;
	unsigned long long idiff_abs = icur - istart;
	mips_avg = (double)idiff_abs / 1000.0 / tdiff_abs;

	unsigned long long tdiff_rel = tcur - tlast;
	unsigned long long idiff_rel = icur - ilast;
	mips_cur = (double)idiff_rel / 1000.0 / tdiff_rel;
	if (mips_cur > mips_max) {
		mips_max = mips_cur;
	}
	if (mips_cur < mips_min) {
		mips_min = mips_cur;
	}

#if 0
	printf("\nMIPS(abstime/reltime;cur/avg/min/max): %.3f/%.3f;%.2f/%.2f/%.2f/%.2f",
	       tdiff_abs / 1000.0, tdiff_rel / 1000.0,
	       mips_cur, mips_avg, mips_min, mips_max);
#endif
	printf("\nMIPS: abstime = %.3f; reltime = %.3f; mips_cur = %.3f; mips_avg = %.3f; mips_min = %.3f; mips_max = %.3f",
	       tdiff_abs / 1000.0, tdiff_rel / 1000.0,
	       mips_cur, mips_avg, mips_min, mips_max);
	fflush(stdout);

	tlast = tcur;
	ilast = icur;
}

int main(int argc, char **argv)
{
	int c;

	if (argc > 1) {
		printf("riscvlineMIPS V0.2 (C) 2024 Manfred Schlaegl <manfred.schlaegl@gmx.at>\n\n");
		printf("Usage examples:\n");
		printf("stdout:        $ <program to measure> | %s\n", argv[0]);
		printf("stdout+stderr: $ <program to measure> 2>&1 | %s\n", argv[0]);
		printf("\n");
		exit(0);
	}

	MIPS_start();
	while (1) {
		c = getchar();
		if (c == EOF) {
			printf("stop\n");
			break;
		} else if (c == '\n') {
			MIPS_print();
		}
		putchar(c);
		fflush(stdout);
	}
	MIPS_print();
	printf("\n");
}
