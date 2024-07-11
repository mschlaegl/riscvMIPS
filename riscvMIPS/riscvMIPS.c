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

int main(int argc, char **argv)
{
	char *command = NULL;

	if (argc < 2) {
		printf("riscvMIPS V0.2 (C) 2024 Manfred Schlaegl <manfred.schlaegl@gmx.at>\n\n");
		printf("Usage example: %s <command> <args>\n", argv[0]);
		printf("\n");
		exit(0);
	}

	/* alloc arg buffer */
	size_t commandlen = 0;
	for (int i = 1; i < argc; i++) {
		commandlen += strlen(argv[i]) + 1; // str + space/\0
	}
	command = malloc(commandlen * sizeof(*command));

	/* copy arguments */
	char *cptr = command;
	for (int i = 1; i < argc; i++) {
		cptr = stpcpy(cptr, argv[i]);
		*cptr = ' '; // replace \0 with space
		cptr++;
	}
	*(--cptr) = '\0'; // replace last space with \0

	fprintf(stderr, "riscvMIPS(\"%s\")): begin \n", command);

	/* begin measurement */
	unsigned long long istart = get_instr_count();
	unsigned long long tstart = get_time_ms();

	/* execute */
	int ret = system(command);

	/* end measurement */
	unsigned long long tdiff = get_time_ms() - tstart;
	unsigned long long idiff = get_instr_count() - istart;

	/* print results */
	fprintf(stderr, "riscvMIPS(\"%s\")): end %.3f MIPS (#instr = %llu, time = %.3f)\n",
		command,
		(double)idiff / 1000.0 / tdiff,
		idiff, (double)tdiff / 1000.0);

	/* return code of command */
	return ret;
}
