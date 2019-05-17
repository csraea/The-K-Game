#include <stdlib.h>

#include "k.h"

void add_random_tile(struct game *game){
    int row, col;
    // find random, but empty tile
    do{
        row = rand() % SIZE;
        col = rand() % SIZE;
    }while(game->board[row][col] != ' ');

    // place to the random position 'A' or 'B' tile
    if(rand() % 2 == 0){
        game->board[row][col] = 'A';
    }else{
        game->board[row][col] = 'B';
    }
}

bool is_game_won(const struct game game){
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            if(game.board[i][j] == 'K'){
                return true;
            }
        }
    }
    return false;
}

bool is_move_possible(const struct game game){
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            if(game.board[i][j] == ' ' || (i != 3 && game.board[i][j] == game.board[i+1][j]) || (j != 3 && game.board[i][j] == game.board[i][j+1])){
                return true;
            }
        }
    }
    return false;
}

bool update(struct game *game, int dy, int dx){
    bool result;
    if((dy != 0 && dx != 0)){
        return false;
    } else if(dx == 0) {
        switch (dy) {
            case -1: 
                result = move_UP(game);
                break; 
            case 1:
                result = move_DOWN(game);
                break;    
        }                 
    } else if(dy == 0) {
        switch (dx) {
            case 1:
                result = move_RIGHT(game);
                break;
            case -1:
                result = move_LEFT(game);
                break;
        }
    }
    return result;
}

bool move_UP(struct game *game){
    bool movement;
    //skipping spaces
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 3; j++){
            if(game->board[j][i] == ' '){                        
                int raw;
                for(raw = j; game->board[raw][i] == ' ' && raw < 3; raw++){
                    ; 
                }
                if(game->board[raw][i] != ' '){
                    movement = true;
                    game->board[j][i] = game->board[raw][i];
                    game->board[raw][i] = ' ';
                }
            }
        }
    }
    //adding letters if possible
    for(int i = 0; i < 4; i++){
        int botCount = 4;
        for(int j = 0; j < 3; j++){
            if(game->board[j][i] == game->board[j+1][i] && game->board[j+1][i] != ' '){
                trace_score(i, j, game);
                movement = true;
                game->board[j][i] = game->board[j][i]+1;
                botCount--;
                int raw;
                for(raw = j+1; raw < 3; raw++){
                    game->board[raw][i] = game->board[raw+1][i];
                }
            }
            if(botCount != 4)
                game->board[botCount][i] = ' ';
        }
    }
    return (movement == true) ? true : false;
}

bool move_DOWN(struct game *game){
    bool movement;
    //skipping spaces
    for(int i = 0; i < 4; i++){
        for(int j = 3; j > 0; j--){
            if(game->board[j][i] == ' '){                        
                int raw;
                for(raw = j; game->board[raw][i] == ' ' && raw > 0; raw--){
                    ; 
                }
                if(game->board[raw][i] != ' '){
                    movement = true;
                    game->board[j][i] = game->board[raw][i];
                    game->board[raw][i] = ' ';
                }
            }
        }
    }
    //adding letters if possible
    for(int i = 0; i < 4; i++){
        int botCount = -1;
        for(int j = 3; j > 0; j--){
            if(game->board[j][i] == game->board[j-1][i] && game->board[j-1][i] != ' '){
                trace_score(i, j, game);
                movement = true;
                game->board[j][i] = game->board[j][i]+1;
                botCount++;
                int raw;
                for(raw = j-1; raw > 0; raw--){
                    game->board[raw][i] = game->board[raw-1][i];
                }
            }
            if(botCount != -1)
                game->board[botCount][i] = ' ';
        }
    }
    return (movement == true) ? true : false;                
}

bool move_RIGHT(struct game *game){
    bool movement;
    //skipping spaces
    for(int j = 0; j < 4; j++){
        for(int i = 3; i > 0; i--){
            if(game->board[j][i] == ' '){                        
                int col;
                for(col = i; game->board[j][col] == ' ' && col > 0; col--){
                    ; 
                }
                if(game->board[j][col] != ' '){
                    movement = true;
                    game->board[j][i] = game->board[j][col];
                    game->board[j][col] = ' ';
                }
            }
        }
    }
    //adding letters if possible
    for(int j = 0; j < 4; j++){
        int botCount = -1;
        for(int i = 3; i > 0; i--){
            if(game->board[j][i] == game->board[j][i-1] && game->board[j][i-1] != ' '){
                trace_score(i, j, game);
                movement = true;
                game->board[j][i] = game->board[j][i]+1;
                botCount++;
                int col;
                for(col = i-1; col > 0; col--){
                    game->board[j][col] = game->board[j][col-1];
                }
            }
            if(botCount != -1)
                game->board[j][botCount] = ' ';
        }
    }
    return (movement == true) ? true : false;            
}

bool move_LEFT(struct game *game){
    bool movement;
    //skipping spaces
    for(int j = 0; j < 4; j++){
        for(int i = 0; i < 3; i++){
            if(game->board[j][i] == ' '){                        
                int col;
                for(col = i; game->board[j][col] == ' ' && col < 3; col++){
                    ; 
                }
                if(game->board[j][col] != ' '){
                    movement = true;
                    game->board[j][i] = game->board[j][col];
                    game->board[j][col] = ' ';
                }
            }
        }
    }
    //adding letters if possible
    for(int j = 0; j < 4; j++){
        int botCount = 4;
        for(int i = 0; i < 3; i++){
            if(game->board[j][i] == game->board[j][i+1] && game->board[j][i+1] != ' '){
                trace_score(i, j, game);
                movement = true;
                game->board[j][i] = game->board[j][i]+1;
                botCount--;
                int col;
                for(col = i+1; col < 3; col++){
                    game->board[j][col] = game->board[j][col+1];
                }
            }
            if(botCount != 4)
                game->board[j][botCount] = ' ';
        }
    }
    return (movement == true) ? true : false;
}

void trace_score(int col, int raw, struct game *game){
    char letterToFind = game->board[raw][col];
    char *letters = "ABCDEFGHIJK";
    int power = search(letters, letterToFind);
    double increasing = pow(2.0, (double)power + 1.0);
    game->score += increasing;
}

int search(char *letters, char letterToFind){
    int low = 0;
    int high = strlen(letters);
    int mid;
    while (low <= high) {
        mid = (low + high)/2;
        if (letterToFind < letters[mid])
            high = mid - 1;
        else if (letterToFind > letters[mid])
            low = mid + 1;
        else
            return mid;
    }
}

void get_input(int *dy, int *dx){
    int but = getch();
    switch(but) {
        case KEY_LEFT :
            *dy = 0;
            *dx = -1;
            break;
        case KEY_RIGHT : 
            *dy = 0;
            *dx = 1;
            break;
        case KEY_UP :
            *dy = -1;
            *dx = 0;
            break;
        case KEY_DOWN :
            *dy = 1;
            *dx = 0;
            break;              
    }
}
