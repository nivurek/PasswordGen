#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>


#define MAX_WEBSITE_SIZE 50
#define MAX_PASSWORD_SIZE 50  
#define MAX_ARRAY_SIZE 50

struct entry {
    char url[MAX_WEBSITE_SIZE];
    char password[MAX_PASSWORD_SIZE];
};
typedef struct entry entry_t;
/******************************************************************************
 * Function prototypes
******************************************************************************/
void printMenu(void);
void addPassword(entry_t password_list[], unsigned int* password_list_size);
void deletePassword(void);
void editPassword(void);
void displayPasswordList(void);
void savePasswordList(void);
int readPasswordList(void);
// char* scanString(unsigned int size, char prompt[]);


/******************************************************************************
 * Main
******************************************************************************/
int main(void) {
    /* Initialise file reading/writing here */

    entry_t password_list[MAX_ARRAY_SIZE];
    unsigned int password_list_size = 0;

    /* char dbFileName[] = "database.txt"; */
/******************************************************************************
 * User Interface/ Menu
******************************************************************************/
    while(1){
        int c;
        printMenu();
        char line[100];
        fgets(line ,sizeof(line), stdin);
        if(sscanf(line,"%d",&c) != 1);

        /* printf("Please enter your choice (1-6): ");
        scanf("%d", &c); */


        if (c == 7){
            break;
        }

        switch(c){
            case 1: 
            addPassword(password_list, &password_list_size);
            break;
            case 2:
            deletePassword();
            break;
            case 3:
            editPassword();
            break;
            case 4:
            displayPasswordList();
            break;
            case 5:
            savePasswordList();
            break; 
            case 6:
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
    printf("\n"
     "1. Add a password\n"
     "2. Delete a password\n"
     "3. Edit a password\n"
     "4. Display password list\n"
     "5. Save the password list as an encrypted file\n"
     "6. Read a password list from an encrypted file\n"
     "7. Exit Password Manager\n");
}


void addPassword(entry_t password_list[], unsigned int* password_list_size) {
    if(*password_list_size >= MAX_ARRAY_SIZE) {
        printf("List is full");
        return;
    }

    entry_t* password_p  = &password_list[*password_list_size];



}

void deletePassword(void){
    
}

void editPassword(void){
    
}

void savePasswordList(void){
    
}

int readPasswordList(void){
    
}

void displayPasswordList(void) {
    
}



char* scanString(unsigned int size, char prompt[]) {
    char result[size];
    printf("%s", prompt);
    fgets(result, sizeof(result), stdin);
    return result;
}







