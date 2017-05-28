#include <bcm2835.h>

#define ADDR_CLEAR_BUSY (0x300)

int spi_clear_busy(int hexbd)
{
   unsigned char page[4];
   unsigned spi_read, spi_auto_inc, spi_addr, spi_command;
   unsigned char cmd[4], data[4];

   // Decode the page of the hexaboard.
        if (hexbd == 0) page[0] = 2; // ORM_0
   else if (hexbd == 1) page[0] = 2; // ORM_0
   else if (hexbd == 2) page[0] = 4; // ORM_1
   else if (hexbd == 3) page[0] = 4; // ORM_1
   else if (hexbd == 4) page[0] = 6; // ORM_2
   else if (hexbd == 5) page[0] = 6; // ORM_2
   else if (hexbd == 6) page[0] = 8; // ORM_3
   else if (hexbd == 7) page[0] = 8; // ORM_3
   else                 page[0] = 8; // ???

   // Select the appropriate oRM.
   bcm2835_spi_chipSelect(BCM2835_SPI_CS0);
   bcm2835_spi_writenb(page,1);
   bcm2835_spi_chipSelect(BCM2835_SPI_CS1);

   // Create the 32-bit command word.
   spi_read = 0;
   spi_auto_inc = 0;
   spi_addr = ADDR_CLEAR_BUSY;
   spi_command = (spi_read<<31)|(spi_auto_inc<<30)|(spi_addr<<20);

   // Send the command.
   cmd[0] = spi_command >> 24;
   cmd[1] = spi_command >> 16;
   cmd[2] = spi_command >> 8;
   cmd[3] = spi_command >> 0;
   bcm2835_spi_transfernb(cmd, data, sizeof(cmd));

   return(0); // Assume ACK is handled by firmware.
}
