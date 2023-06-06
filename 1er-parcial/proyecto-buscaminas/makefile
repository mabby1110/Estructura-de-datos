CC = gcc
CFLAGS = -Wall
DEBUG = -g

SOURCES = busca-minas
 
all:
	$(CC) $(SOURCES).c $(CFLAGS) -o $(SOURCES)
debug:
	$(CC) $(SOURCES).c $(CFLAGS) -o $(SOURCES)
clean:
	rm -f $(SOURCES).o
fresh:
	make clean
	make all 
