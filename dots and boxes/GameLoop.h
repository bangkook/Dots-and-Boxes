#include "computer.h"
#include "Grid.h"

//function to check if move played is valid
int ValidMove(int r, int c, char (*grid)[size], int size){
    //valid only if it is a position of line and free
    if(r % 2 == 0 && c % 2 == 1 || r % 2 == 1 && c % 2 == 0)
        if(grid[r][c] == ' ')
            return 1;

    return 0;

}
//main loop of the game
int GameLoop(int n, int size, int mode, char (*grid)[size]){
    //total lines that can be drawn
    int remLines = 2 * n * (n + 1);
    //player1 starts the game
    int playerNo = 1, undo = 0;
    //time of starting game
    time_t starttime;
    starttime = time(NULL);
    //helping grid to store lines and be printed to screen
    char grid2[size][size];
    char h = 205;//horizontal line
    char v = 186;//vertical line
    for (int i=0; i<size; i++){

       for (int j=0; j<size; j++){
        //initializing the grid with dots and spaces
        grid[i][j] = (i%2==0 && j%2==0)? 254 : ' ' ;
        if(i % 2 == 0 && j % 2 != 0 && grid[i][j] == ' ')
                grid2[i][j] = h;//horizontal

        else if(i % 2 != 0 && j % 2== 0 && grid[i][j] == ' ')
            grid2[i][j] = v;//vertical

        else
            grid2[i][j] = grid[i][j];

        }

    }

     UI(starttime, grid, grid2, player1, player2, remLines);

    int boxes[n*n][5];
    //initializing last column to zero to indicate box is not checked
    for(int i = 0; i < n*n; i++)
        boxes[i][4] = 0;

    while(remLines != 0){
            //if mode 1
        char row, col;
        char* color = playerNo==1? player1.color : player2.color;
        setTextColor(color);
        if(playerNo == 2 && mode == 0){
            computerTurn(size, grid, &row, &col);
        }

        else {
            printf(" player %d's turn\n", playerNo);
            printf(" Enter row: ");
            row = get_int();
            printf(" Enter column: ");
            col = get_int();

            //returning char value to its correct integer value
            //row -= 48; col -= 48;

            if(!ValidMove(row, col, grid, size)){
                setTextColor(reset);
                UI(starttime, grid, grid2, player1, player2, remLines);
                printf("\t\t\t\tMOVE IS NOT AVAILABLE!\n");
                continue;
            }

        }



        remLines--;

        char l = playerNo == 1 ? 'A' : 'B';
        grid[row][col] = l;

        int scorebefore;
        // number of moves
        if (playerNo==1){
            player1.moves++;
            scorebefore = player1.score;
        }
        else{
            player2.moves++;
            scorebefore = player2.score;
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
                grid[c+1][d+1] = l;
                grid2[c+1][d+1] = l;
            }

            if(d < size - 4) {
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

    }

    setTextColor(reset);
    printf("\t\t\t\t\tGAME ENDED\n");
    if(player1.score > player2.score)
        printf("\t\t\t\t\tplayer 1 wins\n");
    else if(player2.score > player1.score)
        printf("\t\t\t\t\tplayer 2 wins\n");
    else{
        printf("\t\t\t\t\tTIE\n");
        return 0;
    }


    return playerNo;
}
