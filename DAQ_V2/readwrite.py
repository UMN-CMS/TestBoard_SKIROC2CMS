#
#   Author: Ryan Quinn
#   Email: quinn.ryanx@gmail.com
#
#       Functions to read/write from/to the FPGA.
#       This module is called from the 'options.py' file.
#

import RPi.GPIO as GPIO



# GPIO pin definitions (Broadcom)
DOUT = [19, 13, 21, 20, 24, 25, 16, 26] # Data lines MISC[3:0] and DIP[4:1]
RW = 17                                 # R/W BUTTON 0
ST = 18                                 # Strobe BUTTON 1
ACK = 23                                # Acknowledge



# Set up channels
# write is TRUE for a write operation and FALSE for a read operation
def setupGPIO(write):
    GPIO.setmode(GPIO.BCM)                              # Broadcom pin definitions
    GPIO.setup(DOUT, GPIO.OUT if write else GPIO.IN)    # Controlled by Pi/FPGA on write/read
    GPIO.setup(RW, GPIO.OUT, initial=GPIO.LOW)          # Controlled by Pi
    GPIO.setup(ST, GPIO.OUT, initial=GPIO.HIGH)         # Controlled by Pi
    GPIO.setup(ACK, GPIO.IN)                            # Controlled by FPGA


# Cleanup GPIO pins. Placeholder for now just in case extra steps need to be taken during cleanup.
def cleanupGPIO():
    GPIO.cleanup()



def sendcommand(command):
    '''
        Sends a 1 byte command to the FPGA and waits
        for a response.
    '''

    setupGPIO(True) # Set up the GPIO pins for the type of operation (write)

    # Python's array numbering system is backwards from the FPGA's bus labeling.
    # In Python, DOUT[0] and DOUT[7] correspond to MSB and LSB, respectively.
    GPIO.output(DOUT[0], 1)             # DOUT MSB is always HI on write
    GPIO.output(DOUT[1:4], command)     # DOUT[6:3] are used for data transmission
    GPIO.output(DOUT[5:7], [0, 0, 0])   # DOUT[2:0] are used to send bitstreams
                                        # so they stay low here.

    GPIO.output(RW, GPIO.LOW)           # Set R/W low for write operation
    GPIO.output(ST, not GPIO.input(ST)) # Toggle strobe to FPGA knows we're ready

    GPIO.wait_for_edge(ACK, GPIO.BOTH, timeout=30000)   # Waiting for ACK to toggle within
                                                        # 30 sec (30000 ms). Might want to
                                                        # raise an exception if this
                                                        # function times out...

    GPIO.output(ST, not GPIO.input(ST)) # Toggle strobe again

    GPIO.wait_for_edge(ACK, GPIO.BOTH, timeout=30000)  # Wait for ACK to toggle again

    # To send the bitstream. Not sure if we need to create this for other possible commands...
    if(command == [0, 0, 1, 0]):
        send_bitstream('bitstream.txt')
    else:
        cleanupGPIO()



def send_bitstream(bitfile):
    '''
        Sends a bitstream of length 384 to the
        FPGA using the last 3 bits of DOUT.
    '''

    setupGPIO(True)

    f = open(bitfile, 'r')                              # Opening the file containing the bitstream.
    bitstream = [int(num) for num in f.readlines()[0]]  # Converting the data in the file into an array.
    f.close()                                           # The bitstream must be contained in the first
                                                        # line of the bitfile.

    # Sending the bitstream to the FPGA
    for i in range(0, 128):
        GPIO.output(DOUT[0], 1)                         # DOUT MSB is HI for write
        GPIO.output(DOUT[1:4], 0)                       # DOUT[6:3] are not used for the bitstream.
        GPIO.output(DOUT[5:7], bitstream[3*i:(3*i)+2])  # DOUT[2:0] are used for bitstream transmission.

        GPIO.output(RW, not GPIO.input(RW))             # Same timing structure as seen in the
        GPIO.output(ST, not GPIO.input(ST))             # sendcommand() function.

        GPIO.wait_for_edge(ACK, GPIO.BOTH, timeout=30000)

        GPIO.output(ST, not GPIO.input(ST))

        GPIO.wait_for_edge(ACK, GPIO.BOTH, timeout=30000)

    cleanupGPIO()


# Read from FPGA. Not currently set up.
def read():
    pass
