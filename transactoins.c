#include "login.h"
void makeTransactionsMenu(sqlite3 *db, int user_id, char *username)
{

    int choice;
    int highlight = 0;  // To highlight the currently selected option
    int numOptions = 4; // Number of menu options

    while (1)
    {
        clear();
        printw("Make Transactions\n");

        for (int i = 0; i < numOptions; i++)
        {
            if (i == highlight)
                attron(A_REVERSE); // Highlight the entire row
            printw("%d. ", i + 1);
            switch (i)
            {
            case 0:
                printw("Deposit Money\n");
                break;
            case 1:
                printw("Withdraw Money\n");
                break;
            case 2:
                printw("Transfer Money\n");
                break;
            case 3:
                printw("Back to Main Menu\n");
                break;
            }
            attroff(A_REVERSE); // Disable highlighting
        }

        choice = getch(); // Get user input

        switch (choice)
        {
        case KEY_UP:
            if (highlight > 0)
                highlight--;
            break;

        case KEY_DOWN:
            if (highlight < numOptions - 1)
                highlight++;
            break;

        case '\n': // Enter key
            clear();
            switch (highlight)
            {
            case 0:
                depositMoney(db, user_id);
                break;
            case 1:
                withdrawMoney(db, user_id);
                break;
            case 2:
                transferMoney(db, user_id);
                break;
            case 3:
                mainMenu(db, user_id,username);
                break;
            }
            refresh();
            getch(); // Wait for user input
            break;

        default:
            break;
        }
    }

    endwin(); // Clean up curses
    exit(1);
}
