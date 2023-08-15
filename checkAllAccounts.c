#include "login.h"
void checkAllAccounts(sqlite3 *db,int user_id)
{
    char query_account[MAX_LENGTH];
    char query_user[MAX_LENGTH];
    sqlite3_stmt *stmt;
    sprintf(query_user, "SELECT username FROM users WHERE user_id = %d", user_id);
    sprintf(query_account, "SELECT * FROM accounts WHERE user_id = %d", user_id);

    int result = sqlite3_prepare_v2(db, query_user, -1, &stmt, NULL);
    if (result != SQLITE_OK)
    {
        printf("Authentication query error: %s\n", sqlite3_errmsg(db));
        return;
    }

    result = sqlite3_step(stmt);
    const char *username = sqlite3_column_text(stmt,0);

    result = sqlite3_prepare_v2(db, query_account, -1, &stmt, NULL);
    if (result != SQLITE_OK)
    {
        printf("Query error: %s\n", sqlite3_errmsg(db));
        return;
    }

    printf("\t\t====== All accounts from user, %s =====\n\n", username);
    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        printf("_____________________\n");
        int accountNumber = sqlite3_column_int(stmt, 0);
        const char *accountType = (const char *)sqlite3_column_text(stmt, 6);
        float balance = sqlite3_column_double(stmt, 4);
        const char *country = (const char *)sqlite3_column_text(stmt, 2);
        const char *phone_no = (const char *)sqlite3_column_text(stmt, 3);
        const char *created_on = (const char *)sqlite3_column_text(stmt, 7);
        printf("Account Number: %d\n", accountNumber);
        printf("Account Type: %s\n", accountType);
        printf("Balance: %.2f\n", balance);
        printf("Country: %s\n", country);
    }
    // sqlite3_finalize(stmt);
    Success(db, user_id);
}
