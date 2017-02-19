#
#   Author: Ryan Quinn
#   Email: quinn.ryanx@gmail.com
#
#       Sends a bitstream to the FPGA to program the SKIROCs.
#

import RPi.GPIO as GPIO
import binary, readwrite, time



# GPIO pin definitions (Broadcom)
DOUT = [19, 13, 21, 20, 24, 25, 16, 26] # Data lines {MISC[3:0], DIP[4:1]}
RW = 17                                 # R/W BUTTON 0
ST = 18                                 # Strobe BUTTON 1
ACK = 23                                # Acknowledge



def programming_options():
    '''
        Provides the user with options to
        program the FPGA. The .csv files
        containing the bits are specified
        within this function.
    '''

    print("Programming Operation")
    print("OPTIONS:-[Note: Only one of the options below are valid. No protection for any other option.]")
    print("1) Default")
    print("2) Charge Sensitive")
    print("3) Current Sensitive")

    choice = int(input("Programming Choice: ")) - 1

    strtoprint = [
        'Default Programming',
        'Charge Sensitive Programming',
        'Current Sensitive Programming',
        ]
    files = [
        'Parse_Skiroc2cms_Programming_Default.csv',
        'Parse_Skiroc2cms_Programming_ChargeSensitive.csv',
        'Parse_Skiroc2cms_Programming_CurrentSensitive.csv',
        ]

    print(strtoprint[choice])

    bitstream = create_bitstream_buffer(files[choice])
    if -99 in bitstream:
        print('PARSING UNSUCCESSFUL! DO NOT PROCEED.')
        cleanupGPIO()
        exit()
    else:
        for bit in bitstream:
            print(bit)
    print("\nBit Stream created to be pushed")
    print("Write Prog Mode Command")
    readwrite.send_command(3)
    print("Now the bit stream will be pushed")

    send_bitstream(bitstream)




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



def create_bitstream_buffer(bitfile):
    '''
        Creates a bitstream from the .csv
        file 'bitfile'. This bitstream can
        then be sent to the FPGA.
    '''

    f = open(bitfile, 'r')
    bitstream = [-99 for i in range(0,384)]
    f.close()



def send_bitstream(bitstream):
    '''
        Sends a bitstream of length 384 to the
        FPGA using the last 3 bits of DOUT.
    '''

    setupGPIO(True)

    # Sending the bitstream to the FPGA. This is done four times to program each SKIROC.
    for n in range(0,4):
        for i in range(0, 128):
            GPIO.output(DOUT[0], 1)                         # DOUT MSB is HI for write
            GPIO.output(DOUT[1:5], 0)                       # DOUT[6:3] are not used for the bitstream.
            GPIO.output(DOUT[5:8], bitstream[3*i:(3*i)+2])  # DOUT[2:0] are used for bitstream transmission.

            time.sleep(0.01)                                # To be safe
            GPIO.output(ST, not GPIO.input(ST))             # Same timing structure as seen in the
                                                            # readwrite.send_command() function.

            wait_for_toggle(ACK, GPIO.FALLING, 30000)

            GPIO.output(ST, not GPIO.input(ST))

            wait_for_toggle(ACK, GPIO.RISING, 30000)
        print('Push', n+1, 'complete')

    print('Performing interleaved write/read operations to read back the bitstream')

    cleanupGPIO()



def wait_for_toggle(pin, edge_type, timeout):
    '''
        Waits for 'pin' to change state on a
        'edge_type' edge within 'timeout' ms.
        If it times out, the program restarts.
    '''
    chan = GPIO.wait_for_edge(pin, edge_type, timeout)
    if chan == None:
        print("FPGA did not respond within 30 seconds")
        gotomain()



def gotomain():
    '''
        Goes back to main() function of
        options.py.
    '''
    import TestBoard_DAQ
    TestBoard_DAQ.main()
