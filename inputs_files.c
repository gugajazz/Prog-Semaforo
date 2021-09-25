// Trabalho Pratico Programacao - LEI
// DEIS-ISEC 2020-2021
//Gustavo Mateus 2020138902

#include <stdio.h>
#include <stdlib.h>
#include "inputs_files.h"
#include "utils.h"
#include "tabuleiro.h"
#include "structs.h"
#include "player_hist.h"

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
        //fflush(stdin);
        clear_buffer();
        scanf("%c",&escolha);
        if(escolha=='P' || escolha=='A' || escolha=='J' || escolha=='U' || escolha=='p' || escolha=='a' || escolha=='j' || escolha=='u'){
            
            if(escolha=='P' && jg.current_player=='A' && jg.nPedrasA>=1 || escolha=='p' && jg.current_player=='A' && jg.nPedrasA>=1){
                printf("\nJa utilizou todas as pedras disponiveis\n");
            }
            else if(escolha=='P' && jg.current_player=='B' && jg.nPedrasB>=1 || escolha=='p' && jg.current_player=='B' && jg.nPedrasB>=1){
                printf("\nJa utilizou todas as pedras disponiveis\n");
            }
            else if(escolha=='A' && jg.current_player=='A' && jg.nAumentosA>=2 || escolha=='a' && jg.current_player=='A' && jg.nAumentosA>=2){
                printf("\nJa utilizou todos os aumentos disponiveis\n");
            }
            else if(escolha=='A' && jg.current_player=='B' && jg.nAumentosB>=2 || escolha=='a' && jg.current_player=='B' && jg.nAumentosB>=2){
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
            //fflush(stdin);
            clear_buffer();
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

        //fflush(stdin);
        clear_buffer();
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
        //fflush(stdin);
        clear_buffer();
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

void clear_buffer(){
    int i;
    do{
        i = getchar();
    }while ( i != '\n' && i != EOF );
    return;
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

/* 
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
} */

/* 
void read_bin(){

    FILE *fp = fopen("jogo.bin", "rb");

    fseek(fp, 0, SEEK_END);
    long tamanho = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    printf("\ntamanho=%d\n",tamanho);
    char *temp = malloc(tamanho + 1);
    fread(temp, 1, tamanho, fp);
    temp[tamanho]='\0';
    printf("%s\n",temp);
    fclose (fp);

    struct historico *(recuperado) = (struct historico*) malloc(sizeof(struct historico));

    int my_ylenght, my_xlenght;

    int i=0, pos_lista=0;
    for(;temp[i]!='Z';i=i+1,pos_lista+=2){ //pos_lista mais dois pq deve haver um problema c a aloc de memoria e assim nao como o outro tabuleiro

        printf("++++%d\n",i);
        int posJ=i;

        for(;temp[i]!='X';i++){}
        printf("ate proximo X:%d\n\n",i); //tamanho da string até ao proximo X (uma jogada)
        
        my_ylenght=posJ+3;//numero de numeros ate ao proximo x
        //printf("antes:%d\n",my_ylenght);
        for(;temp[my_ylenght]!='K';my_ylenght++){}
        my_ylenght-=posJ+3;
        printf("my_ylenght:%d\n\n",my_ylenght); //tamanho da string até ao proximo X (uma jogada)
    
        int num_ks=0;
        my_xlenght=posJ+3; //numero de k do inicio ate ao x (altura/numero de linhas)
        for(;temp[my_xlenght]!='X';my_xlenght++){
            if(temp[my_xlenght]=='K'){
                num_ks++;
            }
        }
        my_xlenght=num_ks;
        printf("my_xlenght:%d\n\n",my_xlenght);


        //--------------------------------------------------------

        (recuperado+pos_lista)->tabuleiro = (int**)malloc(sizeof(int*)*my_ylenght);
        if (recuperado->tabuleiro!=NULL){
            for (int i = 0; i<my_ylenght; i++){
                (recuperado+pos_lista)->tabuleiro[i] = (int*)malloc(sizeof(int)*my_xlenght);
            }
        }
        else{
            printf("Erro na alocacao de memoria hh1\n");
        }



        

        for(int j=posJ+3, l=0, c=0; temp[j+1]!='X' ;j++){  //j=3 para saltar o jogador atual, ylenght e xlenght
            if(temp[j]=='K'){
                //printf("\n");
                c=0;
                j++;
                l++;
            }
            
            printf("%d %d\n",l,c);
            (recuperado+pos_lista)->tabuleiro[l][c]=temp[j] - '0';
            //printf("%c",temp[j]);
            c++;
        }

        printf("\n\n");
        for(int i=0;i<5;i++){
            for(int j=0;j<4;j++){
                printf("%d ",(recuperado+pos_lista)->tabuleiro[i][j]);
            }
            printf("\n");
        }
    }


    /*printf("\n\n");
        for(int i=0;i<my_ylenght;i++){
            for(int j=0;j<my_xlenght;j++){
                printf("%d ",(recuperado+2)->tabuleiro[i][j]);
            }
            printf("\n");
    } 

    FromFile->current_player = temp[0];
    FromFile->ylenght = temp[1] - '0'; // char - '0' resulta no int correspondente
    FromFile->xlenght = temp[2] - '0'; 

    //printf("\n\n%c %d %d",FromFile->current_player,FromFile->ylenght,FromFile->xlenght);
    //printf("tamanho 1 jogada=%d",3+ylenght*xlenght);
    //printf("\ntamanho 1 jogada=%d",3+(5*5));
} */



