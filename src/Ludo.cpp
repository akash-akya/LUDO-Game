#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include <time.h>
#include "SOIL.h"


#define NUM_OF_MENU_ITEMS 4

#include "miscFunctions.h"
#include "Game.h"
#include "gameView.h"
#include "gamePrefView.h"
#include "aboutView.h"
#include "mainMenu.h"

using namespace std;

GLint width;
GLint height;
GLint mainMenuTexture[5];

int main(int argc, char **argv) 
{
    glutInit (&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    // glutFull
    // glutInitWindowSize (600, 500); 
    // glutInitWindowPosition (100, 100);
    // glLineWidth(2);


    glutCreateWindow ("Main Window");
    glutFullScreen();  
    glutReshapeFunc(reshape);

    // glutTimerFunc (0, mainMenuTimer, 0); 
    // glutKeyboardFunc (mainMenuKeyboard);
    // glutDisplayFunc (mainMenuDisplay);
    // glutMouseFunc (mainMenuMouse);

    mainMenuTexture[0] =  SOIL_load_OGL_texture ( "main_menu_bg.png",
                            SOIL_LOAD_AUTO,
                            SOIL_CREATE_NEW_ID,
                            SOIL_FLAG_INVERT_Y | SOIL_FLAG_MIPMAPS
                          );    

    mainMenuTexture[1] =  SOIL_load_OGL_texture ( "board.png",
                            SOIL_LOAD_AUTO,
                            SOIL_CREATE_NEW_ID,
                            SOIL_FLAG_INVERT_Y
                          );    

    mainMenuTexture[3] =  SOIL_load_OGL_texture ( "about.png",
                            SOIL_LOAD_AUTO,
                            SOIL_CREATE_NEW_ID,
                            SOIL_FLAG_INVERT_Y
                          );
    mainMenuTexture[4] =  SOIL_load_OGL_texture ( "help.png",
                            SOIL_LOAD_AUTO,
                            SOIL_CREATE_NEW_ID,
                            SOIL_FLAG_INVERT_Y | SOIL_FLAG_MIPMAPS
                          );

    setMainMenuView ();
    glutMainLoop ();
    return 0;
}