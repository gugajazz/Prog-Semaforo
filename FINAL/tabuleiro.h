#ifndef TABULEIRO_H
#define TABULEIRO_H

#include "structs.h"

void InicializaTabuleiro(int **tab);

int changeTabuleiro(int **tabuleiro, int xPosition, int yPosition, int pedra);

int **ResizeTabuleiro(int *ylenght ,int *xlenght,int **tabuleiro, char mode, int *nAumentosA, int *nAumentosB);

void printTabuleiro(int **tab, int ylenght, int xlenght);

#endif