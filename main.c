#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "algorithms.h"
#include "cryptography.h"


#define MAX_WEBSITE_SIZE 100
#define MAX_USERNAME_SIZE 50
#define MAX_PASSWORD_SIZE 50  
#define MAX_ARRAY_SIZE 50
#define DATABASE_FILE_NAME "passwords.txt"
#define KEY_FILE_NAME "key.txt"

/******************************************************************************
 * Function prototypes
******************************************************************************/
void printMainMenu(void);
void printLoginMenu(void);
void createKey(void);
void loginKey(void);
void addEntry(LinkedList* account_list);
void deletePassword(LinkedList* account_list);
void editPassword(LinkedList* account_list);
void displayPasswordList(LinkedList account_list);
void savePasswordList(LinkedList account_list, char* key);
int readPasswordList(LinkedList* account_list, char* key);
char* scanString(unsigned int size, char prompt[]);


/******************************************************************************
 * Main
******************************************************************************/
int main(void) {

    LinkedList account_list;
    account_list.size = 0;
    account_list.head = NULL;
    char* key = "HelloWorld";
    /* char dbFileName[] = "database.txt"; */

    
/******************************************************************************
 * User Interface/ Menu 
******************************************************************************/
    printf("\nWelcome to Password Manager\n");

    int menuInput;
    int loginInput;
    char line[100];

    while(1) {
        printLoginMenu();
        printf("\nPlease enter your choice (1-3): ");
        fgets(line ,sizeof(line), stdin);
        
        if(sscanf(line,"%d",&loginInput) != 1) {
            printf("Invalid Choice.\n");
            continue;
        }
        if (loginInput == 3) {
            printf("Exited program.");
            break;
        }

        switch(loginInput) {
            case 1:
            /* If key.txt contains data, calls the function insertKey()  */
                readPasswordList(&account_list, key);

                while(1){
                    printMainMenu();
                    printf("\nPlease enter your choice (1-5): ");
                    fgets(line, sizeof(line), stdin);
                    if(sscanf(line,"%d", &menuInput) != 1) {
                        printf("Invalid Choice.\n");
                        continue;
                    }
                
                    if (menuInput == 5){
                        break;
                    }

                    switch(menuInput){
                        case 1: 
                            addEntry(&account_list);
                            savePasswordList(account_list, key);
                            break;
                        case 2:
                            displayPasswordList(account_list);
                            deletePassword(&account_list);
                            savePasswordList(account_list, key);
                            break;
                        case 3:
                            displayPasswordList(account_list);
                            editPassword(&account_list);
                            savePasswordList(account_list, key);
                            break;
                        case 4:
                            displayPasswordList(account_list);
                            break;
                        default:
                            printf("Invalid choice.\n"); /* error message when a foreign input is entered e.g. 8 */
                            break;
                        }
                    }         
                break;

            case 2:
                createKey();
                break;

            default:
                printf("Invalid choice.\n"); 
                break;
        }
    }
    return 0;
}



    
/* 
    while(1){
        readPasswordList(&account_list,flag);
        flag=1;
        printMainMenu();
        char line[100];
        printf("\nPlease enter your choice (1-5): ");
        fgets(line ,sizeof(line), stdin);
        if(sscanf(line,"%d",&menuInput) != 1) {
            printf("Invalid Choice.\n");
            continue;
        }
        
        if (menuInput == 5){
            printf("Exiting Program..");
            break;
        }

        switch(menuInput){
            case 1: 
            addEntry(&account_list);
            savePasswordList(account_list);
            break;
            case 2:
            deletePassword(&account_list);
            break;
            case 3:
            editPassword(&account_list);
            break;
            case 4:
            displayPasswordList(account_list);
            break;
            case 5:
            return 0;

            default:
            printf("Invalid choice.\n"); 
            break;
        }
    }
    return 0; */


/******************************************************************************
 * Key Login Interface/ Sub-menu
******************************************************************************/

/*  while(1){
    printLoginMenu();
    char line[100];
        printf("\nPlease enter your choice (1-3): ");
        fgets(line ,sizeof(line), stdin);
        
        if(sscanf(line,"%d",&loginInput) != 1) {
            printf("Invalid Choice.\n");
            continue;
        }
         if (loginInput == 3){
            printf("Exiting Program..");
            break;
        }

        switch(loginInput){
            case 1: 
            useKey();
            switch1();
            break;
            case 2:
            createKey();
            break;

            default:
            printf("Invalid choice.\n"); 
            break;
        }
    return 0;
} */

void printLoginMenu(void) {
    printf(
    "================================\n"
    "           Login Menu           \n"
    "================================\n"
     "1. Unlock\n"
     "2. Create Key\n"
     "3. Exit Password Manager\n");
}

void printMainMenu(void) {
    printf(
    "================================\n"
    "           Main Menu            \n"
    "================================\n"
     "1. Add an account\n"
     "2. Delete an account\n"
     "3. Edit an account\n"
     "4. Display account list\n"
     "5. Go back to Login Menu\n");
}

void createKey(void){

}



void loginKey(void){
/* FILE *fp;
fp = fopen( key.txt,"r" );
if (NULL != fp) {
    fseek (fp, 0, SEEK_END);
    size = ftell(fp);

    if (0 == size) {
        printf("file is empty\n");
    }
} */
}

void addEntry(LinkedList* account_list) {
    /* Allocating memory for new entry */
    entry_t* new_entry = (entry_t*)malloc(sizeof(entry_t));

    /* Getting the inputted website that is relevant to the user's accountand putting it into the entry */
    char* website = scanString(MAX_WEBSITE_SIZE, "Enter website: ");
    strcpy(new_entry->url, website);

    /* Getting user's account username input and putting it into entry */
    char* username = scanString(MAX_USERNAME_SIZE, "Enter username: ");
    strcpy(new_entry->username, username);

    /* Getting user password input and putting it into entry */
    char* password = scanString(MAX_PASSWORD_SIZE, "Enter password: ");
    strcpy(new_entry->password, password);

    /* Adding the entry to the account_list */
    LL_push(account_list, new_entry);

    /* Freeing memory */
    free(website);
    free(username);
    free(password);
}

void deletePassword(LinkedList* account_list) {
    char line[100];
    int input;

    /* Getting user input of what entry they want to delete */ 
    printf("\nPlease enter the decimal of the entry you would like to delete: ");
    fgets(line, sizeof(line), stdin);
    while(sscanf(line,"%d", &input) != 1 || input > account_list->size || input <  1) {
        printf("Invalid input. Try again: ");
        fgets(line, sizeof(line), stdin);
    }

    /* Deleting entry at position */
    LL_remove(account_list, input - 1);
}

void editPassword(LinkedList* account_list){
    
    char line[100];
    int input;

    /* Getting user input of what entry they want to edit */
    printf("\nPlease enter the decimal of the entry you would like to edit: ");
    fgets(line, sizeof(line), stdin);
    while(sscanf(line,"%d", &input) != 1 || input > account_list->size || input <  1) {
        printf("Invalid input. Try again: ");
        fgets(line, sizeof(line), stdin);
    }
    
    /* Finding entry at position user has specified */
    entry_t* entry = LL_get(account_list, input - 1);

    /* Getting new values for entry */
    strcpy(entry->url, scanString(MAX_WEBSITE_SIZE, "Enter new website: "));
    strcpy(entry->username, scanString(MAX_USERNAME_SIZE, "Enter new username: "));
    strcpy(entry->password, scanString(MAX_PASSWORD_SIZE, "Enter new password: "));
}

void savePasswordList(LinkedList account_list, char* key) {
    FILE *fp;
    if((fp = fopen(DATABASE_FILE_NAME, "w")) == NULL) {
        printf("Write error");
        return;
    }

    LLNode* node = account_list.head;
    /* Writing the employee list to the database file */
    while(node != NULL) {
        fprintf(fp,"%s %s %s", node->data->url, node->data->username, node->data->password);
        fputs("\n", fp);
        node = node->next;
    }
    printf("Saved into passwords.txt successfully.\n");

    /*Close file */
    fclose(fp);
}

int readPasswordList(LinkedList* account_list, char* key) {
    FILE *fp;

    if((fp = fopen(DATABASE_FILE_NAME, "r")) == NULL) {
        printf("Read error");
        return 0;
    }
   
    while(1) {
        entry_t* new_entry = (entry_t*)malloc(sizeof(entry_t));
        if(fscanf(fp, "%s %s %s", new_entry->url, new_entry->username, new_entry->password) == 3) {           
            LL_push(account_list, new_entry);
        }
        else {
            break;
        }
    }
    fclose(fp);
    return 1;
}


void displayPasswordList(LinkedList account_list) {
    if(account_list.size <= 0) {
        printf("List is empty!\n");
        return;
    }

    printf("     +================================+===========================+======================+\n");
    printf("     | Website                        | Username                  | Password             |\n");
    printf("     +================================+===========================+======================+\n");

    LLNode* node = account_list.head;
    int i = 1;
    while(node != NULL) {
        printf("%3d. | %-30s | %-25s | %-20s |\n", i, node->data->url, node->data->username, node->data->password);
        node = node->next;
        i++;
    }
    printf("     +--------------------------------+---------------------------+----------------------+\n");
}

char* scanString(unsigned int size, char prompt[]) {
    /* Printing out prompt */
    printf("%s", prompt);

    /* Creating a buffer that will contain the user input */
    char buffer[100];
    fgets(buffer, sizeof(buffer), stdin);
    /* Removing the newline at the end of the user input */
    buffer[strcspn(buffer, "\n")] = 0;

    /* Converting the char array into a char pointer to be returned */
    char* result = (char*)malloc(size);
    strcpy(result, buffer);
    return result;
}

