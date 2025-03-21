#include <stdio.h>
// Desafio Batalha Naval - MateCheck
// Este código inicial serve como base para o desenvolvimento do sistema de Batalha Naval.
// Siga os comentários para implementar cada parte do desafio.

    // Nível Novato - Posicionamento dos Navios
    // Sugestão: Declare uma matriz bidimensional para representar o tabuleiro (Ex: int tabuleiro[5][5];).
    // Sugestão: Posicione dois navios no tabuleiro, um verticalmente e outro horizontalmente.
    // Sugestão: Utilize `printf` para exibir as coordenadas de cada parte dos navios.

    // Nível Aventureiro - Expansão do Tabuleiro e Posicionamento Diagonal
    // Sugestão: Expanda o tabuleiro para uma matriz 10x10.
    // Sugestão: Posicione quatro navios no tabuleiro, incluindo dois na diagonal.
    // Sugestão: Exiba o tabuleiro completo no console, mostrando 0 para posições vazias e 3 para posições ocupadas.

    // Nível Mestre - Habilidades Especiais com Matrizes
    // Sugestão: Crie matrizes para representar habilidades especiais como cone, cruz, e octaedro.
    // Sugestão: Utilize estruturas de repetição aninhadas para preencher as áreas afetadas por essas habilidades no tabuleiro.
    // Sugestão: Exiba o tabuleiro com as áreas afetadas, utilizando 0 para áreas não afetadas e 1 para áreas atingidas.

    #define LINHAS 10
    #define COLUNAS 10
    #define NAVIO 3
    #define HABILIDADE 5

    void inicializarTabuleiro(int tabuleiro[LINHAS][COLUNAS]) {
        for (int i = 0; i < LINHAS; i++) {
            for (int j = 0; j < COLUNAS; j++) {
                tabuleiro[i][j] = 0;
            }
        }
    }
    
    int podePosicionar(int tabuleiro[LINHAS][COLUNAS], int linha, int coluna, char orientacao) {
        for (int i = 0; i < NAVIO; i++) {
            int r = linha, c = coluna;
            switch (orientacao) {
                case 'H': c = coluna + i; break;
                case 'V': r = linha + i; break;
                case 'D': r = linha + i; c = coluna + i; break;
                case 'E': r = linha + i; c = coluna - i; break;
            }
            if (r < 0 || r >= LINHAS || c < 0 || c >= COLUNAS || tabuleiro[r][c] != 0)
                return 0;
        }
        return 1;
    }
    
    void posicionarNavio(int tabuleiro[LINHAS][COLUNAS], int linha, int coluna, char orientacao) {
        if (podePosicionar(tabuleiro, linha, coluna, orientacao)) {
            for (int i = 0; i < NAVIO; i++) {
                int r = linha, c = coluna;
                switch (orientacao) {
                    case 'H': c = coluna + i; break;
                    case 'V': r = linha + i; break;
                    case 'D': r = linha + i; c = coluna + i; break;
                    case 'E': r = linha + i; c = coluna - i; break;
                }
                tabuleiro[r][c] = NAVIO;
            }
        } else {
            printf("Não foi possível posicionar navio em (%d, %d) na direção '%c'\n", linha, coluna, orientacao);
        }
    }
    
    void aplicarHabilidade(int tabuleiro[LINHAS][COLUNAS], int linha, int coluna, char tipo) {
        int area[5][5] = {0};
        
        if (tipo == 'C') {
            for (int i = 0; i < 5; i++) {
                area[2][i] = 1;
                area[i][2] = 1;
            }
        } else if (tipo == 'O') {
            for (int i = 0; i < 5; i++) {
                for (int j = 0; j < 5; j++) {
                    if (abs(i - 2) + abs(j - 2) <= 2) {
                        area[i][j] = 1;
                    }
                }
            }
        } else if (tipo == 'N') {
            for (int i = 0; i < 3; i++) {
                for (int j = 2 - i; j <= 2 + i; j++) {
                    area[i][j] = 1;
                }
            }
        }
        
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                int r = linha + i - 2;
                int c = coluna + j - 2;
                if (r >= 0 && r < LINHAS && c >= 0 && c < COLUNAS) {
                    if (area[i][j] == 1) {
                        tabuleiro[r][c] = HABILIDADE;
                    }
                }
            }
        }
    }
    
    void exibirTabuleiro(int tabuleiro[LINHAS][COLUNAS]) {
        printf("\n   ");
        for (int j = 0; j < COLUNAS; j++) {
            printf("%2d ", j);
        }
        printf("\n");
    
        for (int i = 0; i < LINHAS; i++) {
            printf("%2d ", i);
            for (int j = 0; j < COLUNAS; j++) {
                printf(" %d ", tabuleiro[i][j]);
            }
            printf("\n");
        }
    }
    
    int main() {
        int tabuleiro[LINHAS][COLUNAS];
        inicializarTabuleiro(tabuleiro);
    
        // Posicionamento de navios
        posicionarNavio(tabuleiro, 1, 1, 'H'); // Horizontal
        posicionarNavio(tabuleiro, 4, 4, 'V'); // Vertical
        posicionarNavio(tabuleiro, 7, 0, 'D'); // Diagonal ↘
        posicionarNavio(tabuleiro, 0, 9, 'E'); // Diagonal ↙
        
        // Aplicação de habilidades
        aplicarHabilidade(tabuleiro, 3, 3, 'C'); // Cruz
        aplicarHabilidade(tabuleiro, 6, 6, 'O'); // Octaedro
        aplicarHabilidade(tabuleiro, 2, 7, 'N'); // Cone
    
        exibirTabuleiro(tabuleiro);
    
        return 0;
    }    