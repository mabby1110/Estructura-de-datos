CC = gcc
CFLAGS = -Wall
DEBUG = -g

SOURCES = examen
 
all:
	$(CC) $(SOURCES).c $(CFLAGS) -o $(SOURCES).o
debug:
	$(CC) $(SOURCES).c $(CFLAGS) -o $(SOURCES).o
clean:
	rm -f $(SOURCES).o
fresh:
	make clean
	make all 
