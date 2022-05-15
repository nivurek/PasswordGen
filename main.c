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

/******************************************************************************
 * Function prototypes
******************************************************************************/
void printMenu(void);
void addEntry(LinkedList* account_list);
void deletePassword(LinkedList* account_list);
void editPassword(void);
void displayPasswordList(LinkedList account_list);
void savePasswordList(LinkedList account_list);
int readPasswordList(LinkedList* account_list);
char* scanString(unsigned int size, char prompt[]);


/******************************************************************************
 * Main
******************************************************************************/
int main(void) {

    LinkedList account_list;
    account_list.size = 0;
    account_list.size = NULL;

    /* char dbFileName[] = "database.txt"; */
/******************************************************************************
 * User Interface/ Menu
******************************************************************************/
    
    printf("\nWelcome to Password Manager\n");
    while(1){
        int menuInput;
        printMenu();
        char line[100];
        printf("\nPlease enter your choice (1-7): ");
        fgets(line ,sizeof(line), stdin);
        if(sscanf(line,"%d",&menuInput) != 1) {
            printf("Invalid Choice.\n");
            continue;
        }
        
        if (menuInput == 7){
            break;
        }

        switch(menuInput){
            case 1: 
            addEntry(&account_list);
            break;
            case 2:
            deletePassword(&account_list);
            break;
            case 3:
            editPassword();
            break;
            case 4:
            displayPasswordList(account_list);
            break;
            case 5:
            savePasswordList(account_list);
            break; 
            case 6:
            readPasswordList(&account_list);
            break; 
            
            default:
            printf("Invalid choice.\n"); /* error message when a foreign input is entered e.g. 8 */
            break;
        }
    }
    return 0;
}

void printMenu(void) {
    printf("\n"
     "1. Add an account\n"
     "2. Delete an account\n"
     "3. Edit an account\n"
     "4. Display account list\n"
     "5. Save the account list as an encrypted file\n"
     "6. Read an account list from an encrypted file\n"
     "7. Exit Password Manager\n");
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
    LL_pop(account_list); 
}

void editPassword(void){
    
}

void savePasswordList(LinkedList account_list){
    FILE *fp;
    if((fp = fopen(DATABASE_FILE_NAME, "w")) == NULL) {
        printf("Write error");
        return;
    }

    int i;
    LLNode* node = account_list.head;
    /* Writing the employee list to the database file */
    while(node != NULL) {
        // fwrite(node->data, sizeof(entry_t), 1, fp);
        fprintf(fp,"%s %s %s\n", node->data->url, node->data->username, node->data->password);
        node = node->next;
    }

    /*Close file */
    fclose(fp);
}

int readPasswordList(LinkedList* account_list){
    FILE *fp;

    if((fp = fopen(DATABASE_FILE_NAME, "r")) == NULL) {
        printf("Read error");
        return 1;
    }


    LLNode* current = account_list->head;
    char *website, *username, *password;

    while(fscanf(fp, "%s %s %s\n", website, username, password)) {
        entry_t* new_entry = (entry_t*)malloc(sizeof(entry_t));        

        current = (LLNode*)malloc(sizeof(LLNode));

        strcpy(new_entry->url, website);
        strcpy(new_entry->username, username);
        strcpy(new_entry->password, password);

        current->data = new_entry;

        current = current->next;
    }
    
    fclose(fp);
    return 0;
}


void displayPasswordList(LinkedList account_list) {
    if(account_list.size <= 0) {
        printf("List is empty!\n");
        return;
    }

    printf("\nWebsite                         Username                   Password\n");
    printf("------------------------------  -------------------------  --------------------\n");

    LLNode* node = account_list.head;
    while(node != NULL) {
        printf("%-30s  %-25s  %-20s\n", node->data->url, node->data->username, node->data->password);
        node = node->next;
    }
    printf("Size: %d", account_list.size);
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

