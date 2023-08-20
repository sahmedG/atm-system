#include "login.h"

void withdrawMoney(sqlite3 *db, int user_id)
{
    char query[MAX_LENGTH];
    int accountNumber;
    float amount;

    clear();
    printw("Withdraw Money\n");
    printw("Enter account number: ");
    scanw("%d", &accountNumber);

    printw("Enter amount to withdraw: $");
    scanw("%f", &amount);

    sprintf(query, "SELECT balance, account_type FROM accounts WHERE account_number = %d AND user_id = %d", accountNumber, user_id);
    sqlite3_stmt *stmt;
    int result = sqlite3_prepare_v2(db, query, -1, &stmt, NULL);
    if (result != SQLITE_OK)
    {
        printw("Query error: %s\n", sqlite3_errmsg(db));
        refresh();
        getch();
        return;
    }

    result = sqlite3_step(stmt);
    if (result == SQLITE_ROW)
    {
        float balance = sqlite3_column_double(stmt, 0);
        const char *accountType = (const char *)sqlite3_column_text(stmt, 1);

        if (strcmp(accountType, "savings") == 0 || strcmp(accountType, "current") == 0)
        {
            if (amount <= balance)
            {
                sprintf(query, "UPDATE accounts SET balance = balance - %.2f WHERE account_number = %d AND user_id = %d",
                        amount, accountNumber, user_id);

                result = sqlite3_exec(db, query, NULL, NULL, NULL);
                if (result == SQLITE_OK)
                {
                    sprintf(query, "INSERT INTO transactions (user_id, account_number, transaction_type, amount) VALUES (%d, %d, 'WITHDRAW', %lf)", user_id, accountNumber, amount);
                    result = sqlite3_exec(db, query, NULL, NULL, NULL);
                    if (result != SQLITE_OK)
                    {
                        printw("Error inserting transaction: %s\n", sqlite3_errmsg(db));
                        refresh();
                        getch();
                        return;
                    }
                    printw("Money withdrawn successfully!\n");
                }
                else
                {
                    printw("Error withdrawing money: %s\n", sqlite3_errmsg(db));
                }
            }
            else
            {
                printw("Insufficient balance.\n");
            }
        }
        else
        {
            printw("Cannot withdraw from this type of account.\n");
        }
    }
    else
    {
        printw("Account not found.\n");
    }

    sqlite3_finalize(stmt);
    refresh();
}
