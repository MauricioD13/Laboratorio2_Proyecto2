#include <windows.h>
#include <stdio.h>
#define BUFFERLENGTH 256
int main(int argc,char *argv[]){
    HANDLE hComm;
    BOOL Read_Status;
    DWORD dwEventMask;
    DWORD NoBytesRead;
    char SerialBuffer[BUFFERLENGTH - 1];
    char Temp;
    hComm = CreateFileA("\\\\.\\COM9",                //port name
                      GENERIC_READ | GENERIC_WRITE, //Read/Write
                      0,                            // No Sharing
                      NULL,                         // No Security
                      OPEN_EXISTING,// Open existing port only
                      0,            // Non Overlapped I/O
                      NULL);        // Null for Comm Devices
    if (hComm == INVALID_HANDLE_VALUE){
		
		  if (GetLastError() == ERROR_FILE_NOT_FOUND){
		    puts("cannot open port!");
			  return 1;
		  }

		puts("invalid handle value!");
		return 1;
	  }
    
    LPDCB lpdcb;
    lpdcb->ByteSize = 8;
    
    lpdcb->BaudRate = 19200;
    lpdcb->StopBits = 1;
    
    SetCommState(hComm,lpdcb);
    Read_Status = SetCommMask(hComm,EV_RXCHAR);
    if (Read_Status == FALSE){
		  printf("\n\n    Error! in Setting CommMask");
    }
	  else{
		  printf("\n\n    Setting CommMask successfull");
    }
    printf("\n\n    Waiting for Data Reception");
    Read_Status = WaitCommEvent(hComm, &dwEventMask, NULL); //Wait for the character to be received
    int i = 0;
    do{
        if(!ReadFile(hComm,SerialBuffer,BUFFERLENGTH,&NoBytesRead,NULL)){
          printf("Wrong character");
        }
        printf("Valor: %c\n",SerialBuffer[i]);
        i++;
    }while(100 > i);

}
