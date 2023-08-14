#include <stdio.h>
#include <stdbool.h>
#include <sqlite3.h>
#include <string.h>
#define MAX_LENGTH 200

void createAccount(sqlite3 *db, const char *user_name, const char *country, const char *phoneNumber, const char *accountType)
{
    float initialBalance = 0.0;
    float interestRate = 0.0;
    int user_id;
    char query[MAX_LENGTH];

    sprintf(query, "SELECT user_id FROM users WHERE username = '%s'", user_name);
    sqlite3_stmt *stmt;
    int result = sqlite3_prepare_v2(db, query, -1, &stmt, NULL);
    if (result != SQLITE_OK)
    {
        printf("Query error: %s\n", sqlite3_errmsg(db));
        return;
    };
    result = sqlite3_step(stmt);
    if (result == SQLITE_ROW)
    {
        user_id = sqlite3_column_int(stmt, 0);
    };
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

     result = sqlite3_exec(db, query, NULL, NULL, NULL);
    if (result != SQLITE_OK)
    {
        printf("Error creating account: %s\n", sqlite3_errmsg(db));
    }
    else
    {
        printf("Account created successfully!\n");
    }
}
