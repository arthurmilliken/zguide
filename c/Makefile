SRC=src
BIN=bin
LIBS = -lczmq -lzmq -lpthread
DEPS = $(SRC)/zzz.h

CC=gcc
CFLAGS=-I$(SRC)/ -DDEBUG

PROGS = version hello test \
		server client interrupt mtserver \
		wuserver wuclient wuproxy \
		taskvent taskwork taskwork2 tasksink tasksink2 \
		rrclient rrworker rrbroker msgqueue \
		msreader mspoller \
		lbclient lbserver lbproxy \
		mtrelay syncpub syncsub
TARGETS = $(addprefix $(BIN)/,$(PROGS))

all: $(TARGETS)

bin/%: $(SRC)/$(notdir %).c $(DEPS)
	$(CC) $< -o $@ $(CFLAGS) $(LIBS)

.PHONY: clean
clean:
	rm $(TARGETS)
