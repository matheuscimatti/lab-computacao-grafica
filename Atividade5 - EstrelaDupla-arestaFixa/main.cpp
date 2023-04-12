#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define PI 3.141592

GLdouble r1 = 9; //medida do raio do hexadecágono, feito nos exercícios anteriores
GLdouble r2 = 7; //medida inicial do raio da estrela de oito pontas (da origem do plano até a extremidade da ponta da estrela)
GLfloat a = float(r1 * sin(11.25 * (PI/180))); //medida da metade de cada lado do hexadecágono, obtido por cálculos discutidos em aula
GLfloat delta = 0.3; //valor adicional para a medida de cada lado do polígono, afim de se ter a junta de rotação
GLfloat l = 2.0 * a; //tamanho de cada lado do poligono
GLfloat tam = l + delta; //tamanho total de cada lado do polígono (acrescentado do valor de delta para a junta de rotação)
GLfloat b = 2*r2*cos(22.5 * (PI/180)); //calculo utilizado na fórmula de bhaskara para calcular o valor do lado x
GLfloat x = (b - sqrt(pow(b, 2) + 4*pow(l, 2) - 4*pow(r2, 2)))/2; //tamanho do lado x do triangulo formado
GLfloat alfa = acos((pow(l,2)+pow(r2,2)-pow(x,2))/(2*l*r2)) * (180/PI); //medida do ângulo alfa para cada alteração no raio r2
GLfloat beta = 22.5 + alfa; //medida do ângulo beta
GLfloat aux = 0.1; //valor auxiliar para alteração no valor de r2, utilizado na função Timer()
GLfloat angulo = alfa+22.5; //medida do angulo de rotação de cada lado da segunda estrela em relação a primeira

//Função para atualização do viewport para alterações no tamanho da janela (adaptado dos códigos exemplo do professor)
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

//Função base para criar os quadrados (tirada dos slides do professor)
void Square(){
    glBegin(GL_QUADS);
        glVertex2f(-0.5,-0.5);
        glVertex2f(0.5,-0.5);
        glVertex2f(0.5,0.5);
        glVertex2f(-0.5,0.5);
    glEnd();
}

//Função para dimensionar e desenhar os lados vermelhos da figura (utilizado neste exercício apenas para a primeira estrela)
void vermelho(){
    glPushMatrix();
        glScalef(tam,0.3,1.0); //Aplica a escala para o quadrado, afim de gerar como resultado o retângulo utilizado como lado da estrela
        glColor3f(1.0f, 0.0f, 0.0f); //Aplica a cor vermelha
        Square(); //Desenha o "quadrado" baseado em todas as condições estabelecidas
    glPopMatrix();
}

//Função para rotacionar, dimensionar e desenhar os lados azuis da figura (utilizado neste exercício para a segunda estrela)
void azul(int n){
    glPushMatrix();
        if(n%2 == 1) //Condicional para identificar cada lado da ponta da segunda estrela (lado esquerdo ou lado direito) afim de rotacionar corretamente
            glRotatef(angulo,0,0,1); //Rotação do lado da segunda estrela em um angulo predefinido, tendo o lado com centro fixo no centro do lado da primeira estrela
        else
            glRotatef(-angulo,0,0,1);
        glScalef(tam,0.3,1.0);
        glColor3f(0.0f, 0.0f, 1.0f); //Aplica a cor azul
        Square();
    glPopMatrix();
}

//Função para posicionar todos os lados da primeira estrela
void posiciona_prox_primeira(int n){
    if(n%2 == 0){
        glTranslatef(-(l/2),0.0,0.0);
        glRotatef(2*beta,0,0,1);
        glTranslatef((l/2),0.0,0.0);
        vermelho();
    }
    else{
        glTranslatef((l/2),0.0,0.0);
        glRotatef(-2*alfa,0,0,1);
        glTranslatef(-(l/2),0.0,0.0);
        vermelho();
    }
}

//Função para posiocionar os lados da segunda estrela
void posiciona_prox_segunda(int n){
    if(n%2 == 0){
        glTranslatef(0.0,l/2,0.0);
        glRotatef(2*beta,0,0,1);
        glTranslatef(0,-l/2,0);
        azul(n);
    }
    else{
        glTranslatef(0.0,-l/2,0.0);
        glRotatef(-2*alfa,0,0,1);
        glTranslatef(0,l/2,0);
        azul(n);
    }
}

//Função geral para construção da primeira estrela
void Estrela_Oito(void){
    glTranslatef(r2,0.0,0.0); //Translação da distância do raio da estrela em direção ao eixo x
    glRotatef(-alfa,0,0,1); //Rotação de "alfa" graus no sentido horário (rotação negativa)
    glTranslatef(-(l/2),0.0,0.0); //Translação para ajuste do lado na posição correta
    vermelho(); //Desenha o primeiro lado da primeira estrela
    for(int n=0;n<15;n++){
        posiciona_prox_primeira(n);//posiciona e desenha os demais 15 lados a partir da condição (lado direito ou esquerdo que forma cada ponta)
    }
    glFlush();
}

//Função geral para construção da segunda estrela
void Segunda_Estrela(void){
    glTranslatef(r2,0.0,0.0); //Translação da distância do raio da estrela em direção ao eixo x
    glRotatef(-alfa+90,0,0,1); //Rotação de "alfa" graus no sentido horário adicionado de 90 graus para ficar perpendicular ao lado da primeira estrela
    glTranslatef(0.0,l/2,0.0); //Translação para posicionar o ponto médio exatamente no ponto médio da primeira estrela
    azul(1);
    for(int n=0;n<15;n++){
        posiciona_prox_segunda(n);
    }
    glFlush();
}

//Função para construção das duas estrelas
void Estrela_Dupla(void){
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity(); //Carrega matriz identidade
    glClear(GL_COLOR_BUFFER_BIT); //Limpa a tela
    Estrela_Oito(); //Desenha primeira estrela
    glLoadIdentity(); //Carrega matriz identidade
    Segunda_Estrela(); //Desenha segunda estrela
}

//Função para controle da animação
void Timer(int value)
{
    if(r2 <= l || r2 >= r1) //Condição para quando o raio da estrela atingir os valores limite inferior e superior, começar a aumentar ou diminuir
        aux = -aux;

    r2 += aux; //Utilizando a variavel auxiliar para aumentar e diminuir o raio da estrela para a animação
    b = 2*r2*cos(22.5 * (PI/180));                                      //
    x = (b - sqrt(pow(b, 2) + 4*pow(l, 2) - 4*pow(r2, 2)))/2;           //Refazendo todos os cálculos para
    alfa = acos((pow(l,2)+pow(r2,2)-pow(x,2))/(2*l*r2)) * (180/PI);     // ajustar corretamente a estrela
    beta = 22.5 + alfa;                                                 //

    Estrela_Dupla(); //Desenhando as estrelas
    glutTimerFunc(50,Timer, 1); //Função para loop da função de timer
}


int main(){
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(700,700);
    glutCreateWindow("LCG - Atividade 05");
    glutDisplayFunc(Estrela_Dupla);
    glutReshapeFunc(Atualiza_tamanho);
    glutTimerFunc(50, Timer, 1);
    glClearColor(1,1,1,1);
    glutMainLoop();
    return 0;
}
