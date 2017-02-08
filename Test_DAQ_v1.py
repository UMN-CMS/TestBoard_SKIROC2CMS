import RPi.GPIO as GPIO
import time
from timeit import default_timer

def Print_Options():
	print '\nOPTIONS:-[Note: Only one of the options below are valid, No protection for any other option]\n'
	print '1) Write a command\n'
	print '2) Read operation\n'
	print '3) Programming\n'
	print '0) Quit\n'


def Write_Options():
        print '\nOPTIONS:-[Note: Only one of the options below are valid, No protection for any other option]\n'
        print '1) NOP 0000\n'
        print '2) RstB pulse 0001\n'
        print '3) SetProgMode 0010\n'
        print '4) SetDAQMode 0011\n'
        print '5) ArmTrigger 0100\n'
        print '6) Trigger 0101\n'
        print '7) StartConv 0110\n'
	print '8) StartReadOut 0111\n'
        print '9) ReadEvent 1000\n'
        print '10) SetSelect 1001\n'
        print '11) WrConf3Bit 1010\n'
        print '12) ReadStatus 1011\n'
	print '0)  Exit\n'
#        print '12) Unused 1 1100\n'
#        print '13) Unused 2 1101\n'
#        print '14) Unused 3 1110\n'
#        print '15) Unused 4 1111\n'

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

####################################################################################################################
def Test_Write(Command):
	for i in range(0,8):
		GPIO.setup(DATA[i], GPIO.OUT) 
	
	GPIO.output(RW, GPIO.LOW)# indicates its a write operation
        GPIO.output(ST, GPIO.HIGH)# indicates the command to be written has not yet been setup on the DOUT lines
# Now depending on the command to be written setup the DOUT lines accordingly
# Hardcoded for now, there must be a smarter way to do this[since need something that works quickly hence the vanilla implementation]
	GPIO.output(DATA[0], GPIO.HIGH)# has to be high
#The following three are the programming bits so dont care while sending a command
	GPIO.output(DATA[5], GPIO.LOW)
	GPIO.output(DATA[6], GPIO.LOW)
	GPIO.output(DATA[7], GPIO.LOW)
	if Command == 1:
		GPIO.output(DATA[1], GPIO.LOW)
		GPIO.output(DATA[2], GPIO.LOW)
		GPIO.output(DATA[3], GPIO.LOW)
		GPIO.output(DATA[4], GPIO.LOW)
	elif Command == 2:
                GPIO.output(DATA[1], GPIO.LOW)
                GPIO.output(DATA[2], GPIO.LOW)
                GPIO.output(DATA[3], GPIO.LOW)
                GPIO.output(DATA[4], GPIO.HIGH)
	elif Command == 3:
                GPIO.output(DATA[1], GPIO.LOW)
                GPIO.output(DATA[2], GPIO.LOW)
                GPIO.output(DATA[3], GPIO.HIGH)
                GPIO.output(DATA[4], GPIO.LOW)
	elif Command == 4:
                GPIO.output(DATA[1], GPIO.LOW)
                GPIO.output(DATA[2], GPIO.LOW)
                GPIO.output(DATA[3], GPIO.HIGH)
                GPIO.output(DATA[4], GPIO.HIGH)
	elif Command == 5:
                GPIO.output(DATA[1], GPIO.LOW)
                GPIO.output(DATA[2], GPIO.HIGH)
                GPIO.output(DATA[3], GPIO.LOW)
                GPIO.output(DATA[4], GPIO.LOW)
	elif Command == 6:
                GPIO.output(DATA[1], GPIO.LOW)
                GPIO.output(DATA[2], GPIO.HIGH)
                GPIO.output(DATA[3], GPIO.LOW)
                GPIO.output(DATA[4], GPIO.HIGH)
	elif Command == 7:
                GPIO.output(DATA[1], GPIO.LOW)
                GPIO.output(DATA[2], GPIO.HIGH)
                GPIO.output(DATA[3], GPIO.HIGH)
                GPIO.output(DATA[4], GPIO.LOW)
	elif Command == 8:
                GPIO.output(DATA[1], GPIO.LOW)
                GPIO.output(DATA[2], GPIO.HIGH)
                GPIO.output(DATA[3], GPIO.HIGH)
                GPIO.output(DATA[4], GPIO.HIGH)
	elif Command == 9:
                GPIO.output(DATA[1], GPIO.HIGH)
                GPIO.output(DATA[2], GPIO.LOW)
                GPIO.output(DATA[3], GPIO.LOW)
                GPIO.output(DATA[4], GPIO.LOW)
	elif Command == 10:
                GPIO.output(DATA[1], GPIO.HIGH)
                GPIO.output(DATA[2], GPIO.LOW)
                GPIO.output(DATA[3], GPIO.LOW)
                GPIO.output(DATA[4], GPIO.HIGH)
	elif Command == 11:
                GPIO.output(DATA[1], GPIO.HIGH)
                GPIO.output(DATA[2], GPIO.LOW)
                GPIO.output(DATA[3], GPIO.HIGH)
                GPIO.output(DATA[4], GPIO.LOW)
	else:
        	GPIO.output(DATA[1], GPIO.HIGH)
                GPIO.output(DATA[2], GPIO.LOW)
                GPIO.output(DATA[3], GPIO.HIGH)
                GPIO.output(DATA[4], GPIO.HIGH)
###############DOUT has been setup############################
#set strobe LOW
	GPIO.output(ST, GPIO.LOW)
#keep ST high until ACK is high[Another option is to even do nothing here as ST will remain high as its set to be high]
	while (GPIO.input(ACK) != 0):
        	GPIO.output(ST, GPIO.LOW)

	GPIO.output(ST, GPIO.HIGH)#on receiving ACK set ST to high
###################################################################################################################################	

####################################################################################################################
def Test_Read():
	read_counter = 0
        for i in range(0,8):
                GPIO.setup(DATA[i], GPIO.IN)

        GPIO.output(RW, GPIO.HIGH)# indicates its a write operation
        GPIO.output(ST, GPIO.HIGH)# indicates the Readiness to read data on the DOUT lines
#Now wait for ACK
	start = default_timer()
	while (default_timer() - start) < 30: # wait for a max. of 30 seconds for ACK
		if (GPIO.input(ACK) == 0):
			read_counter = read_counter + 1
			print 'Transaction: ', read_counter
			print
			print 'Data: \n'
			for i in range(0,8):
				print GPIO.input(DATA[i])
			print
			#Data has been read
			GPIO.output(ST, GPIO.LOW)# indicates DATA has been read, and ACK may be removed		
			while (GPIO.input(ACK) != 1):#keep ST low till ACK is high
		                GPIO.output(ST, GPIO.LOW)
			GPIO.output(ST, GPIO.HIGH)# ready for the next transaction
			start = default_timer()

Choice = 1 #tmp value to enter the loop, another option is do-while

while Choice == 1 or Choice == 2 or Choice == 3:
	Print_Options()
	Choice = input('Choice : ')
	if Choice == 1:
		Write_Choice = 1 #tmp value to enter the loop, another option is do-while
		while Write_Choice > 0 and Write_Choice < 13:
			Write_Options()
			Write_Choice = input('Write Choice : ')
			Test_Write(Write_Choice)
	if Choice == 2:
		Test_Read()	
