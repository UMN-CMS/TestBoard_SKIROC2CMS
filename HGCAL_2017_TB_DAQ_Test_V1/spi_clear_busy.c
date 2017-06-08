#include <bcm2835.h>
#include <stdio.h>

#define ADDR_CLEAR_BUSY (0x000)
#define ADDR_BUSY_FLAG  (0x080)

int spi_next_trigger()
{
   unsigned char page[4];
   unsigned spi_read, spi_auto_inc, spi_addr, spi_command;
   unsigned char cmd[4], data[4];

   // Select the appropriate oRM.
   page[0] = 10;
   bcm2835_spi_chipSelect(BCM2835_SPI_CS0);
   bcm2835_spi_writenb(page,1);
   bcm2835_spi_chipSelect(BCM2835_SPI_CS1);

   // Create the 32-bit command word.
   spi_read = 0;
   spi_auto_inc = 0;
   spi_addr = ADDR_CLEAR_BUSY;
   spi_command = (spi_read<<31)|(spi_auto_inc<<30)|(spi_addr<<20);
   cmd[0] = spi_command >> 24;
   cmd[1] = spi_command >> 16;
   cmd[2] = spi_command >> 8;
   cmd[3] = spi_command >> 0;

   // Send the command.
   cmd[3] |= 1;
   bcm2835_spi_transfernb(cmd, data, sizeof(cmd));
   cmd[3] ^= 1;
   bcm2835_spi_transfernb(cmd, data, sizeof(cmd));

   //------------------------------------------------------
   // Wait for a new trigger, then return.
   //------------------------------------------------------

   // Create the 32-bit command word.
   spi_read = 1;
   spi_auto_inc = 0;
   spi_addr = ADDR_BUSY_FLAG;
   spi_command = (spi_read<<31)|(spi_auto_inc<<30)|(spi_addr<<20);
   cmd[0] = spi_command >> 24;
   cmd[1] = spi_command >> 16;
   cmd[2] = spi_command >> 8;
   cmd[3] = spi_command >> 0;

   int busy_flag;
   busy_flag = 0;
   while (busy_flag == 0) {
      bcm2835_spi_transfernb(cmd, data, sizeof(cmd));
      busy_flag = (data[2]<<8) | data[3];
      busy_flag &= 1;
   }

   return(0);
}
