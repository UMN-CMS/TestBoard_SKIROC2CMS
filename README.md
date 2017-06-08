# HGCal Test Beam DAQ
Contains the code used for the DAQ as well as extra code used to program FPGA's, check for cable disconnects, etc...


## HGCAL_2017_TB_DAQ_Test_V1


## System_Codes
Contains code used for various tasks. This directory contains code than can be used on both types of boards as well as readout and sync board specific codes.


### RDOUT
### SYNC
read_flash_memory.c:
	Compiled as: read_flash_memory
	Reads out all of the data stored in the flash memory.

program_fpga.c:
	Compiled as: program_fpga
	Writes a configuration file to the flash memory. This file is then used to configure the FPGA after a power cycle.
	Usage:
		sudo ./program_fpga < {ENTER HEX FILE HERE}

read_board_ID.c
	Compiled as: read_board_ID
	Reads the board ID as specified by the first 8 DIP switches.

set_IP_address:
	Uses ReadBoardID and set's the IP address to 192.168.222.xxx where xxx is the board ID.

pwr_cycle.c:
	Compiled as: pwr_cycle
	Power cycles an FPGA.

check_cable_disconnect.c:
	Compiled as: check_cable_disconnect
	Displays the status of each HDMI cable as connected/disconnected.



compile:
	Compiles all of the C files listed above to the file specified in the "Compiled as:" line.

Tests/:
	Contains code used to test the board's SPI communication.

OldPythonCode/:
	Contains the original python SPI code.


## Other
