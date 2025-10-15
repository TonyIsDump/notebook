from datetime import datetime
import time
import serial

# Initialize the serial connection (replace 'COM3' with your Arduino's port)
try:
    ser = serial.Serial('/dev/ttyACM0', 9600, timeout=0.01)  # Adjust 'COM3' to your port
    time.sleep(1)  # Wait for the serial connection to initialize
except serial.SerialException as e:
    exit()

while True:
    try:
        # Get the current date and time
        current_datetime = datetime.now()
        
        # Format the datetime object to display only the time
        current_time_str = current_datetime.strftime("%H:%M:%S")
        
        # Send the time string to Arduino with a newline
        ser.write(f"{current_time_str}\n".encode('utf-8'))
        
        # Flush the output to ensure it updates immediately
        time.sleep(1)
        
    except KeyboardInterrupt:
        ser.close()  # Close the serial port when done
        break
    except Exception as e:
        ser.close()
        break
