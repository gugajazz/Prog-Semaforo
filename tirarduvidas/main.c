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
}

int changeTabuleiro(int **tabuleiro, int xPosition, int yPosition, int pedra){
    if(pedra==1){
        if(tabuleiro[yPosition][xPosition]==4){
            printf("Ja exite uma pedra nessa posicao\n");
            return 1;
        }
        tabuleiro[yPosition][xPosition]=4;
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

int** ResizeTabuleiro(int *ylenght ,int *xlenght,int **tabuleiro, char mode){
    int **error=NULL;

    if(mode=='X'){
        //more xlenght
        for(int i=0;i<(*ylenght);i++){
            tabuleiro[i] = realloc( tabuleiro[i], sizeof(int) * ((*xlenght)+1) );

            if(tabuleiro[0]==NULL){
                printf("ERRO NA ALOCACAO DE MEMORIA X%d\n",i);
                return error;
            }
        }
        
        

        for(int i=0;i<(*ylenght);i++){
            int j=(*xlenght);
            tabuleiro[i][j]=6;
        }

        (*xlenght)++;
        return tabuleiro;
    }
    
    else if(mode=='Y'){
        //more ylenght
        tabuleiro = realloc( tabuleiro, sizeof(int*) * ((*ylenght)+1) );
        if(tabuleiro==NULL){
                printf("ERRO NA ALOCACAO DE MEMORIA Y1\n");
                return error;
        }
        tabuleiro[*ylenght] = malloc( sizeof(int) * ((*xlenght)) );
        if(tabuleiro[(*ylenght)]==NULL){
            printf("ERRO NA ALOCACAO DE MEMORIA Y1\n");
            return error;
        }

        for(int i=0;i<(*xlenght);i++){
            int j=(*ylenght);
            tabuleiro[j][i]=4;
        } 

        (*ylenght)++;
        return tabuleiro;
    }

    else{
        printf("MODO DESCONHECIDO");
        return error;
    }
}

void InicializaTabuleiro(int ylenght ,int xlenght,int **tab){
    for(int i=0;i<ylenght;i++){
        for(int j=0;j<xlenght;j++){
            if(tab[i][j]!=0 && tab[i][j]!=1 && tab[i][j]!=2 && tab[i][j]!=3 && tab[i][j]!=4){
                tab[i][j]=0;
            }
        }
    }
}

int main(){
    int ylenght=4, xlenght=4, posicao_valida, ModoJogo;
    int **tabuleiro;

    tabuleiro = (int**)malloc(sizeof(int*)*ylenght);
    if (tabuleiro!=NULL){
        for (int i = 0; i<ylenght; i++){
            tabuleiro[i] = (int*)malloc(sizeof(int)*xlenght);
        }
    }
    else{
        printf("Erro na alocacao de memoria\n");
    }
    
    InicializaTabuleiro(ylenght,xlenght,tabuleiro);

    printTabuleiro(ylenght,xlenght,tabuleiro);
    tabuleiro = ResizeTabuleiro(&ylenght,&xlenght,tabuleiro,'Y');
    tabuleiro = ResizeTabuleiro(&ylenght,&xlenght,tabuleiro,'Y');
    tabuleiro = ResizeTabuleiro(&ylenght,&xlenght,tabuleiro,'Y');
    tabuleiro = ResizeTabuleiro(&ylenght,&xlenght,tabuleiro,'Y');
    
    printTabuleiro(ylenght,xlenght,tabuleiro);

    /* Y=1 X=0
    0000
    0001
    0010
    0011
    0100
    0101
    0110
    0111
    1000
    1001
    1010
    1011
    1100
    1101
    1110
    1111 */

}
