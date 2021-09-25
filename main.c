// Trabalho Pratico Programacao - LEI
// DEIS-ISEC 2020-2021
//Gustavo Mateus 2020138902

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "inputs_files.h"
#include "tabuleiro.h"
#include "player_hist.h"
#include "structs.h"

int main(){
    initRandom();
    int tamanhoInicial = intUniformRnd(3, 5);
    int numeroRondas=0;

    jg.ylenght=tamanhoInicial, jg.xlenght=tamanhoInicial;
    jg.nPedrasA=0,jg.nPedrasB=0,jg.nAumentosA=0,jg.nAumentosB=0;
    jg.current_player='A';

    int posicao_valida, ModoJogo;
    int **tabuleiro;
    
    char modo, modoResize;
    int playing = 1;
    int xPosition, yPosition;
    struct historico *head = NULL;
    char NomeFicheiro[50];

    tabuleiro = (int**)malloc(sizeof(int*)*jg.ylenght);
    if (tabuleiro!=NULL){
        for (int i = 0; i<jg.ylenght; i++){
            tabuleiro[i] = (int*)malloc(sizeof(int)*jg.xlenght);

            if(tabuleiro[i]==NULL){
                printf("Erro na alocacao de memoria\n");
            }
        }
    }
    else{
        printf("Erro na alocacao de memoria\n");
    }
    
    do{
        printf("Escolha entre 1 ou 2 jogadores '1' ou '2': ");
        scanf("%d",&ModoJogo);
        printf("\n");
    }while(ModoJogo!=1 && ModoJogo!=2);

    InicializaTabuleiro(tabuleiro);
    
    while(playing){         
        posicao_valida=1;
        printTabuleiro(tabuleiro,jg.ylenght,jg.xlenght);
        
        modo = Input1(); // U, P, A ou J
        while(modo=='U' || modo=='u'){
            printf("\n"); 
            Input3(head,&jg.xlenght,&jg.ylenght,numeroRondas);
            modo = Input1(); // U, P, A ou J
        }

        if(modo=='J' || modo=='j'){
            printf("\n"); 
            Input2(tabuleiro,&jg.nPedrasA,&jg.nPedrasB,0);
        }
        else if(modo=='P' || modo=='p'){
            printf("\n"); 
            Input2(tabuleiro,&jg.nPedrasA,&jg.nPedrasB,1);
        }
        else if(modo=='A' || modo=='a'){
            printf("\n");
            modoResize = Input4();
            if(modo=='C'){
                aumentaColuna(&jg.ylenght,&jg.xlenght,tabuleiro,&jg.nAumentosA,&jg.nAumentosB);
            }
            tabuleiro = ResizeTabuleiro(&jg.ylenght,&jg.xlenght,tabuleiro,modoResize,&jg.nAumentosA,&jg.nAumentosB);
        }

        AdicionaAoHistorico(&head,tabuleiro);

        playing = checkForWinner(tabuleiro);

        if(ModoJogo==2){
            ChangeCurrentPlayer();
        }

        else if(ModoJogo==1 && playing==1){ //contra um bot
            ChangeCurrentPlayer(); //dentro dos dois changecurrentplayer o bot joga com o "B"
            char output;
            output = randomPlayer(tabuleiro);
            
            if(output=='C' || output=='L'){
                modoResize = output;
                tabuleiro = ResizeTabuleiro(&jg.ylenght,&jg.xlenght,tabuleiro,modoResize,&jg.nAumentosA,&jg.nAumentosB);
            }

            AdicionaAoHistorico(&head,tabuleiro);
            playing = checkForWinner(tabuleiro);
            ChangeCurrentPlayer();
            numeroRondas++;
        }

        if(playing==0){
            printf("\nIndique o nome do ficheiro por favor (sem a extensao): ");
            clear_buffer();
            scanf("%20s",NomeFicheiro);
            exportFile(head, NomeFicheiro);
        }
        numeroRondas++; 
    }
}
