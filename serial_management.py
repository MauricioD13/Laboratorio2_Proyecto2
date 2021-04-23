

import serial      
import os

cont_A = 0
cont_B = 0
while(1):
    
    option = int(input("[1] Leer puerto serial\n[2] Enviar cambio de parametros\n[3]Salir\n"))
    if(option==1):
        fileA = open("datosA.csv",'w')
        fileB = open("datosB.csv",'w')
        port = serial.Serial('COM9',114285)
        i = 0
        while i<3000:
            data = port.readline()
            data = data.decode()
            data = data.split(',')
            print(data)
            try:
                dato_1 = int(data[0])/100
                dato_2 = int(data[1])/100
                fileA.write(str(i)+ ',' +str(dato_1)+'\n')
                fileB.write(str(i)+ ',' + str(dato_2)+ '\n')
                i += 1
            except: 
                continue
        port.close()
        fileA.close()    
        fileB.close()
        
            
    elif(option == 2):
        number_send = str(input("Ingrese numero de veces a contar 100us (0 a 10): "))
        os.system("send_serial.exe "+ number_send);
        

    else:
        break