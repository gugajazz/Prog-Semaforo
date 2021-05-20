//Gustavo Mateus 2020138902
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

struct historico{
    int xlenght;
    int ylenght;
    char current_player;
    int **tabuleiro;

    struct historico *next;
};

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
        if(tabuleiro[xPosition][yPosition]==4){
            printf("Ja exite uma pedra nessa posicao\n");
            return 1;
        }
        tabuleiro[xPosition][yPosition]=4;
        return 0;
    }
    if(tabuleiro[xPosition][yPosition]==0){
        tabuleiro[xPosition][yPosition]=1;
        return 0;
    }
    else if(tabuleiro[xPosition][yPosition]==1){
        tabuleiro[xPosition][yPosition]=2;
        return 0;
    }
    else if(tabuleiro[xPosition][yPosition]==2){
        tabuleiro[xPosition][yPosition]=3;
        return 0;
    }
    else{
        printf("Posicao Invalida\n");
        return 1;
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
            }

            if(equal_straight==3){
                printTabuleiro(ylenght,xlenght,tabuleiro);
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
            }
            printf("\n");
        
            if(equal_straight==3){
                printTabuleiro(ylenght,xlenght,tabuleiro);
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
                printTabuleiro(ylenght,xlenght,tabuleiro);
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
                printTabuleiro(ylenght,xlenght,tabuleiro);
                printf("PLAYER %c IS THE WINNER\n",*current_player);
                return 0;
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

int ResizeTabuleiro(int *ylenght ,int *xlenght,int **tabuleiro, char mode){
    if(mode=='X'){
        //more xlenght
            tabuleiro = realloc( tabuleiro, sizeof(int) * ((*xlenght)+1) );
            if(tabuleiro==NULL){
                printf("ERRO NA ALOCACAO DE MEMORIA X1\n");
                return 1;
            }
            tabuleiro[*xlenght] = malloc(sizeof(int)*(*ylenght));
            if(tabuleiro[*xlenght]==NULL){
                printf("ERRO NA ALOCACAO DE MEMORIA X2\n");
                return 1;
            }
        (*xlenght)++; 
        return 0;
    }
    
    else if(mode=='Y'){
        //more ylenght
        tabuleiro[(*ylenght)] = malloc( sizeof(int) * ((*xlenght)) );
        (*ylenght)++;
        return 0;
    }

    else{
        printf("MODO DESCONHECIDO");
        return 1;
    }
}

void InicializaTabuleiro(int ylenght ,int xlenght,int **tab){
    for(int i=0;i<ylenght;i++){
        for(int j=0;j<xlenght;j++){
            //printf("%d y=%d x=%d\n",tab[i][j],i,j);
            if(tab[i][j]!=0 && tab[i][j]!=1 && tab[i][j]!=2 && tab[i][j]!=3 && tab[i][j]!=4){
                tab[i][j]=0;
            }
        }
        //printf("\n");
    }
}

int GetInput(int *xPosition, int *yPosition,char current_player, int **tabuleiro, int *xlenght, int *ylenght){
    char escolha, escolhaResize;
    int loop_escolha=1, loop_resize=1, loop_jogar=1, loop_changeTabuleiro=1;
    printf("Vez do jogador %c\n",current_player);
    while(loop_escolha){
        printf("\nPretende colocar uma pedra (P), aumentar o tabuleiro (A) ou jogar(J)?:");
        fflush(stdin);
        scanf("%c",&escolha);
        if(escolha=='P' || escolha=='A' || escolha=='J'){
            loop_escolha=0;
        }
        else{
            printf("\nEscolha apenas entre P, A ou J");
        }
    }

    if(escolha=='P'){
        loop_changeTabuleiro=1;
        while(loop_changeTabuleiro){
            printf("Escolha a posicao da pedra (y x): ");
            fflush(stdin);
            scanf("%d %d",xPosition,yPosition);

            if(*xPosition>=*xlenght || *yPosition>=*ylenght || *xPosition<0 || *yPosition<0){
                printf("Posicao Invalida\n");
                return 1;
            }
            loop_changeTabuleiro = changeTabuleiro(tabuleiro,*xPosition,*yPosition,1);
        }
        return 0;
    }

    else if(escolha=='A'){
        while(loop_resize){
            printf("Pretende aumentar uma linha (L) ou coluna (C)?:");
            fflush(stdin);
            scanf("%c",&escolhaResize);
            if(escolhaResize=='C'){
                loop_resize = ResizeTabuleiro(ylenght,xlenght,tabuleiro,'X');
                InicializaTabuleiro(*ylenght,*xlenght,tabuleiro);
                return 0;
            }
            else if(escolhaResize=='L'){
                loop_resize = ResizeTabuleiro(ylenght,xlenght,tabuleiro,'Y');
                InicializaTabuleiro(*ylenght,*xlenght,tabuleiro);
                return 0;
            }
            else{
                printf("Escolha apenas entre L ou C\n");
            }
            
        }
    }

    else{
        while(loop_jogar){
            printf("Escolha a posicao em que quer jogar (y x): ");
            fflush(stdin);
            scanf("%d %d",xPosition,yPosition);

            if(*xPosition>=*xlenght || *yPosition>=*ylenght || *xPosition<0 || *yPosition<0){
                printf("Posicao Invalida\n");
            }
            else{
                loop_jogar = changeTabuleiro(tabuleiro,*xPosition,*yPosition,0);
            }
        }
        return 0;
    } 
}

void CriaTabuleiro(int ylenght ,int xlenght,int **tabuleiro){
    //TO BE CONTINUED
}

void AdicionaAoHistorico(struct historico** head, char current_player, int ylenght ,int xlenght, int **tabela_atual){
	struct historico* new_historico = (struct historico*) malloc(sizeof(struct historico));

	struct historico *last = *head;

    /*****************************************************************/

    new_historico->tabuleiro = (int**)malloc(sizeof(int*)*xlenght);
    if (new_historico->tabuleiro!=NULL){
        for (int i = 0; i<ylenght; i++){
            new_historico->tabuleiro[i] = (int*)malloc(sizeof(int)*ylenght);
        }
    }
    else{
        printf("Erro na alocacao de memoria\n");
    }

    for(int i=0; i<ylenght; i++){
        for(int j=0; j<xlenght; j++){
            new_historico->tabuleiro[i][j] = tabela_atual[i][j];
        }
    }

    new_historico->xlenght=xlenght;
    new_historico->ylenght=ylenght;
    new_historico->current_player=current_player;



    /*****************************************************************/

	new_historico->next = NULL;

	if (*head == NULL){
        *head = new_historico;
        return;
	}
    else{
        while (last->next != NULL) //enquanto o last n for o ultimo 
            last = last->next;

        
        last->next = new_historico; /*aponta o penultimo p o q criamos agr*/
        return;
    }
}

void PrintHistorico(struct historico *head){
    while(head!=NULL){
        printf("\nCurrent player %c, ylenght=%d, xlenght=%d\n",head->current_player,head->ylenght,head->xlenght);
        printf("Table:\n");
        for(int i=0; i<3; i++){
            for(int j=0; j<3; j++){
                printf("%d ",head->tabuleiro[i][j]);
            }
            printf("\n");
        }
        //printf("%d -> ",head->data);
        head = head->next;
    }
    //printf("NULL");
} 

int main(){
    //system("cls");
    initRandom();
    int tamanhoInicial = intUniformRnd(3, 5);
    int ylenght=tamanhoInicial, xlenght=tamanhoInicial, posicao_valida;
    int **tabuleiro;
    char current_player='A';
    int playing = 1;
    int xPosition, yPosition;

    tabuleiro = (int**)malloc(sizeof(int*)*xlenght);
    if (tabuleiro!=NULL){
        for (int i = 0; i<ylenght; i++){
            tabuleiro[i] = (int*)malloc(sizeof(int)*ylenght);
        }
    }
    else{
        printf("Erro na alocacao de memoria\n");
    }

    /* InicializaTabuleiro(ylenght,xlenght,tabuleiro);
    while(playing){
        posicao_valida=1;
        printTabuleiro(ylenght,xlenght,tabuleiro);
        while(posicao_valida){
            posicao_valida = GetInput(&xPosition,&yPosition,current_player,tabuleiro, &xlenght, &ylenght);
        }
        checkForWinner(xlenght,ylenght,tabuleiro,&current_player);
    } */

    InicializaTabuleiro(ylenght,xlenght,tabuleiro);

    struct historico *head = NULL;
    AdicionaAoHistorico(&head,current_player,ylenght,xlenght,tabuleiro);
    AdicionaAoHistorico(&head,'B',ylenght,xlenght,tabuleiro);
    PrintHistorico(head);
}
