import RPi.GPIO as GPIO
import time


# Pin Definition(Broadcom)
DATA = [19, 13, 21, 20, 24, 25, 16, 26]# Data lines MISC[3:0] and DIP[4:1]
RW   = 17 #R/W BUTTON 0
ST   = 18 #Strobe BUTTON 1
ACK  = 23 # Acknowledge is GPIO 23

# Pin setup: Numbering scheme, PIN input/output definition
GPIO.setmode(GPIO.BCM)

#The Pi drives the RW and ST, the FPGA drives ACK
GPIO.setup(RW, GPIO.OUT)
GPIO.setup(ST, GPIO.OUT)
GPIO.setup(ACK, GPIO.IN)

#Currently hard-coded, but to be generalized into a functions that sets the data lines as INP/OUT depending on the operation
for i in range(0,8):
	GPIO.setup(DATA[i], GPIO.OUT)

# If the loop doesnt work comment the loop and uncomment the following 8 lines
#GPIO.setup(DATA[0], GPIO.OUT)
#GPIO.setup(DATA[1], GPIO.OUT)
#GPIO.setup(DATA[2], GPIO.OUT)
#GPIO.setup(DATA[3], GPIO.OUT)
#GPIO.setup(DATA[4], GPIO.OUT)
#GPIO.setup(DATA[5], GPIO.OUT)
#GPIO.setup(DATA[6], GPIO.OUT)
#GPIO.setup(DATA[7], GPIO.OUT)

#Hard-coded for first test: Hold data line to 11010000, RW to 1 and ST to 1 until ACK is high
GPIO.output(RW, GPIO.HIGH)

#setup 11010000 on the data lines
GPIO.output(DATA[0], GPIO.HIGH)
GPIO.output(DATA[1], GPIO.HIGH)
GPIO.output(DATA[2], GPIO.LOW)
GPIO.output(DATA[3], GPIO.HIGH)
GPIO.output(DATA[4], GPIO.LOW)
GPIO.output(DATA[5], GPIO.LOW)
GPIO.output(DATA[6], GPIO.LOW)
GPIO.output(DATA[7], GPIO.LOW)

#set strobe high
GPIO.output(ST, GPIO.HIGH)


#keep ST high until ACK is high[Another option is to even do nothing here as ST will remain high as its set to be high]
while (GPIO.input(ACK) != 1):
	GPIO.output(ST, GPIO.HIGH)

GPIO.output(ST, GPIO.LOW)#on receiving ACK set ST to low

#Clean up GPIO states
GPIO.cleanup()
