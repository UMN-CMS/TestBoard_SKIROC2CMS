#define ADDR_PI_TO_HEXA0 (0x100)
#define ADDR_HEXA0_TO_PI (0x101)
#define ADDR_PI_TO_HEXA1 (0x102)
#define ADDR_HEXA1_TO_PI (0x103)
#define ADDR_STATUS0 (0x200)
#define ADDR_STATUS1 (0x201)
#define ADDR_RESET_FW (0x000)

#define EMPTY_FLAG (0)
#define FULL_FLAG  (1)


/*****************************************************/
/* define commands for Master FPGA */
/*****************************************************/
#define CMD_IDLE         0x80
#define CMD_RESETPULSE   0x88
#define CMD_WRPRBITS     0x90
#define CMDH_WRPRBITS    0x12 
#define CMD_SETSTARTACQ  0x98
#define CMD_STARTCONPUL  0xA0
#define CMD_STARTROPUL   0xA8
#define CMD_SETSELECT    0xB0
#define CMD_RSTBPULSE    0xD8
#define CMD_READSTATUS   0xC0
#define CMDH_READSTATUS  0x18
#define CMD_LOOPBRFIFO   0xF0
#define CMDH_LOOPBRFIFO  0x1E
#define CMD_LOOPBACK     0xF8
#define CMDH_LOOPBACK    0x1F


#include <bcm2835.h>
#include <stdio.h>

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


int spi_local_fifo_empty(int hexbd)
{
  unsigned indx, a2, a1, a0, rw;
  unsigned char page[4], c;
  unsigned spi_read, spi_auto_inc, spi_addr, spi_command;
  unsigned empty_flag;
  unsigned char status_cmd[4];
  unsigned char data[4];
  int i;
  
  // Decode the index of the hexaboard.
  if      (hexbd == 0) { page[0] = 2; indx = 0; } // ORM_0
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

  spi_read = 1;
  spi_auto_inc = 0;
  if (indx == 0) spi_addr = ADDR_STATUS0;
  else spi_addr = ADDR_STATUS1;
  spi_command = (spi_read<<31)|(spi_auto_inc<<30)|(spi_addr<<20);
  status_cmd[0] = spi_command >> 24;
  status_cmd[1] = spi_command >> 16;
  status_cmd[2] = spi_command >> 8;
  status_cmd[3] = spi_command >> 0;

  bcm2835_spi_transfernb(status_cmd, data, 4);

fprintf(stderr,"data[2]=%02x   data[3]=%02x\n",(int)data[2],(int)data[3]);

  //empty_flag = (data[2+indx] >> EMPTY_FLAG) & 1;
  empty_flag = (data[3] >> EMPTY_FLAG) & 1;

  return(empty_flag);
} 

int spi_reset_firmware(int hexbd)
{
  unsigned indx, a2, a1, a0, rw;
  unsigned char page[4], c;
  unsigned spi_read, spi_auto_inc, spi_addr, spi_command;
  unsigned char cmd[4];
  unsigned char data[4];
  
  // Decode the index of the hexaboard.
  if      (hexbd == 0) page[0] = 2; // ORM_0
  else if (hexbd == 1) page[0] = 2; // ORM_0
  else if (hexbd == 2) page[0] = 4; // ORM_1
  else if (hexbd == 3) page[0] = 4; // ORM_1
  else if (hexbd == 4) page[0] = 6; // ORM_2
  else if (hexbd == 5) page[0] = 6; // ORM_2
  else if (hexbd == 6) page[0] = 8; // ORM_3
  else if (hexbd == 7) page[0] = 8; // ORM_3
  else return(-1);
  
  // Select the appropriate oRM.
  bcm2835_spi_chipSelect(BCM2835_SPI_CS0);
  bcm2835_spi_writenb(page,1);
  bcm2835_spi_chipSelect(BCM2835_SPI_CS1);

  spi_read = 0;
  spi_auto_inc = 0;
  spi_addr = ADDR_RESET_FW;
  spi_command = (spi_read<<31)|(spi_auto_inc<<30)|(spi_addr<<20);
  cmd[0] = spi_command >> 24;
  cmd[1] = spi_command >> 16;
  cmd[2] = spi_command >> 8;
  cmd[3] = spi_command >> 0;

  cmd[3] |= 1;
  bcm2835_spi_transfernb(cmd, data, 4);
  cmd[3] ^= 1;
  bcm2835_spi_transfernb(cmd, data, 4);

  return(0);
} 

int spi_queue_status(int hexbd)
{
  unsigned indx, orm, a2, a1, a0, rw;
  char page[4];
  unsigned spi_read, spi_auto_inc, spi_addr, spi_command;
  char cmd[4], data[4];
  unsigned status;

  // Decode the index of the hexaboard.
  indx = hexbd & 1;
  orm = hexbd >> 1;
  page[0] = 2 * (orm + 1);

  // Select the appropriate oRM.
  bcm2835_spi_chipSelect(BCM2835_SPI_CS0);
  bcm2835_spi_writenb(page,1);
  bcm2835_spi_chipSelect(BCM2835_SPI_CS1);

  spi_read = 1;
  spi_auto_inc = 0;
  if (indx == 0) spi_addr = ADDR_STATUS0;
  else spi_addr = ADDR_STATUS1;
  spi_command = (spi_read<<31)|(spi_auto_inc<<30)|(spi_addr<<20);
  cmd[0] = spi_command >> 24;
  cmd[1] = spi_command >> 16;
  cmd[2] = spi_command >> 8;
  cmd[3] = spi_command >> 0;

  bcm2835_spi_transfernb(cmd, data, 4);

  status = (data[2]<<8) | data[3];
  return(status);
}

int spi_verify_hexbd_communication(int hexbd)
{
   int status, data[200];
   int i, error_all, bits;
 
   // verify that the command and response queues are empty
   status = spi_queue_status(hexbd);
   if ((status & 0x0101) != 0x0101) {
      fprintf(stderr,"ERROR: queue is not empty. (%08x)\n", (int)status);
      return(-1);
   }

   // write and then read 200 values from the local_fifo
   for (i=0; i<200; i++) spi_write_local_fifo(hexbd, 0x05^i);
   spi_read200_local_fifo(hexbd, &(data[0]));

   // check the results from the local_fifo
   error_all = 0xFF;
   for (i=0; i<200; i++) error_all &= (0xFF ^ 0x05) ^ data[i] ^ i;
   if (error_all != 0xFF) {
      fprintf(stderr,"ERROR: incorrect value from local_fifo integrity test.\n");
      return(-1);
   }

   // send 50 CMD_LOOPBACK commands to the hexaboard, and check the results
   for (i=0; i<50; i++) {
      bits = (i^2) & 7;
      //if (bits == 7) bits = 0; // 7 sends a MAX10 slave reset
      //fprintf(stderr,"bits = %02x.\n", (int)bits);
      spi_send_command(hexbd, (0xF8 | bits));
      data[0] = spi_read_command(hexbd);
      //fprintf(stderr,"data[0] = %02x.\n", (int)data[0]);
      if (data[0] != (0xF8 | bits)) {
         fprintf(stderr,"ERROR: incorrect value from LOOPBACK integrity test%d.\n", (int)i);
         return(-1);
      }
   }

   return(0);
}

