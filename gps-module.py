import serial
import time
import string
import pynmea2

PORT = "/dev/ttyAMA0"
BAUDRATE = 9600
TIMEOUT = 0.5

class GpsTracker:
    def __init__(self, port_name, baud_rate, time_out):
        self.serial = serial.Serial(port_name, baudrate=baud_rate, timeout=time_out)
        self.lat = 0.0
        self.lon = 0.0
        self.gps = ""
    
    def get_GPS_data(self):
        return(self.gps, self.lat, self.lon)

    def read_GPS_data(self):
        while True:
            newdata = self.serial.readline()
            if newdata[0:6] == b"$GPRMC":
                newmsg = pynmea2.parse(newdata.decode("utf-8"))
                self.lat = newmsg.latitude
                self.lon = newmsg.longitude
                self.gps = "Latitude = " + str(self.lat) + " and Longitude = " + str(self.lon)
                break
        return(self.gps, self.lat, self.lon)

    def close_GPS_connection(self):
        try:
            self.serial.close()
            return True
        except:
            return False


gps = GpsTracker(PORT, BAUDRATE, TIMEOUT)
print(gps.read_GPS_data())
gps.close_GPS_connection
