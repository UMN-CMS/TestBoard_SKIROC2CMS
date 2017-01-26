#
#   Author: Ryan Quinn
#   Email: quinn.ryanx@gmail.com
#   Sends (writes) a multiple-byte command to the FPGA and waits for a response.
#

import rpi.GPIO as GPIO
import time


# GPIO pins
DOUT = [19, 13, 21, 20, 24, 25, 16, 26]
RW = 17
ST = 18
ACK = 23

# Set up channels
GPIO.setmode(GPIO.BCM)
GPIO.setup(DOUT, GPIO.OUT)
GPIO.setup(RW, GPIO.OUT, initial=GPIO.HIGH)     # The initial values here are not known for sure yet.
GPIO.setup(ST, GPIO.OUT, initial=GPIO.HIGH)     # The write() function just toggles the input, so only
GPIO.setup(ACK, GPIO.IN)                        # the initial values need to be changed.

def sendcommand(command):
    '''
        Sends a 1 byte command to the FPGA and waits
        for a response. The command must be a list
        containing the bytes. Each byte must be a list
        of length 8 containing 0's and 1's.
    '''

    for byte in command:
        GPIO.output(DOUT, byte)
        time.sleep(0.1)                             # Not sure how long to wait or if we should be clocked.
        GPIO.output(RW, not GPIO.input(RW))
        GPIO.output(ST, not GPIO.input(ST))
        GPIO.wait_for_edge(ACK, GPIO.BOTH)
        GPIO.output(ST, not GPIO.input(ST))
        GPIO.wait_for_edge(ACK, GPIO.BOTH)

    GPIO.output(RW, not GPIO.input(RW))

sendcommand([[0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,1]])

GPIO.cleanup()
