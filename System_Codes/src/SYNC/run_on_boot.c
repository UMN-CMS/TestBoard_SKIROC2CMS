//---------------------------------------------------------------------
// COMPILE:
// gcc run_on_boot.c -o run_on_boot -l bcm2835 -Wall -std=c11
//---------------------------------------------------------------------
// USAGE:
// 	sudo ./run_on_boot
//---------------------------------------------------------------------
//	Script designed to be run on boot on the syncboard's pi. Checks
//	for disconnected cables every 30 seconds, and checks for a
//	clear signal every 5 seconds. On a clear signal, the ORM is
//	power cycled.
//---------------------------------------------------------------------

#include <bcm2835.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


void die(const char *s);
void init_SPI();
void end_SPI();

int check_for_clear();
void pwr_cycle_orm();
uint16_t check_cable_disconnect();
void send_conn_info(uint16_t conns);



int main() {
	// Setting up SPI
	init_SPI();

	int time = 0;
	while(1) {
		if(!(time % 5)) {
			if(check_for_clear()) {
				pwr_cycle_orm();
			}
		}
		if(!(time % 30)) {
			uint16_t connections = check_cable_disconnect();
			send_conn_info(connections);
		}
		time++;
		sleep(1);
	}

	end_SPI();
	return 0;
}



void send_conn_info(uint16_t conns) {
	//TODO
	return;
}



int check_for_clear() {

	// Check BCM pin 15 (physical pin 10)
	bcm2835_gpio_fsel(RPI_GPIO_P1_15, BCM2835_GPIO_FSEL_INPT);
	bcm2835_gpio_set_pud(RPI_GPIO_P1_15, BCM2835_GPIO_PUD_UP);

	// return 1 if LO, 0 if HI
        return !(bcm2835_gpio_lev(RPI_GPIO_P1_15));
}



uint16_t check_cable_disconnect() {

	char PAGE[1];

	bcm2835_spi_chipSelect(BCM2835_SPI_CS0);
	PAGE[0] = 0x9;					// Chip has PAGE 13
	bcm2835_spi_writenb(PAGE,1);
	bcm2835_spi_chipSelect(BCM2835_SPI_CS1);

	char PORTA_pullup[] = {0x40, 0xC, 0xFF};	// Pulling up on PORTA
	char PORTB_pullup[] = {0x40, 0xD, 0xFF};	// Pulling up on PORTB
	bcm2835_spi_writenb(PORTA_pullup, sizeof(PORTA_pullup));
	bcm2835_spi_writenb(PORTB_pullup, sizeof(PORTB_pullup));

	char PORTA_read_DIPS[] = {0x41, 0x12, 0};	// Reading DIP switches
	char PORTA_DIPS[sizeof(PORTA_read_DIPS)];
	bcm2835_spi_transfernb(PORTA_read_DIPS, PORTA_DIPS, sizeof(PORTA_read_DIPS));
	//printf("PORT A: %2x (%i)\n", PORTA_DIPS[2], PORTA_DIPS[2]);

	char PORTB_read_DIPS[] = {0x41, 0x13, 0};	// Reading DIP switches
	char PORTB_DIPS[sizeof(PORTB_read_DIPS)];
	bcm2835_spi_transfernb(PORTB_read_DIPS, PORTB_DIPS, sizeof(PORTB_read_DIPS));
	//printf("PORT B: %2x (%i)\n", PORTB_DIPS[2], PORTB_DIPS[2]);

	uint16_t CONN_LIST = (PORTB_DIPS[2] << 8) + PORTA_DIPS[2]; // Could use a short here, but this makes it clearer that it's 2 bytes I think.

	/*
	//Print out info.
	int conn;
	for(conn = 0; conn < 16; conn++) {
	if (CONN_LIST & (1 << conn)) {
	printf("Connector %i: Disconnected\n", conn);
	}
	else {
	printf("Connector %i: Connected\n", conn);
	}
	}
	*/
	return CONN_LIST;
}



void pwr_cycle_orm() {

	char PAGE[1];
	char GPIO_PIN = 0;// only possible ORM is ORM0 on the syncboard.

	// Time to power cycle the FPGA
	bcm2835_spi_chipSelect(BCM2835_SPI_CS0);	// CS0
	PAGE[0] = 0xF;
	bcm2835_spi_writenb(PAGE, sizeof(PAGE));
	bcm2835_spi_chipSelect(BCM2835_SPI_CS1);	// CS1

	// Clearing Pin
	char PIN_SELECT = 0xFF ^ (1 << GPIO_PIN);
	char PIN_as_output[] = {0x40, 0x01, PIN_SELECT};	// Want PIN to be an output
	bcm2835_spi_writenb(PIN_as_output, sizeof(PIN_as_output)+1);
	char PIN_low[] = {0x40, 0x13, PIN_SELECT};	// Set PIN to output low
	bcm2835_spi_writenb(PIN_low, sizeof(PIN_low)+1);
	sleep(5);						// Wait!
	char PIN_as_input[] = {0x40, 0x01, 0xFF};		// Set PIN as input again
	bcm2835_spi_writenb(PIN_as_input, sizeof(PIN_as_input)+1);

	//int status, hexbd;
	//hexbd = My_ORM * 2;
	//status = spi_verify_hexbd_communication(hexbd);
	//hexbd = (My_ORM * 2) + 1;
	//status = spi_verify_hexbd_communication(hexbd);
}








void die(const char *s) {
	printf(s);
	exit(1);
}



void init_SPI() {
	if(!bcm2835_init()) {
		die("bcm2825_init failed. You most likely are not running as root.\n");
	}

	if(!bcm2835_spi_begin()) {
		die("bcm2825_spi_begin failed. You most likely are not running as root.\n");
	}

	bcm2835_spi_begin();
	bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);
	bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);
	bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_256);	// 1.5625 MHz
	bcm2835_spi_chipSelect(BCM2835_SPI_CS0);			// Chip-Select 0
	bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, LOW);	// Value of CS when active
}



void end_SPI() {
	bcm2835_spi_end();
	bcm2835_close();
}
