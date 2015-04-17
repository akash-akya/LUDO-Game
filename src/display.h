#ifndef DISPLAY_H
#define DISPLAY_H

#define LIMIT 20

extern GLuint texture[10];
extern Game game;
extern GLfloat angle;
extern int player, dice;
extern bool animateDice;
GLfloat translateVectors[13][3] = { 
    {1,0,0},    {0,1,0},    {1,0,0},    {0,-1,0},    {1,0,0},    {0,-1,0},  {-1,0,0},
    {0,-1,0},    {-1,0,0},    {0,1,0},    {-1,0,0},    {0,1,0},    {1,0,0}     
};
const char digits[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };

GLfloat vectorMaxValues[13] = {5,6,2,5,6,2,5,6,2,5,6,1,5};
GLfloat boxPosition[13] = {6,6,2,6,6,2,6,6,2,6,6,1,5};

GLfloat points[][3] = {
        {-1,-1,-1},{-1,1,-1},{1,1,-1},{1,-1,-1},
        {-1,-1,1},{-1,1,1},{1,1,1},{1,-1,1}};

extern GLuint texture[10];
extern GLfloat axis[3];

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
    glPushMatrix();

    glTranslatef(8,8,0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_TEXTURE_2D);
    
    setFace(dice);
    
    glRotatef(angle, axis[0],axis[1],axis[2]);
    glColor3f(1,1,1);
    quad(0,1,2,3,0);
    quad(0,4,7,3,1);
    quad(0,4,5,1,2);
    quad(3,7,6,2,3);
    quad(4,5,6,7,4);
    quad(5,6,2,1,5);

    glDisable(GL_NORMALIZE);
    glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_TEXTURE_2D);

    glPopMatrix();
}

void displayItems(Game &game)
{
    int dPoint,  bReminder;


    for (int i = 0; i < game.numberOfPlayers; ++i){
        GLfloat color[3] = {1,1,1};
        game.player[i].getColor(color);
        glColor3f(color[0],color[1], color[2]);

        for (int j = 0; j < 4; ++j){

            glPushMatrix();

            glRotatef(-90 * i , 0, 0, 1);
            glTranslatef(-7, 1, 0);

            dPoint = game.player[i].items[j];
            if(dPoint >0 && dPoint <= 56){

                int k = 0;
                while(dPoint > 0){

                    if(dPoint > vectorMaxValues[k]){
                        bReminder = boxPosition[k];
                        dPoint = dPoint - vectorMaxValues[k];
                    }else{
                        bReminder = dPoint;
                        dPoint = 0;
                    }

                    glTranslatef(translateVectors[k][0] * bReminder, translateVectors[k][1] * bReminder , 0);
                    k++;
                }

            } else if(dPoint <= 56) {
                // glPushMatrix();
                glTranslatef(2.5, 3.5, 0);
                switch(j){
                    case 0 :    glTranslatef(0,-1,0);
                                break;
                    case 1 :    glTranslatef(-1,0,0); 
                                break;
                    case 2 :    glTranslatef(0,1,0);
                                break;
                    case 3 :    glTranslatef(1,0,0);
                                break;
                }
                // glPopMatrix();
            }

            if(dPoint <= 56){
                glLoadName(i*4+j+1);
                glutSolidCone(0.5, 2.0, 30, 30);
            }
            glPopMatrix();
        }
    }
}

void displayBoard()
{
 
    glEnable(GL_DEPTH_TEST);

    glColor3f(1,1,1);

    glPushMatrix();

    glRotatef(-90 * 0 , 0, 0, 1);
  
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glBegin(GL_QUADS);

    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-7.5,-7.5,0);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(7.5,-7.5,0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(7.5,7.5,0);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-7.5,7.5,0);

    glEnd();

    glDisable(GL_DEPTH_TEST);

    glPopMatrix();

}
void renderStrokeFontString(
        float x,
        float y,
        float z,
        void *font,
        char *string) {

    char *c;
    glPushMatrix();
    glTranslatef(x, y,z);
    glScalef(0.005,0.005,0);

    for (c=string; *c != '\0'; c++) {
        glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, *c);
    }

    glPopMatrix();
}

/*void drawDice(int face){
    int x = face % 3;
    int y = face / 3; 

    GLfloat xCor1,xCor2;
    GLfloat yCor1,yCor2;

    xCor1 = (GLfloat) x * 0.333;
    xCor2 = xCor1 + 0.333;
    yCor1 = (GLfloat) y * 0.5;
    yCor2 = yCor1 + 0.5;

    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glBegin(GL_QUADS);
        glTexCoord2f(xCor1, yCor1);   glVertex3f(8.0,8.0,0.0);
        glTexCoord2f(xCor1, yCor2);   glVertex3f(8.0,10.0,0.0);
        glTexCoord2f(xCor2, yCor2);   glVertex3f(10.0,10.0,0.0);
        glTexCoord2f(xCor2, yCor1);   glVertex3f(10.0,8.0,0.0);
    glEnd();

    glDisable(GL_NORMALIZE);
    glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_TEXTURE_2D);
}*/

void drawMenuBox()
{
    glPushMatrix();
    glColor3f(0.1,0.1,0.1);
    glBegin(GL_POLYGON);
        glVertex3f(-10,10,0);
        glVertex3f(10,10,0);
        glVertex3f(10,8.5,0);
        glVertex3f(-10,8.5,0);
    glEnd();

    char str[] = "Player:";
    char ch[] = "0";
    GLfloat color[3];
    ch[0] =  digits[player+1];
    strcat(str, ch);
    
    game.player[player].getColor(color);
    glColor3fv(color);
    renderStrokeFontString(-5,9,0,GLUT_STROKE_ROMAN,str);
    glColor3f(1,1,1);

    strcpy(str,"Right Click");
    if(dice>0){
        glBindTexture(GL_TEXTURE_2D, texture[2]);
        drawDice();
    }
    else
        renderStrokeFontString(1,9,0,GLUT_STROKE_ROMAN,str);


    glPopMatrix();

}





void crossProduct(GLfloat a[], GLfloat b[], GLfloat c[])
{
    // GLfloat c[3];
    c[0] = a[1] * b[2] - a[2] * b[1];
    c[1] = a[2] * b[0] - a[0] * b[2];
    c[2] = a[0] * b[1] - a[1] * b[0];
}

///////////////////////////////

#endif