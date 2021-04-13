

import serial      
import os

cont_A = 0
cont_B = 0
while(1):
    
    option = int(input("[1] Leer puerto serial\n[2] Enviar cambio de parametros\n[3]Salir\n"))
    if(option==1):
        #fileA = open("datosA.csv",'w')
        #fileB = open("datosB.csv",'w')
        os.system("receive_serial.exe")
        os.system("cls")

        fileA = open("data_A.csv","r")
        fileB = open("data_B.csv","r")
        dataA = fileA.readline()
        dataA = dataA.split(",")
        dataB = fileB.readline()
        dataB = dataB.split(",")
        
        numbersA = []
        numbersB = []
        for i in dataA:
            try:
                numbersA.append(int(i)/100)
            except:
                continue
        for j in dataB:
            try:
                numbersB.append(int(j)/100)
            except:
                continue    
        fileA.close()    
        fileB.close()
        fileA = open("data_A.csv","w")
        fileB = open("data_B.csv","w")
        for i in numbersA:
            fileA.write(str(cont_A) + ","+ str(i)+"\n")
            cont_A +=1
        for i in numbersB:
            fileB.write(str(cont_B) + ","+ str(i)+"\n")
            cont_B+=1
        fileA.close()    
        fileB.close()
        
            
    elif(option == 2):
        number_send = str(input("Ingrese numero de veces a contar 100us (0 a 10): "))
        os.system("send_serial.exe "+ number_send);
        

    else:
        break