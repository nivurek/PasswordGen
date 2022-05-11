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
void deletePassword(unsigned int* password_list_size);
void editPassword(void);
void displayPasswordList(entry_t password_list[], unsigned int* password_list_size);
void savePasswordList(void);
int readPasswordList(void);
char* scanString(unsigned int size, char prompt[]);


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
    printf("\nWelcome to Password Manager 2022\n");
    
    printf("\nWelcome to Password Manager\n");
    while(1){
        int c;
        printMenu();
        char line[100];
        fgets(line ,sizeof(line), stdin);
        if(sscanf(line,"%d",&c) != 1);
   

        /* printf("Please enter your choice (1-7): ");
        scanf("%d", &c); */


        if (c == 7){
            break;
        }

        switch(c){
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


void addPassword(entry_t password_list[], unsigned int* password_list_size) {
    if(*password_list_size >= MAX_ARRAY_SIZE) {
        printf("List is full");
        return;
    }

    entry_t* password_p  = &password_list[*password_list_size];

    char* website = scanString(MAX_WEBSITE_SIZE, "Enter website: ");
    strcpy(password_p->url, website);

    char* password = scanString(MAX_PASSWORD_SIZE, "Enter password: ");
    strcpy(password_p->password, password);

    (*password_list_size)++;
}

void deletePassword(unsigned int* password_list_size) {
    if(*password_list_size > 0) {
        (*password_list_size)--; 
    }
    else {
        printf("List already empty");
    }
}

void editPassword(void){
    
}

void savePasswordList(void){
    
}

int readPasswordList(void){
    
}

void displayPasswordList(entry_t password_list[], unsigned int* password_list_size) {
    int i;
    printf("Website    Password\n");
    printf("---------- ----------\n");
    for(i = 0; i < *password_list_size; i++) {
        printf("%s %s\n", password_list[i].url, password_list[i].password);
    }
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