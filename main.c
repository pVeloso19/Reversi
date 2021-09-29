#include <stdio.h>
#include "multi.h"


// Apresentar instruções sempre que se entra no jogo
int main(){
            printf(" Bem Vindo...\n\n");
            printf(" Instruções:\n");
            printf(" N <peça>: Novo jogo em que o primeiro a jogar é o jogador com peça.\n");
            printf(" L <ficheiro>: Ler um jogo de ficheiro.\n");
            printf(" E <ficheiro>: Escrever em ficheiro estado do jogo.\n");
            printf(" J <L> <C>): Jogar peça atual na posição (L,C).\n");
            printf(" A <peça> <nível>: jogo contra 'bot' que joga com a <peça> e com dificuldade <nível> (1<=nível<=3).\n");
            printf(" S: Imprimir um ponto '.' nas posições com jogada válida.\n");
            printf(" H: Sugestão de jogada. É colocado um '?' no sitio sugerido.\n");
            printf(" U: Desfazer a última jogada (Undo).\n");
            printf(" Z: Instruções.\n\n");
            printf(" Q: Sair.\n\n");
            jogarMultiNovo();
return 0;
}