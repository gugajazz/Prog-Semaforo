// Trabalho Pratico Programacao - LEI
// DEIS-ISEC 2020-2021
//Gustavo Mateus 2020138902

#include <stdio.h>
#include <stdlib.h>
#include "inputs_files.h"
#include "utils.h"

char Input1(){
    //devolve U ou P ou A ou J
    int loop_escolha=1;
    char escolha;

    if(jg.current_player=='A'){
        printf("Vez do jogador A \n[ %d Pedra e %d Aumento(s) disponiveis ]\n",1-jg.nPedrasA,2-jg.nAumentosA);
    }
    else if(jg.current_player=='B'){
        printf("Vez do jogador B \n[ %d Pedra e %d Aumento(s) disponiveis ]\n",1-jg.nPedrasB,2-jg.nAumentosB);
    }

    while(loop_escolha){
        printf("\nindique o que pretende:\n\tVer as ultimas jogadas (U)\n\tColocar uma pedra (P),\n\tAumentar o tabuleiro (A)\n\tJogar(J)\n\tSair(S)\n\t-> ");
        fflush(stdin);
        scanf("%c",&escolha);
        if(escolha=='P' || escolha=='A' || escolha=='J' || escolha=='U' || escolha=='p' || escolha=='a' || escolha=='j' || escolha=='u'){
            if(escolha=='P' || escolha=='p' && jg.current_player=='A' && jg.nPedrasA>=1){
                printf("\nJa utilizou todas as pedras disponiveis\n");
            }
            else if(escolha=='P' || escolha=='p' && jg.current_player=='B' && jg.nPedrasB>=1){
                printf("\nJa utilizou todas as pedras disponiveis\n");
            }
            else if(escolha=='A' || escolha=='a' && jg.current_player=='A' && jg.nAumentosA>=2){
                printf("\nJa utilizou todos os aumentos disponiveis\n");
            }
            else if(escolha=='A' || escolha=='a' && jg.current_player=='B' && jg.nAumentosB>=2){
                printf("\nJa utilizou todos os aumentos disponiveis\n");
            }
            else{ //se nao houver nenhuma restricao que se aplique sair e devolver a escolha
                loop_escolha=0;
            } 
        }
        else if(escolha=='S' || escolha=='s'){
            printf("\n");
            exit(0);
        }
        else{
            printf("\nEscolha apenas entre U, P, A J ou S");
        }
    }
    return escolha;
}

void Input2(int **tabuleiro, int *nPedrasA, int *nPedrasB, int pedra){
    int loop_jogar,xPosition,yPosition;
    while(loop_jogar){
            printf("Escolha a posicao em que quer jogar (x y): ");
            fflush(stdin);
            scanf("%d %d",&xPosition,&yPosition);

            if(xPosition>=jg.xlenght || yPosition>=jg.ylenght || xPosition<0 || yPosition<0){
                printf("Posicao Invalida\n");
            }
            else{
                loop_jogar = changeTabuleiro(tabuleiro,xPosition,yPosition,pedra);
            }
        }
}

void Input3(struct historico* head, int *xlenght, int *ylenght, int numeroRondas){
    int k,loop_ultimas;
    while(loop_ultimas){
        printf("Numero de jogadas decorridas -> %d\n",numeroRondas);
        printf("Indique o numero de jogadas anteriores a visualisar: ");

        fflush(stdin);
        scanf("%d",&k);
        if(k>=0 && k<=numeroRondas){ //não permite q o numero de jogadas q pretende visualizar seja maior do q as já jogadas
            PrintHistorico(head,k);
            loop_ultimas = 0;
        }
        else{
            printf("Indique um numero menor ou igual as jogadas decorridas\n");
        }
    }
}

char Input4(){
    char escolhaResize;
    while(1){
        printf("Pretende aumentar uma linha (L) ou coluna (C)?:");
        fflush(stdin);
        scanf("%c",&escolhaResize);
        if(escolhaResize=='C' || escolhaResize=='c'){
            escolhaResize='C';
            return escolhaResize;
        }
        else if(escolhaResize=='L' || escolhaResize=='l'){
            escolhaResize='L';
            return escolhaResize;
        }
        else{
            printf("Escolha apenas entre L ou C\n");
        }
        
    }
}

void exportFile(struct historico *head, char NomeFicheiro[50]){

    int m=0, contador_jogadas=1;
    char winner;

    do{
        m++;
    }while(NomeFicheiro[m]!='\0');
    NomeFicheiro[m]='.';
    NomeFicheiro[m+1]='t';
    NomeFicheiro[m+2]='x';
    NomeFicheiro[m+3]='t';
    NomeFicheiro[m+4]='\0';

    FILE *fp;
    fp = fopen (NomeFicheiro,"w");

    fprintf(fp,"\n+-+-+-+-+-+-+-HISTORICO-+-+-+-+-+-+-+-+\n\n");

    while(head!=NULL){

        fprintf(fp, "Jogada numero %d feita por %c\n",contador_jogadas,head->current_player);

        for(int i=0;i<head->xlenght;i++){
            if(i==0){
                fprintf(fp,"      x%d",i);
            }
            else{
                fprintf(fp,"   x%d",i);
            }
        }

        fprintf(fp,"\n     ");
            for(int i=0;i<head->xlenght*5;i++){
                fprintf(fp,"-");
            }
            fprintf(fp,"\n");

        for(int y=0;y<head->ylenght;y++){
            for(int x=0;x<head->xlenght;x++){
                if(x==0){
                    fprintf(fp,"y%d  | ",y);
                }
                switch(head->tabuleiro[y][x]){
                case 0:
                    fprintf(fp,"   | ");
                    break;
                case 1:
                    fprintf(fp," G | ");
                    break;
                case 2:
                    fprintf(fp," Y | ");
                    break;
                case 3:
                    fprintf(fp," R | ");
                    break;
                case 4:
                    fprintf(fp," S | ");
                    break;
                
                default:
                    break;
                }
            }

            fprintf(fp,"\n     ");
            for(int i=0;i<head->xlenght*5;i++){
                fprintf(fp,"-");
            }
            fprintf(fp,"\n");
        }
        fprintf(fp,"\n");


            contador_jogadas++;
            winner=head->current_player;
            head = head->next;
    }

    fprintf(fp,"!!! O JOGADOR '%c' VENCEU !!!\n\n",winner);
    fprintf(fp,"+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+\n");
    fclose (fp);

}

void write_bin(struct historico *head){
    FILE *fp = fopen ("jogo.bin","wb");

    while(head!=NULL){
        fprintf(fp, "%c%d%d",head->current_player,head->ylenght,head->xlenght);
        for(int i=0; i<head->ylenght; i++){
            for(int j=0; j<head->xlenght; j++){
                fprintf(fp,"%d",head->tabuleiro[i][j]);
            }
            fprintf(fp,"K");
        }
        fprintf(fp,"X");
        head = head->next;
    }
    fprintf(fp,"Z");
    fclose (fp);
}

