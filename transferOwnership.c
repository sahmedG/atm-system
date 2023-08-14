#include "login.h"

void transferOwnership(sqlite3 *db, int accountNumber, const char *newOwner) {
    char query[MAX_LENGTH];
    sprintf(query, "UPDATE accounts SET username = '%s' WHERE account_number = %d", newOwner, accountNumber);

    int result = sqlite3_exec(db, query, NULL, NULL, NULL);
    if (result != SQLITE_OK) {
        printf("Error transferring ownership: %s\n", sqlite3_errmsg(db));
    } else {
        printf("Ownership transferred successfully!\n");
    }
}
