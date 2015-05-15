/*
 *  Ludo.cpp
 *  Binds all the header files. Sets and initialize
 *  OpenGL context. Also creates window and calls a
 *  funtion to set the first view, 'MenuView'
 */

#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include <time.h>

// External library required for loading image
#include <SOIL.h>

#include "miscFunctions.h"
#include "Game.h"
#include "gameView.h"
#include "Game_pref_board.h"
#include "gamePrefView.h"
#include "aboutView.h"
#include "mainMenu.h"

using namespace std;

GLint mainMenuTexture[5];  // Pointer to the buffer containing the image
GLint width;               // Screen width
GLint height;              // Screen height

int main(int argc, char **argv)
{
    glutInit (&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutCreateWindow ("Ludo");
    glutFullScreen();
    glutReshapeFunc(reshape);

    // Load Menu-screen background used by views
	mainMenuTexture[0] =  SOIL_load_OGL_texture ( "main_menu_bg.png",
                          SOIL_LOAD_AUTO,
                            SOIL_CREATE_NEW_ID,
                            SOIL_FLAG_INVERT_Y | SOIL_FLAG_MIPMAPS
                          );

    // Load menu-screen item background used by main-menu
    mainMenuTexture[1] =  SOIL_load_OGL_texture ( "board.png",
                            SOIL_LOAD_AUTO,
                            SOIL_CREATE_NEW_ID,
                            SOIL_FLAG_INVERT_Y
                          );


    // Load about screen image
    mainMenuTexture[3] =  SOIL_load_OGL_texture ( "about.png",
                            SOIL_LOAD_AUTO,
                            SOIL_CREATE_NEW_ID,
                            SOIL_FLAG_INVERT_Y
                          );

    // Load help screen image
    mainMenuTexture[4] =  SOIL_load_OGL_texture ( "help.png",
                            SOIL_LOAD_AUTO,
                            SOIL_CREATE_NEW_ID,
                            SOIL_FLAG_INVERT_Y | SOIL_FLAG_MIPMAPS
                          );
    // Call the first view(Main-menu) and set the world-space
	setMainMenuView ();

    glutMainLoop ();
    return 0;
}