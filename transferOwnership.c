#include "login.h"

void transferOwnership(sqlite3 *db, int user_id)
{
    char query[MAX_LENGTH];
    char update_owner[MAX_LENGTH];
    int accountNumber;
    char newOwner[MAX_LENGTH];
    sqlite3_stmt *stmt;

    printw("Enter account number: ");
    scanw("%d", &accountNumber);

    printw("Enter new owner username: ");
    getstr(newOwner);

    sprintf(query, "SELECT user_id FROM accounts WHERE account_number = %d", accountNumber);

    int result = sqlite3_prepare_v2(db, query, -1, &stmt, NULL);
    if (result != SQLITE_OK)
    {
        printw("Query error: %s\n", sqlite3_errmsg(db));
        refresh();
        printw("Press enter to go back.");
    }
    result = sqlite3_step(stmt);
    if (result == SQLITE_ROW)
    {
        int owner_id = sqlite3_column_int(stmt, 0);
        if (owner_id != user_id)
        {
            printw("Error: This account does not belong to you.\n");
            printw("Press enter to go back.");
            refresh();
            sqlite3_finalize(stmt);
            return;
        }
        else
        {
            sprintf(query, "SELECT user_id FROM users WHERE username = '%s'", newOwner);
            result = sqlite3_prepare_v2(db, query, -1, &stmt, NULL);
            if (result != SQLITE_OK)
            {
                printw("Authentication query error: %s\n", sqlite3_errmsg(db));
                sqlite3_finalize(stmt);
                printw("Press enter to go back.");
                return;
            }

            result = sqlite3_step(stmt);
            int new_user_id;
            new_user_id = sqlite3_column_int(stmt, 0);

            if (new_user_id == 0)
            {
                printw("This user dosen't exist.\n");
                printw("Press enter to go back.");
                sqlite3_finalize(stmt);
                return;
            }
            else
            {

                sprintf(update_owner, "UPDATE accounts SET user_id = %d WHERE account_number = %d", new_user_id, accountNumber);
                result = sqlite3_exec(db, update_owner, NULL, NULL, NULL);
                if (result != SQLITE_OK)
                {
                    printw("Error transferring ownership: %s\n", sqlite3_errmsg(db));
                    sqlite3_finalize(stmt);
                    return;
                }
                else if (result == SQLITE_OK)
                {
                    printw("Ownership transferred successfully!\n");
                    SendNotification(newOwner,"\nAccount transferred to you!\n");
                    sqlite3_finalize(stmt);
                    printw("Press enter to go back.");
                }
            }
        }
    }
    else
    {
        printw("Account not found.\n");
        printw("Press enter to go back.");
    }
}