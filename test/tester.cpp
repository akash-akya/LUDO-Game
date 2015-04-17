#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include <time.h>
#include <SOIL.h>

#define PI 22/7
#define LIMIT 20

using namespace std;

GLfloat points[][3] = {
        {-10,-10,-10},{-10,10,-10},{10,10,-10},{10,-10,-10},
        {-10,-10,10},{-10,10,10},{10,10,10},{10,-10,10}};

GLfloat angle = 0.0f, angleDiff = 1.0f;
GLuint texture;
GLfloat sangle = 90.0f;
GLfloat axis[3] = {0.0f, 0.0f, 0.0f};
int refreshMills = 20;

void Timer(int value) {
    glutPostRedisplay();      // Post re-paint request to activate display()
    glutTimerFunc(refreshMills, Timer, 0); // next Timer call milliseconds later

    if(angleDiff >= 0)
        angle =  angle + 50 * (0 + angleDiff) ;// * angleDiff;

    if(angle > 360){
        angleDiff = sin(sangle*PI/180.0);
        angle = 0;
        if(sangle < 180)
            sangle+=5;
    }
   
}

void setFace(int diceVal)
{
    switch(diceVal)
    {
        case 1 :    glRotatef(180,1,0,0);       break ; 
        case 2 :    glRotatef(-90,1,0,0);       break ; 
        case 3 :    glRotatef(90,0,1,0);        break ; 
        case 4 :    glRotatef(-90,0,1,0);       break ; 
        case 5 :                                break ; 
        case 6 :    glRotatef(90,1,0,0);        break ; 
    }
}

void quad(GLint v1,GLint v2,GLint v3,GLint v4, int face){
    int x = face % 3;
    int y = face / 3; 

    GLfloat xCor1,xCor2;
    GLfloat yCor1,yCor2;

    xCor1 = (GLfloat) x * 0.333;
    xCor2 = xCor1 + 0.333;
    yCor1 = (GLfloat) y * 0.5;
    yCor2 = yCor1 + 0.5;

    glBegin(GL_QUADS);
        glTexCoord2f(xCor1, yCor1);   glVertex3fv(points[v1]);
        glTexCoord2f(xCor1, yCor2);   glVertex3fv(points[v2]);
        glTexCoord2f(xCor2, yCor2);   glVertex3fv(points[v3]);
        glTexCoord2f(xCor2, yCor1);   glVertex3fv(points[v4]);
    glEnd();

}

void drawDice()
{
    glColor3f(1,1,1);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);

    quad(0,1,2,3,0);

    quad(0,4,7,3,1);

    quad(0,4,5,1,2);

    quad(3,7,6,2,3);

    quad(4,5,6,7,4);

    quad(5,6,2,1,5);

    glDisable(GL_TEXTURE_2D);

}



   
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   // Clear the color buffer
    glMatrixMode(GL_MODELVIEW);     // To operate on Model-View matrix
    glLoadIdentity();               // Reset the model-view matrix
 
    glPushMatrix(); 

    setFace(2);

    glRotatef(angle, axis[0],axis[1],axis[2]);
    
    drawDice();
    
    glPopMatrix();   
    glFlush();


}



void init() {
    glClearColor(0, 0, 0, 0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-LIMIT, LIMIT, -LIMIT, LIMIT, -LIMIT, LIMIT);
    glColor3f(1,1,1);
    glEnable(GL_DEPTH_TEST);

    srand(time(NULL));
    for (int i=0 ; i <2 ; i++)
        axis[i] = ((rand()%200)-100)/100.0;

}

void keyboard(unsigned char button, int status, int x){
    if(button == 'q')
        exit(0);
    
}

void loadTexture() 
{
    texture = SOIL_load_OGL_texture 
    (
        "dice.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(40, 40);
    glutCreateWindow("Square");
    glutKeyboardFunc(keyboard);
    loadTexture();
    glutDisplayFunc(display);
    glutTimerFunc(0, Timer, 0); 
    init();
    glutMainLoop();
}