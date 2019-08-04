#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#define BUFSIZE 4096
HANDLE FD[2];
int main() {
    // Créer un tube anonyme
    // Initialisation de SECURITY_ATTRIBUTES du pipe à créer.
    SECURITY_ATTRIBUTES saAttr;
    saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
    saAttr.bInheritHandle = TRUE; // les handles du pipe peuvent être hérités par les fils
    saAttr.lpSecurityDescriptor = NULL;
    if (!CreatePipe(&FD[0], &FD[1], &saAttr, 0)) {
        printf("CreatePipe a échoué (%d).\n", GetLastError());
        ExitProcess(1);
    } else
        printf("FD[0]= %d, FD[1]=%d\n", FD[0], FD[1]);
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));
    //convert the handle FD[0] to char[]
    char buf[10];
    sprintf(buf, "tube2.exe %d", FD[0]);
    // Créer un processus fils.
    if (!CreateProcess("tube2.exe", buf, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi)) {
        printf("CreateProcess a échoué (%d).\n", GetLastError());
        ExitProcess(1);
    }
    CloseHandle(FD[0]);
    DWORD dwWritten;
    CHAR chBuf[BUFSIZE] = "Bonjour du Pere au Fils\0";
    if (!WriteFile(FD[1], chBuf, strlen(chBuf) + 1, &dwWritten, NULL)) {
        printf("WriteFile pipe a échoué (%d).\n", GetLastError());
        return -1;
    } else
        printf("WriteFile pipe a réussi (%d).\n", dwWritten);
    CloseHandle(FD[1]);
    // Wait until child process exits.
    WaitForSingleObject(pi.hProcess, INFINITE );
    // Close process and thread handles.
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    ExitProcess(0);
    return 0;
}