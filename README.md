# riscvMIPS

(C) 2024 Manfred Schlaegl <manfred.schlaegl@gmx.at>

SPDX-License-Identifier: MIT

riscvMIPS provides compact tools to measure MIPS of console application.

CAUTION: Does currently only provide valid results on single core machines!

WORK IN PROGRESS

## Build

### Build and install in ```/usr/local/bin```
```
make
sudo make install
```

### Build and install in custom directory ```<custom dir>```
Variable "INSTALL_BIN_DIR": Overrides default install directory
```
make
INSTALL_BIN_DIR=<custom dir> sudo make install
```

### Debug build
Variable: "debug"
 * debug=1 .. no optimization, debug symbols, unstripped install
 * debug=0 .. optimization, no debug symbols, stripped install

```
make clean
debug=1 make
```

## riscvlineMIPS

Print detailed MIPS statistics after every line the software under measurement prints on the console.

More detail, but greater impact on performance.

### Usage
```
riscvlineMIPS V0.2 (C) 2024 Manfred Schlaegl <manfred.schlaegl@gmx.at>

Usage examples:
stdout:        $ <program to measure> | riscvlineMIPS
stdout+stderr: $ <program to measure> 2>&1 | riscvlineMIPS
```

### Example Output
```
$ (sleep 0.3; echo "hello"; sleep 1; echo "world"; sleep 1.2; echo "!"; sleep 0.1) | riscvlineMIPS
hello
MIPS: abstime = 0.301; reltime = 0.301; mips_cur = 23.100; mips_avg = 23.100; mips_min = 23.100; mips_max = 23.100
world
MIPS: abstime = 1.303; reltime = 1.002; mips_cur = 22.000; mips_avg = 22.550; mips_min = 22.000; mips_max = 23.100
!
MIPS: abstime = 2.506; reltime = 1.203; mips_cur = 25.000; mips_avg = 23.367; mips_min = 22.000; mips_max = 25.000
stop

MIPS: abstime = 2.607; reltime = 0.101; mips_cur = 24.200; mips_avg = 23.575; mips_min = 22.000; mips_max = 25.000
```

## riscvMIPS
Print MIPS after execution of software under measurement is completed.

Less detail, but also less impact on performance.

### Usage
```
riscvMIPS V0.2 (C) 2024 Manfred Schlaegl <manfred.schlaegl@gmx.at>

Usage example: ./riscvMIPS <command> <args>
```

### Example Output
```
$ riscvMIPS "(sleep 0.3; echo "hello"; sleep 1; echo "world"; sleep 1.2; echo "!"; sleep 0.1)"
riscvMIPS("(sleep 0.3; echo hello; sleep 1; echo world; sleep 1.2; echo !; sleep 0.1)")): begin 
hello
world
!
riscvMIPS("(sleep 0.3; echo hello; sleep 1; echo world; sleep 1.2; echo !; sleep 0.1)")): end 23.921 MIPS (#instr = 62362047, time = 2.607)
```
