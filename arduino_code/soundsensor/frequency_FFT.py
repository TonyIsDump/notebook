import serial
import time
import matplotlib.pyplot as plt
import numpy as np

def FFT(x):
    N = len(x)
    
    if N == 1:
        return x
    else:
        X_even = FFT(x[::2])
        X_odd = FFT(x[1::2])
        factor = np.exp(-2j * np.pi * np.arange(N) / N)
        
        X = np.concatenate(
            [X_even + factor[:int(N/2)] * X_odd,
             X_even + factor[int(N/2):] * X_odd]
        )
        return X

# Configuration
ser = serial.Serial(port='/dev/ttyACM0', baudrate=115200, timeout=0.1)
N = 1024  # Number of samples for FFT, must be power of 2
time.sleep(2)  # Wait for serial connection to establish

try:
    plt.ion()  # Interactive mode for non-blocking plots
    fig, ax = plt.subplots()
    
    while True:
        values = []
        start_time = time.time()
        
        while len(values) < N:
            line = ser.readline().decode('utf-8').strip()
            if line:
                try:
                    val = int(line)
                    values.append(val)
                except ValueError:
                    pass  # Skip invalid lines
        
        end_time = time.time()
        dt = end_time - start_time
        sampling_rate = N / dt
        
        x = np.array(values, dtype=float)
        x -= np.mean(x)  # Remove DC offset
        
        X = FFT(x)
        mags = 2*np.abs(X[:N//2])
        freqs = np.linspace(0, sampling_rate / 2, N//2)
        
        # Find dominant frequency (skip DC component)
        if np.any(mags[1:]):
            peak_idx = np.argmax(mags[1:]) + 1
            peak_freq = freqs[peak_idx]
            print(f"Dominant frequency: {peak_freq:.2f} Hz")
        else:
            print("No significant frequency detected.")
        
        # Update plot
        ax.cla()
        ax.plot(freqs, mags)
        ax.set_xlabel('Frequency (Hz)')
        ax.set_ylabel('Magnitude')
        ax.set_title('Frequency Spectrum')
        plt.pause(0.01)  # Brief pause to update plot

except KeyboardInterrupt:
    print("Exiting program.")
finally:
    ser.close()
    plt.ioff()
    plt.close()
