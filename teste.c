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
            printf("%d %d\n",i,j);
            //tab[i][j]=0;
        }
        printf("\n");
    }
}

int main(){
    int ylenght=4, xlenght=4;
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
        printf("ERRO FODAO");
    }
    
    InicializaTabuleiro(ylenght,xlenght,tabuleiro);
    printTabuleiro(ylenght,xlenght,tabuleiro);
    
/*     for ( size_t i = 0; i < (xlenght); i++ ){
            int *tmp = realloc( tabuleiro[i], sizeof *tabuleiro[i] * ((ylenght) + 1) );
            if ( tmp ){
                tabuleiro[i] = tmp;
            }
    }
    (ylenght)++; */

    for ( size_t i = 0; i < (xlenght); i++ ){
        printf("%d\n",i);
            tabuleiro[i] = realloc( tabuleiro[i], sizeof *tabuleiro[i] * ((ylenght) + 1) );
    }
    (ylenght)++;

    //printf("%d",ylenght);
    InicializaTabuleiro(ylenght,xlenght,tabuleiro);
    printTabuleiro(ylenght,xlenght,tabuleiro);
}




























