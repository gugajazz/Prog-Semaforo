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
    printTabuleiro(ylenght,xlenght,tabuleiro);
    ResizeTabuleiro(&ylenght,&xlenght,tabuleiro,'Y');
    printTabuleiro(ylenght,xlenght,tabuleiro);

    /* while(playing){
        printTabuleiro(xlenght,ylenght,tabuleiro);
        GetInput(&xPosition,&yPosition,current_player,tabuleiro, xlenght, ylenght);
        playing = checkForWinner(xlenght,ylenght,tabuleiro,&current_player);
    } */
}