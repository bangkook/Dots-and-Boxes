#include "checkBox.h"
#include "computer.h"
#include "Grid.h"


//function to check if move played is valid
int ValidMove(int r, int c, char (*grid)[size], int size){

    //undo, redo, save and exit choices are valid
    if(r == 0 && c == 0 || r == 1 && c == 1 || r == 2 && c == 2 || r == 3 && c == 3)
        return 1;

    //valid only if it is a position of line and free
    if(r % 2 == 0 && c % 2 == 1 || r % 2 == 1 && c % 2 == 0)
        if(grid[r][c] == ' ')
            return 1;

    // any other move regarded invalid
    return 0;

}
//main loop of the game
int GameLoop(int starttime, int n, int boxes[n*n][2], int size, int mode, char (*grid)[size], char grid2[size][size], int playerNo, int remLines){

    time_t timeAfter;
    int timePassed = time(&timeAfter);
    timePassed -= starttime;

    int moves = 0, undo = 0, redo = 0, numOfUndo = 0;
    //array to store information about each move
    int movesPlayed[remLines][9];
    //[playerNo][row][column][row of checked box1][its column][box no.][row of checked box2][its column][box no.]

    int comp = 0;
    UI(timePassed, grid, grid2, player1, player2, remLines);

    while(remLines != 0){
        //position of line
        char row, col;

        char* color = playerNo == 1 ? player1.color : player2.color;

        char l = playerNo == 1 ? 'A' : 'B';

        setTextColor(color);

        if(playerNo == 2 && mode == 0){
            //computer AI
            computerTurn(grid, &row, &col, grid2, n, boxes, l, movesPlayed, moves);
        }

        else {

            printf(" player %d's turn\n", playerNo);

            printf(" Enter row: ");
            row = get_int();

            printf(" Enter column: ");
            col = get_int();

            //check if move is valid or not
            if(!ValidMove(row, col, grid, size)){
                setTextColor(reset);
                UI(timePassed, grid, grid2, player1, player2, remLines);
                printf("\t\t\t\tMOVE IS NOT AVAILABLE!\n");
                continue;
            }

        }

        int save = 0;

        if(row == 0 && col == 0) undo = 1;//undo
        if(row == 1 && col == 1) redo = 1;//redo
        if(row == 2 && col == 2) save = 1;//save game
        if(row == 3 && col == 3) exit(1);//exit game

        if(save){

            system("cls");
            setTextColor(reset);
            //name of file to save to
            char file_name[5];

            scan:

            printf("Enter number of file (1 or 2 or 3): ");
            int f = get_int();//number of file

            if(f == 1 || f == 2 || f == 3){

                sprintf(file_name, "%d.bin", f);
                //get time passed of game before saving
                time_t currenttime;
                int current = time(&currenttime);
                starttime = current - timePassed;

                FILE *savedGame;
                //open as binary file
                savedGame = fopen(file_name, "wb");

                //write all needed information of the game to the file
                fwrite(&starttime, sizeof(int), 1, savedGame);
                fwrite(&size, sizeof(int), 1, savedGame);
                fwrite(&n, sizeof(int), 1, savedGame);
                fwrite(&mode, sizeof(int), 1, savedGame);
                fwrite(&player1, sizeof(player), 1, savedGame);
                fwrite(&player2, sizeof(player), 1, savedGame);
                fwrite(&remLines, sizeof(int), 1, savedGame);
                fwrite(&playerNo, sizeof(int), 1, savedGame);
                fwrite(grid, sizeof(char), size * size, savedGame);
                fwrite(grid2, sizeof(char), size * size, savedGame);
                fwrite(boxes, sizeof(int), n * n * 2, savedGame);

                //close file
                fclose(savedGame);
                //update interface
                UI(timePassed, grid, grid2, player1, player2, remLines);
                printf("successfully saved to %s\n\n", file_name);

                continue;
            }

            else{

                printf("wrong number.\n");
                goto scan;
            }
        }


        if(undo){

            if(moves == 0){
                setTextColor(reset);
                UI(timePassed, grid, grid2, player1, player2, remLines);
                printf("no moves to undo\n");
                undo = 0;
                continue;
            }

            int i;
            //if player 2 is computer loop back till last move of player 1 and erase all moves in between
            for(i = moves - 1; i >= 0; i--){
                remLines++;
                if(mode == 0 && movesPlayed[i][0] == 2){
                    grid[movesPlayed[i][1]][movesPlayed[i][2]] = ' ';
                    if(movesPlayed[i][3] != 0){
                        grid[movesPlayed[i][3]][movesPlayed[i][4]] = ' ';
                        grid2[movesPlayed[i][3]][movesPlayed[i][4]] = ' ';
                        boxes[movesPlayed[i][5]][1] = 0;
                        player2.score--;
                    }
                    if(movesPlayed[i][6] != 0){
                        grid[movesPlayed[i][6]][movesPlayed[i][7]] = ' ';
                        grid2[movesPlayed[i][6]][movesPlayed[i][7]] = ' ';
                        boxes[movesPlayed[i][8]][1] = 0;
                        player2.score--;
                    }
                    player2.moves--;
                }
                else break;

            }
            //erase player's last move
            grid[movesPlayed[i][1]][movesPlayed[i][2]] = ' ';
            if(movesPlayed[i][3] != 0){
                grid[movesPlayed[i][3]][movesPlayed[i][4]] = ' ';
                grid2[movesPlayed[i][3]][movesPlayed[i][4]] = ' ';
                boxes[movesPlayed[i][5]][1] = 0;
                if(movesPlayed[i][0] == 1) player1.score--;
                if(movesPlayed[i][0] == 2) player2.score--;
            }
            if(movesPlayed[i][6] != 0){
                grid[movesPlayed[i][6]][movesPlayed[i][7]] = ' ';
                grid2[movesPlayed[i][6]][movesPlayed[i][7]] = ' ';
                boxes[movesPlayed[i][8]][1] = 0;
                if(movesPlayed[i][0] == 1) player1.score--;
                if(movesPlayed[i][0] == 2) player2.score--;
            }

            //decrement number of moves
            if(movesPlayed[i][0] == 1){
                player1.moves--;
                playerNo = 1;
            }
            else if(movesPlayed[i][0] == 2){
                player2.moves--;
                playerNo = 2;
            }

            undo = 0;
            numOfUndo++;
            moves = i;
            UI(timePassed, grid, grid2, player1, player2, remLines);
            continue;

        }

        if(redo){
            if(numOfUndo == 0){
                setTextColor(reset);
                UI(timePassed, grid, grid2, player1, player2, remLines);
                printf("no moves to redo\n");
                redo = 0;
                continue;
            }
            char p = movesPlayed[moves][0] == 1? 'A' : 'B';
            //loop to handle redo when player 2 is computer
            for(int i = moves; i < remLines; i++){
                if(movesPlayed[i][0] == 2 && mode == 0){
                    grid[movesPlayed[i][1]][movesPlayed[i][2]] = 'B';
                    if(movesPlayed[i][3] != 0){
                        grid[movesPlayed[i][3]][movesPlayed[i][4]] = 'B';
                        grid2[movesPlayed[i][3]][movesPlayed[i][4]] = 'B';
                        boxes[movesPlayed[i][5]][1] = 1;
                        player2.score++;
                    }
                    if(movesPlayed[i][6] != 0){
                        grid[movesPlayed[i][6]][movesPlayed[i][7]] = 'B';
                        grid2[movesPlayed[i][6]][movesPlayed[i][7]] = 'B';
                        boxes[movesPlayed[i][8]][1] = 1;
                        player2.score++;
                    }
                    player2.moves++;
                    remLines--;
                    moves++;
                }
                //when found move of player 1
                else break;
            }
            //append the move and update score
            grid[movesPlayed[moves][1]][movesPlayed[moves][2]] = p;
            if(movesPlayed[moves][3] != 0){
                grid[movesPlayed[moves][3]][movesPlayed[moves][4]] = p;
                grid2[movesPlayed[moves][3]][movesPlayed[moves][4]] = p;
                boxes[movesPlayed[moves][5]][1] = 1;
                if(movesPlayed[moves][0] == 1) player1.score++;
                if(movesPlayed[moves][0] == 2) player2.score++;
            }
            if(movesPlayed[moves][6] != 0){
                grid[movesPlayed[moves][6]][movesPlayed[moves][7]] = p;
                grid2[movesPlayed[moves][6]][movesPlayed[moves][7]] = p;
                boxes[movesPlayed[moves][8]][1] = 1;
                if(movesPlayed[moves][0] == 1) player1.score++;
                if(movesPlayed[moves][0] == 2) player2.score++;
            }

            remLines--;
            //increment number of moves and switch turns if player didn't score points
            if(movesPlayed[moves][0] == 1){
                player1.moves++;
                if(movesPlayed[moves][3] == 0) playerNo = 2;
            }
            else if(movesPlayed[moves][0] == 2){
                player2.moves++;
                if(movesPlayed[moves][3] == 0) playerNo = 1;
            }

            redo = 0;
            //decrement number of moves to redo
            numOfUndo--;
            moves++;
            UI(timePassed, grid, grid2, player1, player2, remLines);
            continue;
        }

        //clear redo if player made a new move
        if(!(playerNo == 2 && mode == 0)) numOfUndo = 0;
        movesPlayed[moves][0] = playerNo;
        movesPlayed[moves][1] = row;//row of line
        movesPlayed[moves][2] = col;//column of line
        movesPlayed[moves][3] = 0;
        movesPlayed[moves][4] = 0;
        movesPlayed[moves][6] = 0;
        movesPlayed[moves][7] = 0;

        remLines--;

        grid[row][col] = l;//player is assigned to position

        //score before checking completed boxes
        int scorebefore;
        // increment number of moves
        if (playerNo==1){
            player1.moves++;
            scorebefore = player1.score;
        }

        else{
            player2.moves++;
            scorebefore = player2.score;
        }

        //check if move completes a box
        check_box(grid, grid2, n, boxes, l, 0, movesPlayed, moves);
        //update interface
        UI(timePassed, grid, grid2, player1, player2, remLines);

        //switch player if his move didn't complete a box, else give him another turn
        if(playerNo == 1 && player1.score == scorebefore)
             playerNo = switchPlayer(playerNo);
        else if(playerNo == 2 && player2.score == scorebefore)
            playerNo = switchPlayer(playerNo);

        moves++;

    }

    //display winner
    setTextColor(reset);
    printf("\t\t\t\t\tGAME ENDED\n");
    if(player1.score > player2.score){
        setTextColor(red);
        printf("\t\t\t\t\t%s wins\n", player1.name);
        printf("\t\t\t\t\tscore: %d", player1.score);
    }
    else if(player2.score > player1.score){
        setTextColor(blue);
        printf("\t\t\t\t\t%s wins\n", player2.name);
        printf("\t\t\t\t\tscore: %d\n", player2.score);
    }
    else{
        printf("\t\t\t\t\tTIE\n");
        return 0;
    }
    setTextColor(reset);
    //number of winner
    return playerNo;
}
