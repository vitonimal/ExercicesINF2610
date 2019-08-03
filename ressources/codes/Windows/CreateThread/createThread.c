#include <windows.h>
#include <stdio.h>

DWORD WINAPI ThreadAction( LPVOID lpParam ) 
{ 
    char* message = (char*) lpParam;
    printf("%s", message);
    return 0; 
} 

void main () {

    HANDLE threadHandle = CreateThread(NULL, 0, ThreadAction, "Hello Win32!", 0, NULL);
    WaitForSingleObject(threadHandle, INFINITE);
    
}