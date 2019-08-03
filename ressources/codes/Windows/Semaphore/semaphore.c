#include <windows.h>
#include <stdio.h>

int glob=100;
HANDLE hSem;
DWORD WINAPI FuncThread1(LPVOID arg)
{
    int i;
    for(i=0; i<=10; i++) {
        WaitForSingleObject(hSem, INFINITE); // P(hSem)
        glob = glob+10;
        printf("ici thread %p : valeur de glob = %d \n",*((HANDLE*)arg), glob);
        ReleaseSemaphore(hSem, 1, NULL); // V(hSem)
    }
    return 0;
}

DWORD WINAPI FuncThread2(LPVOID arg)
{
    for(int i=0; i<=10; i++) {
    WaitForSingleObject(hSem, INFINITE); // P(hSem)
    glob = glob-10;
    printf("ici thread %p : valeur de glob = %d \n",*((HANDLE*)arg), glob);
    ReleaseSemaphore(hSem, 1, NULL); // V(hSem)
    }
    return 0;
}

int main()
{
    HANDLE th[2];
    DWORD tid1, tid2;
    hSem = CreateSemaphore(NULL,1,1,NULL); // Semaphore hSem=1
    if (hSem == NULL) {
        printf("CreateSemaphore error: %d\n", GetLastError());
        return -1;
    }
    th[0] = CreateThread(NULL, 0, FuncThread1, (LPVOID) &th[0], 0, &tid1);
    th[1] = CreateThread(NULL, 0, FuncThread2, (LPVOID) &th[1], 0, &tid2);
    WaitForMultipleObjects(2, th,TRUE,INFINITE);
    printf("Fin des threads %d , %d \n", th[0], th[1]);
    CloseHandle(hSem);
    CloseHandle(th[0]);
    CloseHandle(th[1]);
    return 0;
}