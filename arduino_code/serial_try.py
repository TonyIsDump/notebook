import serial
import time

arduino = serial.Serial(port='/dev/ttyACM1', baudrate=9600, timeout=0.1)

def write_read(x):
    arduino.write(bytes(x, 'utf-8'))
    time.sleep(0.05)
    data = arduino.readline()
    return data

while True:
    input_data = input("Enter 0 - 180: ")  # Take single character input

    try:
        input_data = int(input_data)
        if(input_data > 0 & input_data < 180):
            value = write_read(str(input_data))
            #print(value.decode('utf-8', errors='ignore'))  # Decode and print response
        else:
            print("Invalid input, error 0")
    except:
        print("Invalid input, error 1")
