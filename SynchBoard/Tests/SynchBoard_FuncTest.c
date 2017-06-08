//
//	Synch Board Functionality Test
//

#include <bcm2835.h>
#include <stdio.h>
#include <stdlib.h>


void die(const char *s);
void init_SPI();
void end_SPI();


int main()
{
	// Setting up SPI
	init_SPI();
	printf("FUNCTIONALITY TEST\n\n");


	// Let's read the DIP switches
	bcm2835_spi_chipSelect(BCM2835_SPI_CS0);
	char PAGE[] = {0xD};				// Has PAGE 13
	bcm2835_spi_writenb(PAGE,1);
	bcm2835_spi_chipSelect(BCM2835_SPI_CS1);

	char PORTA_pullup[] = {0x40, 0xC, 0xFF};	// Pulling up on PORTA
	bcm2835_spi_writenb(PORTA_pullup, sizeof(PORTA_pullup));
	char PORTA_read_DIPS[] = {0x41, 0x12, 0};
	char PORTA_DIPS[sizeof(PORTA_read_DIPS)];
	bcm2835_spi_transfernb(PORTA_read_DIPS, PORTA_DIPS, sizeof(PORTA_read_DIPS));
	printf("PORTA DIPS: %02x (%u)\n", PORTA_DIPS[2], PORTA_DIPS[2]);

	char PORTB_pullup[] = {0x40, 0xD, 0xF};		// Pulling up on PORTB
	bcm2835_spi_writenb(PORTB_pullup, sizeof(PORTB_pullup));
	char PORTB_read_DIPS[] = {0x41, 0x13, 0};
	char PORTB_DIPS[sizeof(PORTB_read_DIPS)];
	bcm2835_spi_transfernb(PORTB_read_DIPS, PORTB_DIPS, sizeof(PORTB_read_DIPS));
	printf("PORTB DIPS: %02x (%u)\n", PORTB_DIPS[2], PORTB_DIPS[2]);
	printf("\n");


	// Let's get the EEPROM's MAC address
	printf("Getting EEPROM's MAC address\n");
	bcm2835_spi_chipSelect(BCM2835_SPI_CS0);
	PAGE[0] = 0xC;					// EEPROM has PAGE 12
	bcm2835_spi_writenb(PAGE,1);			// Send PAGE to FPGA
	bcm2835_spi_chipSelect(BCM2835_SPI_CS1);	// CS1 to talk to EEPROM
	int addr;
	for(addr=250;addr<256;addr++)			// MAC address is stored in 250-255
	{
		char to_send[] = {0x3, addr, 0};	// First byte is read command, then memory address, then push back byte
		char to_recv[sizeof(to_send)];
		bcm2835_spi_transfernb(to_send, to_recv, sizeof(to_send));
		printf("%02x ", to_recv[2]);
	}
	printf("\n\n");


	// Now let's write to the EEPROM
	printf("Writing to EEPROM\n");
	for(addr=0;addr<10;addr++)
	{
		char set_WEL[] = {0x6};
		bcm2835_spi_writenb(set_WEL, 1);
		char write_cmd[] = {0x2, addr, addr};
		bcm2835_spi_writenb(write_cmd, sizeof(write_cmd));
		
		char check_status[] = {0x5, 0};
		while(1)
		{
			char status[sizeof(check_status)];
			bcm2835_spi_transfernb(check_status, status, sizeof(check_status));
			if(!(status[1] % 2)) break;
		}
	}


	// Reading from what we just wrote
	printf("Reading from EEPROM\n");
	for(addr=0;addr<10;addr++)
	{
		char read_cmd[] = {0x3, addr, 0};
		char data[sizeof(read_cmd)];
		bcm2835_spi_transfernb(read_cmd, data, sizeof(read_cmd));
		printf("Address %u: %u\n", addr, data[2]);
	}
	printf("\n");

	// Clearing EEPROM for next time.
	for(addr=0;addr<10;addr++)
	{
		char set_WEL[] = {0x6};
		bcm2835_spi_writenb(set_WEL, 1);
		char write_cmd[] = {0x2, addr, 0};
		bcm2835_spi_writenb(write_cmd, sizeof(write_cmd));

		char check_status[] = {0x5, 0};
		while(1)
		{
			char status[sizeof(check_status)];
			bcm2835_spi_transfernb(check_status, status, sizeof(check_status));
			if(!(status[1] % 2)) break;
		}
	}


	// Close SPI
	end_SPI();
	return 0;
}



void die(const char *s)
{
	printf(s);
	exit(1);
}



void init_SPI()
{
	if(!bcm2835_init())
	{
		die("bcm2825_init failed. You most likely are not running as root.\n");
	}

	if(!bcm2835_spi_begin())
	{
		die("bcm2825_spi_begin failed. You most likely are not running as root.\n");
	}

	bcm2835_spi_begin();
	bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);
	bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);
	bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_256);	// 1.5625 MHz
	bcm2835_spi_chipSelect(BCM2835_SPI_CS0);			// Chip-Select 0
	bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, LOW);	// Value of CS when active
}



void end_SPI()
{
	bcm2835_spi_end();
	bcm2835_close();
}
