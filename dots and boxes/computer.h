void computerTurn(char (*grid)[size], char *r, char *c, char (*grid2)[size], int n, int boxes[n*n][2], char l, int movesPlayed[2*n*(n+1)][9], int moves){
    //algorithm for computer's turn to help it to win
    int i, j, checked = 0, good_move = 0, comp = 1;

    for(i = 0; i < size; i++){

        for(j = 0; j < size; j++){

            if((i % 2 == 0 && j % 2 == 1 || i % 2 == 1 && j % 2 == 0) && grid[i][j] == ' '){

                grid[i][j] = l;
                //if this move checks a box return that move
                checked = check_box(grid, grid2, n, boxes, l, comp, movesPlayed , moves);
                if(checked > 0){
                    good_move = 1;
                    grid[i][j] = ' ';
                    break;
                }

                else{
                    grid[i][j] = ' ';
                }
            }

        }
        if(good_move)//if found good move break from second array
            break;
    }

    if(!good_move){//try not to help the other player

        for(i = 0; i < size; i++){

            for(j = 0; j < size; j++){

                //if available move
                if((i % 2 == 0 && j % 2 == 1 || i % 2 == 1 && j % 2 == 0) && grid[i][j] == ' '){

                    grid[i][j] = l;
                    int found = 1;//found a move that doesn't help user

                    for(int x = 0; x < size; x++){

                        for(int y = 0; y < size; y++){

                            if((x % 2 == 0 && y % 2 == 1 || x % 2 == 1 && y % 2 == 0) && grid[x][y] == ' '){
                                grid[x][y] = l;
                                //if a move after computer's move closes a box, then it is a bad move
                                checked = check_box(grid, grid2, n, boxes, l, comp, movesPlayed, moves);
                                if(checked > 0){
                                    grid[x][y] = ' ';
                                    grid[i][j] = ' ';
                                    found = 0;
                                    break;
                                }

                                else{
                                    grid[x][y] = ' ';
                                }


                            }


                        }

                        if(!found) break;
                    }

                    if(found){
                    good_move = 1;//found move that doesn't help the other player
                    grid[i][j] = ' ';
                    break;
                    }
                }


            }
            if(good_move) break;
        }

    }

    if(!good_move){//if there is no good move, return any valid move

        int foundmove = 0;

        for(i = 0; i < size; i++){

            for(j = 0; j < size; j++){

                if((i % 2 == 0 && j % 2 == 1  || i % 2 == 1 && j % 2 == 0) && grid[i][j] == ' '){

                   foundmove = 1;
                    break;

                }
            }

            if(foundmove)
                break;
        }
    }
    //return found row and column
    *r = i;
    *c = j;

}
