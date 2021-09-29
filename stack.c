#include "multi.h"
#include "botz.h"
#include "executar.h"
#include "stack.h"

#include <stdio.h>
#include <stdlib.h>

STACK  push (ESTADO est, STACK st) //manda um estado para a STACK
{
    STACK s = (STACK )malloc(sizeof(struct stack)); // alocar espaço para a stack

    s->valores=est; // stack de Estados
    s->prox=st;

    return s;
}

STACK pop (ESTADO *est, STACK st, char *peca, char bot) //retira um estado da STACK
{
    STACK s=NULL;

    *est = st->valores; //devolver estado anterior
    printa(*est,bot); //imprimir esse estado estado
    s=st;
    st=st->prox;

    free(s); // libertar memória

    if ((*est).peca==VALOR_X)
    {
        *peca='X';
    } else{
        *peca='O';
    }

    return(st);
}

int isEMPETY (STACK st) //verifica se uma STACK esta vazia
{
    if (st==NULL) // se for vazia
    {
        return 1;
    }

    return 0;
}