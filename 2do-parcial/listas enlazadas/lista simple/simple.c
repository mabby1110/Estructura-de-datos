#include <stdio.h>
#include <stdlib.h>

typedef struct Nodo {
    int dato;
    struct Nodo *sig;
} Nodo;

void append(int dato, Nodo *lista);
void printList(Nodo *lista);

// cola
void popFirst(Nodo **lista);

// pila
void popLast(Nodo *lista);

int main(){
    Nodo *lista = malloc(sizeof(Nodo));

    append(5, lista);
    append(6, lista);
    append(7, lista);
    append(8, lista);
    append(9, lista);

    popFirst(&lista);
    popFirst(&lista);

    popLast(lista);
    popLast(lista);

    // debe imprimir solo el 7 y el siguiente elemnto debe ser null
    printList(lista);
    return 0;
}

void append(int dato, Nodo *lista){
    if(!lista->dato){
        lista->dato = dato;
    } else {
        Nodo *aux = lista;
        Nodo *nuevo = malloc(sizeof(Nodo));

        while(aux->sig){
            aux = aux->sig;
        }

        aux->sig = nuevo;
        aux->sig->dato = dato;
    }
}

void printList(Nodo *lista){
    Nodo *aux = lista;

    while(aux){
        printf("nodo: %p\n", aux);
        printf("dato: %d\n", aux->dato);
        printf("siguiente: %p\n\n", aux->sig);
        aux = aux->sig;
    }
}

void popLast(Nodo *lista){
    Nodo *aux = lista;

    while(aux->sig->sig){
        aux = aux->sig;
    }
    
    free(aux->sig);
    aux->sig = NULL;

}

void popFirst(Nodo **lista) {
    if (*lista == NULL) {
        return; // La lista está vacía, no hay elementos para eliminar.
    }

    Nodo *aux = *lista;
    *lista = (*lista)->sig;
    free(aux);
}