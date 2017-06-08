import spidev
import time
import random

BYTES = 16							# can only send 16 bytes at a time.
byte_array = [random.randint(0,255) for i in range(0,BYTES)]	# random values
speeds = [1000000*MHz for MHz in [0.5, 1, 2, 4, 8, 16, 32]]	# all possible clock speeds

spi = spidev.SpiDev()

spi.open(0,0)
spi.writebytes([12])						# for EEPROM

spi.open(0,1)
spi.writebytes([0b110])						# set WEL
spi.writebytes([0b10,0] + byte_array)				# write all data
while spi.xfer2([0b101,0])[1] % 2:				# wait for writes to be done
    continue


for clockspeed in speeds:
    spi.max_speed_hz = int(clockspeed)				# changing SPI speed
    time.sleep(0.25)						# wait just in case
    read_back = []
    for address in range(0, BYTES):				# read all the data back
        mem = spi.xfer2([0b11,address,0])[2]
        read_back.append(mem)

    if read_back != byte_array:					# compare the two arrays
        print str(clockspeed/1000000.) + " MHz: Failure!"
    else:
        print str(clockspeed/1000000.) + " MHz: Success!"

    time.sleep(0.25)						# wait just in case
