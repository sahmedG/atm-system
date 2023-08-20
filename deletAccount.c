#include "login.h"

int deleteAccount(sqlite3 *db, int user_id)
{
    int accountNumber;
    printw("Enter account number to delete: ");
    scanw("%d", &accountNumber);

    char query[MAX_LENGTH];
    sprintf(query, "SELECT balance FROM accounts WHERE user_id = %d AND account_number = %d",user_id,accountNumber);

    sqlite3_stmt *stmt;
    int result = sqlite3_prepare_v2(db, query, -1, &stmt, NULL);
    if (result != SQLITE_OK)
    {
        return 1;
    }

    // Execute the query
    result = sqlite3_step(stmt);
    if (result == SQLITE_ROW)
    {
        double balance = sqlite3_column_double(stmt, 0);
        if (balance > 0)
        {
            return 2;
        }
        else
        {
            sprintf(query, "DELETE FROM transactions WHERE account_number = %d",accountNumber);
            result = sqlite3_prepare_v2(db, query, -1, &stmt, NULL);
            if (result != SQLITE_OK)
            {
                return 3;
            }

            result = sqlite3_step(stmt);
            sprintf(query, "DELETE FROM accounts WHERE user_id = %d AND account_number = %d",user_id,accountNumber);
            result = sqlite3_prepare_v2(db, query, -1, &stmt, NULL);
            if (result != SQLITE_OK)
            {
                return 3;
            }

            // Execute the DELETE query
            result = sqlite3_step(stmt);
            if (result == SQLITE_DONE)
            {
                return 0;
            }
            else
            {
                return 3;
            }
        }
    }
    sqlite3_finalize(stmt);
    return 3;
}