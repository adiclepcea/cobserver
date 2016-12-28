IDIR=./include
SDIR=./src
TDIR=./test
OUTPUT=simpleObserver
TESTS=tests
CC=gcc
CFLAGS=-I$(IDIR) -lpthread -Wall -pedantic
SRC=$(SDIR)/*.c

.PHONY: build clean help test static

help:
	@echo "make build   - build the program"
	@echo "make clean   - clean the generated files"
	@echo "make help    - show this help message"

build:
	@$(CC) -o $(OUTPUT) $(SRC) $(CFLAGS)

static:
	@$(CC) -c $(SDIR)/observer.c -o $(OUTPUT).o $(CFLAGS)
	ar -cqv libcobserver.a *.o

test:
	#@echo "Building tests"
	#@$(CC) -o $(TESTS) $(TDIR)/*.c $(SDIR)/observer.c -I$(TDIR) $(CFLAGS)
	#@echo "Runing tests"
	#@./$(TESTS)

clean:
	@rm $(OUTPUT)
	@rm $(TESTS)
