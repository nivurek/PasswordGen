#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "algorithms.h"
#include "cryptography.h"


#define MAX_WEBSITE_SIZE 50
#define MAX_PASSWORD_SIZE 50  
#define MAX_ARRAY_SIZE 50

/******************************************************************************
 * Function prototypes
******************************************************************************/
void printMenu(void);
void addPassword(LinkedList* password_list);
void deletePassword(LinkedList* password_list);
void editPassword(void);
void displayPasswordList(LinkedList password_list);
void savePasswordList(void);
int readPasswordList(void);
char* scanString(unsigned int size, char prompt[]);


/******************************************************************************
 * Main
******************************************************************************/
int main(void) {

    LinkedList password_list;
    password_list.size = 0;

    /* char dbFileName[] = "database.txt"; */
/******************************************************************************
 * User Interface/ Menu
******************************************************************************/
    
    printf("\nWelcome to Password Manager\n");
    while(1){
        int menuInput;
        printMenu();
        char line[100];
        printf("\nPlease enter your choice (1-7): ")
        fgets(line ,sizeof(line), stdin);
        if(sscanf(line,"%d",&menuInput) != 1);
        
        if (menuInput == 7){
            break;
        }

        switch(menuInput){
            case 1: 
            addPassword(password_list, &password_list_size);
            break;
            case 2:
            deletePassword(&password_list_size);
            break;
            case 3:
            editPassword();
            break;
            case 4:
            displayPasswordList(password_list, &password_list_size);
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


void addPassword(LinkedList* password_list) {
    entry_t* new_entry = (entry_t*)malloc(sizeof(entry_t));

    char* website = scanString(MAX_WEBSITE_SIZE, "Enter website: ");
    strcpy(new_entry->url, website);

    char* password = scanString(MAX_PASSWORD_SIZE, "Enter password: ");
    strcpy(new_entry->password, password);

    LL_push(password_list, new_entry);
}

void deletePassword(LinkedList* password_list) {
    LL_pop(password_list); 
}

void editPassword(void){
    
    
}

void savePasswordList(void){
    
}

int readPasswordList(void){
    
}

void displayPasswordList(LinkedList password_list) {
    if(password_list.size <= 0) {
        printf("List is empty");
        return;
    }

    printf("Website    Password\n");
    printf("---------- ----------\n");

    LLNode* node = password_list.head;
    while(node != NULL) {
        printf("%s %s\n", node->data->url, node->data->password);
        node = node->next;
    }
    printf("Size: %d", password_list.size);
}

char* scanString(unsigned int size, char prompt[]) {
    printf("%s", prompt);
    char buffer[100];
    char* result = (char*)malloc(size);
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    strcpy(result, buffer);
    return result;
}