//main grid

void UI(time_t timebefore, char (*grid)[size], char (*grid2)[size], player player1, player player2, int remLines){
    system("cls");
    //printing the index number
    setCursorPosition(40, 1);
    setTextColor(reset);
    for(int i=0; i<size; i++){
        if(i == 10) printf("A");//hexadecimal digit instead of int 10
        else printf("%d ", i);
    }
    for(int i=0; i<size; i++){
        setCursorPosition(38, 2+i);
        if(i == 10) printf("A");//hexadecimal
        else printf("%d", i);
    }

    for (int i=0; i<size; i++){
        setCursorPosition(40, 2+i);
        for (int j=0; j<size; j++){
            setTextColor(reset);

            if(grid[i][j] == 'A'){
               setTextColor(player1.color);
               printf("%c ", grid2[i][j]);
            }
            else if(grid[i][j] == 'B'){
                setTextColor(player2.color);
                printf("%c ", grid2[i][j]);
            }
            else
                printf("%c ", grid[i][j]);
        }

        printf("\n");
    }

    setTextColor(red);
    printf("\n  player 1's name: %s\n\n",player1.name);
    printf("  number of moves for player 1: %d\n\n", player1.moves);
    printf("  player 1's score: %d\n\n", player1.score);
    setTextColor(green);
    printf("  no. of remaining lines: %d\n\n", remLines);
    //struct player player_2 = mode=="2 players""? player2 : computer;

    setTextColor(blue);
    setCursorPosition(0, size+3);
    printf("\t\t\t\t\t\tplayer 2's name: %s \n\n", player2.name);
    printf("\t\t\t\t\t\tnumber of moves for player 2: %d\n\n", player2.moves);
    printf("\t\t\t\t\t\tplayer 2's score: %d\n\n", player2.score);
    setTextColor(green);
    time_t timeafter = time(NULL);
    int min = (timeafter - timebefore) / 60;
    int sec = (timeafter - timebefore) % 60;
    printf("\t\t\t\t\t\ttime: %02d:%02d\n\n", min, sec);
    setTextColor(reset);

}
