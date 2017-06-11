//--------------------------------------------------------------------------------------//
// COMPILE: 										//
// gcc -g calibrate_clk_delays.c -o calibrate_clk_delays -l bcm2835 -Wall -std=c11	//
//--------------------------------------------------------------------------------------//
// USAGE: 										//
// sudo ./calibrate_clk_delays [Delay Value in picoseconds]				//
//--------------------------------------------------------------------------------------//
//	Set all the clock delays. Sets the first clock delay to the delay value		//
//	provided as the argument, and then lines up the rest of the clocks with the	//
//	first one. The default delays must be measured first. The default delays are	//
//	specified in the DEFAULT_DELAYS array.						//
//--------------------------------------------------------------------------------------//


/*** Includes ***/
#include <bcm2835.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>



/*** SPI Functions ***/
void init_spi();
void end_spi();
void send_page(char page);
void make_pins_output(char gpio_iodir, int pins_to_change[], int numPins);
void make_all_pins_input(char gpio_iodir);

/*** Bit Manipulations ***/
char flip_bit(char state, int bitnum);
char write_bit(char state, int bitnum, int val);
unsigned int reversed(unsigned int v);

/*** SDI Transactions ***/
void sdi_clock_bit(char gpio, int SDIN, int SCLK, int bit);
void sdi_send_data(char gpio, int SLOAD, int SDIN, int SCLK, char *to_send);

/*** Global Vars ***/
int REG_LEN = 11;// shift register is 11 bits long.
int NUM_CLK_DELS = 8;

double DEFAULT_DELAYS[] = {// the delays between clocks with no added delay
	2.20016,
	2.12744,
	2.23652,
	2.16380,
	2.20016,
	2.16380,
	2.16380,
	2.12744
	};




/*** Main ***/
int main (int argc, char *argv[]) {

	if(argc != 2) {
		fprintf(stderr, "ERROR: Usage\n");
		exit(1);
	}

	// getting delay from argument
	int usr_delay = atoi(argv[1]);// user should enter desired delay in picoseconds
	unsigned int delay = usr_delay / 11;// 11 picoseconds increment size
	if(delay > 511) {
		fprintf(stderr, "ERROR: Delay must be less than 5622 picoseconds\n");// max 9 bit delay
		exit(1);
	}
	double real_delay_ns = (delay*11.) / 1000.;// actual delay in nanoseconds to be added to the first clock delay chip


	// Important variables
	int SLOAD_B[] = {6, 2};			// toggled to latch the bits into the shift register of the delay chip
	int SDIN_B[] = {5, 1};			// serial data line
	int SCLK_B[] = {4, 0};			// serial clock line

	int SLOAD_A[] = {6, 2};			// same as GPIOB
	int SDIN_A[] = {5, 1};			// there are two clock delay chips per set of GPIO pins.
	int SCLK_A[] = {4, 0};			// they just happen to be at the same pins on both sides

	char GPIOA = 0x12, GPIOA_IODIR = 0x00;	// GPIO pin access register and GPIO pin I/O direction access register
	char GPIOB = 0x13, GPIOB_IODIR = 0x01;

	int MSEL = 0;				// Ensures the two clock delays within each chip act independently of eachother


	// getting clock delay chip from argument
	int SLOAD, SDIN, SCLK, PSEL;
	char GPIO, IODIR;
	int clk_del_select;
	for(clk_del_select = 0; clk_del_select < NUM_CLK_DELS; clk_del_select++) {
		if(clk_del_select < 4) {
			int chipnum = clk_del_select > 1;
			SLOAD = SLOAD_B[chipnum];
			SDIN = SDIN_B[chipnum];
			SCLK = SCLK_B[chipnum];
			GPIO = GPIOB;
			IODIR = GPIOB_IODIR;
			PSEL = clk_del_select % 2;
		}
		else if(clk_del_select < 8) {
			int chipnum = clk_del_select > 5;
			SLOAD = SLOAD_A[chipnum];
			SDIN = SDIN_A[chipnum];
			SCLK = SCLK_A[chipnum];
			GPIO = GPIOA;
			IODIR = GPIOA_IODIR;
			PSEL = clk_del_select % 2;
		}
		else {
			fprintf(stderr, "ERROR: The clock delay chip must be less than 8\n");
			exit(1);
		}


		// Calculate the correct delay
		double diff_ns = DEFAULT_DELAYS[0] + real_delay_ns - DEFAULT_DELAYS[clk_del_select];// difference between this clock and the first one
		unsigned int calib_delay = (diff_ns * 1000.) / 11;// delay to be added in 11 picosecond increments
		if(calib_delay > 511) {// max 9 bit delay
			fprintf(stderr, "The calibration delay for chip %i is too large. It must be less than 5622 picoseconds.\n", clk_del_select);
			exit(1);
		}


		// Setting up SPI
		init_spi();


		// Send PAGE 14 to talk to MCP that controls the clock delay modules
		send_page(0xE);

		
		// Setting SLOAD, SDIN, SCLK as output
		unsigned int to_be_output[] = {SLOAD, SDIN, SCLK};
		make_pins_output(IODIR, to_be_output, 3);


		// send PSEL, then MSEL, then the delay byte (LSB first!)
		char to_send[REG_LEN]; to_send[0] = PSEL; to_send[1] = MSEL;
		int bitnum;
		for(bitnum = 0; bitnum < REG_LEN-2; bitnum++) {
			to_send[bitnum+2] = (calib_delay >> bitnum) & 1;
		}
		sdi_send_data(GPIO, SLOAD, SDIN, SCLK, to_send);


		// make everything input again
		make_all_pins_input(IODIR);

		// let the user know
		printf("Clock delay chip number %i was given a delay of %i picoseconds.\n", clk_del_select, calib_delay*11);
	}


	// Closing time
	end_spi();
	return 0;
}



/*** SDI Transactions ***/
void sdi_clock_bit(char gpio, int SDIN, int SCLK, int bit) {

	char STATE = 0;
	char write_state[] = {0x40, gpio, STATE};
	bcm2835_spi_writenb(write_state, sizeof(write_state));

	STATE = write_bit(STATE, SDIN, bit);
	write_state[2] = STATE;
	bcm2835_spi_writenb(write_state, sizeof(write_state));

	STATE = flip_bit(STATE, SCLK);
	write_state[2] = STATE;
	bcm2835_spi_writenb(write_state, sizeof(write_state));

	STATE = flip_bit(STATE, SCLK);
	write_state[2] = STATE;
	bcm2835_spi_writenb(write_state, sizeof(write_state));

	STATE = 0;
	write_state[2] = STATE;
	bcm2835_spi_writenb(write_state, sizeof(write_state));
}


void sdi_send_data(char gpio, int SLOAD, int SDIN, int SCLK, char *to_send) {

	// Send in that shit
	int bitnum;
	for(bitnum = 0; bitnum < REG_LEN; bitnum++) {
		// sdi_clock_bit just checks if the value is > 0. It doesn't have to be 1.
		sdi_clock_bit(gpio, SDIN, SCLK, to_send[bitnum]);
	}

	char STATE = 0;
	char write_state[] = {0x40, gpio, STATE};
	bcm2835_spi_writenb(write_state, sizeof(write_state));

	STATE = flip_bit(STATE, SLOAD);
	write_state[2] = STATE;
	bcm2835_spi_writenb(write_state, sizeof(write_state));

	STATE = flip_bit(STATE, SLOAD);
	write_state[2] = STATE;
	bcm2835_spi_writenb(write_state, sizeof(write_state));
}



/*** Bit Manipulations ***/
char flip_bit(char state, int bitnum) {
	return state ^ (1 << bitnum);
}


char write_bit(char state, int bitnum, int val) {
	if(val) {
		return state | (1 << bitnum);
	}
	else {
		return state & ~(1 << bitnum);
	}
}

unsigned int reversed(unsigned int v) {// taken from Bit Twiddling Hacks
	unsigned int r = v; // r will be reversed bits of v; first get LSB of v
	int s = 9 - 1; // extra shift needed at end

	for(v >>= 1; v; v >>= 1) {   
		r <<= 1;
		r |= v & 1;
		s--;
	}
	r <<= s;

	return r;
}



/*** SPI Functions ***/
void make_pins_output(char gpio_iodir, int pins_to_change[], int numPins) {
	char PINS_OUTPUT = 0xFF;
	int i;
	for(i = 0; i < numPins; i++) {
		PINS_OUTPUT ^= (1 << pins_to_change[i]);
	}
	char pin_as_output[] = {0x40, gpio_iodir, PINS_OUTPUT};
	bcm2835_spi_writenb(pin_as_output, sizeof(pin_as_output));
}


void make_all_pins_input(char gpio_iodir) {
	char ALL_INPUT = 0xFF;
	char pins_as_input[] = {0x40, gpio_iodir, ALL_INPUT};
	bcm2835_spi_writenb(pins_as_input, sizeof(pins_as_input));
}


void send_page(char page) {
	char PAGE[] = {page};				// bcm2835_spi_writenb needs an array, even if it's only one value
	bcm2835_spi_chipSelect(BCM2835_SPI_CS0);	// set CS0
	bcm2835_spi_writenb(PAGE, sizeof(PAGE));	// send PAGE
	bcm2835_spi_chipSelect(BCM2835_SPI_CS1);	// set CS1 to talk to the device at PAGE
}


void init_spi() {
	if(!bcm2835_init()) {
		fprintf(stderr, "bcm2825_init failed. You most likely are not running as root.\n");
		exit(1);
	}

	if(!bcm2835_spi_begin()) {
		fprintf(stderr, "bcm2825_spi_begin failed. You most likely are not running as root.\n");
		exit(1);
	}

	bcm2835_spi_begin();
	bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);
	bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);
	bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_256);	// 1.5625 MHz
	bcm2835_spi_chipSelect(BCM2835_SPI_CS0);			// Chip-Select 0
	bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, LOW);	// Value of CS when active
}


void end_spi() {
	bcm2835_spi_end();
	bcm2835_close();
}
