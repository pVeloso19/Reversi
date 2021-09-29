#ifndef REVERSI_EXECUTAR_H
#define REVERSI_EXECUTAR_H
#endif //REVERSI_EXECUTAR_H

void jogaBOT (ESTADO *est, int posicao[60][2]);

int maxindice (int v[],int x);

int max (int v[],int x);

int min (int v[],int x);

int avaliaESTADO (ESTADO est);

ESTADO simulaJogada (ESTADO est, int x, int y,int peca);

int recursiva (ESTADO est, int x,int peca);

int BOT (ESTADO *est,int x);
