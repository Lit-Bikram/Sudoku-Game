#ifndef  UI_H_
#define  UI_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct User
{
    char name[20];
    int password;
};


void clear();

// password() is used to for all necessary inputs and ui of login page
int password()
{                       


    char name1[20] = "Abir\0";
    int id1 = 2001;
    char name2[20] = "Debanjan\0";
    int id2 = 2031;
    char name3[20] = "Abhik\0";
    int id3 = 2034;
    char name4[20] = "Bikram\0";
    int id4 = 2035;



    char c,enter;
    int i;
    struct User user;

    clear();

    printf("\t\t**  LOGIN PAGE  **\n\n");
    printf("\nUser Name : ");
    scanf("%s", &user.name);
    printf("\nPassword : ");
    scanf("%d",&user.password);
    fflush(stdin);

    // checking for username and password
    if (strcmp(user.name,name1)==0 && user.password==id1)
    {
        printf("\n\nWelcome.....\n");
        printf("\n\nPress Enter to continue... ");
        scanf("%c",&enter);
        fflush(stdin);
        return 1;
    }else if(strcmp(user.name,name2)==0 && user.password==id2)
    {
        printf("\n\nWelcome.....\n");
        printf("\n\nPress Enter to continue... ");
        scanf("%c",&enter);
        fflush(stdin);
        return 1;
    }else if(strcmp(user.name,name3)==0 && user.password==id3)
    {
        printf("\n\nWelcome.....\n");
        printf("\n\nPress Enter to continue... ");
        scanf("%c",&enter);
        fflush(stdin);
        return 1;
    }else if(strcmp(user.name,name4)==0 && user.password==id4)
    {
        printf("\n\nWelcome.....\n");
        printf("\n\nPress Enter to continue... ");
        scanf("%c",&enter);
        fflush(stdin);
        return 1;
    }else{                                                //if the username and password not matching to what is stored
        while(1){
        	printf("\n\nWrong Username or Password...\n");
            printf("\nPress Enter to try again or press \"q\" to quit.\n");
            c = getchar();
            if((c == 'q') || (c == 'Q')){
                printf("\n\n");
                exit(0);
            }else{
                return 0;
            }
        }

    }
}


// this unction is used to print empty lines to clear up the interface
void clear()
{
    int i=0;
    while (i<45){
        printf("\n");
        i++;
    }
}


// this function is used to display the level selection screen
int level(int nolvl)
{
    int cas,i,lvlc;
    char enter;
    cas = nolvl/215;
    
    
    if (cas==0){
        clear();
        printf("\n\nFirst create a level to continue.\n\n");
        printf("Press Enter to continue... ");
        scanf("%c",&enter);
        return 0;
    }

    while (1){
        i=1;
        clear();

        printf("\t\t**  SELECT LEVEL  **\n\n");

        while (i <= cas){
            printf("%d. Level %d\n",i,i);
            i++;
        }
        i--;

        printf("\n\nSelect level to continue...\n");
	    scanf("%d",&lvlc);
        fflush(stdin);

        if (lvlc > i){
            printf("\n\nEnter your choice correctly.....\n\n");
            printf("Press Enter to continue... ");
            scanf("%c",&enter);
            fflush(stdin);
            continue;
        }else if (lvlc < 1){
            printf("\n\nEnter your choice correctly.....\n\n");
            printf("Press Enter to continue... ");
            scanf("%c",&enter);
            fflush(stdin);
            continue;
        }else{
            break;
        }
    }
    return lvlc;
}

// this function is used to print the home page 
void home()
{
    printf("\t\t\t**  SUDOKU GAME  **\n\n\n");
    printf("1. Continue \n");
    printf("2. New Game \n");
    printf("3. How To Play\n");
    printf("4. Rules \n");
    printf("5. Settings\n");
    printf("6. Exit \n\n");

}

// this function is used to print the how to play screen
void howtoplay()
{
    printf("\t\t**  HOW TO PLAY  **\n\n");
    printf("\n\n1. Press Enter to start the game \n");
    printf("2. Select the level \n"); // use only if required
    printf("3. Select |X| and |Y| cordinate to enter the value at that position \n");
    printf("4. Check if your given answer is write or not \n");
    printf("5. Play as many times you want \n\n");
}

// this function is used to printthe rules page
void rules()
{
    printf("\t\t**  RULES  **\n\n");
    printf("\n\n1. Sudoku Rule 1: Use Numbers 1-9 \n");
    printf("2. Sudoku Rule 2: Don't Repeat Any Numbers \n");
    printf("3. Sudoku Rule 3: Don't Guess \n");
    printf("4. Sudoku Rule 4: Use Process of Elimination \n\n");
}

#endif
