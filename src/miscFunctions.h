/*  miscFuntions.h
 *  Contains generic funtions needed for more then
 *  one view. Reduces the code size.
 */

#ifndef MISC_FUNC_H
#define MISC_FUNC_H

#define COLOR_RED 0
#define COLOR_BLUE 1
#define COLOR_YELLOW 2
#define COLOR_GREEN 3

extern GLint width, height;

// Draws a rectangular box from bottom-left point
// co-ordinates and width and height
void menuBox(GLfloat x, GLfloat y, GLfloat width, GLfloat height)
{
    glBegin (GL_POLYGON);
        glVertex3f (x,          y,          0);
        glVertex3f (x+width,    y,          0);
        glVertex3f (x+width,    y+height,   0);
        glVertex3f (x,          y+height,   0);
    glEnd ();
}

// Maps a texture as screen background
void displayBg(int texture)
{
    glEnable(GL_DEPTH_TEST);
    glColor3f(1,1,1);
    glPushMatrix();

    glBindTexture(GL_TEXTURE_2D, texture);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(0,0,0);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(width,0,0);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(width,height,0);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(0,height,0);
    glEnd();

    glDisable(GL_DEPTH_TEST);
    glPopMatrix();
}

// Draws a texture as background for a rectangle specified by
// Bottom-left point coordinates, width and height
void displayBoard(GLint texture, GLfloat x, GLfloat y, GLfloat w, GLfloat h)
{
    glColor3f(1,1,1);
    glPushMatrix();

    // Blend is used to enable transparency.
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D, texture);

    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(x,y,0);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(x+w,y,0);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(x+w,y+h,0);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(x,y+h,0);
    glEnd();

    glDisable (GL_BLEND);

    glPopMatrix();
}

// Renders a text at specified co-ordinate and with specified
// scale parameter
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

    for (c=string; *c != '\0'; c++)
    {
        glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, *c);
    }

    glLineWidth(1.0f);
    glPopMatrix();
}

// Funtion for picking of the menu items.
// Returns the id of the item clicked.
// Requires the display funtion of the respective view as a parameter
int getPrefMenu(int x, int y, void (*disp)(void))
{
  // Get the y co-ordinate from the bottom
  y         = height - y;
  GLint     pawn = 0;
  GLint     hits;
  GLuint    buff[64] = {0};
  GLint     view[4];

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
  glOrtho (0, width, 0, height, 0, 100);

  glMatrixMode(GL_MODELVIEW);
  // Redraw the items
  disp();
  glutSwapBuffers();
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();

  // Get the 'hits' i.e. number items rendered based 'id' and viewport
  hits = glRenderMode(GL_RENDER);

  for (int i = 0; i < hits; i++){
    // Get the top most rendered item id.
    pawn = (GLubyte)buff[i * 4 + 3];
  }

  // Reset the view mode
  glMatrixMode(GL_MODELVIEW);
  return pawn;
}

#endif