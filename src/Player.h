/*  Player.h
 *  Contains declaration of Player class
 *  Player class holds the data related to pirticular player,
 *  like player color, player pawns and getter funtions.
 *  Its a subclass of Game
 */


#ifndef PLAYER_H
#define PLAYER_H

#include <GL/glut.h>

#define TOP_LEFT 0
#define TOP_RIGHT 1
#define BOTTOM_LEFT 2
#define BOTTOM_RIGHT 3

#define COLOR_RED 0
#define COLOR_BLUE 1
#define COLOR_YELLOW 2
#define COLOR_GREEN 3

class Player
{
    GLfloat color[3];
    int startPosition;

public:
    int items[4];
    Player();
    Player(int startPosition, int color);
    void getColor(GLfloat colorVal[]);
    int getPosition();
};

#endif