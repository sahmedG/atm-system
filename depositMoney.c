#include "login.h"
void depositMoney(sqlite3 *db, int accountNumber, float amount) {
    printf("%f\n", amount);
    char query[MAX_LENGTH];
    sprintf(query, "UPDATE accounts SET balance = balance + %0.2f WHERE account_number = %d;",
            amount, accountNumber);
    printf("OutsPut is (%s)\n", query);
    int result = sqlite3_exec(db, query, NULL, NULL, NULL);
    if (result != SQLITE_OK) {
        printf("Error depositing money: %s\n", sqlite3_errmsg(db));
    } else {
        printf("Money deposited successfully!\n");
    }
}
