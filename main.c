#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "sudoku.h"
#include "ui.h"
#include "settings.h"

static int call=0;

int main()
{
    int choice;
    char enter;
    int** puzzle;
    int** userPuzzle;
    int** tempPuzzle;
    int** array;
    int size;
    int flag;

    if (call==0){
        while (flag=password()!=1){
            continue;
        }call = 1;
    }
    
    clear();               // clearing the screen
    home();                // displays the home page
    printf("Enter your choice: ");
    scanf("%d",&choice);                 // input the user's choice
    fflush(stdin);

    switch (choice)
    {
        case 1:
            size = sizeofhistory();          // checks weather the file continue.txt is empty or not

            if (size == 0) {                 // if file is empty show the message
                printf("\n\nYou Must start a new game to continue. \n\n");
                printf("Press Enter to continue... ");
                scanf("%c",&enter);
                fflush(stdin);
                main();
            }
            else {                  // if puzzle is present

                clear();

                puzzle = createcontinuePuzzle();        // used to import the puzzle from file and store it in variable
                userPuzzle = copyPuzzle(puzzle);        // creating a copy of file for future reference
                tempPuzzle = copyPuzzle(puzzle);        // creating a copy of file for future reference

                clear();

                printPuzzle(userPuzzle);                   //prints the puzzle
                userChoice(userPuzzle,tempPuzzle,puzzle);       // this funtioon is used to update the puzzle

                // free the memory allocated

                free(puzzle);
                free(userPuzzle);
                free(tempPuzzle);
            }

            break;
        case 2:
            clear();

            puzzle = createPuzzle();
            userPuzzle = copyPuzzle(puzzle);
            tempPuzzle = copyPuzzle(puzzle);

            clear();

            printPuzzle(userPuzzle);
            userChoice(userPuzzle,tempPuzzle,puzzle);

            // free the memory allocated

            free(puzzle);
            free(userPuzzle);
            free(tempPuzzle);
            break;
        case 3:

            clear();

            howtoplay();        // display the how to play screen
            printf("Press Enter to continue... ");
            scanf("%c",&enter);
            fflush(stdin);
            main();
            break;
        case 4:

            clear();

            rules();            // display the rules screen
            printf("Press Enter to continue... ");
            scanf("%c",&enter);
            fflush(stdin);
            main();
            break;
        case 5:

            settings();         // displays settings screen
            break;
        case 6:                 // exit the program
            printf("\n\nThank You for Playing... \n\n");
            printf("Press Enter to quit... \n\n");
            scanf("%c",&enter);
            exit(1);
            break;
        default:                // default case for wrong choice
            printf("\n\nEnter your choice correctly !! \n");
            printf("Press Enter to continue... \n\n");
            scanf("%c",&enter);
            fflush(stdin);
            main();
    }


    return 0;
}
