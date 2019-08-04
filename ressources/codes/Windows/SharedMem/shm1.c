#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <tchar.h>
#define BUF_SIZE 256
TCHAR szName[] = TEXT("MyFileMappingObject");
TCHAR szMsg[] = TEXT("Message from first process.");
int main() {
    HANDLE hMapFile;
    LPCTSTR pBuf;
    hMapFile = CreateFileMapping(
        INVALID_HANDLE_VALUE, // use paging file
        NULL, // default security
        PAGE_READWRITE, // read/write access
        0, // max. object size
        BUF_SIZE, // buffer size
        szName
    ); // name of mapping object
    if (hMapFile == NULL) {
        printf(TEXT("Could not create file mapping object (%d).\n"), GetLastError());
        return 1;
    }
    pBuf = (LPTSTR) MapViewOfFile(hMapFile, // handle to map object
            FILE_MAP_ALL_ACCESS, // read/write permission
            0, 0, BUF_SIZE);
    if (pBuf == NULL) {
        printf(TEXT("Could not map view of file (%d).\n"), GetLastError());
        CloseHandle(hMapFile);
        return 1;
    }
    CopyMemory((PVOID)pBuf, szMsg, (_tcslen(szMsg) * sizeof(TCHAR)));
    _getch(); // Gets a character from the console without echo
    UnmapViewOfFile(pBuf);
    CloseHandle(hMapFile);
    return 0;
}