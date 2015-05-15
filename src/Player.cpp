/*  Player.cpp
 *  Contains defination of Player class
 *  Player class holds the data related to pirticular player,
 *  like player color, player pawns and getter funtions.
 *  Its a subclass of Game
 */

#include <GL/glut.h>
#include "Player.h"

Player::Player()
{

}

// Constructor with parameter. Sets player starting
// position, color and initialize pawns
Player::Player(int startPosition, int color )
{
    GLfloat colorRed, colorGreen, colorBlue;
    this->startPosition = startPosition;

    switch(color)
    {
        case COLOR_RED      :   colorRed = 1.0f;
                                colorGreen = 0.0f;
                                colorBlue = 0.0f;
                                break;

        case COLOR_GREEN    :   colorRed = 0.0f;
                                colorGreen = 1.0f;
                                colorBlue = 0.0f;
                                break;

        case COLOR_BLUE     :   colorRed = 0.0f;
                                colorGreen = 0.0f;
                                colorBlue = 1.0f;
                                break;

        case COLOR_YELLOW   :   colorRed = 1.0f;
                                colorGreen = 1.0f;
                                colorBlue = 0.0f;
                                break;
    }

    this->color[0] = colorRed;
    this->color[1] = colorGreen;
    this->color[2] = colorBlue;

    items[0] = 0;
    items[1] = 0;
    items[2] = 0;
    items[3] = 0;
}


// Getter funtions
void Player::getColor(GLfloat colorVal[])
{
    colorVal[0] = color[0];
    colorVal[1] = color[1];
    colorVal[2] = color[2];
}

int Player::getPosition ()
{
    return startPosition;
}


