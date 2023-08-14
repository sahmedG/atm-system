#include <stdio.h>
#include <stdbool.h>
#include <sqlite3.h>
#include <string.h>
#define MAX_LENGTH 100
void registerUser(sqlite3 *db, const char *username, const char *password) {
    char query[MAX_LENGTH];
    sprintf(query, "INSERT INTO users (username, password) VALUES ('%s', '%s')", username, password);

    int result = sqlite3_exec(db, query, NULL, NULL, NULL);
    if (result != SQLITE_OK) {
        printf("Error registering user: %s\n", sqlite3_errmsg(db));
    } else {
        printf("User registered successfully!\n");
    }
}
