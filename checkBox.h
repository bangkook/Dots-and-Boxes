int check_box (char grid[size][size], char grid2[size][size], int n, int boxes[n*n][2], char l, int comp, int movesPlayed[2*n*(n+1)][9], int moves){

    //check if move completes a box
    int c = 0, d = 0, v = 0, count = 0;

    while(v < n*n){//loop through all boxes

        //initialize number of checked sides to zero
        boxes[v][0] = 0;

        for(int i = c; i <= c + 2; i++){
            //if box is already completed, no need to check it
            if(boxes[v][1] == 1) break;

            for(int j = d; j <= d + 2; j++){
                //if it is a valid position of line
                if(i % 2 == 1 && j % 2 == 0 || i % 2 == 0 && j % 2 == 1){
                    //counting no. of sides
                    if(grid[i][j] == 'A' || grid[i][j] == 'B') boxes[v][0] += 1;

                }
            }
        }

        // if all sides of a box are drawn and the box is not checked before, then check it
        if(boxes[v][0] == 4 && boxes[v][1] == 0){
            //not computer's turn
            if(comp == 0){
                //increment score
                if(l == 'A') player1.score++;
                else player2.score++;

                boxes[v][1] = 1;
                grid[c+1][d+1] = l;
                grid2[c+1][d+1] = l;

                if(movesPlayed[moves][3] == 0){
                    movesPlayed[moves][3] = c + 1;
                    movesPlayed[moves][4] = d + 1;
                    movesPlayed[moves][5] = v;
                }

                else if(movesPlayed[moves][6] == 0){
                    movesPlayed[moves][6] = c + 1;
                    movesPlayed[moves][7] = d + 1;
                    movesPlayed[moves][8] = v;
                }

            }

            count++;
        }

        if(d < size - 4) {
            d += 2;
        }

        else{
           c += 2;
           d = 0;
        }

        v++;
    }

    //number of completed boxes by a player in each turn
    return count;

}
