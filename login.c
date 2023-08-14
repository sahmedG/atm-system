#include "login.h"

bool authenticateUser(sqlite3 *db, const char *username, const char *password) {
    char query[MAX_LENGTH];
    int user_id;
    sprintf(query, "SELECT * FROM users WHERE username = '%s' AND password = '%s'", username, password);

    sqlite3_stmt *stmt;
    int result = sqlite3_prepare_v2(db, query, -1, &stmt, NULL);
    if (result != SQLITE_OK) {
        printf("Authentication query error: %s\n", sqlite3_errmsg(db));
        return false;
    }
    result = sqlite3_step(stmt);
    if (result == SQLITE_ROW)
    {
        user_id = sqlite3_column_int(stmt, 0);
    };

    result = sqlite3_step(stmt);
    bool authenticated = (result == SQLITE_ROW);

    sqlite3_finalize(stmt);
    return user_id;
}
