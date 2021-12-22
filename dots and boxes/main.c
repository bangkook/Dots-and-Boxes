#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <time.h>
#include "computer.h"
#define red FOREGROUND_RED
#define blue FOREGROUND_BLUE
#define green FOREGROUND_GREEN
#define reset FOREGROUND_BLUE|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY
#define easy 2
#define medium 3
#define expert 5

int size, level, mode;


void setCursorPosition(int x, int y){
    COORD pos = {x, y};
    HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hstdout, pos);
}

void setTextColor(char* color){
    HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hstdout, color);
}



typedef struct{
    char name[20];
    int score;
    char* color;
    int moves;
}player;
player player1={.score=0, .color=red, .moves=0},
player2={.score=0, .color=blue, .moves=0},
computer={"computer", 0, blue, 0};



//mainmenu
void mainMenu(){
    setTextColor(green);
    printf("\n\t\t\t\tWelcome to\n\t\t\t      Dots and Boxes\n\n");
    setTextColor(reset);
   printf(" Enter 0 to start\n");
   printf(" Enter 1 to load a game\n");
   printf(" Enter 2 to view  Top 10 players\n");
   printf(" Enter 3 to exit\n\n ");
   int x;
   scanOfx:
   scanf("%i",&x);

   switch(x){

       case 0:system("cls");
              scanLevel:
              printf("\nEnter 0 for beginner\n");
              printf("\nEnter 1 for medium\n\nEnter 2 for expert\n\n");
              scanf("%i",&level);
              if(level == 0) size = 2 * easy + 1;
              else if (level == 1) size = 2 * medium + 1;
              else if (level == 2) size = 2 * expert + 1;
              system("cls");
              if(level!=0 && level!=1 && level!=2){
                  printf("invalid number.Please, enter another number\n");
                  goto scanLevel;
              }

              scanNOP:
              printf("\nEnter 0 for playing against the computer\n");
              printf("\nEnter 1 for 2 players\n\n");
              int numOfPlayers;
              scanf("%i",&numOfPlayers);
              system("cls");
              if(numOfPlayers==0 ){
                    mode = 0;
                  printf("Please, enter your name: ");
                  scanf("%s",&player1.name);
                  player2 = computer;
                  system("cls");
              }
              if(numOfPlayers==1 ){
                  mode = 1;
                  setTextColor(red);
                  printf("Please, enter player1 first name: ");
                  scanf("%s",&player1.name);
                  setTextColor(blue);
                  printf("\nPlease, enter player2 first name: ");
                  scanf("%s",&player2.name);
                  setTextColor(reset);
                  system("cls");
              }
              if(numOfPlayers!=0 && numOfPlayers!=1){
                  printf("invalid number.Please, enter another number\n");
                  goto scanNOP;
              }

               break;

      /* case 1:

       case 2:*/

       case 3: printf("bye");
               exit(1);


       default:
       printf("invalid number.Please enter another number\n");
       goto scanOfx;
   }
}

//main grid
void UI(int n, char (*grid)[size], player player1, player player2){
    int remLines = 2 * n * (n + 1);
    //printing the index number
    setCursorPosition(40, 1);
    for(int i=0; i<size; i++) printf("%d ", i);
    for(int i=0; i<size; i++){
        setCursorPosition(38, 2+i);
        printf("%d", i);
    }

    for (int i=0; i<size; i++){
        setCursorPosition(40, 2+i);
        for (int j=0; j<size; j++){

            grid[i][j] = (i%2==0 && j%2==0)? 254 : ' ' ;

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
    printf("\t\t\t\t\t\tplayer 2's name: %s \n\n",player2.name);
    printf("\t\t\t\t\t\tnumber of moves for player 2: %d\n\n", player2.moves);
    printf("\t\t\t\t\t\tplayer 2's score: %d\n\n", player2.score);
    setTextColor(green);
    printf("\t\t\t\t\t\ttime: %02d:%02d\n\n", 0, 0);
    setTextColor(reset);

}


void GameLoop(int n, char (*grid)[size]){
    int a1=0, a2=0, a3=0, a4=0;

    int remLines = 2 * n * (n + 1);

    int playerNo = 1;

    time_t starttime;
    starttime = time(NULL);
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
    char grid2[size][size];
        for (int z=0; z<size; z++){
          for (int j=0; j<size; j++){

            grid2[z][j] = (z%2==0 && j%2==0)? 254 : ' ' ;

        }

    }

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
            if(!ValidMove(row1-48, col1-48, row2-48, col2-48, grid, size)){
                setTextColor(reset);
                printf("\t\t\t\tMOVE IS NOT AVAILABLE!\n");
                continue;
            }
            //returning char value to its correct integer value
            row1 -= 48; row2 -= 48; col1 -= 48; col2 -= 48;
        }


        remLines--;

        //updateGrid(playerNo, 5, &grid, row1, col1, row2, col2, seconds, remLines, player1.moves, player1.score, player2.moves, player2.score);
        //playerNo = switchPlayer(playerNo);

        system("cls");
        time_t seconds;
        seconds = time(NULL);
        char l = playerNo == 1 ? 'A' : 'B';
        if(row1 == row2) {
            grid[row1][(col1 + col2) / 2] = l;
        }
        else if (col1 == col2){
            grid[(row1 + row2) / 2][col1] = l;
        }

        setTextColor(reset);
        //printing grid indix
        setCursorPosition(40, 1);
        for(int i=0; i<size; i++) printf("%d ", i);
        for(int i=0; i<size; i++){
            setCursorPosition(38, 2+i);
            printf("%d", i);
        }
        // number of moves
        if (playerNo==1) player1.moves++;
        else player2.moves++;
        for (int i=0; i<size; i++){
            setCursorPosition(40, 2+i);
            for (int j=0; j<size; j++){
                setTextColor(reset);
                if(grid[i][j] == 'A') {
                    setTextColor(player1.color);
                    if(newgrid[i][j] == 'h') {


                        grid2[i][j]= 205;
                    }
                    if(newgrid[i][j] == 'v') {


                        grid2[i][j]= 186;
                    }
                }
                else if(grid[i][j] == 'B'){
                    setTextColor(player2.color);
                    if(newgrid[i][j] == 'h') {

                        grid2[i][j]= 205;
                    }
                    if(newgrid[i][j] == 'v') {
                            grid2[i][j]= 186;
                    }
                }
                printf("%c ", grid2[i][j]);


            }
            if(grid[0][1]!=' '&&grid[1][2]!=' '&&grid[1][0]!=' '&&grid[2][1]!=' '&&a1==0){
                    grid[1][1]=l;
                    grid2[1][1]=l;
                    a1++;
                    if(l=='A') player1.score=player1.score+1;
                    else player2.score=player2.score+1;
                    playerNo = switchPlayer(playerNo);
            }
            if(grid[0][3]!=' '&&grid[1][2]!=' '&&grid[1][4]!=' '&&grid[2][3]!=' '&&a2==0){
                    grid[1][3]=l;
                    grid2[1][3]=l;
                    a2++;
                    if(l=='A') player1.score=player1.score+1;
                    else player2.score=player2.score+1;
                    playerNo = switchPlayer(playerNo);
            }
            if(grid[4][1]!=' '&&grid[3][2]!=' '&&grid[3][0]!=' '&&grid[2][1]!=' '&&a3==0){
                    grid[3][1]=l;
                    grid2[3][1]=l;
                    a3++;
                    if(l=='A') player1.score=player1.score+1;
                    else player2.score=player2.score+1;
                    playerNo = switchPlayer(playerNo);
            }
            if(grid[3][4]!=' '&&grid[3][2]!=' '&&grid[4][3]!=' '&&grid[2][3]!=' '&&a4==0){
                    grid[3][3]=l;
                    grid2[3][3]=l;
                    a4++;
                    if(l=='A') player1.score=player1.score+1;
                    else player2.score=player2.score+1;
                    playerNo = switchPlayer(playerNo);
            }
            setTextColor(reset);

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
        printf("\t\t\t\t\t\tplayer 2's name: %s \n\n",player2.name);
        printf("\t\t\t\t\t\tnumber of moves for player 2: %d\n\n", player2.moves);
        printf("\t\t\t\t\t\tplayer 2's score: %d\n\n", player2.score);
        setTextColor(green);
        int min = (seconds-starttime) / 60;
        int sec = (seconds-starttime) % 60;
        printf("\t\t\t\t\t\ttime: %02d:%02d\n\n", min, sec);
        setTextColor(reset);
        playerNo = switchPlayer(playerNo);

    }


}


int switchPlayer(int playerNo){

    return (playerNo==1? 2 : 1);
}

int ValidMove(int r1, int c1, int r2, int c2, char (*grid)[size], int size){//add if c2>c1 or r2>r1
    //not vaild if same point
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

int main(){


    mainMenu();

    //size of grid
    int n;
    if(level==0) n = easy;
    else if(level==1) n = medium;
    else if(level==2) n = expert;

    char grid[size][size];

    UI(n, grid, player1, player2);

    GameLoop(n, grid);
    //system("cls");




    return 0;
}
