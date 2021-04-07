

import serial      
import os

result = []

flag_init_A = 0;
flag_init_B = 0;
while(1):
    
    option = int(input("[1] Leer puerto serial\n[2] Enviar cambio de parametros\n[3]Salir\n"))
    if(option==1):
        port = serial.Serial('COM9', 19200, timeout=0,write_timeout = 0)
        fileA = open("datosA.csv",'w')
        fileB = open("datosB.csv",'w')
        i = 0
        j = 0
        while True:
            
            data = port.read()
            try:
                if(data.decode() == 'A'):
                    flag_init_A = 1;
                elif(flag_init_A == 1 and data.decode()!='-' and data.decode()!=''and data.decode()!='A' and data.decode()!='B'):
                    result.append(data.decode());
                    
                    if(len(result)==3):
                        flag_init_A = 0;
                        result = int(result[0]) + int(result[1])/10 + int(result[2])/100
                        print(f"VOLTAGE A:{result}\r\t",end="")
                        
                        fileA.write(str(i)+","+str(result)+"\n")
                        result = []
                        i+=1
                if(data.decode() == 'B'):
                    flag_init_B = 1
                elif(flag_init_B == 1 and data.decode()!='-' and data.decode()!='' and (data.decode()!='A' or data.decode()!='B')):
                    result.append(data.decode())
                    
                    if(len(result)==3):
                        flag_init_B = 0;
                        result = int(result[0]) + int(result[1])/10 + int(result[2])/100
                        print(f"VOLTAGE B:{result}")
                        
                        fileB.write(str(i)+","+str(result)+"\n")
                        result = []
                        j+=1
                        
            except KeyboardInterrupt: 
                fileA.close()
                fileB.close()
                break
        port.close();
    elif(option == 2):
        number_send = str(input("Ingrese numero de veces a contar 100us (0 a 10): "))
        os.system("send_serial.exe "+ number_send);
        

    else:
        break