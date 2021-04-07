SRC=src
BIN=bin
LIBS = -lczmq -lzmq
DEPS = $(SRC)/zzz.h

CC=gcc
CFLAGS=-I$(SRC)/

PROGS = version hello server client wuserver wuclient \
		taskvent taskwork taskwork2 tasksink tasksink2 \
		rrclient rrworker rrbroker msgqueue \
		msreader mspoller test
TARGETS = $(addprefix $(BIN)/,$(PROGS))

all: $(TARGETS)

bin/%: $(SRC)/$(notdir %).c $(DEPS)
	$(CC) $< -o $@ $(LIBS)

.PHONY: clean
clean:
	rm $(TARGETS)
