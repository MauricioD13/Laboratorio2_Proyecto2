#include <windows.h>
#include <stdio.h>
int main(int argc,char *argv[]){

    int Status;
  HANDLE hComm;

  hComm = CreateFileA("\\\\.\\COM9",                //port name
                      GENERIC_READ | GENERIC_WRITE, //Read/Write
                      0,                            // No Sharing
                      NULL,                         // No Security
                      OPEN_EXISTING,// Open existing port only
                      0,            // Non Overlapped I/O
                      NULL);        // Null for Comm Devices

  if (hComm == INVALID_HANDLE_VALUE)
      printf("Error in opening serial port\n");
  else
      printf("Opening serial port successful\n");

    int lpBuffer;
    
    lpBuffer = atoi(argv[1]);
    
    int number_bytes = 1;
    long unsigned int status_bytes;
    Status = WriteFile(hComm,        // Handle to the Serial port
                   &lpBuffer,     // Data to be written to the port
                   number_bytes,  //No of bytes to write
                   &status_bytes, //Bytes written
                   NULL);
    LPDCB lpdcb;
    lpdcb->BaudRate = 19200;
    lpdcb->StopBits = 1;
    
    SetCommState(hComm,lpdcb);
    GetCommState(hComm,lpdcb);

  CloseHandle(hComm);//Closing the Serial Port

  return 0;
}