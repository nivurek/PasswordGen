#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>


#define MAX_WEBSITE_SIZE 50
#define MAX_PASSWORD_SIZE 50  

struct entry {
    char url[MAX_WEBSITE_SIZE];
    char password[MAX_PASSWORD_SIZE];
};
typedef struct entry entry_t;
/******************************************************************************
 * Function prototypes
******************************************************************************/
void printMenu(void);
void addPassword(void);
void deletePassword(void);
void editPassword(void);
void savePasswordList(void);
int readPasswordList(void);

/******************************************************************************
 * Main
******************************************************************************/
int main(void) {


    /* Initialise file reading/writing here */

    /* char dbFileName[] = "database.txt"; */
/******************************************************************************
 * User Interface/ Menu
******************************************************************************/
while(1){

        int c = 0;
        printMenu();
        printf("Please enter your choice (1-6): ");
        scanf("%d", &c);
        if ( c == 6){
            break;
        }

        switch(c){
            case 1: 
            addPassword();
            break;
            case 2:
            deletePassword();
            break;
            case 3:
            editPassword();
            break;
            case 4:
            savePasswordList();
            break;
            case 5:
            readPasswordList();
            break; 
            default:
            printf("Invalid choice."); /* error message when a foreign input is entered e.g. 8 */
            break;
        }
    }
    return 0;
}

void printMenu(void) {
    printf("\n\n"
     "1. Add a password\n"
     "2. Delete a password\n"
     "3. Edit a password\n"
     "4. Save the password list as an encrypted file\n"
     "5. Read a password list from an encrypted file\n"
     "6. Exit Password Manager\n");
}


void addPassword(void){
    
}

void deletePassword(void){
    
}

void editPassword(void){
    
}

void savePasswordList(void){
    
}

int readPasswordList(void){
    
}









