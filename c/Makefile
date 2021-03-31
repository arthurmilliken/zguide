SRC=src
BIN=bin
LIBS = -lczmq -lzmq
DEPS = $(SRC)/zhelpers.h

CC=gcc
CFLAGS=-I$(SRC)/

PROGS = version hello server client wuserver wuclient \
		taskvent taskwork tasksink msreader mspoller test
TARGETS = $(addprefix $(BIN)/,$(PROGS))

all: $(TARGETS)

bin/%: $(SRC)/$(notdir %).c $(DEPS)
	$(CC) $< -o $@ $(LIBS)

.PHONY: clean
clean:
	rm $(TARGETS)
