// Trabalho Pratico Programacao - LEI
// DEIS-ISEC 2020-2021
//Gustavo Mateus 2020138902

#include <stdio.h>
#include <stdlib.h>
#include "tabuleiro.h"
#include "utils.h"
#include "inputs_files.h"
#include "structs.h"
#include "player_hist.h"


void printTabuleiro(int **tab, int ylenght, int xlenght){ //tem q ter ylenght e xlenght pq é usada par printhistorico e ele usa head->ylenght

    for(int i=0;i<xlenght;i++){
        if(i==0){
            printf("      x%d",i);
        }
        else{
            printf("   x%d",i);
        }
    }

    printf("\n     ");
        for(int i=0;i<xlenght*5;i++){
            printf("-");
        }
        printf("\n");

    for(int y=0;y<ylenght;y++){
        for(int x=0;x<xlenght;x++){
            if(x==0){
                printf("y%d  | ",y);
            }
            switch(tab[y][x]){
            case 0:
                printf("   | ");
                break;
            case 1:
                printf(" G | ");
                break;
            case 2:
                printf(" Y | ");
                break;
            case 3:
                printf(" R | ");
                break;
            case 4:
                printf(" S | ");
                break;
            
            default:
                break;
            }
        }

        printf("\n     ");
        for(int i=0;i<xlenght*5;i++){
            printf("-");
        }
        printf("\n");
    }
    printf("\n");
}

int changeTabuleiro(int **tabuleiro, int xPosition, int yPosition, int pedra){
    if(pedra==1){
        if(tabuleiro[yPosition][xPosition]==4){ //verifica que não há uma pedra onde estamos a tentar por uma pedra
            printf("Ja exite uma pedra nessa posicao\n");
            return 1;
        }
        if(tabuleiro[yPosition][xPosition]!=0){ //verifica que não há uma peca onde estamos a tentar por uma pedra
            printf("Ja exite uma peca nessa posicao\n");
            return 1;
        }
        tabuleiro[yPosition][xPosition]=4;
        if(jg.current_player=='A'){
            (jg.nPedrasA)++;
        }
        else{
            (jg.nPedrasB)++;
        }
        return 0;
    }
    if(tabuleiro[yPosition][xPosition]==0){
        tabuleiro[yPosition][xPosition]=1;
        return 0;
    }
    else if(tabuleiro[yPosition][xPosition]==1){
        tabuleiro[yPosition][xPosition]=2;
        return 0;
    }
    else if(tabuleiro[yPosition][xPosition]==2){
        tabuleiro[yPosition][xPosition]=3;
        return 0;
    }
    else{
        printf("Posicao Invalida\n");
        return 1;
    }
}

int **ResizeTabuleiro(int *ylenght ,int *xlenght,int **tabuleiro, char mode, int *nAumentosA, int *nAumentosB){

    if(mode=='C'){
        //more xlenght

        for(int i=0;i<(*ylenght);i++){
            tabuleiro[i] = realloc( tabuleiro[i], sizeof(int) * ((*xlenght)+1) );

            if(tabuleiro[0]==NULL){
                printf("ERRO NA ALOCACAO DE MEMORIA X%d\n",i);
                return NULL;
            }
        }

        for(int i=0;i<(*ylenght);i++){
            int j=(*xlenght);
            tabuleiro[i][j]=0;
        }

        (*xlenght)++;
        if(jg.current_player=='A'){
            (*nAumentosA)++;
        }
        else if(jg.current_player=='B'){
            (*nAumentosB)++;
        }
        return tabuleiro;
    }
    
    else if(mode=='L'){
        //more ylenght
        tabuleiro = realloc( tabuleiro, sizeof(int*) * ((*ylenght)+1) );
        if(tabuleiro==NULL){
                printf("ERRO NA ALOCACAO DE MEMORIA Y1\n");
                return NULL;
        }
        tabuleiro[*ylenght] = malloc( sizeof(int) * ((*xlenght)) );
        if(tabuleiro[(*ylenght)]==NULL){
            printf("ERRO NA ALOCACAO DE MEMORIA Y2\n");
            return NULL;
        }

        for(int i=0;i<(*xlenght);i++){
            int j=(*ylenght);
            tabuleiro[j][i]=0;
        } 

        (*ylenght)++;
        if(jg.current_player=='A'){
            (*nAumentosA)++;
        }
        else{
            (*nAumentosB)++;
        }
        return tabuleiro;
    }

    else{
        printf("MODO DESCONHECIDO");
        return NULL;
    }
}

void InicializaTabuleiro(int **tab){
    for(int i=0;i<jg.ylenght;i++){
        for(int j=0;j<jg.xlenght;j++){
            if(tab[i][j]!=0 && tab[i][j]!=1 && tab[i][j]!=2 && tab[i][j]!=3 && tab[i][j]!=4){
                tab[i][j]=0;
            }
        }
    }
}

