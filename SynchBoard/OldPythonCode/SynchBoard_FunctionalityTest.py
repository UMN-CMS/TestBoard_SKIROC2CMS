import spidev
import os
import time

print "Check"

spi = spidev.SpiDev()

print "\n\nSending PAGE 13 to the FPGA"
spi.open(0,0)
spi.writebytes([13])				# we only need to send it once - it's perfectly functional this way.

print "opening PAGE 13"
spi.open(0,1)
print "Pulling up on PORTA"
spi.writebytes([0b01000000,0x0C,0b11111111])	# need to pull up these resistors. 0x0C is the GPPUA address. the last byte turns on all pull ups.
print "DIPs for PORTA"
adc = spi.xfer2([0b01000001,0x12,0])		# read command, then GPIOA address, then byte to push back the data.
print adc[2]					# should be 246 (0b11110110). DIP switches are HI when they are not pressed in.
						# MSB is SW7 (GPA7), LSB is SW0 (GPA0).

print "Pulling up on PORTB"
spi.writebytes([0b01000000,0x0D,0b1111])	# same procedure as before, except only pulling up the last four because the others are hardwired.
print "DIPs and hardwired resistors for PORTB"
adc = spi.xfer2([0b01000001,0x13,0])		# same as before. Should be 21 (0b00010101). MSB is SW15 (GPB7), LSB is SW8 (GPB0)
print adc[2]




print "\n\nopening the EEPROM by sending PAGE 12 to the FPGA"
spi.open(0,0)
spi.writebytes([12])				# again, only send it once

print "reading the mac address"
spi.open(0,1)
for i in range(250,256):
    mem = spi.xfer2([0b11,i,0])[2]		# MAC address is stored in the last 6 bytes of the EEPROM's memory.
    print hex(mem)				# Should be d8:80:39:ef:a8:a0

print "current status"
status = spi.xfer2([0b101,0])[1]		# should be 0b100 because WEL is off by default. if not, it was previously set and not cleared.
print bin(status)

print "set write enable latch, writing address number to first 10 addresses and waiting for each write to finish"
for address in range(0,10):
    spi.writebytes([0b110])			# setting WEL so we can write. It gets reset after every successful write, so I put it in the while loop.
    spi.writebytes([0b10,address,address])	# Sending the write command, then the address, then the byte to write.
    while spi.xfer2([0b101,0])[1] % 2:		# Waiting for the last digit in the STATUS command to turn to 0.
        continue				# The last digit of the STATUS command indicates a write is still in progress.

print "current status"
status = spi.xfer2([0b101,0])[1]		# should be 0b100 now because WEL is off again.
print bin(status)

print "reading from first 10 addresses"
for address in range(0,10):
    mem = spi.xfer2([0b11,address,0])[2]	# sending read command, then address to read from, then a null byte to push the data back.
    print hex(mem)

print "clearing the addresses for next time"
for address in range(0,10):			# same procedure as last time.
    spi.writebytes([0b110])
    spi.writebytes([0b10,address,0])
    while spi.xfer2([0b101,0])[1] % 2:
        continue		
for address in range(0,10):
    mem = spi.xfer2([0b11,address,0])[2]
    print hex(mem)


spi.close()
