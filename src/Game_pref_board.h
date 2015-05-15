/*  Game_pref_board.h
 *  Contains callback funtions required for game preference
 *  view (Game board selection).
 */

#ifndef GAME_PREF_BOARD_H
#define GAME_PREF_BOARD_H

extern  GLint width, height;
extern  GLint mainMenuTexture[5];
extern  GLint numberOfPlayers ;
GLint   boardTexture[3];
int     numberOfBoards = 3;
int     selectedItem = 0;

void gamePrefBoardTimer(int value)
{
    glutPostRedisplay();      // Post re-paint request to activate display()
    glutTimerFunc(refreshMills, gamePrefBoardTimer, 0); // next Timer call milliseconds later
}

void gamePrefBoardDisplay()
{
    // variable for setting the x-axis for text and texture
    int xPos;
    int ListYPos = 700;

    glClear (GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity ();

    glPushMatrix ();
    glColor3f (1,1,1);

    glEnable(GL_TEXTURE_2D);
    displayBg(mainMenuTexture[0]);
    glDisable(GL_TEXTURE_2D);

    // Enable 'Blend' feature for transparency
    glEnable (GL_BLEND);
    // Set the blending parameters to use the Alpha channel
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.267, 0.38, 0.039, 0.4);
    // Draw the box behind the menu item text.
    menuBox(500, 70, 400, 600 );
    char ch[] = "Select Board";
    char boards[] = "Board 0 :  ";

    // find x-axis position based on string length and screen width to make its
    // center aligned. 15 is the approx. each charecter size
    xPos = width/2 - strlen(ch)/2 * 15;
    glColor3f(1.0,1.0,1.0);
    // Draw the text twice with slightly different x-axis to get bold text
    renderStrokeFontString (xPos, ListYPos, 0, 0.18, ch);
    renderStrokeFontString (xPos+2, ListYPos, 0, 0.18, ch);

    const int boardSize = 120;
    const int Boardmargin = 40;
    ListYPos -= 200;

    for (int i = 0; i < numberOfBoards; ++i)
    {
        boards[6] = '0' + (unsigned char) i+1;
        if (i==selectedItem)
            glColor3f (1.0,0.75,0.25);
        else
            glColor3f(1,1,1);

        // Render board name
        xPos = width/2 - strlen(boards)/2 * 15 - 50;
        renderStrokeFontString (xPos, ListYPos-i* (boardSize+Boardmargin)+boardSize/2, 0, 0.15 , boards);

        glLoadName(20+i);
        glColor3f(1,1,1);
        glEnable(GL_TEXTURE_2D);
        // Diplay the board texture in small rectangle
        displayBoard (boardTexture[i], width/2 + 25, ListYPos-i* (boardSize+Boardmargin), boardSize, boardSize);
        glDisable(GL_TEXTURE_2D);
    }

    ListYPos = 300;
    glLoadName(5);
    xPos = width/2 - 15*1.5;

    // Draw 'Next' button
    glColor3f(1.0f, 1.0f, 1.0f);
    menuBox(xPos-15, ListYPos-40*numberOfPlayers-120, 95 , 50);

    glColor3f(0.0f, 0.0f, 0.0f);
    renderStrokeFontString (xPos, ListYPos-40*numberOfPlayers-100, 0, 0.15, "Next");

    glPopMatrix();
    glutSwapBuffers();
}

void gamePrefBoardMouse(int button, int status, int x, int y)
{
    if (status == GLUT_DOWN)
    {
        // Increase or decrease numberOfPlayers based on user input
        int item = getPrefMenu (x, y, gamePrefBoardDisplay);
        switch (item)
        {
            case 1  :
                        if(numberOfPlayers < 4)
                            numberOfPlayers ++;
                    break;
            case 2  :
                        if(numberOfPlayers > 2)
                            numberOfPlayers --;
                    break;
            // Goto next view if user press 'Next' button
            case 5  :
                        setGameView (numberOfPlayers, selectedItem);
                    break;

        }
        if(item >= 20)
            selectedItem = item - 20;
    }
    glutPostRedisplay();
}

void gamePrefBoardKeyboard (unsigned char key, int x, int y)
{
    // Goto main menu if user press Esc
    if (key == 27)
        setMainMenuView ();
}

// Funtion which sets the callback funtions required for the view
void setGamePrefBoardView()
{
    // Store the image names in an arrey
    const char images[3][20] = {"ludo1.png","ludo2.jpg","ludo3.jpg"};
    glutDisplayFunc (gamePrefBoardDisplay);
    glutKeyboardFunc (gamePrefBoardKeyboard);
    glutTimerFunc (0, gamePrefBoardTimer, 0);
    glutMouseFunc (gamePrefBoardMouse);
    glutSpecialFunc (NULL);

    // Load all the boared images
    for (int i = 0; i < numberOfBoards; ++i)
    {
        boardTexture[i] =  SOIL_load_OGL_texture ( images[i],
                              SOIL_LOAD_AUTO,
                              SOIL_CREATE_NEW_ID,
                              SOIL_FLAG_INVERT_Y | SOIL_FLAG_MIPMAPS
                              );
    }
}

#endif