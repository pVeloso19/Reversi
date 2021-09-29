#include "multi.h"
#include "botz.h"
#include "executar.h"
#include "stack.h"

#include <stdio.h>
#include <ctype.h>
#include <ctype.h>
#include <stdlib.h>

void jogaBOT (ESTADO *est, int posicao[60][2]) // faz com que o bot jogue na primeira jogada possivel
{
    int x=0,y=0;

    x=posicao[0][0]; // coordenada x da 1º posição válida
    y=posicao[0][1]; // coordenada y da 1º posição válida

    //comer as peças
    comerVPositivo(est, x, y);
    comerVNegativo(est, x, y);
    comerHPositivo(est, x, y);
    comerHNegativo(est, x, y);
    comerVONeg(est, x, y);
    comerHONeg(est, x, y);
    comerVOPos(est, x, y);
    comerHOPos(est, x, y);
    colocarPeca(est, x, y);
}

int maxindice (int v[],int x) //retorna o indice do maximo valor de um vetor
{
    int r=v[0];
    int indice=0;

    for (int i=1;i<x;i++)
    {
        if (r<v[i])
        {
            r=v[i];
            indice=i;
        }
    }

    return indice;
}

int max (int v[],int x) //retorna o maximo de um vetor de inteiros
{
    int r=v[0];

    for (int i=1;i<x;i++)
    {
        if (r<v[i])
        {
            r=v[i];
        }
    }
    return r;
}

int min (int v[],int x) //retorna o minimo de um vetor de inteiros
{
    int r=v[0];

    for (int i=1;i<x;i++)
    {
        if (r>v[i])
        {
            r=v[i];
        }
    }
    return r;
}

int avaliaESTADO (ESTADO est) // avalia um estado atrvés de notas por posiçoes
{
    int r=0;
    int tab[8][8] = {{120,-20,20,5,5,20,-20,120},
                     {-20,-40,-5,-5,-5,-5,-40,-20},
                     {20,-5,15,3,3,15,-5,20},
                     {5,-5,3,3,3,3,-5,5},
                     {5,-5,3,3,3,3,-5,5},
                     {20,-5,15,3,3,15,-5,20},
                     {-20,-40,-5,-5,-5,-5,-40,-20},
                     {120,-20,20,5,5,20,-20,120}};

    // igualar grelha ao tabuleiro
    for (int i=0;i<8;i++)
    {
        for (int j=0;j<8;j++)
        {
            if (est.grelha[i][j] == est.peca){
                r += tab[i][j];
            }
        }
    }

    return r;
}

ESTADO simulaJogada (ESTADO est, int x, int y,int peca){ // retorna o ESTADO da jogada simulada

    ESTADO new;

    //copiar informações para um novo estado, de maneira a não alterar o própio estado (simula)
    new.modo = est.modo;

    new.peca = est.peca;

    for (int i=0; i<8; i++){
        for (int j=0; j<8; j++){
            new.grelha[i][j] = est.grelha[i][j];
        }
    }

    //come as peças
    comerVPositivo(&new, x, y);
    comerVNegativo(&new, x, y);
    comerHPositivo(&new, x, y);
    comerHNegativo(&new, x, y);
    comerVONeg(&new, x, y);
    comerHONeg(&new, x, y);
    comerVOPos(&new, x, y);
    comerHOPos(&new, x, y);
    colocarPeca(&new, x, y);

    return new;
}

int recursiva (ESTADO est, int x, int peca){ //funçao que vai fazer as jogadas recursivamente e avalias-a consoante o miniMax;

    int l=0;
    int max1;
    int posicao[60][2];
    ESTADO new;
    int v[30];

    if (peca==1)
    {est.peca = VALOR_X;}
    else
    {est.peca = VALOR_O;}

    if (x==0)
    {

        return avaliaESTADO(est); // retorna valor do tabuleiro
    }

    else
    {
        max1 = posicoes(est,posicao); // nº jogadas válidas, bem como vetor com jogadas possíveis(posicao)

        for (l=0; l<max1; l++)
        {
            new = simulaJogada(est,posicao[l][0],posicao[l][1],peca); // simulação da 1º jogada
            v[l] = recursiva(new,x-1,1-peca); // aplicar recursivamente a função, mas para níveis sucessivamente menores
        }

        if (x%2==0) // se for a vez do Adversário, maximiza jogada
        {
            return max(v,max1);
        }
        else // se for a vex do Jogador, minimiza jogada
        {
            return min(v,max1);
        }
    }
}

int BOT(ESTADO *est,int x){ // funçao responsavel pelo bot jogar através da estrategia MinMax

    int max;
    int posicao[60][2];
    int r;
    int v[100];
    int peca;
    ESTADO new;

    if (est->peca == VALOR_X){
        peca = 1;
    }
    else{
        peca = 0;
    }

    max = posicoes(*est,posicao); // nº jogadas válidas, bem como vetor com jogadas possíveis(posicao)

    for (int l=0; l<max; l++)
    {
        new = simulaJogada(*est,posicao[l][0],posicao[l][1],peca); // simulação da 1º jogada
        v[l] = recursiva(new,x-1,1-peca); // aplicar recursivamente a função, mas para níveis sucessivamente menores
    }

    r=maxindice (v,max); // no final, jogada de maior valor

    //comer peças
    comerVPositivo(est, posicao[r][0], posicao[r][1]);
    comerVNegativo(est, posicao[r][0], posicao[r][1]);
    comerHPositivo(est, posicao[r][0], posicao[r][1]);
    comerHNegativo(est, posicao[r][0], posicao[r][1]);
    comerVONeg(est, posicao[r][0], posicao[r][1]);
    comerHONeg(est, posicao[r][0], posicao[r][1]);
    comerVOPos(est, posicao[r][0], posicao[r][1]);
    comerHOPos(est, posicao[r][0], posicao[r][1]);
    colocarPeca(est, posicao[r][0], posicao[r][1]);

    return r;
}

