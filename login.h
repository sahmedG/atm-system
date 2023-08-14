#include <stdio.h>
#include <stdbool.h>
#include <sqlite3.h>
#include <string.h>

bool authenticateUser(sqlite3 *db, const char *username, const char *password);
