.POSIX:

include config.mk

SRC = ip2cidr.c
OBJ = $(SRC:.c=.o)

all: options ip2cidr

options:
	@echo ip2cidr build options:
	@echo "CC      = $(CC)"

.c.o:
	$(CC) $(STCFLAGS) -c $<

ip2cidr.o: ip2cidr.h

$(OBJ): config.mk

ip2cidr: $(OBJ)
	$(CC) -g -o $@ $(OBJ) $(STLDFLAGS)

clean:
	rm -f ip2cidr $(OBJ)

install: ip2cidr
	mkdir -p /usr/local/bin
	cp -f ip2cidr /usr/local/bin
	chmod 755 /usr/local/bin/ip2cidr

uninstall:
	rm -f /usr/local/bin/ip2cidr

.PHONY: all options clean install uninstall
