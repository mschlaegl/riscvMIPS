# Copyright (C) 2021 Manfred Schlaegl <manfred.schlaegl@gmx.at>
#
# SPDX-License-Identifier: GPL-3.0-only

SUBDIRS=riscvMIPS riscvlineMIPS


.PHONY: all check style test clean distclean install

BINS := $(patsubst %,bin/%,$(SUBDIRS))

all: $(BINS)

bin/%:
		mkdir -p bin
		@(b=$(@:bin/%=%) && make -C $$b $$b && cp $$b/$$b bin)

check:
		@for d in $(SUBDIRS) ; do make -C $$d $@ ; done

style:
		@for d in $(SUBDIRS) ; do make -C $$d $@ ; done

test:
		@for d in $(SUBDIRS) ; do make -C $$d $@ ; done

clean:
		@for d in $(SUBDIRS) ; do make -C $$d $@ ; done
		- rm -rf bin

distclean:
		@for d in $(SUBDIRS) ; do make -C $$d $@ ; done

install:
		@for d in $(SUBDIRS) ; do make -C $$d $@ ; done
