#include <stdio.h>

void mostrarMenu() {
    printf("\n ******* Menú ******* \n");
    printf("1) Ciudad de México\n");
    printf("2) Londres\n");
    printf("3) París\n");
    printf("4) Roma\n");
    printf("5) Nueva York\n");
    printf("6) Salir\n");
    printf("************************** \n");
}

int obtenerOpcion() {
    int opcion;
    printf("Ingrese la opción: ");
    scanf("%d", &opcion);
    return opcion;
}

int main() {
    int costos[5][5] = {
        {0, 7, 9, 12, 10},
        {6, 0, 4, 8, 15},
        {8, 5, 0, 6, 14},
        {11, 9, 7, 0, 16},
        {9, 14, 13, 17, 0} 
    };

    int opcion;
    int salir = 0;

    while (!salir) {
        mostrarMenu();
        opcion = obtenerOpcion();

        switch (opcion) {
            case 1:
                printf("Ha seleccionado Ciudad de México.\n");
                break;
            case 2:
                printf("Ha seleccionado Londres.\n");
                break;
            case 3:
                printf("Ha seleccionado París.\n");
                break;
            case 4:
                printf("Ha seleccionado Roma.\n");
                break;
            case 5:
                printf("Ha seleccionado Nueva York.\n");
                break;
            case 6:
                printf("Gracias por usar el programa. ¡Hasta luego!\n");
                salir = 1;
                break;
            default:
                printf("Opción inválida. Por favor, seleccione una opción válida.\n");
                break;
        }

        if (!salir) {
            int destino;
            printf("Ingrese el destino: ");
            scanf("%d", &destino);

            int origenIdx = opcion - 1;
            int destinoIdx = destino - 1;

            if (origenIdx >= 0 && origenIdx < 5 && destinoIdx >= 0 && destinoIdx < 5) {
                printf("El costo del viaje desde %d hasta %d es: %d\n", opcion, destino, costos[origenIdx][destinoIdx]);
            } else {
                printf("Opción de ciudad no válida.\n");
            }
        }
    }

    return 0;
}
