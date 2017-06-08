//
//	Synch Board Speed Test
//

#include <bcm2835.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void die(const char *s);
void init_SPI();
void end_SPI();


int main()
{
	// Setting up SPI
	init_SPI();
	printf("SPEED TEST\n\n");


	// Initialization stuff
	srand(time(NULL));
	int BYTES = 16;					// Can only write 16 bytes at once
	bcm2835_spi_chipSelect(BCM2835_SPI_CS0);
	char PAGE[] = {0xC};				// PAGE 12
	bcm2835_spi_writenb(PAGE, sizeof(PAGE));
	bcm2835_spi_chipSelect(BCM2835_SPI_CS1);

	char set_WEL[] = {0x6};				// Set WEL
	bcm2835_spi_writenb(set_WEL, 1);

	char write_cmd[2+BYTES], data[BYTES], data_back[BYTES];
	write_cmd[0] = 0x2;
	write_cmd[1] = 0;
	int byte;
	for(byte=0;byte<BYTES;byte++)
	{
		data[byte] = rand() % 256;
		write_cmd[byte+2] = data[byte];
	}
	bcm2835_spi_writenb(write_cmd, sizeof(write_cmd));	// Write data
	
	char check_status[] = {0x5, 0};
	char status[sizeof(check_status)];
	while(1)					// Wait til write is done
	{
		bcm2835_spi_transfernb(check_status, status, sizeof(check_status));
		if(!(status[1] % 2)) break;
	}


	bcm2835SPIClockDivider speed;
	for(speed=BCM2835_SPI_CLOCK_DIVIDER_1;speed<=BCM2835_SPI_CLOCK_DIVIDER_32768;speed*=2)
	{
		bcm2835_spi_setClockDivider(speed);	// New speed

		int addr;
		for(addr=0;addr<BYTES;addr++)		// Read back data
		{
			char to_send[] = {0x3, addr, 0};
			char to_recv[sizeof(to_send)];
			bcm2835_spi_transfernb(to_send, to_recv, sizeof(to_send));
			data_back[addr] = to_recv[2];
		}

		int same=1;
		for(addr=0;addr<BYTES;addr++)		// Check if it's the same
		{
			if(data[addr] != data_back[addr])
			{
				printf("%.3f MHz: Failure!\n", speed==1 ? 400./65536 : 400./speed);
				same = 0;
				break;
			}
		}
		if(same) printf("%.3f MHz: Success!\n", speed==1 ? 400./65536 : 400./speed);
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
