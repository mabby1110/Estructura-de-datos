#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 10

// recorrer arreglo con puntero

int main() {
    char arreglo[] = "Esto es un arreglo";
    char *pArreglo = NULL;
    pArreglo = arreglo;

    printf("arreglo[0] %p\tapuntador %p\n\n", arreglo, pArreglo);

    // Recorrer el arreglo utilizando el puntero
    while (*pArreglo) {
        printf("%c\n", *pArreglo);
        pArreglo++;
    }

    return 0;
}