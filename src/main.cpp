/*
Ajuste de velocidade implementado.
Tamanho da tela responsivo.
Game over e reset.
Próxima peça no canto da tela.
Função Hold.
Entre outras.
*/

//RAFAEL CARNEIRO PREGARDIER

#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include "gl_canvas2d.h"
#include "auxiliar.h"

#define X_INICIO screenWidth/2-200
#define X_FIM screenWidth/2+200
#define Y_INICIO screenHeight/2-400
#define Y_FIM screenHeight/2+400
#define TAMANHO_BLOCO 40
#define LINHAS 20
#define COLUNAS 10
#define ALTURA_PECA 4
#define COMPRIMENTO_PECA 6
#define metade_tela_horizontal screenWidth/2
#define metade_tela_vertical screenHeight/2
#define vetor_de_cores 3
#define X_PAINEL_INICIO screenWidth/2-400
#define X_PAINEL_FIM screenWidth/2+400
#define Y_PAINEL_INICIO screenHeight/2+200
#define Y_PAINEL_FIM screenHeight/2+500

//variaveis globais
int screenWidth = 800, screenHeight = 700; //largura e altura inicial da tela. Alteram com o redimensionamento de tela.
int mouseX, mouseY; //variaveis globais do mouse para poder exibir dentro da render().


clock_t lastDrop;


int peca[ALTURA_PECA][COMPRIMENTO_PECA];
int hold_peca[ALTURA_PECA][COMPRIMENTO_PECA];
int peca_rotacao[LINHAS][COLUNAS];
int tabela[LINHAS][COLUNAS];
int copia_tabela[LINHAS][COLUNAS];


float vermelho[vetor_de_cores]={0.5, 0.5, 0.5};
float verde[vetor_de_cores]={0.5, 0.5, 0.5};
float azul[vetor_de_cores]={0.5, 0.5, 0.5};


double velocidade=0.99;


int peca_escolhida=0;
int um_segundo=1;
int auxiliar;
int pontuacao;
int peca_proxima=0;
int hold;
int cont_hold=0;
int cont_rotacao=0;
int index_menor=20;
int index2_menor=10;
int cont_velocidade=1;
int cont_linhas=0;
int pontuacao_maxima=0;


bool bateu_embaixo;
bool bateu_esquerda;
bool bateu_direita;
bool bateu_peca;
bool parar=FALSE;
bool sortear_peca;
bool holding=FALSE;
bool apertou_holding=FALSE;
bool copiada=FALSE;
bool menu=TRUE;
bool ajuda=FALSE;


void Painel(){ //Função que desenha a logo "TETRIS".

    CV::color(1,0,0);
    CV::rectFill(X_PAINEL_INICIO,              Y_PAINEL_INICIO,
                 X_PAINEL_INICIO+TAMANHO_BLOCO, Y_PAINEL_INICIO+(5*TAMANHO_BLOCO));

    CV::color(1,0,0);
    CV::rectFill((-1*TAMANHO_BLOCO)+X_PAINEL_INICIO,              (4*TAMANHO_BLOCO)+Y_PAINEL_INICIO,
                     TAMANHO_BLOCO+X_PAINEL_INICIO+TAMANHO_BLOCO, (4*TAMANHO_BLOCO)+Y_PAINEL_INICIO+(TAMANHO_BLOCO));

    CV::color(0,1,0);
    CV::rectFill(3*TAMANHO_BLOCO+X_PAINEL_INICIO,              Y_PAINEL_INICIO,
                 3*TAMANHO_BLOCO+X_PAINEL_INICIO+TAMANHO_BLOCO, Y_PAINEL_INICIO+(5*TAMANHO_BLOCO));

    CV::color(0,1,0);
    CV::rectFill(3*TAMANHO_BLOCO+X_PAINEL_INICIO, 4*TAMANHO_BLOCO+Y_PAINEL_INICIO,
                 5*TAMANHO_BLOCO+X_PAINEL_INICIO+TAMANHO_BLOCO, 4*TAMANHO_BLOCO+Y_PAINEL_INICIO+(TAMANHO_BLOCO));

    CV::color(0,1,0);
    CV::rectFill(3*TAMANHO_BLOCO+X_PAINEL_INICIO, 2*TAMANHO_BLOCO+Y_PAINEL_INICIO,
                 4*TAMANHO_BLOCO+X_PAINEL_INICIO+TAMANHO_BLOCO, 2*TAMANHO_BLOCO+Y_PAINEL_INICIO+(TAMANHO_BLOCO));

    CV::color(0,1,0);
    CV::rectFill(3*TAMANHO_BLOCO+X_PAINEL_INICIO, 0*TAMANHO_BLOCO+Y_PAINEL_INICIO,
                 5*TAMANHO_BLOCO+X_PAINEL_INICIO+TAMANHO_BLOCO, 0*TAMANHO_BLOCO+Y_PAINEL_INICIO+(TAMANHO_BLOCO));

    CV::color(0,0,1);
    CV::rectFill(8*TAMANHO_BLOCO+X_PAINEL_INICIO,              Y_PAINEL_INICIO,
                 8*TAMANHO_BLOCO+X_PAINEL_INICIO+TAMANHO_BLOCO, Y_PAINEL_INICIO+(5*TAMANHO_BLOCO));

    CV::color(0,0,1);
    CV::rectFill((7*TAMANHO_BLOCO)+X_PAINEL_INICIO,              (4*TAMANHO_BLOCO)+Y_PAINEL_INICIO,
                  9*TAMANHO_BLOCO+X_PAINEL_INICIO+TAMANHO_BLOCO, (4*TAMANHO_BLOCO)+Y_PAINEL_INICIO+(TAMANHO_BLOCO));

    CV::color(0,1,1);
    CV::rectFill(11*TAMANHO_BLOCO+X_PAINEL_INICIO,              Y_PAINEL_INICIO,
                 11*TAMANHO_BLOCO+X_PAINEL_INICIO+TAMANHO_BLOCO, Y_PAINEL_INICIO+(5*TAMANHO_BLOCO));

    CV::color(0,1,1);
    CV::rectFill((11*TAMANHO_BLOCO)+X_PAINEL_INICIO,              (4*TAMANHO_BLOCO)+Y_PAINEL_INICIO,
                  13*TAMANHO_BLOCO+X_PAINEL_INICIO+TAMANHO_BLOCO, (4*TAMANHO_BLOCO)+Y_PAINEL_INICIO+(TAMANHO_BLOCO));

    CV::color(0,1,1);
    CV::rectFill(13*TAMANHO_BLOCO+X_PAINEL_INICIO,              Y_PAINEL_INICIO+4*TAMANHO_BLOCO,
                 13*TAMANHO_BLOCO+X_PAINEL_INICIO+TAMANHO_BLOCO, Y_PAINEL_INICIO+(2*TAMANHO_BLOCO));

    CV::color(0,1,1);
    CV::rectFill(12*TAMANHO_BLOCO+X_PAINEL_INICIO,              Y_PAINEL_INICIO+2*TAMANHO_BLOCO,
                 12*TAMANHO_BLOCO+X_PAINEL_INICIO+TAMANHO_BLOCO, Y_PAINEL_INICIO+(3*TAMANHO_BLOCO));

    CV::color(0,1,1);
    CV::rectFill(12*TAMANHO_BLOCO+X_PAINEL_INICIO,              Y_PAINEL_INICIO+1*TAMANHO_BLOCO,
                 12*TAMANHO_BLOCO+X_PAINEL_INICIO+TAMANHO_BLOCO, Y_PAINEL_INICIO+(2*TAMANHO_BLOCO));

    CV::color(0,1,1);
    CV::rectFill(13*TAMANHO_BLOCO+X_PAINEL_INICIO,              Y_PAINEL_INICIO+0*TAMANHO_BLOCO,
                 13*TAMANHO_BLOCO+X_PAINEL_INICIO+TAMANHO_BLOCO, Y_PAINEL_INICIO+(1*TAMANHO_BLOCO));

    CV::color(1,0.5,0);
    CV::rectFill(16*TAMANHO_BLOCO+X_PAINEL_INICIO,              Y_PAINEL_INICIO,
                 16*TAMANHO_BLOCO+X_PAINEL_INICIO+TAMANHO_BLOCO, Y_PAINEL_INICIO+(5*TAMANHO_BLOCO));

    CV::color(1,0.5,0);
    CV::rectFill((15*TAMANHO_BLOCO)+X_PAINEL_INICIO,              (4*TAMANHO_BLOCO)+Y_PAINEL_INICIO,
                  17*TAMANHO_BLOCO+X_PAINEL_INICIO+TAMANHO_BLOCO, (4*TAMANHO_BLOCO)+Y_PAINEL_INICIO+(TAMANHO_BLOCO));

    CV::color(1,0.5,0);
    CV::rectFill((15*TAMANHO_BLOCO)+X_PAINEL_INICIO,              (0*TAMANHO_BLOCO)+Y_PAINEL_INICIO,
                  17*TAMANHO_BLOCO+X_PAINEL_INICIO+TAMANHO_BLOCO, (0*TAMANHO_BLOCO)+Y_PAINEL_INICIO+(TAMANHO_BLOCO));

    CV::color(1,0,1);
    CV::rectFill(19*TAMANHO_BLOCO+X_PAINEL_INICIO,              Y_PAINEL_INICIO+2*TAMANHO_BLOCO,
                 19*TAMANHO_BLOCO+X_PAINEL_INICIO+TAMANHO_BLOCO, Y_PAINEL_INICIO+(5*TAMANHO_BLOCO));

    CV::color(1,0,1);
    CV::rectFill((19*TAMANHO_BLOCO)+X_PAINEL_INICIO,              (4*TAMANHO_BLOCO)+Y_PAINEL_INICIO,
                  21*TAMANHO_BLOCO+X_PAINEL_INICIO+TAMANHO_BLOCO, (4*TAMANHO_BLOCO)+Y_PAINEL_INICIO+(TAMANHO_BLOCO));

    CV::color(1,0,1);
    CV::rectFill((19*TAMANHO_BLOCO)+X_PAINEL_INICIO,              (2*TAMANHO_BLOCO)+Y_PAINEL_INICIO,
                  21*TAMANHO_BLOCO+X_PAINEL_INICIO+TAMANHO_BLOCO, (2*TAMANHO_BLOCO)+Y_PAINEL_INICIO+(TAMANHO_BLOCO));

    CV::color(1,0,1);
    CV::rectFill((19*TAMANHO_BLOCO)+X_PAINEL_INICIO,              (0*TAMANHO_BLOCO)+Y_PAINEL_INICIO,
                  21*TAMANHO_BLOCO+X_PAINEL_INICIO+TAMANHO_BLOCO, (0*TAMANHO_BLOCO)+Y_PAINEL_INICIO+(TAMANHO_BLOCO));

    CV::color(1,0,1);
    CV::rectFill(21*TAMANHO_BLOCO+X_PAINEL_INICIO,              Y_PAINEL_INICIO+0*TAMANHO_BLOCO,
                 21*TAMANHO_BLOCO+X_PAINEL_INICIO+TAMANHO_BLOCO, Y_PAINEL_INICIO+(2*TAMANHO_BLOCO));

}

void Menu_do_jogo(){ //Função que exibe o menu.
    Painel();

    CV::color(255,255,255);
    CV::rect(X_INICIO, Y_INICIO+(5*TAMANHO_BLOCO), X_FIM, Y_FIM-(6*TAMANHO_BLOCO));

    CV::color(1,1,1);
    CV::text(metade_tela_horizontal-(CV::getTextWidth("WELCOME TO TETRIS", GLUT_BITMAP_TIMES_ROMAN_24)/2),
             metade_tela_vertical-(CV::getBitmapHeight(GLUT_BITMAP_TIMES_ROMAN_24)/2)+(2*TAMANHO_BLOCO),
             "WELCOME TO TETRIS",
             GLUT_BITMAP_TIMES_ROMAN_24);

    CV::color(vermelho[0],verde[0],azul[0]);
    CV::rectFill(metade_tela_horizontal-(2*TAMANHO_BLOCO), metade_tela_vertical-(0.5*TAMANHO_BLOCO),
                 metade_tela_horizontal+(2*TAMANHO_BLOCO), metade_tela_vertical+(0.5*TAMANHO_BLOCO));

    CV::color(0,0,0);
    CV::text(metade_tela_horizontal-(CV::getTextWidth("PLAY", GLUT_BITMAP_HELVETICA_18)/2),
             metade_tela_vertical-(CV::getBitmapHeight(GLUT_BITMAP_HELVETICA_18)/2),
             "PLAY",
             GLUT_BITMAP_HELVETICA_18);

    if(mouseX>=metade_tela_horizontal-(2*TAMANHO_BLOCO) && mouseX<=metade_tela_horizontal+(2*TAMANHO_BLOCO)
       && mouseY>=metade_tela_vertical-(0.5*TAMANHO_BLOCO) && mouseY<=metade_tela_vertical+(0.5*TAMANHO_BLOCO)){
        vermelho[0]=1;
        verde[0]=1;
        azul[0]=1;
    }
    else{
        vermelho[0]=0.5;
        verde[0]=0.5;
        azul[0]=0.5;
    }

    CV::color(vermelho[1],verde[1],azul[1]);
    CV::rectFill(metade_tela_horizontal-(2*TAMANHO_BLOCO), metade_tela_vertical-TAMANHO_BLOCO,
                 metade_tela_horizontal+(2*TAMANHO_BLOCO), metade_tela_vertical-(2*TAMANHO_BLOCO));

    CV::color(0,0,0);
    CV::text(metade_tela_horizontal-(CV::getTextWidth("HELP", GLUT_BITMAP_HELVETICA_18)/2),
             metade_tela_vertical-(1.5*TAMANHO_BLOCO)-(CV::getBitmapHeight(GLUT_BITMAP_HELVETICA_18)/2),
             "HELP",
             GLUT_BITMAP_HELVETICA_18);

    if(mouseX>=metade_tela_horizontal-(2*TAMANHO_BLOCO) && mouseX<=metade_tela_horizontal+(2*TAMANHO_BLOCO)
       && mouseY<=metade_tela_vertical-TAMANHO_BLOCO && mouseY>=metade_tela_vertical-(2*TAMANHO_BLOCO)){
        vermelho[1]=1;
        verde[1]=1;
        azul[1]=1;
    }
    else{
        vermelho[1]=0.5;
        verde[1]=0.5;
        azul[1]=0.5;
    }

    CV::color(vermelho[2],verde[2],azul[2]);
    CV::rectFill(metade_tela_horizontal-(2*TAMANHO_BLOCO), metade_tela_vertical-(3*TAMANHO_BLOCO)+(TAMANHO_BLOCO/2),
                 metade_tela_horizontal+(2*TAMANHO_BLOCO), metade_tela_vertical-(4*TAMANHO_BLOCO)+(TAMANHO_BLOCO/2));

    CV::color(0,0,0);
    CV::text(metade_tela_horizontal-(CV::getTextWidth("QUIT", GLUT_BITMAP_HELVETICA_18)/2),
             metade_tela_vertical-(3*TAMANHO_BLOCO)-(CV::getBitmapHeight(GLUT_BITMAP_HELVETICA_18)/2),
             "QUIT",
             GLUT_BITMAP_HELVETICA_18);

    if(mouseX>=metade_tela_horizontal-(2*TAMANHO_BLOCO) && mouseX<=metade_tela_horizontal+(2*TAMANHO_BLOCO)
       && mouseY<=metade_tela_vertical-(2*TAMANHO_BLOCO)-(TAMANHO_BLOCO/2) && mouseY>=metade_tela_vertical-(3*TAMANHO_BLOCO)-(TAMANHO_BLOCO/2)){
        vermelho[2]=1;
        verde[2]=1;
        azul[2]=1;
    }
    else{
        vermelho[2]=0.5;
        verde[2]=0.5;
        azul[2]=0.5;
    }

    if(ajuda==TRUE){
        CV::color(0,0,0);
        CV::rectFill(0,0,screenWidth, screenHeight);
        CV::color(1,1,1);
        CV::rect(X_INICIO, Y_INICIO, X_FIM, Y_FIM);
        CV::color(1,1,1);
        CV::text(X_INICIO+TAMANHO_BLOCO, Y_FIM-TAMANHO_BLOCO, "A = MOVE LEFT", GLUT_BITMAP_HELVETICA_18);
        CV::text(X_INICIO+TAMANHO_BLOCO, Y_FIM-2*TAMANHO_BLOCO, "S = MOVE DOWN", GLUT_BITMAP_HELVETICA_18);
        CV::text(X_INICIO+TAMANHO_BLOCO, Y_FIM-3*TAMANHO_BLOCO, "D = MOVE RIGHT", GLUT_BITMAP_HELVETICA_18);
        CV::text(X_INICIO+TAMANHO_BLOCO, Y_FIM-5*TAMANHO_BLOCO, "R = ROTATE", GLUT_BITMAP_HELVETICA_18);
        CV::text(X_INICIO+TAMANHO_BLOCO, Y_FIM-6*TAMANHO_BLOCO, "C = HOLD CURRENT BLOCK", GLUT_BITMAP_HELVETICA_18);
        CV::text(X_INICIO+TAMANHO_BLOCO, Y_FIM-8*TAMANHO_BLOCO, "ESC = CLOSE HELP", GLUT_BITMAP_HELVETICA_18);

    }
}


void Limpar_linha(){ //Função responsável por limpar as linhas cheias.
    int contador_colunas=0, h, i, j, quantia_de_linhas=0;

    for(i=0; i<LINHAS; i++){
        for(j=0; j<COLUNAS; j++){
            if(tabela[i][j]>0){
               contador_colunas++;
               }
        }
        if(contador_colunas==10){
            quantia_de_linhas++;
            cont_linhas++;

            for(j=COLUNAS-1; j>=0; j--){
                tabela[i][j]=0;
            }
            for(h=LINHAS-1; h>=0; h--){
                if(h<i){
                    for(j=COLUNAS-1; j>=0; j--){
                        auxiliar=tabela[h][j];
                        tabela[h][j]=tabela[h+1][j];
                        tabela[h+1][j]=auxiliar;
                    }
                }
            }
        }
        contador_colunas=0;
    }

    if(quantia_de_linhas==4){
        pontuacao=pontuacao+1000;
    }

    else{
        pontuacao=pontuacao+quantia_de_linhas*100;
    }

    if(pontuacao>=1000*cont_velocidade){
        cont_velocidade++;
        velocidade=velocidade*0.99;
    }


}

void Parar_peca(){ //Função que para a peça, assim que ela atingir outra ou chegar no fundo da tabela.
    int i, j;

    switch(peca_escolhida){
            case 1: pontuacao=pontuacao+10;
                break;
            case 2: pontuacao=pontuacao+20;
                break;
            case 3: pontuacao=pontuacao+20;
                break;
            case 4: pontuacao=pontuacao+10;
                break;
            case 5: pontuacao=pontuacao+25;
                break;
            case 6: pontuacao=pontuacao+15;
                break;
            case 7: pontuacao=pontuacao+25;
                break;
            default: break;

        }

    for(i=LINHAS; i>=0; i--){
        for(j=COLUNAS; j>=0; j--){
            if(tabela[i][j]<0){
                tabela[i][j]=tabela[i][j]*-1;
            }
        }
    }

    Limpar_linha();

    peca_escolhida=0;
    cont_hold=0;
    cont_rotacao=0;
}


void Copia_para_colisao(){ //Função que copia a tabela para testar colisão.
    int i, j;

    for(i=0; i<LINHAS; i++){
        for(j=0; j<COLUNAS; j++){
            copia_tabela[i][j]=tabela[i][j];
        }
    }
}

void Colisao_rotacao(){ //Função que testa a colisão na rotação da peça.
    int i, j;

    for(i=0; i<LINHAS; i++){
        for(j=0; j<COLUNAS; j++){
            if(copia_tabela[i][j]<0 && tabela[i][j]>0){
                bateu_peca=TRUE;
            }
        }
    }
}

void Colisao(){ //Função que testa a colisão normalmente.
    int i, j;

    for(i=0; i<LINHAS; i++){
        for(j=0; j<COLUNAS; j++){
            if(copia_tabela[i][j]>0 && tabela[i][j]<0){
                bateu_peca=TRUE;
            }
        }
    }
}

void Copia_para_rotacao(){ //Função que chama o teste de colisão e executa ela.
    int i, j;

    switch(peca_escolhida){
            case 1:
                switch(cont_rotacao){
                    case 0:
                            cont_rotacao++;
                            if(index2_menor<9){
                                Copia_para_colisao();
                                copia_tabela[index_menor][index2_menor]=-1; copia_tabela[index_menor][index2_menor+1]=-1; copia_tabela[index_menor][index2_menor+2]=-1; copia_tabela[index_menor][index2_menor+3]=-1;  //I
                                Colisao_rotacao();
                                if(bateu_peca==FALSE){
                                    for(i=0; i<LINHAS; i++){
                                        for(j=0; j<COLUNAS; j++){
                                            if(tabela[i][j]<0){
                                                tabela[i][j]=0;
                                            }
                                        }
                                    }

                                tabela[index_menor][index2_menor]=-1; tabela[index_menor][index2_menor+1]=-1; tabela[index_menor][index2_menor+2]=-1; tabela[index_menor][index2_menor+3]=-1;  //I
                                }
                            }
                            else{
                                Copia_para_colisao();
                                copia_tabela[index_menor][6]=-1; copia_tabela[index_menor][7]=-1; copia_tabela[index_menor][8]=-1; copia_tabela[index_menor][9]=-1;  //I
                                Colisao_rotacao();
                                if(bateu_peca==FALSE){
                                    for(i=0; i<LINHAS; i++){
                                        for(j=0; j<COLUNAS; j++){
                                            if(tabela[i][j]<0){
                                                tabela[i][j]=0;
                                            }
                                        }
                                    }
                                tabela[index_menor][6]=-1; tabela[index_menor][7]=-1; tabela[index_menor][8]=-1; tabela[index_menor][9]=-1;  //I
                                }
                            }
                    break;

                    case 1:
                            cont_rotacao=0;
                            if(index_menor<=16){
                            Copia_para_colisao();
                            copia_tabela[index_menor][index2_menor]=-1; copia_tabela[index_menor+1][index2_menor]=-1; copia_tabela[index_menor+2][index2_menor]=-1; copia_tabela[index_menor+3][index2_menor]=-1;
                            Colisao_rotacao();
                            if(bateu_peca==TRUE){

                            }
                            if(bateu_peca==FALSE){
                                for(i=0; i<LINHAS; i++){
                                    for(j=0; j<COLUNAS; j++){
                                        if(tabela[i][j]<0){
                                            tabela[i][j]=0;
                                        }
                                    }
                                }

                            tabela[index_menor][index2_menor]=-1; tabela[index_menor+1][index2_menor]=-1; tabela[index_menor+2][index2_menor]=-1; tabela[index_menor+3][index2_menor]=-1;
                            }
                        }
                        else{
                            Copia_para_colisao();
                            copia_tabela[16][index2_menor]=-1; copia_tabela[17][index2_menor]=-1; copia_tabela[18][index2_menor]=-1; copia_tabela[19][index2_menor]=-1;  //I
                            Colisao_rotacao();
                            if(bateu_peca==FALSE){
                                for(i=0; i<LINHAS; i++){
                                    for(j=0; j<COLUNAS; j++){
                                        if(tabela[i][j]<0){
                                            tabela[i][j]=0;
                                        }
                                    }
                                }
                                tabela[16][index2_menor]=-1; tabela[17][index2_menor]=-1; tabela[18][index2_menor]=-1; tabela[19][index2_menor]=-1;  //I
                            }
                        }
                    break;
                }
                break;

            case 2:
                switch(cont_rotacao){
                    case 0:
                            cont_rotacao++;
                            if(index_menor<=17){
                                Copia_para_colisao();
                                copia_tabela[index_menor+2][index2_menor]=-2; copia_tabela[index_menor+2][index2_menor+1]=-2; copia_tabela[index_menor+1][index2_menor+1]=-2; copia_tabela[index_menor][index2_menor+1]=-2;  //J
                                Colisao_rotacao();
                                if(bateu_peca==FALSE){
                                    for(i=0; i<LINHAS; i++){
                                        for(j=0; j<COLUNAS; j++){
                                            if(tabela[i][j]<0){
                                                tabela[i][j]=0;
                                            }
                                        }
                                    }
                                    tabela[index_menor+2][index2_menor]=-2; tabela[index_menor+2][index2_menor+1]=-2; tabela[index_menor+1][index2_menor+1]=-2; tabela[index_menor][index2_menor+1]=-2;  //J
                                }
                            }
                            else{
                                Copia_para_colisao();
                                copia_tabela[17][index2_menor]=-2; copia_tabela[17][index2_menor+1]=-2; copia_tabela[16][index2_menor+1]=-2; copia_tabela[15][index2_menor+1]=-2;  //J
                                Colisao_rotacao();
                                if(bateu_peca==FALSE){
                                    for(i=0; i<LINHAS; i++){
                                        for(j=0; j<COLUNAS; j++){
                                            if(tabela[i][j]<0){
                                                tabela[i][j]=0;
                                            }
                                        }
                                    }
                                    tabela[17][index2_menor]=-2; tabela[17][index2_menor+1]=-2; tabela[16][index2_menor+1]=-2; tabela[15][index2_menor+1]=-2;  //J
                                }
                            }
                    break;

                    case 1:
                            cont_rotacao++;
                            if(index2_menor<8){
                                Copia_para_colisao();
                                copia_tabela[index_menor][index2_menor]=-2; copia_tabela[index_menor+1][index2_menor]=-2; copia_tabela[index_menor+1][index2_menor+1]=-2; copia_tabela[index_menor+1][index2_menor+2]=-2;  //J
                                Colisao_rotacao();
                                if(bateu_peca==FALSE){
                                    for(i=0; i<LINHAS; i++){
                                        for(j=0; j<COLUNAS; j++){
                                            if(tabela[i][j]<0){
                                                tabela[i][j]=0;
                                            }
                                        }
                                    }
                                    tabela[index_menor][index2_menor]=-2; tabela[index_menor+1][index2_menor]=-2; tabela[index_menor+1][index2_menor+1]=-2; tabela[index_menor+1][index2_menor+2]=-2;  //J
                                }
                            }
                            else{
                                Copia_para_colisao();
                                copia_tabela[index_menor][7]=-2; copia_tabela[index_menor+1][7]=-2; copia_tabela[index_menor+1][8]=-2; copia_tabela[index_menor+1][9]=-2;  //J
                                Colisao_rotacao();
                                if(bateu_peca==FALSE){
                                    for(i=0; i<LINHAS; i++){
                                        for(j=0; j<COLUNAS; j++){
                                            if(tabela[i][j]<0){
                                                tabela[i][j]=0;
                                            }
                                        }
                                    }
                                    tabela[index_menor][7]=-2; tabela[index_menor+1][7]=-2; tabela[index_menor+1][8]=-2; tabela[index_menor+1][9]=-2;  //J
                                }
                            }

                    break;

                    case 2:
                            cont_rotacao++;
                            if(index_menor<=17){
                                Copia_para_colisao();
                                copia_tabela[index_menor][index2_menor]=-2; copia_tabela[index_menor+1][index2_menor]=-2; copia_tabela[index_menor+2][index2_menor]=-2; copia_tabela[index_menor][index2_menor+1]=-2;  //J
                                Colisao_rotacao();
                                if(bateu_peca==FALSE){
                                    for(i=0; i<LINHAS; i++){
                                        for(j=0; j<COLUNAS; j++){
                                            if(tabela[i][j]<0){
                                                tabela[i][j]=0;
                                            }
                                        }
                                    }
                                    tabela[index_menor][index2_menor]=-2; tabela[index_menor+1][index2_menor]=-2; tabela[index_menor+2][index2_menor]=-2; tabela[index_menor][index2_menor+1]=-2;  //J
                                }
                            }
                            else{
                                Copia_para_colisao();
                                copia_tabela[17][index2_menor]=-2; copia_tabela[18][index2_menor]=-2; copia_tabela[19][index2_menor]=-2; copia_tabela[17][index2_menor+1]=-2;  //J
                                Colisao_rotacao();
                                if(bateu_peca==FALSE){
                                    for(i=0; i<LINHAS; i++){
                                        for(j=0; j<COLUNAS; j++){
                                            if(tabela[i][j]<0){
                                                tabela[i][j]=0;
                                            }
                                        }
                                    }
                                    tabela[17][index2_menor]=-2; tabela[18][index2_menor]=-2; tabela[19][index2_menor]=-2; tabela[17][index2_menor+1]=-2;  //J
                                }
                            }

                    break;

                    case 3:
                            cont_rotacao=0;
                            if(index2_menor<8){
                                Copia_para_colisao();
                                copia_tabela[index_menor][index2_menor]=-2; copia_tabela[index_menor][index2_menor+1]=-2; copia_tabela[index_menor+1][index2_menor+2]=-2; copia_tabela[index_menor][index2_menor+2]=-2;  //J
                                Colisao_rotacao();
                                if(bateu_peca==FALSE){
                                    for(i=0; i<LINHAS; i++){
                                        for(j=0; j<COLUNAS; j++){
                                            if(tabela[i][j]<0){
                                                tabela[i][j]=0;
                                            }
                                        }
                                    }
                                    tabela[index_menor][index2_menor]=-2; tabela[index_menor][index2_menor+1]=-2; tabela[index_menor+1][index2_menor+2]=-2; tabela[index_menor][index2_menor+2]=-2;  //J
                                }
                            }
                            else{
                                Copia_para_colisao();
                                copia_tabela[index_menor][7]=-2; copia_tabela[index_menor][8]=-2; copia_tabela[index_menor+1][9]=-2; copia_tabela[index_menor][9]=-2;  //J
                                Colisao_rotacao();
                                if(bateu_peca==FALSE){
                                    for(i=0; i<LINHAS; i++){
                                        for(j=0; j<COLUNAS; j++){
                                            if(tabela[i][j]<0){
                                                tabela[i][j]=0;
                                            }
                                        }
                                    }
                                    tabela[index_menor][7]=-2; tabela[index_menor][8]=-2; tabela[index_menor+1][9]=-2; tabela[index_menor][9]=-2;  //J
                                }
                            }
                        break;
                }
                break;

            case 3:
                switch(cont_rotacao){
                    case 0:
                            cont_rotacao++;
                            if(index_menor<=17){
                                Copia_para_colisao();
                                copia_tabela[index_menor][index2_menor]=-3; copia_tabela[index_menor+1][index2_menor]=-3; copia_tabela[index_menor+2][index2_menor]=-3; copia_tabela[index_menor+2][index2_menor+1]=-3;  //L
                                Colisao_rotacao();
                                if(bateu_peca==FALSE){
                                    for(i=0; i<LINHAS; i++){
                                        for(j=0; j<COLUNAS; j++){
                                            if(tabela[i][j]<0){
                                                tabela[i][j]=0;
                                            }
                                        }
                                    }
                                    tabela[index_menor][index2_menor]=-3; tabela[index_menor+1][index2_menor]=-3; tabela[index_menor+2][index2_menor]=-3; tabela[index_menor+2][index2_menor+1]=-3;  //L
                                }
                            }
                            else{
                                Copia_para_colisao();
                                copia_tabela[17][index2_menor]=-3; copia_tabela[18][index2_menor]=-3; copia_tabela[19][index2_menor]=-3; copia_tabela[19][index2_menor+1]=-3;  //L
                                Colisao_rotacao();
                                if(bateu_peca==FALSE){
                                    for(i=0; i<LINHAS; i++){
                                        for(j=0; j<COLUNAS; j++){
                                            if(tabela[i][j]<0){
                                                tabela[i][j]=0;
                                            }
                                        }
                                    }
                                    tabela[17][index2_menor]=-3; tabela[18][index2_menor]=-3; tabela[19][index2_menor]=-3; tabela[19][index2_menor+1]=-3;  //L
                                }
                            }
                    break;

                    case 1:
                            cont_rotacao++;
                            if(index2_menor<8){
                                Copia_para_colisao();
                                copia_tabela[index_menor][index2_menor]=-3; copia_tabela[index_menor+1][index2_menor]=-3; copia_tabela[index_menor][index2_menor+1]=-3; copia_tabela[index_menor][index2_menor+2]=-3;  //L
                                Colisao_rotacao();
                                if(bateu_peca==FALSE){
                                    for(i=0; i<LINHAS; i++){
                                        for(j=0; j<COLUNAS; j++){
                                            if(tabela[i][j]<0){
                                                tabela[i][j]=0;
                                            }
                                        }
                                    }
                                    tabela[index_menor][index2_menor]=-3; tabela[index_menor+1][index2_menor]=-3; tabela[index_menor][index2_menor+1]=-3; tabela[index_menor][index2_menor+2]=-3;  //L
                                }
                            }
                            else{
                                Copia_para_colisao();
                                copia_tabela[index_menor][7]=-3; copia_tabela[index_menor+1][7]=-3; copia_tabela[index_menor][8]=-3; copia_tabela[index_menor][9]=-3;  //L
                                Colisao_rotacao();
                                if(bateu_peca==FALSE){
                                    for(i=0; i<LINHAS; i++){
                                        for(j=0; j<COLUNAS; j++){
                                            if(tabela[i][j]<0){
                                                tabela[i][j]=0;
                                            }
                                        }
                                    }
                                    tabela[index_menor][7]=-3; tabela[index_menor+1][7]=-3; tabela[index_menor][8]=-3; tabela[index_menor][9]=-3;  //L
                                }
                            }

                    break;

                    case 2:
                            cont_rotacao++;
                            if(index_menor<=17){
                                Copia_para_colisao();
                                copia_tabela[index_menor][index2_menor]=-3; copia_tabela[index_menor][index2_menor+1]=-3; copia_tabela[index_menor+1][index2_menor+1]=-3; copia_tabela[index_menor+2][index2_menor+1]=-3;  //L
                                Colisao_rotacao();
                                if(bateu_peca==FALSE){
                                    for(i=0; i<LINHAS; i++){
                                        for(j=0; j<COLUNAS; j++){
                                            if(tabela[i][j]<0){
                                                tabela[i][j]=0;
                                            }
                                        }
                                    }
                                    tabela[index_menor][index2_menor]=-3; tabela[index_menor][index2_menor+1]=-3; tabela[index_menor+1][index2_menor+1]=-3; tabela[index_menor+2][index2_menor+1]=-3;  //L
                                }
                            }
                            else{
                                Copia_para_colisao();
                                copia_tabela[17][index2_menor]=-3; copia_tabela[17][index2_menor+1]=-3; copia_tabela[18][index2_menor+1]=-3; copia_tabela[19][index2_menor+1]=-3;  //L
                                Colisao_rotacao();
                                if(bateu_peca==FALSE){
                                    for(i=0; i<LINHAS; i++){
                                        for(j=0; j<COLUNAS; j++){
                                            if(tabela[i][j]<0){
                                                tabela[i][j]=0;
                                            }
                                        }
                                    }
                                    tabela[17][index2_menor]=-3; tabela[17][index2_menor+1]=-3; tabela[18][index2_menor+1]=-3; tabela[19][index2_menor+1]=-3;  //L  //L
                                }
                            }

                    break;

                    case 3:
                            cont_rotacao=0;
                            if(index2_menor<8){
                                Copia_para_colisao();
                                copia_tabela[index_menor+1][index2_menor]=-3; copia_tabela[index_menor+1][index2_menor+1]=-3; copia_tabela[index_menor+1][index2_menor+2]=-3; copia_tabela[index_menor][index2_menor+2]=-3;  //L
                                Colisao_rotacao();
                                if(bateu_peca==FALSE){
                                    for(i=0; i<LINHAS; i++){
                                        for(j=0; j<COLUNAS; j++){
                                            if(tabela[i][j]<0){
                                                tabela[i][j]=0;
                                            }
                                        }
                                    }
                                    tabela[index_menor+1][index2_menor]=-3; tabela[index_menor+1][index2_menor+1]=-3; tabela[index_menor+1][index2_menor+2]=-3; tabela[index_menor][index2_menor+2]=-3;  //L
                                }
                            }
                            else{
                                Copia_para_colisao();
                                copia_tabela[index_menor+1][7]=-3; copia_tabela[index_menor+1][8]=-3; copia_tabela[index_menor+1][9]=-3; copia_tabela[index_menor][9]=-3;  //L
                                Colisao_rotacao();
                                if(bateu_peca==FALSE){
                                    for(i=0; i<LINHAS; i++){
                                        for(j=0; j<COLUNAS; j++){
                                            if(tabela[i][j]<0){
                                                tabela[i][j]=0;
                                            }
                                        }
                                    }
                                    tabela[index_menor+1][7]=-3; tabela[index_menor+1][8]=-3; tabela[index_menor+1][9]=-3; tabela[index_menor][9]=-3;  //L
                                }
                            }
                        break;
                }
                break;
            break;

            case 5:
                switch(cont_rotacao){
                    case 0:
                            cont_rotacao++;
                            if(index_menor<18){
                                Copia_para_colisao();
                                copia_tabela[index_menor][index2_menor]=-5; copia_tabela[index_menor+1][index2_menor]=-5; copia_tabela[index_menor+1][index2_menor+1]=-5; copia_tabela[index_menor+2][index2_menor+1]=-5;  //S
                                Colisao_rotacao();
                                if(bateu_peca==FALSE){
                                    for(i=0; i<LINHAS; i++){
                                        for(j=0; j<COLUNAS; j++){
                                            if(tabela[i][j]<0){
                                                tabela[i][j]=0;
                                            }
                                        }
                                    }

                                tabela[index_menor][index2_menor]=-5; tabela[index_menor+1][index2_menor]=-5; tabela[index_menor+1][index2_menor+1]=-5; tabela[index_menor+2][index2_menor+1]=-5;  //S
                                }
                            }
                            else{
                                Copia_para_colisao();
                                copia_tabela[17][index2_menor]=-5; copia_tabela[18][index2_menor]=-5; copia_tabela[18][index2_menor+1]=-5; copia_tabela[19][index2_menor+1]=-5;  //S
                                Colisao_rotacao();
                                if(bateu_peca==FALSE){
                                    for(i=0; i<LINHAS; i++){
                                        for(j=0; j<COLUNAS; j++){
                                            if(tabela[i][j]<0){
                                                tabela[i][j]=0;
                                            }
                                        }
                                    }
                                tabela[17][index2_menor]=-5; tabela[18][index2_menor]=-5; tabela[18][index2_menor+1]=-5; tabela[19][index2_menor+1]=-5;  //S
                                }
                            }
                    break;

                    case 1:
                            cont_rotacao=0;
                            if(index2_menor<7){
                                Copia_para_colisao();
                                copia_tabela[index_menor+1][index2_menor]=-5; copia_tabela[index_menor+1][index2_menor+1]=-5; copia_tabela[index_menor][index2_menor+1]=-5; copia_tabela[index_menor][index2_menor+2]=-5;  //S
                                Colisao_rotacao();
                            if(bateu_peca==FALSE){
                                for(i=0; i<LINHAS; i++){
                                    for(j=0; j<COLUNAS; j++){
                                        if(tabela[i][j]<0){
                                            tabela[i][j]=0;
                                        }
                                    }
                                }

                            tabela[index_menor+1][index2_menor]=-5; tabela[index_menor+1][index2_menor+1]=-5; tabela[index_menor][index2_menor+1]=-5; tabela[index_menor][index2_menor+2]=-5;  //S
                            }
                        }
                        else{
                            Copia_para_colisao();
                            copia_tabela[index_menor+1][7]=-5; copia_tabela[index_menor+1][8]=-5; copia_tabela[index_menor][8]=-5; copia_tabela[index_menor][9]=-5;  //S
                            Colisao_rotacao();
                            if(bateu_peca==FALSE){
                                for(i=0; i<LINHAS; i++){
                                    for(j=0; j<COLUNAS; j++){
                                        if(tabela[i][j]<0){
                                            tabela[i][j]=0;
                                        }
                                    }
                                }
                                tabela[index_menor+1][7]=-5; tabela[index_menor+1][8]=-5; tabela[index_menor][8]=-5; tabela[index_menor][9]=-5;  //S
                            }
                        }
                    break;
                }
                break;

            case 6:
                switch(cont_rotacao){
                    case 0:
                            cont_rotacao++;
                            if(index_menor<=17){
                                Copia_para_colisao();
                                copia_tabela[index_menor][index2_menor+1]=-6; copia_tabela[index_menor+1][index2_menor]=-6; copia_tabela[index_menor+1][index2_menor+1]=-6; copia_tabela[index_menor+2][index2_menor+1]=-6;  //T
                                Colisao_rotacao();
                                if(bateu_peca==FALSE){
                                    for(i=0; i<LINHAS; i++){
                                        for(j=0; j<COLUNAS; j++){
                                            if(tabela[i][j]<0){
                                                tabela[i][j]=0;
                                            }
                                        }
                                    }
                                    tabela[index_menor][index2_menor+1]=-6; tabela[index_menor+1][index2_menor]=-6; tabela[index_menor+1][index2_menor+1]=-6; tabela[index_menor+2][index2_menor+1]=-6;  //T
                                }
                            }
                            else{
                                Copia_para_colisao();
                                copia_tabela[17][index2_menor+1]=-6; copia_tabela[18][index2_menor]=-6; copia_tabela[18][index2_menor+1]=-6; copia_tabela[19][index2_menor+1]=-6;  //T
                                Colisao_rotacao();
                                if(bateu_peca==FALSE){
                                    for(i=0; i<LINHAS; i++){
                                        for(j=0; j<COLUNAS; j++){
                                            if(tabela[i][j]<0){
                                                tabela[i][j]=0;
                                            }
                                        }
                                    }
                                    tabela[17][index2_menor+1]=-6; tabela[18][index2_menor]=-6; tabela[18][index2_menor+1]=-6; tabela[19][index2_menor+1]=-6;  //T
                                }
                            }
                    break;

                    case 1:
                            cont_rotacao++;
                            if(index2_menor<8){
                                Copia_para_colisao();
                                copia_tabela[index_menor+1][index2_menor]=-6; copia_tabela[index_menor+1][index2_menor+1]=-6; copia_tabela[index_menor][index2_menor+1]=-6; copia_tabela[index_menor+1][index2_menor+2]=-6;  //T
                                Colisao_rotacao();
                                if(bateu_peca==FALSE){
                                    for(i=0; i<LINHAS; i++){
                                        for(j=0; j<COLUNAS; j++){
                                            if(tabela[i][j]<0){
                                                tabela[i][j]=0;
                                            }
                                        }
                                    }
                                    tabela[index_menor+1][index2_menor]=-6; tabela[index_menor+1][index2_menor+1]=-6; tabela[index_menor][index2_menor+1]=-6; tabela[index_menor+1][index2_menor+2]=-6;  //T
                                }
                            }
                            else{
                                Copia_para_colisao();
                                copia_tabela[index_menor+1][7]=-6; copia_tabela[index_menor][8]=-6; copia_tabela[index_menor+1][8]=-6; copia_tabela[index_menor+1][9]=-6;  //T
                                Colisao_rotacao();
                                if(bateu_peca==FALSE){
                                    for(i=0; i<LINHAS; i++){
                                        for(j=0; j<COLUNAS; j++){
                                            if(tabela[i][j]<0){
                                                tabela[i][j]=0;
                                            }
                                        }
                                    }
                                    tabela[index_menor+1][7]=-6; tabela[index_menor][8]=-6; tabela[index_menor+1][8]=-6; tabela[index_menor+1][9]=-6;  //T
                                }
                            }

                    break;

                    case 2:
                            cont_rotacao++;
                            if(index_menor<=17){
                                Copia_para_colisao();
                                copia_tabela[index_menor][index2_menor]=-6; copia_tabela[index_menor+1][index2_menor]=-6; copia_tabela[index_menor+1][index2_menor+1]=-6; copia_tabela[index_menor+2][index2_menor]=-6;  //T
                                Colisao_rotacao();
                                if(bateu_peca==FALSE){
                                    for(i=0; i<LINHAS; i++){
                                        for(j=0; j<COLUNAS; j++){
                                            if(tabela[i][j]<0){
                                                tabela[i][j]=0;
                                            }
                                        }
                                    }
                                    tabela[index_menor][index2_menor]=-6; tabela[index_menor+1][index2_menor]=-6; tabela[index_menor+1][index2_menor+1]=-6; tabela[index_menor+2][index2_menor]=-6;  //T
                                }
                            }
                            else{
                                Copia_para_colisao();
                                copia_tabela[17][index2_menor]=-6; copia_tabela[18][index2_menor]=-6; copia_tabela[18][index2_menor+1]=-6; copia_tabela[19][index2_menor]=-6;  //T
                                Colisao_rotacao();
                                if(bateu_peca==FALSE){
                                    for(i=0; i<LINHAS; i++){
                                        for(j=0; j<COLUNAS; j++){
                                            if(tabela[i][j]<0){
                                                tabela[i][j]=0;
                                            }
                                        }
                                    }
                                    tabela[17][index2_menor]=-6; tabela[18][index2_menor]=-6; tabela[18][index2_menor+1]=-6; tabela[19][index2_menor]=-6;  //T
                                }
                            }

                    break;

                    case 3:
                            cont_rotacao=0;
                            if(index2_menor<8){
                                Copia_para_colisao();
                                copia_tabela[index_menor][index2_menor]=-6; copia_tabela[index_menor][index2_menor+1]=-6; copia_tabela[index_menor+1][index2_menor+1]=-6; copia_tabela[index_menor][index2_menor+2]=-6;  //T
                                Colisao_rotacao();
                                if(bateu_peca==FALSE){
                                    for(i=0; i<LINHAS; i++){
                                        for(j=0; j<COLUNAS; j++){
                                            if(tabela[i][j]<0){
                                                tabela[i][j]=0;
                                            }
                                        }
                                    }
                                    tabela[index_menor][index2_menor]=-6; tabela[index_menor][index2_menor+1]=-6; tabela[index_menor+1][index2_menor+1]=-6; tabela[index_menor][index2_menor+2]=-6;  //T
                                }
                            }
                            else{
                                Copia_para_colisao();
                                copia_tabela[index_menor][7]=-6; copia_tabela[index_menor][8]=-6; copia_tabela[index_menor+1][8]=-6; copia_tabela[index_menor][9]=-6;  //T
                                Colisao_rotacao();
                                if(bateu_peca==FALSE){
                                    for(i=0; i<LINHAS; i++){
                                        for(j=0; j<COLUNAS; j++){
                                            if(tabela[i][j]<0){
                                                tabela[i][j]=0;
                                            }
                                        }
                                    }
                                    tabela[index_menor][7]=-6; tabela[index_menor][8]=-6; tabela[index_menor+1][8]=-6; tabela[index_menor][9]=-6;  //T
                                }
                            }
                        break;
                }
                break;
            break;

            case 7:
                switch(cont_rotacao){
                    case 0:
                            cont_rotacao++;
                            if(index_menor<18){
                                Copia_para_colisao();
                                copia_tabela[index_menor][index2_menor+1]=-7; copia_tabela[index_menor+1][index2_menor+1]=-7; copia_tabela[index_menor+1][index2_menor]=-7; copia_tabela[index_menor+2][index2_menor]=-7;  //Z
                                Colisao_rotacao();
                                if(bateu_peca==FALSE){
                                    for(i=0; i<LINHAS; i++){
                                        for(j=0; j<COLUNAS; j++){
                                            if(tabela[i][j]<0){
                                                tabela[i][j]=0;
                                            }
                                        }
                                    }

                                    tabela[index_menor][index2_menor+1]=-7; tabela[index_menor+1][index2_menor+1]=-7; tabela[index_menor+1][index2_menor]=-7; tabela[index_menor+2][index2_menor]=-7;  //Z
                                }
                            }
                            else{
                                Copia_para_colisao();
                                copia_tabela[17][index2_menor+1]=-7; copia_tabela[18][index2_menor+1]=-7; copia_tabela[18][index2_menor]=-7; copia_tabela[19][index2_menor]=-7;  //Z
                                Colisao_rotacao();
                                if(bateu_peca==FALSE){
                                    for(i=0; i<LINHAS; i++){
                                        for(j=0; j<COLUNAS; j++){
                                            if(tabela[i][j]<0){
                                                tabela[i][j]=0;
                                            }
                                        }
                                    }
                                    tabela[17][index2_menor+1]=-7; tabela[18][index2_menor+1]=-7; tabela[18][index2_menor]=-7; tabela[19][index2_menor]=-7;  //Z
                                }
                            }
                    break;

                    case 1:
                            cont_rotacao=0;
                            if(index2_menor<8){
                                Copia_para_colisao();
                                copia_tabela[index_menor][index2_menor]=-7; copia_tabela[index_menor][index2_menor+1]=-7; copia_tabela[index_menor+1][index2_menor+1]=-7; copia_tabela[index_menor+1][index2_menor+2]=-7;  //Z
                                Colisao_rotacao();
                                if(bateu_peca==FALSE){
                                    for(i=0; i<LINHAS; i++){
                                        for(j=0; j<COLUNAS; j++){
                                            if(tabela[i][j]<0){
                                                tabela[i][j]=0;
                                            }
                                        }
                                    }

                                tabela[index_menor][index2_menor]=-7; tabela[index_menor][index2_menor+1]=-7; tabela[index_menor+1][index2_menor+1]=-7; tabela[index_menor+1][index2_menor+2]=-7;  //Z
                                }
                            }
                            else{
                                Copia_para_colisao();
                                copia_tabela[index_menor][7]=-7; copia_tabela[index_menor][8]=-7; copia_tabela[index_menor+1][8]=-7; copia_tabela[index_menor+1][9]=-7;  //Z
                                Colisao_rotacao();
                                if(bateu_peca==FALSE){
                                    for(i=0; i<LINHAS; i++){
                                        for(j=0; j<COLUNAS; j++){
                                            if(tabela[i][j]<0){
                                                tabela[i][j]=0;
                                            }
                                        }
                                    }
                                    tabela[index_menor][7]=-7; tabela[index_menor][8]=-7; tabela[index_menor+1][8]=-7; tabela[index_menor+1][9]=-7;  //Z
                                }
                            }
                    break;
                }
                break;


            default: break;

    }

}

void Rotation(){ //Função que controla a rotação.
    int i, j;

    if(parar==FALSE){
        index_menor=20;
        index2_menor=20;

        for(i=0; i<LINHAS; i++){
            for(j=0; j<COLUNAS; j++){
                    if(tabela[i][j]<0){
                        if(i<index_menor){
                        index_menor=i;
                        }
                        if(j<index2_menor){
                        index2_menor=j;
                    }
                    }
            }
        }

        Copia_para_rotacao();
    }
}

void Parar_jogo(){ //Função que verifica o fim do jogo.

        switch(peca_escolhida){
        case 1: if(tabela[0][3]>0 || tabela[0][4]>0 || tabela[0][5]>0 || tabela[0][6]>0){
            parar=TRUE;
        }
            break;
        case 2: if(tabela[0][5]>0 || tabela[1][5]>0 || tabela[2][5]>0 || tabela[2][4]>0){
            parar=TRUE;
        }
            break;
        case 3: if(tabela[0][4]>0 || tabela[1][4]>0 || tabela[2][4]>0 || tabela[2][5]>0){
            parar=TRUE;
        }
            break;
        case 4: if(tabela[0][4]>0 || tabela[0][5]>0 || tabela[1][4]>0 || tabela[1][5]>0){
            parar=TRUE;
        }
            break;
        case 5: if(tabela[0][4]>0 || tabela[1][5]>0 || tabela[1][4]>0 || tabela[2][5]>0){
            parar=TRUE;
        }
            break;
        case 6: if(tabela[0][5]>0 || tabela[1][4]>0 || tabela[1][5]>0 || tabela[2][5]>0){
            parar=TRUE;
        }
            break;
        case 7: if(tabela[0][5]>0 || tabela[1][4]>0 || tabela[1][5]>0 || tabela[2][4]>0){
            parar=TRUE;
        }
            break;
        default:
            parar=FALSE;
            break;

        }
}

void Sorteia_peca(){ //Funão que sorteia a próxima peça.
    peca_proxima=(1+rand() % 7);
}

void Pecas_possiveis(){ //Função que copia a peça sorteada na tabela.

    if(apertou_holding==FALSE){
        peca_escolhida=peca_proxima;
        Sorteia_peca();
        Parar_jogo();
    }
    else{
        peca_escolhida=hold;
        hold=auxiliar;
        apertou_holding=FALSE;
    }



    bateu_embaixo=FALSE;
    bateu_esquerda=FALSE;
    bateu_direita=FALSE;
    bateu_peca=FALSE;



    sortear_peca=FALSE;

    if(parar==FALSE){
        switch(peca_escolhida){
            case 1: tabela[0][3]=-1; tabela[0][4]=-1; tabela[0][5]=-1; tabela[0][6]=-1; //I
                break;
            case 2: tabela[0][5]=-2; tabela[1][5]=-2; tabela[2][5]=-2; tabela[2][4]=-2; //J
                break;
            case 3: tabela[0][4]=-3; tabela[1][4]=-3; tabela[2][4]=-3; tabela[2][5]=-3; //L
                break;
            case 4: tabela[0][4]=-4; tabela[0][5]=-4; tabela[1][4]=-4; tabela[1][5]=-4; //O
                break;
            case 5: tabela[0][4]=-5; tabela[1][5]=-5; tabela[1][4]=-5; tabela[2][5]=-5; //S
                break;
            case 6: tabela[0][5]=-6; tabela[1][4]=-6; tabela[1][5]=-6; tabela[2][5]=-6; //T
                break;
            case 7: tabela[0][5]=-7; tabela[1][4]=-7; tabela[1][5]=-7; tabela[2][4]=-7; //Z
                break;
            default: break;

        }
    }

}

void Hold_back_end(){ //Função que controla o Hold.
    int i, j;

    if(parar==FALSE){
        if(holding==FALSE){
            hold=peca_escolhida;
            for(i=0; i<LINHAS; i++){
                for(j=0; j<COLUNAS; j++){
                    if(tabela[i][j]<0){
                        tabela[i][j]=0;
                    }
                }
            }
            Pecas_possiveis();
            holding=TRUE;
            cont_hold++;
        }
        else{
            if(cont_hold==0){
                auxiliar=peca_escolhida;
                for(i=0; i<LINHAS; i++){
                    for(j=0; j<COLUNAS; j++){
                        if(tabela[i][j]<0){
                            tabela[i][j]=0;
                        }
                    }
                }
                apertou_holding=TRUE;
                Pecas_possiveis();
                cont_hold++;
            }
        }
    }

}

void Hold_peca_hud(){ //Função que mostra a funcionalidade do Hold na tela.
    memset(hold_peca, 0, sizeof hold_peca);

    int r, s;

    switch(hold){
            case 1: hold_peca[1][1]=-10; hold_peca[1][2]=-10; hold_peca[1][3]=-10; hold_peca[1][4]=-10;
                break;
            case 2: hold_peca[0][3]=-20; hold_peca[1][3]=-20; hold_peca[2][3]=-20; hold_peca[2][2]=-20;
                break;
            case 3: hold_peca[0][2]=-30; hold_peca[1][2]=-30; hold_peca[2][2]=-30; hold_peca[2][3]=-30;
                break;
            case 4: hold_peca[0][2]=-40; hold_peca[0][3]=-40; hold_peca[1][2]=-40; hold_peca[1][3]=-40;
                break;
            case 5: hold_peca[0][2]=-50; hold_peca[1][3]=-50; hold_peca[1][2]=-50; hold_peca[2][3]=-50;
                break;
            case 6: hold_peca[0][3]=-60; hold_peca[1][2]=-60; hold_peca[1][3]=-60; hold_peca[2][3]=-60;
                break;
            case 7: hold_peca[0][3]=-70; hold_peca[1][2]=-70; hold_peca[1][3]=-70; hold_peca[2][2]=-70;
                break;
            default: break;

        }

    for(r=0; r<ALTURA_PECA; r++){
        for(s=0; s<COMPRIMENTO_PECA; s++){
            if(hold_peca[r][s]<=-10){
                switch(hold_peca[r][s]){
                case -10:
                    CV::color(1,0,0); //I //red
                    break;

                case -20:
                    CV::color(1,0,1); //J //magenta
                    break;

                case -30:
                    CV::color(0,1,0); //L //green
                    break;

                case -40:
                    CV::color(1,1,0); //O //yellow
                    break;

                case -50:
                    CV::color(1,0.5,0); //S //orange
                    break;

                case -60:
                    CV::color(0,0,1); //T //blue
                    break;

                case -70:
                    CV::color(0,1,1); //Z //cyan

                }

                CV::rectFill(X_INICIO-(2*TAMANHO_BLOCO)-(s*TAMANHO_BLOCO), Y_FIM-(2*TAMANHO_BLOCO)-(r*TAMANHO_BLOCO)-TAMANHO_BLOCO,
                             X_INICIO-(2*TAMANHO_BLOCO)-(s*TAMANHO_BLOCO)-TAMANHO_BLOCO, Y_FIM-(2*TAMANHO_BLOCO)-(r*TAMANHO_BLOCO)-TAMANHO_BLOCO-TAMANHO_BLOCO);

                CV::color(1,1,1);
                CV::rect(X_INICIO-(2*TAMANHO_BLOCO)-(s*TAMANHO_BLOCO), Y_FIM-(2*TAMANHO_BLOCO)-(r*TAMANHO_BLOCO)-TAMANHO_BLOCO,
                         X_INICIO-(2*TAMANHO_BLOCO)-(s*TAMANHO_BLOCO)-TAMANHO_BLOCO, Y_FIM-(2*TAMANHO_BLOCO)-(r*TAMANHO_BLOCO)-TAMANHO_BLOCO-TAMANHO_BLOCO);
            }

        }
    }

}

void Next_peca_hud(){ //Função que mostra a funcionalidade Next_peça na tela.
    memset(peca, 0, sizeof peca);

    int r, s;

    switch(peca_proxima){
            case 1: peca[1][1]=-10; peca[1][2]=-10; peca[1][3]=-10; peca[1][4]=-10;
                break;
            case 2: peca[0][3]=-20; peca[1][3]=-20; peca[2][3]=-20; peca[2][2]=-20;
                break;
            case 3: peca[0][2]=-30; peca[1][2]=-30; peca[2][2]=-30; peca[2][3]=-30;
                break;
            case 4: peca[0][2]=-40; peca[0][3]=-40; peca[1][2]=-40; peca[1][3]=-40;
                break;
            case 5: peca[0][2]=-50; peca[1][3]=-50; peca[1][2]=-50; peca[2][3]=-50;
                break;
            case 6: peca[0][3]=-60; peca[1][2]=-60; peca[1][3]=-60; peca[2][3]=-60;
                break;
            case 7: peca[0][3]=-70; peca[1][2]=-70; peca[1][3]=-70; peca[2][2]=-70;
                break;
            default: break;

        }

    for(r=0; r<ALTURA_PECA; r++){
        for(s=0; s<COMPRIMENTO_PECA; s++){
            if(peca[r][s]<=-10){
                switch(peca[r][s]){
                case -10:
                    CV::color(1,0,0); //I //red
                    break;

                case -20:
                    CV::color(1,0,1); //J //magenta
                    break;

                case -30:
                    CV::color(0,1,0); //L //green
                    break;

                case -40:
                    CV::color(1,1,0); //O //yellow
                    break;

                case -50:
                    CV::color(1,0.5,0); //S //orange
                    break;

                case -60:
                    CV::color(0,0,1); //T //blue
                    break;

                case -70:
                    CV::color(0,1,1); //Z //cyan

                }

                CV::rectFill(X_FIM+(2*TAMANHO_BLOCO)+(s*TAMANHO_BLOCO), Y_FIM-(2*TAMANHO_BLOCO)-(r*TAMANHO_BLOCO)-TAMANHO_BLOCO,
                             X_FIM+(2*TAMANHO_BLOCO)+(s*TAMANHO_BLOCO)+TAMANHO_BLOCO, Y_FIM-(2*TAMANHO_BLOCO)-(r*TAMANHO_BLOCO)-TAMANHO_BLOCO-TAMANHO_BLOCO);

                CV::color(1,1,1);
                CV::rect(X_FIM+(2*TAMANHO_BLOCO)+(s*TAMANHO_BLOCO), Y_FIM-(2*TAMANHO_BLOCO)-(r*TAMANHO_BLOCO)-TAMANHO_BLOCO,
                             X_FIM+(2*TAMANHO_BLOCO)+(s*TAMANHO_BLOCO)+TAMANHO_BLOCO, Y_FIM-(2*TAMANHO_BLOCO)-(r*TAMANHO_BLOCO)-TAMANHO_BLOCO-TAMANHO_BLOCO);
            }

        }
    }
}

void Next_hud(){ //Função que mostra o design do Next.
    CV::color(1,1,1);
    CV::rect(X_FIM+(2*TAMANHO_BLOCO), Y_FIM-(2*TAMANHO_BLOCO), X_FIM+(8*TAMANHO_BLOCO), Y_FIM-(7*TAMANHO_BLOCO));

    CV::color(1,1,1);
    CV::text(X_FIM+(2*TAMANHO_BLOCO)+(3*TAMANHO_BLOCO)-(CV::getTextWidth("NEXT", GLUT_BITMAP_TIMES_ROMAN_24)/2),
             Y_FIM-TAMANHO_BLOCO-(CV::getTextWidth("NEXT", GLUT_BITMAP_TIMES_ROMAN_24)/2)+(TAMANHO_BLOCO/2),
             "NEXT",
             GLUT_BITMAP_TIMES_ROMAN_24);
}

void Hold_hud(){ //Função que mostra o design do Hold.
    CV::color(1,1,1);
    CV::rect(X_INICIO-(2*TAMANHO_BLOCO), Y_FIM-(2*TAMANHO_BLOCO), X_INICIO-(8*TAMANHO_BLOCO), Y_FIM-(7*TAMANHO_BLOCO));

    CV::color(1,1,1);
    CV::text(X_INICIO-(2*TAMANHO_BLOCO)-(3*TAMANHO_BLOCO)-(CV::getTextWidth("HOLD", GLUT_BITMAP_TIMES_ROMAN_24)/2),
             Y_FIM-TAMANHO_BLOCO-(CV::getTextWidth("HOLD", GLUT_BITMAP_TIMES_ROMAN_24)/2)+(TAMANHO_BLOCO/2),
             "HOLD",
             GLUT_BITMAP_TIMES_ROMAN_24);
}

void Score_hud(){ //Função que mostra o design do Score.
    char str[10];
    char str2[10];
    char str3[10];

    CV::color(1,1,1);
    CV::rect(X_INICIO-(2*TAMANHO_BLOCO), Y_INICIO, X_INICIO-(8*TAMANHO_BLOCO), Y_INICIO+(6*TAMANHO_BLOCO));

    CV::color(1,1,1);
    CV::text(X_INICIO-(2*TAMANHO_BLOCO)-(3*TAMANHO_BLOCO)-(CV::getTextWidth("SCORE", GLUT_BITMAP_HELVETICA_18)/2),
             Y_INICIO+(6*TAMANHO_BLOCO)-(CV::getTextWidth("SCORE", GLUT_BITMAP_HELVETICA_18)/2),
             "SCORE",
             GLUT_BITMAP_HELVETICA_18);


    sprintf(str, "%d", pontuacao);
    CV::color(1,1,1);
    CV::text(X_INICIO-(5*TAMANHO_BLOCO)-(TAMANHO_BLOCO/2),
             Y_INICIO+(4*TAMANHO_BLOCO)+(TAMANHO_BLOCO/2),
             str,
             GLUT_BITMAP_HELVETICA_18);


    CV::color(1,1,1);
    CV::text(X_INICIO-(2*TAMANHO_BLOCO)-(3*TAMANHO_BLOCO)-(CV::getTextWidth("LEVEL", GLUT_BITMAP_HELVETICA_18)/2),
             Y_INICIO+(4*TAMANHO_BLOCO)-(CV::getTextWidth("LEVEL", GLUT_BITMAP_HELVETICA_18)/2),
             "LEVEL",
             GLUT_BITMAP_HELVETICA_18);


    sprintf(str2, "%d", cont_velocidade);
    CV::color(1,1,1);
    CV::text(X_INICIO-(5*TAMANHO_BLOCO+TAMANHO_BLOCO/4),
             Y_INICIO+(3*TAMANHO_BLOCO)-(CV::getTextWidth("pontuaca", GLUT_BITMAP_HELVETICA_18)/2)+(TAMANHO_BLOCO/2),
             str2,
             GLUT_BITMAP_HELVETICA_18);


    CV::color(1,1,1);
    CV::text(X_INICIO-(2*TAMANHO_BLOCO)-(3*TAMANHO_BLOCO)-(CV::getTextWidth("LINES", GLUT_BITMAP_HELVETICA_18)/2),
             Y_INICIO+(2*TAMANHO_BLOCO)-(CV::getTextWidth("LINES", GLUT_BITMAP_HELVETICA_18)/2),
             "LINES",
             GLUT_BITMAP_HELVETICA_18);


    sprintf(str3, "%d", cont_linhas);
    CV::color(1,1,1);
    CV::text(X_INICIO-(5*TAMANHO_BLOCO+TAMANHO_BLOCO/4),
             Y_INICIO+(TAMANHO_BLOCO)-(TAMANHO_BLOCO/3),
             str3,
             GLUT_BITMAP_HELVETICA_18);



}

void Hud(){ //Função que controla os Huds.
    Next_hud();
    Hold_hud();
    Score_hud();

}

void Game_over(){ //Função que controla o design do Game Over
    CV::color(0,0,0);
    CV::rectFill(metade_tela_horizontal-(5*TAMANHO_BLOCO), metade_tela_vertical-(5*TAMANHO_BLOCO),
                 metade_tela_horizontal+(5*TAMANHO_BLOCO)-1, metade_tela_vertical+(5*TAMANHO_BLOCO)-1);

    CV::color(1,1,1);
    CV::rect(metade_tela_horizontal-(3*TAMANHO_BLOCO), metade_tela_vertical-(3*TAMANHO_BLOCO),
             metade_tela_horizontal+(3*TAMANHO_BLOCO), metade_tela_vertical+(3*TAMANHO_BLOCO));

    CV::rect(metade_tela_horizontal-(5*TAMANHO_BLOCO), metade_tela_vertical-(5*TAMANHO_BLOCO),
             metade_tela_horizontal+(5*TAMANHO_BLOCO), metade_tela_vertical+(5*TAMANHO_BLOCO));

    CV::color(0.5,0.5,0.5);
    CV::text(metade_tela_horizontal-(CV::getTextWidth("RESTART GAME?", GLUT_BITMAP_TIMES_ROMAN_24)/2),
             metade_tela_vertical-(CV::getBitmapHeight(GLUT_BITMAP_TIMES_ROMAN_24)/2)+(2*TAMANHO_BLOCO),
             "RESTART GAME?",
             GLUT_BITMAP_TIMES_ROMAN_24);

    CV::color(vermelho[0],verde[0],azul[0]);
    CV::rectFill(metade_tela_horizontal-(2*TAMANHO_BLOCO), metade_tela_vertical-(0.5*TAMANHO_BLOCO),
                 metade_tela_horizontal+(2*TAMANHO_BLOCO), metade_tela_vertical+(0.5*TAMANHO_BLOCO));

    CV::color(0,0,0);
    CV::text(metade_tela_horizontal-(CV::getTextWidth("YES", GLUT_BITMAP_HELVETICA_18)/2),
             metade_tela_vertical-(CV::getBitmapHeight(GLUT_BITMAP_HELVETICA_18)/2),
             "YES",
             GLUT_BITMAP_HELVETICA_18);

    if(mouseX>=metade_tela_horizontal-(2*TAMANHO_BLOCO) && mouseX<=metade_tela_horizontal+(2*TAMANHO_BLOCO)
       && mouseY>=metade_tela_vertical-(0.5*TAMANHO_BLOCO) && mouseY<=metade_tela_vertical+(0.5*TAMANHO_BLOCO)){
        vermelho[0]=1;
        verde[0]=1;
        azul[0]=1;
    }
    else{
        vermelho[0]=0.5;
        verde[0]=0.5;
        azul[0]=0.5;
    }

    CV::color(vermelho[1],verde[1],azul[1]);
    CV::rectFill(metade_tela_horizontal-(2*TAMANHO_BLOCO), metade_tela_vertical-TAMANHO_BLOCO,
                 metade_tela_horizontal+(2*TAMANHO_BLOCO), metade_tela_vertical-(2*TAMANHO_BLOCO));

    CV::color(0,0,0);
    CV::text(metade_tela_horizontal-(CV::getTextWidth("NO", GLUT_BITMAP_HELVETICA_18)/2),
             metade_tela_vertical-(1.5*TAMANHO_BLOCO)-(CV::getBitmapHeight(GLUT_BITMAP_HELVETICA_18)/2),
             "NO",
             GLUT_BITMAP_HELVETICA_18);

    if(mouseX>=metade_tela_horizontal-(2*TAMANHO_BLOCO) && mouseX<=metade_tela_horizontal+(2*TAMANHO_BLOCO)
       && mouseY<=metade_tela_vertical-TAMANHO_BLOCO && mouseY>=metade_tela_vertical-(2*TAMANHO_BLOCO)){
        vermelho[1]=1;
        verde[1]=1;
        azul[1]=1;
    }
    else{
        vermelho[1]=0.5;
        verde[1]=0.5;
        azul[1]=0.5;
    }

    ajuda=FALSE;
}


void Tabuleiro(){ //Função que desenha o tabuleiro na tela.
    int i;

    CV::color(255,255,255);
    CV::rect(X_INICIO, Y_INICIO, X_FIM, Y_FIM);

    for(i=0; i<COLUNAS; i++){
       CV::line(X_INICIO+TAMANHO_BLOCO*i, Y_INICIO,
                X_INICIO+TAMANHO_BLOCO*i, Y_FIM);
    }

    for(i=0; i<LINHAS; i++){
        CV::line(X_INICIO, Y_INICIO+TAMANHO_BLOCO*i,
                 X_FIM,    Y_INICIO+TAMANHO_BLOCO*i);
    }


}

void Blocos(){ //Função que desenha os blocos na tabela.
    int i, j;
    for(i=0; i<LINHAS; i++){
        for(j=0; j<COLUNAS; j++){
            if(tabela[i][j]!=0){
                switch(tabela[i][j]){
                case -1:
                case 1: CV::color(1,0,0); //I //red
                    break;

                case -2:
                case 2: CV::color(1,0,1); //J //magenta
                    break;

                case -3:
                case 3: CV::color(0,1,0); //L //green
                    break;

                case -4:
                case 4: CV::color(1,1,0); //O //yellow
                    break;

                case -5:
                case 5: CV::color(1,0.5,0); //S //orange
                    break;

                case -6:
                case 6: CV::color(0,0,1); //T //blue
                    break;

                case -7:
                case 7: CV::color(0,1,1); //Z //cyan

                }

                CV::rectFill(X_INICIO+(j*TAMANHO_BLOCO)-1, Y_FIM-(i*TAMANHO_BLOCO),
                             X_INICIO+(j*TAMANHO_BLOCO)+TAMANHO_BLOCO, Y_FIM-(i*TAMANHO_BLOCO)-TAMANHO_BLOCO-1);
            }
        }
    }

}


void Descer_peca(){ //Função que faz a peca descer.
    int i, j;


    bateu_peca=FALSE;

    for(i=LINHAS; i>=0; i--){
        for(j=COLUNAS; j>=0; j--){
            if(tabela[i][j]<0){
                if(i==19){
                    bateu_embaixo=TRUE;
                    Parar_peca();
                }
            }
        }
    }

    Copia_para_colisao();

    for(i=LINHAS; i>=0; i--){
        for(j=COLUNAS; j>=0; j--){
            if(copia_tabela[i][j]<0){
                auxiliar=copia_tabela[i][j];
                copia_tabela[i][j]=copia_tabela[i+1][j];
                copia_tabela[i+1][j]=auxiliar;
            }
        }
    }

    Colisao();

    if(bateu_peca==TRUE){
       Parar_peca();
    }

    for(i=LINHAS; i>=0; i--){
        for(j=COLUNAS; j>=0; j--){
            if(tabela[i][j]<0){
                if(bateu_embaixo==FALSE){
                    auxiliar=tabela[i][j];
                    tabela[i][j]=tabela[i+1][j];
                    tabela[i+1][j]=auxiliar;
                }
            }
        }
    }

}

void Mover_direita_peca(){ //Função que faz a peça ir para a direita.
    int i, j;

    bateu_direita=FALSE;

    for(i=LINHAS; i>=0; i--){
        for(j=COLUNAS; j>=0; j--){
            if(tabela[i][j]<0 && tabela[i][j]>-10){
                if(j==9){
                    bateu_direita=TRUE;
                }
            }
        }
    }

    Copia_para_colisao();

    for(i=LINHAS; i>=0; i--){
        for(j=COLUNAS; j>=0; j--){
            if(tabela[i][j]<0){
                auxiliar=copia_tabela[i][j];
                copia_tabela[i][j]=copia_tabela[i][j+1];
                copia_tabela[i][j+1]=auxiliar;
            }
        }
    }

    Colisao();

    for(i=LINHAS; i>=0; i--){
        for(j=COLUNAS; j>=0; j--){
            if(tabela[i][j]<0 && bateu_direita==FALSE && bateu_peca==FALSE){
                auxiliar=tabela[i][j];
                tabela[i][j]=tabela[i][j+1];
                tabela[i][j+1]=auxiliar;
            }
        }
    }
}

void Mover_esquerda_peca(){ //Função que faz a peça ir para a esquerda.
    int i, j;

    bateu_esquerda=FALSE;

    for(i=LINHAS; i>=0; i--){
        for(j=COLUNAS; j>=0; j--){
            if(tabela[i][j]<0){
                if(j==0){
                    bateu_esquerda=TRUE;
                }
            }
        }
    }

    Copia_para_colisao();

    for(i=0; i<LINHAS; i++){
        for(j=0; j<COLUNAS; j++){
            if(tabela[i][j]<0){
                auxiliar=copia_tabela[i][j];
                copia_tabela[i][j]=copia_tabela[i][j-1];
                copia_tabela[i][j-1]=auxiliar;
            }
        }
    }

    Colisao();

    for(i=0; i<LINHAS; i++){
        for(j=0; j<COLUNAS; j++){
            if(tabela[i][j]<0 && bateu_esquerda==FALSE && bateu_peca==FALSE){
                auxiliar=tabela[i][j];
                tabela[i][j]=tabela[i][j-1];
                tabela[i][j-1]=auxiliar;
            }
        }
    }

}



void Tempo(){ //Função que controla o tempo de descida da peça.
    clock_t now = clock();
    double timeSinceLastDrop = (double)(now-lastDrop)/CLOCKS_PER_SEC;

    if(timeSinceLastDrop>=um_segundo*velocidade){
        lastDrop=now;
        Descer_peca();
    }
}

void Controle(){ //Função que controla o jogo.
    char str[10];

    if(menu==FALSE){
        Blocos();
        Tabuleiro();
        Hud();


        if(peca_escolhida==0){
            Pecas_possiveis();
        }

        Tempo();
        Next_peca_hud();
        Hold_peca_hud();

        CV::color(1,1,1);
        CV::text(X_FIM+(2*TAMANHO_BLOCO),
            metade_tela_vertical,
            "HIGHSCORE",
            GLUT_BITMAP_TIMES_ROMAN_24);


        sprintf(str, "%d", pontuacao_maxima);
        CV::color(1,1,1);
        CV::text(X_FIM+(7*TAMANHO_BLOCO),
            metade_tela_vertical,
            str,
            GLUT_BITMAP_TIMES_ROMAN_24);

        if(parar==TRUE){
            Game_over();

            if(pontuacao>pontuacao_maxima){
                pontuacao_maxima=pontuacao;
            }
        }
    }
    else{
        Menu_do_jogo();

    }
}


void render(){   //Função chamada continuamente. Deve-se controlar o que desenhar por meio de variaveis globais que podem ser setadas pelo metodo keyboard()
    CV::clear(0,0,0);
    Controle();

}

void keyboard(int key){  //Função chamada toda vez que uma tecla for pressionada.
    switch(key){
        case 27:
        ajuda=FALSE;
        break;

      case 65:
      case 97:
        Mover_esquerda_peca();
        break;

      case 82:
      case 114:
        Rotation();
        break;

	  case 83:
      case 115:
          if(parar==FALSE && menu==FALSE){
             pontuacao++;
          }
        Descer_peca();
        break;

	  case 99:
      case 67:
        Hold_back_end();
        break;

	  case 100:
      case 68:
        Mover_direita_peca();
        break;

   }
}

void keyboardUp(int key){   //Função chamada toda vez que uma tecla for liberada.
    switch(key){
       case 97:

         break;

	   case 83:
       case 115:

         break;

	   case 99:

         break;

	   case 100:

         break;
    }
}

void mouse(int button, int state, int wheel, int direction, int x, int y){  //Função para tratamento de mouse: cliques, movimentos e arrastos.
    mouseX = x; //Guarda as coordenadas do mouse para exibir dentro da render()
    mouseY = y;

    if(mouseX>=metade_tela_horizontal-(2*TAMANHO_BLOCO) && mouseX<=metade_tela_horizontal+(2*TAMANHO_BLOCO)
       && mouseY>=metade_tela_vertical-(0.5*TAMANHO_BLOCO) && mouseY<=metade_tela_vertical+(0.5*TAMANHO_BLOCO)){
        if(button==0 && state==0){
                if(menu==FALSE){
                    if(parar==TRUE){
                        memset(tabela, 0, sizeof tabela);
                        memset(peca, 0, sizeof peca);
                        memset(copia_tabela, 0, sizeof copia_tabela);
                        parar=FALSE;
                        peca_escolhida=0;
                        hold=0;
                        pontuacao=0;
                        cont_velocidade=0;
                        cont_linhas=0;
                    }
                }
                else{
                    menu=FALSE;
                }
        }
    }

    if(mouseX>=metade_tela_horizontal-(2*TAMANHO_BLOCO) && mouseX<=metade_tela_horizontal+(2*TAMANHO_BLOCO)
       && mouseY<=metade_tela_vertical-TAMANHO_BLOCO && mouseY>=metade_tela_vertical-(2*TAMANHO_BLOCO)){
        if(button==0 && state==0){
                if(menu==FALSE){
                    if(parar==TRUE){
                        menu=TRUE;
                        memset(tabela, 0, sizeof tabela);
                        memset(peca, 0, sizeof peca);
                        memset(copia_tabela, 0, sizeof copia_tabela);
                        parar=FALSE;
                        peca_escolhida=0;
                        hold=0;
                        pontuacao=0;
                        cont_velocidade=0;
                        cont_linhas=0;
                        ajuda=FALSE;
                    }
                }
       }
    }

    if(mouseX>=metade_tela_horizontal-(2*TAMANHO_BLOCO) && mouseX<=metade_tela_horizontal+(2*TAMANHO_BLOCO)
       && mouseY<=metade_tela_vertical-(2*TAMANHO_BLOCO)-(TAMANHO_BLOCO/2) && mouseY>=metade_tela_vertical-(3*TAMANHO_BLOCO)-(TAMANHO_BLOCO/2)){
           if(button==0 && state==0){
                if(menu==TRUE){
                    exit(0);
                }
           }

       }

    if(mouseX>=metade_tela_horizontal-(2*TAMANHO_BLOCO) && mouseX<=metade_tela_horizontal+(2*TAMANHO_BLOCO)
       && mouseY<=metade_tela_vertical-TAMANHO_BLOCO && mouseY>=metade_tela_vertical-(2*TAMANHO_BLOCO)){
           if(button==0 && state==0){
                if(menu==TRUE && parar==FALSE){
                    ajuda=TRUE;
                }
           }
       }
}

int main(void){    //Função main.
    srand(time(NULL));
    memset(tabela, 0, sizeof tabela);
    memset(peca, 0, sizeof peca);
    memset(hold_peca, 0, sizeof hold_peca);
    memset(copia_tabela, 0, sizeof copia_tabela);
    memset(peca_rotacao, 0, sizeof peca_rotacao);
    peca_proxima=(1+rand() % 7);
    CV::init(&screenWidth, &screenHeight, "TRABALHO LA - RAFAEL CARNEIRO PREGARDIER");
    CV::run();
}
