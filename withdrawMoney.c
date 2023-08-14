#include <stdio.h>
#include <stdbool.h>
#include <sqlite3.h>
#include <string.h>

#define MAX_LENGTH 100
void withdrawMoney(sqlite3 *db, int accountNumber, float amount) {
    char query[MAX_LENGTH];
    sprintf(query, "SELECT balance, account_type FROM accounts WHERE account_number = %d", accountNumber);

    sqlite3_stmt *stmt;
    int result = sqlite3_prepare_v2(db, query, -1, &stmt, NULL);
    if (result != SQLITE_OK) {
        printf("Query error: %s\n", sqlite3_errmsg(db));
        return;
    }

    result = sqlite3_step(stmt);
    if (result == SQLITE_ROW) {
        float balance = sqlite3_column_double(stmt, 0);
        const char *accountType = (const char *)sqlite3_column_text(stmt, 1);

        if (strcmp(accountType, "saving") == 0 || strcmp(accountType, "current") == 0) {
            if (amount <= balance) {
                sprintf(query, "UPDATE accounts SET balance = balance - %.2f WHERE account_number = %d",
                        amount, accountNumber);

                result = sqlite3_exec(db, query, NULL, NULL, NULL);
                if (result == SQLITE_OK) {
                    printf("Money withdrawn successfully!\n");
                } else {
                    printf("Error withdrawing money: %s\n", sqlite3_errmsg(db));
                }
            } else {
                printf("Insufficient balance.\n");
            }
        } else {
            printf("Cannot withdraw from this type of account.\n");
        }
    } else {
        printf("Account not found.\n");
    }

    sqlite3_finalize(stmt);
}
