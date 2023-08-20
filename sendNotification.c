#include "login.h"

void SendNotification(const char *targetUsername, const char *message) {
    char pipeName[256];
    _snprintf(pipeName, sizeof(pipeName), PIPE_NAME_TEMPLATE, targetUsername);

    HANDLE hPipe = CreateFile(
        pipeName,
        GENERIC_WRITE,
        0,
        NULL,
        OPEN_EXISTING,
        0,
        NULL
    );

    if (hPipe != INVALID_HANDLE_VALUE) {
        DWORD bytesWritten;
        WriteFile(hPipe, message, strlen(message), &bytesWritten, NULL);
        CloseHandle(hPipe);
    } else {
        // Handle pipe creation error
    }
}