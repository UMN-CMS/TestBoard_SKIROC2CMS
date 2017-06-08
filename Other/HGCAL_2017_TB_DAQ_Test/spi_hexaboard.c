#define ADDR_PI_TO_HEXA0 (0x100)
#define ADDR_HEXA0_TO_PI (0x101)
#define ADDR_PI_TO_HEXA1 (0x102)
#define ADDR_HEXA1_TO_PI (0x103)
#define ADDR_STATUS0 (0x200)
#define ADDR_STATUS1 (0x201)

#define EMPTY_FLAG (0)
#define FULL_FLAG  (1)

#include <bcm2835.h>

/*
int spi_send_test(int indx)
{
   unsigned spi_read, spi_auto_inc, spi_addr, spi_command, full_flag;
   unsigned char cmd[4], data[4];
	unsigned char page[4];
	page[0] = 2;
   int rw = 0;
   int a2 = 0;
   int a1 = 0;
   int a0 = 0;
   unsigned char c = 0x98;

    bcm2835_spi_chipSelect(BCM2835_SPI_CS0);
    bcm2835_spi_writenb(page,1);
    bcm2835_spi_chipSelect(BCM2835_SPI_CS1);
	
   // Create the 32-bit command word.
   spi_read = 0;
   spi_auto_inc = 0;
   if (indx == 0) spi_addr = ADDR_PI_TO_HEXA0;
   else spi_addr = ADDR_PI_TO_HEXA1;
   spi_command = (spi_read<<31)|(spi_auto_inc<<30)|(spi_addr<<20)|
                 (rw<<11)|(a2<<10)|(a1<<9)|(a0<<8)|(c<<0);

   // Send the command.
   cmd[0] = spi_command >> 24;
   cmd[1] = spi_command >> 16;
   cmd[2] = spi_command >> 8;
   cmd[3] = spi_command >> 0;
	while(1){
		bcm2835_spi_transfernb(cmd, data, sizeof(cmd));
	}
   return(0); // Assume ACK is handled by firmware.
}
*/

/*
int spi_send_test(int indx)
 {
   unsigned spi_read, spi_auto_inc, spi_addr, spi_command, full_flag;
   unsigned char cmd[4], data[4];

   int rw = 0;
   int a2 = 0;
   int a1 = 0;
   int a0 = 0;
   unsigned char c = 0x98;

   indx &= 1; // Paranoia.
   rw &= 1; // Paranoia.
   a0 &= 1; // Paranoia.
   a1 &= 1; // Paranoia.
   a2 &= 1; // Paranoia.

   // Wait while this fifo is full.
   full_flag = 1;
   while (full_flag != 0) {
      // Create the 32-bit command word.
      spi_read = 1;
      spi_auto_inc = 0;
      if (indx == 0) spi_addr = ADDR_STATUS0;
      else spi_addr = ADDR_STATUS1;
      spi_command = (spi_read<<31)|(spi_auto_inc<<30)|(spi_addr<<20);

      // Send the command.
      cmd[0] = spi_command >> 24;
      cmd[1] = spi_command >> 16;
      cmd[2] = spi_command >> 8;
      cmd[3] = spi_command >> 0;
      bcm2835_spi_transfernb(cmd, data, sizeof(cmd));
//       printf("Data = %02x %02x %02x %02x\n ", data[0], data[1], data[2], data[3]);
      full_flag = (data[2] >> FULL_FLAG) & 1;
   }

   // Create the 32-bit command word.
   spi_read = 0;
   spi_auto_inc = 0;
   if (indx == 0) spi_addr = ADDR_PI_TO_HEXA0;
   else spi_addr = ADDR_PI_TO_HEXA1;
   spi_command = (spi_read<<31)|(spi_auto_inc<<30)|(spi_addr<<20)|
                 (rw<<11)|(a2<<10)|(a1<<9)|(a0<<8)|(c<<0);

    // Send the command.
   cmd[0] = spi_command >> 24;
   cmd[1] = spi_command >> 16;
   cmd[2] = spi_command >> 8;
   cmd[3] = spi_command >> 0;
	while(1){
		bcm2835_spi_transfernb(cmd, data, sizeof(cmd));
	}
   return(0); // Assume ACK is handled by firmware.

}
*/

int spi_send_generic(int indx, int rw, int a2, int a1, int a0, unsigned char c)
{
   unsigned spi_read, spi_auto_inc, spi_addr, spi_command, full_flag;
   unsigned char cmd[4], data[4];

   indx &= 1; // Paranoia.
   rw &= 1; // Paranoia.
   a0 &= 1; // Paranoia.
   a1 &= 1; // Paranoia.
   a2 &= 1; // Paranoia.
   
   // Wait while this fifo is full.
   full_flag = 1;
   while (full_flag != 0) {
      // Create the 32-bit command word.
      spi_read = 1;
      spi_auto_inc = 0;
      if (indx == 0) spi_addr = ADDR_STATUS0;
      else spi_addr = ADDR_STATUS1;
      spi_command = (spi_read<<31)|(spi_auto_inc<<30)|(spi_addr<<20);

      // Send the command.
      cmd[0] = spi_command >> 24;
      cmd[1] = spi_command >> 16;
      cmd[2] = spi_command >> 8;
      cmd[3] = spi_command >> 0;
      bcm2835_spi_transfernb(cmd, data, sizeof(cmd));
//	 printf("Data = %02x %02x %02x %02x\n ", data[0], data[1], data[2], data[3]);
      full_flag = (data[2] >> FULL_FLAG) & 1;
   }

   // Create the 32-bit command word.
   spi_read = 0;
   spi_auto_inc = 0;
   if (indx == 0) spi_addr = ADDR_PI_TO_HEXA0;
   else spi_addr = ADDR_PI_TO_HEXA1;
   spi_command = (spi_read<<31)|(spi_auto_inc<<30)|(spi_addr<<20)|
                 (rw<<11)|(a2<<10)|(a1<<9)|(a0<<8)|(c<<0);

   // Send the command.
   cmd[0] = spi_command >> 24;
   cmd[1] = spi_command >> 16;
   cmd[2] = spi_command >> 8;
   cmd[3] = spi_command >> 0;
   bcm2835_spi_transfernb(cmd, data, sizeof(cmd));

   return(0); // Assume ACK is handled by firmware.
}

int spi_read_generic(int indx, int a2, int a1, int a0)
{
   int rw, result;
   unsigned spi_read, spi_auto_inc, spi_addr, spi_command, empty_flag;
   unsigned char c, cmd[4], data[4];

   a0 &= 1; // Paranoia.
   a1 &= 1; // Paranoia.
   a2 &= 1; // Paranoia.

   // Start by sending the command, then get the response.
   rw = 1; // Do a read.
   c = 0x00; // unused
   spi_send_generic(indx, rw, a2, a1, a0, c);

   // Wait while this response fifo is empty.
   empty_flag = 1;
   while (empty_flag != 0) {
      // Create the 32-bit command word.
      spi_read = 1;
      spi_auto_inc = 0;
      if (indx == 0) spi_addr = ADDR_STATUS0;
      else spi_addr = ADDR_STATUS1;
      spi_command = (spi_read<<31)|(spi_auto_inc<<30)|(spi_addr<<20);

      // Send the command.
      cmd[0] = spi_command >> 24;
      cmd[1] = spi_command >> 16;
      cmd[2] = spi_command >> 8;
      cmd[3] = spi_command >> 0;
      bcm2835_spi_transfernb(cmd, data, sizeof(cmd));
//	printf("Data = %02x %02x %02x %02x\n ", data[0], data[1], data[2], data[3]);
      empty_flag = (data[3] >> EMPTY_FLAG) & 1;
   }

   // Create the 32-bit command word.
   spi_read = 1;
   spi_auto_inc = 0;
   if (indx == 0) spi_addr = ADDR_HEXA0_TO_PI;
   else spi_addr = ADDR_HEXA1_TO_PI;
   spi_command = (spi_read<<31)|(spi_auto_inc<<30)|(spi_addr<<20);

   // Send the command.
   cmd[0] = spi_command >> 24;
   cmd[1] = spi_command >> 16;
   cmd[2] = spi_command >> 8;
   cmd[3] = spi_command >> 0;
   bcm2835_spi_transfernb(cmd, data, sizeof(cmd));

   result = data[3];
   return(result);
}

int spi_send_command(int hexbd, unsigned char c)
{
   int rw, status;
   unsigned indx, a2, a1, a0;
   unsigned char page[4];

   // Decode the index of the hexaboard.
        if (hexbd == 0) { page[0] = 2; indx = 0; } // ORM_0
   else if (hexbd == 1) { page[0] = 2; indx = 1; } // ORM_0
   else if (hexbd == 2) { page[0] = 4; indx = 0; } // ORM_1
   else if (hexbd == 3) { page[0] = 4; indx = 1; } // ORM_1
   else if (hexbd == 4) { page[0] = 6; indx = 0; } // ORM_2
   else if (hexbd == 5) { page[0] = 6; indx = 1; } // ORM_2
   else if (hexbd == 6) { page[0] = 8; indx = 0; } // ORM_3
   else if (hexbd == 7) { page[0] = 8; indx = 1; } // ORM_3
   else return(-1);

   // Select the appropriate oRM.
   bcm2835_spi_chipSelect(BCM2835_SPI_CS0);
   bcm2835_spi_writenb(page,1);
   bcm2835_spi_chipSelect(BCM2835_SPI_CS1);

   rw = 0; // Do a write.
   a2 = 0;
   a1 = 0;
   a0 = 0;
   status = spi_send_generic(indx, rw, a2, a1, a0, c);

   return(status);
}

int spi_read_command(int hexbd)
{
   int result;
   unsigned indx, a2, a1, a0;
   unsigned char page[4];

   // Decode the index of the hexaboard.
        if (hexbd == 0) { page[0] = 2; indx = 0; } // ORM_0
   else if (hexbd == 1) { page[0] = 2; indx = 1; } // ORM_0
   else if (hexbd == 2) { page[0] = 4; indx = 0; } // ORM_1
   else if (hexbd == 3) { page[0] = 4; indx = 1; } // ORM_1
   else if (hexbd == 4) { page[0] = 6; indx = 0; } // ORM_2
   else if (hexbd == 5) { page[0] = 6; indx = 1; } // ORM_2
   else if (hexbd == 6) { page[0] = 8; indx = 0; } // ORM_3
   else if (hexbd == 7) { page[0] = 8; indx = 1; } // ORM_3
   else return(-1);

   // Select the appropriate oRM.
   bcm2835_spi_chipSelect(BCM2835_SPI_CS0);
   bcm2835_spi_writenb(page,1);
   bcm2835_spi_chipSelect(BCM2835_SPI_CS1);

   a2 = 0;
   a1 = 0;
   a0 = 0;
   result = spi_read_generic(indx, a2, a1, a0);

   return(result);
}

int spi_write_local_fifo(int hexbd, unsigned char c)
{
   int rw, status;
   unsigned indx, a2, a1, a0;
   unsigned char page[4];
   // Decode the index of the hexaboard.
        if (hexbd == 0) { page[0] = 2; indx = 0; } // ORM_0
   else if (hexbd == 1) { page[0] = 2; indx = 1; } // ORM_0
   else if (hexbd == 2) { page[0] = 4; indx = 0; } // ORM_1
   else if (hexbd == 3) { page[0] = 4; indx = 1; } // ORM_1
   else if (hexbd == 4) { page[0] = 6; indx = 0; } // ORM_2
   else if (hexbd == 5) { page[0] = 6; indx = 1; } // ORM_2
   else if (hexbd == 6) { page[0] = 8; indx = 0; } // ORM_3
   else if (hexbd == 7) { page[0] = 8; indx = 1; } // ORM_3
   else return(-1);
   // Select the appropriate oRM.
   bcm2835_spi_chipSelect(BCM2835_SPI_CS0);
   bcm2835_spi_writenb(page,1);
   bcm2835_spi_chipSelect(BCM2835_SPI_CS1);
   rw = 0; // Do a write.
   a2 = 0;
   a1 = 0;
   a0 = 1;
//   a0 = 0;	
   status = spi_send_generic(indx, rw, a2, a1, a0, c);
   return(status);
}

int spi_read_local_fifo(int hexbd)
{
   int result;
   unsigned indx, a2, a1, a0;
   unsigned char page[4];
   // Decode the index of the hexaboard.
        if (hexbd == 0) { page[0] = 2; indx = 0; } // ORM_0
   else if (hexbd == 1) { page[0] = 2; indx = 1; } // ORM_0
   else if (hexbd == 2) { page[0] = 4; indx = 0; } // ORM_1
   else if (hexbd == 3) { page[0] = 4; indx = 1; } // ORM_1
   else if (hexbd == 4) { page[0] = 6; indx = 0; } // ORM_2
   else if (hexbd == 5) { page[0] = 6; indx = 1; } // ORM_2
   else if (hexbd == 6) { page[0] = 8; indx = 0; } // ORM_3
   else if (hexbd == 7) { page[0] = 8; indx = 1; } // ORM_3
   else return(-1);
   // Select the appropriate oRM.
   bcm2835_spi_chipSelect(BCM2835_SPI_CS0);
   bcm2835_spi_writenb(page,1);
   bcm2835_spi_chipSelect(BCM2835_SPI_CS1);
   a2 = 0;
   a1 = 0;
   a0 = 1;
   result = spi_read_generic(indx, a2, a1, a0);
   return(result);
}

int spi_read_usedwh(int hexbd)
{
   int result;
   unsigned indx, a2, a1, a0;
   unsigned char page[4];

   // Decode the index of the hexaboard.
        if (hexbd == 0) { page[0] = 2; indx = 0; } // ORM_0
   else if (hexbd == 1) { page[0] = 2; indx = 1; } // ORM_0
   else if (hexbd == 2) { page[0] = 4; indx = 0; } // ORM_1
   else if (hexbd == 3) { page[0] = 4; indx = 1; } // ORM_1
   else if (hexbd == 4) { page[0] = 6; indx = 0; } // ORM_2
   else if (hexbd == 5) { page[0] = 6; indx = 1; } // ORM_2
   else if (hexbd == 6) { page[0] = 8; indx = 0; } // ORM_3
   else if (hexbd == 7) { page[0] = 8; indx = 1; } // ORM_3
   else return(-1);

   // Select the appropriate oRM.
   bcm2835_spi_chipSelect(BCM2835_SPI_CS0);
   bcm2835_spi_writenb(page,1);
   bcm2835_spi_chipSelect(BCM2835_SPI_CS1);

   a2 = 0;
   a1 = 1;
   a0 = 1;
   result = spi_read_generic(indx, a2, a1, a0);

   return(result);
}

int spi_read_usedwl(int hexbd)
{
   int result;
   unsigned indx, a2, a1, a0;
   unsigned char page[4];

   // Decode the index of the hexaboard.
        if (hexbd == 0) { page[0] = 2; indx = 0; } // ORM_0
   else if (hexbd == 1) { page[0] = 2; indx = 1; } // ORM_0
   else if (hexbd == 2) { page[0] = 4; indx = 0; } // ORM_1
   else if (hexbd == 3) { page[0] = 4; indx = 1; } // ORM_1
   else if (hexbd == 4) { page[0] = 6; indx = 0; } // ORM_2
   else if (hexbd == 5) { page[0] = 6; indx = 1; } // ORM_2
   else if (hexbd == 6) { page[0] = 8; indx = 0; } // ORM_3
   else if (hexbd == 7) { page[0] = 8; indx = 1; } // ORM_3
   else return(-1);

   // Select the appropriate oRM.
   bcm2835_spi_chipSelect(BCM2835_SPI_CS0);
   bcm2835_spi_writenb(page,1);
   bcm2835_spi_chipSelect(BCM2835_SPI_CS1);

   a2 = 0;
   a1 = 1;
   a0 = 0;
   result = spi_read_generic(indx, a2, a1, a0);

   return(result);
}

void spi_trigger_gen(int hexbd)
{
   int rw, status;
   unsigned indx, a2, a1, a0;
   unsigned char page[4];
   unsigned char c;

   // Decode the index of the hexaboard.
        if (hexbd == 0) { page[0] = 2; indx = 0; } // ORM_0
   else if (hexbd == 1) { page[0] = 2; indx = 1; } // ORM_0
   else if (hexbd == 2) { page[0] = 4; indx = 0; } // ORM_1
   else if (hexbd == 3) { page[0] = 4; indx = 1; } // ORM_1
   else if (hexbd == 4) { page[0] = 6; indx = 0; } // ORM_2
   else if (hexbd == 5) { page[0] = 6; indx = 1; } // ORM_2
   else if (hexbd == 6) { page[0] = 8; indx = 0; } // ORM_3
   else if (hexbd == 7) { page[0] = 8; indx = 1; } // ORM_3
   else                 { page[0] = 8; indx = 1; } // ???


   // Select the appropriate oRM.
   bcm2835_spi_chipSelect(BCM2835_SPI_CS0);
   bcm2835_spi_writenb(page,1);
   bcm2835_spi_chipSelect(BCM2835_SPI_CS1);

   rw = 0;
   a2 = 1;
   a1 = 1;
   a0 = 1;
   c = 0x00; // unused
   status = spi_send_generic(indx, rw, a2, a1, a0, c);
}
