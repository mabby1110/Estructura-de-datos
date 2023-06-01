#include <stdio.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Carta {
    int num;
    char palo[15];
} Carta;

typedef struct Jugador {
    int id;
    Carta mano[6];
    Carta juego[3][2];
} Jugador;

typedef struct Mesa {
    Carta carta_mesa;
    Carta baraja[52];
    Carta *index;
} Mesa;

// juego
void inicializarJugadores(Mesa* mesa, Jugador* jugador1, Jugador* jugador2) {
    // Inicializar el generador de números aleatorios
    srand(time(NULL));
    
    // Asignar un ID a cada jugador
    jugador1->id = 1;
    jugador2->id = 2;
    
    // Crear una lista de 52 barajas
    Carta baraja[52];
    
    // Inicializar la lista de barajas
    int indice = 0;
    for (int palo = 0; palo < 4; ++palo) {
        for (int num = 1; num <= 13; ++num) {
            baraja[indice].num = num;
            
            switch (palo) {
                case 0:
                    snprintf(baraja[indice].palo, sizeof(baraja[indice].palo), "%s", "Picas");
                    break;
                case 1:
                    snprintf(baraja[indice].palo, sizeof(baraja[indice].palo), "%s", "Corazones");
                    break;
                case 2:
                    snprintf(baraja[indice].palo, sizeof(baraja[indice].palo), "%s", "Tréboles");
                    break;
                case 3:
                    snprintf(baraja[indice].palo, sizeof(baraja[indice].palo), "%s", "Diamantes");
                    break;
            }

            indice++;
        }
    }
    
    // Revolver la baraja
    for (int i = 51; i > 0; --i) {
        int j = rand() % (i + 1);
        
        // Intercambiar baraja[i] y baraja[j]
        Carta temp = baraja[i];
        baraja[i] = baraja[j];
        baraja[j] = temp;
    }
    
    // Asignar cartas a la mano de cada jugador
    for (int i = 0; i < 5; ++i) {
        jugador1->mano[i] = baraja[i];
        jugador2->mano[i] = baraja[i + 5];
    }
    
    // Dejar un espacio vacío para una carta extra
    jugador1->mano[5].num = 0;
    jugador2->mano[5].num = 0;

    // incializar mesa
    mesa->carta_mesa = baraja[10];
}

void menu(Jugador* jugador1, Jugador* jugador2){
    printf("\nmenu");
}

// acciones jugador
int input(){
    int opc;
    printf("- - seleccione una opcion - -\n");
    scanf("%d", &opc);

    return opc;
}

int main() {
    Jugador jugadores[2];
    Mesa mesa;
    int opc;
    
    // Inicializar jugadores
    inicializarJugadores(&mesa, &jugadores[0], &jugadores[1]);
    // menu(mesa, &jugadores[0], &jugadores[1]);

    while(1){
        // while(turno_jugaro) =1 =2 =0
            // jugador[turno_jugador-1]
            // mostrar la mesa, pares jugados, 1 carta destapada
            // opciones

            // 1) jugar carta mesa
                // es par, poner en la mesa
                // volver a opciones

            // 2) jugar baraja
                // es par, poner en la mesa
                // pasar

            
            // int es_par(Jugador* jugador) {
            //     *jugador->mano[0];
            // }

        opc = input();


    }

    return 0;
}
