IDIR=./include
SDIR=./src
TDIR=./test
OUTPUT=simpleObserver
TESTS=tests
CC=gcc
CFLAGS=-I$(IDIR) -lpthread
SRC=$(SDIR)/*.c

.PHONY: build clean help test

help:
	@echo "make build   - build the program"
	@echo "make clean   - clean the generated files"
	@echo "make help    - show this help message"

build:
	@$(CC) -o $(OUTPUT) $(SRC) $(CFLAGS)

test:
	#@echo "Building tests"
	#@$(CC) -o $(TESTS) $(TDIR)/*.c $(SDIR)/observer.c -I$(TDIR) $(CFLAGS)
	#@echo "Runing tests"
	#@./$(TESTS)

clean:
	@rm $(OUTPUT)
	@rm $(TESTS)
