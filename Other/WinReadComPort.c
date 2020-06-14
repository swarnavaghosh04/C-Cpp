#include <stdio.h>
#include <Windows.h>
#include <WinBase.h>

#define REFRECH_RATE 5000

HANDLE hComm;                  // Handle to COM file
DCB dcb;                      // DCB for the COM file
COMMTIMEOUTS cto;             // COMMTIMEOUTS for the COM file
int run = 1;                  // Program terminates when run = 0 (when the enter key is hit)

// =========== General Functions ===============

void closeProgram(){
    BOOL aok;
    do aok = CloseHandle(hComm);
    while(aok == 0);
}

DWORD WINAPI readThread(){
    DWORD event;
    char input;
    DWORD noBytesRead;
    while(1){
        WaitCommEvent(hComm, &event, NULL);
        ReadFile(hComm, &input, 1, &noBytesRead, NULL);
        printf("%c", input);
    }
}

void printCommState(){
    printf("Baud Rate: %d, Parity: %d, Stop Bits: %d\n", dcb.BaudRate, dcb.Parity, dcb.StopBits);
}

// ============== Main Function ===============

int main(int argv, char** argc){

    // Open Handle to Com Port
    argc++;
    printf("%s\n", *argc);
    hComm = CreateFile(
        *argc,
        GENERIC_READ,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL,
        OPEN_EXISTING,
        0,
        NULL);
    
    if(hComm == INVALID_HANDLE_VALUE){
        printf("There was an error while opening the handle to %s\nError Code: %d\n", *argc, GetLastError());
        return 1;
    }

    // Initialize COMTIMEOUTS
    ZeroMemory(&cto, sizeof(COMMTIMEOUTS));
    cto.ReadIntervalTimeout = MAXDWORD;
    cto.ReadTotalTimeoutMultiplier = 0;
    cto.ReadTotalTimeoutConstant = 0;
    SetCommTimeouts(hComm, &cto);

    // Initilize DCB
    ZeroMemory(&dcb, sizeof(DCB));
    dcb.DCBlength = sizeof(DCB);

    // Get Com state
    if(GetCommState(hComm, &dcb) == 0){
        printf("There was an error while getting the state of %s\nError code: %d\n", *argc, GetLastError());
        closeProgram();
        return 2;
    }
    
    // Set Comm state
    dcb.BaudRate = CBR_9600;
    dcb.Parity = NOPARITY;
    dcb.StopBits = ONESTOPBIT;
    dcb.fParity = FALSE;
    dcb.fBinary = TRUE;
    if(SetCommState(hComm, &dcb) == 0){
        printf("There was an error while setting the state of %s\nError code: %d\n", *argc, GetLastError());
        closeProgram();
        return 3;
    }

    // Print comm state
    printCommState();

    // Set Com Mask
    if(SetCommMask(hComm, EV_RXCHAR) == 0){
        printf("There was an error while setting the mask for %s\nError code: %d\n", *argc, GetLastError());
        closeProgram();
        return 4;
    }

    // Start keepRunning thread
    HANDLE tRead = CreateThread(NULL, 0, readThread, NULL, 0, NULL);

    // Keep running till the enter key is hit
    getchar();
    TerminateThread(tRead, STILL_ACTIVE);

    // Close Handle
    closeProgram();
    return 0;
}
