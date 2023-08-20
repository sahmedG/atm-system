#include "login.h"
void registerUser(sqlite3 *db)
{
    char query[MAX_LENGTH];
    char username[MAX_LENGTH];
    char password[MAX_LENGTH];

    clear();
    printw("New user register\n");
    printw("Enter new username: ");
    getstr(username);
    printw("Password: ");
    refresh();

    noecho();
    getstr(password);
    echo();

    unsigned char hashedPassword[SHA256_DIGEST_LENGTH];
    SHA256((const unsigned char *)password, strlen(password), hashedPassword);

    sprintf(query, "INSERT INTO users (username, password) VALUES ('%s', ?)", username);
    sqlite3_stmt *stmt;
    int result = sqlite3_prepare_v2(db, query, -1, &stmt, NULL);
    if (result != SQLITE_OK)
    {
        printf("Query error: %s\n", sqlite3_errmsg(db));
        return;
    }
    sqlite3_bind_blob(stmt, 1, hashedPassword, SHA256_DIGEST_LENGTH, SQLITE_STATIC);
    result = sqlite3_step(stmt);
    if (result == SQLITE_DONE)
    {
        printw("\nUser registered successfully!\n");
        printw("Press Enter to go back to the main menu...");
        getch();
        endwin();
        initMenu(db);
    }
    else
    {
        printw("Error registering user with similar username already exist.\n");
        exit(0);
    }
    sqlite3_finalize(stmt);
}
