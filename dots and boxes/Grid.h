//main grid

void UI(int timebefore, char (*grid)[size], char (*grid2)[size], player player1, player player2, int remLines){
    //clear screen
    system("cls");

    setTextColor(green);

    //print number of remaining lines
    printf("  no. of remaining lines: %d\n\n", remLines);

    //print passed time since game started
    time_t timeafter = time(NULL);
    int min = (timeafter - timebefore) / 60;
    int sec = (timeafter - timebefore) % 60;
    printf("  time: %02d:%02d\n\n", min, sec);

    //printing the index number
    setCursorPosition(40, 1);
    setTextColor(reset);
    //columns indexes
    for(int i=0; i<size; i++){

        if(i == 10) printf("A");//hexadecimal digit instead of int 10
        else printf("%d ", i);

    }
    //rows indexes
    for(int i=0; i<size; i++){

        setCursorPosition(38, 2+i);
        if(i == 10) printf("A");//hexadecimal
        else printf("%d", i);

    }

    FILE *fp;
    //open grid file for appending new data
    fp = fopen("grid.txt", "a");

    char p;//character that will be printed to the file
    char h = 205;//horizontal line ASCII code

    for (int i=0; i<size; i++){
        //position to be printed at
        setCursorPosition(40, 2+i);

        for (int j=0; j<size; j++){

            setTextColor(reset);

            if(grid[i][j] == 'A'){

               setTextColor(player1.color);
               printf("%c ", grid2[i][j]);

               if(grid2[i][j] == h) p = '-';
               else if(grid2[i][j] == 'A') p = 'A';
               else p = '|';

               fputc(p, fp);

            }
            else if(grid[i][j] == 'B'){

                setTextColor(player2.color);
                printf("%c ", grid2[i][j]);

                if(grid2[i][j] == h) p = '-';
                else if(grid2[i][j] == 'B') p = 'B';
                else p = '|';

                fputc(p, fp);

            }
            else
                printf("%c ", grid[i][j]);

                if(i % 2 == 0 && j % 2 == 0) p = '*';
                else p = ' ';

                fputc(p, fp);
        }

        printf("\n");
        fprintf(fp,"\n");
    }
    fprintf(fp,"\n");
    //close file
    fclose(fp);

    //print each player's information
    setTextColor(red);
    printf("\n  player 1's name: %s\n\n",player1.name);
    printf("  number of moves for player 1: %d\n\n", player1.moves);
    printf("  player 1's score: %d\n\n", player1.score);

    setTextColor(blue);
    setCursorPosition(40, size+3);
    printf("player 2's name: %s \n\n", player2.name);
    setCursorPosition(40, size+5);
    printf("number of moves for player 2: %d\n\n", player2.moves);
    setCursorPosition(40, size+7);
    printf("player 2's score: %d\n\n", player2.score);

    //in game menu to undo, redo, save or exit game
    setTextColor(reset);
    printf("\tUNDO (0,0)\tREDO (1,1)\tSAVE (2,2)\tEXIT (3,3)\n\n");

}
