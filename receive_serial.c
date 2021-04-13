#include <windows.h>
#include <stdio.h>
#define BUFFERLENGTH 1024

int flag_init = 0;
int main(int argc,char *argv[]){
    FILE *file_A;
    FILE *file_B;
    file_A = fopen("data_A.csv","w");
    file_B = fopen("data_B.csv","w");

    HANDLE hComm;
    BOOL Read_Status;
    DWORD dwEventMask;
    DWORD NoBytesRead;
    BOOL Status;
    char SerialBuffer[BUFFERLENGTH - 1];
    char Voltage_A[3];
    char Voltage_B[3];
    char Temp;
    hComm = CreateFile("\\\\.\\COM9",                //port name
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
		
	  }
    
    DCB dcbSerialParams;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.BaudRate = 19200;
   
     
    dcbSerialParams.StopBits = 1;
    
    Status = SetCommState(hComm,&dcbSerialParams);
    Read_Status = SetCommMask(hComm,EV_RXCHAR);
    
    if (Read_Status == FALSE){
		  printf("\n\n    Error! in Setting CommMask");
    }
	  else{
		  printf("\n\n    Setting CommMask successfull");
    }
    printf("\n\n    Waiting for Data Reception");
    int cont_A = 0;
    int cont_B = 0;
    char *aux[4];

    for(int k = 0; k<100 ; k++){
      Status = WaitCommEvent(hComm, &dwEventMask, NULL); //Wait for the character to be received
      if (Status == FALSE)
          {
            printf("\n  Error! in Setting WaitCommEvent()");
          }
        else //If  WaitCommEvent()==True Read the RXed data using ReadFile();
          {
            
            int i = 0;
            char TempChar;
            do{
                      
                Status = ReadFile(hComm, &TempChar, sizeof(TempChar), &NoBytesRead, NULL);
                
                SerialBuffer[i] = TempChar;
                
                i++;
            }while (NoBytesRead > 0);

                  printf("\n\n    ");
                  int a = 0;
                  int b = 0;
                  
                  for (int j = 0; j < i-1; j++){	// j < i-1 to remove the dupliated last character
                      
                      if(SerialBuffer[j] == '#'){
                        flag_init = 1;
                        a = 0;
                      }
                      else if(flag_init == 1 && SerialBuffer[j] != ','){
                        
                        if(a<3){
                          fputc(SerialBuffer[j],file_A);
                          if(a==2){
                            fputc(',',file_A);
                          }
                          cont_A++;
                          a++;
                        }else {
                          fputc(SerialBuffer[j],file_B);
                          if(a==4){
                            fputc(',',file_B);
                          }
                          cont_B++;
                          a++;
                        }
                        
                      }
                      
                      
                    }                  
                    
            flag_init=0;
            //printf("Voltaje A: %c ,%c%c Voltaje B: %c ,%c%c",Voltage_A[0],Voltage_A[1],Voltage_A[2],Voltage_B[0],Voltage_B[1],Voltage_B[2]);
          }
          }
    printf("\n\n    End receiving\n");
    fclose(file_A);
    fclose(file_B);
    CloseHandle(hComm);

    }

