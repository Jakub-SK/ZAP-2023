#define _DEFAULT_SOURCE
#define _POSIX_C_SOURCE 200201L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>
#include <time.h>
#include <unistd.h>

#define HERO "(*-*)u"
#define GFOOD "$"
#define BFOOD "c"

void draw_world();
void move_hero(int direction, int *heroStartX, int heroStartY, struct timespec *heroDelay);
void move_food(int gfoodX[], int gfoodY[], int bfoodX[], int bfoodY[], int startY, int startX, int *fallCounter, struct timespec *foodDelay, int *stopGame);
int detect_collision(int heroStartX, int heroStartY, int gfoodX[], int gfoodY[], int bfoodX[], int bfoodY[]);
void display_congratulations(int counter);

int main() {
    srand(time(NULL));

    initscr();
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_CYAN, COLOR_BLACK); 
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(FALSE);
    nodelay(stdscr, TRUE);

    draw_world();

    int startY = (LINES - 25) / 2;
    int startX = (COLS - 38) / 2;
    int heroStartX = (COLS - strlen(HERO)) / 2;
    int heroStartY = startY + 23;

    int gfoodX[5];
    int gfoodY[5];
    int bfoodX[5];
    int bfoodY[5];

    for (int i = 0; i < 5; i++) {
        gfoodX[i] = rand() % 34 + startX;
        gfoodY[i] = rand() % 25 + startY;
        bfoodX[i] = rand() % 34 + startX;
        bfoodY[i] = rand() % 25 + startY;
    }

    struct timespec heroDelay = {.tv_nsec = 50000000L};
    struct timespec foodDelay = {.tv_nsec = 100000000L};

    int ch;
    int fallCounter = 0;
    int counter = 0;
    int stopGame = 0;

    while ((ch = getch()) != 'q' && fallCounter < 150 && !stopGame) {
        move_hero(ch, &heroStartX, heroStartY, &heroDelay);
        move_food(gfoodX, gfoodY, bfoodX, bfoodY, startY, startX, &fallCounter, &foodDelay, &stopGame);

        counter += detect_collision(heroStartX, heroStartY, gfoodX, gfoodY, bfoodX, bfoodY);

        mvprintw(startY - 1, (COLS - 40) / 2, "Made by Jakub Žir | Money collected: %d", counter);

        refresh();
    }

    display_congratulations(counter);
    timeout(50000000);
    getch();
    getch();
    endwin();
    return EXIT_SUCCESS;
}

void draw_world() {
    struct timespec ts = {.tv_sec = 0, .tv_nsec = 0.001 * 1000000000L};

    int startX = (COLS - 38) / 2;
    int startY = (LINES - 25) / 2;

    for (int x = 0; x < 38; x++) {
        mvprintw(startY, startX + x, "=");
        mvprintw(startY + 24, startX + x, "=");
        refresh();
        nanosleep(&ts, NULL);
    }

    for (int y = 1; y < 24; y++) {
        mvprintw(startY + y, startX, "|");
        mvprintw(startY + y, startX + 37, "|");
        refresh();
        nanosleep(&ts, NULL);
    }
}

void move_hero(int direction, int *heroStartX, int heroStartY, struct timespec *heroDelay) {
    nanosleep(heroDelay, NULL);

    mvprintw(heroStartY, *heroStartX, "       ");

    switch (direction) {
    case KEY_RIGHT:
        if (*heroStartX + strlen(HERO) < (COLS - 30)) {
            *heroStartX += 1;
        }
        break;
    case KEY_LEFT:
        if (*heroStartX > (COLS - 37) / 2) {
            *heroStartX -= 1;
        }
        break;
    }

    mvprintw(heroStartY, *heroStartX, HERO);
    refresh();
}

void move_food(int *gfoodX, int *gfoodY, int *bfoodX, int *bfoodY, int startY, int startX, int *fallCounter, struct timespec *foodDelay, int *stopGame) {
    for (int i = 0; i < 5; i++) {
        mvprintw(gfoodY[i], gfoodX[i], " ");
        mvprintw(bfoodY[i], bfoodX[i], " ");

        if (gfoodY[i] > startY + 22) {
            gfoodX[i] = rand() % 34 + startX;
            gfoodY[i] = startY + 1;
            (*fallCounter)++;
        } else {
            gfoodY[i] += 1;
            if (gfoodX[i] > startX + 2 && gfoodX[i] < startX + 34) {
                gfoodX[i] += (rand() % 5) - 1;
            } else if (gfoodX[i] <= startX + 2) {
                gfoodX[i] += 1;
            } else if (gfoodX[i] >= startX + 34) {
                gfoodX[i] -= 1;
            }
        }

        attron(COLOR_PAIR(1)); 
        mvprintw(gfoodY[i], gfoodX[i], GFOOD);
        attroff(COLOR_PAIR(1));
    }

    for (int i = 0; i < 5; i++) {
        if (bfoodY[i] > startY + 22) {
            bfoodX[i] = rand() % 34 + startX;
            bfoodY[i] = startY + 1;
            (*fallCounter)++;
        } else {
            bfoodY[i] += 1;
            if (bfoodX[i] > startX + 2 && bfoodX[i] < startX + 34) {
                bfoodX[i] += (rand() % 3) - 1;
            } else if (bfoodX[i] <= startX + 2) {
                bfoodX[i] += 1;
            } else if (bfoodX[i] >= startX + 34) {
                bfoodX[i] -= 1;
            }
        }

        attron(COLOR_PAIR(2));
        mvprintw(bfoodY[i], bfoodX[i], BFOOD);
        attroff(COLOR_PAIR(2));
    }

    refresh();
    nanosleep(foodDelay, NULL);
}

int detect_collision(int heroStartX, int heroStartY, int gfoodX[], int gfoodY[], int bfoodX[], int bfoodY[]) {
    int heroLength = strlen(HERO);

    for (int i = 0; i < heroLength; i++) {
        for (int j = 0; j < 5; j++) {
            if (heroStartX + i >= gfoodX[j] && heroStartX + i < gfoodX[j] + strlen(GFOOD) &&
                heroStartY == gfoodY[j]) {
                mvprintw(gfoodY[j], gfoodX[j], " ");
                return 1;
            }
        }

        for (int j = 0; j < 5; j++) {
            if (heroStartX + i >= bfoodX[j] && heroStartX + i < bfoodX[j] + strlen(BFOOD) &&
                heroStartY == bfoodY[j]) {
                mvprintw(bfoodY[j], bfoodX[j], " ");
                return 1;
            }
        }
    }

    return 0;
}

void display_congratulations(int counter) {
    int startX = (COLS - 38) / 2;
    int startY = (LINES - 25) / 2;
    mvprintw(startY + 25, startX, "Congratulations, your score is %d ! Press any key to quit", counter);
    refresh();
}
