CC=gcc
CFLAGS=-std=c1x -Wall `pkg-config --cflags opencv`
LDFLAGS= `pkg-config --libs opencv`

all:
	$(CC) $(CFLAGS) $(PWD)/src/main.c -o $(PWD)/bin/mm-sorter $(LDFLAGS)

clean:
	rm $(PWD)/bin/mm-sorter