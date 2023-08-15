#include <stdio.h>
#include <stdbool.h>
#include <sqlite3.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/sha.h>
#define MAX_LENGTH 200
bool authenticateUser(sqlite3 *db);
void depositMoney(sqlite3 *db, int user_id);
void checkAllAccounts(sqlite3 *db,int user_id);
void updateAccountInfo(sqlite3 *db, int accountId);
void withdrawMoney(sqlite3 *db, int user_id);
void createAccount(sqlite3 *db, int user_id);
void transferMoney(sqlite3 *db, int user_id);
void registerUser(sqlite3 *db);
void transferOwnership(sqlite3 *db,int user_id);
void success(sqlite3 *db,int user_id);
void initMenu(sqlite3 *db);
void mainMenu(sqlite3 *db,int user_id);
void checkOneAccount(sqlite3 *db, int user_id);
void Success(sqlite3 *db, int user_id);
void makeTransactionsMenu(sqlite3 *db,int user_id);
void Rectangle(int x,int y,int l,int b);
void Gotoxy(int x,int y);