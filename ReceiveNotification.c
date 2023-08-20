#include "login.h"

void ReceiveNotifications(const char *username) {
    char pipeName[256];
    sprintf(pipeName, PIPE_NAME_TEMPLATE, username);

    HANDLE hPipe = CreateNamedPipe(
        pipeName,
        PIPE_ACCESS_INBOUND,
        PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
        1,
        0,
        0,
        NMPWAIT_USE_DEFAULT_WAIT,
        NULL
    );

    if (hPipe != INVALID_HANDLE_VALUE) {
        while (1) {
            ConnectNamedPipe(hPipe, NULL);
            
            char buffer[256];
            DWORD bytesRead;
            ReadFile(hPipe, buffer, sizeof(buffer), &bytesRead, NULL);
            buffer[bytesRead] = '\0';

            // Handle the received notification as needed
            printf("Received Notification: %s\n", buffer);

            DisconnectNamedPipe(hPipe);
        }
        CloseHandle(hPipe);
    } else {
        // Handle pipe creation error
    }
}
