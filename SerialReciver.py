import serial

ser = serial.Serial('/dev/ttyACM0', 115200, timeout=None)

def main():
    while True:
        data = []
        datacollection(data)
        print(len(data))
        print(data)

def datacollection(data):
    while (len(data) < 400):
        input = ser.read(2).hex()
        decimalinput = int(input,16)
        data.append(decimalinput)

if __name__ == "__main__":
    main()