#include <ncurses.h>

#include "k.c"
#include "ui.c"
#include "hof.c"

int main(void){
	struct game game = {
        .board = {
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '}
        },
        .score = 0
    };
    struct player player = {
    	.name = "Alex",
    	.score = 0
	};
	struct player list[10];
	int size = load(list);
	int dy, dx;
	bool result;
	initscr();
	noecho();
	cbreak();
	clear();
	curs_set(0);
	keypad(stdscr, TRUE);
	start_color();
	do{
		add_random_tile(&game);
		render(game);
		if(is_move_possible(game) == true){
A:			get_input(&dy, &dx);
			result = update(&game, dy, dx);
			if(result == false)
				goto A;
		} else
			break;
	} while(result == true || is_game_won(game) == false);
	player.score = game.score;
	add_player(list, &size, player);
	getch();
	exit_game(player.score);
	endwin();
}