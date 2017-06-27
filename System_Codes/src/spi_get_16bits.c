#include <stdio.h>
#include <stdlib.h>
#include <bcm2835.h>

int spi_select_orm(int orm);
int spi_get_16bits(int orm, int addr);
void init_SPI();
void end_SPI();


int main(int argc, char *argv[]) {

	if(argc != 3) {
		printf("usage: sudo ./spi_get_16bits [ORM] [ADDRESS]\n");
		exit(1);
	}

	// get orm and address from arguments
	int orm, addr;
	orm = (int)strtol(argv[1], NULL, 0);
	addr = (int)strtol(argv[2], NULL, 0);

	init_SPI();

	// read from the address
	printf("%02x\n", spi_get_16bits(orm, addr));

	end_SPI();
	return 0;

}

// Set the page register so we can talk to an ORM.
int spi_select_orm(int orm)
{
	char page[4];
	page[0] = 2 * (orm + 1);

	// Select the appropriate oRM.
	bcm2835_spi_chipSelect(BCM2835_SPI_CS0);
	bcm2835_spi_writenb(page,1);
	bcm2835_spi_chipSelect(BCM2835_SPI_CS1);
}

// Send a 32-bit spi_read command, and keep the 16 bits that are returned.
int spi_get_16bits(int orm, int addr)
{
	char cmd[4], data[4];
	unsigned spi_read, spi_auto_inc, spi_addr, spi_command;
	int result;

	// Select the appropriate orm.
	spi_select_orm(orm);

	// Create the 32-bit command word.
	spi_read = 1;
	spi_auto_inc = 0;
	spi_addr = addr & 0x3FF;
	spi_command = (spi_read<<31)|(spi_auto_inc<<30)|(spi_addr<<20);
	cmd[0] = spi_command >> 24;
	cmd[1] = spi_command >> 16;
	cmd[2] = spi_command >> 8;
	cmd[3] = spi_command >> 0;

	// Send the command.
	bcm2835_spi_transfernb(cmd, data, 4);

	result = (data[2]<<8) | data[3];
	return (result);
}

void init_SPI()
{
	if(!bcm2835_init())
	{
		printf("bcm2825_init failed. You most likely are not running as root.\n");
		exit(1);
	}

	if(!bcm2835_spi_begin())
	{
		printf("bcm2825_spi_begin failed. You most likely are not running as root.\n");
		exit(1);
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
