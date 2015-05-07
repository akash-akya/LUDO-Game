#ifndef GAME_PREF_H
#define GAME_PREF_H

int numberOfPlayers = 2;
int playerColor[4] = {0,1,2,3};
GLfloat colorRed, colorGreen, colorBlue;
extern GLint width, height;
extern GLint mainMenuTexture[5];


void gamePrefTimer(int value)
{
    glutPostRedisplay();      // Post re-paint request to activate display()
    glutTimerFunc(refreshMills, gamePrefTimer, 0); // next Timer call milliseconds later
}

/*  
 *  Draws the box based on x & y and width and height. (x,y) is left most top corner  
 */


void gamePrefDisplay()
{
    int xPos;
    glClear (GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity ();

    glPushMatrix ();
    glColor3f(1,1,1);

    glEnable(GL_TEXTURE_2D);
    displayBg(mainMenuTexture[0]);
    glDisable(GL_TEXTURE_2D); 

    // glEnable(GL_TEXTURE_2D);
    // displayBoard(mainMenuTexture[2], 400, 200, 400, 500 );
    // glDisable(GL_TEXTURE_2D);

    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.267, 0.38, 0.039, 0.4);
    menuBox(500, 70, 400, 600 );


    char ch[] = "Number of players :  ";
    char player[] = "Player 0 color :  ";

    ch[20] = '0' + (unsigned char) numberOfPlayers;

    xPos = width/2 - strlen(ch)/2 * 15;
    glColor3f(1,1,1);
    renderStrokeFontString (xPos, 600, 0, 0.15, ch);

    glLoadName(1);
    glColor4f(1,1,1,0.5);
    menuBox( width/2-30,520,30,30);
    glColor3f(0,0,0);
    renderStrokeFontString (width/2-23, 529, 0, 0.15, "+");

    glLoadName(2);
    glColor4f(1,1,1,0.5);
    menuBox( width/2+30,520,30,30);
    glColor3f(0,0,0);
    renderStrokeFontString (width/2+36, 529, 0, 0.15, "-");
    glDisable(GL_BLEND);



    for (int i = 1; i <= numberOfPlayers; ++i)
    {
        player[7] = '0' + (unsigned char) i;
        glColor3f(1,1,1);

        xPos = width/2 - strlen(player)/2 * 15;
        renderStrokeFontString (xPos, 550-40-i*80, 0, 0.15 , player);

        switch(playerColor[i-1]){
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

        glColor3f(colorRed, colorGreen, colorBlue);
        glLoadName(20+i);
        menuBox(xPos + strlen(player) * 15 + 20,  550-40-i*80-20, 50 , 50);
    }

    glLoadName(5);
    xPos = width/2 - 15*2;

    glColor3f(1.0f, 1.0f, 1.0f);
    menuBox(xPos-15, 550-40-80*numberOfPlayers-100, 100 , 50);

    glColor3f(0.0f, 0.0f, 0.0f);
    renderStrokeFontString (xPos, 550-40-80*numberOfPlayers-80, 0, 0.15, "Next");

    glPopMatrix();
    glutSwapBuffers();
}


int getGamePrefMenu(int x, int y)
{
  GLint height  = glutGet(GLUT_WINDOW_HEIGHT);
  y = height - y;

  GLint     pawn = 0;
  GLint     hits;
  GLuint    buff[64] = {0};
  GLint     view[4];
 
  glSelectBuffer(64, buff);
  glGetIntegerv(GL_VIEWPORT, view);
 
  glRenderMode(GL_SELECT);
  glInitNames();
  glPushName(0);
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  gluPickMatrix(x, y, 1.0, 1.0, view);
  glOrtho (0, width, 0, height, 0, 100);

  glMatrixMode(GL_MODELVIEW);
  glutSwapBuffers();
  gamePrefDisplay();
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  hits = glRenderMode(GL_RENDER);

  for (int i = 0; i < hits; i++){
    pawn = (GLubyte)buff[i * 4 + 3];
    // cout << "hits : " << hits << " pawn : "<< pawn << endl;
  }
  glMatrixMode(GL_MODELVIEW);
  return pawn;
}

void gamePrefMouse(int button, int status, int x, int y)
{
    if (status == GLUT_DOWN){
        cout << "value : " << getGamePrefMenu (x, y) << endl;

        switch (getGamePrefMenu(x, y ))
        {
            case 1  :
                        if(numberOfPlayers < 4){
                            numberOfPlayers ++;
                        }
                break;

            case 2  :
                        if(numberOfPlayers > 2){
                            numberOfPlayers --;
                        }
                break;

            case 5  :   setGameView (numberOfPlayers); 
                break;

            case 21 :   
            case 22 :
            case 23 :
            case 24 :
                    // int player =  21-getGamePrefMenu(x,y);
                    // int color =  playerColor[player];
                    // color  = (playerColor[player]+1) % 4;
                    // for (int i = 0; i < numberOfPlayers; ++i)
                    // {
                    //     if(playerColor[i] == color && i != player){
                    //         int temp = playerColor[player];
                    //         playerColor[player] = color;
                    //         playerColor[i] = temp;
                    //         break;
                    //     }
                    // }
                    // for (int i = 0; i < numberOfPlayers; ++i)
                    // {
                    //     /* code */
                    // }
                break;
        }

    }
    glutPostRedisplay();
}

void gamePrefKeyboard (unsigned char key, int x, int y) {

    if (key == 27) 
        exit (0); 
}

void setGamePrefView()
{

    glutDisplayFunc (gamePrefDisplay);
    glutKeyboardFunc (gamePrefKeyboard);
    glutTimerFunc (0, gamePrefTimer, 0); 
    glutMouseFunc (gamePrefMouse);
    glutSpecialFunc (NULL);
    // glutReshapeFunc(reshape);
    // glMatrixMode (GL_PROJECTION);
    // glLoadIdentity ();
    // glOrtho (-100, 100, -100, 100, -100, 100);
    // glMatrixMode (GL_MODELVIEW);
}



#endif