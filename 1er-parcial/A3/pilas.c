#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 10

typedef struct stack{
    char stacked[MAX_SIZE];
    char *li;
} Stack;

int main() {
    char arreglo[] = "alsdkjffgh";
    char *puntero = arreglo;  // Asignar el puntero al primer elemento del arreglo
    Stack pila;
    pila.li = pila.stacked;

    printf("%p", *pila.li);
    printf("%p", pila.stacked);

    // Recorrer el arreglo utilizando el puntero
    while (*puntero) {
        printf("%c\n", *puntero);
        puntero++;
    }

    return 0;
}