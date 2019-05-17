#include <stdio.h>
#include <curses.h>
#include <string.h>

#include "k.h"

//void render(const struct game game){
//    printf("score: %d\n", game.score);
//
//    for(int row = 0; row < SIZE; row++){
//        printf("+---+---+---+---+\n|");
//        for(int col = 0; col < SIZE; col++){
//            printf(" %c |", game.board[row][col]);
//        }
//        printf("\n");
//    }
//    printf("+---+---+---+---+\n");
//}

void render(const struct game game){
    init_pair(0, COLOR_BLACK, COLOR_YELLOW);
    init_pair(1, COLOR_WHITE, COLOR_GREEN);
    init_pair(2, COLOR_WHITE, COLOR_CYAN);
    init_pair(3, COLOR_WHITE, COLOR_BLUE);
    init_pair(4, COLOR_WHITE, COLOR_MAGENTA);
    init_pair(5, COLOR_WHITE, COLOR_BLACK);
    init_pair(6, COLOR_BLUE, COLOR_WHITE);
    init_pair(7, COLOR_WHITE, COLOR_BLACK);
    init_pair(8, COLOR_YELLOW, COLOR_BLACK);

    clear();
    char text[20];
    sprintf(text, "Score: %d", game.score);
    attrset(COLOR_PAIR(0));
    mvprintw(1, (COLS - (int)strlen(text)) / 2, text);
    int x_start = (COLS - 25) / 2;
    int y_start = 3;
    attrset(COLOR_PAIR(6));

    for (int y = y_start; y < y_start + 17; y++){
        for (int x = x_start; x < x_start + 25; x++){
            mvprintw(y, x, " ");
        }
    }

    for (int y = 0; y < SIZE; y++){
        for (int x = 0; x < SIZE; x++) {
            if (game.board[y][x] == ' ')
                attrset(COLOR_PAIR(0));
            else if (game.board[y][x] < 'C')
                attrset(COLOR_PAIR(1));
            else if (game.board[y][x] < 'E')
                attrset(COLOR_PAIR(2));
            else if (game.board[y][x] < 'G')
                attrset(COLOR_PAIR(3));
            else if (game.board[y][x] < 'J')
                attrset(COLOR_PAIR(4));
            else
                attrset(COLOR_PAIR(5));

            mvprintw(y_start + (y * SIZE) + 1, x_start + (x * 6) + 1, "     ");
            mvprintw(y_start + (y * SIZE) + 2, x_start + (x * 6) + 1, "  %c  ", game.board[y][x]);
            mvprintw(y_start + (y * SIZE) + 3, x_start + (x * 6) + 1, "     ");
        }
    }

    refresh();
}

void exit_game(int score){
    char answer;
    clear();
    char logo[14][50] = {
        
        {"                                             "},
        {"    ______   _____   ___    ___  ______      "},
        {"   / _____\\ / ___ \\ |   \\  /   ||  ____|  "},
        {"  | | ____ | /___\\ || |\\ \\/ /| || |___    "},
        {"  | | \\_  \\|  ___  || | \\__/ | ||  ___|   "},
        {"  | \\___/ || |   | || |      | || |____     "},
        {"   \\_____/ |_|   |_||_|      |_||______|    "},
        {"     ____  __      __ _______  ______        "},
        {"    / __ \\ \\ \\    / /|  _____||  ___ \\   "},
        {"   | /  \\ | \\ \\  / / | |____  | [___) |   "},
        {"   | |  | |  \\ \\/ /  |  ____| |  __  /     "},
        {"   | \\__/ |   \\  /   | |_____ | |  \\ \\   "},
        {"    \\____/     \\/    |_______||_|   \\_\\  "},
        {"                                             "}

    };

    int center = COLS/2 - strlen(logo[0])/2;

    int target = 4;

    attron(COLOR_PAIR(8));
    for( int row_count = 1; row_count <= 14; row_count++ ){

        for( int y = LINES-1; y >= target; y-- ){
            move(y, center);
            printw("%s", logo[row_count]);
            refresh();
            usleep( 1 * 25000 );

            // clear
            move(y,center);
            printw(logo[0]);
        }

        move(target,center);
        printw(logo[row_count]);

        target++;
    }

    refresh();
    attron(COLOR_PAIR(7));
    mvprintw(target+2, COLS/2-28, "Your score was %d. Next time you'll be better. Perhaps.\n", score);
    refresh();
    usleep( 5 * 1000000 );

    clear();
    curs_set(TRUE);
    endwin();


    exit(0);
}
