#include "util.h"
#include <unistd.h>
#include <time.h>
#include <ncurses.h>
#include <pthread.h>

#define WIDTH 40
#define HEIGHT 20

#define CABEZA  1
#define CUERPO  2
#define MANZANA 3

#define DERECHA     1
#define ARRIBA      2
#define IZQUIERDA   3
#define ABAJO       4

typedef struct {
    int x, y, tipo;
} Nodo;

typedef struct Culebra{
    Nodo nodo;
    int dir;
    struct Culebra *ant, *sig;
} Culebra;

void setup(Culebra *culebra, Nodo *fruta);
void draw(Culebra *culebra, Nodo *fruta);
void grow(Culebra *culebra, Nodo *fruta);
void* gameLogic(void* arg);
void* userInput(void* arg);

Culebra culebra;
Nodo fruta;
int run = 1;

int main(){
    pthread_t gameLogicThread, userInputThread;

    // Crear los hilos
    pthread_create(&gameLogicThread, NULL, gameLogic, NULL);
    pthread_create(&userInputThread, NULL, userInput, NULL);

    // Esperar a que los hilos terminen
    pthread_join(gameLogicThread, NULL);
    pthread_join(userInputThread, NULL);

    

    return 0;
}

void* gameLogic(void* arg) {
    setup(&culebra, &fruta);

    while(run){
        draw(&culebra, &fruta);
        
        switch(culebra.dir){
            case DERECHA:
                culebra.nodo.x++;
                break;
            case ARRIBA:
                culebra.nodo.y--;
                break; 
            case IZQUIERDA:
                culebra.nodo.x--;
                break;
            case ABAJO:
                culebra.nodo.y++;
                break;
        }
        system("sleep 0.1");
    }
    return NULL;
}

void* userInput(void* arg) {
    system("stty -echo"); // supress echo
    system("stty cbreak"); // go to RAW mode

    while (run) {
        // cambio de direccion
        char tecla = getch();

        switch(tecla){
            case 'd':
                culebra.dir = DERECHA;
                break;
            case 'w':
                culebra.dir = ARRIBA;
                break; 
            case 'a':
                culebra.dir = IZQUIERDA;
                break;
            case 's':
                culebra.dir = ABAJO;
                break;
            case 'q':
                run = 0;
        }
    }
    system ("stty echo"); // Make echo work
    system("stty -cbreak");// go to COOKED mode

    return NULL;
}

void setup(Culebra *culebra, Nodo *fruta){
    initscr();
    cbreak();
    noecho();
    curs_set(0);

    srand(time(NULL));

    culebra->nodo.x = WIDTH / 2;
    culebra->nodo.y = HEIGHT / 2;
    culebra->nodo.tipo = CABEZA;
    culebra->dir = DERECHA;
    culebra->sig = NULL;
    culebra->ant = NULL;

    fruta->x = rand() % WIDTH;
    fruta->y = rand() % HEIGHT;
    fruta->tipo = MANZANA;
}

void draw(Culebra *culebra, Nodo *fruta){
    Culebra *aux = malloc(sizeof(struct Culebra));
    aux = culebra;
    clear();

    // bordes
    for (int i = 0; i < WIDTH + 2; i++)
        mvprintw(0, i, "-");
    for (int i = 0; i < HEIGHT + 2; i++)
        mvprintw(i, 0, "|");
    for (int i = 0; i < HEIGHT + 2; i++)
        mvprintw(i, WIDTH + 1, "|");
    for (int i = 0; i < WIDTH + 2; i++)
        mvprintw(HEIGHT + 1, i, "-");

    // tablero
    mvprintw(HEIGHT + 3, 2, "direccion: %i", culebra->dir);

    // fruta
    mvprintw(fruta->y, fruta->x, "*");

    // culebra
    while(aux){
        mvprintw(aux->nodo.y, aux->nodo.x, "@");
        aux = aux->ant;
    }

    refresh();
}

void grow(Culebra *culebra, Nodo *fruta){
    Culebra *nuevo = malloc(sizeof(struct Culebra));
    fruta->tipo = CUERPO;
    nuevo->nodo = *fruta;
    nuevo->ant = NULL;

    while(culebra->ant)
        culebra = culebra->ant;
    
    nuevo->sig = culebra;
    culebra->ant = nuevo;
}