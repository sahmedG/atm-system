#include "login.h"

int main()
{

  initscr();            // Initialize the curses library
  cbreak();             // Enable line buffering
  keypad(stdscr, TRUE); // Enable special keys

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
}