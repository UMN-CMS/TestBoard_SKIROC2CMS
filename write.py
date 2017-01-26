#
#   Author: Ryan Quinn
#   Email: quinn.ryanx@gmail.com
#   Date: 1 January 2017
#

import rpi.GPIO as GPIO
import time



DOUT = [19, 13, 21, 20, 24, 25, 16, 26]
RW = 17
ST = 18
ACK = 23

GPIO.setmode(GPIO.BCM)

GPIO.setup(DOUT, GPIO.OUT)
GPIO.setup(RW, GPIO.OUT, initial=GPIO.HIGH)
GPIO.setup(ST, GPIO.OUT, initial=GPIO.HIGH)
GPIO.setup(ACK, GPIO.IN)

def write(byte):

    GPIO.output(DOUT, byte)
    time.sleep(0.1)
    GPIO.output(RW, not GPIO.input(RW))
    time.sleep(0.1)
    GPIO.outputi(ST, not GPIO.input(ST))

write([1,1,1,1,1,1,1,1])
