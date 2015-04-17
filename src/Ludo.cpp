#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include <time.h>
#include <SOIL.h>


#define GTOR 0.01746
#define PI 3.14


#include "Game.h"
#include "display.h"
// #include "mouse.h"

using namespace std;

Game game = Game();
GLuint texture[10];
int dice, diceRoll = 0, player;
GLfloat axis[3] = {0.0f, 0.0f, 0.0f};
bool animateDice = false;
bool viewProspective = true, toggle = true;
GLfloat angleHorizantal = 90.0f, angleVetical = 45.0f;
GLfloat dist = 35.0f; 
GLfloat camX, camY, camZ ;
GLfloat mat_specular[] = { 0.5, 0.5, 0.5, 0.3 };
GLfloat mat_shininess[] = { 10.0 };
GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };

GLfloat angle = 0.0f, angleDiff = 1.0f;
GLfloat sangle = 90.0f;

int refreshMills = 20;

void Timer(int value) {
    glutPostRedisplay();      // Post re-paint request to activate display()
    glutTimerFunc(refreshMills, Timer, 0); // next Timer call milliseconds later

    if(angleDiff >= 0 && animateDice){
        angle =  angle + 80 * angleDiff;// * angleDiff;
        if(angle > 360){
            angle = 0;
            if(sangle < 175)
                sangle+=5;
            else
                animateDice = false;

            angleDiff = sin(sangle*PI/180.0);
        }    
    }else{
        angle = 0.0f;
        angleDiff = 1.0f;
        sangle = 90.0f;
    }
   
}

void display (void) 
{

    glClear (GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    glPushMatrix();
    gluLookAt( 0, 0, 25,
            0.0f,0.0f,0.0f,
            0.0f, 1.0f,  0.0f);
    drawMenuBox();
    glPopMatrix();

    glTranslatef(0,-1.8,-1.5);

    gluLookAt( camX, camY, camZ,
            0.0f,0.0f,0.0f,
            0.0f, 1.0f,  0.0f);

    glRotatef(-90,1,0,0);
    // glTranslatef(0,0,-5);

    glPushMatrix();

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
    displayItems(game);
    glDisable(GL_COLOR_MATERIAL);        
    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);

    glPopMatrix();
    glutSwapBuffers();   


}

int getPawn(int x, int y, Game game)
{
  y = 500 - y;
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
  gluPerspective(45, 1, 0.1, 100);

  glMatrixMode(GL_MODELVIEW);
  glutSwapBuffers();
  // gl_draw(game);
  display();
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  hits = glRenderMode(GL_RENDER);
 
  for (int i = 0; i < hits; i++){
    // printf( "Pawn : %d\n",(GLubyte)buff[i * 4 + 3]);
    pawn = (GLubyte)buff[i * 4 + 3];
    // if(pawn != 0)

  }

  glMatrixMode(GL_MODELVIEW);
  return pawn;

}

void myMouse(int button, int status, int x, int y)
{
    int value;

    if(!animateDice){
        if(button == GLUT_LEFT_BUTTON && status == GLUT_DOWN){
            if(toggle){
                value = getPawn(x, y, game);
                if(value == 100){
                    dice = (rand()%6)+1;
                    cout << "Dice : " << dice << endl;
                    toggle = !toggle;
                    cout << "\nPlayer :: " << player << endl;
                }


            } else {

                int playerNo, pawn ;
                value = getPawn(x, y, game);
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

void myInit()
{
    camY = 23 * sin(angleVetical * PI / 180);
    camX = 23 * cos(angleVetical * PI / 180) * cos(angleHorizantal * PI / 180);
    camZ = 23 * cos(angleVetical * PI / 180) * sin(angleHorizantal * PI / 180);
    glEnable(GL_DEPTH_TEST);

    texture[0] = SOIL_load_OGL_texture 
        (
            "ludo.png",
            SOIL_LOAD_AUTO,
            SOIL_CREATE_NEW_ID,
            SOIL_FLAG_INVERT_Y | SOIL_FLAG_MIPMAPS //| SOIL_FLAG_MIPMAPS 
            /*| SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT*/
        );    


    texture[2] = SOIL_load_OGL_texture 
    (
        "dice.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );

    // glShadeModel (GL_SMOOTH);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glColorMaterial ( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE ) ;
    srand(time(NULL));

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

void processSpecialKeys(int key, int xx, int yy) {

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



void keyboard (unsigned char key, int x, int y) {
    int val;

    if (key == 27) 
        exit (0); 

    switch (key) {
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

int main(int argc, char **argv) {
    glutInit (&argc, argv); /* Initialise Open GL */
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (600, 500); /* Set the window size */
    glutInitWindowPosition (100, 100); /* Set the window position */
    glutCreateWindow ("ex5"); /* Create the window */

    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective(45, 1, 0.1, 100);
    glMatrixMode (GL_MODELVIEW);
    glutSpecialFunc(processSpecialKeys);
    glutDisplayFunc (display); /* Register the "display" function */
    glutKeyboardFunc (keyboard); /* Register the "keyboard" function */
    glutTimerFunc(0, Timer, 0); 
    glutMouseFunc (myMouse); /* Register the "keyboard" function */
    myInit();
    glutMainLoop (); /* Enter the OpenGL main loop */
    return 0;
}


