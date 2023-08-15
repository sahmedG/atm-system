#include "login.h"
void registerUser(sqlite3 *db)
{
    char query[MAX_LENGTH];
    char username[MAX_LENGTH];
    char password[MAX_LENGTH];
    
    system("cls");
    printf("Enter new username: ");
    scanf("%s", username);

    printf("Enter new password: ");
    scanf("%s", password);

    unsigned char hashedPassword[SHA256_DIGEST_LENGTH];
    SHA256((const unsigned char*)password,strlen(password),hashedPassword);

    sprintf(query, "INSERT INTO users (username, password) VALUES ('%s', ?)", username);
    sqlite3_stmt *stmt;
    int result = sqlite3_prepare_v2(db, query, -1, &stmt, NULL);
    if (result != SQLITE_OK)
    {
        printf("Query error: %s\n", sqlite3_errmsg(db));
        return;
    }
    sqlite3_bind_blob(stmt,1,hashedPassword,SHA256_DIGEST_LENGTH,SQLITE_STATIC);
    result = sqlite3_step(stmt);
    if (result == SQLITE_DONE)
    {
        printf("User registered successfully!\n");
    } else {
        printf("Error registering user.\n");
    }
    sqlite3_finalize(stmt);
}
