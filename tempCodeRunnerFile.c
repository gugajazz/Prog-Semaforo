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