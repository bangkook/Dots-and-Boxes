#include "GameLoop.h"

int mainMenu(){

    menu:
    system("cls");
    setTextColor(green);
    printf("\n\t\t\t\tWelcome to\n\t\t\t      Dots and Boxes\n\n");
    setTextColor(yellow);
    printf("\t0.start new game\n");
    printf("\n\t1.load a previous game\n");
    printf("\n\t2.view Top 10 players\n");
    printf("\n\t3.exit\n\n ");
    printf("\n\tEnter number: ");
    int x;
    scanOfx:
    x = get_int();

    switch(x){

        case 0:
            system("cls");
            scanLevel:
            //scan game level
            printf("Difficulty level\n");
            printf("\n0.beginner\n");
            printf("\n1.medium\n\n2.expert\n\n");
            level = get_int();

            system("cls");
            if(level != 0 && level != 1 && level != 2){
                printf("invalid number.Please, enter another number\n");
                goto scanLevel;
            }

            scanNOP:
            //scan game mode(number of players)
            printf("Game modes\n");
            printf("\n0.one player (vs computer)\n");
            printf("\n1.two players\n\n");
            int numOfPlayers = get_int();

            system("cls");
            //reading player's name
            if(numOfPlayers == 0){
                mode = 0;
                printf("Please, enter your name: ");
                scanf(" %[^\n]s", player1.name);
                strcpy(player2.name, "computer");
                system("cls");
            }

            if(numOfPlayers == 1){
                mode = 1;
                setTextColor(red);
                printf("Please, enter player1 first name: ");
                scanf(" %[^\n]s", player1.name);
                setTextColor(blue);
                printf("\nPlease, enter player2 first name: ");
                scanf(" %[^\n]s", player2.name);
                setTextColor(reset);
                system("cls");
            }
            //if invalid input, ask for another one
            if(numOfPlayers != 0 && numOfPlayers != 1){
                printf("invalid number.Please, enter another number\n");
                goto scanNOP;
            }

            break;

        case 1://loading a previous game

            system("cls");
            printf("Enter file number (1 or 2 or 3): ");
            int num = get_int();//number of loaded file

            if(num == 1 || num == 2 || num == 3){
                char loaded_file[5];
                //name of file
                sprintf(loaded_file, "%d.bin", num);

                FILE *loadedGame;
                //open file for reading
                loadedGame = fopen(loaded_file, "rb");
                if(loadedGame == NULL){
                        printf("File does not exist\n\n");
                        goto input;
                }
                else
                {
                    int n, remLines, playerNo;
                    int loaded_time;

                    fread(&loaded_time, sizeof(int), 1, loadedGame);
                    fread(&size, sizeof(int), 1, loadedGame);
                    fread(&n, sizeof(int), 1, loadedGame);
                    fread(&mode, sizeof(int), 1, loadedGame);
                    fread(&player1, sizeof(player), 1, loadedGame);
                    fread(&player2, sizeof(player), 1, loadedGame);
                    fread(&remLines, sizeof(int), 1, loadedGame);
                    fread(&playerNo, sizeof(int), 1, loadedGame);

                    char grid[size][size];
                    char grid2[size][size];

                    fread(grid, sizeof(char), size * size, loadedGame);
                    fread(grid2, sizeof(char), size * size, loadedGame);

                    int boxes[n*n][2];
                    fread(boxes, sizeof(int), n * n * 2, loadedGame);

                    fclose(loadedGame);

                    int player = GameLoop(loaded_time, n, boxes, size, mode, grid, grid2, playerNo, remLines);

                    return (4 + player);

                }

            }
            else{
                //if user enters invalid number, ask to return or exit
                printf("\nNo such file\n");
                input:
                printf("1.main menu\n2.exit\n");
                num = get_int();
                if(num == 1) goto menu;
                else if(num == 2) exit(1);
                else printf("INVALID INPUT\n");
                goto input;
            }

            break;

        case 2://top 10 list
            system("cls");
            //sort list according to score
            sort(topPlayers);
            printf("rank name score\n");

            int z = 0;
            while(z < 10)
            {
                printf("%d.", z+1);
                printf("%s", topPlayers[z].name);
                printf("  (%d)\n", topPlayers[z].score);
                z++;
            }

            printf("\n\n0.return to main menu\n");
            printf("1.exit\n");
            int n;
            scanOfn:
            n = get_int();
            if(n == 0) goto menu;
            else if(n == 1) exit(1);
            else printf("please enter 0 or 1\n");
            goto scanOfn;

            break;

        case 3: exit(1);
        //default action if user entered invalid number
        default:
        printf("invalid number.Please enter another number\n");
        goto scanOfx;
    }
    //return user's choice
    return x;
}
