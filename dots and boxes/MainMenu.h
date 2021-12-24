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
