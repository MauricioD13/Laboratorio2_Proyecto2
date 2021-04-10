

import serial      
import os

result_A = []
result_B = []
flag_init = 0;
flag_init_B = 0;
while(1):
    
    option = int(input("[1] Leer puerto serial\n[2] Enviar cambio de parametros\n[3]Salir\n"))
    if(option==1):
        port = serial.Serial('COM9', 19200, timeout=1,write_timeout = 0)
        #fileA = open("datosA.csv",'w')
        #fileB = open("datosB.csv",'w')
        i = 0
        j = 0
        while True:
            
            data = port.read()
            
            if(data.decode()=='#'):
                    flag_init = 1
                    flag_init_B = 0;
            elif(flag_init == 1):
                if(data.decode()==','):
                        flag_init_B = 1
                elif(flag_init_B != 1):
                    result_A.append(data.decode())
                else:
                        result_B.append(data.decode())
            if(len(result_B)==3):
                    print(f"Voltaje 1: {result_A[0]},{result_A[1]}{result_A[2]}  Voltaje 2: {result_B[0]},{result_B[1]}{result_B[2]} ")

            port.flush()
                
                        
            
            
    elif(option == 2):
        number_send = str(input("Ingrese numero de veces a contar 100us (0 a 10): "))
        os.system("send_serial.exe "+ number_send);
        

    else:
        break