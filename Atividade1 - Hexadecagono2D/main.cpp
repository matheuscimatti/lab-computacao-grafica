#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define PI 3.141592

GLdouble raio = 0.5;
GLfloat a = float(raio * sin(11.25 * (PI/180)));
GLfloat delta = 0.03;
GLfloat tam = (2.0*a)+delta;

void Square(){
    glBegin(GL_QUADS);
        glVertex2f(-0.5,-0.5);
        glVertex2f(0.5,-0.5);
        glVertex2f(0.5,0.5);
        glVertex2f(-0.5,0.5);
    glEnd();
}

void vermelho(){
    glPushMatrix();
        glScalef(tam,0.03,1.0);
        glColor3f(1.0f, 0.0f, 0.0f);
        Square();
    glPopMatrix();
}

void azul(){
    glPushMatrix();
        glScalef(tam,0.03,1.0);
        glColor3f(0.0f, 0.0f, 1.0f);
        Square();
    glPopMatrix();
}

void posiciona_proximo(){
    glTranslatef(a,0.0,0.0);
    glRotatef(22.5,0,0,1);
    glTranslatef(a,0.0,0.0);
}

void Hexadecagono(void){
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT);
    glTranslatef(raio,0.0,0.0);
    glRotatef(101.25,0,0,1);
    glTranslatef(a,0.0,0.0);
    vermelho();
    for(int i=0;i<15;i++){
        posiciona_proximo();
        if(i%2 == 0)
            azul();
        else
            vermelho();
    }
	glFlush();
}

int main(){
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(700,700);
    glutCreateWindow("LCG - Atividade 01");
    glutDisplayFunc(Hexadecagono);
    glClearColor(1,1,1,1);
    glutMainLoop();
    return 0;
}
