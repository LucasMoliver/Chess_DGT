//
// Created by mirai on 29/05/23.
//
#include "../Pilha/Pilha.h"

#ifndef XADREZ_TABULEIRO_H
#define XADREZ_TABULEIRO_H

/*
 * função exibe_matriz
 * @param matriz: matriz a ser exibida
 */
void exibe_matriz(char matriz[8][8]);

/*
 * função checa_saida
 * @param peca: peça a ser verificada
 * @param presenca: leitura do hardware
 * @return bool: true se saiu, false se não
 */
bool checa_saida(char peca, bool presenca);

/*
 * função checa_entrada
 * @param peca: peça a ser verificada
 * @param presenca: leitura do hardware
 * @return bool: true se entrou, false se não
 */
bool checa_entrada(char peca, bool presenca);

/*
 * função atualiza_presencas
 * @param presencas: leitura a ser atualizada
 * TODO: Varredura oficial
 */
void atualiza_presencas(bool presencas[8][8]);

/*
 * função atualiza_tabuleiro_saida
 * @param board: tabuleiro de xadrez
 * @param linha: index da linha do elemento que será removido
 * @param coluna: index da coluna do elemento que será removido
 * @return char: peca removida
 */
char atualiza_tabuleiro_saida(char board[8][8], int linha, int coluna);

/*
 * função atualiza_tabuleiro_saida
 * @param board: tabuleiro de xadrez
 * @param linha: index da linha do elemento que será inserido
 * @param coluna: index da coluna do elemento que será inserido
 * @return char: peca removida
 */
void atualiza_tabuleiro_entrada(char board[8][8], int linha, int coluna, char nova_peca);

/*
 *função checa_mesma_cor
 * @param primeira_empilhada: primeira peça que foi empilhada
 * @param ultima_empilhada: peça a ser comparada com a primeira
 * @return bool: true se forem de mesma cor, false caso contrário
 */
bool checa_mesma_cor(char primeira_empilhada, char ultima_empilhada);

/*
 * função detecta_promocao
 * @param matriz: tabuleiro de xadrez
 */
void detecta_promocao(char matriz[8][8]);
#endif //XADREZ_TABULEIRO_H
