CC=gcc
CFLAGS=-Isrc/
LIBS = -lczmq -lzmq
DEPS = src/zhelpers.h

PROGS = hello client server version args wuserver wuclient
TARGETS = $(addprefix bin/,$(PROGS))

all: $(TARGETS)

bin/%: src/$(notdir %).c $(DEPS)
	$(CC) $< -o $@ $(LIBS)

.PHONY: clean
clean:
	rm $(TARGETS)
