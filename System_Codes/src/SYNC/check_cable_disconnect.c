//---------------------------------------------------------------------
// COMPILE:
// gcc check_cable_disconnect.c -o check_cable_disconnect -l bcm2835 -Wall -std=c11
//---------------------------------------------------------------------
// USAGE:
// 	sudo ./check_cable_disconnect
//---------------------------------------------------------------------
//	Displays if each HDMI connector on the SYNC board is connected
//	or disconnected.
//---------------------------------------------------------------------

#include <bcm2835.h>
#include <stdio.h>
#include <stdlib.h>


void die(const char *s);
void init_SPI();
void end_SPI();


int main() {
	// Setting up SPI
	init_SPI();

	// Let's read the DIP switches
	bcm2835_spi_chipSelect(BCM2835_SPI_CS0);
	char PAGE[] = {0x9};				// Chip has PAGE 13
	bcm2835_spi_writenb(PAGE,1);
	bcm2835_spi_chipSelect(BCM2835_SPI_CS1);

	char PORTA_pullup[] = {0x40, 0xC, 0xFF};	// Pulling up on PORTA
	char PORTB_pullup[] = {0x40, 0xD, 0xFF};	// Pulling up on PORTB
	bcm2835_spi_writenb(PORTA_pullup, sizeof(PORTA_pullup));
	bcm2835_spi_writenb(PORTB_pullup, sizeof(PORTB_pullup));

	char PORTA_read_DIPS[] = {0x41, 0x12, 0};	// Reading DIP switches
	char PORTA_DIPS[sizeof(PORTA_read_DIPS)];
	bcm2835_spi_transfernb(PORTA_read_DIPS, PORTA_DIPS, sizeof(PORTA_read_DIPS));
	printf("PORT A: %2x (%i)\n", PORTA_DIPS[2], PORTA_DIPS[2]);

	char PORTB_read_DIPS[] = {0x41, 0x13, 0};	// Reading DIP switches
	char PORTB_DIPS[sizeof(PORTB_read_DIPS)];
	bcm2835_spi_transfernb(PORTB_read_DIPS, PORTB_DIPS, sizeof(PORTB_read_DIPS));
	printf("PORT B: %2x (%i)\n", PORTB_DIPS[2], PORTB_DIPS[2]);

	uint16_t CONN_LIST = (PORTB_DIPS[2] << 8) + PORTA_DIPS[2]; // Could use a short here, but this makes it clearer that it's 2 bytes I think.


	// Print out info.
	int conn;
	for(conn = 0; conn < 16; conn++) {
		if (CONN_LIST & (1 << conn)) {
			printf("Connector %i: Disconnected\n", conn);
		}
		else {
			printf("Connector %i: Connected\n", conn);
		}
	}


	// Close SPI
	end_SPI();
	return 0;
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
