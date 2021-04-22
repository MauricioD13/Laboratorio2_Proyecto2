import serial      
import grafica_procesamiento
import numpy as np
from scipy.fft import fft, fftfreq
import matplotlib.pyplot as plt
result = []

flag_init = 0;

i =0
option = int(input("[1]Tomar datos\n[2] Graficar\n[3]FFT\n[4]Salir\n"))

if(option==1):
        port = serial.Serial('COM9', 19200, timeout=0)
        fileA = open("plot.txt",'w')
        fileB = open("plot_1.txt","w")
        while(i<3000):
            data = port.readline()
            
            data = int.from_bytes(data,"big")
            
            if(data!=0 and data>40000 and data>128):
                
                data = data>>8
                
                fileA.write(str(i) + ','+str(data)+'\n')
                fileB.write(str(data)+'\n')
                i+=1
        fileA.close()
elif(option == 2):
        graficas = ["IIR_Altas.txt"]
        grafica_procesamiento.graphics(graficas,"tab",",","1","Serial plot","Tiempo[s]","ADC[samples]","5000","lineal")


elif(option == 3):
        
    # Number of sample points

    N = 3000

    # sample spacing

    T = 1/120
    data = []
    y = []
    fileA = open("plot.txt","r")
    for line in fileA:
        data= line.split(",")
        y.append(int(data[1]))
    
    y_array = np.array(y)
    
    yf = fft(y)
    print(yf)
    xf = fftfreq(N, T)[:N//2]

    

    plt.plot(xf,np.abs(yf[0:N//2]))

    plt.grid()

    plt.show()
    