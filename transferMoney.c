#include "login.h"

void transferMoney(sqlite3 *db, int user_id)
{
    clear();
    int fromAccountNumber, toAccountNumber;
    float amount;

    printw("Transfer Money\n");
    printw("Enter source account number: ");
    scanw("%d", &fromAccountNumber);

    printw("Enter destination account number: ");
    scanw("%d", &toAccountNumber);

    printw("Enter the amount you wish to transfer: $");
    scanw("%f", &amount);

    char query[MAX_LENGTH];
    sqlite3_stmt *stmt;

    sprintf(query, "SELECT balance, account_type FROM accounts WHERE account_number = %d AND user_id = %d", fromAccountNumber, user_id);
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
                // Check if destination account exists
                sprintf(query, "SELECT COUNT(*) FROM accounts WHERE account_number = %d", toAccountNumber);
                result = sqlite3_prepare_v2(db, query, -1, &stmt, NULL);
                if (result != SQLITE_OK)
                {
                    printw("Query error: %s\n", sqlite3_errmsg(db));
                    sqlite3_finalize(stmt);
                    refresh();
                    getch();
                    return;
                }

                result = sqlite3_step(stmt);
                if (result == SQLITE_ROW && sqlite3_column_int(stmt, 0) > 0)
                {
                    // Destination account exists
                    // Transfer money logic here

                    // Update 'from' account balance
                    sprintf(query, "UPDATE accounts SET balance = balance - %.2f WHERE account_number = %d AND user_id = %d", amount, fromAccountNumber, user_id);
                    result = sqlite3_exec(db, query, NULL, NULL, NULL);
                    if (result != SQLITE_OK)
                    {
                        printw("Error updating balance: %s\n", sqlite3_errmsg(db));
                        sqlite3_finalize(stmt);
                        refresh();
                        getch();
                        return;
                    }

                    // Update 'to' account balance
                    sprintf(query, "UPDATE accounts SET balance = balance + %.2f WHERE account_number = %d AND user_id = %d", amount, toAccountNumber, user_id);
                    result = sqlite3_exec(db, query, NULL, NULL, NULL);
                    if (result != SQLITE_OK)
                    {
                        printw("Error updating balance: %s\n", sqlite3_errmsg(db));
                        sqlite3_finalize(stmt);
                        refresh();
                        getch();
                        return;
                    }

                    sprintf(query, "INSERT INTO transactions (user_id, account_number, transaction_type, amount) VALUES (%d, %d, 'Transfer', %lf)", user_id, fromAccountNumber, amount);
                    result = sqlite3_exec(db, query, NULL, NULL, NULL);
                    if (result != SQLITE_OK)
                    {
                        printw("Error inserting transaction: %s\n", sqlite3_errmsg(db));
                        refresh();
                        getch();
                        return;
                    }

                    sprintf(query, "INSERT INTO transactions (user_id, account_number, transaction_type, amount) VALUES (%d, %d, 'Transfer', %lf)", user_id, toAccountNumber, amount);
                    result = sqlite3_exec(db, query, NULL, NULL, NULL);
                    if (result != SQLITE_OK)
                    {
                        printw("Error inserting transaction: %s\n", sqlite3_errmsg(db));
                        refresh();
                        getch();
                        return;
                    }

                    printw("Money transferred successfully!\n");
                }
                else
                {
                    printw("Destination account does not exist.\n");
                }
            }
            else
            {
                printw("Insufficient balance in the source account.\n");
            }
        }
        else
        {
            printw("Cannot transfer from this type of account.\n");
        }
    }
    else
    {
        printw("Source account not found.\n");
    }

    sqlite3_finalize(stmt);
    refresh();
}
