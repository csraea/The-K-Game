#ifndef K_UI_H
#define K_UI_H
#define _BSD_SOURCE
#include "k.h"

/**
 * Renders the game
 * @param game the game object with board and score to render
 */
void render(const struct game game);
void exit_game(int score);

#endif 
