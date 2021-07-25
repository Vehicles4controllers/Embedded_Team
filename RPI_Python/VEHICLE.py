import serial
import time

''' UART - Serial Communication with Tiva-C '''
UART = serial.Serial("/dev/ttyS0",baudrate=1200, timeout=1)

global Encoder_Reading
Encoder_Reading      = 0
Calibration_Value_1m = 612
Distance = 0
Speed    = 0
while True: 
    ''' UART '''
    UART_line = UART.readline()
    Tiva_data = UART_line.split(",")
    ''' State of the car Moving or Stop '''
    if (Tiva_data[0] == "State:"):
        ''' Tme of the state '''
        time_t = time.localtime()
        current_time = time.strftime("%H:%M:%S", time_t).split(":")
        current_time[0] = str(int(current_time[0])+1)
        print("Time: " + current_time[0] + ":" + current_time[1] + ":" + current_time[2])
        print(Tiva_data[0] + Tiva_data[1])
        ''' Reading the Encoder and measure the distance '''
        if (Tiva_data[1] == " Moving"):
            try:
                Encoder_Reading = float(Tiva_data[2])
                Distance        = Encoder_Reading/Calibration_Value_1m
                print("Distance= " + str(Distance) + " m")
                End_Time = float(int(current_time[0]) + (float(current_time[1])/60) + (float(current_time[2][0:2])/3600))
                Time     = End_Time - Start_Time
                print(Start_Time)
                print(End_Time)
                Speed = Distance/(Time*1000)
                print("Speed: " + str(Speed) + " Km/h" + "\n")
            except:
                print(Tiva_data[2])
        else:
            Speed    = 0
            Start_Time = float(int(current_time[0]) + (float(current_time[1])/60) + (float(current_time[2][0:2])/3600))
            UART.write("S")            