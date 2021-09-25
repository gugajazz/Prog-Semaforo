// Trabalho Pratico Programacao - LEI
// DEIS-ISEC 2020-2021
//Gustavo Mateus 2020138902

#include <stdio.h>
#include <stdlib.h>
#include "player_hist.h"
#include "utils.h"
#include "inputs_files.h"
#include "tabuleiro.h"
#include "structs.h"



void ChangeCurrentPlayer(){
    if(jg.current_player=='A'){
        jg.current_player='B';
    }
    else if(jg.current_player=='B'){
        jg.current_player='A';
    }
    else{
        printf("Erro, jogador nao e nem A nem B\n");
    }
}

int checkForWinner(int **tabuleiro){
    int equal_straight=0, last_equal;
    //horizontal
    for(int y=0;y<jg.ylenght;y++){
        if(tabuleiro[y][0]!=0){
            last_equal=tabuleiro[y][0];

            for(int x=1;x<jg.xlenght;x++){
                if(tabuleiro[y][x]==last_equal){
                    equal_straight++;
                }
            }

            if(equal_straight==jg.xlenght-1){
                printTabuleiro(tabuleiro,jg.ylenght,jg.xlenght);
                printf("PLAYER %c IS THE WINNER\n",jg.current_player);
                return 0;
            }
            else{
                equal_straight=0;
            }
        }        
    }

    equal_straight=0;
    //vertical
    for(int x=0;x<jg.xlenght;x++){
        if(tabuleiro[0][x]!=0){
            last_equal=tabuleiro[0][x];
            for(int y=1;y<jg.ylenght;y++){
                if(tabuleiro[y][x]==last_equal){
                    equal_straight++;
                }
            }
            printf("\n");
        
            if(equal_straight==jg.ylenght-1){
                printTabuleiro(tabuleiro,jg.ylenght,jg.xlenght);
                printf("PLAYER %c IS THE WINNER\n",jg.current_player);
                return 0;
            }
            else{
                equal_straight=0;
            }
        }        
    }

    //diagonal esquerda p direita
    if(tabuleiro[0][0]!=0){
        equal_straight=0;
        last_equal=tabuleiro[0][0];
        if(jg.xlenght==jg.ylenght){
            for(int i=1;i<jg.xlenght;i++){
                if(tabuleiro[i][i]==last_equal){
                    equal_straight++;
                }
            }
            if(equal_straight==jg.xlenght-1){
                printTabuleiro(tabuleiro,jg.ylenght,jg.xlenght);
                printf("PLAYER %c IS THE WINNER\n",jg.current_player);
                return 0;
            }
        }
    }

    //diagonal direita p esquerda
    if(tabuleiro[0][jg.xlenght-1]!=0){
        equal_straight=0;
        last_equal=tabuleiro[0][jg.xlenght-1];
        if(jg.xlenght==jg.ylenght){
            for(int x=jg.xlenght-2, y=1 ;x>=0; x--,y++){
                if(tabuleiro[y][x]==last_equal){
                    equal_straight++;
                }
            }
            if(equal_straight==jg.xlenght-1){
                printTabuleiro(tabuleiro,jg.ylenght,jg.xlenght);
                printf("PLAYER %c IS THE WINNER\n",jg.current_player);
                return 0;
            }
        }
    }
    return 1;
}

void AdicionaAoHistorico(struct historico** head, int **tabela_atual){

	struct historico *new_historico = (struct historico*) malloc(sizeof(struct historico));

	struct historico *last = *head;
    /*****************************************************************/
    //IGUAL A CRIAR UM TABULEIRO PELA PRIMEIRA VEZ NO MAIN
    new_historico->tabuleiro = (int**)malloc(sizeof(int*)*jg.ylenght);
    if (new_historico->tabuleiro!=NULL){
        for (int i = 0; i<jg.ylenght; i++){
            new_historico->tabuleiro[i] = (int*)malloc(sizeof(int)*jg.xlenght);
        }
    }
    else{
        printf("Erro na alocacao de memoria historico\n");
    }

    for(int i=0; i<jg.ylenght; i++){
        for(int j=0; j<jg.xlenght; j++){
            new_historico->tabuleiro[i][j] = tabela_atual[i][j];
        }
    }

    new_historico->xlenght=jg.xlenght;
    new_historico->ylenght=jg.ylenght;
    new_historico->current_player=jg.current_player;
    /*****************************************************************/
	new_historico->next = NULL;

	if (*head == NULL){
        *head = new_historico;
        return;
	}
    else{
        while (last->next != NULL) //enquanto o last n for o ultimo 
            last = last->next;

        
        last->next = new_historico; /*aponta o penultimo p o q criamos agr*/
        return;
    }
}

void PrintHistorico(struct historico *head, int num_jogadas){
    int contador_jogadas=1;
    printf("\n+-+-+-+-+-+-+-HISTORICO-+-+-+-+-+-+-+-+\n\n");
    while(head!=NULL && num_jogadas>0){
        printf("Jogada numero %d feita por %c\n",contador_jogadas,head->current_player);
        printTabuleiro(head->tabuleiro,head->ylenght,head->xlenght);
        contador_jogadas++;
        head = head->next;
        num_jogadas--; //para só mostrar o numero de jogadas pedido
    }
    printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+\n");
} 

char randomPlayer(int **tabuleiro){
    initRandom();
    int output_change = 1, xpos, ypos, pedra, aumentar, coluna;

    
    pedra = intUniformRnd(0, 100); 
    aumentar = intUniformRnd(0, 100);


    if(pedra<=30 && jg.nPedrasB<1){ //30% de prob de jogar uma pedra
        pedra=1;
    }
    else{
        pedra=0;
    }

    if(pedra==0 && aumentar<=30 && jg.nAumentosB<2){
        coluna = intUniformRnd(0, 1);
        if(coluna==1){
            printf("\nO computador aumentou uma linha no tabuleiro\n");
            return 'L';
        }
        else{
            printf("\nO computador aumentou uma coluna no tabuleiro\n");
            return 'C';
        }
        jg.nAumentosB++;
    }

    do{
        xpos = intUniformRnd(0, jg.xlenght-1);
        ypos = intUniformRnd(0, jg.ylenght-1);
        output_change = changeTabuleiro(tabuleiro, xpos, ypos,pedra); //devolve 1 se for invalida
    }while(output_change);

    if(pedra==1){
        printf("\nO computador jogou uma pedra na posicao x%d y%d\n\n",xpos,ypos);
    }
    else{
        printf("\nO computador jogou na posicao x%d y%d\n\n",xpos,ypos);
    }
    return 'X';
}