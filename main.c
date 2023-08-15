#include "login.h"

void initMenu(sqlite3 *db)
{
  int r = 0;
  int choice;
  system("cls");
  printf("\n\n\t\t======= ATM =======\n");
  printf("\n\t\t-->> Feel free to login / register :\n");
  printf("\n\t\t[1]- login\n");
  printf("\n\t\t[2]- register\n");
  printf("\n\t\t[3]- exit\n");
  while (!r)
  {
    scanf("%d", &choice);

    char username[MAX_LENGTH];
    char password[MAX_LENGTH];
    int user_id;
    switch (choice)
    {
    case 1:
      // Authenticate user
      user_id = authenticateUser(db);
      break;
    case 2:
      // Register user
      registerUser(db);
      r = 1;
      break;
    case 3:
      exit(1);
      break;
    default:
      printf("Insert a valid operation!\n");
    }
  }
};

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
  initMenu(db);
  return 0;
};
void mainMenu(sqlite3 *db, int user_id)
{

  int choice;
  if (user_id > 0)
  {
    do
    {
      system("cls");
      printf("\n\n\t\t======= ATM Management System =======\n\n");
      printf("\n\t\t[1]- Create a new account\n");
      printf("\n\t\t[2]- Update account information\n");
      printf("\n\t\t[3]- Check account details\n");
      printf("\n\t\t[4]- Make Transaction\n");
      printf("\n\t\t[5]- Check list of owned account\n");
      printf("\n\t\t[6]. Transfer Ownership\n");
      printf("\n\t\t[7]. Delete account\n");
      printf("\n\t\t[8]. Exit\n");
      printf("Enter your choice: ");
      scanf("%d", &choice);

      switch (choice)
      {
      case 1:
      {
        // Create new account
        createAccount(db, user_id);
        break;
      }
      case 2:
      {
        // Update account info
        updateAccountInfo(db, user_id);
        break;
      }
      case 3:
      {
        // Check one account
        checkOneAccount(db, user_id);
        break;
      }
      case 4:
      {
        // Multiple transactions
        makeTransactionsMenu(db,user_id);
      }
      case 5:
      {
        // check all acounts
        checkAllAccounts(db, user_id);
        break;
      }
      case 6:
      {
        // Transfer ownership
        transferOwnership(db, user_id);
        break;
      }
      case 7:
      {
        // Delete account
      }
      case 8:
        sqlite3_close(db);
        exit(1);
      default:
        printf("Invalid choice\n");
      }
    } while (choice != 8);
  }
  else
  {
    printf("Authentication failed\n");
  }
}
