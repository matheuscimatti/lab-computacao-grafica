

#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#include <GL/glut.h>


#define ESC 27


GLdouble raio = 10; //medida do raio do circulo em que os bonecos ser�o posicionados
GLdouble distancia = raio/2; // medida da dist�ncia entre um boneco e outro (raio * sin(30�), em que sin(30�) = 0.5 = 1/2)

void TamanhoJanela (int w , int h ){

    float ratio =  ((float) w ) / ((float) h ); //  raz�o de aspecto
    glMatrixMode (GL_PROJECTION ); // Matriz de proje��o
    glLoadIdentity (); // inicializa matriz de proje��o com a matriz identidade
    gluPerspective (45.0, ratio , 0.1, 100.0); // Transforma��o Perspectiva
    glMatrixMode (GL_MODELVIEW ); // Seleciona Matriz corrente como Model View
    glViewport (0, 0, w, h ); // Define view port na janela de intera��o
}
void DesenhaQuadrado (){

    glBegin (GL_LINE_LOOP );
        glVertex3f (-1.0, -1.0 , 0.0);
        glVertex3f (-1.0,  1.0 , 0.0);
        glVertex3f ( 1.0,  1.0 , 0.0);
        glVertex3f ( 1.0, -1.0 , 0.0);
    glEnd ();
}

void DesenhaBoneco (){

    // Corpo - esfera de raio 0.75, 20 por 20
    glColor3f (1.0, 1.0 , 1.0); // Cor Branca
    glPushMatrix ();
        glTranslatef (0.0, 0.0 , 0.75);
        glutSolidSphere (0.75, 20 , 20);
    glPopMatrix ();

    // Cabe�a - esfera de raio 0.25, 20 por 20
    glPushMatrix ();
        glTranslatef (0.0, 0.0, 1.75); // posi��o da cabe�a - (0.75 + 0.75: corpo) + (0.25: raio cabe�a)
        glutSolidSphere (0.25, 20, 20);


        // Olhos - esfera de raio 0.05, 10 por 10
        glColor3f (0.0, 0.0, 0.0); // cor preta
        glPushMatrix ();
            glTranslatef (0.0, -0.18, 0.10); // posi��o final dos olhos
            glPushMatrix ();
                glTranslatef (-0.05, 0.0, 0.0);
                glutSolidSphere (0.05, 10, 10); // olho direito
            glPopMatrix ();
            glPushMatrix ();
                glTranslatef (+0.05, 0.0, 0.0);
                glutSolidSphere (0.05, 10, 10); // olho esquerdo
                glRotated (-30,1, 0,0);
                glTranslatef (-0.05, 0.18, 0.15);
                glColor3f (1.0, 0.5, 0.5);
                DesenhaQuadrado ();
            glPopMatrix ();
        glPopMatrix ();

        // Nariz
        glColor3f (1.0, 0.5, 0.5); // cor laranja
        glPushMatrix ();
            glRotatef (90.0, 1.0, 0.0, 0.0); // rota��o com final apontando para -y
            glutSolidCone (0.08, 0.5, 10, 2); // Cone - base,altura, 10 por 2
        glPopMatrix ();
    glPopMatrix ();

}


void DesenhaCena (void)
{
    int i , j ;

    glClearColor (0.0, 0.7, 1.0, 1.0); // limpa a janela de itera��o com a cor azul
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glLoadIdentity ();

    // Configura��o da c�mera
    // posi��o, dire��o da cena, orienta��o up
    //gluLookAt (0,-20.0, 1.0, 0, -4.0 ,1.0,0.0, 0.0,1.0);// altera��o no valor da posi��o (eyeY) para visualiza��o de todos os bonecos na cena
    //Para vizualizar os 12 bonecos em melhor �ngulo, comentar a linha acima e descomentar linha abaixo:
    gluLookAt (0,-20.0, 40.0, 0, -4.0 ,1.0,0.0, 0.0,1.0);

    // Piso - quadrado 200 por 200
    glColor3f (0.0, 0.7, 0.0);
    glBegin (GL_QUADS );
        glVertex3f (-100.0, -100.0, 0.0);
        glVertex3f (-100.0,  100.0, 0.0);
        glVertex3f ( 100.0,  100.0, 0.0);
        glVertex3f ( 100.0, -100.0, 0.0);
    glEnd ();

    //desenhando os bonecos dispostos no circulo
    //baseado nos conceitos do modelo de hexadecagonos visto em aula
    glTranslated(raio, 0.0, 0.0); //transla��o em dire��o ao eixo x no valor do raio do circulo
    glPushMatrix();
        glRotated(-90, 0, 0, 1); //rota��o de 270� no eixo z para o boneco olhar em direcao ao centro do circulo
        DesenhaBoneco(); //desenha o primeiro boneco
    glPopMatrix();
    for(int k=0; k<11; k++){ //la�o de repeti��o para os pr�ximos 11 bonecos
        glRotated(30, 0, 0, 1); //rotaciona em 30� o sistema de referencia do objeto (boneco) no eixo z
        glTranslated(0.0, distancia, 0.0); //transla��o em dire��o ao eixo y no valor da distancia (baseada no raio, conforme dito na declara��o da vari�vel, linha 14)
        glPushMatrix();
            glRotated(-90, 0, 0, 1); //rota��o de 270� no eixo z, mais uma vez para o boneco olhar para o centro do circulo
            DesenhaBoneco();
        glPopMatrix();
    }
    glutSwapBuffers ();
}


void Teclas (unsigned char key , int kx , int ky ){

    if ( key == ESC || key == 'q' || key == 'Q') exit (0);
}





int main (int argc , char **argv ){








    // Inicializa��o
    glutInit (&argc , argv );
    glutInitDisplayMode (GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA );
    glutInitWindowPosition (100, 100 );
    glutInitWindowSize (800, 400 );
    glutCreateWindow (" Boneco de Neve");

    glutReshapeFunc (TamanhoJanela );
    glutDisplayFunc (DesenhaCena );
    glutKeyboardFunc (Teclas );

    glutMainLoop ();
    return 0 ;
}
