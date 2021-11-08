import serial
import time

ser = serial.Serial("/dev/ttyS0", 115200, timeout=2)


def main():
    while True:
        ser.write("\x37".encode('utf-8'))
        print("send to Arena: \x37")

        time.sleep(2)


if __name__ == '__main__':
    try:
        main()
    except KeyboardInterrupt:
        if ser != None:
            ser.close()
