#include "computer.h"
#include "Grid.h"
#include <stdlib.h>

int ValidMove(int r1, int c1, int r2, int c2, char (*grid)[size], int size){
    //not valid if same point or random point
    if(r1==r2 && c1==c2 || r1 != r2 && c1!=c2)
        return 0;
    if (c1 % 2 != 0 || c2 % 2 != 0 || r1 % 2 != 0 || r2 % 2 != 0)
        return 0;
    if(r1==r2 && grid[r1][(c1+c2)/2] != ' ')
        return 0;
    if(c1==c2 && grid[(r1+r2)/2][c1] != ' ')
        return 0;
    if(r1<0 || r1>size-1 || c1<0 || c1>size-1 || r2<0 || r2>size-1 || c2<0 || c2>size-1)
        return 0;
    if(r1 == r2 && abs(c1-c2) != 2)
        return 0;
    if(c1 == c2 && abs(r1-r2) != 2)
        return 0;

    return 1;

}

void GameLoop(int n, int size, int mode, char (*grid)[size]){

    int remLines = 2 * n * (n + 1);

    int playerNo = 1, undo = 0;

    time_t starttime;
    starttime = time(NULL);

    char grid2[size][size];
    for (int i=0; i<size; i++){

       for (int j=0; j<size; j++){

        grid[i][j] = (i%2==0 && j%2==0)? 254 : ' ' ;
        grid2[i][j] = grid[i][j];

        }

    }
    //grid to store information of positions of lines either vertical or horizontal
    char newgrid[size][size];

    for(int i=0; i<size; i++){
        for(int j=0; j<size; j++){
            if(i % 2 == 0 && j % 2 != 0 && grid[i][j] == ' ')
                newgrid[i][j] = 'h';//horizontal

            else if(i % 2 != 0 && j % 2== 0 && grid[i][j] == ' ')
                newgrid[i][j] = 'v';//vertical

            else
                newgrid[i][j] = grid[i][j];
        }
    }

     UI(starttime, grid, grid2, player1, player2, remLines);

    int boxes[n*n][5];
    while(remLines != 0){
            //if mode 1
        char row1, row2, col1, col2;
        char* color = playerNo==1? player1.color : player2.color;
        setTextColor(color);
        if(playerNo == 2 && mode == 0){
            computerTurn(size, grid, &row1, &row2, &col1, &col2);
        }

        else {
            printf(" player %d's turn\n", playerNo);
            printf(" Enter row of first point: ");
            scanf(" %c", &row1);
            printf(" Enter column of first point: ");
            scanf(" %c", &col1);
            printf(" Enter row of second point: ");
            scanf(" %c", &row2);
            printf(" Enter column of second point: ");
            scanf(" %c", &col2);

            //returning char value to its correct integer value
            row1 -= 48; row2 -= 48; col1 -= 48; col2 -= 48;



            if(!ValidMove(row1, col1, row2, col2, grid, size)){
                setTextColor(reset);
                system("cls");
                UI(starttime, grid, grid2, player1, player2, remLines);
                printf("\t\t\t\tMOVE IS NOT AVAILABLE!\n");
                continue;
            }

        }

        //undo store last move then delete it , redo restore it
        if(undo){
                system("cls");
                player1.moves--;
                player2.moves--;

                grid2[player1.lastmove[0]][player1.lastmove[1]] = ' ';
                grid2[player2.lastmove[0]][player2.lastmove[1]] = ' ';
                grid[player1.lastmove[0]][player1.lastmove[1]] = ' ';
                grid[player2.lastmove[0]][player2.lastmove[1]] = ' ';

                remLines += 2;
                playerNo = switchPlayer(playerNo);
            }



        //else{
            remLines--;

            //updateGrid(playerNo, 5, &grid, row1, col1, row2, col2, seconds, remLines, player1.moves, player1.score, player2.moves, player2.score);
            //playerNo = switchPlayer(playerNo);

            system("cls");

            char l = playerNo == 1 ? 'A' : 'B';
            grid[(row1 + row2) / 2][(col1 + col2) / 2] = l;

            int scorebefore;
            // number of moves
            if (playerNo==1){
                player1.moves++;
                scorebefore = player1.score;
                player1.lastmove[0] = (row1 + row2) / 2;
                player1.lastmove[1] = (col1 + col2) / 2;
            }
            else{
                player2.moves++;
                scorebefore = player2.score;
                player2.lastmove[0] = (row1 + row2) / 2;
                player2.lastmove[1] = (col1 + col2) / 2;
            }
        //}

        for (int i=0; i<size; i++){

            for (int j=0; j<size; j++){

                if(grid[i][j] == 'A') {

                    if(newgrid[i][j] == 'h') {

                        grid2[i][j]= 205;
                    }
                    if(newgrid[i][j] == 'v') {

                        grid2[i][j]= 186;
                    }
                }
                else if(grid[i][j] == 'B'){

                    if(newgrid[i][j] == 'h') {

                        grid2[i][j]= 205;
                    }
                    if(newgrid[i][j] == 'v') {
                            grid2[i][j]= 186;
                    }
                }

            }

        }


        //check if move completes a box
        int c = 0, d = 0, v = 0, s = 0;
        while(v < n*n){
            for(int i = c; i <= c+2; i++){
                if(boxes[v][4] == 1) break;
                for(int j = d; j <= d+2; j++){
                    if(i % 2 == 1 && j % 2 == 0 || i % 2 == 0 && j % 2 == 1){
                        if(grid[i][j] == 'A' || grid[i][j] == 'B') {boxes[v][s++] = 1;}
                    }
                }
            }
            if(s == 4 && boxes[v][4] != 1){
                if(l == 'A') player1.score++;
                else player2.score++;
                boxes[v][4] = 1;
                grid2[c+1][d+1] = l;
                grid[c+1][d+1] = l;
            }
            if(d < n) {
                d += 2;
            }
            else{
               c += 2;
               d = 0;
            }
            s = 0;
            v++;
        }

        //update interface
        UI(starttime, grid, grid2, player1, player2, remLines);

        //switch player if his move didn't complete a box, else give him another turn
        if(playerNo == 1 && player1.score == scorebefore)
             playerNo = switchPlayer(playerNo);
        else if(playerNo == 2 && player2.score == scorebefore)
            playerNo = switchPlayer(playerNo);

        undo = 0;

    }


}
