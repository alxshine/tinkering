import psutil
import serial
from time import sleep


COM = "COM6"  # /dev/ttyACM0 (Linux)
BAUD = 115200

ser = serial.Serial(COM, BAUD, timeout=0.1)

print("Waiting for device")
sleep(3)
print(ser.name)

# clear bytes the MC sends during startup
ser.readall()

i = 0
while True:
    load = psutil.cpu_percent()
    print(f"Load is {load}")
    converted = int(load / 12.5)
    message = f"{converted}".encode()
    print(f"Writing {message}")
    ser.write(message)

    while not ser.inWaiting():
        sleep(0.01)
    response = ser.readline()
    print(f"Got response {response}")

    i = (i + 1) % 8

    sleep(0.5)
