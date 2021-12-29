void undo(int *remLines, int size, int mode, int *moves, int *playerNo, int grid[size][size], int (*boxes)[5], int grid2[size][size], player player1, player player2, int movesPlayed[remLines][9]){
 int movesPlayed[remLines][9];//array to store information about each move
    //[playerNo][row][column][row of checked box1][its column][box no.][row of checked box2][its column][box no.]
    int moves = 0;
 if(mode == 1){
            if(moves == 0){
                setTextColor(reset);
                UI(starttime, grid, grid2, player1, player2, remLines);
                printf("no moves to undo\n");
            }
            grid[movesPlayed[moves-1][1]][movesPlayed[moves-1][2]] = ' ';
            grid2[movesPlayed[moves-1][1]][movesPlayed[moves-1][2]] = ' ';
            if(movesPlayed[moves-1][3] != 0){
                grid[movesPlayed[moves-1][3]][movesPlayed[moves-1][4]] = ' ';
                grid2[movesPlayed[moves-1][3]][movesPlayed[moves-1][4]] = ' ';
                boxes[movesPlayed[moves-1][5]][4] = 0;
                if(movesPlayed[moves-1][0] == 1) player1.score--;
                if(movesPlayed[moves-1][0] == 2) player2.score--;
            }
            if(movesPlayed[moves-1][6] != 0){
                grid[movesPlayed[moves-1][6]][movesPlayed[moves-1][7]] = ' ';
                grid2[movesPlayed[moves-1][6]][movesPlayed[moves-1][7]] = ' ';
                boxes[movesPlayed[moves-1][8]][4] = 0;
                if(movesPlayed[moves-1][0] == 1) player1.score--;
                if(movesPlayed[moves-1][0] == 2) player2.score--;
            }

            remLines++;
            if(movesPlayed[moves-1][0] == 1){
                player1.moves--;
                playerNo = 1;
            }
            else if(movesPlayed[moves-1][0] == 2){
                player2.moves--;
                playerNo = 2;
            }
            undo = 0;
            moves--;
            UI(starttime, grid, grid2, player1, player2, remLines);
            continue;


        }
        else if(undo && mode == 0){//if player 2 is computer return till player 1 last turn and cancel moves in between
            if(moves == 0){
                setTextColor(reset);
                UI(starttime, grid, grid2, player1, player2, remLines);
                printf("no moves to undo\n");
                undo = 0;
                continue;
            }
            int i;
            for(i = moves - 1; i >= 0; i--){
                remLines++;
                if(movesPlayed[i][0] == 2){
                    grid[movesPlayed[i][1]][movesPlayed[i][2]] = ' ';
                    grid2[movesPlayed[i][1]][movesPlayed[i][2]] = ' ';
                    if(movesPlayed[i][3] != 0){
                        grid[movesPlayed[i][3]][movesPlayed[i][4]] = ' ';
                        grid2[movesPlayed[i][3]][movesPlayed[i][4]] = ' ';
                        boxes[movesPlayed[i][5]][4] = 0;
                        player2.score--;
                    }
                    if(movesPlayed[i][6] != 0){
                        grid[movesPlayed[i][6]][movesPlayed[i][7]] = ' ';
                        grid2[movesPlayed[i][6]][movesPlayed[i][7]] = ' ';
                        boxes[movesPlayed[i][8]][4] = 0;
                        player2.score--;
                    }
                    player2.moves--;
                }
                else if(movesPlayed[i][0] == 1){
                    grid[movesPlayed[i][1]][movesPlayed[i][2]] = ' ';
                    grid2[movesPlayed[i][1]][movesPlayed[i][2]] = ' ';
                    if(movesPlayed[i][3] != 0){
                        grid[movesPlayed[i][3]][movesPlayed[i][4]] = ' ';
                        grid2[movesPlayed[i][3]][movesPlayed[i][4]] = ' ';
                        boxes[movesPlayed[i][5]][4] = 0;
                        player1.score--;
                    }
                    if(movesPlayed[i][6] != 0){
                        grid[movesPlayed[i][6]][movesPlayed[i][7]] = ' ';
                        grid2[movesPlayed[i][6]][movesPlayed[i][7]] = ' ';
                        boxes[movesPlayed[i][8]][4] = 0;
                        player1.score--;
                    }
                    player1.moves--;
                    break;
                }

            }

            moves = i;
            playerNo = 1;
            UI(starttime, grid, grid2, player1, player2, remLines);
            continue;
        }

}
