#include "login.h"

bool authenticateUser(sqlite3 *db)
{
    char username[MAX_LENGTH];
    char password[MAX_LENGTH];
    char query[MAX_LENGTH];

    system("cls");
    printf("\n\n\n\t\t\t\t   Bank Management System\n\t\t\t\t\t User Login:");
    scanf("%s", username);

    printf("\n\n\n\n\n\t\t\t\tEnter the password to login:");
    scanf("%s", password);
    unsigned char hashedPassword[SHA256_DIGEST_LENGTH];
    SHA256((const unsigned char *)password, strlen(password), hashedPassword);

    int user_id;
    sprintf(query, "SELECT user_id,password FROM users WHERE username = '%s'", username);

    sqlite3_stmt *stmt;
    int result = sqlite3_prepare_v2(db, query, -1, &stmt, NULL);
    if (result != SQLITE_OK)
    {
        printf("Authentication query error: %s\n", sqlite3_errmsg(db));
        return false;
    }
    result = sqlite3_step(stmt);
    if (result == SQLITE_ROW)
    {
        user_id = sqlite3_column_int(stmt, 0);
        const void *storedHashedPassword = sqlite3_column_blob(stmt,1);
        if (memcmp(hashedPassword,storedHashedPassword,SHA256_DIGEST_LENGTH) == 0){
            printf("Login Successful.\n");
            mainMenu(db,user_id);
        } else {
            printf("Wrong username or password.\n");
        }
    } else
    {
        printf("Authentication failed\n");
        exit(0);
    }
}