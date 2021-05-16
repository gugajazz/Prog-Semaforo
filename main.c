//Gustavo Mateus 2020138902
#include <stdio.h>
#include <stdlib.h>

void printTabuleiro(int ylenght ,int xlenght,int tab[ylenght][xlenght]){

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

int changeTabuleiro(int xlenght ,int ylenght,int tab[xlenght][ylenght], int xPosition, int yPosition){
    if(xPosition>xlenght || yPosition>ylenght || xPosition<0 || yPosition<0){
        printf("Posicao Invalida");
        return 0;
    }

    if(tab[xPosition][yPosition]==0){
        tab[xPosition][yPosition]=1;
        return 1;
    }
    else if(tab[xPosition][yPosition]==1){
        tab[xPosition][yPosition]=2;
        return 1;
    }
    else if(tab[xPosition][yPosition]==2){
        tab[xPosition][yPosition]=3;
        return 1;
    }
    else{
        printf("Posicao Invalida\n");
        return 0;
    }
}

int checkForWinner(int xlenght ,int ylenght,int tab[ylenght][xlenght]){
    int equal_straight=0, last_equal;
    //horizontal
    for(int y=0;y<ylenght;y++){
        if(tab[y][0]!=0){
            last_equal=tab[y][0];

            for(int x=1;x<xlenght;x++){
            if(tab[y][x]==last_equal){
                equal_straight++;
            }
            printf("x=%d y=%d val=%d las=%d strai=%d\n",x,y,tab[y][x],last_equal,equal_straight);
        }
        printf("\n");

        if(equal_straight==3){
            printf("WINNER\n");
            return 1;
        }
        else{
            equal_straight=0;
        }
        }        
    }

    equal_straight=0;
    //vertical
    for(int x=0;x<xlenght;x++){
        if(tab[0][x]!=0){
            last_equal=tab[0][x];

            for(int y=1;y<ylenght;y++){
            if(tab[y][x]==last_equal){
                equal_straight++;
            }
            printf("x=%d y=%d val=%d las=%d strai=%d\n",x,y,tab[y][x],last_equal,equal_straight);
        }
        printf("\n");
        
        if(equal_straight==3){
            printf("WINNER\n");
            return 1;
        }
        else{
            equal_straight=0;
        }
        }        
    }

    //diagonal esquerda p direita
    if(tab[0][0]!=0){
        equal_straight=0;
        last_equal=tab[0][0];
        if(xlenght==ylenght){
            for(int i=1;i<xlenght;i++){
                if(tab[i][i]==last_equal){
                    equal_straight++;
                }
            }
            if(equal_straight==xlenght-1){
                printf("WINNER");
            }
        }
    }

    //diagonal direita p esquerda
    if(tab[0][xlenght-1]!=0){
        equal_straight=0;
        last_equal=tab[0][xlenght-1];
        if(xlenght==ylenght){
            for(int x=xlenght-2, y=1 ;x>=0; x--,y++){
                if(tab[y][x]==last_equal){
                    equal_straight++;
                }
            }
            if(equal_straight==xlenght-1){
                printf("WINNER");
            }
        }
    }
}

void GetInput(int *xPosition, int *yPosition, char current_player){
    printf("Vez do jogador %c\n",current_player);
    printf("Escolha a posicao em que quer jogar (x y): ");
    scanf("%d %d",xPosition,yPosition);
}

void Add(int ylenght ,int xlenght,int tab[ylenght][xlenght],){

}

void main(){
    int tabuleiro[][] = *malloc(sizeof(int)*16);
    int tabuleiro[4][4] = {0};

    /* int tabuleiro[4][4] = {{1,2,2,2},
                           {2,0,2,2},
                           {1,2,1,0},
                           {2,2,0,1}
                           }; */
    
    char current_player='A';
    int playing = 1;
    int xPosition, yPosition;

    printTabuleiro(4,4,tabuleiro);
    //changeTabuleiro(4,4,tabuleiro,1,3);
    //checkForWinner(4,4,tabuleiro);
    //GetInput(&xPosition,&yPosition,current_player);
    //printf("%d %d",xPosition,yPosition,current_player);
    /* while(playing){
        printTabuleiro(4,4,tabuleiro);

    } */

}
