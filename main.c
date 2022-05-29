/******************************************************************************
 * PASSWORD MANAGER
 * 
 * Compilation Instructions:                    Terminal Input:
 *  1. Make using make file.                    1. make
 *  2. Run PasswordManager file.                2. ./PasswordManager
 * 
 * 
 * Project Group 3
 * Students:
 *  - Aidan Grigg (14314328)    | Lab 07
 *  - Vatsin Kumar (13760893)   | Lab 06
*   - Kelvin Huang (13228186)   | Lab 05
******************************************************************************/

/******************************************************************************
 * Includes
******************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

/* Library containing LinkedList struct, Entry struct and associated functions */
#include "algorithms.h" 
/* Library containing XOR Cipher function */
#include "cryptography.h"

/******************************************************************************
 * Defines
******************************************************************************/
#define MAX_WEBSITE_SIZE 50
#define MAX_USERNAME_SIZE 30
#define MAX_PASSWORD_SIZE 30
#define MAX_KEY_SIZE 50

#define DATABASE_FILE_NAME "passwords.bin"
#define KEY_FILE_NAME "key.bin"
#define KEY_ENCRYPT "BOPFoq117gFXT9ax90aPnzcmCdAHV0AQYlz3e0TPj2IzeRZ9dh"

/******************************************************************************
 * Function prototypes
******************************************************************************/
void loginMenu(LinkedList_t* account_list, char* key);
void mainMenu(LinkedList_t* account_list, char* key);
void printMainMenu(void);
void printLoginMenu(void);

void createKey(char* key);
void loginKey(char* key);
void editKey(LinkedList_t account_list, char* key);

void addEntry(LinkedList_t* account_list);
void deleteEntry(LinkedList_t* account_list);
void editEntry(LinkedList_t* account_list);
void displayEntryList(LinkedList_t account_list);
void saveEntryList(LinkedList_t account_list, char* key);
void readEntryList(LinkedList_t* account_list, char* key);

char* scanString(unsigned int size, char prompt[]);
void xorEntry(entry_t* entry, char* key);

/******************************************************************************
 * Main
******************************************************************************/
int main(void) {
    LinkedList_t account_list;
    account_list.size = 0;
    account_list.head = NULL;
    char* key = (char*)malloc(MAX_KEY_SIZE);

    loginMenu(&account_list, key);
    
    free(key);

    return 0;
}

/******************************************************************************
 * loginMenu
 * Takes the user input for the login menu and calls the corresponding function
 * related to users input.
******************************************************************************/
void loginMenu(LinkedList_t* account_list, char* key) {
    int loginInput;
    char line[100];

    while(1) {
        printLoginMenu();

        /* Getting user input */
        printf("\nPlease enter your choice (1-3): ");
        fgets(line ,sizeof(line), stdin);
        
        if(sscanf(line,"%d",&loginInput) != 1) {
            printf("Invalid Choice.\n");
            continue;
        }

        /* Cases for each option on menu */
        switch(loginInput){
            case 1:
                loginKey(key);
                mainMenu(account_list, key);        
                break;
            case 2:
                createKey(key);
                mainMenu(account_list, key);        
                break;
            case 3:
                exit(0);
                break;
            default:
                printf("Invalid choice.\n"); 
                break;
        }
    }
}

/******************************************************************************
 * mainMenu
 * Takes the user input for the main menu and calls the corresponding function
 * related to users input.
******************************************************************************/
void mainMenu(LinkedList_t* account_list, char* key) {
    int menuInput;
    char line[100];
    readEntryList(account_list, key);

    while(1) {
        printMainMenu();

        /* Getting user input */
        printf("\nPlease enter your choice (1-5): ");
        fgets(line, sizeof(line), stdin);
        if(sscanf(line,"%d", &menuInput) != 1) {
            printf("Invalid Choice.\n");
            continue;
        }

        /* Cases for each option on menu */
        switch(menuInput) {
            case 1: 
                addEntry(account_list);
                saveEntryList(*account_list, key);
                break;
            case 2:
                displayEntryList(*account_list);
                deleteEntry(account_list);
                saveEntryList(*account_list, key);
                break;
            case 3:
                displayEntryList(*account_list);
                editEntry(account_list);
                saveEntryList(*account_list, key);
                break;
            case 4:
                displayEntryList(*account_list);
                break;
            case 5:
                editKey(*account_list, key);
                break;
            case 6:
                exit(0);
                break;
            default:
                printf("Invalid choice.\n");
                break;
        }
    }         
}

/******************************************************************************
 * printLoginMenu - LOGIN MENU
 * Prints the login menu.
******************************************************************************/
void printLoginMenu(void) {
    printf(
    "\n================================\n"
    "           Login Menu           \n"
    "================================\n"
     "1. Unlock\n"
     "2. Create Key\n"
     "3. Exit Password Manager\n");
}

/******************************************************************************
 * printMainMenu - MAIN MENU
 * Prints the main menu.
******************************************************************************/
void printMainMenu(void) {
    printf(
    "\n================================\n"
    "           Main Menu            \n"
    "================================\n"
     "1. Add an account\n"
     "2. Delete an account\n"
     "3. Edit an account\n"
     "4. Display account list\n"
     "5. Change key\n"
     "6. Exit program\n");
}

/******************************************************************************
 * createKey - LOGIN MENU
 * Prompts user for a key and creates a file to save it into.
 * Returns key through key parameter.
******************************************************************************/
void createKey(char* key) {
    /* Checking if there is already a key */
    FILE* fp;
    if((fp = fopen(KEY_FILE_NAME, "rb")) != NULL) {
        fclose(fp);
        printf("There is already an existing key! Redirecting to unlock...\n");
        loginKey(key);
        return;
    }

    /* If a key is not set, get users key input */
    char* first_key = scanString(MAX_KEY_SIZE, "Create a key: ");
    char* second_key = scanString(MAX_KEY_SIZE, "Enter key to confirm: ");

    while(strcmp(first_key, second_key) != 0) {
        printf("Keys are not the same, try again. \n");
        free(first_key);
        free(second_key);
        first_key = scanString(MAX_KEY_SIZE, "Create a key: ");
        second_key = scanString(MAX_KEY_SIZE, "Enter key to confirm: ");
    }

    /* Copying users key into actual key variable */
    strcpy(key, first_key);

    /* Writing encrypted key into key file in format of (key_length , key) */
    if((fp = fopen(KEY_FILE_NAME, "wb")) == NULL) {
        printf("Error writing key");
    }

    size_t key_len = strlen(key);
    
    char* encrypted_key = XORCipher(key, KEY_ENCRYPT, key_len);

    fwrite(&key_len, sizeof(size_t), 1, fp);
    fwrite(encrypted_key, key_len + 1, 1, fp);

    free(first_key);
    free(second_key);
    free(encrypted_key);
    fclose(fp);
}

/******************************************************************************
 * createKey - LOGIN MENU
 * Prompts user for a prexisting key and tests it against key saved to file.
 * If the keys are the same, returns key through key parameter.
******************************************************************************/
void loginKey(char* key) {
    /* Checking if there is not already a key */
    FILE* fp;
    if((fp = fopen(KEY_FILE_NAME, "rb")) == NULL) {
        printf("Key has not been set! Redirecting to create key...\n");
        createKey(key);
        return;
    }

    /* Reading in encrypted key in format of (key_len , key) */
    size_t key_len;
    fread(&key_len, sizeof(size_t), 1, fp);

    char* encrypted_key = (char*)malloc(key_len);
    fread(encrypted_key, key_len, 1, fp);

    /* Decrypting key */
    char* file_key = XORCipher(encrypted_key, KEY_ENCRYPT, key_len);
    file_key[key_len] = '\0';

    /* Comparing users inputted key to the key in the file, ensuring the key is correct */
    char* user_key = scanString(MAX_KEY_SIZE, "Enter key: ");
    while(strcmp(user_key, file_key) != 0) {
        printf("Incorrect key, try again. \n");
        free(user_key);
        user_key = scanString(MAX_KEY_SIZE, "Enter key: ");
    }

    /* Copying key in file into actual key variable */
    strcpy(key, file_key);
    
    free(encrypted_key);
    free(file_key);
    free(user_key);

    fclose(fp);
}

/******************************************************************************
 * editKey - MAIN MENU
 * Prompts user for a key and saves it to key file. Re-saves the password list
 * encrypted with the newly inputted user key.
 * Returns key through key parameter. 
******************************************************************************/
void editKey(LinkedList_t account_list, char* key) {

    /* Getting a users key input */
    char* first_key = scanString(MAX_KEY_SIZE, "Enter new key: ");
    char* second_key = scanString(MAX_KEY_SIZE, "Enter key to confirm: ");

    while(strcmp(first_key, second_key) != 0) {
        printf("Keys are not the same, try again. \n");
        free(first_key);
        free(second_key);
        first_key = scanString(MAX_KEY_SIZE, "Create a key: ");
        second_key = scanString(MAX_KEY_SIZE, "Enter key to confirm: ");
    }

    /* Setting actual key variable to be users newly inputted key */
    strcpy(key, first_key);

    /* Saving file again with new key encryption */
    saveEntryList(account_list, key);

    /* Saving new key to key file in format of (key_len , key) */
    FILE* fp;
    if((fp = fopen(KEY_FILE_NAME, "wb")) == NULL) {
        printf("Error writing key");
    }

    size_t key_len = strlen(key);
    
    char* encrypted_key = XORCipher(key, KEY_ENCRYPT, key_len);

    fwrite(&key_len, sizeof(size_t), 1, fp);
    fwrite(encrypted_key, key_len + 1, 1, fp);

    free(encrypted_key);
    free(first_key);
    free(second_key);
}

/******************************************************************************
 * addEntry - MAIN MENU
 * Creates a new entry, gets user inputted values for the entry, and adds
 * it to the list.
******************************************************************************/
void addEntry(LinkedList_t* account_list) {
    /* Allocating memory for new entry */
    entry_t* new_entry = (entry_t*)malloc(sizeof(entry_t));

    /* Getting the inputted website that is relevant to the user's accountand putting it into the entry */
    new_entry->url= scanString(MAX_WEBSITE_SIZE, "Enter website: ");
    new_entry->url_len = strlen(new_entry->url);

    /* Getting user's account username input and putting it into entry */
    new_entry->username = scanString(MAX_USERNAME_SIZE, "Enter username: ");
    new_entry->user_len= strlen(new_entry->username);

    /* Getting user password input and putting it into entry */
    new_entry->password = scanString(MAX_PASSWORD_SIZE, "Enter password: ");
    new_entry->pass_len = strlen(new_entry->password);

    /* Adding the entry to the account_list */
    LL_push(account_list, new_entry);
}

/******************************************************************************
 * deleteEntry - MAIN MENU
 * Prompts user input for the node to delete, and removes it from the list.
******************************************************************************/
void deleteEntry(LinkedList_t* account_list) {
    /* Edge case where list is empty */
    if(account_list->size <= 0) {
        return;
    }
    char line[100];
    int input;

    /* Getting user input of what entry they want to delete */ 
    printf("\nPlease enter the number of the entry you would like to delete: ");
    fgets(line, sizeof(line), stdin);
    while(sscanf(line,"%d", &input) != 1 || input > account_list->size || input <  1) {
        printf("Invalid input.\nPlease try again: ");
        fgets(line, sizeof(line), stdin);
    }

    /* Deleting entry at position */
    LL_remove(account_list, input - 1);
}

/******************************************************************************
 * editEntry - MAIN MENU
 * Prompts user input for the node to edit, and and updates the nth 
 * nodes values with newly prompted values. 
******************************************************************************/
void editEntry(LinkedList_t* account_list){ 
    /* Edge case where list is empty */
    if(account_list->size <= 0) {
        return;
    }
    char line[100];
    int input;

    /* Getting user input of what entry they want to edit */
    printf("\nPlease enter the decimal of the entry you would like to edit: ");
    fgets(line, sizeof(line), stdin);
    while(sscanf(line,"%d", &input) != 1 || input > account_list->size || input <  1) {
        printf("Invalid input.\n Please try again: ");
        fgets(line, sizeof(line), stdin);
    }
    
    /* Finding entry at position user has specified */
    entry_t* entry = LL_get(account_list, input - 1);

    /* Getting new values for entry */
    entry->url = scanString(MAX_WEBSITE_SIZE, "Enter new website: ");
    entry->url_len = strlen(entry->url);

    entry->username = scanString(MAX_USERNAME_SIZE, "Enter new username: ");
    entry->user_len = strlen(entry->username);

    entry->password = scanString(MAX_PASSWORD_SIZE, "Enter new password: ");
    entry->pass_len = strlen(entry->password);
}

/******************************************************************************
 * saveEntryList - MAIN MENU
 * Saves the entry linked list to a  binary file. File is formatted as follows.
 * 
 * Size of the list is saved at the start of the binary file, followed by each
 * entry in the following format:
 * {url length , url , username length , username , password length , password}
******************************************************************************/
void saveEntryList(LinkedList_t account_list, char* key) {
    FILE *fp;
    if((fp = fopen(DATABASE_FILE_NAME, "wb")) == NULL) {
        printf("Write error");
        return;
    }

    /* Writing the size of the list to the file */    
    fwrite(&account_list.size, sizeof(unsigned int), 1, fp);

    /* Incremement through the linked list */
    LLNode_t* node = account_list.head;
    while(node != NULL) {
        entry_t temp = *(node->data);
        /* Encrypting the entry */
        xorEntry(&temp, key);

        /* Writing url to file */
        fwrite(&temp.url_len, sizeof(size_t), 1, fp);
        fwrite(temp.url, temp.url_len + 1, 1, fp);

        /* Writing username to file */
        fwrite(&temp.user_len, sizeof(size_t), 1, fp);
        fwrite(temp.username, temp.user_len + 1, 1, fp);

        /* Writing password to file */
        fwrite(&temp.pass_len, sizeof(size_t), 1, fp);
        fwrite(temp.password, temp.pass_len + 1, 1, fp);

        node = node->next;
    }
    printf("Data updated successfully.\n");
    fclose(fp);
}

/******************************************************************************
 * readEntryList - MAIN MENU
 * Reads the saved binary file into the account list. 
 * File is formatted as follows.
 * 
 * Size of the list is saved at the start of the binary file, followed by each
 * entry in the following format:
 * {url length , url , username length , username , password length , password}
******************************************************************************/
void readEntryList(LinkedList_t* account_list, char* key) {
    FILE *fp;

    /* Opening the file, if the file fails to open return from function */
    if((fp = fopen(DATABASE_FILE_NAME, "rb")) == NULL) {
        return;
    }

    /* Ensuring account list is already empty */
    while(account_list->size > 0) {
        LL_pop(account_list);
    }

    /* Reading in the size of the list */
    unsigned int list_size;
    fread(&list_size, sizeof(unsigned int), 1, fp);

    /* Reading in each entry in the file */
    int i;
    for(i = 0; i < list_size; i++) {
        entry_t* new_entry = (entry_t*)malloc(sizeof(entry_t));
        
        /* Reading in url */
        fread(&new_entry->url_len, sizeof(size_t), 1, fp);
        new_entry->url = (char*)malloc(new_entry->url_len);
        fread(new_entry->url, new_entry->url_len + 1, 1, fp);

        /* Reading in username */
        fread(&new_entry->user_len, sizeof(size_t), 1, fp);
        new_entry->username= (char*)malloc(new_entry->user_len);
        fread(new_entry->username, new_entry->user_len + 1, 1, fp);

        /* Reading in password */ 
        fread(&new_entry->pass_len, sizeof(size_t), 1, fp);
        new_entry->password = (char*)malloc(new_entry->pass_len);
        fread(new_entry->password, new_entry->pass_len + 1, 1, fp);

        /* Decrypting file and adding to account list */
        xorEntry(new_entry, key);
        LL_push(account_list, new_entry);
    }

    fclose(fp);
}

/******************************************************************************
 * displayEntryList - MAIN MENU
 * Displays the list in a formatted table.
******************************************************************************/
void displayEntryList(LinkedList_t account_list) {
    /* Edge case where list is empty */
    if(account_list.size <= 0) {
        printf("List is empty!\n");
        return;
    }

    /* Print header */
    printf("\n     +====================================================+================================+================================+\n");
    printf("     | Website                                            | Username                       | Password                       |\n");
    printf("     +====================================================+================================+================================+\n");

    /* Increment though list, printing each entry */
    LLNode_t* node = account_list.head;
    int i = 1;
    while(node != NULL) {
        printf("%3d. | %-50s | %-30s | %-30s |\n", i, node->data->url, node->data->username, node->data->password);
        node = node->next;
        i++;
    }

    /* Print footer */
printf("     +====================================================+================================+================================+\n");
}

/******************************************************************************
 * scanString - HELPER FUNCTION
 * Prompts user with the prompt parameter and returns a pointer to a string of
 * maximum size in parameter.
******************************************************************************/
char* scanString(unsigned int size, char prompt[]) {
    /* Printing out prompt */
    printf("%s", prompt);

    /* Creating a buffer that will contain the user input */
    char buffer[size];
    fgets(buffer, sizeof(buffer), stdin);
    /* Removing the newline at the end of the user input */
    buffer[strcspn(buffer, "\n")] = '\0';

    /* Flushing the stdin buffer if the length of the string exceeds the maximum */
    while(strlen(buffer) + 1 >= size) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) { }

    /* Validates the string to see if size of buffer array is more than the max defined size for the type of input */    
    printf("Input is too large! Try again: ");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = '\0';
    }

    /* Converting the char array into a char pointer to be returned */
    char* result = (char*)malloc(size);
    strcpy(result, buffer);
    return result;
}

/******************************************************************************
 * xorEntry - HELPER FUNCTION
 * Applies XOR cipher to each string in entry.
******************************************************************************/
void xorEntry(entry_t* entry, char* key) {
    /* Encrypting each string in entry */
    entry->url = XORCipher(entry->url, key, entry->url_len);
    entry->username = XORCipher(entry->username, key, entry->user_len);
    entry->password = XORCipher(entry->password, key, entry->pass_len);
    entry->url[entry->url_len] = '\0';
    entry->username[entry->user_len] = '\0';
    entry->password[entry->pass_len] = '\0';
}