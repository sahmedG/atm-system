#include "login.h"

void initMenu(sqlite3 *db)
{
    int choice;
    int highlight = 0;  // To highlight the currently selected option
    int numOptions = 3; // Number of menu options
    while (1)
    {
        clear();
        // Main menu
        printw("ATM Management System\n");

        for (int i = 0; i < numOptions; i++)
        {
            if (i == highlight)
                attron(A_REVERSE); // Highlight the entire row
            printw("%d. ", i + 1);
            switch (i)
            {
            case 0:
                printw("Login\n");
                break;
            case 1:
                printw("Register\n");
                break;
            case 2:
                printw("Exit\n");
                break;
            }
            attroff(A_REVERSE); // Disable highlighting
        }
        choice = getch();
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
                authenticateUser(db);
                break;
            case 1:
                registerUser(db);
                break;
            case 2:
                endwin(); // Clean up curses
                sqlite3_close(db);
                exit(1);
            }
            refresh();
            getch(); // Wait for user input
            break;

        default:
            break;
        }
    }
    endwin(); // Clean up curses
}