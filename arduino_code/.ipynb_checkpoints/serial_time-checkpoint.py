import datetime
import time
import serial

arduino = serial.Serial(port='/dev/ttyACM1', baudrate=115200, timeout=0.05)

def write_read(x):
    arduino.write(x.encode())

while True:
    current_time = datetime.datetime.now()
    cycle = current_time.second%20
    if cycle <10:
        print(cycle)
        write_read(str(cycle))
    else:
        write_read("no signal")
    time.sleep(1)
