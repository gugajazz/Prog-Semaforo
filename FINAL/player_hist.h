#ifndef PLAYER_HIST_H
#define PLAYER_HIST_H

#include "structs.h"
#include "tabuleiro.h"
#include "inputs_files.h"

void AdicionaAoHistorico(struct historico** head, int **tabela_atual);

int checkForWinner(int **tabuleiro);

void ChangeCurrentPlayer();

void PrintHistorico(struct historico *head, int num_jogadas);

char randomPlayer(int **tabuleiro);

#endif
