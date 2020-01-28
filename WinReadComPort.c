#include <stdio.h>
#include <Windows.h>
#include <WinBase.h>

#define REFRECH_RATE 5000

HANDLE comh;
DCB dcb;

void closeProgram(){
    BOOL aok;
    do{
        aok = CloseHandle(comh);
    }while(aok == 0);
}

BOOL stringCompare(char* c1, char* c2){
    while(1){
        
    }
}

void printCommState(){
    printf("Baud Rate: %d, Parity: %d, Stop Bits: %d\n", dcb.BaudRate, dcb.Parity, dcb.StopBits);
}

int main(int argv, char** argc){

    // Open Handle to Com Port

    argc++;

    printf("%s\n", *argc);
    comh = CreateFile(
        *argc,
        GENERIC_READ,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL,
        OPEN_EXISTING,
        0,
        NULL);
    
    if(comh == INVALID_HANDLE_VALUE){
        printf("There was an error while opening the handle to %s\nError Code: %d\n", *argc, GetLastError());
        return 1;
    }

    // Initilize DCB

    ZeroMemory(&dcb, sizeof(DCB));
    dcb.DCBlength = sizeof(DCB);

    // Get Com state

    if(GetCommState(comh, &dcb) == 0){
        printf("There was an error while getting the state of %s\nError code: %d\n", *argc, GetLastError());
        closeProgram();
        return 2;
    }

    // Print initial comm state
    printCommState();
    
    // Set Comm state

    // Close Handle
    closeProgram();
    return 0;
}
