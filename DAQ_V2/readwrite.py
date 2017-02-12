#
#   Author: Ryan Quinn
#   Email: quinn.ryanx@gmail.com
#
#       Functions to read/write from/to the FPGA.
#       This module is called from the 'options.py' file.
#

import RPi.GPIO as GPIO
import binary



# GPIO pin definitions (Broadcom)
DOUT = [19, 13, 21, 20, 24, 25, 16, 26] # Data lines {MISC[3:0], DIP[4:1]}
RW = 17                                 # R/W BUTTON 0
ST = 18                                 # Strobe BUTTON 1
ACK = 23                                # Acknowledge



def setupGPIO(write):
    '''
        Set up GPIO pins. 'write' is TRUE
        for a write operation and FALSE
        for a read operation.
    '''

    GPIO.setmode(GPIO.BCM)                                              # Broadcom pin definitions
    GPIO.setup(DOUT, GPIO.OUT if write else GPIO.IN)                    # Controlled by Pi/FPGA on write/read
    GPIO.setup(RW, GPIO.OUT, initial=GPIO.LOW if write else GPIO.HIGH)  # Controlled by Pi. HI on read, LO on write.
    GPIO.setup(ST, GPIO.OUT, initial=GPIO.HIGH)                         # Controlled by Pi. Always HI before transaction.
    GPIO.setup(ACK, GPIO.IN)                                            # Controlled by FPGA



def cleanupGPIO():
    '''
        Cleanup GPIO pins. Placeholder
        for now just in case extra steps
        need to be taken during cleanup.
    '''

    GPIO.cleanup()



def send_command(command):
    '''
        Sends a 1 byte command to the FPGA and waits
        for a response.
    '''

    setupGPIO(True) # Set up the GPIO pins for the type of operation (write)

    # Python's array numbering system is backwards from the FPGA's bus labeling.
    # In Python, DOUT[0] and DOUT[7] correspond to MSB and LSB, respectively.
    GPIO.output(DOUT[0], 1)                                 # DOUT[7] (MSB) is always HI on write
    GPIO.output(DOUT[1:5], command)                         # DOUT[6:3] are used for data transmission
    GPIO.output(DOUT[5:8], [0, 0, 0])                       # DOUT[2:0] are used to send bitstreams
                                                            # so they stay low here.

    GPIO.output(ST, not GPIO.input(ST))                     # Toggle strobe so FPGA knows we're ready

    GPIO.wait_for_edge(ACK, GPIO.FALLING, timeout=30000)    # Waiting for ACK to go low within
                                                            # 30 sec (30000 ms). Might want to
                                                            # raise an exception if this
                                                            # function times out...

    GPIO.output(ST, not GPIO.input(ST))                     # Toggle strobe again

    GPIO.wait_for_edge(ACK, GPIO.RISING, timeout=30000)     # Wait for ACK to toggle again

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
        GPIO.output(DOUT[1:5], 0)                       # DOUT[6:3] are not used for the bitstream.
        GPIO.output(DOUT[5:8], bitstream[3*i:(3*i)+2])  # DOUT[2:0] are used for bitstream transmission.

        GPIO.output(ST, not GPIO.input(ST))             # Same timing structure as seen in the
                                                        # sendcommand() function.

        GPIO.wait_for_edge(ACK, GPIO.FALLING, timeout=30000)

        GPIO.output(ST, not GPIO.input(ST))

        GPIO.wait_for_edge(ACK, GPIO.RISING, timeout=30000)

    cleanupGPIO()



def read(outfile):
    '''
        Reads data back from the FPGA into
        the file 'outfile'. Uses DOUT[6:0].
    '''

    setupGPIO(False)    # Setup GPIO for the type of operation (read)

    f = open(outfile, 'w')  # Open text file to be written to.

    transac = 0
    while transac < 50:
        GPIO.wait_for_edge(ACK, GPIO.FALLING, timeout=30000)    # Wait for ACK to toggle signaling FPGA is sending data

        data = GPIO.input(DOUT[1:8])                            # Reading the data from DOUT excluding MSB
        print(binary.toStr(data, 7))
        f.write(binary.toStr(data, 7) + '\n')                   # Writing data to a text file
        transac += 1

        GPIO.output(ST, not GPIO.input(ST))                     # Toggle ST to signal we are done reading

        GPIO.wait_for_edge(ACK, GPIO.RISING, timeout=30000)     # Wait for ACK from FPGA

        GPIO.output(ST, not GPIO.input(ST))                     # Toggle ST to signal we are ready for next transaction.

    f.close()

    cleanupGPIO()

