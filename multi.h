#ifndef REVERSI_MULTI_H
#define REVERSI_MULTI_H
#endif //REVERSI_MULTI_H

// definição de valores possiveis no tabuleiro
typedef enum {VAZIA, VALOR_X, VALOR_O} VALOR;


 typedef struct estado { //Estrutura que armazena o estado do jogo
    VALOR peca; // peça do jogador que vai jogar!
    VALOR grelha[8][8];
    char modo; // modo em que se está a jogar! 0-> manual, 1-> contra computador
} ESTADO;

typedef struct stack { // Guardar todos estados jogo
    ESTADO valores;
    struct stack *prox;
} *STACK;


void jogarMultiNovo ();









