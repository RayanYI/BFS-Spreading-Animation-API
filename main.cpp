#include "CGame.h"

int main(){
    CGame game(1600,900,"BFS Animation");
    while(game.IsOpen()){
        game.Events();
        game.Clear();
        game.Draw();
        game.Dislplay();
    }
    return 0;
}