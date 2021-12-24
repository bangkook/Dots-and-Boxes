#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <time.h>
#define red FOREGROUND_RED
#define blue FOREGROUND_BLUE
#define green FOREGROUND_GREEN
#define reset FOREGROUND_BLUE|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY
#define easy 2
#define medium 3
#define expert 5

typedef struct{
    char name[20];
    int score;
    char* color;
    int moves;
    char lastmove[2];
}player;
player player1={.score=0, .color=red, .moves=0},
player2={.score=0, .color=blue, .moves=0},
computer={"computer", 0, blue, 0};

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

#include "GameLoop.h"
#include "MainMenu.h"



int switchPlayer(int playerNo){

    return (playerNo==1? 2 : 1);
}



int main(){


    mainMenu();
    system(" ");
    //size of grid
    int n;
    if(level==0) n = easy;
    else if(level==1) n = medium;
    else if(level==2) n = expert;


    char grid[size][size];

    GameLoop(n, size, mode, grid);
    //system("cls");




    return 0;
}
