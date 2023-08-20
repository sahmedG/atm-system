#include "login.h"

int isExistingConnectionOpen()
{
    FILE *file = fopen(CONNECTION_FILE, "r");
    if (file)
    {
        fclose(file);
        return 1; // Existing connection found
    }
    return 0; // No existing connection
}

void mainMenu(sqlite3 *db, int user_id, char *username)
{

    int choice;
    while (1)
    {
        clear();
        printw("======= ATM Management System =======\n");
        printw("\n\tWelcome to the Main Menu %s!\n", username);
        printw("1. Create a new account\n");
        printw("2. Update account information\n");
        printw("3. Check account details\n");
        printw("4. Make Transaction\n");
        printw("5. Check list of owned account\n");
        printw("6. Transfer Ownership\n");
        printw("7. Delete account\n");
        printw("8. Exit\n");
        refresh();

        choice = getch();

        switch (choice)
        {
        case '1':
            clear();
            createAccount(db, user_id);
            refresh();
            getch();
            break;

        case '2':
            clear();
            if (updateAccountInfo(db, user_id))
            {
                printw("Account info updated successfully!\n");
            }
            else
            {
                printw("No records were updated. Please check the account number and ownership.\n");
            };
            refresh();
            printw("Press enter to go back\n");
            getch();
            break;

        case '3':
            clear();
            checkOneAccount(db, user_id);
            refresh();
            getch();
            break;

        case '4':
            clear();
            makeTransactionsMenu(db, user_id, username);
            refresh();
            getch();
            break;

        case '5':
            clear();
            if (checkAllAccounts(db, user_id))
            {
                printw("Press enter to go back\n");
            }
            else
            {
                printw("Authentication query error: %s\n", sqlite3_errmsg(db));
            };
            refresh();
            getch();
            break;

        case '6':
            clear();
            transferOwnership(db, user_id);
            refresh();
            getch();
            break;

        case '7':
            clear();
            int err_code;
            err_code = deleteAccount(db, user_id);
            switch (err_code)
            {
            case 0:
                printw("Account was deleted!\n");
                break;
            case 3:
                printw("Account not found!\n");
                break;
            case 2:
                printw("Account balance is greater than zero. Please transfer the amount to another account before deleting.\n");
                break;
            default:
                printw("Error excuting the sql!\n");
                break;
            };
            refresh();
            printw("Press enter to go back\n");
            getch();
            break;

        case '8':
            sqlite3_close(db);
            endwin();
            exit(0); // Use 0 for successful exit
        default:
            printw("Invalid choice. Choose between '1' and '8'.\n");
            refresh();
            getch();
            break;
        }
    }

    ReceiveNotifications(username);
    endwin(); // Clean up curses
    exit(1);
}

void recordConnection()
{
    FILE *file = fopen(CONNECTION_FILE, "w");
    if (file)
    {
        fclose(file);
    }
    else
    {
        perror("Failed to open file");
    }
}
