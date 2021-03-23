SRC=src
BIN=bin
LIBS = -lczmq -lzmq
DEPS = $(SRC)/zhelpers.h

CC=gcc
CFLAGS=-I$(SRC)/

PROGS = hello client server version args wuserver wuclient
TARGETS = $(addprefix $(BIN)/,$(PROGS))

all: $(TARGETS)

bin/%: $(SRC)/$(notdir %).c $(DEPS)
	$(CC) $< -o $@ $(LIBS)

.PHONY: clean
clean:
	rm $(TARGETS)
