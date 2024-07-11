# Copyright (C) 2021 Manfred Schlaegl <manfred.schlaegl@gmx.at>
#
# SPDX-License-Identifier: GPL-3.0-only

BIN_NAME=riscvMIPS

include ../Makefile.common

test: $(BIN_NAME)
		./$(BIN_NAME) "(sleep 0.3; echo "hello"; sleep 1; echo "world"; sleep 1.2; echo "!"; sleep 0.1)"
