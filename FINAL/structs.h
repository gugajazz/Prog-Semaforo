#ifndef STRUCTS_H
#define STRUCTS_H

struct historico{
    int xlenght;
    int ylenght;
    char current_player;
    int **tabuleiro;

    struct historico *next;
};

struct dados_jogo{
    int ylenght;
    int xlenght; 
    int nPedrasB;
    int nPedrasA;
    int nAumentosB;
    int nAumentosA;
    int current_player;
};

struct dados_jogo jg;

#endif