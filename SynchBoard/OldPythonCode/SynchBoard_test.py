import spidev
import os
import time

print "Check"

spi = spidev.SpiDev()

#spi.open(0,1)
#to_send = [00001001, 00001001, 00001001]
#adc = spi.xfer2(to_send)
#print adc

#spi.open(0,1)
#to_send1 = [0xA, 0xA]
#adc = spi.xfer2(to_send)
#print adc

#for page in range(0,16):
#    print "Trying PAGE " + str(page) + " for EEPROM status"
#    spi.open(0,0)
#    spi.xfer2([page for i in range(0,5)])
#    spi.open(0,1)
#    print spi.xfer2([0b101,0,0])
#spi.close()

#print
#print
#print
print "Sending PAGE 12 for EEPROM"
spi.open(0,0)					# CS0 to get to the guy that connects us to what we want to talk to
t = spi.xfer2([0b1100 for i in range(0,5)])	# Sending the address we want to talk to many times
print t						# Idk if we should expect a response here

spi.open(0,1)					# Open what is (hopefully) the device at the address we sent earlier
print "Reading status"
print spi.xfer2([0b101,0])			# We should get a nonzero response in the last byte (Should be a value of 4 because BP0 is set by default)
print "setting WEL"
spi.writebytes([0b110])			        # Let's set the Write-Enable latch
print "Status again"
print spi.xfer2([0b101,0])			# Should get a value of 6 in the last byte because WEL was just set.
print "clearing WEL"
spi.writebytes([0b101])			        # Let's clear the Write-Enable latch
print "reading status again"
print spi.xfer2([0b101,0])			# Should get back to 4.
'''
print "Reading some bytes from memory"
mem = spi.xfer2([0b11,0,0])			# This code should read a byte starting from the address 0.
print mem
mem = spi.xfer2([0b11,0x0C,0])			# Trying some other addresses.
print mem
mem = spi.xfer2([0b11,0xAF,0])
print mem
mem = spi.xfer2([0b11,0xC0,0])
print mem

print "reading all memory addresses"
for i in range(0,256):				# Maybe one of these will have some data
    mem = spi.xfer2([0b11,i,0])
    if sum(mem)!=0:
        print mem


print "\nSending PAGE 13 for DIP thing"
spi.open(0,0)
t = spi.xfer2([0b1101 for i in range(0,5)])
print t

spi.open(0,1)
print "reading out hardwired resistors"
adc = spi.xfer2([0b01000001,0x13,0x13,0x13])
print adc

'''
spi.close()
