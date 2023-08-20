#include "login.h"

void authenticateUser(sqlite3 *db)
{

    char username[MAX_LENGTH];
    char password[MAX_LENGTH];
    char query[MAX_LENGTH];

    clear();
    printw("Login\n");
    printw("Username: ");
    getstr(username);
    printw("Password: ");
    refresh();

    // Hide the password input
    noecho();
    getstr(password);
    echo();
    unsigned char hashedPassword[SHA256_DIGEST_LENGTH];
    SHA256((const unsigned char *)password, strlen(password), hashedPassword);

    int user_id;
    sprintf(query, "SELECT user_id,password FROM users WHERE username = '%s'", username);

    sqlite3_stmt *stmt;
    int result = sqlite3_prepare_v2(db, query, -1, &stmt, NULL);
    if (result != SQLITE_OK)
    {
        printw("Authentication query error: %s\n", sqlite3_errmsg(db));
        return;
    }
    result = sqlite3_step(stmt);
    if (result == SQLITE_ROW)
    {
        user_id = sqlite3_column_int(stmt, 0);
        const void *storedHashedPassword = sqlite3_column_blob(stmt, 1);
        if (memcmp(hashedPassword, storedHashedPassword, SHA256_DIGEST_LENGTH) == 0)
        {
            printw("\nLogin Successful.\n");
            getch();
            mainMenu(db, user_id,username);
        }
        else
        {
            printw("\nWrong username or password.\n");
            printw("Press enter to try again\n");
            getch();
            initMenu(db);
        }
    }
    else
    {
        printw("\nWrong username or password.\n");
        printw("Press enter to try again\n");
        getch();
        initMenu(db);
    }
}

