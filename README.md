# Laboratorio2_Proyecto2

## Desarrollo

Realizar un código para convertir de analógico a digital, dos canales de entrada y convertir las dos señales digitalizadas a analógicas utilizando el DAC de la tarjeta de desarrollo (PIC18F47). Para una segunda parte de debía implementar 7 filtros digitales a través de uno de los dos canales desarrollados en la primera parte y comprobar su funcionamiento.

## Dispositivo

- PIC18F47
- Voltimetro
- Analizador de estados lógicos

## Algunos resultados

Con una señal sinusoidal de entrada por canal (dos frecuencias similares) que cumplan con criterio de Nyquist en el menor tiempo de muestreo (100us), escoger 10 tiempos de muestreo escritos por UART entre el mínimo y el máximo, y mostrar la señal reconstruida a la salida del DAC y en la gráfica del archivo CSV que se adquiere por el puerto serial.
Para un tiempo de muestreo de 100 us se obtuvieron las siguientes reconstrucciones:

![Resultado1](/img/Practica2a.png)

## Autores

- Daniel Morantes [Github](https://github.com/DanielMorantes)
- Joan Muñoz    [Github](https://github.com/JoanFerney99)
- Mauricio Cuello [Github](https://github.com/MauricioD13)