/*  mainMenu.h
 *  Contains callback funtions specially required for the view
 *  MainMenu.
 */


#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#define NUM_OF_MENU_ITEMS 4

// Menu items text
const char menuItems[NUM_OF_MENU_ITEMS][30] = { "New Game", "Help",
                                                "About",    "Exit"};
extern GLint height, width;
extern GLint mainMenuTexture[5];

void mainMenuTimer(int value)
{
    glutPostRedisplay();     // Post re-paint request to activate display()
    glutTimerFunc(refreshMills, mainMenuTimer, 0); // next Timer call milliseconds later
}

void mainMenuDisplay()
{
    glClear (GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity ();

    glPushMatrix ();
    glLoadName(0);

    glEnable(GL_TEXTURE_2D);
    displayBg(mainMenuTexture[0]); // Set menu-view background
    glDisable(GL_TEXTURE_2D);

    for (int i = 0; i < NUM_OF_MENU_ITEMS; ++i)
    {
        // get the middle position along x-axis
        int xPos = width/2 - strlen(menuItems[i])/2 * 18;
        glLoadName(i+1);

        glColor3f(1,1,1);
        glEnable(GL_TEXTURE_2D);
        // Set the 'wodden-board' as menu item bakcground
        displayBoard (mainMenuTexture[1], width/2-200 , 600-i*120-30, 400, 100);
        glDisable(GL_TEXTURE_2D);

        glColor3f(1,1,1);
        // Draw the menu item text
        renderStrokeFontString(xPos, 600-i*120+7, 0.0, 0.18, menuItems[i]);
    }

    glPopMatrix();
    glutSwapBuffers();
}


// Mouse Function
void mainMenuMouse(int button, int status, int x, int y)
{
    if (status == GLUT_DOWN){
        switch(getPrefMenu(x, y, mainMenuDisplay))
        {
          // User pressed 'New Game' menu item
          case 1 :  setGamePrefView (); break;
          // User pressed 'Help' menu item
          case 2 :  setView(mainMenuTexture[4]); break;
          // User pressed 'About' menu item
          case 3 :  setView(mainMenuTexture[3]); break;
          // User pressed 'Exit' menu item
          case 4 :  exit(0); break;
        }
    }
}

void mainMenuKeyboard (unsigned char key, int x, int y) {

    // Terminate when user press 'Esc' key
    if (key == 27)
        exit (0);
}

//  Reshape funtion.
void reshape(GLint swidth, GLint sheight)
{
    // Store the screen width and height
    width = swidth;
    height = sheight;

    glViewport(0,0,width,height);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    // Set the ortho to match screen resolution
    glOrtho (0, width, 0, height, 0, 100);
    glMatrixMode (GL_MODELVIEW);

}

// Funtion which sets the callback funtions required for the view
void setMainMenuView()
{
    glutTimerFunc (0, mainMenuTimer, 0);
    glutKeyboardFunc (mainMenuKeyboard);
    glutDisplayFunc (mainMenuDisplay);
    glutMouseFunc (mainMenuMouse);
    glutReshapeFunc(reshape);

}

#endif