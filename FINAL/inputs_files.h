// Trabalho Pratico Programacao - LEI
// DEIS-ISEC 2020-2021
//Gustavo Mateus 2020138902

#ifndef INPUTS_H
#define INPUTS_H

#include "structs.h"
#include "tabuleiro.h"
#include "player_hist.h"


char Input1();

void Input2(int **tabuleiro, int *nPedrasA, int *nPedrasB, int pedra);

void Input3(struct historico* head, int *xlenght, int *ylenght, int numeroRondas);

char Input4();

void exportFile(struct historico *head, char NomeFicheiro[50]);

#endif