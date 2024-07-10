# Linetime

(C) 2024 Manfred Schlaegl <manfred.schlaegl@gmx.at>

SPDX-License-Identifier: MIT

Linetime is a compact tool to measure timing of console application.
For each line (first character on a new line), a timestamp in the format
seconds.milliseconds is printed before the line content.

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
$ ./linetime --help
Linetime V1 (C) 2024 Manfred Schlaegl <manfred.schlaegl@gmx.at>

Usage examples:
stdout:        $ <program to measure> | linetime
stdout+stderr: $ <program to measure> 2>&1 | linetime
```

### Example
```
$ (echo; sleep 0.3; echo "hello"; sleep 1; echo "world"; sleep 1.2; echo "!"; sleep 0.1) | ./linetime
      0.000 : 
      0.301 : hello
      1.301 : world
      2.502 : !
      2.603 : 
```

### Format
```
      1.305 : world
-Timestamp--: -Original output--------------------------------------
```
Timestamp
 * Timestamp of first character in output line (above example 'w') relative to program start
 * Format: seconds.milliseconds (above example: 1 second and 305 millisecons)

