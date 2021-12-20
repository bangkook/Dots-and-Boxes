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
    printf("0 1 2 3 4");

    printf("\n\t\t\t\t\t0\n1\n2\n3\n4");
    for (int i=0; i<size; i++){
            printf("\t\t\t\t\t ");
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
    int remLines = 12;
    int playerNo = 1;
    time_t starttime;
    starttime = time(NULL);

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
        //updateGrid(playerNo, 5, &grid, row1, col1, row2, col2, seconds, remLines, player1.moves, player1.score, player2.moves, player2.score);
        //playerNo = switchPlayer(playerNo);
        system("cls");
        time_t seconds;
        seconds = time(NULL);
        char l = playerNo==1?'A':'B';
        if(row1==row2) {
            grid[row1-48][col1+1-48] = l;
        }
        else if (col1==col2){
            grid[row1+1-48][col1-48] = l;
        }

        setTextColor(reset);
        for (int i=0; i<size; i++){
            setCursorPosition(40, 2+i);
            for (int j=0; j<size; j++){
                setTextColor(reset);
                if(grid[i][j] == 'A') {
                    setTextColor(player1.color);
                }
                else if(grid[i][j] == 'B'){
                    setTextColor(player2.color);
                }
                printf("%c ", grid[i][j]);

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

int ValidMove(int r1, int c1, int r2, int c2, char (*grid)[5], int size){
    //not vaild if same point
    if(r1==r2 && c1==c2){
        return 0;
    }
    if(r1==r2 && grid[r1][c1+1] != ' ')
        return 0;
    if(c1==c2 && grid[r1+1][c1] != ' ')
        return 0;
     if(r1<0 || r1>size || c1<0 || c1>size || r2<0 || r2>size || c2<0 || c2>size)
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
