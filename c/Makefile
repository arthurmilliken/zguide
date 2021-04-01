SRC=src
BIN=bin
LIBS = -lczmq -lzmq
DEPS = $(SRC)/zzz.h

CC=gcc
CFLAGS=-I$(SRC)/

PROGS = version hello server client wuserver wuclient \
		taskvent taskwork tasksink msreader mspoller \
		rrclient rrworker rrbroker msgqueue test
TARGETS = $(addprefix $(BIN)/,$(PROGS))

all: $(TARGETS)

bin/%: $(SRC)/$(notdir %).c $(DEPS)
	$(CC) $< -o $@ $(LIBS)

.PHONY: clean
clean:
	rm $(TARGETS)
