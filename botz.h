#ifndef REVERSI_BOTZ_H
#define REVERSI_BOTZ_H
#endif //REVERSI_BOTZ_H

int validarVNeg(ESTADO *a, int l, int c);

int validarVPos(ESTADO *a, int l, int c);

int validarHNeg(ESTADO *a, int l, int c);

int validarHPos(ESTADO *a, int l, int c);

int validarHONeg(ESTADO *a, int l, int c);

int validarHOPos(ESTADO *a, int l, int c);

int validarVONeg(ESTADO *a, int l, int c);

int validarVOPos(ESTADO *a, int l, int c);

void comerVPositivo (ESTADO *est, int x, int y);

void comerHPositivo (ESTADO *est, int x, int y);

void comerVNegativo (ESTADO *est, int x, int y);

void comerHNegativo (ESTADO *est, int x, int y);

void comerVONeg (ESTADO *est, int x, int y);

void comerVOPos (ESTADO *est, int x, int y);

void comerHOPos (ESTADO *est, int x, int y);

void comerHONeg (ESTADO *est, int x, int y);

void colocarPeca (ESTADO *a, int l, int c);

void alteraJogador(ESTADO *est,char *peca);

int validaOK(ESTADO *est, int l, int c);

int fimDeJOGO (ESTADO est);

void guardar (ESTADO est, char nome[], int dif);

int ler (ESTADO *est, char nome[], char *p, int *dificuldade, char *bot);

void novoESTADO (ESTADO *est, char peca, char modo);

void converteTAB (ESTADO est, char tab[8][8]);

void desconverterTAB (ESTADO *est, char tab[8][8]);

void printa(ESTADO est,char b);

int grelhaCompleta (ESTADO *est);

int posicoes (ESTADO est, int posisicoes[60][2]);

int validaJogada (int pos, int x, int y, int posicao[60][2]);

void printaH (ESTADO est, int x, int y,char b);

void printaS (ESTADO est, int posicao[60][2], int max,char b);

int quantasTem (ESTADO est,int *o, char bot);

int quantasTemM (char tab [8][8],int *o);

void printaBot (ESTADO est);

char vencedor (ESTADO est);