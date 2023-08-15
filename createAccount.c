#include "login.h"

void createAccount(sqlite3 *db, int user_id)
{
    float initialBalance = 0.0;
    float interestRate = 0.0;
    char query[MAX_LENGTH];
    char country[MAX_LENGTH];
    char phoneNumber[MAX_LENGTH];
    char accountType[MAX_LENGTH];
    float balanceMoney[MAX_LENGTH];

    printf("Enter country: ");
    scanf("%s", country);

    printf("Enter phone number: ");
    scanf("%s", phoneNumber);

    printf(
        "Enter account type (savings/fixed01/fixed02/fixed03/current): ");
    scanf("%s", accountType);

    if (strcmp(accountType, "savings") == 0)
    {
        interestRate = 0.07;
    }
    else if (strcmp(accountType, "fixed01") == 0)
    {
        interestRate = 0.04;
    }
    else if (strcmp(accountType, "fixed02") == 0)
    {
        interestRate = 0.05;
    }
    else if (strcmp(accountType, "fixed03") == 0)
    {
        interestRate = 0.08;
    }
    else if (strcmp(accountType, "current") == 0)
    {
        interestRate = 0.0;
        printf("You will not get interests because the account is of type current.\n");
    }
    else
    {
        printf("Invalid account type.\n");
        return;
    }

    sprintf(query, "INSERT INTO accounts (user_id,country, phone_number, balance, interest_rate, account_type) "
                   "VALUES ( '%i','%s', '%s', %.2f, %.4f, '%s')",
            user_id, country, phoneNumber, initialBalance, interestRate, accountType);

    int result = sqlite3_exec(db, query, NULL, NULL, NULL);
    if (result != SQLITE_OK)
    {
        printf("Error creating account: %s\n", sqlite3_errmsg(db));
    }
    else
    {
        printf("Account created successfully!\n");
    }
    Success(db,user_id);
}
