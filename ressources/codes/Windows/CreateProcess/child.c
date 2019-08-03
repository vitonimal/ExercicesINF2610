/* child.c */
#include <windows.h>
#include <stdio.h>
#include <tchar.h>
void main()
{
    printf("I am the child. My Pid and Tid: (%d, %d).\n",
    GetCurrentProcessId(), GetCurrentThreadId());
    printf( "I am the child. Going to sleep for 5 seconds. \n");
    Sleep(5000);
    ExitProcess(10); // exit code
}