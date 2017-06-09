# HGCal Test Beam DAQ
Contains the code used for the DAQ as well as extra code used to program FPGA's, check for cable disconnects, etc...

This entire folder should be copied to each Pi that is going to be used. This folder also contains the BCM2835 C library so it can be built on each Pi.

## HGCAL_2017_TB_DAQ_Test_V1
Contains the first version of the DAQ code. This uses the Raspberry Pi as the DAQ instead of the IP bus.


## System_Codes
Contains code used for various tasks. This directory contains code than can be used on both types of boards as well as readout and sync board specific codes.

* read_flash_memory.c:
  * Compiled as: read_flash_memory
  * Reads out all of the data stored in the flash memory.

* program_fpga.c:
  * Compiled as: program_fpga
  * Writes a configuration file to the flash memory. This file is then used to configure the FPGA after a power cycle.
  * Usage: sudo ./program_fpga < {ENTER HEX FILE HERE}

* pwr_cycle.c:
  * Compiled as: pwr_cycle
  * Power cycles an FPGA.

* read_board_ID.c
  * Compiled as: read_board_ID
  * Reads the board ID as specified by the first 8 DIP switches.

* set_IP_address:
  * Uses ReadBoardID and set's the IP address to 192.168.222.xxx where xxx is the board ID.

* get_board_type.c:
  * Compiled as: get_board_type
  * Reads the state of the last four DIP switches as well as the hardwired ones.

* compile:
  * Compiles all of the files to their respective outputs.


### RDOUT

### SYNC
* check_cable_disconnect.c:
  * Compiled as: check_cable_disconnect
  * Displays the status of each HDMI cable as connected/disconnected.

* run_on_boot.c:
  * Compiled as: run_on_boot
  * Script that is run on boot. Checks for cable disconnects and the clear signal.

* set_clk_delay.c:
  * Compiled as: set_clk_delay
  * Sets the clock delay of a given clock. The delay value supplied is in picoseconds.
  * Usage: sudo ./set_clk_delay [CLOCK NUMBER] [DELAY]

* calibrate_clk_delays.c:
  * Compiled as: calibrate_clk_delays
  * Sets all of the clock delays. The first clock delay is set to the delay value provided as the argument, and then lines up the rest of the clocks with the first one. The default delays must be measured first. The default delays (delays created due to path lengths) are specified in the DEFAULT_DELAYS array within the file. The delay value supplied is in picoseconds.
  * Usage: sudo ./calibrate_clk_delays [DELAY]

* sync_flash.hex & sync_flash2.hex:
  * The hex files used to program an FPGA with the program_fpga routine. sync_flash2.hex is a compressed version of the firmware.


## Other
Contains other code and old versions of the DAQ.
