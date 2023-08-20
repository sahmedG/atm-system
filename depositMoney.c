#include "login.h"
void depositMoney(sqlite3 *db, int user_id)
{
    char query[MAX_LENGTH];
    int accountNumber;
    float amount;
    int result;

    sqlite3_stmt *stmt;
    printw("Enter account number: ");
    scanw("%d", &accountNumber);
    printw("Enter amount to deposit: $");
    scanw("%f", &amount);

    sprintf(query, "SELECT count(*) FROM accounts WHERE account_number = %d AND user_id = %d", accountNumber, user_id),

        result = sqlite3_prepare_v2(db, query, -1, &stmt, NULL);
    if (result != SQLITE_OK)
    {
        printw("Error checking account: %s\n", sqlite3_errmsg(db));
        return;
    }

    result = sqlite3_step(stmt);
    if (result == SQLITE_ROW)
    {
        int count = sqlite3_column_int(stmt, 0);
        if (count == 0)
        {
            printw("\nAccount does not exist!\n");
            sqlite3_finalize(stmt);
            return;
        }
    }
    else
    {
        printw("Error getting row from database.\n");
        sqlite3_finalize(stmt);
        return;
    }
    sprintf(query, "UPDATE accounts SET balance = balance + %0.2f WHERE account_number = %d;", amount, accountNumber);
    result = sqlite3_exec(db, query, NULL, NULL, NULL);
    if (result != SQLITE_OK)
    {
        printw("Error depositing money: %s\n", sqlite3_errmsg(db));
        return;
    }

    sprintf(query, "INSERT INTO transactions (user_id, account_number, transaction_type, amount) VALUES (%d, %d, 'DEPOSIT', %lf)", user_id, accountNumber, amount);
    result = sqlite3_exec(db, query, NULL, NULL, NULL);
    if (result != SQLITE_OK)
    {
        printw("Error inserting transaction: %s\n", sqlite3_errmsg(db));
        return;
    }
    printw("Deposit successful.\n");
    sqlite3_finalize(stmt);
    return;
}
