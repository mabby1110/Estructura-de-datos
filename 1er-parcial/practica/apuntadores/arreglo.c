#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 10

// recorrer arreglo con puntero

int main() {
    char arreglo[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char *pArreglo = NULL;
    pArreglo = &arreglo[strlen(arreglo)-1];

    printf("tamanio: %d %c\n", strlen(arreglo), *pArreglo);

    // Recorrer el arreglo utilizando el puntero
    while (&arreglo[0] <= pArreglo) {
        // printf("arreglo %p apuntador %p", arreglo, pArreglo);
        printf("\n%c", *pArreglo);
        pArreglo--;
        // getchar();
    }

    return 0;
}