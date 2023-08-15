#include "login.h"
void makeTransactionsMenu(sqlite3 *db, int user_id) {
    int choice;
    do {
        system("cls");
        printf("Make Transactions\n");
        printf("1. Deposit Money\n");
        printf("2. Withdraw Money\n");
        printf("3. Transfer Money\n");
        printf("0. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();  // Consume the newline character

        switch (choice) {
            case 1:
                depositMoney(db, user_id);
                break;
            case 2:
                withdrawMoney(db, user_id);
                break;
            case 3:
                transferMoney(db, user_id);
                break;
            case 0:
                break;
            default:
                printf("Invalid choice.\n");
        }

        if (choice != 0) {
            printf("Press Enter to return to the Make Transactions menu or type 'exit' to go back to the main menu: ");
            char input[MAX_LENGTH];
            fgets(input, sizeof(input), stdin);
            input[strcspn(input, "\n")] = 0;
            if (strcmp(input, "exit") == 0) {
                choice = 0;
            }
        }
    } while (choice != 0);
}