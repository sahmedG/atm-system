CFLAGS = -Wall -Wextra -std=c99 -D_WIN32_WINNT=0x0601
LDFLAGS = -lsqlite3 -lcrypto -luser32 -I. -L/ascii-art/PDCurses-3.9/wincon -lpdcurses 
SRC = main.c initial_menu.c program_menu.c register.c login.c createAccount.c updateAccount.c checkAllAccounts.c depositMoney.c withdrawMoney.c transferMoney.c transferOwnership.c checkOneaccount.c transactoins.c deletAccount.c ReceiveNotification.c sendNotification.c
OBJ = $(SRC:.c=.o)

atm: $(OBJ)
	cc -o atm.exe $(OBJ) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	del /f $(OBJ) atm.exe
