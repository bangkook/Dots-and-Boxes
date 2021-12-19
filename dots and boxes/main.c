#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include "Grid.h"
#include "GameLoop.h"
#define red FOREGROUND_RED
#define blue FOREGROUND_BLUE
#define green FOREGROUND_GREEN

int switchPlayer(int playerNo){
    if(playerNo == 1) playerNo = 2;
    else playerNo = 1;
    return playerNo;
}


int main(){

    int len = 2;
    UI(len, len);

    //system("cls");
    GameLoop(12);


    return 0;
}
