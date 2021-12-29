#include "GameLoop.h"

int mainMenu(){
    system("cls");
    setTextColor(green);
    printf("\n\t\t\t\tWelcome to\n\t\t\t      Dots and Boxes\n\n");
    setTextColor(reset);
   printf(" Enter 0 to start\n");
   printf(" Enter 1 to load a game\n");
   printf(" Enter 2 to view  Top 10 players\n");
   printf(" Enter 3 to exit\n\n ");
   int x;
   scanOfx:
   x = get_int();

   switch(x){

       case 0:system("cls");
              scanLevel:
              printf("\nEnter 0 for beginner\n");
              printf("\nEnter 1 for medium\n\nEnter 2 for expert\n\n");
              level = get_int();
              if(level == 0){
                size = 2 * easy + 1;
              }
              else if (level == 1){
                size = 2 * medium + 1;
              }
              else if (level == 2){
                 size = 2 * expert + 1;
              }
              system("cls");
              if(level!=0 && level!=1 && level!=2){
                  printf("invalid number.Please, enter another number\n");
                  goto scanLevel;
              }

              scanNOP:
              printf("\nEnter 0 for playing against the computer\n");
              printf("\nEnter 1 for 2 players\n\n");
              int numOfPlayers = get_int();
              system("cls");
              if(numOfPlayers==0 ){
                  mode = 0;
                  printf("Please, enter your name: ");
                  scanf(" %[^\n]s", player1.name);
                  player2 = computer;
                  system("cls");
              }
              if(numOfPlayers==1 ){
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
              if(numOfPlayers!=0 && numOfPlayers!=1){
                  printf("invalid number.Please, enter another number\n");
                  goto scanNOP;
              }

               break;

      /* case 1:*/

       case 2:
            {system("cls");
            sort(topPlayers);
            printf("rank name score\n");
            int z = 0;
            while(z < 10)
            {
                printf("%d.",z+1);
                printf("%s",topPlayers[z].name);
                printf("  (%d)\n",topPlayers[z].score);
                z++;
            }

            printf("\n\nEnter 0 to return to main menu\n");
            printf("Enter 1 to exit\n");
            while(1){
                int n = get_int();
                if(n == 0) mainMenu();
                else if(n == 1) exit(1);
                else printf("please enter 0 or 1\n");
            }

            break;}

       case 3: printf("bye");
               exit(1);


       default:
       printf("invalid number.Please enter another number\n");
       goto scanOfx;
   }
   return x;
}
