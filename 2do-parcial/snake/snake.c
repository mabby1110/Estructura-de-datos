#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <ncurses.h>

#define WIDTH 40
#define HEIGHT 20

typedef struct {
    int x, y;
} Point;

typedef struct {
    Point position;
    int length;
    int direction;
    Point body[100];
} Snake;

typedef struct {
    Point position;
    int eaten;
} Fruit;

void setup();
void draw();
void input();
void logic();
void game_over();

int game_running = 1;
int score = 0;
Snake snake;
Fruit fruit;

int main() {
    setup();

    while (game_running) {
        draw();
        input();
        logic();
        usleep(100000);
    }

    game_over();
    return 0;
}

void setup() {
    initscr();
    noecho();
    curs_set(0);

    srand(time(NULL));

    snake.position.x = WIDTH / 2;
    snake.position.y = HEIGHT / 2;
    snake.length = 1;
    snake.direction = KEY_RIGHT;

    fruit.position.x = rand() % WIDTH;
    fruit.position.y = rand() % HEIGHT;
    fruit.eaten = 0;
}

void draw() {
    clear();

    for (int i = 0; i < WIDTH + 2; i++)
        mvprintw(0, i, "#");
    for (int i = 0; i < HEIGHT + 2; i++)
        mvprintw(i, 0, "#");
    for (int i = 0; i < HEIGHT + 2; i++)
        mvprintw(i, WIDTH + 1, "#");
    for (int i = 0; i < WIDTH + 2; i++)
        mvprintw(HEIGHT + 1, i, "#");

    mvprintw(fruit.position.y + 1, fruit.position.x + 1, "*");

    for (int i = 0; i < snake.length; i++)
        mvprintw(snake.body[i].y + 1, snake.body[i].x + 1, "O");

    mvprintw(HEIGHT + 3, 2, "Score: %d", score);

    refresh();
}

void input() {
    int key = getch();

    switch (key) {
        case KEY_UP:
            if (snake.direction != KEY_DOWN)
                snake.direction = KEY_UP;
            break;
        case KEY_DOWN:
            if (snake.direction != KEY_UP)
                snake.direction = KEY_DOWN;
            break;
        case KEY_LEFT:
            if (snake.direction != KEY_RIGHT)
                snake.direction = KEY_LEFT;
            break;
        case KEY_RIGHT:
            if (snake.direction != KEY_LEFT)
                snake.direction = KEY_RIGHT;
            break;
        case 'q':
            game_running = 0;
            break;
    }
}

void logic() {
    Point prev = snake.position;

    switch (snake.direction) {
        case KEY_UP:
            snake.position.y--;
            break;
        case KEY_DOWN:
            snake.position.y++;
            break;
        case KEY_LEFT:
            snake.position.x--;
            break;
        case KEY_RIGHT:
            snake.position.x++;
            break;
    }

    if (snake.position.x <= 0 || snake.position.x >= WIDTH + 1 ||
        snake.position.y <= 0 || snake.position.y >= HEIGHT + 1)
    {
        game_running = 0;
        return;
    }

    for (int i = 0; i < snake.length; i++) {
        if (snake.position.x == snake.body[i].x &&
            snake.position.y == snake.body[i].y)
        {
            game_running = 0;
            return;
        }
    }

    if (snake.position.x == fruit.position.x &&
        snake.position.y == fruit.position.y)
    {
        score++;
        snake.length++;
        fruit.position.x = rand() % WIDTH;
        fruit.position.y = rand() % HEIGHT;
    }

    Point temp;
    Point prev2 = prev;

    for (int i = 0; i < snake.length; i++) {
        temp = snake.body[i];
        snake.body[i] = prev2;
        prev2 = temp;
    }
}

void game_over() {
    clear();
    mvprintw(HEIGHT / 2, WIDTH / 2 - 4, "Game Over!");
    mvprintw(HEIGHT / 2 + 1, WIDTH / 2 - 4, "Score: %d", score);
    refresh();
    sleep(2);
    endwin();
}
