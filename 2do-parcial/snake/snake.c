#include <stdlib.h>
#include <stdio.h>
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

void setup();
void draw();
void grow();
void endGame();
void* gameLogic(void* arg);
void* userInput(void* arg);

// variables globales
Culebra culebra;
Nodo fruta;
int run = 1, puntos = 1;

// juego
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
    setup();

    Culebra *aux = malloc(sizeof(struct Culebra));

    while(run){
        draw();

        // condicionales antes del movimiento
        if (culebra.nodo.x == fruta.x
            && culebra.nodo.y == fruta.y){
            puntos++;
            grow();
        }

        // actualizar cuerpo de la culebra
        aux = &culebra;
        while(aux->ant){
            aux = aux->ant;
        }

        while(aux->sig){
            // la culebra se muerde la cola
            if (culebra.nodo.x == aux->nodo.x
                && culebra.nodo.y == aux->nodo.y){
                    if(aux->sig->nodo.tipo != CABEZA){
                        endGame();
                    }
            }

            aux->nodo.x = aux->sig->nodo.x;
            aux->nodo.y = aux->sig->nodo.y;
            aux = aux->sig;
        }

        // movimiento
        switch(culebra.dir){
            case DERECHA:
                if(culebra.nodo.x >= WIDTH){
                    culebra.nodo.x = 1;
                } else{
                    culebra.nodo.x++;
                }
                break;
            case ARRIBA:
                if(culebra.nodo.y <= 0){
                    culebra.nodo.y = HEIGHT;
                } else{
                    culebra.nodo.y--;
                }
                break;
            case IZQUIERDA:
                if(culebra.nodo.x <= 0){
                    culebra.nodo.x = WIDTH;
                } else{
                    culebra.nodo.x--;
                }
                break;
            case ABAJO:
                if(culebra.nodo.y >= HEIGHT){
                    culebra.nodo.y = 1;
                } else{
                    culebra.nodo.y++;
                }
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
                if (culebra.dir != IZQUIERDA)
                    culebra.dir = DERECHA;
                break;
            case 'w':
                if (culebra.dir != ABAJO)
                    culebra.dir = ARRIBA;
                break; 
            case 'a':
                if (culebra.dir != DERECHA)
                    culebra.dir = IZQUIERDA;
                break;
            case 's':
                if (culebra.dir != ARRIBA)
                    culebra.dir = ABAJO;
                break;
            case 27:
                run = 0;
        }
    }
    system ("stty echo"); // Make echo work
    system("stty -cbreak");// go to COOKED mode

    return NULL;
}

void setup(){
    // cosas para ncurses
    initscr();
    cbreak();
    noecho();
    curs_set(0);

    // semilla aleatoria
    srand(time(NULL));

    // se asignan los valores iniciales a la cabeza
    culebra.nodo.x = WIDTH / 2;
    culebra.nodo.y = HEIGHT / 2;
    culebra.nodo.tipo = CABEZA;
    culebra.dir = DERECHA;
    culebra.sig = NULL;
    culebra.ant = NULL;

    // se asignan los valores para la fruta
    fruta.x = rand() % WIDTH + 1;
    fruta.y = rand() % HEIGHT + 1;
    fruta.tipo = MANZANA;
}

void draw(){
    Culebra *aux = malloc(sizeof(struct Culebra));
    aux = &culebra;
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
    mvprintw(HEIGHT + 3, 2, "direccion: %i", culebra.dir);
    mvprintw(HEIGHT + 4, 2, "puntos: %i", puntos);
    mvprintw(HEIGHT + 6, 2, "presione ESC para salir");

    // fruta
    mvprintw(fruta.y, fruta.x, "*");

    // culebra
    while(aux){
        mvprintw(aux->nodo.y, aux->nodo.x, "@");
        aux = aux->ant;
    }

    refresh();
}

void grow(){
        // crea un nuevo espacio en memoria y se enlaza al final
        Culebra *aux = &culebra;
        Culebra *nuevo = malloc(sizeof(Culebra));

        while(aux->ant){
            aux = aux->ant;
        }

        nuevo->nodo.tipo = CUERPO;

        nuevo->sig = aux;
        aux->ant = nuevo;

        fruta.x = rand() % WIDTH + 1;
        fruta.y = rand() % HEIGHT + 1;
}

void endGame(){
    run = 0;
    draw();
    mvprintw(HEIGHT / 2, WIDTH / 2, "HAS PERDIDO!!!");
    refresh();
}