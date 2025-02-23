import serial, time

filename = "desk.txt"
with serial.Serial("COM13", 9600) as ser, open(filename, mode='wb') as of:
    
    try:  
        while 1: 
            time.sleep(1)
            of.write((ser.read(ser.inWaiting())))
            of.flush()
    except KeyboardInterrupt:
        print('stopped') 