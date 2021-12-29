void computerTurn(int size, char (*grid)[size], char *r, char *c){

    for( int i=0; i<size; i++){

        for(int j=0; j<size; j++){

            if((i%2==0 && j%2==1 || i%2==1 && j%2==0) && grid[i][j] == ' '){

                *r = i;
                *c = j;

            }

        }
    }
}
