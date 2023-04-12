#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define PI 3.141592

GLdouble raio = 520;
GLfloat a = float(raio * sin(11.25 * (PI/180)));
GLfloat delta = 10;
GLfloat tam = (2.0*a)+delta;

GLfloat angle, fAspect;

void Cubo(){
	glBegin(GL_LINE_LOOP);
		glNormal3f(0.0, 0.0, 1.0);
		glVertex3f(0.5, 0.5, 0.5);
		glVertex3f(-0.5, 0.5, 0.5);
		glVertex3f(-0.5, -0.5, 0.5);
		glVertex3f(0.5, -0.5, 0.5);
	glEnd();


	glBegin(GL_LINE_LOOP);
		glNormal3f(0.0, 0.0, -1.0);
		glVertex3f(0.5, 0.5, -0.5);
		glVertex3f(0.5, -0.5, -0.5);
		glVertex3f(-0.5, -0.5, -0.5);
		glVertex3f(-0.5, 0.5, -0.5);
	glEnd();

	glBegin(GL_LINE_LOOP);
		glNormal3f(-1.0, 0.0, 0.0);
		glVertex3f(-0.5, 0.5, 0.5);
		glVertex3f(-0.5, 0.5, -0.5);
		glVertex3f(-0.5, -0.5, -0.5);
		glVertex3f(-0.5, -0.5, 0.5);
	glEnd();

	glBegin(GL_LINE_LOOP);
		glNormal3f(1.0, 0.0, 0.0);
		glVertex3f(0.5, 0.5, 0.5);
		glVertex3f(0.5, -0.5, 0.5);
		glVertex3f(0.5, -0.5, -0.5);
		glVertex3f(0.5, 0.5, -0.5);
	glEnd();
	glBegin(GL_LINE_LOOP);
		glNormal3f(0.0, 1.0, 0.0);
		glVertex3f(-0.5, 0.5, -0.5);
		glVertex3f(-0.5, 0.5, 0.5);
		glVertex3f(0.5, 0.5, 0.5);
		glVertex3f(0.5, 0.5, -0.5);
	glEnd();
	glBegin(GL_LINE_LOOP);
		glNormal3f(0.0, -1.0, 0.0);
		glVertex3f(-0.5, -0.5, -0.5);
		glVertex3f(0.5, -0.5, -0.5);
		glVertex3f(0.5, -0.5, 0.5);
		glVertex3f(-0.5, -0.5, 0.5);
	glEnd();

}

void vermelho(){
    glPushMatrix();
        glScalef(tam,delta,delta);
        glColor3f(1.0f, 0.0f, 0.0f);
        Cubo();
    glPopMatrix();
}

void azul(){
    glPushMatrix();
        glScalef(tam,delta,delta);
        glColor3f(0.0f, 0.0f, 1.0f);
        Cubo();
    glPopMatrix();
}

void posiciona_proximo(){
    glTranslatef(a,0.0,0.0);
    glRotatef(22.5,0,0,1);
    glTranslatef(a,0.0,0.0);
}

void Hexadecagono()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1.0f, 0.0f, 0.0f);
    glTranslatef(raio, 0.0, 0.0);
    glRotatef(101.25,0,0,1);
    glTranslated(a, 0.0, 0.0);
    vermelho();
    for(int i = 0;i<15;i++){
        posiciona_proximo();
        if(i%2 == 0)
            azul();
        else
            vermelho();
    }
    glFlush();
	glutSwapBuffers();
 }

void ParametrosVisualizacao()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(angle,fAspect,350,750);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0,0,600, 0,0,0, 0,1,0);
}

void Atualiza_tamanho(GLsizei w, GLsizei h)
{
	if ( h == 0 ) h = 1;
	glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if(h==0)h=1;
    if (w <= h)
        gluOrtho2D(-700.0, 700.0, -700.0 * h/w, 700.0 * h/w);
    else
        gluOrtho2D(-700.0 * w/h, 700.0 * w/h, -700.0, 700.0);

	fAspect = (GLfloat)w/(GLfloat)h;
	ParametrosVisualizacao();
}

int main()
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(700,700);
	glutCreateWindow("LCG - Atividade 06");
	glutDisplayFunc(Hexadecagono);
	glutReshapeFunc(Atualiza_tamanho);
	glClearColor(1, 1, 1, 1);
    angle=90;
	glutMainLoop();
	return 0;
}
