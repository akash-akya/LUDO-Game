#include "Player.h"

#ifndef GAME_H
#define GAME_H


class Game
{
public:
    Player player[4];
    int numberOfPlayers;
    Game();
    Game(int num);
    void move(int playerId, int item, int diceVal);    
};

#endif