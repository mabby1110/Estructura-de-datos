CC = gcc
CFLAGS = -Wall
DEBUG = -g

SOURCES = culebrita
 
all:
	$(CC) $(SOURCES).c $(CFLAGS) -o $(SOURCES).o -lncurses
debug:
	$(CC) $(SOURCES).c $(CFLAGS) -o $(SOURCES).o -lncurses
clean:
	rm -f $(SOURCES).o
fresh:
	make clean
	make all 
