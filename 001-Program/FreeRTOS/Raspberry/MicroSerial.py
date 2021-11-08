#
# Created by dream on 2021/10/25.
#
import time

from serial.serialutil import SerialException
from serial import Serial


class MicroSerial:
    def __init__(self, port="/dev/ttyS0", baudrate=115200, timeout=0.5):
        self.port = port
        self.writeTimeout = timeout
        self.timeout = timeout
        self.baudrate = baudrate
        self.interCharTimeout = timeout / 30.

        self.redPos = 0
        self.tarPos = 0
        self.attackJudge = 0

    def connect(self):
        try:
            print ("Connecting to Arena stm32", self.port, "...")
            self.port = Serial(port=self.port, baudrate=self.baudrate, timeout=self.timeout,
                               writeTimeout=self.writeTimeout)
            time.sleep(1)

        except SerialException:
            print ("Serial Exception:")

    def send(self, cmd):
        self.port.write(cmd + "\r")
        print ("send to Arena: " + cmd)

    def recv(self, timeout=0.5):
        timeout = min(timeout, self.timeout)
        c = ''
        value = ''
        attempts = 0
        while c != '\r':
            c = self.port.read(1)
            value += c
            attempts += 1
            if attempts * self.interCharTimeout > timeout:
                return None
        value = value.strip('\r')
        print ("receive from Arena: " + value)
        return value

    def recv_int(self):
        value = self.recv(self.timeout)
        try:
            print ("receive int from Arena: " + int(value))
            return int(value)
        except:
            return None

    def close(self):
        self.port.close()


if __name__ == '__main__':
    stm32F407 = MicroSerial(port="/dev/ttyS0", baudrate=115200, timeout=0.5)

    stm32F407.connect()
    a = 321

    while True:
        stm32F407.send(str(a))
        time.sleep(1)
        stm32F407.recv()
        # stm32F407.recv_int()
        time.sleep(1)

    stm32F407.close()
