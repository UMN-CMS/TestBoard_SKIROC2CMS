import RPi.GPIO as GPIO
import time
import sys
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
###################For Programming##################
Num_bits = 384 #Registers 0-383
Reversed_Register_Address1 = 19
Reversed_Register_Address2 = 25
Reversed_Register_Address3 = 31
buffer_bits_for_programming = [-99 for i in range(Num_bits)]# cross-check if any address has a negative value it means parsing was un-successful
buffer_bits_for_programming_read_back = [-99 for i in range(Num_bits)]
#####################################################
# Pin setup: Numbering scheme, PIN input/output definition
GPIO.setmode(GPIO.BCM)
#The Pi drives the RW and ST, the FPGA drives ACK
GPIO.setup(RW, GPIO.OUT)
GPIO.setup(ST, GPIO.OUT)
GPIO.setup(ACK, GPIO.IN)

####################################################################################################################
def Create_BitStream_Buffer(fileName):
	fp = open(filename, 'r')
	line = fp.readline()
############################Start parsing file##############################################
	while line != '':
		buffer_bit_address_size = line[0:line.find(",")]
		tmp_line = line[line.find(",")+1:line.find("\n")+1]
		buffer_bit_address = tmp_line[0:tmp_line.find(",")]
		buffer_bits_choice = tmp_line[tmp_line.find(",")+1:tmp_line.find("\n")]

		if(buffer_bits_choice == 'ones'):
			for iii in range(int(buffer_bit_address),int(buffer_bit_address)+int(buffer_bit_address_size)):
				buffer_bits_for_programming[iii] = 1
		elif(buffer_bits_choice == 'zeros' or buffer_bits_choice == 'NO'):
			for iii in range(int(buffer_bit_address),int(buffer_bit_address)+int(buffer_bit_address_size)):
				buffer_bits_for_programming[iii] = 0

		elif(int(buffer_bit_address) == Reversed_Register_Address1 or int(buffer_bit_address) == Reversed_Register_Address2 or int(buffer_bit_address) == Reversed_Register_Address3):
			counter = int(buffer_bit_address_size) - 1
			for iii in range(int(buffer_bit_address),int(buffer_bit_address)+int(buffer_bit_address_size)):
				buffer_bits_for_programming[iii] = int(buffer_bits_choice[counter])
				counter -= 1
		else:
			counter = 0
			for iii in range(int(buffer_bit_address),int(buffer_bit_address)+int(buffer_bit_address_size)):
				buffer_bits_for_programming[iii] = int(buffer_bits_choice[counter])
				counter += 1

		line = fp.readline()
#######################################File parsed###########################################
	fp.close()

####################################################################################################################
def Test_Write_Programming_Quad():
	for i in range(0,8):
                GPIO.setup(DATA[i], GPIO.OUT)

        GPIO.output(RW, GPIO.LOW)# indicates its a write operation
        GPIO.output(ST, GPIO.HIGH)# indicates the command to be written has not yet been setup on the DOUT lines
# Now depending on the command to be written setup the DOUT lines accordingly
# Hardcoded for now, there must be a smarter way to do this[since need something that works quickly hence the vanilla implementation]
# Here we dont care for the states of the DOUT_Data lines only care for the last 3
        GPIO.output(DATA[0], GPIO.HIGH)# has to be high
	GPIO.output(DATA[1], GPIO.LOW)
        GPIO.output(DATA[2], GPIO.LOW)
        GPIO.output(DATA[3], GPIO.LOW)
        GPIO.output(DATA[4], GPIO.LOW)
	push_counter = 1# to push 4 times
	while (push_counter < 5):
#########################One full push operation takes place in the for loop########
		for iii in range(Num_bits-1,-1,-3): 		  
			GPIO.output(DATA[5], buffer_bits_for_programming[iii-2])
		        GPIO.output(DATA[6], buffer_bits_for_programming[iii-1])
		        GPIO.output(DATA[7], buffer_bits_for_programming[iii])
##############################DOUT has been setup############################
#set strobe LOW
		        GPIO.output(ST, GPIO.LOW)
#keep ST high until ACK is high[Another option is to even do nothing here as ST will remain high as its set to be high]
		        while (GPIO.input(ACK) != 0):
		                GPIO.output(ST, GPIO.LOW)
		        GPIO.output(ST, GPIO.HIGH)#on receiving ACK set ST to high
#################################Push Complete######################################
		print push_counter,' push has been done'	
		push_counter+=1
#########On coming out of the while loop 4 pushes have been done. Now interleaved R/W operation###############
	print 'We shall now perform interleaved Write and read operations'
	print
	for iii in range(Num_bits-1,-1,-3):	
#############################First a 3 bit write#######################################
		for i in range(0,8):
	                GPIO.setup(DATA[i], GPIO.OUT)

		GPIO.output(RW, GPIO.LOW)# indicates its a write operation
	        GPIO.output(ST, GPIO.HIGH)# indicates the command to be written has not yet been setup on the DOUT lines
# Now depending on the command to be written setup the DOUT lines accordingly
# Hardcoded for now, there must be a smarter way to do this[since need something that works quickly hence the vanilla implementation]
# Here we dont care for the states of the DOUT_Data lines only care for the last 3
	        GPIO.output(DATA[0], GPIO.HIGH)# has to be high
	        GPIO.output(DATA[1], GPIO.LOW)
	        GPIO.output(DATA[2], GPIO.LOW)
	        GPIO.output(DATA[3], GPIO.LOW)
	        GPIO.output(DATA[4], GPIO.LOW)
		GPIO.output(DATA[5], buffer_bits_for_programming[iii-2])
                GPIO.output(DATA[6], buffer_bits_for_programming[iii-1])
                GPIO.output(DATA[7], buffer_bits_for_programming[iii])
		print 'Wrote: ', buffer_bits_for_programming[iii-2], buffer_bits_for_programming[iii-1], buffer_bits_for_programming[iii]
##############################DOUT has been setup############################
#set strobe LOW
                GPIO.output(ST, GPIO.LOW)
#keep ST high until ACK is high[Another option is to even do nothing here as ST will remain high as its set to be hig
		while (GPIO.input(ACK) != 0):
                	GPIO.output(ST, GPIO.LOW)
		GPIO.output(ST, GPIO.HIGH)#on receiving ACK set ST to high
#############################Completed 3 bit write, Now do a read#######################################
                GPIO.output(RW, GPIO.HIGH)# indicates its a write operation
                GPIO.output(ST, GPIO.HIGH)# indicates the Readiness to read data on the DOUT lines

		for i in range(0,8):
	                GPIO.setup(DATA[i], GPIO.IN)

##################Now wait for ACK#########################################################
		if (GPIO.input(ACK) == 0):
			print 'Read: ', GPIO.input(DATA[5]),GPIO.input(DATA[6]),GPIO.input(DATA[7])
			buffer_bits_for_programming_read_back[iii] = GPIO.input(DATA[7])
			buffer_bits_for_programming_read_back[iii-1] = GPIO.input(DATA[6])
			buffer_bits_for_programming_read_back[iii-2] = GPIO.input(DATA[5])
			GPIO.output(ST, GPIO.LOW)# indicates DATA has been read, and ACK may be removed         
                        while (GPIO.input(ACK) != 1):#keep ST low till ACK is high
                                GPIO.output(ST, GPIO.LOW)
			GPIO.output(ST, GPIO.HIGH)# ready for the next transaction
#################################One Read operation of 3 bits done######################################################
	print 'Programming sequence complete'

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
	while (default_timer() - start) < 5: # wait for a max. of 5 seconds for ACK
		if (GPIO.input(ACK) == 0):
			read_counter = read_counter + 1
			print 'Transaction: ', read_counter
			print
			print 'Data: \n'
			for i in range(0,8):
				print GPIO.input(DATA[i]),
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
	if Choice == 3:
		print "Programming Operation"
		print '\nOPTIONS:-[Note: Only one of the options below are valid, No protection for any other option]\n'
	        print '1) Default\n'
	        print '2) Charge Sensitive\n'
	        print '3) Current Sensitive\n'
		Programming_Choice = input('Programming Choice : ')
		while Programming_Choice == 1 or Programming_Choice == 2 or Programming_Choice == 3:
			if Programming_Choice == 1:
				print 'Default Programming'
				Create_BitStream_Buffer("Parse_Skiroc2cms_Programming_Default.csv")
			elif Programming_Choice == 2:
				print 'Charge Sensitive Programming'
				Create_BitStream_Buffer("Parse_Skiroc2cms_Programming_ChargeSensitive.csv")
			else:
				print 'Current Sensitive Programming'
                                Create_BitStream_Buffer("Parse_Skiroc2cms_Programming_CurrentSensitive.csv")
###################################Print out the bit stream##############################################################		
			for iii in range(0,Num_bits):
			        if(buffer_bits_for_programming[iii] < 0):
			                print 'PARSING UNSUCESSFULL! DO NOT PROCEED.'
					GPIO.cleanup()
					quit()
			        else:
			                print buffer_bits_for_programming[iii],
			print 'Bit Stream created to be pushed'
#########################################################################################################################			
		#First invoke the SetProgMode Write Command
		print 'Write Prog Mode'
		Test_Write(3)		
		print 'Now the bit stream shall be pushed'
		Test_Write_Programming_Quad()
		Sanity_Flag = 0		
		for iii in range(0,Num_bits):
			if(buffer_bits_for_programming_read_back[iii] != buffer_bits_for_programming[iii]):
				Sanity_Flag = 1
		if(Sanity_Flag == 0):
			print 'MATCH OBTAINED!!'
		else:
			print 'PROGRAMMING UNSUCCESSFUL!!'

#Clean up GPIO states
GPIO.cleanup()
	
