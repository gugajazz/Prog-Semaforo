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

int changeTabuleiro(int **tabuleiro, int xPosition, int yPosition){
    if(tabuleiro[xPosition][yPosition]==0){
        tabuleiro[xPosition][yPosition]=1;
        return 1;
    }
    else if(tabuleiro[xPosition][yPosition]==1){
        tabuleiro[xPosition][yPosition]=2;
        return 1;
    }
    else if(tabuleiro[xPosition][yPosition]==2){
        tabuleiro[xPosition][yPosition]=3;
        return 1;
    }
    else{
        printf("Posicao Invalida\n");
        return 0;
    }
}

int checkForWinner(int xlenght ,int ylenght,int **tabuleiro, char *current_player){
    int equal_straight=0, last_equal;
    //horizontal
    for(int y=0;y<ylenght;y++){
        if(tabuleiro[y][0]!=0){
            last_equal=tabuleiro[y][0];

            for(int x=1;x<xlenght;x++){
                if(tabuleiro[y][x]==last_equal){
                    equal_straight++;
                }
                //printf("x=%d y=%d val=%d las=%d strai=%d\n",x,y,tab[y][x],last_equal,equal_straight);
            }
            //printf("\n");

            if(equal_straight==3){
                printTabuleiro(xlenght,ylenght,tabuleiro);
                printf("PLAYER %c IS THE WINNER\n",*current_player);
                return 0;
            }
            else{
                equal_straight=0;
            }
        }        
    }

    equal_straight=0;
    //vertical
    for(int x=0;x<xlenght;x++){
        if(tabuleiro[0][x]!=0){
            last_equal=tabuleiro[0][x];
            for(int y=1;y<ylenght;y++){
                if(tabuleiro[y][x]==last_equal){
                    equal_straight++;
                }
                //printf("x=%d y=%d val=%d las=%d strai=%d\n",x,y,tab[y][x],last_equal,equal_straight);
            }
            printf("\n");
        
            if(equal_straight==3){
                printTabuleiro(xlenght,ylenght,tabuleiro);
                printf("PLAYER %c IS THE WINNER\n",*current_player);
                return 0;
            }
            else{
                equal_straight=0;
            }
        }        
    }

    //diagonal esquerda p direita
    if(tabuleiro[0][0]!=0){
        equal_straight=0;
        last_equal=tabuleiro[0][0];
        if(xlenght==ylenght){
            for(int i=1;i<xlenght;i++){
                if(tabuleiro[i][i]==last_equal){
                    equal_straight++;
                }
            }
            if(equal_straight==xlenght-1){
                printTabuleiro(xlenght,ylenght,tabuleiro);
                printf("PLAYER %c IS THE WINNER\n",*current_player);
                return 0;
            }
        }
    }

    //diagonal direita p esquerda
    if(tabuleiro[0][xlenght-1]!=0){
        equal_straight=0;
        last_equal=tabuleiro[0][xlenght-1];
        if(xlenght==ylenght){
            for(int x=xlenght-2, y=1 ;x>=0; x--,y++){
                if(tabuleiro[y][x]==last_equal){
                    equal_straight++;
                }
            }
            if(equal_straight==xlenght-1){
                printTabuleiro(xlenght,ylenght,tabuleiro);
                printf("PLAYER %c IS THE WINNER\n",*current_player);
            }
        }
    }

    if(*current_player=='A'){
        *current_player='B';
    }
    else{
        *current_player='A';
    }
    return 1;
}

int GetInput(int *xPosition, int *yPosition,char current_player, int **tabuleiro, int xlenght, int ylenght){
    printf("Vez do jogador %c\n",current_player);
    printf("Escolha a posicao em que quer jogar (y x): ");
    scanf("%d %d",xPosition,yPosition);

    if(*xPosition>=xlenght || *yPosition>=ylenght || *xPosition<0 || *yPosition<0){ /*|| *xPosition<0 || *yPosition<0*/
        printf("Posicao Invalida\n");
        return 0;
    }

    changeTabuleiro(tabuleiro,*xPosition,*yPosition);
    return 1;
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

void CriaTabuleiro(int ylenght ,int xlenght,int **tabuleiro){
    //TO BE CONTINUED
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
            } 
        }
        for(int i=0;i<(*ylenght);i++){
            int j=(*xlenght);
            tabuleiro[i][j]=0;
        }
        (*xlenght)++; 
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
        }
        for(int j=0;j<(*xlenght);j++){
            int i=(*ylenght);
            tabuleiro[i][j]=0;
        }
        (*ylenght)++;
    }

    else{
        printf("MODO DESCONHECIDO");
    }
}

int main(){
    //system("cls");
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

    InicializaTabuleiro(ylenght,xlenght,tabuleiro);
    while(playing){
        printTabuleiro(xlenght,ylenght,tabuleiro);
        GetInput(&xPosition,&yPosition,current_player,tabuleiro, xlenght, ylenght);
        playing = checkForWinner(xlenght,ylenght,tabuleiro,&current_player);
    }
}
