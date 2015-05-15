/*  gamePrefView.h
 *  Contains callback funtions specially required for game preference
 *  view (number of players selection).
 */

#ifndef GAME_PREF_H
#define GAME_PREF_H

int             numberOfPlayers = 2;
int             playerColor[4] = {0,1,2,3};
GLfloat         colorRed, colorGreen, colorBlue;
extern GLint    width, height;
extern GLint    mainMenuTexture[5];

void setMainMenuView ();

void gamePrefTimer(int value)
{
    glutPostRedisplay();      // Post re-paint request to activate display()
    glutTimerFunc(refreshMills, gamePrefTimer, 0); // next Timer call milliseconds later
}

void gamePrefDisplay()
{
    // variable for setting the x-axis for text and texture
    int xPos;
    glClear (GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity ();

    glPushMatrix ();
    glColor3f(1,1,1);

    glEnable(GL_TEXTURE_2D);
    displayBg(mainMenuTexture[0]); // Set view background
    glDisable(GL_TEXTURE_2D);

    // Enable 'Blend' feature for transparency
    glEnable (GL_BLEND);
    // Set the blending parameters to use the Alpha channel
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.267, 0.38, 0.039, 0.4);
    // Draw the box behind the menu item text.
    menuBox(500, 70, 400, 600 );

    char ch[] = "Number of players :  ";
    char player[] = "Player 0 color :  ";

    ch[20] = '0' + (unsigned char) numberOfPlayers;

    // find x-axis position based on string length and screen width to make its
    // center aligned. 15 is the approx. each charecter size
    xPos = width/2 - strlen(ch)/2 * 15;
    glColor3f(1,1,1);
    // Draw the text
    renderStrokeFontString (xPos, 600, 0, 0.15, ch);

    // + (Plus) button
    glLoadName(1);
    glColor4f(1,1,1,0.5);
    menuBox( width/2-30,520,30,30);
    glColor3f(0,0,0);
    renderStrokeFontString (width/2-23, 529, 0, 0.15, "+");

    // - (Minus) button
    glLoadName(2);
    glColor4f(1,1,1,0.5);
    menuBox( width/2+30,520,30,30);
    glColor3f(0,0,0);
    renderStrokeFontString (width/2+36, 529, 0, 0.15, "-");
    glDisable(GL_BLEND);

    // Display player name and color for the player based on the number of players
    for (int i = 1; i <= numberOfPlayers; ++i)
    {
        // Set player name using counter variable 'i'
        player[7] = '0' + (unsigned char) i;
        glColor3f(1,1,1);

        xPos = width/2 - strlen(player)/2 * 15;
        // Render player name
        renderStrokeFontString (xPos, 540-i*80, 0, 0.15 , player);

        // If there are only 2 players then second player color must
        // be YELLOW. because 2 player will will have his 'Home0' diagonally
        int val;
        if (i == 2 && numberOfPlayers == 2)
            val = COLOR_YELLOW;
        else
            val = playerColor[i-1];

        // Set the Player color
        switch(val){
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
        menuBox(xPos + strlen(player) * 15 + 20,  540-i*80-20, 50 , 50);
    }

    glLoadName(5);
    xPos = width/2 - 15*2;

    // Draw 'Next' button
    glColor3f(1.0f, 1.0f, 1.0f);
    menuBox(xPos-15, 510-80*numberOfPlayers-100, 100 , 50);

    glColor3f(0.0f, 0.0f, 0.0f);
    renderStrokeFontString (xPos, 510-80*numberOfPlayers-80, 0, 0.15, "Next");

    glPopMatrix();
    glutSwapBuffers();
}



void gamePrefMouse(int button, int status, int x, int y)
{

    if (status == GLUT_DOWN){
        // Increase or decrease numberOfPlayers based on user input
        switch (getPrefMenu(x, y, gamePrefDisplay))
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

            // Goto next view if user press 'Next' button
            case 5  :
                        setGamePrefBoardView ();
                    break;
        }

    }
    glutPostRedisplay();
}

void gamePrefKeyboard (unsigned char key, int x, int y) {
    // Goto main menu if user press Esc
    if (key == 27)
        setMainMenuView ();
}

// Funtion which sets the callback funtions required for the view
void setGamePrefView()
{
    glutDisplayFunc (gamePrefDisplay);
    glutKeyboardFunc (gamePrefKeyboard);
    glutTimerFunc (0, gamePrefTimer, 0);
    glutMouseFunc (gamePrefMouse);
    glutSpecialFunc (NULL);
}

#endif