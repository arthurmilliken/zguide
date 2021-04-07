SRC=src
BIN=bin
LIBS = -lczmq -lzmq
DEPS = $(SRC)/zzz.h

CC=gcc
CFLAGS=-I$(SRC)/

PROGS = version hello test \
		server client \
		wuserver wuclient wuproxy \
		taskvent taskwork taskwork2 tasksink tasksink2 \
		rrclient rrworker rrbroker msgqueue \
		msreader mspoller 
TARGETS = $(addprefix $(BIN)/,$(PROGS))

all: $(TARGETS)

bin/%: $(SRC)/$(notdir %).c $(DEPS)
	$(CC) $< -o $@ $(LIBS)

.PHONY: clean
clean:
	rm $(TARGETS)
