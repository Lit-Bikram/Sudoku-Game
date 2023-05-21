#ifndef  SUDOKU_H_
#define  SUDOKU_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "ui.h"

int main();
void addautolevel();

// this function creates an empty puzzle with only 0's
int** createemptypuzzle()
{
    int** puzzle;
    int i,j;

    puzzle = (int**)malloc(sizeof(int*) * 9);

    for (i = 0; i < 9; i++){
        puzzle[i] = (int*)malloc(sizeof(int) * 9);
        for(j = 0; j < 9; j++){
            puzzle[i][j] = 0;
        }
    }

    return puzzle;
}

// this function is used to count the length of continue.txt
int sizeofhistory(){
    int len;
    FILE* fp = fopen("history.txt", "r");     //opens the file in read mode

    fseek(fp, 0, SEEK_END);
    len = ftell(fp);
    fclose(fp);                   //closes the file
    return len;                    //len returns the size
}

void storeinhistory(int** userPuzzle){               //stores the sudoku in the file for future access

    FILE *fp = fopen("history.txt", "w");             //opens the file in write mode

    if (fp == NULL) {                                 //checks if file is open or not
        printf("Error opening file!\n");
        exit(0);
    }
    
    // Write 2D array to file
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 8; j++) {
            fprintf(fp, "%d ", userPuzzle[i][j]);
            if (j==2 || j==5){
                fprintf(fp,"  ");
            }
        }
        fprintf(fp, "%d", userPuzzle[i][8]);
        fprintf(fp, "\n");
        if (i==2 || i==5){
                fprintf(fp,"\n");
            }
    }
    fprintf(fp,"\n\n");
    fclose(fp);                                //closes the file

}

// this function copies the data from continue.txt and stores un puzzle
int** createcontinuePuzzle()
{
    int i,j;
    int** puzzle;
    int arr[9][9];

    FILE *fptr=fopen("history.txt", "r");;           //opens the file in read mode

    if (fptr == NULL) {
		printf("The file is not opened. The program will now exit.");
		exit(0);
	}

    for (i=0;i<9;i++){
        for (j=0;j<9;j++){
            fscanf(fptr,"%d",&arr[i][j]);
        }
    }

    puzzle = (int**)malloc(sizeof(int*) * 9);

    for (i = 0; i < 9; i++){
        puzzle[i] = (int*)malloc(sizeof(int) * 9);
        for(j = 0; j < 9; j++){
            puzzle[i][j] = arr[i][j];
        }
    }

    // returns the puzzle
    return puzzle;
}

 // this function is used to define the 9x9 sudoku puzzzle
int** createPuzzle()
{
    int i, j,difficulty,enter,lvlc,val,nolvl;
    int** puzzle;
    int arr[9][9];
    int choice;

    FILE *fptr;

    printf("\t\t\t**  SELECT DIFFICULTY  **\n\n\n");
    printf("1. Easy \n");
    printf("2. Medium \n");
    printf("3. Hard \n\n");
    printf("Enter number for difficulty or Press any key to return to home \n");

    scanf("%d", &difficulty);   // user provides the level as input
    fflush(stdin);


    // used for defining file pointer
    if (difficulty==1){
        fptr = fopen("Easy.txt", "r");
        fseek(fptr, 0, SEEK_END);
        nolvl = ftell(fptr);
        lvlc = level(nolvl);
    }else if (difficulty==2){
        fptr = fopen("Medium.txt", "r");
        fseek(fptr, 0, SEEK_END);
        nolvl = ftell(fptr);
        lvlc = level(nolvl);
    }else if (difficulty==3){
        fptr = fopen("Hard.txt", "r");
        fseek(fptr, 0, SEEK_END);
        nolvl = ftell(fptr);
        lvlc = level(nolvl);
    }else{
        printf("\n\nPress Enter to continue... ");
        scanf("%c",&enter);
        fflush(stdin);
        main(); 
    }

    if (lvlc==0){
        printf("\n\nCreate a level to continue\n");
        printf("\n\nWant to add new level ?\n\n");
        printf("Press 1 to continue or eny key to return to home page..\n");
        scanf("%d",&choice);
        if (choice==1){
            addautolevel();
        }else{
            main();
        }
        lvlc=1;
    }

    if (fptr == NULL) {
		printf("The file is not opened. The program will now exit.");
		exit(0);
	}

    val=(lvlc-1)*215;           // used to find the position to import puzzle
    fseek(fptr, val, SEEK_SET); // used to seek the file pointer to desired position

    // reading puzzle from the file
    for (i=0;i<9;i++){
        for (j=0;j<9;j++){
            fscanf(fptr,"%d",&arr[i][j]);
        }
    }

    puzzle = (int**)malloc(sizeof(int*) * 9);

    for (i = 0; i < 9; i++){
        puzzle[i] = (int*)malloc(sizeof(int) * 9);
        for(j = 0; j < 9; j++){
            puzzle[i][j] = arr[i][j];
        }
    }

    // returns the new puzzle
    return puzzle;
}

//prints the sudoku puzzle and the co-ordinates to the screen
void printPuzzle(int** puzzle)
{
    int i, j, a;

    printf("\n");
    printf(" 0 | 1  2  3 | 4  5  6 | 7  8  9 | X\n");
    printf(" ---------------------------------\n");
    for (i = 0, a = 1; i < 9; i++, a++){
        for(j = 0; j < 9; j++){
            if (j == 0)
                printf(" %d |", a);
            else if ((j) % 3 == 0)
                printf("|");
            printf(" %d ", puzzle[i][j]);
            if (j == 8)
                printf("|");
        }
        printf("\n");
        if ((i + 1) % 3 == 0)
            printf(" ---------------------------------\n");
    }
    printf(" Y\n");
}

//checks if the cpuzzle has any empty places or not
bool checkAvailable(int** puzzle, int* row, int* column)
{
    int i, j;

    for (i = 0; i < 9; i++){
        for(j = 0; j < 9; j++){
            if (puzzle[i][j] == 0){ // checks if the coordinates has 0 in the position or not
                *row = i;
                *column  = j;
                return true;
            }
        }
    }

    return false;
}

// used to check weather value is present in row , column , or 3x3 matrix
bool checkBox(int** puzzle, int row, int column, int val)
{
    int i, j;
    int squareRow, squareColumn;

    //CHECK VERTICAL
    for(i = 0; i < 9; i++){
        if (puzzle[i][column] == val)
            return false;
    }

    //CHECK HORIZONTAL
    for(j = 0; j < 9; j++){
        if (puzzle[row][j] == val)
            return false;
    }

    //CHECK SQUARE
    squareRow = row - row % 3;
    squareColumn = column - column % 3;

    for(i = 0; i < 3; i++){
        for(j = 0; j < 3; j++){
            if(puzzle[squareRow + i][squareColumn + j] == val)
                return false;
        }
    }

    return true;
}

//this function solves the puzzle and checks the value if not matched
bool solvePuzzle(int** puzzle)
{
    int i, j, val;

    // checks weather the position is vacant or not
    if(!checkAvailable(puzzle, &i, &j))
        return true;
    
    // assigning values to the position
    for(val = 1; val < 10; val++){
        // checking if the value is alredy present or not
        if(checkBox(puzzle, i, j, val)){
            puzzle[i][j] = val;
            if(solvePuzzle(puzzle))
                return true;            //solution available
            else
                puzzle[i][j] = 0;
        }
    }
    return false;                       //puzzle not solved
}

//copies values from existing puzzle to new puzzle
int** copyPuzzle(int** puzzle){
    int i, j;
    int** newPuzzle;

    newPuzzle = (int**)malloc(sizeof(int*) * 9);

    for (i = 0; i < 9; i++){
        newPuzzle[i] = (int*)malloc(sizeof(int) * 9);
        for(j = 0; j < 9; j++){
            newPuzzle[i][j] = puzzle[i][j];
        }
    }
    return newPuzzle;
}


// function to enter values to the puzzle
void userChoice(int** userPuzzle, int** tempPuzzle, int** puzzle)
{
    int i, j, enter;
    int positionX, positionY, userVal;
    char c;

    while(1){
        // checks completion of the puzzle
        if(!checkAvailable(userPuzzle, &i, &j)){
            printf("\nGood Job You Solved the Puzzle!!!\n");
            return;
        }

        while(1){
            printf("\nPress Enter to continue or Press \"q\" to return to HOME page.\n");           //prompt after each successful entry
            c = getchar();
            if((c == 'q') || (c == 'Q')){
                getchar();
                main();
                return;
            }
            else if((c != '\n') && (c != 'q'))
                getchar();
            else
                break;
        }

        // takes the user desired co-ordinate as input
        printf("\nPlease Enter Coordinate for the square you want to insert the value to in the following format \"X Y\":\n");
        scanf("%d %d",&positionX, &positionY);

        while(1){
            // checking range of coordinate
            if ((positionX > 9) || (positionX < 1) || (positionY > 9) || (positionY < 1) || (userPuzzle[positionY - 1][positionX - 1] != 0))
            {
                printf("\nYou can't insert value to this Coordinate, please pick a new Coordinate\n");
                scanf("%d %d",&positionX, &positionY);
            }
            else {
                positionX -= 1;
                positionY -= 1;
                break;
            }
        }


        printf("\nPlease insert value from 1 to 9\n");
        scanf("%d", &userVal);          // takes the user desired value for the already provided co-ordinate

        while(1){
            if((userVal > 9) || (userVal < 1)){
                printf("\nPlease insert valid value:\n");
                scanf("%d", &userVal);
            }
            else break;
        }
        // returns true if value is not present in the puzzle
        if (checkBox(userPuzzle, positionY, positionX, userVal)){
            userPuzzle[positionY][positionX] = userVal;// storing val to user puzzle
        }
        else{
            printf("\nIncorrect value for the X = %d Y = %d coordinate, please try again\n",positionX + 1, positionY + 1);     //display the value is already present
            printf("\n\nPress Enter to continue... ");
            scanf("%c",&enter);
        }
        // changes value of userval to temp puzzle
        for (i = 0; i < 9; i++){
            for(j = 0; j < 9; j++){
                tempPuzzle[i][j] = userPuzzle[i][j];
            }
        }
        // checks weather the value is correct or not
        if(!solvePuzzle(tempPuzzle)){
            //checks temp puzzle and changes the value of temppuzzle
            printf("\nIncorrect value for the X = %d Y = %d coordinate, please try again\n",positionX + 1, positionY + 1);
            userPuzzle[positionY][positionX] = 0;
            printf("\n\nPress Enter to continue... ");
            scanf("%c",&enter);
        }

        getchar();
        clear();
        printPuzzle(userPuzzle);
        if (puzzle!=userPuzzle)
            {
                storeinhistory(userPuzzle);
            }
    }
    return;
}

#endif
