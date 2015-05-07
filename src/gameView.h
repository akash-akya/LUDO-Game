#ifndef GAME_DISPLAY_H
#define GAME_DISPLAY_H
#include <string.h>
#include <iostream>
#include <cmath>
#include <time.h> 

using namespace std;


#define LIMIT 20
#define GTOR 0.01746
#define PI 3.14

extern GLint width, height;

int     dice;
int     diceRoll = 0;
int     player;
int     refreshMills = 20;
bool    animateDice = false;
bool    viewProspective = true;
bool    toggle = true;
Game    game;
GLuint  texture[10];
GLfloat camX, camY, camZ ;
GLfloat angleVetical     = 45.0f;
GLfloat angleHorizantal  = 90.0f; 
GLfloat axis[3]          = { 0.0f, 0.0f, 0.0f};
GLfloat mat_specular[]   = { 0.5, 0.5, 0.5, 0.3 };
GLfloat mat_shininess[]  = { 10.0 };
GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
GLfloat angle            = 0.0f;
GLfloat angleDiff        = 1.0f;
GLfloat sangle           = 90.0f;
GLfloat translateVectors[13][3] = { {1,0,0},     {0,1,0},    {1,0,0},
                                    {0,-1,0},    {1,0,0},    {0,-1,0},
                                    {-1,0,0},    {0,-1,0},   {-1,0,0},
                                    {0,1,0},     {-1,0,0},   {0,1,0},
                                    {1,0,0}};
const char digits[]             = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
GLfloat vectorMaxValues[13]     = {5,6,2,5,6,2,5,6,2,5,6,1,5};
GLfloat boxPosition[13]         = {6,6,2,6,6,2,6,6,2,6,6,1,5};
GLfloat points[][3]             = { {-1,-1,-1}, {-1,1,-1},  {1,1,-1},   {1,-1,-1},
                                    {-1,-1,1},  {-1,1,1},   {1,1,1},    {1,-1,1} };

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

void drawDice()
{
    glPushMatrix();

    glTranslatef(8,8,0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_TEXTURE_2D);
    
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

void displayItems()
{
    int dPoint,  bReminder;
    for (int i = 0; i < game.numberOfPlayers; ++i){
        GLfloat color[3] = {1,1,1};
        game.player[i].getColor(color);
        glColor3f(color[0],color[1], color[2]);

        for (int j = 0; j < 4; ++j){
            glPushMatrix();
            glRotatef(-90 * i , 0, 0, 1);
            glTranslatef(-7, 1, 0);

            dPoint = game.player[i].items[j];
            if(dPoint >0 && dPoint <= 56){
                int k = 0;
                while(dPoint > 0){
                    if(dPoint > vectorMaxValues[k]){
                        bReminder = boxPosition[k];
                        dPoint = dPoint - vectorMaxValues[k];
                    }else{
                        bReminder = dPoint;
                        dPoint = 0;
                    }
                    glTranslatef(translateVectors[k][0] * bReminder, translateVectors[k][1] * bReminder , 0);
                    k++;
                }
            } else if(dPoint <= 56) {
                // glPushMatrix();
                glTranslatef(2.5, 3.5, 0);
                switch(j){
                    case 0 :    glTranslatef(0,-1,0);
                                break;
                    case 1 :    glTranslatef(-1,0,0); 
                                break;
                    case 2 :    glTranslatef(0,1,0);
                                break;
                    case 3 :    glTranslatef(1,0,0);
                                break;
                }
                // glPopMatrix();
            }
            if(dPoint <= 56){
                glLoadName(i*4+j+1);
                glutSolidCone(0.5, 2.0, 30, 30);
            }
            glPopMatrix();
        }
    }
}

void displayBoard()
{
 
    glEnable(GL_DEPTH_TEST);
    glColor3f(1,1,1);
    glPushMatrix();
    glRotatef(-90 * 0 , 0, 0, 1);
  
    glBindTexture(GL_TEXTURE_2D, texture[0]);
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

void drawMenuBox()
{
    glPushMatrix();
    glColor4f(0.1,0.1,0.1,0.5);
    glBegin(GL_POLYGON);
        glVertex3f(-10,10,0);
        glVertex3f(10,10,0);
        glVertex3f(10,8.5,0);
        glVertex3f(-10,8.5,0);
    glEnd();

    char str[] = "Player:";
    char ch[] = "0";
    GLfloat color[3];
    ch[0] =  digits[player+1];
    strcat(str, ch);
    
    game.player[player].getColor(color);
    glColor3fv(color);
    renderStrokeFontString(-5,9,0,0.005,str);
    glColor3f(1,1,1);

    strcpy(str,"Right Click");
    if(dice>0){
        glBindTexture(GL_TEXTURE_2D, texture[2]);
        drawDice();
    }
    else
        renderStrokeFontString(1,9,0,0.005,str);
    glPopMatrix();
}

void crossProduct(GLfloat a[], GLfloat b[], GLfloat c[])
{
    // GLfloat c[3];
    c[0] = a[1] * b[2] - a[2] * b[1];
    c[1] = a[2] * b[0] - a[0] * b[2];
    c[2] = a[0] * b[1] - a[1] * b[0];
}

/*
 ************************ OPEN-GL CALLBACK FUNCTIONS ********************************
*/

void gameTimer(int value)
{
    glutPostRedisplay();      // Post re-paint request to activate display()
    glutTimerFunc(refreshMills, gameTimer, 0); // next Timer call milliseconds later

    if ( angleDiff >= 0 && animateDice )
    {
        angle =  angle + 80 * angleDiff;// * angleDiff;
        if ( angle > 360)
        {
            angle = 0;
            if ( sangle < 175 )
                sangle+=5;
            else
                animateDice = false;
            angleDiff = sin(sangle*PI/180.0);
        }
    }
    else
    {
        angle = 0.0f;
        angleDiff = 1.0f;
        sangle = 90.0f;
    }
   
}

void gameDisplay (void) 
{
    glClear (GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity ();

    glPushMatrix();
    
    glTranslatef ( 0, -1.8, -1.5);
    gluLookAt ( camX, camY, camZ,
                0.0f, 0.0f, 0.0f,
                0.0f, 1.0f, 0.0f );

    glRotatef(-90,1,0,0);

    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_TEXTURE_2D);
    displayBoard();

    glDisable(GL_NORMALIZE);
    glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    displayItems();
    glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);

    glPopMatrix();
    glPushMatrix ();
    gluLookAt ( 0.0f,  0.0f,  25.0,
                0.0f,  0.0f,  0.0f,
                0.0f,  1.0f,  0.0f );
    drawMenuBox ();
    glPopMatrix ();
    glutSwapBuffers();
}

int getPawn(int x, int y)
{
  // GLint width   = glutGet(GLUT_WINDOW_WIDTH);
  GLint height  = glutGet(GLUT_WINDOW_HEIGHT);
  y = height - y;

  GLuint buff[64] = {0};
  int pawn = 0;
  GLint hits, view[4];
 
  glSelectBuffer(64, buff);
  glGetIntegerv(GL_VIEWPORT, view);
 
  glRenderMode(GL_SELECT);
  glInitNames();
  glPushName(0);
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  gluPickMatrix(x, y, 1.0, 1.0, view);
  gluPerspective(45, (GLfloat)width/(GLfloat)height, 0.1, 100);  

  glMatrixMode(GL_MODELVIEW);
  gameDisplay();
  glutSwapBuffers();
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  hits = glRenderMode(GL_RENDER);
 
  for (int i = 0; i < hits; i++){
    pawn = (GLubyte)buff[i * 4 + 3];
  }

  glMatrixMode(GL_MODELVIEW);
  return pawn;
}

void gameMouse(int button, int status, int x, int y)
{
    int value;

    if(!animateDice){
        if(button == GLUT_LEFT_BUTTON && status == GLUT_DOWN){
            if(toggle){
                value = getPawn(x, y);
                if(value == 100){
                    dice = (rand()%6)+1;
                    cout << "Dice : " << dice << endl;
                    toggle = !toggle;
                    cout << "\nPlayer :: " << player << endl;
                }
            } else {
                int playerNo, pawn ;
                value = getPawn(x, y);
                value--;
                playerNo = value / 4; 
                pawn = value % 4;

                if(value > -1 && playerNo == player ){  
                  
                    cout << "player : " << playerNo << " Pawn : " << pawn << endl;
                    int prestPawnPos = game.player[playerNo].items[pawn] + dice;

                    for (int j = 0; j < 4; ++j)
                        if(j != pawn){
                            int pos = game.player[playerNo].items[j];
                            if(prestPawnPos == pos)
                                return;
                        }           
                    prestPawnPos = (prestPawnPos + 13 * playerNo) %52;
                    game.move(player, pawn, dice);

                    for (int i = 0; i < game.numberOfPlayers; ++i)
                        if(i != playerNo)
                            for (int j = 0; j < 4; ++j){
                                int pos = game.player[i].items[j] + 13 * i;
                                if(game.player[i].items[j] < 52){
                                    pos = (pos % 52);
                                    if(prestPawnPos == pos)
                                        game.move(i, j, 0);       
                                }
                            }
                    diceRoll++;
                    if(dice != 6 || diceRoll == 3){
                        diceRoll = 0;     
                        player = (player+1)% game.numberOfPlayers;
                    }
                    dice = 0;
                    toggle = !toggle;
                }
            }
        } else if(button == GLUT_RIGHT_BUTTON && status == GLUT_DOWN && toggle){
            dice = (rand()%6)+1;
            srand(time(NULL));
            for (int i=0 ; i <2 ; i++)
                axis[i] = ((rand()%200)-100)/100.0;
            animateDice = true;
            cout << "Dice : " << dice << endl;
            toggle = !toggle;
        }
    }

}

void updateCamera(){
    if(angleVetical > 360 )
        angleHorizantal = angleHorizantal - 360;    

    if(angleVetical < 0 )
        angleHorizantal = angleHorizantal + 360;

    camY = 23 * sin(angleVetical * PI / 180);
    camX = 23 * cos(angleVetical * PI / 180) * cos(angleHorizantal * PI / 180);
    camZ = 23 * cos(angleVetical * PI / 180) * sin(angleHorizantal * PI / 180);
    glutPostRedisplay();
}

void gameSpecialKeys(int key, int xx, int yy) {
    // float fraction = 1.0f;
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

void gameKeyboard (unsigned char key, int x, int y) {
    int val;

    if (key == 27) 
        exit (0); 

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

void setGameView(int numberOfPlayers)
{
    glutDisplayFunc (gameDisplay);
    glutKeyboardFunc (gameKeyboard);
    glutTimerFunc (0, gameTimer, 0); 
    glutMouseFunc (gameMouse);
    glutSpecialFunc (gameSpecialKeys);
    
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective(45, (GLfloat)width/(GLfloat)height, 0.1, 100);  
    glMatrixMode (GL_MODELVIEW);

    camY = 23 * sin(angleVetical * PI / 180);
    camX = 23 * cos(angleVetical * PI / 180) * cos(angleHorizantal * PI / 180);
    camZ = 23 * cos(angleVetical * PI / 180) * sin(angleHorizantal * PI / 180);
    glEnable(GL_DEPTH_TEST);

    texture[0] = SOIL_load_OGL_texture (
                    "ludo.png",
                    SOIL_LOAD_AUTO,
                    SOIL_CREATE_NEW_ID,
                    SOIL_FLAG_INVERT_Y | SOIL_FLAG_MIPMAPS
                );

    texture[2] = SOIL_load_OGL_texture (
                    "dice.png",
                    SOIL_LOAD_AUTO,
                    SOIL_CREATE_NEW_ID,
                    SOIL_FLAG_INVERT_Y
                );

    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glColorMaterial ( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE ) ;
    srand(time(NULL));

    game = Game(numberOfPlayers);
}

#endif