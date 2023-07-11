#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 8

struct Node{
    char dato[2];
    struct Node *izq, *der;
};

void addNode(struct Node **nodo, char dato[2]);
void pre_order(struct Node *nodo);
void in_order(struct Node *nodo);
void post_order(struct Node *nodo);

int main(){
    struct Node *raiz;

    addNode(&raiz, "A");

    addNode(&(raiz->izq), "B");
    addNode(&(raiz->izq->izq), "D");
    addNode(&(raiz->izq->izq->izq), "G");
    addNode(&(raiz->izq->izq->izq->der), "K");

    addNode(&(raiz->der), "C");
    addNode(&(raiz->der->izq), "E");
    addNode(&(raiz->der->izq->izq), "H");
    addNode(&(raiz->der->izq->der), "I");

    addNode(&(raiz->der->der), "F");
    addNode(&(raiz->der->der->der), "J");

    printf("pre order\n");
    pre_order(raiz);

    printf("\n\nin order\n");
    in_order(raiz);

    printf("\n\npre order\n");
    post_order(raiz);

    return 0;
}

void pre_order(struct Node *raiz){
    printf("dato: %s\n", raiz->dato);

    if(raiz->izq){
        pre_order(raiz->izq);
    }
    
    if(raiz->der){
        pre_order(raiz->der);
    }
}

void in_order(struct Node *raiz){
    if(raiz->izq){
        in_order(raiz->izq);
    }

    printf("dato: %s\n", raiz->dato);

    if(raiz->der){
        in_order(raiz->der);
    }
}

void post_order(struct Node *raiz){
    if(raiz->izq){
        post_order(raiz->izq);
    }
    
    if(raiz->der){
        post_order(raiz->der);
    }

    printf("dato: %s\n", raiz->dato);
}

void addNode(struct Node **raiz, char dato[2]){
    *raiz = malloc(sizeof(struct Node));

    if (*raiz==NULL){
        perror("");
        exit(1);
    }

    strcpy((*raiz)->dato, dato);
}

