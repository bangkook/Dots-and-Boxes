#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#define red FOREGROUND_RED
#define blue FOREGROUND_BLUE
#define green FOREGROUND_GREEN
#define yellow FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_INTENSITY
#define reset FOREGROUND_BLUE|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY

//structure to store player's information, name, score, color and number of moves
typedef struct{
    char name[20];
    int score;
    char* color;
    int moves;
}player;
player player1 = {.color = red},
player2 = {.color = blue};

//top 10 list
typedef struct{
    int rank;
    char name[20];
    int score;

}rank;
rank topPlayers[10] = {0};

int size, level, mode;
//include header file
#include "MainMenu.h"

//function to set cursor position at desired location on screen
void setCursorPosition(int x, int y);

//function to set color of printed text
void setTextColor(char* color);

//function to switch player after each turn
int switchPlayer(int playerNo);

//function to sort list using bubble sort
void sort(rank list[10]);

//function to read input integers and validate it
int get_int();

int main(){

    system(" ");

    FILE *infile;
    // open file for reading
    infile = fopen ("scores.txt", "r");
    if (infile == NULL)
    {
        infile = fopen("scores.txt", "w");
        close(infile);
        infile = fopen("scores.txt", "r");
    }

    // read file data to top players array
    int c = 0;
    while(!feof(infile)){
        fread(&topPlayers[c], sizeof(rank), 1, infile);
        c++;
    }
    // close file
    fclose (infile);

    //open file to print grid in it each turn for debugging
    FILE *fp;
    //open file for writing first to overwrite old data
    fp = fopen("grid.txt", "w");
    fclose(fp);

    int m;
    restart:
    m = mainMenu();

    int n, playerNo, remLines, player, starttime;

    if(m == 0){
        playAgain://if user chooses to play again reset everything

        player1.score = 0; player2.score = 0;
        player1.moves = 0; player2.moves = 0;

        //size of grid according to level
        if(level == 0) n = 2;
        else if(level == 1) n = 3;
        else if(level == 2) n = 5;

        size = 2 * n + 1;

        //array to store main grid
        char grid[size][size];

        //total lines that can be drawn
        remLines = 2 * n * (n + 1);

        //player1 starts the game
        playerNo = 1;

        //game starts at time 0
        starttime = 0;

        //helping grid to store lines and be printed to screen
        char grid2[size][size];

        char h = 205;//horizontal line
        char v = 186;//vertical line

        for (int i = 0; i < size; i++){

           for (int j = 0; j < size; j++){
            //initializing the grid with dots and spaces
            grid[i][j] = (i % 2 == 0 && j % 2 == 0)? 254 : ' ' ;

            if(i % 2 == 0 && j % 2 != 0 && grid[i][j] == ' ')
                    grid2[i][j] = h;//horizontal

            else if(i % 2 != 0 && j % 2 == 0 && grid[i][j] == ' ')
                grid2[i][j] = v;//vertical

            else
                grid2[i][j] = grid[i][j];

            }

        }

        int boxes[n*n][2];
        //initializing last column to zero to indicate box is not checked
        for(int i = 0; i < n*n; i++)
            boxes[i][1] = 0;

        player = GameLoop(starttime, n, boxes, size, mode, grid, grid2, playerNo, remLines);
    }

    else if(m == 1){//loaded game
        player = m - 4;
    }

    //sort array to compare to winner's score
    sort(topPlayers);
    //player 0 indicates a tie
    if(player == 1 || player == 0){
        //change name to lowercase
        for(int l = 0; l < strlen(player1.name); l++)
            player1.name[l] = tolower(player1.name[l]);

        int found = 0, i;
        for(i = 0; i < 10; i++){
            //check if user played before
            if(strcmp(player1.name, topPlayers[i].name) == 0){
                found = 1;
                break;
            }
        }
        //if found compare score and store the largest
        if(found){
            if(player1.score > topPlayers[i].score)
                topPlayers[i].score = player1.score;
        }
        //if not found compare with smallest score in list
        else if(player1.score > topPlayers[9].score){
            strcpy(topPlayers[9].name, player1.name);
            topPlayers[9].score = player1.score;
        }

    }

    //if player 2 is computer no need to add its score
    //if it is 2 players mode and a tie save player 2 score
    if((player == 2 || player == 0) && mode == 1){
        //changing name to lowercase
        for(int l = 0; l < strlen(player2.name); l++)
            player2.name[l] = tolower(player2.name[l]);

        int found = 0, i;

        for(i = 0; i < 10; i++){
            if(strcmp(player2.name, topPlayers[i].name) == 0){
                found = 1;
                break;
            }
        }

        if(found){
            if(player2.score > topPlayers[i].score)
                topPlayers[i].score = player2.score;
        }
        else if(player2.score > topPlayers[9].score){
            strcpy(topPlayers[9].name, player2.name);
            topPlayers[9].score = player2.score;
        }

    }

    //open file to write scores
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
        if(r == 0) goto playAgain;
        else if(r == 1) goto restart;
        else if(r == 2) exit(1);
        else printf("please enter 0 or 1 or 2\n");

    }

    return 0;
}

void setCursorPosition(int x, int y){
    COORD pos = {x, y};
    HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hstdout, pos);
}

void setTextColor(char* color){
    HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hstdout, color);
}

void sort(rank list[10]){
    //bubble sort
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

    if(strlen(c) > 1)//if user enters more than one digit
        return -1;

    if(c[0] >= 48 && c[0] <= 57)//return char value to its correct integer value
        return c[0] - 48;

    if(c[0] == 65){//10 in hexadecimal
        return 0xA;
    }

    return -1;
}

int switchPlayer(int playerNo){

    return (playerNo == 1 ? 2 : 1);
}


