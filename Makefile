# Copyright (C) 2021 Manfred Schlaegl <manfred.schlaegl@gmx.at>
#
# SPDX-License-Identifier: GPL-3.0-only

# version
BIN_NAME=linetime

debug?=0

ASTYLE_ARGS=--options=none --suffix=none --quiet \
	    --style=linux --indent=force-tab=8 --pad-header --pad-oper --indent-preprocessor
INSTALL_BIN_DIR ?= /usr/local/bin
INSTALL ?= install
STRIP ?= strip

# debug handling
ifeq ($(debug),1)
	# make debug=1
	# no optimization, with debug symbols install unstripped
	CFLAGS+=	-Og -g
	INSTALLFLAGS=
	OBJDIR=		.obj/debug
else
	CFLAGS+=	-O2
	INSTALLFLAGS=	-s --strip-program=$(STRIP)
	OBJDIR=		.obj/release
endif

CFLAGS+=\
		-Wall -D_GNU_SOURCE
LIBS+=
LDFLAGS+=

# All *.h files
HEADERS := $(wildcard *h)

# All *.c files
C_SOURCES := $(wildcard *.c)

# build %.o from %.c
OBJS := $(patsubst %.c,$(OBJDIR)/%.o,$(C_SOURCES))



.PHONY: all check style test clean distclean install create_obj_dir


all: $(BIN_NAME)

create_obj_dir:
		@for o in $(OBJS) ; do mkdir -p `dirname $${o}` ; done

# generic rule
$(OBJDIR)/%.o: %.c $(HEADERS) Makefile | create_obj_dir
		$(CC) $(CFLAGS) -c $< -o $@

$(BIN_NAME): $(OBJS) $(HEADERS) Makefile
		$(CC) $(OBJS) $(CFLAGS) $(LDFLAGS) $(LIBS) -o $@

check:
		cppcheck -q -f . ${C_SOURCES} ${HEADERS}

style:
		(PWD=`pwd`; astyle $(ASTYLE_ARGS) $(C_SOURCES) $(HEADERS);)

test: $(BIN_NAME)
		(echo; sleep 0.3; echo "hello"; sleep 1; echo "world"; sleep 1.2; echo "!"; sleep 0.1) | ./$(BIN_NAME)

clean:
		- rm -rf .obj
		- rm -f $(BIN_NAME)

distclean: clean

install: all
		-@mkdir -p $(INSTALL_BIN_DIR)
		$(INSTALL) -m 755 $(INSTALLFLAGS) $(BIN_NAME) $(INSTALL_BIN_DIR)
