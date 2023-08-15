#include "login.h"

void transferOwnership(sqlite3 *db, int user_id)
{
    char query_newuser_id[MAX_LENGTH];
    char update_owner[MAX_LENGTH];
    int accountNumber;
    char newOwner[MAX_LENGTH];

    printf("Enter account number: ");
    scanf("%d", &accountNumber);

    printf("Enter new owner username: ");
    scanf("%s", newOwner);
    sqlite3_stmt *stmt;

    sprintf(query_newuser_id, "SELECT user_id FROM users WHERE username = '%s'", newOwner);
    int result = sqlite3_prepare_v2(db, query_newuser_id, -1, &stmt, NULL);
    if (result != SQLITE_OK)
    {
        printf("Authentication query error: %s\n", sqlite3_errmsg(db));
        return;
    }
    result = sqlite3_step(stmt);
    int new_user_id = sqlite3_column_int(stmt, 0);

    sprintf(update_owner, "UPDATE accounts SET user_id = %d WHERE account_number = %d", new_user_id, accountNumber);
    result = sqlite3_exec(db, update_owner, NULL, NULL, NULL);
    if (result != SQLITE_OK)
    {
        printf("Error transferring ownership: %s\n", sqlite3_errmsg(db));
    }
    else
    {
        printf("Ownership transferred successfully!\n");
        printf("Congratulations,%s! Someone has transferred an account to you.\n",newOwner);
        Success(db, user_id);
    }
}
