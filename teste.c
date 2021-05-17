#include <stdio.h>
#include <stdlib.h>

void printTabuleiro(int ylenght ,int xlenght,int **tab){

    /* for(int i=0;i<xlenght;i++){
        if(i==0){
            printf("      x%d",i);
        }
        else{
            printf("   x%d",i);
        }
    } */

    /* printf("\n     ");
        for(int i=0;i<xlenght*5;i++){
            printf("-");
        }
        printf("\n"); */

    for(int y=0;y<ylenght;y++){
        for(int x=0;x<xlenght;x++){
            /* if(x==0){
                printf("y%d  | ",y);
            } */
            printf(" %d | ",tab[y][x]);
        }

        /* printf("\n     ");
        for(int i=0;i<xlenght*5;i++){
            printf("-");
        } */
        printf("\n");
    }
    printf("\n");
    //printf("\n------------------------\n\n");
}

void InicializaTabuleiro(int ylenght ,int xlenght,int **tab){
    printf("ylenght=%d xlenght=%d\n",ylenght,xlenght);

    for(int i=0;i<ylenght;i++){
        for(int j=0;j<xlenght;j++){
            printf("%d %d\n",i,j);
            tab[i][j]=0;

        }
        printf("\n");
    }
}


void main(){
    int xlenght=10, ylenght=10;
    int **tabuleiro;
    
    tabuleiro = (int**)malloc(sizeof(int*)*ylenght);
    if (tabuleiro!=NULL){
        for (int i = 0; i<ylenght; i++){
            printf("i=%d\n",i);
            tabuleiro[i] = (int*)malloc(sizeof(int)*xlenght);
        }
    }
    else{
        printf("ERRO FODAO");
    }

    InicializaTabuleiro(ylenght,xlenght,tabuleiro);
    printTabuleiro(ylenght,xlenght,tabuleiro);

}






