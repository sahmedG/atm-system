#include "login.h"
void depositMoney(sqlite3 *db, int user_id)
{
    char query[MAX_LENGTH];
    int accountNumber;
    float amount;
    int result;

    sqlite3_stmt *stmt;
    printf("Enter account number: ");
    scanf("%d", &accountNumber);
    printf("Enter amount to deposit: ");
    scanf("%f", &amount);
    printf("%d", accountNumber);
    sprintf(query, "SELECT count(*) FROM accounts WHERE account_number = %d", accountNumber),

        result = sqlite3_prepare_v2(db, query, -1, &stmt, NULL);
    if (result != SQLITE_OK)
    {
        printf("Error checking account: %s\n", sqlite3_errmsg(db));
        return;
    }

    result = sqlite3_step(stmt);
    if (result == SQLITE_ROW)
    {
        int count = sqlite3_column_int(stmt, 0);
        if (count == 0)
        {
            printf("\nAccount does not exist!\n");
            sqlite3_finalize(stmt);
            return;
        }
    } else {
        printf("Error getting row from database.\n");
        sqlite3_finalize(stmt);
        return;
    }
    sprintf(query, "UPDATE accounts SET balance = balance + %0.2f WHERE account_number = %d;", amount, accountNumber);
    result = sqlite3_exec(db, query, NULL, NULL, NULL);
    if (result != SQLITE_OK)
    {
        printf("Error depositing money: %s\n", sqlite3_errmsg(db));
        return;
    }

    sprintf(query, "INSERT INTO transactions (user_id, account_number, transaction_type, amount) VALUES (%d, %d, 'DEPOSIT', %lf)", user_id, accountNumber, amount);
    result = sqlite3_exec(db, query, NULL, NULL, NULL);
    if (result != SQLITE_OK)
    {
        printf("Error inserting transaction: %s\n", sqlite3_errmsg(db));
        return;
    }
    printf("Deposit successful.\n");
    Success(db, user_id);
}
