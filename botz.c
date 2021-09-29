#include "multi.h"
#include "botz.h"
#include "executar.h"
#include "stack.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// Tabuleiro é o vetor de char [8][8] correspondente á grelha do jogo;

int validaOK (ESTADO *a, int l, int c){ // verifica se a posicao esta vazia, através de um estado e das coordenadas de uma posição

    if (a->grelha[l][c] == VAZIA){
        return 0;
    }
    else{
        return 1;
    }
}

void colocarPeca (ESTADO *a, int l, int c){ // coloca a peça no tabuleiro

    a->grelha[l][c] = a->peca;
}


int validarHPos(ESTADO *a, int l, int c){ // verifica, com base no conteúdo do tabuleiro na mesma linha e em colunas superiores, se pode jogar numa posição

    int i=c;
    int valor=1;

    if (l>=0 && l<8) {
        while (i < 8) { // não pode ultrapassar limites do tabuleiro
            if (a->grelha[l][i + 1] == a->peca || a->grelha[l][i + 1] == VAZIA || i+1>=7) { // se nessas coordenadas (novas) estiver uma peça sua ou estiver vazia
                return 1;

            } else {
                if (a->grelha[l][i + 2] != a->peca) {
                    if (a->grelha[l][i + 2] == VAZIA || i + 2 >= 7) { // se nessas coordenadas (novas) estiver vazia
                        return 1;
                    } else {
                        valor++;
                        i++;
                    }
                } else {
                    valor = 0;
                    break;
                }
            }
        }
    }
return valor;
}

int validarHNeg(ESTADO *a, int l, int c){ // verifica, com base no conteúdo do tabuleiro na mesma linha e em colunas inferiores, se pode jogar numa posição
    int i=c;
    int valor=1;

    if (l>=0 && l<8) {
        while (i >= 0) { // não pode ultrapassar limites do tabuleiro
            if (a->grelha[l][i - 1] == a->peca || a->grelha[l][i - 1] == VAZIA || i-1<=0) { // se nessas coordenadas (novas) estiver uma peça sua ou estiver vazia
                valor = 1;
                break;
            } else {
                if (a->grelha[l][i - 2] != a->peca) {
                    if (a->grelha[l][i - 2] == VAZIA || i - 2 <= 0) { // se nessas coordenadas (novas) estiver vazia
                        return 1;
                    } else {
                        valor++;
                        i--;
                    }
                } else {
                    valor = 0;
                    break;
                }
            }
        }
    }
return valor;
}


int validarVPos(ESTADO *a, int l, int c){ // verifica, com base no conteúdo do tabuleiro na mesma coluna e em linhas inferiores, se pode jogar numa posição
    int i=l;
    int valor=1;

    if (c>=0 && c<8) {
        while (i >= 0) {// não pode ultrapassar limites do tabuleiro
            if (a->grelha[i - 1][c] == a->peca || a->grelha[i - 1][c] == VAZIA || i-1<=0) { // se nessas coordenadas (novas) estiver uma peça sua ou estiver vazia
                valor = 1;
                break;
            } else {
                if (a->grelha[i - 2][c] != a->peca ) { // se nessas coordenadas (novas) estiver vazia
                    if (a->grelha[i - 2][c] == VAZIA || (i - 2 <= 0)) {
                        return 1;
                    } else {
                        valor++;
                        i--;
                    }
                } else {
                    valor = 0;
                    break;
                }
            }
        }
    }


return valor;
}

int validarVNeg(ESTADO *a, int l, int c) {  // verifica, com base no conteúdo do tabuleiro na mesma coluna e em linhas superiores, se pode jogar numa posição
    int i = l;
    int valor = 1;

    if (c >= 0 && c < 8) {
        while (i < 8) { // não pode ultrapassar limites do tabuleiro
            if (a->grelha[i + 1][c] == a->peca || a->grelha[i + 1][c] == VAZIA || i+1>=7) { // se nessas coordenadas (novas) estiver uma peça sua ou estiver vazia
                return 1;
            } else {
                if (a->grelha[i + 2][c] != a->peca) {
                    if (a->grelha[i + 2][c] == VAZIA || i + 2 >= 7) { // se nessas coordenadas (novas) estiver vazia
                        return 1;
                    } else {
                        valor++;
                        i++;
                    }

                } else {
                    valor = 0;
                    break;
                }
            }
        }

        return valor;
    }
}

void comerHPositivo (ESTADO *est, int x, int y) {  // come as peças á sua direits (se a jogada for possível)

    int i = y;

    if (validarHPos(est, x, y) == 0 && validaOK(est, x, y) == 0) { // condições necessárias para poder comer nesse sentido

        while (i < 8 && est->grelha[x][i + 1] != est->peca) { // enquanto não encontrar uma peça sua, irá comer
            if ((est->grelha[x][i + 1] != VAZIA)) { // se essa posição não for vazia, come
                est->grelha[x][i + 1] = est->peca;
                i++;
            } else {
                break;
            }
        }
    }
}

void comerHNegativo (ESTADO *est, int x, int y) { // come as peças á sua esquerda (se a jogada for possível)

    int i = y;

    if (validarHNeg(est, x, y) == 0 && validaOK(est, x, y) == 0) { // condições necessárias para poder comer nesse sentido

        while (i > 0 && est->grelha[x][i - 1] != est->peca) { // enquanto não encontrar uma peça sua, irá comer
            if ((est->grelha[x][i - 1] != VAZIA)) { // se essa posição não for vazia, come
                est->grelha[x][i - 1] = est->peca;
                i--;
            } else {
                break;
            }
        }
    }
}

void comerVPositivo (ESTADO *est, int x, int y) { // come as peças acima desta(se a jogada for possível)

    int i = x;

    if (validarVPos(est, x, y) == 0 && validaOK(est, x, y) == 0) { // condições necessárias para poder comer nesse sentido

        while (i > 0 && (est->grelha[i - 1][y] != est->peca)) { // enquanto não encontrar uma peça sua, irá comer
            if (est->grelha[i - 1][y] != VAZIA ) { // se essa posição não for vazia, come
                est->grelha[i - 1][y] = est->peca;
                i--;
            } else {
                break;
            }
        }
    }
}

void comerVNegativo (ESTADO *est, int x, int y) { // come as peças abaixo desta(se a jogada for possível)

    int i = x;

    if (validarVNeg(est, x, y) == 0 && validaOK(est, x, y) == 0) { // condições necessárias para poder comer nesse sentido

        while (i < 8 && est->grelha[i + 1][y] != est->peca) { // enquanto não encontrar uma peça sua, irá comer
            if ((est->grelha[i + 1][y] != VAZIA)) { // se essa posição não for vazia, come
                est->grelha[i + 1][y] = est->peca;
                i++;
            } else {
                break;
            }
        }
    }
}

int validarHOPos(ESTADO *a, int l, int c){ // verifica, com base no conteúdo do tabuleiro num eixo obliquo(de declive -1 e sentido positivo), se pode jogar numa posição

    int i=c;
    int j=l;
    int valor=1;

    if (j>=0 && j< 8 && i<8 && i>=0) {
        while (i < 8 && j < 8) { // não pode ultrapassar limites do tabuleiro
            if (a->grelha[j + 1][i + 1] == a->peca || a->grelha[j + 1][i + 1] == VAZIA || i+1>=7 || j+1>=7) { // se nessas coordenadas (novas) estiver uma peça sua ou estiver vazia
                return 1;
            } else {
                if (a->grelha[j + 2][i + 2] != a->peca) {
                    if (a->grelha[j + 2][i + 2] == VAZIA || j + 2 >= 7 || i + 2 >= 7) { // se nessas coordenadas (novas) estiver vazia
                        return 1;
                    } else {
                        valor++;
                        j++;
                        i++;
                    }

                } else {
                    return 0;
                }
            }
        }
    }
return valor;
}

int validarHONeg(ESTADO *a, int l, int c){ // verifica, com base no conteúdo do tabuleiro num eixo obliquo(de declive 1 e sentido positivo), se pode jogar numa posição

    int i=c;
    int j=l;
    int valor=1;

    if (j>=0 && j< 8 && i<8 && i>=0) {
        while (i >= 0 && j < 8) { // não pode ultrapassar limites do tabuleiro
            if (a->grelha[j + 1][i - 1] == a->peca || a->grelha[j + 1][i - 1] == VAZIA || j+1>=7 || i-1 <= 0) { // se nessas coordenadas (novas) estiver uma peça sua ou estiver vazia
                return 1;
            } else {
                if (a->grelha[j + 2][i - 2] != a->peca) {
                    if (a->grelha[j + 2][i - 2] == VAZIA || j + 2 >=7  || i - 2 <= 0) { // se nessas coordenadas (novas) estiver vazia
                        return 1;
                    } else {
                        valor++,
                        j++;
                        i--;
                    }

                } else {
                    return 0;
                }
            }
        }
    }
return valor;
}

int validarVONeg(ESTADO *a, int l, int c){ // verifica, com base no conteúdo do tabuleiro num eixo obliquo(de declive 1 e sentido negativo), se pode jogar numa posição

    int i=c;
    int j=l;
    int valor=1;

    if (j>=0 && j< 8 && i<8 && i>=0) {
        while (i < 8 && j >= 0) { // não pode ultrapassar limites do tabuleiro
            if (a->grelha[j - 1][i + 1] == a->peca || a->grelha[j - 1][i + 1] == VAZIA || j-1<=0 || i+1>=7) { // se nessas coordenadas (novas) estiver uma peça sua ou estiver vazia
                return 1;
            } else {
                if (a->grelha[j - 2][i + 2] != a->peca) {
                    if (a->grelha[j - 2][i + 2] == VAZIA || j - 2 <= 0 || i + 2 >= 7) { // se nessas coordenadas (novas) estiver vazia
                        return 1;
                    } else {
                        valor++;
                        j--;
                        i++;
                    }
                } else {
                    return 0;
                }
            }
        }
    }
    return valor;
}

int validarVOPos(ESTADO *a, int l, int c){ // verifica, com base no conteúdo do tabuleiro num eixo obliquo(de declive -1 e sentido negativo), se pode jogar numa posição

    int i=c;
    int j=l;
    int valor=1;

    if (j>=0 && j< 8 && i<8 && i>=0) {
        while (i >= 0 && j >= 0) { // não pode ultrapassar limites do tabuleiro
            if (a->grelha[j - 1][i - 1] == a->peca || a->grelha[j - 1][i - 1] == VAZIA || i-1 <= 0 || j-1 <= 0) { // se nessas coordenadas (novas) estiver uma peça sua ou estiver vazia
                return 1;
            } else {
                if (a->grelha[j - 2][i - 2] != a->peca) {
                    if (a->grelha[j - 2][i - 2] == VAZIA || j - 2 <=0 || i - 2 <= 0) { // se nessas coordenadas (novas) estiver vazia
                        return 1;
                    } else {
                        valor++;
                        i--;
                        j--;
                    }

                } else {
                    return 0;
                }
            }
        }
    }
    return valor;
}

void comerHOPos (ESTADO *est, int x, int y) { // come as peças no seguimento do eixo oblíquo(de declive -1 e sentido positivo), se a jogada for possível)

    int i = y;
    int j = x;

    if (validarHOPos(est, x, y) == 0 && validaOK(est, x, y) == 0) { // condições necessárias para poder comer nesse sentido

        while (i<8 && j<8 && est->grelha[j+1][i+1] != est->peca) { // enquanto não encontrar uma peça sua, irá comer
            if ((est->grelha[j+1][i+1] != VAZIA)) { // se essa posição não for vazia, come
                est->grelha[j+1][i+1] = est->peca;
                i++;
                j++;
            } else {
                break;
            }
        }
    }
}

void comerHONeg (ESTADO *est, int x, int y) { // come as peças no seguimento do eixo oblíquo(de declive 1 e sentido positivo), se a jogada for possível)

    int i = y;
    int j = x;

    if (validarHONeg(est, x, y) == 0 && validaOK(est, x, y) == 0) { // condições necessárias para poder comer nesse sentido

        while (i>=0 && j<8 &&  est->grelha[j+1][i-1] != est->peca) { // enquanto não encontrar uma peça sua, irá comer
            if ((est->grelha[j+1][i-1] != VAZIA)) { // se essa posição não for vazia, come
                est->grelha[j+1][i-1] = est->peca;
                i--;
                j++;
            } else {
                break;
            }
        }
    }
}

void comerVOPos (ESTADO *est, int x, int y) { // come as peças no seguimento do eixo oblíquo(de declive -1 e sentido negativo), se a jogada for possível)

    int i = y;
    int j = x;

    if (validarVOPos(est, x, y) == 0 && validaOK(est, x, y) == 0) { // condições necessárias para poder comer nesse sentido

        while (i>=0 && j>=0 && est->grelha[j-1][i-1] != est->peca) { // enquanto não encontrar uma peça sua, irá comer
            if ((est->grelha[j-1][i-1] != VAZIA)) { // se essa posição não for vazia, come
                est->grelha[j-1][i-1] = est->peca;
                i--;
                j--;
            } else {
                break;
            }
        }
    }
}

void comerVONeg (ESTADO *est, int x, int y) { // come as peças no seguimento do eixo oblíquo(de declive 1 e sentido negativo), se a jogada for possível)

    int i = y;
    int j = x;

    if (validarVONeg(est, x, y) == 0 && validaOK(est, x, y) == 0) { // condições necessárias para poder comer nesse sentido

        while (i<8 && j>=0 && est->grelha[j - 1][i + 1] != est->peca) { // enquanto não encontrar uma peça sua, irá comer
            if ((est->grelha[j-1][i+1] != VAZIA)) { // se essa posição não for vazia, come
                est->grelha[j-1][i+1] = est->peca;
                i++;
                j--;
            } else {
                break;
            }
        }
    }
}

void alteraJogador(ESTADO *est,char *peca) // altera o ESTADO e a peça para o proximo jogador
{
    if (est->peca == VALOR_X){
        est->peca = VALOR_O;
        *peca='O';
    }
    else{
        est->peca = VALOR_X;
        *peca='X';
    }
}

void guardar (ESTADO est, char nome[], int dif) // guardar estado jogo
{
    FILE *ficheiro = fopen(nome, "wt"); // abrir ficheiro de maneira a puder lê-lo e escrever nele
    int i;
    int j;
    char tab[8][8];
    char peca;

    converteTAB(est,tab); // converte a grelha para um tabuleiro

    if (est.peca==VALOR_X)
    {
        peca='X'; // saber a peça do jogador e transformá-la num caracter
    }
    else
    {
        peca='O';
    }

    if (est.modo=='A') // se o modo estiver no Automático
    {
        fprintf(ficheiro, "%c %c %d\n", est.modo, peca, dif); // escreve no início do ficheiro o modo, peça do jogador e a dificuldade do bot
    }
    else // se modo estiver no Manual
    {
        fprintf(ficheiro, "%c %c\n", est.modo, peca); // escreve no inicio do ficheiro modo e peça do jogador a jogar
    }

    for (i=0; i<8; i++){
        for (j=0; j<8; j++){
            fprintf(ficheiro, "%c ", tab[i][j]);
        }
        fprintf(ficheiro, "\n"); // escreve o tabuleiro no ficheiro
    }

    fclose(ficheiro); // fechar ficheiro
}

int ler (ESTADO *est, char nome[], char *p, int *dificuldade, char *bot){   // ler estado do jogo

    FILE *ficheiro = fopen(nome, "r"); // abrir ficheiro para puder lê-lo
    int i=0;
    char tab[8][8];

    if (ficheiro==NULL){return 1;} // se não existir ficheiro com esse nome

    fscanf(ficheiro,"%c %c %d", &est->modo,p, dificuldade); // obter o modo, a peca e a dificuldade(se houver) do estado jogo desse ficheiro

    if (toupper(*p)=='X')
    {
        est->peca=VALOR_X; // converter peca para Jogador
        *bot='O';
    }
    else
    {
        est->peca=VALOR_O;
        *bot='X';
    }

    for (i=0; i<8; i++){
        for (int j=0; j<8; j++){
            fscanf(ficheiro," %c", &tab[i][j]); // valores do tabuleiro guardados num array multidimensional
        }
    }

    desconverterTAB (est,tab); // passar do tabuleiro para a grelha de jogo

    return 0;
}

void novoESTADO (ESTADO *est, char peca, char modo) // inicia o ESTADO com o estado Inicial de um jogo
{
    for (int l=0;l<8;l++)
    {
        for (int c=0;c<8;c++)
        {
            est->grelha[l][c]=VAZIA; // inicializar grelha com todas as posições vazias
        }
    }
    // alterar grelha
    est->grelha[3][3]=VALOR_X;
    est->grelha[3][4]=VALOR_O;
    est->grelha[4][3]=VALOR_O;
    est->grelha[4][4]=VALOR_X;

    if ((toupper(peca))=='X') // saber Peça
    {
        est->peca=VALOR_X;
    }
    else
    {
        est->peca=VALOR_O;
    }

    est->modo=(toupper(modo)); // saber Modo
}

void converteTAB (ESTADO est, char tab[8][8]) // transforma um grelha(do estado) num tabuleiro
{
    for (int i=0;i<8;i++)
    {
        for (int j=0;j<8;j++)
        {
            if (est.grelha[i][j]==VAZIA) {tab[i][j]='-';}
            if (est.grelha[i][j]==VALOR_O) {tab[i][j]='O';}
            if (est.grelha[i][j]==VALOR_X) {tab[i][j]='X';}
        }
    }
}

void desconverterTAB (ESTADO *est, char tab[8][8]) //Transforma um tabuleiro numa grelha(do estado)
{
    for (int i=0;i<8;i++)
    {
        for (int j=0;j<8;j++)
        {
            if (tab[i][j]=='-') {est->grelha[i][j]=VAZIA;}
            if (tab[i][j]=='O') {est->grelha[i][j]=VALOR_O;}
            if (tab[i][j]=='X') {est->grelha[i][j]=VALOR_X;}
        }
    }
}

void printa(ESTADO est,char b){ // escrever o tabuleiro

    char tabuleiro [8][8];
    char peca;
    int bot=0, adv=0;

    if ((est.peca==VALOR_X)&&(est.modo=='M')) // imprimir peça do jogador
    {
        peca='X';
    }

    if ((est.peca==VALOR_O)&&(est.modo=='M'))
    {
        peca='O';
    }

    if ((b=='X')&&(est.modo=='A')) // imprimir peça do jogador
    {
        peca='O';
    }

    if ((b=='O')&&(est.modo=='A'))
    {
        peca='X';
    }

    converteTAB (est,tabuleiro);

    printf("\n");

    printf("   1 2 3 4 5 6 7 8\n"); // imprimir o nº de colunas
    for(int i = 0; i < 8; i++)
    {
        printf(" %d ", i+1);
        for(int j = 0; j < 8; j++)
        {
            printf("%c ", tabuleiro[i][j]); // imprimir tabuleiro
        }
        printf("\n");
    }

    if (est.modo == 'M') // modo Manual
    {
        adv = quantasTemM (tabuleiro,&bot); // nº peças do jogador X
        printf("\n Minha Peça: %c   Modo: %c \n \n", peca, est.modo);
        printf(" Peças X:%d\n Peças O:%d\n\n", adv, bot);
    }
    else // modo Automático
    {
        adv = quantasTem (est,&bot, b); // nº peças do jogador
        printf("\n Minha Peça: %c   Modo: %c \n \n",peca ,est.modo);
        printf(" Pecas %c:%d\n Peças Bot:%d\n\n", peca ,bot, adv); // nº peças jogador e bot

    }
}


int grelhaCompleta (ESTADO *est){ //função que retorna o numero de posições vazias

    int resultado=0;

    for (int i=0; i<8; i++){
        for (int j=0; j<8; j++){
            if (est->grelha[i][j] != VALOR_X && est->grelha[i][j] != VALOR_O){ // se for Vazia
                resultado++;
            }
        }
    }
return resultado;
}

int posicoes (ESTADO est, int posisicoes[60][2]) //preenche um vetor com as posiçoes validas
{                                                //na  posicao [i][0] fica o valor da cordenada x e na [i][1] o valor da cordenada y
    int pos=0;

    for (int i=0;i<8;i++)
    {
        for (int j=0;j<8;j++)
        {
            if ((validaOK(&est, i, j) == 0) &&
                 ((validarVPos(&est, i, j) == 0) ||
                  (validarVNeg(&est, i, j) == 0) ||
                  (validarHPos(&est, i, j) == 0) ||
                  (validarHNeg(&est, i, j) == 0) ||
                  (validarVONeg(&est, i, j) == 0) ||
                  (validarHONeg(&est, i, j) == 0) ||
                  (validarVOPos(&est, i, j) == 0) ||
                  (validarHOPos(&est, i, j) == 0)))
            {
                posisicoes[pos][0]=i;
                posisicoes[pos][1]=j;
                pos++;
            }
        }
    }
    return pos;
}

int validaJogada (int pos, int x, int y, int posicao[60][2]) //verifica se a posicao que recebe pertence a lista de posicoes validas
{
    for (int i=0;i<pos;i++)
    {
        if ((posicao[i][0]==x)&&(posicao[i][1]==y)) // se pertencer à lista
        {
            return 1;
        }
    }
    return 0;
}


char vencedor (ESTADO est) //retorna o caracter da peça vencedora
{
    int x=0, o=0;

    for (int i=0;i<8;i++)
    {
        for (int j=0;j<8;j++)
        {
            if (est.grelha[i][j]==VALOR_X) {x++;}
            if (est.grelha[i][j]==VALOR_O) {o++;}
        }
    }

    if (x<o) // compara nº peças de cada jogador
    {
        return 'O';
    }
    else
        {return 'X';}
}


int fimDeJOGO (ESTADO est) //printa no ecrã a mensagem do vencedor e termina o jogo
{
    int pos1,pos2;
    int posicao [60][2];
    char peca='O';

    if (grelhaCompleta(&est) == 0) { // se grelha estiver completa
        return 0;
        }

    pos1 = posicoes(est, posicao); // saber nºposições válidas para um jogador

    alteraJogador(&est,&peca);

    pos2 = posicoes(est, posicao); // saber nºposições válidas para adversário

    if ((pos1==0)&&(pos2==0)) // nenhum jogador puder jogar
    {
        return 0;
    }

return 1;
}

void printaH (ESTADO est, int x, int y,char b){ // escrever o tabuleiro com a sugestao de jogada ('?')

    char tabuleiro [8][8];
    char peca;
    int bot=0,adv=0;

    if (est.peca==VALOR_X)
    {
        peca='X';
    }
    else
    {
        peca='O';
    }

    converteTAB (est,tabuleiro);
    tabuleiro[x][y]='?'; // coloca '?' na 1º posição válida

    //imprimir tabuleiro jogo
    printf("\n");

    printf("   1 2 3 4 5 6 7 8\n");
    for(int i = 0; i < 8; i++)
    {
        printf(" %d ", i+1);
        for(int j = 0; j < 8; j++)
        {
            printf("%c ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    if (est.modo == 'M') // modo Manual
    { // imprimir informações dos jogadores
        adv = quantasTemM (tabuleiro,&bot);
        printf("\n Minha Peça: %c   Modo: %c \n \n", peca, est.modo);
        printf(" Peças X:%d\n Peças O:%d\n\n", adv, bot);
    }
    else // modo Automático
    {
        adv = quantasTem (est,&bot, b); // nº peças do jogador
        printf("\n Minha Peça: %c   Modo: %c \n \n",peca ,est.modo);
        printf(" Pecas %c:%d\n Peças Bot:%d\n\n", peca ,bot, adv); // nº peças jogador e bot

    }
}

void printaS (ESTADO est, int posicao[60][2], int max,char b){ // escrever o tabuleiro com as posicoes validas para o jogador que vai jogar

    char tabuleiro [8][8];
    char peca;
    int bot=0,adv=0;

    if (est.peca==VALOR_X)
    {
        peca='X';
    }
    else
    {
        peca='O';
    }

    converteTAB (est,tabuleiro);

    //colocar '.' nas posições válidas
    for (int i=0;i<max;i++)
    {
        tabuleiro[posicao[i][0]][posicao[i][1]]='.';
    }

    //imprimir tabuleiro
    printf("\n");

    printf("   1 2 3 4 5 6 7 8\n");
    for(int i = 0; i < 8; i++)
    {
        printf(" %d ", i+1);
        for(int j = 0; j < 8; j++)
        {
            printf("%c ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    if (est.modo == 'M') // modo Manual
    { // imprimir informações dos jogadores
        adv = quantasTemM (tabuleiro,&bot);
        printf("\n Minha Peça: %c   Modo: %c \n \n", peca, est.modo);
        printf(" Peças X:%d\n Peças O:%d\n\n", adv, bot);
    }
    else // modo Automático
    {
        adv = quantasTem (est,&bot, b); // nº peças do jogador
        printf("\n Minha Peça: %c   Modo: %c \n \n",peca ,est.modo);
        printf(" Pecas %c:%d\n Peças Bot:%d\n\n", peca ,bot, adv); // nº peças jogador e bot

    }
}

int quantasTem (ESTADO est,int *o, char bot) // retorna  o numero de peças que o x tem e manda no apontador *o as peças para o O apos receber um ESTADO
{
    int r1=0;
    int r2=0;
    VALOR vb;

    if (bot=='X')
    {
        vb=VALOR_X;
    }
    else
    {
        vb=VALOR_O;
    }

    for (int i=0;i<8;i++)
    {
        for (int j=0;j<8;j++)
        {
            if (est.grelha[i][j]==vb)
            {r1++;}
            else
            {
                if(est.grelha[i][j]!=VAZIA)
                {r2++;}
            }
        }
    }

    *o=r2;
    return r1;
}

int quantasTemM (char tab [8][8],int *o) // retorna  o numero de peças que o x e manda no apontador *o as peças para o O apos receber um tabuleiro
{
    int r1=0;
    int r2=0;

    for (int i=0;i<8;i++)
    {
        for (int j=0;j<8;j++)
        {
            if (tab[i][j]=='X')
            {r1++;}
            if (tab[i][j]=='O')
            {r2++;}
        }
    }

    *o=r2;
    return r1;
}


void printaBot (ESTADO est){ // escrever o tabuleiro inicial para jogar contra bot

    char tabuleiro [8][8];
    char peca;

    if (est.peca==VALOR_X)
    {
        peca='O';
    }
    else
    {
        peca='X';
    }

    converteTAB (est,tabuleiro);

    // imprimir tabuleiro
    printf("   1 2 3 4 5 6 7 8\n");
    for(int i = 0; i < 8; i++)
    {
        printf(" %d ", i+1);
        for(int j = 0; j < 8; j++)
        {
            printf("%c ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    // imprimir informações dos jogadores
    printf("\n Minha Peça: %c   Modo: %c \n \n", peca, est.modo);
    printf(" Pecas %c:2\n Peças Bot:2\n\n", peca);
}