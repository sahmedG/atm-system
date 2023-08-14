#include <stdio.h>
#include <stdbool.h>
#include <sqlite3.h>
#include <string.h>
#define MAX_LENGTH 200
bool authenticateUser(sqlite3 *db, const char *username, const char *password);
void depositMoney(sqlite3 *db, int accountNumber, float amount);
void checkAllAccounts(sqlite3 *db, int *userid, const char *username);
void updateAccountInfo(sqlite3 *db, int accountId, const char *country, const char *phoneNumber);
void withdrawMoney(sqlite3 *db, int accountNumber, float amount);
void createAccount(sqlite3 *db, const char *user_name, const char *country, const char *phoneNumber, const char *accountType);
void transferMoney(sqlite3 *db, const char *username);
void registerUser(sqlite3 *db, const char *username, const char *password);
void transferOwnership(sqlite3 *db, int accountNumber, const char *newOwner);
