CC = gcc
CFLAGS = -Wall
DEBUG = -g

SRC1 = pilas
SRC2 = colas
 
all:
	$(CC) $(SRC1).c $(CFLAGS) -o $(SRC1)
	$(CC) $(SRC2).c $(CFLAGS) -o $(SRC2)
debug:
	$(CC) $(SRC1).c $(CFLAGS) -o $(SRC1)
	$(CC) $(SRC2).c $(CFLAGS) -o $(SRC2)
clean:
	rm -f $(SRC1).o
	rm -f $(SRC1).o
fresh:
	make clean
	make all 
