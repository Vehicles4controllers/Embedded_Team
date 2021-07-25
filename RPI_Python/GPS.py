import serial

GPS  = serial.Serial("/dev/rfcomm0",baudrate=9600,timeout=0.5)
#UART = serial.Serial("/dev/ttyS0",baudrate=9600,timeout=0.5)


while True:
    File = open("GPS_DATA.txt","r+")
    NMEA_line = GPS.readline()
    data      = NMEA_line.split(",")
    ''' Parsing NMEA Code '''
    if data[0] == "$GNRMC":
        #UART.write(line)
        #UART.write("\n")
        ''' Get UTC of postion ''' 
        time = data[1]
        time = time.split(".")
        utc  = time[0]
        utc2 = str(int(utc[0:2])+2)
        hour = utc[0] + utc2
        mins = utc[2:4]
        secs = utc[4:6]
        #print(line)
        print ("Time(UTC+2): " + hour + ":" + mins + ":" + secs)
        File.write("Time(UTC+2): " + hour + ":" + mins + ":" + secs + "\n")
        #UART.write("Time(UTC+2): "+hour+":"+mins+":"+secs)
        #UART.write("\n")
        ''' Check Position status (A = data valid, V = data invalid) '''
        if data[2] == "A":
            ''' Get UTC of Latitude ''' 
            Latitude_deg = data[3][0:2]
            Latitude_min = data[3][2::]
            Latitude_dir = data[4]
            Latitude     = Latitude_deg+Latitude_min+Latitude_dir
            print("Latitude: "+Latitude)
            File.write("Latitude: " + Latitude + "\n")
            #UART.write("Latitude: "+Latitude)
            #UART.write("\n")
            ''' Get UTC of Longtitude ''' 
            Longtitude_deg = data[5][0:3]
            Longtitude_min = data[5][3::]
            Longtitude_dir = data[6]
            Longtitude     = Longtitude_deg+Longtitude_min+Longtitude_dir
            print("Longtitude: " + Longtitude + "\n")
            File.write("Longtitude: "+Longtitude + "\n")
            File.close()
           # UART.write("Longtitude: "+Longtitude)
            #UART.write("\n")
        else:
            print "Not Fix - Data Invalid"