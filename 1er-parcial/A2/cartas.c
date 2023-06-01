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
} Jugador;

void inicializarJugadores(Jugador* jugador1, Jugador* jugador2) {
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
    snprintf(jugador1->mano[5].palo, sizeof(jugador1->mano[5].palo), "%s", "");
    snprintf(jugador2->mano[5].palo, sizeof(jugador2->mano[5].palo), "%s", "");
}


int main() {
    Jugador jugadores[2];
    
    // Inicializar jugadores
    inicializarJugadores(&jugadores[0], &jugadores[1]);
    
    // Imprimir la mano de cada jugador
    printf("Jugador %d:\n", jugadores[0].id);
    for (int i = 0; i < 6; ++i) {
        printf("Carta %d: %d %s\n", i+1, jugadores[0].mano[i].num, jugadores[0].mano[i].palo);
    }
    
    printf("\nJugador %d:\n", jugadores[1].id);
    for (int i = 0; i < 6; ++i) {
        printf("Carta %d: %d %s\n", i+1, jugadores[1].mano[i].num, jugadores[1].mano[i].palo);
    }
    
    return 0;
}
