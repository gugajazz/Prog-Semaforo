#include <stdio.h>
#include <stdlib.h>
void InicializaTabuleiro(int ylenght ,int xlenght,int **tab){
    //printf("ylenght=%d xlenght=%d\n",ylenght,xlenght);
    for(int i=0;i<ylenght;i++){
        for(int j=0;j<xlenght;j++){
            printf("%d %d\n",i,j);
            tab[i][j]=0;
        }
        printf("\n");
    }
}

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

void main(){
    int **array;
    int ROWS=4,COLS=4;

    array = (int**)malloc(sizeof(int*)*ROWS);
    if (array!=NULL){
        for (int i = 0; i<ROWS; i++){
            array[i] = (int*)malloc(sizeof(int)*COLS);
        }
    }
    else{
        printf("ERRO FODAO");
    }

    //OLD
    /* array = malloc( sizeof *array * ROWS );
    if ( array )
    {
    for ( size_t i = 0; i < ROWS; i++ )
        array[i] = malloc( sizeof *array[i] * COLS );
    } */

    //ROWS
    int **tmp = realloc( array, sizeof *array * (ROWS + 1) );
    if ( tmp )
    {
    array = tmp;
    for ( size_t i = 0; i < 1; i++ )
    {
        array[ROWS + i] = malloc( sizeof *array[ROWS + i] * COLS );
    }
    }
    ROWS++; 

    //COLS
    /* for ( size_t i = 0; i < ROWS; i++ )
    {
    int *tmp = realloc( array[i], sizeof *array[i] * (COLS + 1) );
    if ( tmp )
    {
        array[i] = tmp;
    } 
    }
    COLS++; */

    InicializaTabuleiro(ROWS,COLS,array);
    printTabuleiro(ROWS,COLS,array);
}
