#include <stdio.h>
#include <stdbool.h>
#include <sqlite3.h>
#include <string.h>

#define MAX_LENGTH 100

void transferMoney(sqlite3 *db, const char *username) {
    int fromAccountNumber, toAccountNumber;
    float amount;

    printf("Enter source account number: ");
    scanf("%d", &fromAccountNumber);

    printf("Enter destination account number: ");
    scanf("%d", &toAccountNumber);

    printf("Enter amount to transfer: ");
    scanf("%f", &amount);

    char query[MAX_LENGTH];
    sprintf(query, "SELECT balance, account_type FROM accounts WHERE account_number = %d", fromAccountNumber);

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
                // Transfer money logic here

                // Update 'from' account balance
                sprintf(query, "UPDATE accounts SET balance = balance - %.2f WHERE account_number = %d", amount, fromAccountNumber);
                result = sqlite3_exec(db, query, NULL, NULL, NULL);
                if (result != SQLITE_OK) {
                    printf("Error updating balance: %s\n", sqlite3_errmsg(db));
                    sqlite3_finalize(stmt);
                    return;
                }

                // Update 'to' account balance
                sprintf(query, "UPDATE accounts SET balance = balance + %.2f WHERE account_number = %d", amount, toAccountNumber);
                result = sqlite3_exec(db, query, NULL, NULL, NULL);
                if (result != SQLITE_OK) {
                    printf("Error updating balance: %s\n", sqlite3_errmsg(db));
                    sqlite3_finalize(stmt);
                    return;
                }

                printf("Money transferred successfully!\n");
            } else {
                printf("Insufficient balance in the source account.\n");
            }
        } else {
            printf("Cannot transfer from this type of account.\n");
        }
    } else {
        printf("Source account not found.\n");
    }

    sqlite3_finalize(stmt);
}
