#include <GL/glut.h>
 
void renderStrokeFontString(
        float x,
        float y,
        float z,
        void *font,
        char *string) {

    char *c;
    glPushMatrix();
    glTranslatef(x, y,z);

    for (c=string; *c != '\0'; c++) {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, *c);
    }

    glPopMatrix();
}

void display (void) {

    char name[] = "Akash hiremath";
    glClear (GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT);
    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glColor3f(1,1,1);
    glTranslatef(10,50,0);
    glScalef(0.2,0.2,0);
    renderStrokeFontString(0,0,0,GLUT_BITMAP_HELVETICA_18,name);
    // glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN ,'3');
    glutSwapBuffers();
    glPopMatrix();


}

int main(int argc, char **argv) {
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInit (&argc, argv); /* Initialise OpenGL */
    glutInitWindowSize (500, 500); /* Set the window size */
    glutInitWindowPosition (100, 100); /* Set the window position */
    glutCreateWindow ("ex5"); /* Create the window */

    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    glOrtho(0,500,0,500,0,500);  

    glMatrixMode (GL_MODELVIEW);

    glutDisplayFunc (display); /* Register the "display" function */
    glutMainLoop (); /* Enter the OpenGL main loop */
    return 0;
}
