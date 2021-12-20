#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <time.h>
#include "MainMenu.h"
#include "updateGrid.h"
#define red FOREGROUND_RED
#define blue FOREGROUND_BLUE
#define green FOREGROUND_GREEN
#define reset FOREGROUND_BLUE|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY

void setCursorPosition(int x, int y){
    COORD pos = {x, y};
    HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hstdout, pos);
}

void setTextColor(char* color){
    HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hstdout, color);
}

//array to store moves played in the game in the order row column player
int movesplayed[][3];

typedef struct{
    char* name;
    int score;
    char* color;
    int moves;
}player;
player player1={.score=0, .color=red, .moves=0},
player2={.score=0, .color=blue, .moves=0},
computer={"computer", 0, blue, 0};

//main grid
void UI(int size, char (*grid)[5], player player1, player player2){
    int remLines = 12;
    setCursorPosition(40, 1);
    for(int i=0; i<size; i++) printf("%d ", i);
    for(int i=0; i<size; i++){
        setCursorPosition(38, 2+i);
        printf("%d", i);
    }

    for (int i=0; i<size; i++){
        setCursorPosition(40, 2+i);
        for (int j=0; j<size; j++){

            grid[i][j] = (i%2==0 && j%2==0)? '*' : ' ' ;

            printf("%c ", grid[i][j]);
        }

        printf("\n");
    }
    setCursorPosition(0, size+3);
    setTextColor(red);
    printf("player 1's name: \n\n");
    printf("number of moves for player 1: %d\n\n", player1.moves);
    printf("player 1's score: %d\n\n", player1.score);
    setTextColor(green);
    printf("no. of remaining lines: %d\n\n", remLines);
    //struct player player_2 = mode=="2 players""? player2 : computer;
    setCursorPosition(55+size, size+3);
    setTextColor(blue);
    printf("player 2's name: \n\n");
    setCursorPosition(55+size, size+5);
    printf("number of moves for player 2: %d\n\n", player2.moves);
    setCursorPosition(55+size, size+7);
    printf("player 2's score: %d\n\n", player2.score);
    setCursorPosition(55+size, size+9);
    setTextColor(green);
    printf("time: %02d:%02d\n\n", 0, 0);
    setTextColor(reset);

}


void GameLoop(int size, char (*grid)[5]){
    int nmoves = 0;
    int remLines = 12;
    int playerNo = 1;
    time_t starttime;
    starttime = time(NULL);
    char newgrid[size][size];

    for(int i=0; i<size; i++){
        for(int j=0; j<size; j++){
            if(i % 2 == 0 && j % 2 != 0 && grid[i][j] == ' ')
                newgrid[i][j] = 'h';

            else if(i % 2 != 0 && j % 2== 0 && grid[i][j] == ' ')
                newgrid[i][j] = 'v';

            else
                newgrid[i][j] = grid[i][j];
        }
    }

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
        printf("Enter column of second point: ");
        getchar();
        char col2 = getchar();

        if(!ValidMove(row1-48, col1-48, row2-48, col2-48, grid, size)){
            setTextColor(reset);
            printf("\t\t\t\tMOVE IS NOT AVAILABLE!\n");
            continue;
        }

        remLines--;
        nmoves++;
        //updateGrid(playerNo, 5, &grid, row1, col1, row2, col2, seconds, remLines, player1.moves, player1.score, player2.moves, player2.score);
        //playerNo = switchPlayer(playerNo);
        system("cls");
        time_t seconds;
        seconds = time(NULL);
        char l = playerNo == 1 ? 'A' : 'B';
        if(row1 == row2) {
            grid[row1 - 48][(col1 + col2) / 2 - 48] = l;
        }
        else if (col1 == col2){
            grid[(row1 + row2) / 2 - 48][col1 - 48] = l;
        }

        int horizontal = 0;
        if(row1 == row2) horizontal = 1;
        int vertical = 0;
        if(col1 == col2) vertical = 1;

        setTextColor(reset);
        setCursorPosition(40, 1);
        for(int i=0; i<size; i++) printf("%d ", i);
        for(int i=0; i<size; i++){
            setCursorPosition(38, 2+i);
            printf("%d", i);
        }

        for (int i=0; i<size; i++){
            setCursorPosition(40, 2+i);
            for (int j=0; j<size; j++){
                setTextColor(reset);
                if(grid[i][j] == 'A') {
                    setTextColor(player1.color);
                    if(newgrid[i][j] == 'h') {
                        setCursorPosition(40+j, 2+i);
                        printf("---");
                    }
                    if(newgrid[i][j] == 'v') {
                        setCursorPosition(40+j, 2+i);
                        printf('*');
                    }
                }
                else if(grid[i][j] == 'B'){
                    setTextColor(player2.color);
                    if(newgrid[i][j] == 'h') printf("---");
                    if(newgrid[i][j] == 'v') printf('|');
                }


            }

            printf("\n");
        }

        if (playerNo==1) player1.moves++;
        else player2.moves++;

        setCursorPosition(0, size+3);
        setTextColor(red);
        printf("player 1's name: \n\n");
        printf("number of moves for player 1: %d\n\n", player1.moves);
        printf("player 1's score: %d\n\n", player1.score);
        setTextColor(green);
        printf("no. of remaining lines: %d\n\n", remLines);
        //struct player player_2 = mode=="2 players""? player2 : computer;
        setCursorPosition(55+size, size+3);
        setTextColor(blue);
        printf("player 2's name: \n\n");
        setCursorPosition(55+size, size+5);
        printf("number of moves for player 2: %d\n\n", player2.moves);
        setCursorPosition(55+size, size+7);
        printf("player 2's score: %d\n\n", player2.score);
        setCursorPosition(55+size, size+9);
        setTextColor(green);
        int min = (seconds-starttime) / 60;
        int sec = (seconds-starttime) % 60;
        printf("time: %02d:%02d\n\n", min, sec);
        setTextColor(reset);
        playerNo = switchPlayer(playerNo);

    }


}


int switchPlayer(int playerNo){

    return (playerNo==1? 2 : 1);
}

int ValidMove(int r1, int c1, int r2, int c2, char (*grid)[5], int size){//add if c2>c1 or r2>r1
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
    int size = 5;
    char grid[5][5];
    UI(size, grid, player1, player2);
    GameLoop(5, grid);
    //system("cls");




    return 0;
}
