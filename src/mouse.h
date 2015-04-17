#ifndef MOUSE_H
#define MOUSE_H

#include <stdio.h>
int SW = 500;
int SH = 500;

bool viewProspective = false;


void gl_draw (Game game) {

    glClear (GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    glPushMatrix();

    if(viewProspective)
    {
        gluLookAt(0,10,15,
            0,0,0,
            0,1,0);

        glRotatef(-90,1,0,0);
        glTranslatef(0,0,-5);
    }

    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_TEXTURE_2D);
    displayBoard();

    glDisable(GL_NORMALIZE);
    glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_TEXTURE_2D);

    displayItems(game);
    
    glPopMatrix();
    glutSwapBuffers();   


}



#endif