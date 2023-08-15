#include "login.h"

void updateAccountInfo(sqlite3 *db, int user_id)
{
    char query[MAX_LENGTH];
    int accountNumber;
    char newCountry[MAX_LENGTH];
    char newPhoneNumber[MAX_LENGTH];

    printf("Enter account number: ");
    scanf("%d", &accountNumber);

    printf("Enter new country: ");
    scanf("%s", newCountry);

    printf("Enter new phone number: ");
    scanf("%s", newPhoneNumber);

    sprintf(query, "UPDATE accounts SET country = '%s', phone_number = '%s' WHERE account_number = %d",
            newCountry, newPhoneNumber, accountNumber);

    int result = sqlite3_exec(db, query, NULL, NULL, NULL);
    if (result != SQLITE_OK)
    {
        printf("Error updating account info: %s\n", sqlite3_errmsg(db));
    }
    else
    {
        printf("Account info updated successfully!\n");
    }
    Success(db,user_id);
}
