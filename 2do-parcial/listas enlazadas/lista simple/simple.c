#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int num;
    struct Node *next;
} Node;

void *initList(){
    Node *newNode = malloc(sizeof(Node));

    newNode->num = NULL;
    newNode->next = NULL;
    return newNode;
}

void append(Node *lista, Node *newNode){
    Node *aux = lista;

    while(aux->next){
        aux = aux->next;
    }

    aux->next = newNode;
}

void printList(Node *lista){
    Node *aux = lista;

    while(aux){
        printf("nodo: %p\n", aux);
        printf("dato: %d\n", aux->num);
        printf("next: %p\n\n", aux->next);
        aux = aux->next;
    }
}

int main(){
    
    Node *newNode = malloc(sizeof(Node));
    Node *sol = initList();

    newNode->num = 15;
    newNode->next = NULL;


    printList(sol);
    append(sol, newNode);
    printList(sol);
    
    free(sol);
    free(newNode);
    return 0;
}