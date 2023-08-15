#include "login.h"

void Success(sqlite3 *db, int user_id)
{
    int option;
    printf("\nSuccess!\n\n");
invalid:
    printf("Enter 1 to go to the main menu and 0 to exit!\n");
    scanf("%d", &option);
    system("cls");
    if (option == 1)
    {
        mainMenu(db, user_id);
    }
    else if (option == 0)
    {
        exit(1);
    }
    else
    {
        printf("Insert a valid operation!\n");
        goto invalid;
    }
}