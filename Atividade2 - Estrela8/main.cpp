#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define PI 3.141592

GLdouble r1 = 9;
GLdouble r2 = 7;
GLfloat a = float(r1 * sin(11.25 * (PI/180)));
GLfloat delta = 0.3;
GLfloat l = 2.0 * a;
GLfloat tam = l + delta;
GLfloat b = 2*r2*cos(22.5 * (PI/180));
GLfloat x = (b - sqrt(pow(b, 2) + 4*pow(l, 2) - 4*pow(r2, 2)))/2;
GLfloat alfa = acos((pow(l,2)+pow(r2,2)-pow(x,2))/(2*l*r2)) * (180/PI);
GLfloat beta = 22.5 + alfa;

void Atualiza_tamanho(int w, int h){
        glViewport(0, 0, w, h);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        if(h==0)h=1;
        if (w <= h)
            gluOrtho2D(-10.0, 10.0, -10.0 * h/w, 10.0 * h/w);
        else
            gluOrtho2D(-10.0 * w/h, 10.0 * w/h, -10.0, 10.0);
}

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
        glScalef(tam,0.3,1.0);
        glColor3f(1.0f, 0.0f, 0.0f);
        Square();
    glPopMatrix();
}

void azul(){
    glPushMatrix();
        glScalef(tam,0.3,1.0);
        glColor3f(0.0f, 0.0f, 1.0f);
        Square();
    glPopMatrix();
}

void posiciona_proximo_estrela(int n){
    if(n%2 == 0){
        glTranslatef(-(l/2),0.0,0.0);
        glRotatef(2*beta,0,0,1);
        glTranslatef((l/2),0.0,0.0);
        azul();
    }
    else{
        glTranslatef((l/2),0.0,0.0);
        glRotatef(-2*alfa,0,0,1);
        glTranslatef(-(l/2),0.0,0.0);
        vermelho();
    }
}

void Estrela_Oito(void){
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT);
    glTranslatef(r2,0.0,0.0);
    glRotatef(-alfa,0,0,1);
    glTranslatef(-(l/2),0.0,0.0);
    vermelho();
    for(int n=0;n<15;n++){
        posiciona_proximo_estrela(n);
    }
    glFlush();
}

int main(){
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(700,700);
    glutCreateWindow("LCG - Atividade 02");
    glutDisplayFunc(Estrela_Oito);
    glutReshapeFunc(Atualiza_tamanho);
    glClearColor(1,1,1,1);
    glutMainLoop();
    return 0;
}
