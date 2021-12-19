void GameLoop(int remLines){
    int playerNo = 1;
    while(remLines != 0){
        char* color = playerNo==1? player1.color : player2.color;
        setTextColor(color);
        printf("player %d's turn\n", playerNo);
        printf("Enter row of first point: ");
        getchar();
        char row1 = getchar();
        printf("Enter column of first point: ");
        getchar();
        char col1 = getchar();
        printf("Enter row of second point: ");
        getchar();
        char row2 = getchar();
        printf("Enter row of second point: ");
        getchar();
        char col2 = getchar();

        //checkValid();
        //updateGrid();

        playerNo = switchPlayer(playerNo);
        remLines--;
    }


}

