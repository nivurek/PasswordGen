#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "algorithms.h"
#include "cryptography.h"

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
int readPasswordList(int count);

/******************************************************************************
 * Main
******************************************************************************/
int main(void) {

    /* Initialise file reading/writing here */

    /* char dbFileName[] = "database.txt"; */
/******************************************************************************
 * User Interface/ Menu
******************************************************************************/

}

void printMenu(void) {
    printf("\n\n"
     "1. add employee\n"
     "2. delete last employee\n"
     "3. display employee list\n"
     "4. save the employee list to the database\n"
     "5. read the employee list from the database\n"
     "6. exit the program\n");
}








