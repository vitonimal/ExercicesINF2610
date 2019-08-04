#include <windows.h>
#include <stdio.h>
#define THREADCOUNT 4
HANDLE ghWriteEvent;
HANDLE ghThreads[THREADCOUNT];
DWORD WINAPI ThreadProc(LPVOID);
char Buffer[1024];
int main(int argc, char* argv[])
{
    DWORD dwWaitResult;
    int i;
    DWORD dwThreadID;
    // Create a manual-reset event. The main thread
    // sets this object to signaled when it
    // finishes writing to the buffer.
    ghWriteEvent = CreateEvent (
    NULL, // default security attributes
    TRUE, // manual-reset event
    FALSE, // initial state is nonsignaled
    TEXT("WriteEvent") ); // object name
    if (ghWriteEvent == NULL) {
        printf("CreateEvent failed (%d)\n", GetLastError());
        return 1;
    }
    // Create multiple threads to read from the buffer.
    for(i = 0; i < THREADCOUNT; i++) {
        ghThreads[i] = CreateThread(
        NULL, // default security
        0, // default stack size
        ThreadProc, // name of the thread function
        NULL, // no thread parameters
        0, // default startup flags
        &dwThreadID);
        if (ghThreads[i] == NULL) {
            printf("CreateThread failed (%d)\n", GetLastError());
            return 2;
        }
    }
    printf("Main thread writing to the shared buffer...\n");
    strcpy(Buffer,"API WIN32-CreateEvent-Example\n");
    // Set ghWriteEvent to signaled
    if (!SetEvent(ghWriteEvent)) {
        printf("SetEvent failed (%d)\n", GetLastError());
        return 3;
    }
    printf("Main thread waiting for threads to exit...\n");
    // The handle for each thread is signaled when the thread is terminated.
    dwWaitResult = WaitForMultipleObjects(THREADCOUNT, ghThreads, TRUE, INFINITE);
    switch (dwWaitResult) {
        case WAIT_OBJECT_0: // All thread objects were signaled
            printf("All threads ended, cleaning up for application exit...\n"); break;
        default: // An error occurred
            printf("WaitForMultipleObjects failed (%d)\n", GetLastError());
        return 4;
    }
    CloseHandle(ghWriteEvent); // Close the event to clean up
}

DWORD WINAPI ThreadProc(LPVOID lpParam) {
    DWORD dwWaitResult;
    printf("Thread %d waiting for write event...\n", GetCurrentThreadId());
    dwWaitResult = WaitForSingleObject(ghWriteEvent, INFINITE);
    printf("Thread %d reading from buffer: %s\n", GetCurrentThreadId(), Buffer);
    Sleep(1000);
    printf("Thread %d exiting\n", GetCurrentThreadId());
    return 3;
}