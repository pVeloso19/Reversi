#include "multi.h"
#include "botz.h"
#include "executar.h"
#include "stack.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX 30

// Menu do jogo
void jogarMultiNovo ()
{
    ESTADO est = {0}; //Estado Inicial Vazio

    char letra,p, bot;
    char instrucaoTexto[MAX]; // Texto da Instrução
    char nomeFicheiro[MAX]; // Nome do ficheiro que se pretende guardar e/ou ler
    char peca='?'; // Peça quando começa jogo (sem nenhum jogdor)
    int dificuldade;
    int x, y, t, pos;

    STACK st=NULL; // stack onde irá todos os estados jogo

    int posisicoes[60][2] = {0}; // lista de posições válidas

    do {
        printf(" %c> ", (toupper(peca)));
        gets(instrucaoTexto);

           switch (toupper(instrucaoTexto[0])) {

                case 'N' : {
                    sscanf(instrucaoTexto, "%s %c", &letra, &p);

                    if (est.modo == 'A' || est.modo == 'M') {
                        st = push(est, st); // coloca Estado Inicial na Stack
                    }

                    if (((toupper(p)) != 'O') && ((toupper(p)) != 'X')) {
                        printf("\n Peça invalida.\n\n");

                    } else {
                        peca=p; // Peça deixa de ser '?' e fica 'X' ou 'O'
                        novoESTADO(&est, peca, 'M'); // novo estado jogo
                        pos = posicoes(est, posisicoes);
                        printa(est,bot);

                    }

                    break;
                }


                case 'L' : {

                    if (est.modo == 'A' || est.modo == 'M') {
                        st = push(est, st); // coloca estado anterior na stack
                    }

                    sscanf(instrucaoTexto, "%c %s", &letra, nomeFicheiro);

                    t = ler(&est, nomeFicheiro,&peca,&dificuldade, &bot); // carrega o ficheiro

                    if (t == 1) // se fcheiro não existir
                    {
                        printf("\n Ficheiro não encontrado\n\n");
                    }
                    else
                    {
                        printf("\n Jogo carregado com sucesso.\n");
                        pos = posicoes(est, posisicoes); // saber novas jogadas possíveis
                        printa(est,bot); // imprimir esse estado de jogo

                        if (est.peca==VALOR_X)
                        {
                            bot='O';
                        }
                        else
                        {
                            bot='X';
                        }
                    }
                    break;
                }

               case 'E' : {
                   if (peca!='?')
                   {
                       sscanf(instrucaoTexto, "%c %s", &letra, nomeFicheiro);

                       guardar(est, nomeFicheiro, dificuldade); // guarda o ficheiro com modo, jogador a jogar e difuldade(se for contra bot)

                       printf("\n Guardado com Sucesso.\n\n");
                   }
                   if ((peca=='?')&&((isEMPETY (st))==0)) // se estiver no menu inicial, ou seja, ainda não tiver inicializado jogo
                   {
                       printf("\n Impossivel gravar um tabuleiro completo.\n\n");
                   }
                   if ((peca=='?')&&((isEMPETY (st))==1))
                   {
                       printf("\n Sem Tabuleiro inicializado\n\n");
                   }
                   break;
               }

                case 'J' :
                    {
                      if (peca!='?')
                      {
                          sscanf(instrucaoTexto, "%c %d %d", &letra, &x, &y);
                          x = x - 1; // valor correspondente ao índice
                          y = y - 1; // valor correspondente ao índice

                          if (est.modo == 'M') {

                              if (validaJogada(pos, x, y, posisicoes) == 1) {
                                  st = push(est, st);

                                  comerVPositivo(&est, x, y);
                                  comerVNegativo(&est, x, y);
                                  comerHPositivo(&est, x, y);
                                  comerHNegativo(&est, x, y);
                                  comerVONeg(&est, x, y);
                                  comerHONeg(&est, x, y);
                                  comerVOPos(&est, x, y);
                                  comerHOPos(&est, x, y);
                                  colocarPeca(&est, x, y);

                                  alteraJogador(&est, &peca);
                                  printa(est,bot);
                                  pos = posicoes(est, posisicoes);

                                  if (fimDeJOGO(est) == 0)
                                  {
                                      printf(" Acabou o Jogo.\n");
                                      printf(" Vencedor: Jogador %c.\n\n", vencedor(est));
                                      peca='?'; // volta ao menu, logo não existem jogadores
                                  }

                                  if (pos == 0 && peca!='?') {
                                      alteraJogador(&est, &peca); // altera o jogador
                                      printf(" Sem jogadas disponíveis. Vez passada à peça %c.\n", peca);
                                      printa(est,bot);
                                      pos = posicoes(est, posisicoes); // cria lista de posições válidas
                                  }
                              } else {
                                  printf("\n Posicao invalida.\n\n");
                              }
                          } else {
                              if (validaJogada(pos, x, y, posisicoes) == 1) {

                                  if (pos != 0) {
                                      st = push(est, st);

                                      comerVPositivo(&est, x, y);
                                      comerVNegativo(&est, x, y);
                                      comerHPositivo(&est, x, y);
                                      comerHNegativo(&est, x, y);
                                      comerVONeg(&est, x, y);
                                      comerHONeg(&est, x, y);
                                      comerVOPos(&est, x, y);
                                      comerHOPos(&est, x, y);
                                      colocarPeca(&est, x, y);

                                      alteraJogador(&est, &peca);
                                      printa(est,bot);
                                      pos = posicoes(est, posisicoes);

                                      if (fimDeJOGO(est) == 0)
                                      {
                                          printf(" Acabou o Jogo.\n");
                                          printf(" Vencedor: Jogador %c.\n\n", vencedor(est));
                                          peca='?'; // volta ao menu, logo não existem jogadores
                                      }
                                  }

                                  if (fimDeJOGO(est) == 0 && peca!='?')
                                  {
                                      printf(" Acabou o Jogo.\n");
                                      printf(" Vencedor: Jogador %c.\n\n", vencedor(est));
                                      peca='?'; // volta ao menu, logo não existem jogadores
                                  }

                                  if(pos==0 && peca!='?')
                                  {
                                      alteraJogador(&est, &peca);
                                      printf("Sem jogadas disponíveis. Passar.\n\n");
                                      printa(est,bot);
                                  }

                                  while (pos != 0 && bot==peca) {
                                      if (dificuldade == 1) { // bot nivel 1
                                          jogaBOT(&est, posisicoes);
                                          alteraJogador(&est, &peca);
                                          printa(est,bot);

                                      } else {
                                          if (dificuldade == 2) { // bot nivel 2, percorrendo 2 niveis profundidade
                                              BOT(&est, 2);
                                              alteraJogador(&est, &peca);
                                              printa(est,bot);

                                          } else {
                                              BOT(&est, 6); // bot nivel 3, percorrendo 6 niveis profundidade
                                              alteraJogador(&est, &peca);
                                              printa(est,bot);
                                          }
                                      }

                                      pos = posicoes(est, posisicoes);

                                      if (fimDeJOGO(est) == 0)
                                      {
                                          printf(" Acabou o Jogo.\n");
                                          printf(" Vencedor: Jogador %c.\n\n", vencedor(est));
                                          peca='?'; // volta ao menu, logo não existem jogadores
                                      }

                                      if (pos == 0 && peca!='?') {
                                          printf(" Sem jogadas disponíveis. Passar.\n\n");
                                          alteraJogador(&est, &peca);
                                          pos = posicoes(est, posisicoes);
                                      }
                                  }
                                  pos = posicoes(est, posisicoes);
                              } else {
                                  printf("\n Posicao invalida.\n\n");
                              }
                          }
                      } else {
                          printf("\n Sem Tabuleiro inicializado\n\n");
                      }
                        break;
                    }
                    case 'S' : { // coloca '.' num lugar válido

                        if (peca!='?')
                        {
                            printaS(est,posisicoes,pos,bot);
                        }
                        else
                        {
                            printf("\n Sem Tabuleiro inicializado\n\n");
                        }
                        break;
                    }

                    case 'H' : {

                        if (peca!='?')
                        {
                            printaH(est,posisicoes[0][0],posisicoes[0][1],bot);
                        }
                        else
                        {
                            printf("\n Sem Tabuleiro inicializado\n\n");
                        }
                        break;
                    }

                    case 'U' :
                    {
                        if ((isEMPETY (st))==1)
                        {
                            printf("\n Impossivel refazer.\n\n");
                        }

                        else
                        {
                            st = pop(&est, st,&peca,bot);
                            pos = posicoes(est, posisicoes);
                        }
                        break;
                    }

                    case 'A' : {

                        sscanf(instrucaoTexto, "%c %c %d", &letra, &p, &dificuldade);

                        if (est.modo == 'A' || est.modo == 'M') {
                            st = push(est, st);
                        }

                        if ((toupper(p)!= 'X') && (toupper(p) != 'O'))
                        {
                            printf("\n Peca inválida.\n\n"); // peça inexistente
                        } else {
                            if (dificuldade > 3 || dificuldade < 1) { // dificuldade inválida
                                printf("\n Dificuldade inválida.\n\n");;
                            }
                            else {
                                bot=toupper(p);
                                peca=p;
                                if (toupper(peca) == 'X') {
                                    novoESTADO(&est, 'X', 'A');
                                    pos = posicoes(est, posisicoes);
                                    printaBot(est);

                                    if (dificuldade == 1) {
                                        jogaBOT(&est, posisicoes);
                                    } else {
                                        if (dificuldade == 2) {
                                            BOT(&est,2);
                                        } else {
                                            BOT(&est,6);
                                        }
                                    }

                                    alteraJogador(&est, &peca);
                                    printa(est,bot);
                                    pos = posicoes(est, posisicoes);
                                }
                                else {
                                    novoESTADO(&est, 'X', 'A');
                                    pos = posicoes(est, posisicoes);
                                    printa(est,bot);
                                    peca='X';
                                }
                            }
                        }
                        break;
                    }

                    case 'Z' : {
                        printf("\n\n Instruções:\n");
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
                        break;
                    }

                    case 'Q' : {
                        break;
                    }

                    default : {
                        printf("\n Comando invalido...\n\n");
                        break;
                    }
            }

    } while ((toupper(instrucaoTexto[0])) != 'Q');
}
