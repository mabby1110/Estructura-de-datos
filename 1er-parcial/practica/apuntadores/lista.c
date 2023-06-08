#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 10

// recorrer arreglo con puntero

int main() {
    int lista[] = {0, 1, 2, 3, 4, 5, 6};
    int *pLista = NULL;
    pLista = lista;

    printf("lista[0] %p\tapuntador %p\n\n", lista, pLista);

    // Recorrer el lista utilizando el puntero
    while (*pLista != 6) {
        printf("%d\n", *pLista);
        pLista++;
    }

    return 0;
}