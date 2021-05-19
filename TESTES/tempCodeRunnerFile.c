tabuleiro[*xlenght] = malloc(sizeof(int)*(*ylenght));
            if(tabuleiro[*xlenght]==NULL){
                printf("ERRO NA ALOCACAO DE MEMORIA X2\n");
                return 1;
            }