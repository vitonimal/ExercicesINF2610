/* parent.c */
#include <Windows.h>
#include <stdio.h>
void main()
{
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    DWORD status ; // used to receive the exit status
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));
    if(!CreateProcess(
        "child.exe", //name or path of the executable
        NULL, // no command line.
        NULL, // Process handle not inheritable.
        NULL, // Thread handle not inheritable.
        FALSE, // child does not inherit the inheritable handles of his father.
        0, // No new console, etc.
        NULL, // Same as the parent's environment block.
        NULL, // Same as the parent's starting directory.
        &si, // Pointer to STARTUPINFO structure.
        &pi ) // Pointer to PROCESS_INFORMATION structure.
    )
    {
        printf("CreateProcess failed (%d).\n", GetLastError()); ExitProcess(1);
    }
    WaitForSingleObject(pi.hProcess, INFINITE);
    if(GetExitCodeProcess(pi.hProcess, &status)) {
    printf("I am the father. My child [%d:%d] has terminated with (%d).\n",
    pi.dwProcessId, pi.dwThreadId, status);
    } else { printf("GetExitCodeProcess failed (%d).\n", GetLastError()); }
    CloseHandle( pi.hProcess );
    CloseHandle( pi.hThread );
    printf("I am the father. Going to terminate.\n");
    ExitProcess(0);
}