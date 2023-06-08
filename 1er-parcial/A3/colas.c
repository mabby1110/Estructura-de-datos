#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

typedef struct {
    char usuario[20];
    char caracter;
    int apariciones;
} Trabajo;

typedef struct {
    Trabajo data[MAX_SIZE];
    int front;
    int rear;
    int size;
} Cola;

void inicializar(Cola* cola) {
    cola->front = 0;
    cola->rear = -1;
    cola->size = 0;
}

int estaVacia(Cola* cola) {
    return cola->size == 0;
}

int estaLlena(Cola* cola) {
    return cola->size == MAX_SIZE;
}

void insertar(Cola* cola, Trabajo trabajo) {
    if (estaLlena(cola)) {
        printf("Error: La cola está llena\n");
        exit(1);
    }

    cola->rear = (cola->rear + 1) % MAX_SIZE;
    cola->data[cola->rear] = trabajo;
    cola->size++;
}

Trabajo eliminar(Cola* cola) {
    if (estaVacia(cola)) {
        printf("Error: La cola está vacía\n");
        exit(1);
    }

    Trabajo trabajo = cola->data[cola->front];
    cola->front = (cola->front + 1) % MAX_SIZE;
    cola->size--;

    return trabajo;
}

void enviarAImpresion(Cola* cola) {
    Trabajo trabajo;

    printf("Ingrese el nombre de usuario: ");
    scanf("%s", trabajo.usuario);
    printf("Ingrese el carácter a imprimir: ");
    scanf(" %c", &(trabajo.caracter)); // El espacio antes de %c es para evitar el buffer de entrada
    printf("Ingrese el número de apariciones: ");
    scanf("%d", &(trabajo.apariciones));

    insertar(cola, trabajo);

    printf("El trabajo ha sido enviado a impresión.\n");
}

void imprimirTrabajos(Cola* cola) {
    if (estaVacia(cola)) {
        printf("No hay trabajos pendientes de impresión.\n");
        return;
    }

    while (!estaVacia(cola)) {
        Trabajo trabajo = eliminar(cola);

        printf("\"%s\"\n", trabajo.usuario);
        for (int i = 0; i < trabajo.apariciones; i++) {
            printf("%c", trabajo.caracter);
        }
        printf("\n");
    }
}

int main() {
    Cola cola;
    inicializar(&cola);

    int opcion;

    do {
        printf("----- Menú -----\n");
        printf("1. Enviar a impresión\n");
        printf("2. Imprimir todos los trabajos\n");
        printf("3. Salir\n");
        printf("Ingrese una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                enviarAImpresion(&cola);
                break;
            case 2:
                imprimirTrabajos(&cola);
                break;
            case 3:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opción inválida. Por favor, intente nuevamente.\n");
                break;
        }

        printf("\n");

    } while (opcion != 3);

    return 0;
}
