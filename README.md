# riscvMIPS

(C) 2024 Manfred Schlaegl <manfred.schlaegl@gmx.at>

SPDX-License-Identifier: MIT

riscvMIPS is a compact tool to measure MIPS of console application.

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

## Usage
```
$ ./riscvMIPS --help
riscvMIPS V1 (C) 2024 Manfred Schlaegl <manfred.schlaegl@gmx.at>

Usage examples:
stdout:        $ <program to measure> | riscvMIPS
stdout+stderr: $ <program to measure> 2>&1 | riscvMIPS
```

### Example
TODO

### Format
TODO
