#include "login.h"
void checkOneAccount(sqlite3 *db, int user_id)
{
    sqlite3_stmt *stmt;
    int accountNumber;
    printf("Enter account number: ");
    scanf("%d", &accountNumber);

    char query[MAX_LENGTH];
    sprintf(query, "SELECT account_type FROM accounts WHERE account_number = %d", accountNumber);

    
    int result = sqlite3_prepare_v2(db, query, -1, &stmt, NULL);
    if (result != SQLITE_OK)
    {
        printf("Query error: %s\n", sqlite3_errmsg(db));
        exit(0);
    }

    result = sqlite3_step(stmt);
    if (result == SQLITE_ROW)
    {
        const char *accountType = (const char *)sqlite3_column_text(stmt, 0);

        printf("Account Type: %s\n", accountType);

        if (strcmp(accountType, "fixed01") == 0)
        {

            // Query transactions for this account
            sprintf(query, "SELECT amount, transaction_date FROM transactions WHERE account_number = %d", accountNumber);
          
            result = sqlite3_prepare_v2(db, query, -1, &stmt, NULL);
            if (result != SQLITE_OK)
            {
                printf("Query error: %s\n", sqlite3_errmsg(db));
                exit(0);
            }

            float totalInterest = 0.0;

            while (sqlite3_step(stmt) == SQLITE_ROW)
            {
                float amount = sqlite3_column_double(stmt, 0);
                const char *depositDate = (const char *)sqlite3_column_text(stmt, 1);
                printf("Acco : %d\n", amount);
                // Calculate interest based on account type and amount
                float interestRate = 0.0;

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

                float interest = (amount * interestRate) / 100;
                printf("You will get $%.2f as interest on day %s of every month\n", interest, depositDate);

                totalInterest += interest;
            }

            if (totalInterest == 0.0)
            {
                printf("No interest information available.\n");
            }
            else
            {
                printf("Total interest acquired: $%.2f\n", totalInterest);
            }
        }
        else if (strcmp(accountType, "current") == 0)
        {
            printf("You will not get interests because the account is of type current\n");
        }
        else
        {
            printf("Invalid account type.\n");
        }
    }
    else
    {
        printf("Account not found.\n");
    }

    sqlite3_finalize(stmt);
    Success(db, user_id);
}
