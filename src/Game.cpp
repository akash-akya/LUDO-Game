#include "Game.h"

Game::Game()
{
        numberOfPlayers = 2;
        for (int i = 0; i < numberOfPlayers; ++i){
            player[i] = Player(i, i);
        }
}

void Game::move(int playerId, int item, int diceVal)
{
    if(diceVal == 0)
        player[playerId].items[item] = diceVal;
    else 
        player[playerId].items[item] += diceVal;

}