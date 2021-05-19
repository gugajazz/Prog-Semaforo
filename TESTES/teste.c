//Gustavo Mateus 2020138902
#include <stdio.h>
#include <stdlib.h>

void printTabuleiro(int ylenght ,int xlenght,int **tab){

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
            printf(" %d | ",tab[y][x]);
        }

        printf("\n     ");
        for(int i=0;i<xlenght*5;i++){
            printf("-");
        }
        printf("\n");
    }
    printf("\n");
    //printf("\n------------------------\n\n");
}

void InicializaTabuleiro(int ylenght ,int xlenght,int **tab){
    //printf("ylenght=%d xlenght=%d\n",ylenght,xlenght);
    for(int i=0;i<ylenght;i++){
        for(int j=0;j<xlenght;j++){
            //printf("%d %d\n",i,j);
            tab[i][j]=0;
        }
        //printf("\n");
    }
}

void ResizeTabuleiro(int *ylenght ,int *xlenght,int **tabuleiro, char mode){
    if(mode=='X'){
        //more xlenght
        for ( size_t i = 0; i < (*ylenght); i++ ){
            int *tmp = realloc( tabuleiro[i], sizeof *tabuleiro[i] * ((*xlenght) + 1) );
            if(tmp!=NULL){
                tabuleiro[i] = tmp;
            }
            else{
                printf("ERRO NA ALOCACAO DE MEMORIA");
                //return 1;
            } 
        }
        for(int i=0;i<(*ylenght);i++){
            int j=(*xlenght);
            tabuleiro[i][j]=0;
        }
        (*xlenght)++; 
        //return 0;
    }
    
    else if(mode=='Y'){
        //more ylenght
        int **tmp = realloc( tabuleiro, ((*ylenght)+1) );
        if(tmp!=NULL){
            tabuleiro = tmp;
            tabuleiro[(*ylenght)] = malloc( sizeof(int) * ((*xlenght)+1) );
        }
        else{
            printf("ERRO NA ALOCACAO DE MEMORIA");
            //return 1;
        }
        for(int j=0;j<(*xlenght);j++){
            int i=(*ylenght);
            tabuleiro[i][j]=0;
        }
        (*ylenght)++;
        //return 0;
    }

    else{
        printf("MODO DESCONHECIDO");
        //return 1;
    }
}

int main(){
    //system("cls");
    int ylenght=3, xlenght=3, posicao_valida;
    int **tabuleiro;
    char current_player='A';
    int playing = 1;
    int xPosition, yPosition;

    tabuleiro = (int**)malloc(sizeof(int*)*ylenght);
    if (tabuleiro!=NULL){
        for (int i = 0; i<ylenght; i++){
            tabuleiro[i] = (int*)malloc(sizeof(int)*xlenght);
        }
    }
    else{
        printf("Erro na alocacao de memoria\n");
    }
    
    //InicializaTabuleiro(ylenght,xlenght,tabuleiro);
    //printTabuleiro(ylenght,xlenght,tabuleiro);
    //ResizeTabuleiro(&ylenght,&xlenght,tabuleiro,'X');
    //printTabuleiro(ylenght,xlenght,tabuleiro);

    //printTabuleiro(ylenght,xlenght,tabuleiro);
    //printTabuleiro(ylenght,xlenght,tabuleiro);
    //free(tabuleiro);
    //changeTabuleiro(4,4,tabuleiro,1,3);
    //checkForWinner(4,4,tabuleiro);
    //GetInput(&xPosition,&yPosition,current_player);
    //printf("%d %d",xPosition,yPosition,current_player);

    printTabuleiro(ylenght,xlenght,tabuleiro);
    ResizeTabuleiro(&ylenght,&xlenght,tabuleiro,'X');
    ResizeTabuleiro(&ylenght,&xlenght,tabuleiro,'Y');
    ResizeTabuleiro(&ylenght,&xlenght,tabuleiro,'Y');
    ResizeTabuleiro(&ylenght,&xlenght,tabuleiro,'X');
    printTabuleiro(ylenght,xlenght,tabuleiro);

    /* while(playing){
        printTabuleiro(xlenght,ylenght,tabuleiro);
        GetInput(&xPosition,&yPosition,current_player,tabuleiro, xlenght, ylenght);
        playing = checkForWinner(xlenght,ylenght,tabuleiro,&current_player);
    } */
}