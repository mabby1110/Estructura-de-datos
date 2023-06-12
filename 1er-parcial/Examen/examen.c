#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 10

// recorrer arreglo con puntero

int main() {
    char arreglo[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ\n";
    char *pArreglo = NULL;
    pArreglo = &arreglo[strlen(arreglo)-1];

    printf("arreglo: %s", arreglo);
    // Recorrer el arreglo utilizando el puntero
    while (&arreglo[0] <= pArreglo) {
        printf("\n%c", *pArreglo);
        pArreglo--;
    }

    return 0;
}
