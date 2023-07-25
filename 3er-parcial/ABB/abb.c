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
    char input[50];

    gets(input);

    printf("dato\t%d\n", *input);
    // p++;
    // printf("dato\t%d\n", *p);
    // p++;
    // printf("dato\t%d\n", *p);
    // p++;

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

