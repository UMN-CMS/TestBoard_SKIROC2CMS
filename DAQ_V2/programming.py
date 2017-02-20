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
        readwrite.cleanupGPIO()
        exit()
    else:
        for bit in bitstream:
            print(bit)
    print("\nBit Stream created to be pushed")
    print("Write Prog Mode Command")
    readwrite.send_command(3)
    print("Now the bit stream will be pushed")

    bitstream_readback = send_bitstream(bitstream)                  # Sends a bitstream to FPGA. If the bitstream that
    if bitstream==bitstream_readback:                               # was read back from the FPGA is not the same,
        print('Programming Successful')                             # then programming was unsuccessful.
    else:
        print('Programming Unsuccessful')



def create_bitstream_buffer(bitfile):
    '''
        Creates a bitstream from the .csv
        file 'bitfile'. This bitstream can
        then be sent to the FPGA.
    '''

    f = open(bitfile, 'r')
    bitstream = [-99 for i in range(0,384)]
    for line in f:
        arr = line.rstrip().split(',')
        numbits = int(arr[0])
        startpt = int(arr[1])
        data = arr[2]
        if data=='ones':
            for i in range(startpt, numbits):
                bitstream[i] = 1
        else if data=='zeros':
            for i in range(startpt, numbits):
                bitstream[i] = 0
        else:
            for i in range(0, numbits):
                bitstream[i+startpt] = int(data[i])

    f.close()

    return bitstream



def send_bitstream(bitstream):
    '''
        Sends a bitstream of length 384 to the
        FPGA using the last 3 bits of DOUT.
    '''

    readwrite.setupGPIO(True)

    # Sending the bitstream to the FPGA. This is done four times to program each SKIROC.
    for n in range(0,4):
        for i in range(0, 128):
            GPIO.output(DOUT[0], 1)                         # DOUT MSB is HI for write
            GPIO.output(DOUT[1:5], 0)                       # DOUT[6:3] are not used for the bitstream.
            GPIO.output(DOUT[5:8], bitstream[3*i:(3*i)+2])  # DOUT[2:0] are used for bitstream transmission.

            time.sleep(0.01)                                # To be safe
            GPIO.output(ST, not GPIO.input(ST))             # Same timing structure as seen in the
                                                            # readwrite.send_command() function.

            readwrite.wait_for_toggle(ACK, GPIO.FALLING, 30000)

            GPIO.output(ST, not GPIO.input(ST))

            readwrite.wait_for_toggle(ACK, GPIO.RISING, 30000)
        print('Push', n+1, 'complete')

    print('Performing interleaved write/read operations to read back the bitstream')

    bitstream_readback = []
    for i in range(0,128):
        readwrite.setupGPIO(True)

        GPIO.output(DOUT[0], 1)
        GPIO.output(DOUT[1:5], 0)
        GPIO.output(DOUT[5:8], bitstream[3*i:3*i+3])

        GPIO.output(ST, not GPIO.input(ST))

        readwrite.wait_for_toggle(ACK, GPIO.FALLING, 30000)

        GPIO.output(ST, not GPIO.input(ST))

        readwrite.wait_for_toggle(ACK, GPIO.RISING, 30000)

        readwrite.setupGPIO(False)

        readwrite.wait_for_toggle(ACK, GPIO.FALLING, 30000)

        for n in range(5,8):
            bitstream_readback.append(int(GPIO.input(n)))

        GPIO.output(ST, not GPIO.input(ST))

        readwrite.wait_for_toggle(ACK, GPIO.RISING, 30000)

    print("Programming sequence complete")

    readwrite.cleanupGPIO()

    return bitstream_readback
