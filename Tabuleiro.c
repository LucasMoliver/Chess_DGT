//
// Created by mirai on 29/05/23.
//
#include "Tabuleiro.h"
#include "../examples.h"

void exibe_matriz(char matriz[8][8]){
    for(int i =0; i < 8; i++){
        for(int j = 0;j < 8; j++){
            printf("%c ", matriz[i][j]);
        }
        printf("\n");
    }
}

bool checa_saida(char peca, bool presenca){
    if(peca != '0'){
        if(!presenca){
            return true;
        }
    }
    return false;
}

bool checa_entrada(char peca, bool presenca){
    if(peca == '0'){
        if(presenca){
            return true;
        }
    }
    return false;
}

void atualiza_presencas(bool presencas[8][8]){
    int option;
    bool *atualizacao;
    printf("Escolha uma matriz de presencas:\n\n");
    scanf("%d", &option);
    switch (option) {
        case 0:
            atualizacao = standard_ex[0];
            break;
        case 1:
            atualizacao = ex_move1[0];
            break;
        case 2:
            atualizacao = ex_move2[0];
            break;
        case 3:
            atualizacao = ex_capture1[0];
            break;
        case 4:
            atualizacao = ex_capture2[0];
            break;
        case 5:
            atualizacao = ex_capture3[0];
            break;
        case 6:
            atualizacao = ex_capture4[0];
            break;
        case 7:
            atualizacao = ex_capture5[0];
            break;
        case 8:
            atualizacao = castling1[0];
            break;
        case 9:
            atualizacao = castling2[0];
            break;
        case 10:
            atualizacao = castling3[0];
            break;
        case 11:
            atualizacao = castling4[0];
            break;
        case 12:
            atualizacao = castling5[0];
            break;
    }
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            presencas[i][j] = atualizacao[i*8 + j];
        }
    }
}

char atualiza_tabuleiro_saida(char board[8][8], int linha, int coluna){
    char k = board[linha][coluna];
    board[linha][coluna] = '0';
    return k;
}

void atualiza_tabuleiro_entrada(char board[8][8], int linha, int coluna, char nova_peca){
    board[linha][coluna] = nova_peca;
}

bool checa_mesma_cor(char primeira_empilhada, char ultima_empilhada){
    return (primeira_empilhada >= 65 && primeira_empilhada <= 90 && //checa se a primeira empilhada faz parte das pretas
            ultima_empilhada >= 65 && ultima_empilhada <= 90) || (  //e se, ao mesmo tempo, a ultima empilhada faz parte das pretas
            primeira_empilhada >= 97 && primeira_empilhada <= 122 && //OU se a primeira empilhada faz parte das brancas
            ultima_empilhada >= 97 && ultima_empilhada <= 122);      // e a ultima empilhada também.
}

void detecta_promocao(char matriz[8][8]){
    for(int i = 0; i < 8; i++){
        if(matriz[0][i] == 'P'){
            matriz[0][i] = 'Q';
        }
    }
    for(int i = 0; i < 8; i++){
        if(matriz[7][i] == 'p'){
            matriz[7][i] = 'q';
        }
    }
}
