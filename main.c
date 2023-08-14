#include <stdio.h>
#include <stdbool.h>
#include <sqlite3.h>
#include <string.h>

#include "login.h"
#define MAX_LENGTH 100

int main()
{
    sqlite3 *db;
    int result;

    result = sqlite3_open("atm.db", &db);
    if (result != SQLITE_OK)
    {
        printf("Database open error: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    int choice;
    char username[MAX_LENGTH];
    char password[MAX_LENGTH];
    int user_id;
    printf("1. Login\n");
    printf("2. Register\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (choice == 1)
    {
        printf("Enter username: ");
        scanf("%s", username);

        printf("Enter password: ");
        scanf("%s", password);

        // Authenticate user
        user_id = authenticateUser(db, username, password);

        if (user_id > 0)
        {
            while (true)
            {
                printf("\nATM Management System\n");
                printf("1. Create New Account\n");
                printf("2. Update Account Info\n");
                printf("3. Check All Accounts\n");
                printf("4. Deposit Money\n");
                printf("5. Withdraw Money\n");
                printf("7. Transfer Ownership\n");
                printf("8. Logout\n");
                printf("Enter your choice: ");
                scanf("%d", &choice);

                switch (choice)
                {
                case 1:
                {
                    // Create new account
                    char country[MAX_LENGTH];
                    char phoneNumber[MAX_LENGTH];
                    char accountType[MAX_LENGTH];
                    float balanceMoney[MAX_LENGTH];

                    printf("Enter country: ");
                    scanf("%s", country);

                    printf("Enter phone number: ");
                    scanf("%s", phoneNumber);

                    printf("Enter account type (savings/fixed01/fixed02/fixed03/current): ");
                    scanf("%s", accountType);

                    createAccount(db,username, country, phoneNumber, accountType);
                    break;
                }
                case 2:
                {
                    // Update account info
                    int accountNumber;
                    char newCountry[MAX_LENGTH];
                    char newPhoneNumber[MAX_LENGTH];

                    printf("Enter account number: ");
                    scanf("%d", &accountNumber);

                    printf("Enter new country: ");
                    scanf("%s", newCountry);

                    printf("Enter new phone number: ");
                    scanf("%s", newPhoneNumber);

                    updateAccountInfo(db, accountNumber, newCountry, newPhoneNumber);
                    break;
                }
                case 3:
                {
                    // Check all accounts
                    checkAllAccounts(db,user_id, username);
                    break;
                }
                case 4:
                {
                    int accountNumber;
                    float amount;

                    printf("Enter account number: ");
                    scanf("%d", &accountNumber);

                    printf("Enter amount to deposit: ");
                    scanf("%f", &amount);
                    printf("%f\n", amount);
                    depositMoney(db, accountNumber, amount);
                    break;
                }
                case 5:
                {
                    // Withdraw money
                    int accountNumber;
                    float amount;

                    printf("Enter account number: ");
                    scanf("%d", &accountNumber);

                    printf("Enter amount to withdraw: ");
                    scanf("%f", &amount);

                    withdrawMoney(db, accountNumber, amount);
                    break;
                }
                // case 6: {
                //     // Transfer account
                //     int sourceAccount, targetAccount;
                //     float amount;

                //     printf("Enter source account number: ");
                //     scanf("%d", &sourceAccount);

                //     printf("Enter target account number: ");
                //     scanf("%d", &targetAccount);

                //     printf("Enter amount to transfer: ");
                //     scanf("%f", &amount);

                //     transferMoney(db, sourceAccount, targetAccount, amount);
                //     break;
                // }
                case 7:
                {
                    // Transfer ownership
                    int accountNumber;
                    char newOwner[MAX_LENGTH];

                    printf("Enter account number: ");
                    scanf("%d", &accountNumber);

                    printf("Enter new owner username: ");
                    scanf("%s", newOwner);

                    transferOwnership(db, accountNumber, newOwner);
                    break;
                }
                case 8:
                    printf("Logged out.\n");
                    sqlite3_close(db);
                    return 0;
                default:
                    printf("Invalid choice\n");
                }
            }
        }
        else
        {
            printf("Authentication failed\n");
        }
    }
    else if (choice == 2)
    {
        printf("Enter new username: ");
        scanf("%s", username);

        printf("Enter new password: ");
        scanf("%s", password);

        // Register user
        registerUser(db, username, password);
    }

    sqlite3_close(db);
    return 0;
}
