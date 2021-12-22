void computerTurn(int size, char (*grid)[size], char *r1, char *r2, char *c1, char *c2){

    for( int i=0; i<size; i++){

        for(int j=0; j<size; j++){

            for(int x=0; x<size; x++){

                for(int y=0; y<size; y++){

                    if(i%2==0 && j%2==0 && x%2==0 && y%2==0 && grid[(i+x)/2][(j+y)/2] == ' '){
                        if(i == x && abs(j-y) == 2 || j == y && abs(i-x) == 2){
                            *r1 = i;
                            *c1 = j;
                            *r2 = x;
                            *c2 = y;
                        }
                    }

                }
            }
        }
    }


}
