#include "login.h"

bool updateAccountInfo(sqlite3 *db, int user_id)
{
    char query[MAX_LENGTH];
    int accountNumber;
    char newCountry[MAX_LENGTH];
    char newPhoneNumber[MAX_LENGTH];

    printw("Enter account number: ");
    scanw("%d", &accountNumber);

    printw("Enter new country: ");
    getstr(newCountry);

    printw("Enter new phone number: ");
    getstr(newPhoneNumber);

    sprintf(query, "UPDATE accounts SET country = '%s', phone_number = '%s' WHERE account_number = %d AND user_id =%d",
            newCountry, newPhoneNumber, accountNumber, user_id);

    int result = sqlite3_exec(db, query, NULL, NULL, NULL);
    if (result != SQLITE_OK || sqlite3_changes(db) == 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}
