#ifndef MISC_FUNC_H
#define MISC_FUNC_H

#define COLOR_RED 0
#define COLOR_BLUE 1
#define COLOR_YELLOW 2
#define COLOR_GREEN 3

extern GLint width, height;

void menuBox(GLfloat x, GLfloat y, GLfloat width, GLfloat height)
{
    glBegin (GL_POLYGON);
        glVertex3f (x,          y,          0);
        glVertex3f (x+width,    y,          0);
        glVertex3f (x+width,    y+height,   0);
        glVertex3f (x,          y+height,   0);
    glEnd ();
}


void displayBg(int texture)
{
 
    glEnable(GL_DEPTH_TEST);
    glColor3f(1,1,1);
    glPushMatrix();
  
    glBindTexture(GL_TEXTURE_2D, texture);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(0,0,0);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(width,0,0);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(width,height,0);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(0,height,0);
    glEnd();

    glDisable(GL_DEPTH_TEST);
    glPopMatrix();

}

void displayBoard(GLint texture, GLfloat x, GLfloat y, GLfloat w, GLfloat h)
{
     glColor3f(1,1,1);
    glPushMatrix();
  
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D, texture);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(x,y,0);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(x+w,y,0);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(x+w,y+h,0);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(x,y+h,0);
    glEnd();
    glDisable (GL_BLEND);

    glPopMatrix();

}

void renderStrokeFontString(
        float x,
        float y,
        float z,
        GLfloat size,
        const char *string) {

    const char *c;
    glPushMatrix();
    glTranslatef(x, y, z);
    glScalef(size,size,0);
    glLineWidth(2.0);

    glRasterPos2f(x, y);

    for (c=string; *c != '\0'; c++) {
        glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, *c);
        // glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
    glLineWidth(1.0f);

    glPopMatrix();
}

#endif