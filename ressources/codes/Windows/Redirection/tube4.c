#include <windows.h>
#include <stdio.h>
#include <tchar.h>
int main(int argc, char * argv[]) {
    DWORD dwRead;
    char chBuf[4096];
    printf("I am the child. My Pid and Tid: (%d, %d).\n",
    GetCurrentProcessId(), GetCurrentThreadId());
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);

    if (!ReadFile(hStdin, chBuf, 4096, &dwRead, NULL) || dwRead == 0) {
        printf("ReadFile Pipe échoue (%d)\n", GetLastError());
        CloseHandle(hStdin);
        ExitProcess(1);
    }
    printf("Message recu : %s , de taille %d \n", chBuf, dwRead);
    CloseHandle(hStdin);
    ExitProcess(0);
}