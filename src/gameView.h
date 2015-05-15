/*  gameView.h
 *  Contains callback funtions required for the Game play
 *  view.
 */

#ifndef GAME_DISPLAY_H
#define GAME_DISPLAY_H
#include <iostream>
#include <cmath>
#include <time.h>

using namespace std;

#define LIMIT 20
#define GTOR 0.01746
#define PI 3.14

void setMainMenuView();

extern GLint width, height;
extern GLint boardTexture[3];

int     dice;
int     player;
int     selectedBoard;
int     diceRoll        = 0;
int     refreshMills    = 20;
bool    animateDice     = false;
bool    viewProspective = true;
bool    toggle          = true;
Game    game;
GLuint  texture[10];
GLfloat camX, camY, camZ ;
GLfloat angleVetical     = 45.0f;
GLfloat angleHorizantal  = 90.0f;
GLfloat axis[3]          = { 0.0f,  0.0f,   0.0f };
GLfloat mat_specular[]   = { 0.5,   0.5,    0.5,    0.3 };
GLfloat light_position[] = { 1.0,   1.0,    1.0,    0.0 };
GLfloat mat_shininess[]  = { 10.0 };
GLfloat angle            = 0.0f;
GLfloat angleDiff        = 1.0f;
GLfloat sangle           = 90.0f;

// contains the actual unit vector of the game pawn movement for the player-1 (Red color player)
GLfloat translateVectors[13][3] = { {1,0,0},    {0,1,0},    {1,0,0},    {0,-1,0},
                                    {1,0,0},    {0,-1,0},   {-1,0,0},   {0,-1,0},
                                    {-1,0,0},   {0,1,0},    {-1,0,0},   {0,1,0},
                                    {1,0,0}
                                  };
// Maximun values for each direction vector.
GLfloat vectorMaxValues[13]     = {5,6,2,5,6,2,5,6,2,5,6,1,5};
// Maximun values for each direction vector with the extra boxes added for asymetric path.
GLfloat boxPosition[13]         = {6,6,2,6,6,2,6,6,2,6,6,1,5};
GLfloat points[][3]             = { {-1,-1,-1}, {-1,1,-1},  {1,1,-1},   {1,-1,-1},
                                    {-1,-1,1},  {-1,1,1},   {1,1,1},    {1,-1,1} };

// Dice face rotation bsed on the dice value. default face is 5
void setFace(int diceVal)
{
    switch(diceVal)
    {
        case 1 :    glRotatef(180,1,0,0);       break ;
        case 2 :    glRotatef(-90,1,0,0);       break ;
        case 3 :    glRotatef(90,0,1,0);        break ;
        case 4 :    glRotatef(-90,0,1,0);       break ;
        case 5 :                                break ;
        case 6 :    glRotatef(90,1,0,0);        break ;
    }
}

/* Map dice single face based on the side/face
 * |  4  |  5  |  6  |
 * |  1  |  2  |  3  |
 */

void quad(GLint v1,GLint v2,GLint v3,GLint v4, int face){
    int x = face % 3;
    int y = face / 3;

    GLfloat xCor1,xCor2;
    GLfloat yCor1,yCor2;

    xCor1 = (GLfloat) x * 0.333;
    xCor2 = xCor1 + 0.333;
    yCor1 = (GLfloat) y * 0.5;
    yCor2 = yCor1 + 0.5;

    glBegin(GL_QUADS);
        glTexCoord2f(xCor1, yCor1);   glVertex3fv(points[v1]);
        glTexCoord2f(xCor1, yCor2);   glVertex3fv(points[v2]);
        glTexCoord2f(xCor2, yCor2);   glVertex3fv(points[v3]);
        glTexCoord2f(xCor2, yCor1);   glVertex3fv(points[v4]);
    glEnd();

}

// Draw all the faces of the dice at angle for each frame
void drawDice()
{
    glPushMatrix();

    // Move to top right position of the plane
    glTranslatef(8,8,0);

    // Enable light
    glEnable(GL_NORMALIZE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_TEXTURE_2D);

    // Set the face visible based on the dice value. Then we rotate the cube in
    // mutiples of 360' to get the same face as value
    setFace(dice);
    glRotatef(angle, axis[0],axis[1],axis[2]);
    glColor3f(1,1,1);
    quad(0,1,2,3,0);
    quad(0,4,7,3,1);
    quad(0,4,5,1,2);
    quad(3,7,6,2,3);
    quad(4,5,6,7,4);
    quad(5,6,2,1,5);

    glDisable(GL_NORMALIZE);
    glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_TEXTURE_2D);

    glPopMatrix();
}


// Draw board pawns
void displayItems()
{
    int dPoint,  bReminder;

    // iterate over all player
    for (int i = 0; i < game.numberOfPlayers; ++i)
    {
        GLfloat color[3] = {1,1,1};
        // get player color from player object and set it as present color
        game.player[i].getColor(color);
        glColor3f(color[0],color[1], color[2]);

        // Iterate over all pawns of the player
        for (int j = 0; j < 4; ++j)
        {
            glPushMatrix();

            // Move the board so that the player whose pawns we want to draw
            // should appear in top left corner (Player I position)
            // This reduce the extra work of defining separate path for all the players
            glRotatef(-90 * game.player[i].getPosition() , 0, 0, 1);

            // Move to the left of the first box. this indicate position zero
            glTranslatef(-7, 1, 0);

            // get the player-i, pawn-j position
            dPoint = game.player[i].items[j];

            // If the player pawn value is greater then 56 means pawn as reached the destination.
            // Dont display teh pawn
            if(dPoint > 56)
            {
                continue;
            }

            // If the player pawn is in the board (Already entered game)
            // set the posititon  based on the vector
            if(dPoint > 0)
            {
                int k = 0;
                while(dPoint > 0)
                {
                    if(dPoint > vectorMaxValues[k])
                    {
                        bReminder = boxPosition[k];
                        dPoint = dPoint - vectorMaxValues[k];
                    } else {
                        bReminder = dPoint;
                        dPoint = 0;
                    }
                    glTranslatef(translateVectors[k][0] * bReminder, translateVectors[k][1] * bReminder , 0);
                    k++;
                }
            } else {
                // If the player pawn is not yest entered the game. display
                // it in the player home position else there is not need to display
                glTranslatef(2.5, 3.5, 0);
                switch(j)
                {
                    case 0 :    glTranslatef(0,-1,0);
                                break;
                    case 1 :    glTranslatef(-1,0,0);
                                break;
                    case 2 :    glTranslatef(0,1,0);
                                break;
                    case 3 :    glTranslatef(1,0,0);
                                break;
                }
            }

            // Show pawn position with a solid cone
            glLoadName(i*4+j+1);
            glutSolidCone(0.5, 2.0, 30, 30);
            glPopMatrix();

        }
    }
}

// Draw selected image as game board
void displayBoard()
{

    glEnable(GL_DEPTH_TEST);
    glColor3f(1,1,1);
    glPushMatrix();

    glBindTexture(GL_TEXTURE_2D, boardTexture[selectedBoard]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-7.5,-7.5,0);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(7.5,-7.5,0);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(7.5,7.5,0);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(-7.5,7.5,0);
    glEnd();
    glDisable(GL_DEPTH_TEST);
    glPopMatrix();

}

// Draw the top menu showing player who need to play next and dice
void drawMenuBox()
{
    char str[]    = "Player: ";
    GLfloat         color[3];

    glPushMatrix();
    glColor4f(0.1,0.1,0.1,0.5);
    glBegin(GL_POLYGON);
        glVertex3f(-10,10, 0);
        glVertex3f( 10,10, 0);
        glVertex3f( 10,8.5,0);
        glVertex3f(-10,8.5,0);
    glEnd();

    str [7] = '0' + player+1;

    // Get player color
    game.player[player].getColor(color);
    glColor3fv(color);
    renderStrokeFontString(-5,9,0,0.005,str);
    glColor3f(1,1,1);

    strcpy(str,"Right Click");

    // If dice is pesently active then render it
    if(dice>0){
        glBindTexture(GL_TEXTURE_2D, texture[2]);
        drawDice();
    }
    else
        renderStrokeFontString(1,9,0,0.005,str);
    glPopMatrix();
}

/*
 * Callback Functions
 */

// Timer callback funtions
void gameTimer(int value)
{
    glutPostRedisplay();      // Post re-paint request to activate display()
    glutTimerFunc(refreshMills, gameTimer, 0); // next Timer call milliseconds later

    // If dice is presently active thencalculate the angle
    if ( animateDice )
    {
        angle =  angle + 80 * angleDiff;
        if ( angle > 360)
        {
            angle = 0;
            angleDiff = sin(sangle*PI/180.0);
            // 175 is the limit. If sangle reaches that limit the stop dice animation
            if ( sangle < 175 )
            {
                sangle+=5;
            } else {
                animateDice = false;
                angleDiff   = 1.0f;
                sangle      = 90.0f;
            }
        }
    }

}

// Game Display Callback
void gameDisplay (void)
{
    glClear (GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity ();
    glPushMatrix ();
    glTranslatef ( 0, -1.8, -1.5);
    // Set camera position
    gluLookAt ( camX, camY, camZ,
                0.0f, 0.0f, 0.0f,
                0.0f, 1.0f, 0.0f );

    // Rotate -90 along axis so that the objects lie in x-z plane instaed of x-y plane
    glRotatef(-90,1,0,0);

    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_TEXTURE_2D);
    displayBoard();
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_NORMALIZE);

    // Set lighting
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    displayItems();
    glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);

    glPopMatrix();
    glPushMatrix ();

    // Set the camera position to face x-y plane always so that the
    // manu items stay at same posiiton irrespective of the game board rotation
    gluLookAt ( 0.0f,  0.0f,  25.0,
                0.0f,  0.0f,  0.0f,
                0.0f,  1.0f,  0.0f );
    drawMenuBox ();
    glPopMatrix ();
    glutSwapBuffers();
}

// Funtion used for picking
int getPawn(int x, int y)
{
  // Get screen height to calculate the y from the bottom of the screen
  GLint height  = glutGet(GLUT_WINDOW_HEIGHT);
  y = height - y;

  GLuint buff[64] = {0};
  int pawn = 0;
  GLint hits, view[4];

  glSelectBuffer(64, buff);
  // Get present view port
  glGetIntegerv(GL_VIEWPORT, view);

  // Change render mode to 'select' mode
  glRenderMode(GL_SELECT);
  glInitNames();
  glPushName(0);
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  gluPickMatrix(x, y, 1.0, 1.0, view);
  gluPerspective(45, (GLfloat)width/(GLfloat)height, 0.1, 100);

  glMatrixMode(GL_MODELVIEW);
  // Redraw the items
  gameDisplay();
  glutSwapBuffers();
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();

  // Get the 'hits' i.e. number items rendered based 'id' and viewport
  hits = glRenderMode(GL_RENDER);

  for (int i = 0; i < hits; i++)
  {
    // Get the top most rendered item id.
    pawn = (GLubyte)buff[i * 4 + 3];
  }

  // Reset the view mode
  glMatrixMode(GL_MODELVIEW);
  return pawn;
}

// Mouse callback funtion
void gameMouse(int button, int status, int x, int y)
{
    int value;

    // only accept the mouse input if dice is not animating
    if(!animateDice)
    {
        if(button == GLUT_LEFT_BUTTON && status == GLUT_DOWN)
        {
            // toggle indicates the state.
            // toggle = 1 indicates the player need to trow dice
            // toggle = 0 indicates the player need to move pawn
            if(!toggle)
            {
                // get the item clicked it
                int playerNo, pawn;
                value = getPawn(x, y)-1;
                // We assigned id such that id = player * 4 + pawn
                playerNo = value / 4;
                pawn     = value % 4;

                if ( value > -1 && playerNo == player )
                {

                    // cout << "player : " << playerNo << " Pawn : " << pawn << endl;

                    // Check whether the place is already accupied by the pawn of the same player
                    int prestPawnPos = game.player[playerNo].items[pawn] + dice;

                    for (int j = 0; j < 4; ++j)
                        if(j != pawn){
                            int pos = game.player[playerNo].items[j];
                            if(prestPawnPos == pos)
                                return;
                        }

                    prestPawnPos = (prestPawnPos + 13 * game.player[playerNo].getPosition()) %52;

                    // The place is not occupied. Move the pawn.
                    game.move(player, pawn, dice);

                    // Send the other players pawn present back to respective player home place
                    for (int i = 0; i < game.numberOfPlayers; ++i)
                        if(i != playerNo)
                            for (int j = 0; j < 4; ++j)
                            {
                                int pos = game.player[i].items[j] + 13 *  game.player[i].getPosition();
                                if(game.player[i].items[j] < 52)
                                {
                                    pos = (pos % 52);
                                    if(prestPawnPos == pos)
                                        game.move(i, j, 0);
                                }
                            }

                    // At max aplayer can throw only 3 concecutive 6's
                    diceRoll++;

                    if(dice != 6 || diceRoll == 3)
                    {
                        diceRoll = 0;
                        player = (player+1)% game.numberOfPlayers;
                    }

                    // Reset the dice value and change the mode
                    dice = 0;
                    toggle = !toggle;
                }
            }
        } else if(button == GLUT_RIGHT_BUTTON && status == GLUT_DOWN && toggle){
            // If player press right mouse button then show the dice
            // Find the random value between 1 - 6
            dice = (rand()%6)+1;
            srand(time(NULL));

            for (int i=0 ; i <2 ; i++)
                axis[i] = ((rand()%200)-100)/100.0;

            animateDice = true;
            toggle = !toggle;
        }
    }

}

// Update camera used to set the camX, camY, camZ based on the angles
void updateCamera()
{
    if ( angleVetical > 360 )
        angleHorizantal = angleHorizantal - 360;

    if ( angleVetical < 0 )
        angleHorizantal = angleHorizantal + 360;

    camY = 23 * sin(angleVetical * PI / 180);
    camX = 23 * cos(angleVetical * PI / 180) * cos(angleHorizantal * PI / 180);
    camZ = 23 * cos(angleVetical * PI / 180) * sin(angleHorizantal * PI / 180);
    glutPostRedisplay();
}

// Special key callback
void gameSpecialKeys(int key, int xx, int yy)
{
    switch (key) {
        case GLUT_KEY_DOWN :
            angleVetical -= 3.0f;
            if(angleVetical < 0)
                angleVetical = 0.0f;
            break;

        case GLUT_KEY_UP :
            angleVetical += 3.0f;
            if(angleVetical > 90)
                angleVetical = 90.0f;
            break;

        case GLUT_KEY_RIGHT :
            angleHorizantal -= 3.0f;
            break;

        case GLUT_KEY_LEFT :
            angleHorizantal += 3.0f;
            break;
    }
    updateCamera();
}


// Normal keyboard callback
void gameKeyboard (unsigned char key, int x, int y)
{
    int val;

    // Exit on Esc key press
    if (key == 27){
        exit (0);
    }

    switch (key)
    {
        case 'a' :
            angleHorizantal += 90.0f;
            val  = angleHorizantal / 90;
            angleHorizantal = val * 90;
            break;
        case 'd' :
            angleHorizantal -= 90.0f;
            val  = angleHorizantal / 90;
            angleHorizantal = val * 90;
            break;
    }
    updateCamera();
}

// Funtion which sets the callback funtions required for the game view
void setGameView(int numberOfPlayers, int board)
{

    selectedBoard = board;
    glutDisplayFunc (gameDisplay);
    glutKeyboardFunc (gameKeyboard);
    glutTimerFunc (0, gameTimer, 0);
    glutMouseFunc (gameMouse);
    glutSpecialFunc (gameSpecialKeys);

    glMatrixMode (GL_PROJECTION);
    glPushMatrix ();
    glLoadIdentity ();
    gluPerspective(45, (GLfloat)width/(GLfloat)height, 0.1, 100);
    glMatrixMode (GL_MODELVIEW);

    // Set initial camera position
    camY = 23 * sin(angleVetical * PI / 180);
    camX = 23 * cos(angleVetical * PI / 180) * cos(angleHorizantal * PI / 180);
    camZ = 23 * cos(angleVetical * PI / 180) * sin(angleHorizantal * PI / 180);
    glEnable(GL_DEPTH_TEST);

    // Load dice texture to buffer
    texture[2] = SOIL_load_OGL_texture (
                    "dice.png",
                    SOIL_LOAD_AUTO,
                    SOIL_CREATE_NEW_ID,
                    SOIL_FLAG_INVERT_Y
                );

    // Set material properties for the lighting effect
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glColorMaterial ( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE ) ;

    // seed present time as random number
    srand(time(NULL));

    // Create Game class object
    game = Game(numberOfPlayers);
}

#endif