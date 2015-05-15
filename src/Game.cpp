/*  Game.h
 *  Contains defination of Game class
 *  Game class holds the data related to present game,
 *  players, number of players and a funtion to move pawns
 */


#include "Game.h"

// Default constructor
// sets number of players as 2 by default
Game::Game()
{
        numberOfPlayers = 2;
        // For number of players = 2 set
        // player 2 position diagonally
        player[0] = Player(0, 0);
        player[1] = Player(2, 2);

}

// Constructor with parameter as number of players
Game::Game(int num)
{
        numberOfPlayers = num;

        // For number of players = 2 set
        // player 2 position diagonally
        if(numberOfPlayers == 2)
        {
            player[0] = Player(0, 0);
            player[1] = Player(2, 2);
        }
        else
        {
            for (int i = 0; i < numberOfPlayers; ++i){
                player[i] = Player(i, i);
            }
        }
}

// Move the player 'playerId' 's pawn 'item' position in board
// based on diceValue.
// NOTE : dice value 0 indicates special case
// Its used to send the player pawn back to its home
void Game::move(int playerId, int item, int diceVal)
{
    if(diceVal == 0)
        player[playerId].items[item] = diceVal;
    else
        player[playerId].items[item] += diceVal;

}