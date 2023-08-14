#define MAX_LENGTH 100
#include <stdio.h>
#include <stdbool.h>
#include <sqlite3.h>
#include <string.h>
void checkAllAccounts(sqlite3 *db, int *userid, const char *username)
{
    char query[MAX_LENGTH];
    sprintf(query, "SELECT * FROM accounts WHERE user_id = %d", userid);

    sqlite3_stmt *stmt;
    int result = sqlite3_prepare_v2(db, query, -1, &stmt, NULL);
    if (result != SQLITE_OK)
    {
        printf("Query error: %s\n", sqlite3_errmsg(db));
        return;
    }

    printf("\nAccounts under %s:\n", username);
    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        int accountNumber = sqlite3_column_int(stmt, 0);
        const char *accountType = (const char *)sqlite3_column_text(stmt, 6);
        float balance = sqlite3_column_double(stmt, 5);
        const char *country = (const char *)sqlite3_column_text(stmt, 2);
        const char *phone_no = sqlite3_column_text(stmt, 3);
        const char *created_on = (const char *)sqlite3_column_text(stmt, 7);
        printf("Account Number: %d\n", accountNumber);
        printf("Account Type: %s\n", accountType);
        printf("Balance: %.2f\n", balance);
        printf("Country: %s\n", country);
    }
    sqlite3_finalize(stmt);
}
