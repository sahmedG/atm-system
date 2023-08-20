#include "login.h"

void checkOneAccount(sqlite3 *db,int user_id)
{
    int accountNumber;
    printw("Enter account number: ");
    scanw("%d", &accountNumber);

    char query[MAX_LENGTH];
    sprintf(query, "SELECT accounts.account_type, accounts.balance, transactions.transaction_date FROM accounts INNER JOIN transactions on transactions.account_number = accounts.account_number WHERE transaction_type = 'DEPOSIT' AND accounts.account_number = %d AND accounts.user_id = %d", accountNumber,user_id);

    sqlite3_stmt *stmt;
    int result = sqlite3_prepare_v2(db, query, -1, &stmt, NULL);
    if (result != SQLITE_OK)
    {
        printw("Query error: %s\n", sqlite3_errmsg(db));
        return;
    }

    result = sqlite3_step(stmt);
    if (result == SQLITE_ROW)
    {
        const char *accountType = (const char *)sqlite3_column_text(stmt, 0);
        const char *depositDate = (const char *)sqlite3_column_text(stmt, 2);
        float balance = sqlite3_column_double(stmt, 1);

        printw("Account Type: %s\n", accountType);
        printw("Deposit Date: %s\n", depositDate);
        printw("Balance: $%.2f\n", balance);

        if (strcmp(accountType, "savings") == 0 ||
            strcmp(accountType, "fixed01") == 0 ||
            strcmp(accountType, "fixed02") == 0 ||
            strcmp(accountType, "fixed03") == 0)
        {

            // Calculate interest based on deposit date, balance, and current year/month
            int depositMonth, depositDay, depositYear;
            sscanf(depositDate, "%d-%d-%d", &depositYear, &depositMonth, &depositDay);

            // Get the current year and month from the system
            time_t currentTime = time(NULL);
            struct tm *localTime = localtime(&currentTime);
            int currentYear = localTime->tm_year + 1900; // Years since 1900
            int currentMonth = localTime->tm_mon + 1;    // Months are 0-based

            float totalInterest = 0.0;
            float interestForMonth = 0.0;
            while (depositYear < currentYear || (depositYear == currentYear && depositMonth <= currentMonth))
            {
                // Calculate interest for this month and add it to totalInterest
                interestForMonth = (balance * 0.07) / 12; // Monthly interest for savings
                totalInterest += interestForMonth;

                // Move to the next month
                depositMonth++;
                if (depositMonth > 12)
                {
                    depositMonth = 1;
                    depositYear++;
                }
            }

            printw("You will get $%.02f as interest on day %d of every month\n", interestForMonth, depositDay);
            printw("Total interest acquired: $%.2f\n", totalInterest);
        }
        else if (strcmp(accountType, "current") == 0)
        {
            printw("You will not get interests because the account is of type current\n");
        }
        else
        {
            printw("Invalid account type.\n");
        }
    }
    else
    {
        printw("Account not found or account has no details yet.\n");
    }

    sqlite3_finalize(stmt); // Don't forget to finalize the statement
    printw("Press enter to go back\n");
}
