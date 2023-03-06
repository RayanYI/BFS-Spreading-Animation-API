#include "CGame.h"

int main(){
    CGame game(500,500,"BFS Animation");
    while(game.IsOpen()){
        game.Events();
        game.Clear();
        game.Draw();
        game.Dislplay();
    }
    return 0;
}