import serial
from time import sleep
import sys


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
    line = f"{i}".encode()
    print(f"Writing {line}")
    ser.write(line)

    while not ser.inWaiting():
        sleep(0.01)
    response = ser.readline()
    print(f"Got response {response}")

    i = (i + 1) % 8

    sleep(0.5)
