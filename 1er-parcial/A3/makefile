CC = gcc
CFLAGS = -Wall
DEBUG = -g

SRC1 = cola_impresion
SRC2 = verificador_pares
 
all:
	$(CC) $(SRC1).c $(CFLAGS) -o $(SRC1).o
	$(CC) $(SRC2).c $(CFLAGS) -o $(SRC2).o
debug:
	$(CC) $(SRC1).c $(CFLAGS) -o $(SRC1)
	$(CC) $(SRC2).c $(CFLAGS) -o $(SRC2)
clean:
	rm -f $(SRC1).o
	rm -f $(SRC1).o
fresh:
	make clean
	make all 
