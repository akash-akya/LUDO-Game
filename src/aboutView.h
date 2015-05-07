#ifndef ABOUT_H
#define ABOUT_H

extern GLint width, height;
extern GLint mainMenuTexture[5];
int viewTexture;

void setMainMenuView(void);


void aboutTimer(int value)
{
    glutPostRedisplay();      // Post re-paint request to activate display()
    glutTimerFunc(refreshMills, aboutTimer, 0); // next Timer call milliseconds later
}

/*  
 *  Draws the box based on x & y and width and height. (x,y) is left most top corner  
 */

void aboutDisplay()
{
    glClear (GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity ();

    glPushMatrix ();
    glColor3f(1,1,1);

    glEnable(GL_TEXTURE_2D);
    displayBg(viewTexture);
    glDisable(GL_TEXTURE_2D); 

    glPopMatrix();
    glutSwapBuffers();
   
}

void aboutKeyboard (unsigned char key, int x, int y) {

    if (key == 27) 
        setMainMenuView ();

}

void setView(int tex)
{
    viewTexture = tex;

    glutDisplayFunc (aboutDisplay);
    glutKeyboardFunc (aboutKeyboard);
    glutTimerFunc (0, aboutTimer, 0); 
    glutMouseFunc (NULL);
    glutSpecialFunc (NULL);
    // glutReshapeFunc(reshape);


    // glMatrixMode (GL_PROJECTION);
    // glLoadIdentity ();
    // glOrtho (-100, 100, -100, 100, -100, 100);
    // glMatrixMode (GL_MODELVIEW);
}



#endif