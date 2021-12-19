#define red FOREGROUND_RED
#define blue FOREGROUND_BLUE
#define green FOREGROUND_GREEN
#define reset FOREGROUND_BLUE|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY


struct player{
    char* name;
    int score;
    char* color;
    int moves;
}
player1={.score=0, .color=red, .moves=0},
player2={.score=0, .color=blue, .moves=0},
computer={"computer", 0, blue, 0};

void setCursorPosition(int x, int y){
    COORD pos = {x, y};
    HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hstdout, pos);
}

void setTextColor(char* color){
    HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hstdout, color);
}


void UI(int nrow, int ncol){
    int nlines = 12;
    time_t seconds;
    seconds = time(NULL);
    int len = 2 * nrow + 1;
    char grid[len][len];
    for (int i=0; i<len; i++){
        setCursorPosition(40, 2+i);
        for (int j=0; j<len; j++){

            grid[i][j] = (i%2==0 && j%2==0)? 245 : ' ' ;

            printf("%c ", grid[i][j]);
        }

        printf("\n");
    }
    setCursorPosition(0, len+3);
    setTextColor(red);
    printf("player 1's name: \n\n");
    printf("number of moves for player 1: %d\n\n", player1.moves);
    printf("player 1's score: %d\n\n", player1.score);
    setTextColor(green);
    printf("no. of remaining lines: %d\n\n", nlines);
    //struct player player_2 = mode=="2 players""? player2 : computer;
    setCursorPosition(55+len, len+3);
    setTextColor(blue);
    printf("player 2's name: \n\n");
    setCursorPosition(55+len, len+5);
    printf("number of moves for player 2: %d\n\n", player2.moves);
    setCursorPosition(55+len, len+7);
    printf("player 2's score: %d\n\n", player2.score);
    setCursorPosition(55+len, len+9);
    setTextColor(green);
    int min = 0;
    int sec = 0;
    printf("time: %02d:%02d\n\n", min, sec);
    setTextColor(reset);


}
