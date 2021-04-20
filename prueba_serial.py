

import serial      

port = serial.Serial('COM9', 19200, timeout=0)
fileA = open("Entrada.txt",'w')
fileB = open("Salida.txt","w")
while True:
    data = port.readline()
    if data!=b'':
        x = int.from_bytes(data,"big")
        if x > 8589934591:
            x += 4294967296

            y = (x & 0x0000ffff00)>>8
            z = x
            x = x>>24
            x -= 256
            print(f"Datos: {data} datos binarios {bin(z)} Convertido 1: {x} Convertido 2: {y}")
            fileA.write(str(i) + str(x) + '\n')
            fileB.write(str(i) + str(y) + '\n')

