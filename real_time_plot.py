import time
import warnings
from collections import deque
import serial
import numpy as np
import matplotlib.pyplot as plt
import statistics
 
N = 200
data = deque([0] * N, maxlen=N) # deque con longitud máxima N
#Creamos la figura
plt.ion()
fig, ax = plt.subplots()
ll, = ax.plot(data)
 
# Abrimos la conexión con Arduino
arduino = serial.Serial('COM9',baudrate=19200, timeout=1)

 
with arduino:
    while True:
        try:
            line = arduino.readline()
    
            dato = int.from_bytes(line,"big")
            dato = dato>>8
            
            if not line:
            # HACK: Descartamos líneas vacías porque fromstring produce
            # resultados erróneos, ver
            # https://github.com/numpy/numpy/issues/1714
                continue
            print(dato)
            yy = np.array(dato)
            
            #print(yy)
            data.append(yy)
            ll.set_ydata(data)
            
            ax.set_ylim(min(data) - 10, max(data) + 10)
            
            
        except ValueError:
            warnings.warn("Line {} didn't parse, skipping".format(line))
        except KeyboardInterrupt:
            print("Exiting")
            break