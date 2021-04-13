

import serial      
import os
class Data:
    def __init__(self):
        self.aux = str
        self.result_A = []
        self.result_B = []
    def save(self,data,channel):
        if(channel == 'A'):
            self.result_A.append(data.decode())
        else:
            self.result_B.append(data.decode())
    def print_data(self):
        print(f"Voltaje 1: {self.result_A[0]},{self.result_A[1]}{self.result_A[2]}  Voltaje 2: {self.result_B[0]},{self.result_B[1]}{self.result_B[2]}")


data = Data()
flag_init = 0;
flag_init_B = 0;
while(1):
    
    option = int(input("[1] Leer puerto serial\n[2] Enviar cambio de parametros\n[3]Salir\n"))
    if(option==1):
        with serial.Serial('COM9', 19200, timeout=1,write_timeout = 0) as port:
            #fileA = open("datosA.csv",'w')
            #fileB = open("datosB.csv",'w')
            i = 0
            j = 0
            
            while True:
                
                data.aux = port.read()
                
                if(data.aux.decode()=='#'):
                        flag_init = 1
                        flag_init_B = 0;
                elif(flag_init == 1):
                    if(data.aux.decode()==','):
                            flag_init_B = 1
                    elif(flag_init_B != 1):

                        data.save(data.aux,'A')
                    else:

                        data.save(data.aux,'B')

                if(len(data.result_B)==3):
                    data.print_data()
                    
                    

                
                    
                        
            
            
    elif(option == 2):
        number_send = str(input("Ingrese numero de veces a contar 100us (0 a 10): "))
        os.system("send_serial.exe "+ number_send);
        

    else:
        break