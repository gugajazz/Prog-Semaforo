// Trabalho Pratico Programacao - LEI
// DEIS-ISEC 2020-2021
//Gustavo Mateus 2020138902

#ifndef TABULEIRO_H
#define TABULEIRO_H

#include "structs.h"
#include "inputs_files.h"
#include "utils.h"
#include "player_hist.h"

void InicializaTabuleiro(int **tab);

int changeTabuleiro(int **tabuleiro, int xPosition, int yPosition, int pedra);

int **ResizeTabuleiro(int *ylenght ,int *xlenght,int **tabuleiro, char mode, int *nAumentosA, int *nAumentosB);

void printTabuleiro(int **tab, int ylenght, int xlenght);

#endif