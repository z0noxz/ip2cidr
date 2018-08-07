# ztatus version
VERSION = 0.1.1

# paths
PREFIX = /usr/local
MANPREFIX = $(PREFIX)/share/man

# flags
CFLAGS = -Wall -O3 -pedantic
CPPFLAGS = -DVERSION=\"$(VERSION)\" -D_DEFAULT_SOURCE -D_XOPEN_SOURCE=600
STCFLAGS = $(CPPFLAGS) $(CFLAGS)
STLDFLAGS = $(LDFLAGS)

# compiler and linker
CC = gcc
