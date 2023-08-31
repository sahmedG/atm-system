#include <stdio.h>
#include <stdbool.h>
#include <sqlite3.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/sha.h>
#include <openssl/evp.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>
#include <windows.h>
#include <winuser.h>
#include <curses.h>
#include <bcrypt.h>
#define MAX_LENGTH 200
#define PIPE_NAME_TEMPLATE "\\\\.\\pipe\\ATMNotification_%s"
#define CONNECTION_FILE "E:\\ascii-art\\atm-management\\atm-system\\connections.txt"

void authenticateUser(sqlite3 *db);
void depositMoney(sqlite3 *db, int user_id);
bool checkAllAccounts(sqlite3 *db, int user_id);
bool updateAccountInfo(sqlite3 *db, int accountId);
void withdrawMoney(sqlite3 *db, int user_id);
void createAccount(sqlite3 *db, int user_id);
void transferMoney(sqlite3 *db, int user_id);
void registerUser(sqlite3 *db);
void transferOwnership(sqlite3 *db, int user_id);
void initMenu(sqlite3 *db);
void mainMenu(sqlite3 *db, int user_id, char *username);
void checkOneAccount(sqlite3 *db,int user_id);
void makeTransactionsMenu(sqlite3 *db, int user_id, char *username);
void Gotoxy(int x, int y);
int deleteAccount(sqlite3 *db, int user_id);
void SendNotification(const char *targetUsername, const char *message);
void ReceiveNotifications(const char *username);
int main();