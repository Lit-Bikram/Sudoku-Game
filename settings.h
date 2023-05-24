#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "ui.h"

void settings();

// clears the contents of the history file
void clearhistory()
{
    char enter;
    FILE* fptr=fopen("history.txt","w");
    fclose(fptr);
    printf("\n\nProgress deleted...\n ");
    printf("\n\nPress Enter to continue... ");
    scanf("%c",&enter);
}

//add level automatically to the file entered by the user
void addautolevel()
{
    // this function initializes random number with current time every sec
    srand(time(NULL));

    int** sudoku;
    int** tempsudoku;
    char enter;
    int choice;
    int cor_x,cor_y;
    int val,a,flag=0,b,i,j;
    int difficulty;
    
    sudoku = createemptypuzzle();   // this creates apuzzle with only 0's

    FILE *fptr;

    clear();

    printf("\t\t\t**  SELECT DIFFICULTY  **\n\n\n");
    printf("1. Easy \n");
    printf("2. Medium \n");
    printf("3. Hard \n\n");
    printf("Press any key to return to home \n");

    scanf("%d", &difficulty);   // user provides the level as input
    fflush(stdin);

    switch (difficulty)
    {
    case 1:
        a = 41 ; // number of empty places to be made 
        b = 5 ; // number of random places in the puzzle
        fptr = fopen("easy.txt","a");
        break;
    case 2:
        fptr = fopen("medium.txt","a");
        a = 48 ; // number of empty places to be made
        b = 8 ; // number of random places in the puzzle
        break;
    case 3:
        fptr = fopen("hard.txt","a");
        a = 56 ; // number of empty places to be made
        b = 11 ; // number of random places in the puzzle
        break;
    default:
        printf("Press Enter to continue... ");
        scanf("%c",&enter);
        fflush(stdin);
        main();
        break;
    }
    
    
    while (flag < b)
    {
        // generates random number with rand()
        cor_x = (rand() % 9) + 1 ;
        cor_y = (rand() % 9) + 1 ;

        val = (rand() % 9) + 1 ;
        // filling the puzzle with random number
        if (checkBox(sudoku,cor_y-1,cor_x-1,val)){
            sudoku[cor_y-1][cor_x-1] = val ;
        }else{
            continue;
        }

        flag++;
    }
    


    // solves the sudoku
    solvePuzzle(sudoku);

    flag=0;
    while(flag < a){

        // generating random coordinates for removal of digit and changing to 0
        cor_x = (rand() % 9) + 1 ;
        cor_y = (rand() % 9) + 1 ;

        if (sudoku[cor_y-1][cor_x-1]!=0){
            sudoku[cor_y-1][cor_x-1] = 0 ;
        }else{
            continue;
        }

        flag++;
    }
    
    tempsudoku = copyPuzzle(sudoku);
    
    clear();
    
    if (solvePuzzle(tempsudoku)){// if puzzle is solvable
        printf("\n\nPuzzle Generated is : \n\n");
        printPuzzle(sudoku);
    }else{
        printf("\n\nSome unknown error occoured !!\n\n");
        printf("Press Enter to continue... ");
        scanf("%c",&enter);
        fflush(stdin);
        return;
    }

    
    printf("\n\nWant to add this puzzle to the file ?\n\n");
    printf("\nType '1' to make changes or anything to cancel and return to settings page \n\n");
    scanf("%d",&choice);
    fflush(stdin);
    
    // adding puzzle to file
    if (choice == 1){

        if (fptr == NULL) {                                 //checks if file is open or not
            printf("Error opening file!\n");
            exit(0);
        }
        for (i = 0; i < 9; i++) {
            for (j = 0; j < 8; j++) {
                fprintf(fptr, "%d ", sudoku[i][j]);
                if (j==2 || j==5){
                    fprintf(fptr,"  ");
                }
            }
            fprintf(fptr, "%d", sudoku[i][8]);
            fprintf(fptr, "\n");
            if (i==2 || i==5){
                fprintf(fptr,"\n");
            }
        }
        fprintf(fptr,"\n\n");
        fclose(fptr);

        printf("\n\nPuzzle added successfully...");
        printf("\n\nPress Enter to continue... ");
        scanf("%c",&enter);
        fflush(stdin);
        return;
    }else {
        printf("\n\nProcess Terminated ");
        printf("\n\nPress Enter to continue... ");
        scanf("%c",&enter);
        fflush(stdin);
        return;
    }
    fclose(fptr);
    return;
}

// clears the content of file and resets all 3 file
void cleardata(){
    int ch, temp;
    char enter;

    FILE* fptr1;
	FILE* fptr2;

    fptr1 = fopen("easy.txt", "r");
    fptr2 = fopen("replica1.txt", "w");
    temp = 1;

    while (temp != 607){
		ch = fgetc(fptr1);
        fputc(ch, fptr2);
		temp++;
    }
    fclose(fptr1);
    fclose(fptr2);

    remove("easy.txt");
    rename("replica1.txt", "easy.txt");

    fptr1 = fopen("medium.txt", "r");
    fptr2 = fopen("replica2.txt", "w");
    temp = 1;

    while (temp != 607){
		ch = fgetc(fptr1);
        fputc(ch, fptr2);
		temp++;
    }
    fclose(fptr1);
    fclose(fptr2);

    remove("medium.txt");
    rename("replica2.txt", "medium.txt");

    free(fptr1);
    free(fptr2);

    fptr1 = fopen("hard.txt", "r");
    fptr2 = fopen("replica3.txt", "w");
    temp = 1;

    while (temp != 607){
		ch = fgetc(fptr1);
        fputc(ch, fptr2);
		temp++;
    }
    fclose(fptr1);
    fclose(fptr2);

    remove("hard.txt");
    rename("replica3.txt", "hard.txt");

    free(fptr1);
    free(fptr2);

    printf("\n\nGame Reset Successful...\n ");
    printf("\n\nPress Enter to continue... ");
    scanf("%c",&enter);
}

//  reference matrix for adding new level
void reference()
{
    int x=0,i,j,a;
    clear();
    printf("\n\nThe matrix should be of this format \n\n");
    printf("\n");
    printf(" 0 | 1  2  3 | 4  5  6 | 7  8  9 | X\n");
    printf(" ---------------------------------\n");
    for (i = 0, a = 1; i < 9; i++, a++){
        for(j = 0; j < 9; j++){
            if (j == 0)
                printf(" %d |", a);
            else if ((j) % 3 == 0)
                printf("|");
            printf(" %d ", x);
            if (j == 8)
                printf("|");
        }
        printf("\n");
        if ((i + 1) % 3 == 0)
            printf(" ---------------------------------\n");
    }
    printf(" Y\n");
}

// this dunction is used to add new level to the file
void addlevel()
{
    int difficulty;
    int i,j,a;
    char enter;
    int** array;
    int arr[9][9];
    int val;
    int** settemppuzzle;


    FILE* fptr;
    clear();
    printf("\t\t\t**  SELECT DIFFICULTY  **\n\n\n");
    printf("1. Easy \n");
    printf("2. Medium \n");
    printf("3. Hard \n\n");
    printf("Press any key to return to settings \n");
    
    scanf("%d", &difficulty);
    fflush(stdin);

    switch (difficulty)
    {
        case 1:
            fptr=fopen("easy.txt","a");
            break;
        case 2:
            fptr=fopen("medium.txt","a");
            break;
        case 3:
            fptr=fopen("hard.txt","a");
            break;
        default :
            printf("Press Enter to continue... ");
            scanf("%c",&enter);
            fflush(stdin);
            settings();
    }
    reference();
    printf("Press Enter to continue... \n");
    scanf("%c",&enter);
    fflush(stdin);

    for (i=0; i < 9 ; i++){
        for ( j = 0 ; j < 9 ; j++){
            printf("\n\nEnter a number or '0' for empty place \n");
            printf("Enter the value of %d and %d in the format (X Y) :\n",j+1,i+1);
            scanf("%d",&val);
            fflush(stdin);
            arr[i][j]=val;
        }
    }

    array = (int**)malloc(sizeof(int*) * 9);

    for (i = 0; i < 9; i++){
        array[i] = (int*)malloc(sizeof(int) * 9);
        for(j = 0; j < 9; j++){
            array[i][j] = arr[i][j];
        }
    }
    printf("\n\nThe matrix you entered is : \n\n");
    printf("\n");
    printf(" 0 | 1  2  3 | 4  5  6 | 7  8  9 | X\n");
    printf(" ---------------------------------\n");
    for (i = 0, a = 1; i < 9; i++, a++){
        for(j = 0; j < 9; j++){
            if (j == 0)
                printf(" %d |", a);
            else if ((j) % 3 == 0)
                printf("|");
            printf(" %d ", array[i][j]);
            if (j == 8)
                printf("|");
        }
        printf("\n");
        if ((i + 1) % 3 == 0)
            printf(" ---------------------------------\n");
    }
    printf(" Y\n");

    settemppuzzle = copyPuzzle(array);

    if (solvePuzzle(settemppuzzle)){
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 8; j++){
                fprintf(fptr, "%d ", array[i][j]);
                if (j==2 || j==5){
                   fprintf(fptr,"  ");
                }
            }
            fprintf(fptr, "%d", array[i][8]);
            fprintf(fptr, "\n");
            if (i==2 || i==5){
                    fprintf(fptr,"\n");
                }
        }
        fprintf(fptr,"\n\n");
        printf("\n\nValues Entered into the file successfully.. ");
    }else{
        printf("\n\nEnter a valid puzzle....\n");
    }
    fclose(fptr);
    printf("\n\nPress Enter to continue... \n\n");
    scanf("%c",&enter);
    fflush(stdin);
}

// display settings sceen
void settings()
{
    char enter;
    int schoice;

    clear();
    printf("\t\t**  SETTINGS  **\n\n");
    printf("\n\n1. Add a Level by auto input \n");
    printf("2. Add a Level by manual input \n");
    printf("3. Reset Progress \n");
    printf("4. Reset Game Data \n");
    printf("5. Return Home \n\n");
    printf("Enter your choice..\n");
    scanf("%d",&schoice);
    fflush(stdin);
    
    switch (schoice)                   //user choice
    {
    case 1:
        addautolevel();
        settings();
        break;
    case 2:
        addlevel();
        settings();
        break;
    case 3:
        clearhistory();
        settings();
        break;
    case 4:
        cleardata();
        settings();
        break;
    case 5:
        main();
        break;
    default:
        printf("\n\nEnter your choice correctly !! \n");
        printf("Press Enter to continue... \n\n");
        scanf("%c",&enter);
        fflush(stdin);
        settings();
        break;
    }


}
