#include "login.h"

void updateAccountInfo(sqlite3 *db, int accountId, const char *country, const char *phoneNumber) {
    char query[MAX_LENGTH];
    sprintf(query, "UPDATE accounts SET country = '%s', phone_number = '%s' WHERE account_id = %d",
            country, phoneNumber, accountId);

    int result = sqlite3_exec(db, query, NULL, NULL, NULL);
    if (result != SQLITE_OK) {
        printf("Error updating account info: %s\n", sqlite3_errmsg(db));
    } else {
        printf("Account info updated successfully!\n");
    }
}
