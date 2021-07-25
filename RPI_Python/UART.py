import serial

ser = serial.Serial("/dev/ttyS0",baudrate=1200,timeout=0.5)
#ser.write('Hello WorldCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC\r\n')

while True:
    data = ser.readline()
    print(data)