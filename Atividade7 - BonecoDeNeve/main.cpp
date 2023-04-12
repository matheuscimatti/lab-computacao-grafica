

#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#include <GL/glut.h>


#define ESC 27


void TamanhoJanela (int w , int h ){

    float ratio =  ((float) w ) / ((float) h ); //  razão de aspecto
    glMatrixMode (GL_PROJECTION ); // Matriz de projeção
    glLoadIdentity (); // inicializa matriz de projeção com a matriz identidade
    gluPerspective (45.0, ratio , 0.1, 100.0); // Transformação Perspectiva
    glMatrixMode (GL_MODELVIEW ); // Seleciona Matriz corrente como Model View
    glViewport (0, 0, w, h ); // Define view port na janela de interação
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

    // Cabeça - esfera de raio 0.25, 20 por 20
    glPushMatrix ();
        glTranslatef (0.0, 0.0, 1.75); // posição da cabeça - (0.75 + 0.75: corpo) + (0.25: raio cabeça)
        glutSolidSphere (0.25, 20, 20);


        // Olhos - esfera de raio 0.05, 10 por 10
        glColor3f (0.0, 0.0, 0.0); // cor preta
        glPushMatrix ();
            glTranslatef (0.0, -0.18, 0.10); // posição final dos olhos
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
            glRotatef (90.0, 1.0, 0.0, 0.0); // rotação com final apontando para -y
            glutSolidCone (0.08, 0.5, 10, 2); // Cone - base,altura, 10 por 2
        glPopMatrix ();
    glPopMatrix ();

}


void DesenhaCena (void)
{
    int i , j ;

    glClearColor (0.0, 0.7, 1.0, 1.0); // limpa a janela de iteração com a cor azul
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glLoadIdentity ();

    // Configuração da câmera
    // posição, direção da cena, orientação up
    gluLookAt (0,-5.0, 1.0, 0, -4.0 ,1.0,0.0, 0.0,1.0);// alteração no valor da posição (eyeY) para visualização de todos os bonecos na cena


    // Piso - quadrado 200 por 200
    glColor3f (0.0, 0.7, 0.0);
    glBegin (GL_QUADS );
        glVertex3f (-100.0, -100.0, 0.0);
        glVertex3f (-100.0,  100.0, 0.0);
        glVertex3f ( 100.0,  100.0, 0.0);
        glVertex3f ( 100.0, -100.0, 0.0);
    glEnd ();

    DesenhaBoneco(); //desenha o primeiro boneco
    glutSwapBuffers ();
}


void Teclas (unsigned char key , int kx , int ky ){

    if ( key == ESC || key == 'q' || key == 'Q') exit (0);
}





int main (int argc , char **argv ){








    // Inicialização
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
