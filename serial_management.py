

import serial      
        
port = serial.Serial('COM9', 19200, timeout=0,write_timeout = 0)
result = []

flag_init = 0;
while(1):
    option = int(input("[1] Leer puerto serial\n[2] Enviar cambio de parametros\n[3]Salir\n"))
    if(option==1):
        while True:
            
            data = port.read()
            try:
                if(data.decode() == '#'):
                    flag_init = 1;
                    
                elif(flag_init == 1 and data.decode()!='-' and data.decode()!=''):
                    result.append(data.decode());
                    
                    if(len(result)==3):
                        flag_init = 0;
                        print(f"VOLTAGE:{result}")
                        result = []
            except KeyboardInterrupt: 
                break

    elif(option == 2):
        
        port.write(7)

    else:
        break