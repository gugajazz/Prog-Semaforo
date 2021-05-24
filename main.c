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

void PrintHistorico(struct historico *head, int num_jogadas, int ylenght ,int xlenght){
    while(head!=NULL || num_jogadas>0){
        printf("\nCurrent player %c, ylenght=%d, xlenght=%d\n",head->current_player,head->ylenght,head->xlenght);
        printf("Table:\n");
        for(int i=0; i<ylenght; i++){
            for(int j=0; j<xlenght; j++){
                printf("%d ",head->tabuleiro[i][j]);
            }
            printf("\n");
        }
        //printf("%d -> ",head->data);
        head = head->next;
        num_jogadas--;
    }
    //printf("NULL");
} 

int changeTabuleiro(int **tabuleiro, int xPosition, int yPosition, int pedra, char current_player, int *nPedrasA, int *nPedrasB){
    if(pedra==1){
        if(tabuleiro[yPosition][xPosition]==4){
            printf("Ja exite uma pedra nessa posicao\n");
            return 1;
        }
        tabuleiro[yPosition][xPosition]=4;
        if(current_player=='A'){
            (*nPedrasA)++;
            printf("kkkkk");
        }
        else{
            (*nPedrasB)++;
        }
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

void ChangeCurrentPlayer(char *current_player){
    if(*current_player=='A'){
        *current_player='B';
    }
    else{
        *current_player='A';
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
    return 1;
}

int **ResizeTabuleiro(int *ylenght ,int *xlenght,int **tabuleiro, char mode, char current_player, int *nAumentosA, int *nAumentosB){

    if(mode=='C'){
        //more xlenght

        for(int i=0;i<(*ylenght);i++){
            tabuleiro[i] = realloc( tabuleiro[i], sizeof(int) * ((*xlenght)+1) );

            if(tabuleiro[0]==NULL){
                printf("ERRO NA ALOCACAO DE MEMORIA X%d\n",i);
                return NULL;
            }
        }

        for(int i=0;i<(*ylenght);i++){
            int j=(*xlenght);
            tabuleiro[i][j]=0;
        }

        (*xlenght)++;
        if(current_player='A'){
            (*nAumentosA)++;
        }
        else{
            (*nAumentosB)++;
        }
        return tabuleiro;
    }
    
    else if(mode=='L'){
        //more ylenght
        tabuleiro = realloc( tabuleiro, sizeof(int*) * ((*ylenght)+1) );
        if(tabuleiro==NULL){
                printf("ERRO NA ALOCACAO DE MEMORIA Y1\n");
                return NULL;
        }
        tabuleiro[*ylenght] = malloc( sizeof(int) * ((*xlenght)) );
        if(tabuleiro[(*ylenght)]==NULL){
            printf("ERRO NA ALOCACAO DE MEMORIA Y1\n");
            return NULL;
        }

        for(int i=0;i<(*xlenght);i++){
            int j=(*ylenght);
            tabuleiro[j][i]=0;
        } 

        (*ylenght)++;
        if(current_player='A'){
            (*nAumentosA)++;
        }
        else{
            (*nAumentosB)++;
        }
        return tabuleiro;
    }

    else{
        printf("MODO DESCONHECIDO");
        return NULL;
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

char Input1(char current_player, int nPedrasA, int nPedrasB, int nAumentosA, int nAumentosB){
    //devolve U ou P ou A ou J
    int loop_escolha;
    char escolha;

    printf("Vez do jogador %c\n",current_player);

    while(loop_escolha){
        printf("\nPretende ver as ultimas jogadas (U), colocar uma pedra (P), aumentar o tabuleiro (A) ou jogar(J)?:");
        fflush(stdin);
        scanf("%c",&escolha);
        if(escolha=='P' || escolha=='A' || escolha=='J' || escolha=='U'){
            //printf("****%c %c %d\n",escolha,current_player,nPedrasA);
            if(escolha=='P' && current_player=='A' && nPedrasA>=1){
                printf("Ja utilizou todas as pedras disponiveis\n");
            }
            else if(escolha=='P' && current_player=='B' && nPedrasB>=1){
                printf("Ja utilizou todas as pedras disponiveis\n");
            }
            else if(escolha=='A' && current_player=='A' && nAumentosA>=2){
                printf("Ja utilizou todos os aumentos disponiveis\n");
            }
            else if(escolha=='A' && current_player=='B' && nAumentosB>=2){
                printf("Ja utilizou todos os aumentos disponiveis\n");
            }
            else{
                loop_escolha=0;
            } 
        }
        else{
            printf("\nEscolha apenas entre U, P, A ou J");
        }
    }
    return escolha;
}

void Input2(int **tabuleiro, int ylenght, int xlenght, char current_player, int *nPedrasA, int *nPedrasB, int pedra){
    int loop_jogar,xPosition,yPosition;
    while(loop_jogar){
            printf("Escolha a posicao em que quer jogar (x y): ");
            fflush(stdin);
            scanf("%d %d",&xPosition,&yPosition);

            if(xPosition>=xlenght || yPosition>=ylenght || xPosition<0 || yPosition<0){
                printf("Posicao Invalida\n");
            }
            else{
                loop_jogar = changeTabuleiro(tabuleiro,xPosition,yPosition,pedra,current_player,nPedrasA,nPedrasB);
            }
        }
}

void Input3(struct historico* head, int *xlenght, int *ylenght, int numeroRondas){
    int k,loop_ultimas;
    while(loop_ultimas){
        printf("Indique o numero de jogadas anteriores que pretende visualisar:");

        fflush(stdin);
        scanf("%d",&k);
        if(k>=0 && k<=numeroRondas){
            PrintHistorico(head,k,*ylenght,*xlenght);
            loop_ultimas = 0;
        }
        else{
            printf("Valor incorreto\n");
        }
    }
}

char Input4(){
    char escolhaResize;
    while(1){
        printf("Pretende aumentar uma linha (L) ou coluna (C)?:");
        fflush(stdin);
        scanf("%c",&escolhaResize);
        if(escolhaResize=='C'){
            //tabuleiro = ResizeTabuleiro(ylenght,xlenght,tabuleiro,'X',current_player,&nAumentosA,&nAumentosB);
            //InicializaTabuleiro(*ylenght,*xlenght,tabuleiro);
            return escolhaResize;
        }
        else if(escolhaResize=='L'){
            //tabuleiro = ResizeTabuleiro(ylenght,xlenght,tabuleiro,'Y',current_player,&nAumentosA,&nAumentosB);
            //InicializaTabuleiro(*ylenght,*xlenght,tabuleiro);
            return escolhaResize;
        }
        else{
            printf("Escolha apenas entre L ou C\n");
        }
        
    }
}

int GetInput(int *xPosition, int *yPosition,char current_player, int **tabuleiro, int *xlenght, int *ylenght, struct historico* head, int nAumentosA, int nAumentosB, int *nPedrasA, int *nPedrasB){

    char escolha, escolhaResize;
    int loop_escolha=1, loop_resize=1, loop_jogar=1, loop_changeTabuleiro=1, loop_ultimas=1;
    printf("Vez do jogador %c\n",current_player);
    while(loop_escolha){
        printf("\nPretende ver as ultimas jogadas (U), colocar uma pedra (P), aumentar o tabuleiro (A) ou jogar(J)?:");
        fflush(stdin);
        scanf("%c",&escolha);
        if(escolha=='P' || escolha=='A' || escolha=='J' || escolha=='U'){
            loop_escolha=0;
        }
        else{
            printf("\nEscolha apenas entre U, P, A ou J");
        }
    }

    if(escolha=='P'){
        loop_changeTabuleiro=1;
        //printf("pedrasA=%d pedrasB=%d\n",*nPedrasA,*nPedrasB);
        if(current_player=='A' && *nPedrasA>=1){
            printf("Numero maximo de pedras excedido\n");
            return 1;
        }

        if(current_player=='B' && *nPedrasB>=1){
            printf("Numero maximo de pedras excedido\n");
            return 1;
        }

        while(loop_changeTabuleiro){
            printf("Escolha a posicao da pedra (x y): ");
            fflush(stdin);
            scanf("%d %d",xPosition,yPosition);

            if(*xPosition>=*xlenght || *yPosition>=*ylenght || *xPosition<0 || *yPosition<0){
                printf("Posicao Invalida\n");
                return 1;
            }
            loop_changeTabuleiro = changeTabuleiro(tabuleiro,*xPosition,*yPosition,1,current_player,nPedrasA,nPedrasB);
        }
        return 0;
    }

    else if(escolha=='A'){
        //while(tabuleiro){
            printf("Pretende aumentar uma linha (L) ou coluna (C)?:");
            fflush(stdin);
            scanf("%c",&escolhaResize);
            if(escolhaResize=='C'){
                tabuleiro = ResizeTabuleiro(ylenght,xlenght,tabuleiro,'X',current_player,&nAumentosA,&nAumentosB);
                InicializaTabuleiro(*ylenght,*xlenght,tabuleiro);
                return 0;
            }
            else if(escolhaResize=='L'){
                tabuleiro = ResizeTabuleiro(ylenght,xlenght,tabuleiro,'Y',current_player,&nAumentosA,&nAumentosB);
                InicializaTabuleiro(*ylenght,*xlenght,tabuleiro);
                return 0;
            }
            else{
                printf("Escolha apenas entre L ou C\n");
            }
            
        //}
    }

    else if(escolha=='U'){
        int k;
        while(loop_ultimas){
            printf("Indique o numero de jogadas anteriores que pretende visualisar:");
            fflush(stdin);
            scanf("%d",&k);
            if(k>0){
                PrintHistorico(head,k,*ylenght,*xlenght);
                loop_ultimas = 0;
            }
        }
    }

    else{
        while(loop_jogar){
            printf("Escolha a posicao em que quer jogar (x y): ");
            fflush(stdin);
            scanf("%d %d",xPosition,yPosition);

            if(*xPosition>=*xlenght || *yPosition>=*ylenght || *xPosition<0 || *yPosition<0){
                printf("Posicao Invalida\n");
            }
            else{
                loop_jogar = changeTabuleiro(tabuleiro,*xPosition,*yPosition,0,current_player,nPedrasA,nPedrasB);
            }
        }
        return 0;
    } 
}

void CriaTabuleiro(int ylenght ,int xlenght,int **tabuleiro){
    //TO BE CONTINUED
}

void AdicionaAoHistorico(struct historico** head, char current_player, int ylenght ,int xlenght, 
int **tabela_atual){

	struct historico *new_historico = (struct historico*) malloc(sizeof(struct historico));

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

void exportFile(struct historico *head, char NomeFicheiro[50], int ylenght ,int xlenght){

    int m=0;
    do{
        m++;
    }while(NomeFicheiro[m]!='\0');
    NomeFicheiro[m]='.';
    NomeFicheiro[m+1]='t';
    NomeFicheiro[m+2]='x';
    NomeFicheiro[m+3]='t';
    NomeFicheiro[m+4]='\0';
    //printf("%s",NomeFicheiro);

    FILE *fp;
    fp = fopen (NomeFicheiro,"w");

    fprintf (fp, "Tisss b line\n");

    while(head!=NULL){
        fprintf(fp, "Current player %c, ylenght=%d, xlenght=%d\n",head->current_player,head->ylenght,head->xlenght);
        fprintf(fp, "Table:\n");
        for(int i=0; i<ylenght; i++){
            for(int j=0; j<xlenght; j++){
                fprintf(fp,"%d ",head->tabuleiro[i][j]);
            }
            fprintf(fp,"\n");
        }
        fprintf(fp,"\n");
        //printf("%d -> ",head->data);
        head = head->next;
    }
    
    fclose (fp);

}

void SaveState(struct historico *head){
    FILE *fp;
    fp = fopen ("jogo.bin","wb");
    while(head!=NULL){
        fwrite(head,sizeof(struct historico),1,fp);
        /* printf("%d %d %d\n",head->tabuleiro[0][0],head->tabuleiro[0][1],head->tabuleiro[0][2]);
        printf("%d %d %d\n",head->tabuleiro[1][0],head->tabuleiro[1][1],head->tabuleiro[1][2]);
        printf("%d %d %d\n\n",head->tabuleiro[2][0],head->tabuleiro[2][1],head->tabuleiro[2][2]); */
        head = head->next;
    }
    fclose(fp); 
}

void ReadState(int ylenght,int xlenght){
    struct historico *FromFile = (struct historico*) malloc(sizeof(struct historico));
    FILE *fp = fopen("jogo.bin", "rb");

    fread(FromFile, sizeof(struct historico), 1, fp);
    while(FromFile!=NULL){
        
        printf("x = %d\ny = %d\nplayer:%c\n", FromFile->xlenght, FromFile->ylenght,FromFile->current_player);
        
        for(int i=0;i<FromFile->ylenght;i++){
            for(int j=0;j<FromFile->xlenght;j++){
                printf("%d ",FromFile->tabuleiro[i][j]);
            }   
            printf("\n");
        }
        printf("\n");
        FromFile = FromFile->next;
    }

    fclose(fp);
}

void randomPlayer(int ylenght ,int xlenght,int **tabuleiro, char current_player,int nAumentosA, int nAumentosB, int nPedrasA, int nPedrasB){
    initRandom();
    int output_change = 1, xpos, ypos, pedra, aumentar, coluna;

    
    pedra = intUniformRnd(0, 100); 
    aumentar = intUniformRnd(0, 100);


    if(pedra<=30){ //30% de prob de jogar uma pedra
        pedra=1;
    }
    else{
        pedra=0;
    }

    if(pedra==0 && aumentar<=30){
        coluna = intUniformRnd(0, 1);
        if(coluna==1){
            ResizeTabuleiro(&ylenght,&xlenght,tabuleiro,'X',current_player,&nAumentosA,&nAumentosB);
            printf("\nO computador aumentou uma linha no tabuleiro\n");
            return;
        }
        else{
            ResizeTabuleiro(&ylenght,&xlenght,tabuleiro,'Y',current_player,&nAumentosA,&nAumentosB);
            printf("\nO computador aumentou uma coluna no tabuleiro\n");
            return;
        }
    }

    do{
        xpos = intUniformRnd(0, xlenght-1);
        ypos = intUniformRnd(0, ylenght-1);
        //printf("y:%d x:%d",ypos,xpos);
        output_change = changeTabuleiro(tabuleiro, xpos, ypos,pedra,current_player,&nPedrasA,&nPedrasB); //devolve 1 se for invalida
    }while(output_change);

    if(pedra==1){
        printf("\nO computador jogou uma pedra na posicao x%d y%d\n\n",xpos,ypos);
    }
    else{
        printf("\nO computador jogou na posicao x%d y%d\n\n",xpos,ypos);
    }
    
}

int main(){
    initRandom();
    int tamanhoInicial = intUniformRnd(3, 5), numeroRondas=0;
    int ylenght=tamanhoInicial, xlenght=tamanhoInicial, posicao_valida, ModoJogo;
    int **tabuleiro;
    char current_player='A', modo, modoResize;
    int playing = 1;
    int xPosition, yPosition;
    struct historico *head = NULL;
    char NomeFicheiro[50];
    int nPedrasA=0,nPedrasB=0,nAumentosA=0,nAumentosB=0;

    tabuleiro = (int**)malloc(sizeof(int*)*ylenght);
    if (tabuleiro!=NULL){
        for (int i = 0; i<ylenght; i++){
            tabuleiro[i] = (int*)malloc(sizeof(int)*xlenght);
        }
    }
    else{
        printf("Erro na alocacao de memoria\n");
    }
    
    /*InicializaTabuleiro(ylenght,xlenght,tabuleiro);
    changeTabuleiro(tabuleiro,0,0,0);
    AdicionaAoHistorico(&head,'A',3,3,tabuleiro);
    changeTabuleiro(tabuleiro,0,1,0);
    AdicionaAoHistorico(&head,'B',3,3,tabuleiro);
    changeTabuleiro(tabuleiro,0,2,0);
    AdicionaAoHistorico(&head,'A',3,3,tabuleiro); */

    do{
        printf("Escolha entre 1 ou 2 jogadores '1' ou '2': ");
        fflush(stdin);
        scanf("%d",&ModoJogo);
    }while(ModoJogo!=1 && ModoJogo!=2);
    InicializaTabuleiro(ylenght,xlenght,tabuleiro);
    
    while(playing){         
        posicao_valida=1;
        printTabuleiro(ylenght,xlenght,tabuleiro);
        
        modo = Input1(current_player,nPedrasA,nPedrasB,nAumentosA,nAumentosB); // U, P, A ou J
        while(modo=='U'){
            printf("\n"); //se remover n corre o input
            Input3(head,&xlenght,&ylenght,numeroRondas);
            modo = Input1(current_player,nPedrasA,nPedrasB,nAumentosA,nAumentosB); // U, P, A ou J
        }

        if(modo=='J'){
            printf("\n"); //se remover n corre o input
            Input2(tabuleiro,ylenght,xlenght,current_player,&nPedrasA,&nPedrasB,0);
        }
        else if(modo=='P'){
            printf("\n"); //se remover n corre o input
            Input2(tabuleiro,ylenght,xlenght,current_player,&nPedrasA,&nPedrasB,1);
        }
        else if(modo=='A'){
            printf("\n"); //se remover n corre o input
            modoResize = Input4();
            //printf("---%c---\n",modoResize);
            tabuleiro = ResizeTabuleiro(&ylenght,&xlenght,tabuleiro,modoResize,current_player,&nAumentosA,&nAumentosB);
            //InicializaTabuleiro(ylenght,xlenght,tabuleiro);
        }

           
        AdicionaAoHistorico(&head,current_player,ylenght,xlenght,tabuleiro);
        playing = checkForWinner(xlenght,ylenght,tabuleiro,&current_player);

        if(ModoJogo==2){
            ChangeCurrentPlayer(&current_player);
        }
        else if(ModoJogo==1){
            randomPlayer(ylenght, xlenght, tabuleiro,current_player,nAumentosA,nAumentosB,nPedrasA,nPedrasB);
        }

        if(playing==0){
            printf("\nIndique o nome do ficheiro por favor: ");
            fflush(stdin);
            scanf("%20s",NomeFicheiro);
            exportFile(head, NomeFicheiro, ylenght, xlenght);
        }
        numeroRondas++;
    }


    /* InicializaTabuleiro(ylenght,xlenght,tabuleiro);

    printTabuleiro(ylenght,xlenght,tabuleiro);
    tabuleiro = ResizeTabuleiro(&ylenght,&xlenght,tabuleiro,'L',current_player,&nAumentosA,&nAumentosB);
    tabuleiro = ResizeTabuleiro(&ylenght,&xlenght,tabuleiro,'L',current_player,&nAumentosA,&nAumentosB);
    tabuleiro = ResizeTabuleiro(&ylenght,&xlenght,tabuleiro,'L',current_player,&nAumentosA,&nAumentosB);
    tabuleiro = ResizeTabuleiro(&ylenght,&xlenght,tabuleiro,'L',current_player,&nAumentosA,&nAumentosB);
    
    printf("%d %d",ylenght,xlenght);
    InicializaTabuleiro(ylenght,xlenght,tabuleiro);
    printTabuleiro(ylenght,xlenght,tabuleiro); */
}
