# CFLAGS = -Wall -Wextra -std=c99
LDFLAGS = -lsqlite3 -lcrypto

SRC = main.c register.c login.c createAccount.c updateAccount.c checkAllAccounts.c depositMoney.c withdrawMoney.c transferMoney.c transferOwnership.c checkOneaccount.c success.c transactoins.c
OBJ = $(SRC:.c=.o)

atm: $(OBJ)
	cc -o atm.exe $(OBJ) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ)
