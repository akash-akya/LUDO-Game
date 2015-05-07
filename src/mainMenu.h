#ifndef MAIN_MENU_H
#define MAIN_MENU_H

const char menuItems[NUM_OF_MENU_ITEMS][30] = { "New Game", "Help", "About", "Exit"}; 
extern GLint height, width;
extern GLint mainMenuTexture[5];

void mainMenuTimer(int value)
{
    glutPostRedisplay();      // Post re-paint request to activate display()
    glutTimerFunc(refreshMills, mainMenuTimer, 0); // next Timer call milliseconds later
}

void mainMenuDisplay()
{
    glClear (GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity ();

    glPushMatrix ();

    glEnable(GL_TEXTURE_2D);
    displayBg(mainMenuTexture[0]);
    glDisable(GL_TEXTURE_2D);

    for (int i = 0; i < NUM_OF_MENU_ITEMS; ++i){
        int xPos = width/2 - strlen(menuItems[i])/2 * 18;
        
        glColor3f(1,1,1);
        glEnable(GL_TEXTURE_2D);
        glLoadName(i+1);
        displayBoard (mainMenuTexture[1], width/2 - 200 , 600 -i*80-30, 400, 120);
        glDisable(GL_TEXTURE_2D);

        glColor3f(1,1,1);
        renderStrokeFontString(xPos, 600 -i*80+15, 0.0, 0.18, menuItems[i]); 
    }

    glPopMatrix();
    glutSwapBuffers();
}


int getMenu(int x, int y)
{

  y = height - y;
  // cout << "width : " << width <<  " height : " << height  << endl;
  // cout << "x : " << x << " y : " << y << endl;
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
  mainMenuDisplay();
  glutSwapBuffers();
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

void mainMenuMouse(int button, int status, int x, int y)
{
    if (status == GLUT_DOWN){
        // cout << "value : " << getMenu (x, y) << endl;
        switch(getMenu(x, y))
        {
          // case 1 :  setGameView (); break;
          case 1 :  setGamePrefView (); break;
          case 2 :  setView(mainMenuTexture[4]); break;
          case 3 :  setView(mainMenuTexture[3]); break;
          case 4 :  exit(0); break;
        }
    }
}

void mainMenuKeyboard (unsigned char key, int x, int y) {

    if (key == 27) 
        exit (0); 
}

void reshape(GLint swidth, GLint sheight)
{
    width = swidth; 
    height = sheight; 
    
    glViewport(0,0,width,height);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    // glOrtho (0, 1360, 0, 768, 0, 100);

    glOrtho (0, width, 0, height, 0, 100);
    glMatrixMode (GL_MODELVIEW);

    // cout << "width " << width << " height " << height << endl;
}

void setMainMenuView()
{
    glutTimerFunc (0, mainMenuTimer, 0); 
    glutKeyboardFunc (mainMenuKeyboard);
    glutDisplayFunc (mainMenuDisplay);
    glutMouseFunc (mainMenuMouse);
    glutReshapeFunc(reshape);


}

#endif