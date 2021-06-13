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

struct dados_jogo{
    int ylenght;
    int xlenght; 
    int nPedrasB;
    int nPedrasA;
    int nAumentosB;
    int nAumentosA;
    int current_player;
};

struct dados_jogo jg;

void clear_buffer(){
    int i;
    do{
        i = getchar();
    }while ( i != '\n' && i != EOF );
    return;
}

void printTabuleiro(int **tab, int ylenght, int xlenght){ //tem q ter ylenght e xlenght pq é usada par printhistorico e ele usa head->ylenght

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
            switch(tab[y][x]){
            case 0:
                printf("   | ");
                break;
            case 1:
                printf(" G | ");
                break;
            case 2:
                printf(" Y | ");
                break;
            case 3:
                printf(" R | ");
                break;
            case 4:
                printf(" S | ");
                break;
            
            default:
                break;
            }
            //printf(" %d | ",tab[y][x]);
        }

        printf("\n     ");
        for(int i=0;i<xlenght*5;i++){
            printf("-");
        }
        printf("\n");
    }
    printf("\n");
}

void PrintHistorico(struct historico *head, int num_jogadas){
    int contador_jogadas=1;
    printf("\n+-+-+-+-+-+-+-HISTORICO-+-+-+-+-+-+-+-+\n\n");
    while(head!=NULL && num_jogadas>0){ //tirar o comentario para so mostrar o num de jogadas pedidas
        printf("Jogada numero %d feita por %c\n",contador_jogadas,head->current_player);
        printTabuleiro(head->tabuleiro,head->ylenght,head->xlenght);
        contador_jogadas++;
        head = head->next;
        num_jogadas--; //para só mostrar o numero de jogadas pedido
    }
    printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+\n");
} 

int changeTabuleiro(int **tabuleiro, int xPosition, int yPosition, int pedra){
    if(pedra==1){
        if(tabuleiro[yPosition][xPosition]==4){ //verifica que não há uma pedra onde estamos a tentar por uma pedra
            printf("Ja exite uma pedra nessa posicao\n");
            return 1;
        }
        if(tabuleiro[yPosition][xPosition]!=0){ //verifica que não há uma peca onde estamos a tentar por uma pedra
            printf("Ja exite uma peca nessa posicao\n");
            return 1;
        }
        tabuleiro[yPosition][xPosition]=4;
        if(jg.current_player=='A'){
            (jg.nPedrasA)++;
        }
        else{
            (jg.nPedrasB)++;
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

void ChangeCurrentPlayer(){
    if(jg.current_player=='A'){
        jg.current_player='B';
    }
    else if(jg.current_player=='B'){
        jg.current_player='A';
    }
    else{
        printf("Erro, jogador nao e nem A nem B\n");
    }
}

int checkForWinner(int **tabuleiro){
    int equal_straight=0, last_equal;
    //horizontal
    for(int y=0;y<jg.ylenght;y++){
        if(tabuleiro[y][0]!=0){
            last_equal=tabuleiro[y][0];

            for(int x=1;x<jg.xlenght;x++){
                if(tabuleiro[y][x]==last_equal){
                    equal_straight++;
                }
            }

            if(equal_straight==jg.xlenght-1){
                printTabuleiro(tabuleiro,jg.ylenght,jg.xlenght);
                printf("PLAYER %c IS THE WINNER\n",jg.current_player);
                return 0;
            }
            else{
                equal_straight=0;
            }
        }        
    }

    equal_straight=0;
    //vertical
    for(int x=0;x<jg.xlenght;x++){
        if(tabuleiro[0][x]!=0){
            last_equal=tabuleiro[0][x];
            for(int y=1;y<jg.ylenght;y++){
                if(tabuleiro[y][x]==last_equal){
                    equal_straight++;
                }
            }
            printf("\n");
        
            if(equal_straight==jg.ylenght-1){
                printTabuleiro(tabuleiro,jg.ylenght,jg.xlenght);
                printf("PLAYER %c IS THE WINNER\n",jg.current_player);
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
        if(jg.xlenght==jg.ylenght){
            for(int i=1;i<jg.xlenght;i++){
                if(tabuleiro[i][i]==last_equal){
                    equal_straight++;
                }
            }
            if(equal_straight==jg.xlenght-1){
                printTabuleiro(tabuleiro,jg.ylenght,jg.xlenght);
                printf("PLAYER %c IS THE WINNER\n",jg.current_player);
                return 0;
            }
        }
    }

    //diagonal direita p esquerda
    if(tabuleiro[0][jg.xlenght-1]!=0){
        equal_straight=0;
        last_equal=tabuleiro[0][jg.xlenght-1];
        if(jg.xlenght==jg.ylenght){
            for(int x=jg.xlenght-2, y=1 ;x>=0; x--,y++){
                if(tabuleiro[y][x]==last_equal){
                    equal_straight++;
                }
            }
            if(equal_straight==jg.xlenght-1){
                printTabuleiro(tabuleiro,jg.ylenght,jg.xlenght);
                printf("PLAYER %c IS THE WINNER\n",jg.current_player);
                return 0;
            }
        }
    }
    return 1;
}

int **ResizeTabuleiro(int *ylenght ,int *xlenght,int **tabuleiro, char mode, int *nAumentosA, int *nAumentosB){

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
        //printf("\ncurrent player: %c\n",current_player);
        if(jg.current_player=='A'){
            (*nAumentosA)++;
            //printf("GGGGG");
        }
        else if(jg.current_player=='B'){
            (*nAumentosB)++;
            //printf("FFFFFF");
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
            printf("ERRO NA ALOCACAO DE MEMORIA Y2\n");
            return NULL;
        }

        for(int i=0;i<(*xlenght);i++){
            int j=(*ylenght);
            tabuleiro[j][i]=0;
        } 

        (*ylenght)++;
        if(jg.current_player=='A'){
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

void InicializaTabuleiro(int **tab){
    for(int i=0;i<jg.ylenght;i++){
        for(int j=0;j<jg.xlenght;j++){
            //printf("%d y=%d x=%d\n",tab[i][j],i,j);
            if(tab[i][j]!=0 && tab[i][j]!=1 && tab[i][j]!=2 && tab[i][j]!=3 && tab[i][j]!=4){
                tab[i][j]=0;
            }
        }
        //printf("\n");
    }
}

char Input1(){
    //printf("INPUT1\n");
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
            //printf("****%c %c %d\n",escolha,current_player,nPedrasA);
            if(escolha=='P' || escolha=='p' && jg.current_player=='A' && jg.nPedrasA>=1){
                printf("\nJa utilizou todas as pedras disponiveis\n");
            }
            else if(escolha=='P' || escolha=='p' && jg.current_player=='B' && jg.nPedrasB>=1){
                printf("\nJa utilizou todas as pedras disponiveis\n");
            }
            else if(escolha=='A' || escolha=='a' && jg.current_player=='A' && jg.nAumentosA>=2){
                printf("\nJa utilizou todos os aumentos disponiveis\n");
            }
            else if(escolha=='A' || escolha=='a' && jg.current_player=='B' && jg.nAumentosB>=2){
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

void AdicionaAoHistorico(struct historico** head, int **tabela_atual){

	struct historico *new_historico = (struct historico*) malloc(sizeof(struct historico));
    /* if(new_historico==NULL){
        printf("Erro na alocacao de memoria historico 1\n");
    } */
	struct historico *last = *head;
    /*****************************************************************/
    //IGUAL A CRIAR UM TABULEIRO PELA PRIMEIRA VEZ NO MAIN
    new_historico->tabuleiro = (int**)malloc(sizeof(int*)*jg.ylenght);
    if (new_historico->tabuleiro!=NULL){
        for (int i = 0; i<jg.ylenght; i++){
            new_historico->tabuleiro[i] = (int*)malloc(sizeof(int)*jg.xlenght);
        }
    }
    else{
        printf("Erro na alocacao de memoria historico\n");
    }

    for(int i=0; i<jg.ylenght; i++){
        for(int j=0; j<jg.xlenght; j++){
            new_historico->tabuleiro[i][j] = tabela_atual[i][j];
        }
    }

    new_historico->xlenght=jg.xlenght;
    new_historico->ylenght=jg.ylenght;
    new_historico->current_player=jg.current_player;
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

    //printf("%c",head->current_player);
    fprintf(fp,"!!! O JOGADOR '%c' VENCEU !!!\n\n",winner);
    fprintf(fp,"+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+\n");
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

void ReadState(){
    struct historico *FromFile = (struct historico*) malloc(sizeof(struct historico));
    FILE *fp = fopen("jogo.bin", "rb");

    if(fp==NULL){
        printf("Fopen deu NULL\n");
    }

    int i=0;
    while(FromFile!=NULL){ 
        //struct historico *FromFile = (struct historico*) malloc(sizeof(struct historico));
        FromFile=FromFile->next;
    }
    
    fclose(fp);

    printf("dass");
    //PrintHistorico(FromFile,9);
}

/* void dog(){
    FILE *fp;
    struct historico *new_node,*curr,*lista, aux;
    fp=fopen("jogo.bin","rb");
    new_node=malloc(sizeof(struct historico));
    fread(new_node,1,sizeof(struct historico),fp); //new_node e a cabeca da lista
    new_node->next=NULL; 
    lista=curr=new_node;
    while(fread(&aux,sizeof(struct historico),1,fp)==1){ //enquanto conseguires ler para aux
        new_node=malloc(sizeof(struct historico)); //alocas um novo
        /* new_node->tabuleiro = mall 
        *new_node=aux; //ele fica igual a aux
        new_node->next=NULL; //pode ser o utilmo
        curr->next=new_node; //o no anterior fica a apontar para o atual
        curr=curr->next; //curr fica a apontar para o no k foi agr alocado 

    }
    
    printf("--->%d",lista->xlenght);
    lista=lista->next;
    printf("\n--->%d",lista->xlenght);

} */

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
}

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


    /* printf("\n\n");
        for(int i=0;i<my_ylenght;i++){
            for(int j=0;j<my_xlenght;j++){
                printf("%d ",(recuperado+2)->tabuleiro[i][j]);
            }
            printf("\n");
    } */

    /* FromFile->current_player = temp[0];
    FromFile->ylenght = temp[1] - '0'; // char - '0' resulta no int correspondente
    FromFile->xlenght = temp[2] - '0'; */

    //printf("\n\n%c %d %d",FromFile->current_player,FromFile->ylenght,FromFile->xlenght);
    //printf("tamanho 1 jogada=%d",3+ylenght*xlenght);
    //printf("\ntamanho 1 jogada=%d",3+(5*5));
}

char randomPlayer(int **tabuleiro){
    initRandom();
    int output_change = 1, xpos, ypos, pedra, aumentar, coluna;

    
    pedra = intUniformRnd(0, 100); 
    aumentar = intUniformRnd(0, 100);


    if(pedra<=30 && jg.nPedrasB<1){ //30% de prob de jogar uma pedra
        pedra=1;
    }
    else{
        pedra=0;
    }

    if(pedra==0 && aumentar<=30 && jg.nAumentosB<2){
        coluna = intUniformRnd(0, 1);
        if(coluna==1){
            printf("\nO computador aumentou uma linha no tabuleiro\n");
            return 'L';
        }
        else{
            printf("\nO computador aumentou uma coluna no tabuleiro\n");
            return 'C';
        }
        jg.nAumentosB++;
    }

    do{
        xpos = intUniformRnd(0, jg.xlenght-1);
        ypos = intUniformRnd(0, jg.ylenght-1);
        output_change = changeTabuleiro(tabuleiro, xpos, ypos,pedra); //devolve 1 se for invalida
    }while(output_change);

    if(pedra==1){
        printf("\nO computador jogou uma pedra na posicao x%d y%d\n\n",xpos,ypos);
    }
    else{
        printf("\nO computador jogou na posicao x%d y%d\n\n",xpos,ypos);
    }
    return 'X';
}

int main(){
    initRandom();
    int tamanhoInicial = intUniformRnd(3, 5);
    int numeroRondas=0;

    //tamanhoInicial = 4;

    jg.ylenght=tamanhoInicial, jg.xlenght=tamanhoInicial;
    jg.nPedrasA=0,jg.nPedrasB=0,jg.nAumentosA=0,jg.nAumentosB=0;
    jg.current_player='A';

    int posicao_valida, ModoJogo;
    int **tabuleiro;
    
    char modo, modoResize;
    int playing = 1;
    int xPosition, yPosition;
    struct historico *head = NULL;
    char NomeFicheiro[50];

    tabuleiro = (int**)malloc(sizeof(int*)*jg.ylenght);
    if (tabuleiro!=NULL){
        for (int i = 0; i<jg.ylenght; i++){
            tabuleiro[i] = (int*)malloc(sizeof(int)*jg.xlenght);

            if(tabuleiro[i]==NULL){
                printf("Erro na alocacao de memoria\n");
            }
        }
    }
    else{
        printf("Erro na alocacao de memoria\n");
    }
    
    do{
        printf("Escolha entre 1 ou 2 jogadores '1' ou '2': ");
        //fflush(stdin);
        scanf("%d",&ModoJogo);
        printf("\n");
    }while(ModoJogo!=1 && ModoJogo!=2);

    InicializaTabuleiro(tabuleiro);
    
    while(playing){         
        posicao_valida=1;
        printTabuleiro(tabuleiro,jg.ylenght,jg.xlenght);
        
        modo = Input1(); // U, P, A ou J
        while(modo=='U' || modo=='u'){
            printf("\n"); //se remover n corre o input
            Input3(head,&jg.xlenght,&jg.ylenght,numeroRondas);
            modo = Input1(); // U, P, A ou J
        }

        if(modo=='J' || modo=='j'){
            printf("\n"); //se remover n corre o input
            Input2(tabuleiro,&jg.nPedrasA,&jg.nPedrasB,0);
        }
        else if(modo=='P' || modo=='p'){
            printf("\n"); //se remover n corre o input
            Input2(tabuleiro,&jg.nPedrasA,&jg.nPedrasB,1);
        }
        else if(modo=='A' || modo=='a'){
            printf("\n"); //se remover n corre o input
            modoResize = Input4();
            tabuleiro = ResizeTabuleiro(&jg.ylenght,&jg.xlenght,tabuleiro,modoResize,&jg.nAumentosA,&jg.nAumentosB);
        }

        AdicionaAoHistorico(&head,tabuleiro);

        playing = checkForWinner(tabuleiro);

        if(ModoJogo==2){
            ChangeCurrentPlayer();
        }

        else if(ModoJogo==1 && playing==1){ //contra um bot
            ChangeCurrentPlayer(); //dentro dos dois changecurrentplayer o bot joga com o "B"
            char output;
            output = randomPlayer(tabuleiro);
            
            if(output=='C' || output=='L'){
                modoResize = output;
                tabuleiro = ResizeTabuleiro(&jg.ylenght,&jg.xlenght,tabuleiro,modoResize,&jg.nAumentosA,&jg.nAumentosB);
            }

            AdicionaAoHistorico(&head,tabuleiro);
            playing = checkForWinner(tabuleiro);
            ChangeCurrentPlayer();
            numeroRondas++;
        }

        if(playing==0){
            printf("\nIndique o nome do ficheiro por favor (sem a extensao): ");
            //fflush(stdin);
            clear_buffer();
            scanf("%20s",NomeFicheiro);
            exportFile(head, NomeFicheiro);
        }
        numeroRondas++; 
    }
}
