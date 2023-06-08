#include <stdio.h>
#include <string.h>
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
    Carta *carta_mesa;
    Carta baraja[52];
} Mesa;

// juego
void inicializarJugadores(Mesa* mesa, Jugador* jugador1, Jugador* jugador2) {
    // Inicializar el generador de números aleatorios
    srand(time(NULL));
    
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
    
    // Asignar un ID a cada jugador
    jugador1->id = 1;
    jugador2->id = 2;

    // Asignar cartas a la mano de cada jugador
    for (int i = 0; i < 5; ++i) {
        jugador1->mano[i] = baraja[i];
        jugador2->mano[i] = baraja[i + 5];
    }

    // incializar mesa
    memcpy(mesa->baraja, baraja, sizeof(baraja));
    mesa->carta_mesa = &baraja[10];
}

void menu(Mesa* mesa, Jugador* jugador){
    printf("turno jugador %d\n", jugador->id);
    printf("carta en la mesa -> %d de %s\n\n", mesa->carta_mesa->num, mesa->carta_mesa->palo);
}

// acciones jugador
int input(){
    int opc;
    printf("\n- - seleccione una opcion - -\n");
    scanf("%d", &opc);

    return opc;
}

void ver_cartas(Jugador* jugador){
    printf("-----tus cartas-----");
    for(int i=0; i<6; i++){
        printf("\n[%d] %d\t%s", i+1, jugador->mano[i].num, jugador->mano[i].palo);
    }
    printf("\n--------------------\n");
}

void tomar_carta(Mesa* mesa, Jugador* jugador){
    jugador->mano[5] = *mesa->carta_mesa;
}

int main() {
    system("clear");
    Jugador jugadores[2];
    Mesa mesa;
    int opc;
    int turno_jugador = 1;

    // Inicializar jugadores
    // se crea mazo, se revuelve maso, se reparten cartas, se 1 destapa
    inicializarJugadores(&mesa, &jugadores[0], &jugadores[1]);

    while(turno_jugador){
        // jugador[turno_jugador-1]
        // mostrar la mesa, pares jugados, 1 carta destapada
        menu(&mesa, &jugadores[turno_jugador-1]);
        ver_cartas(&jugadores[turno_jugador-1]);

        printf("\nopciones");
        printf("\n1) jugar carta en la mesa");
        printf("\n2) jugar siguiente carta");

        opc = input();
        // opciones
        switch(opc){
            case 1:
                // tomar_carta(&mesa, &jugadores[turno_jugador-1]);
                // elegir par
                // pagar
                break;
            case 2:
                // mostrar siguiente carta
                // tomar carta
                // elegir par
                // pagar
                break;
            default:
                printf("seleccione una opcion valida");
                break;
        }
        system("clear");
    }

    return 0;
}

