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
}player;
player player1={.score=0, .color=red, .moves=0},
player2={.score=0, .color=blue, .moves=0},
computer={"computer", 0, blue, 0};

//top 10 list
typedef struct{
    int rank;
    char name[20];
    int score;

}rank;
rank topPlayers[10] = {0};

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

#include "MainMenu.h"



int switchPlayer(int playerNo){

    return (playerNo==1? 2 : 1);
}

void sort(rank list[10]){
    rank temp;
    for(int i  = 0; i < 9; i++){
        for(int j = 0; j < 9 - i; j++){
            if(topPlayers[j].score < topPlayers[j+1].score){
                temp = topPlayers[j];
                topPlayers[j] = topPlayers[j+1];
                topPlayers[j+1] = temp;
            }
        }
    }

}
int get_int(){
    char c[256];
    scanf(" %[^\n]%*c", c);
    if(strlen(c) > 1)
        return -1;
    if(c[0] >= 48 && c[0] <= 57)
        return c[0] - 48;

    if(c[0] == 65){
        return 0xA;
    }

    return -1;
}

int main(){

    //mainMenu();
    system(" ");

    FILE *infile;
    // open file for reading
    infile = fopen ("scores.txt", "r");
    if (infile == NULL)
    {
        printf("file does not exist");
        infile = fopen("scores.txt", "w");
        close(infile);
        infile = fopen("scores.txt", "r");
    }

    // read struct to file
    int c = 0;
    while(!feof(infile)){
        fread(&topPlayers[c], sizeof(rank), 1, infile);
        c++;
    }
    // close file
    fclose (infile);

    int m = mainMenu();
    //size of grid according to level
    int n;
    if(level == 0) n = easy;
    else if(level == 1) n = medium;
    else if(level == 2) n = expert;
    //array to store main grid
    char grid[size][size];

    int player = GameLoop(n, size, mode, grid);
    //player 0 indicates a tie
    if(player == 1 || player == 0){
        int found = 0, i = 0;
        for(; i<10; i++){
            if(strcmp(player1.name, topPlayers[i].name) == 0){
                found = 1;
                break;
            }
        }
        if(found){
            if(player1.score > topPlayers[i].score)
                topPlayers[i].score = player1.score;
        }
        else if(player1.score > topPlayers[i-1].score){
            strcpy(topPlayers[i-1].name, player1.name);
            topPlayers[i-1].score = player1.score;
        }

    }

    //if player 2 is computer no need to add its score
    //if it is 2 players mode and a tie save player 2 score
    if((player == 2 || player == 0)&& mode == 1){
        int found = 0, i = 0;
        for(i; i<10; i++){
            if(strcmp(player2.name, topPlayers[i].name) == 0){
                found = 1;
                break;
            }
        }
        sort(topPlayers);
        if(found){
            if(player2.score > topPlayers[i].score)
                topPlayers[i].score = player2.score;
        }
        else if(player2.score > topPlayers[i-1].score){
            strcpy(topPlayers[i-1].name, player2.name);
            topPlayers[i-1].score = player2.score;
        }

    }


    FILE *users = fopen("scores.txt", "w");
    int counter = 0;
    while(counter < 10){
        fwrite(&topPlayers[counter++], sizeof(rank), 1, users);
    }
    fclose(users);

    printf("\n\nEnter 0 to play again\n");
    printf("Enter 1 to return to main menu\n");
    printf("Enter 2 to exit\n");

    while(1){
        char r = get_int();
        if(r == '0'){
            //reset score and move to zero if a new game is started
            player1.score = 0; player1.moves = 0;
            player2.score = 0; player2.moves = 0;
            GameLoop(n, size, mode, grid);
            printf("\n\nEnter 0 to play again\n");
            printf("Enter 1 to return to main menu\n");
            printf("Enter 2 to exit\n");
        }
        else if(r == '1') mainMenu(size, grid);
        else if(r == '2') exit(1);
        else printf("please enter 0 or 1\n");
    }

    return 0;
}
