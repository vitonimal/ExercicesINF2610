#include <windows.h>
#include <stdio.h>
#include <tchar.h>
int _tmain(int argc, char * argv[]) {
    DWORD dwRead;
    char chBuf[4096];
    printf("I am the child. My Pid and Tid: (%d, %d).\n",
        GetCurrentProcessId(), GetCurrentThreadId());
    HANDLE fd0 = (HANDLE) atoi(argv[1]);
    printf("argc = %d, argv[0]=%s, argv[1]=%s, fd0=%d\n", argc, argv[0], argv[1], fd0);
    if (!ReadFile(fd0, chBuf, 4096, &dwRead, NULL) || dwRead == 0) {
        printf("ReadFile Pipe échoue (%d)\n", GetLastError());
        CloseHandle(fd0);
        ExitProcess(1);
    }
    printf("Message recu : %s , de taille %d \n", chBuf, dwRead);
    CloseHandle(fd0);
    ExitProcess(0);
}