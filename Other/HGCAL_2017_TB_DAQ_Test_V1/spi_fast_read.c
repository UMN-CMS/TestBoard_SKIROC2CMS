#define ADDR_PI_TO_HEXA0 (0x100)
#define ADDR_HEXA0_TO_PI (0x101)
#define ADDR_PI_TO_HEXA1 (0x102)
#define ADDR_HEXA1_TO_PI (0x103)
#define ADDR_STATUS0 (0x200)
#define ADDR_STATUS1 (0x201)

#define ALMOST_EMPTY_FLAG (2)
#define ALMOST_FULL_FLAG  (3)

#include <bcm2835.h>

int spi_read200_local_fifo(int hexbd, int result[200])
{
  unsigned indx, a2, a1, a0, rw;
  unsigned char page[4], c;
  unsigned spi_read, spi_auto_inc, spi_addr, spi_command;
  unsigned almost_empty_flag, almost_full_flag;
  unsigned char status_cmd[4];
  unsigned char send_cmd[(2*200)+12];
  unsigned char response_cmd[(2*200)+12];
  unsigned char data[(2*200)+12];
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
  
  // Create the SPI command for FIFO status.
  spi_read = 1;
  spi_auto_inc = 0;
  if (indx == 0) spi_addr = ADDR_STATUS0;
  else spi_addr = ADDR_STATUS1;
  spi_command = (spi_read<<31)|(spi_auto_inc<<30)|(spi_addr<<20);
  status_cmd[0] = spi_command >> 24;
  status_cmd[1] = spi_command >> 16;
  status_cmd[2] = spi_command >> 8;
  status_cmd[3] = spi_command >> 0;
  
  // Create the SPI commands for read_local_fifo.
  a2 = 0;
  a1 = 0;
  a0 = 1;
  rw = 1; // Do a read.
  c = 0x00; // unused, since {a2,a1,a0} determine the command
  spi_read = 0;
  spi_auto_inc = 0;
  if (indx == 0) spi_addr = ADDR_PI_TO_HEXA0;
  else spi_addr = ADDR_PI_TO_HEXA1;
  spi_command = (spi_read<<31)|(spi_auto_inc<<30)|(spi_addr<<20)|
                (rw<<11)|(a2<<10)|(a1<<9)|(a0<<8)|(c<<0);
  send_cmd[0] = spi_command >> 24;
  send_cmd[1] = spi_command >> 16;
  send_cmd[2] = spi_command >>  8;
  send_cmd[3] = spi_command >>  0;
  for (i=1; i<200; i++) send_cmd[2+(2*i)] = send_cmd[2];
  for (i=1; i<200; i++) send_cmd[3+(2*i)] = send_cmd[3];
  
  // Create the SPI command for the response.
  spi_read = 1;
  spi_auto_inc = 0;
  if (indx == 0) spi_addr = ADDR_HEXA0_TO_PI;
  else spi_addr = ADDR_HEXA1_TO_PI;
  spi_command = (spi_read<<31)|(spi_auto_inc<<30)|(spi_addr<<20);
  response_cmd[0] = spi_command >> 24;
  response_cmd[1] = spi_command >> 16;
  response_cmd[2] = spi_command >> 8;
  response_cmd[3] = spi_command >> 0;
  
  //--------------------------------------------------------------------

  // Wait until the command fifo is not almost_full.
  almost_full_flag = 1;
  while (almost_full_flag == 1) {
    bcm2835_spi_transfernb(status_cmd, data, 4); 
    almost_full_flag = (data[2+indx] >> ALMOST_FULL_FLAG) & 1;
  }
  
  // Since the SPI speed is slower than firmware, proceed 
  // with transmition of all commands.
  bcm2835_spi_transfernb(send_cmd, data, 2+(2*200));
  
  // Wait while the response fifo is not almost_empty.
  almost_empty_flag = 1;
  while (almost_empty_flag == 1) {
    bcm2835_spi_transfernb(status_cmd, data, 4);
    almost_empty_flag = (data[2+indx] >> ALMOST_EMPTY_FLAG) & 1;
  }
  
  // Since the SPI speed is slower than firmware, proceed 
  // with reception of all responses.
  bcm2835_spi_transfernb(response_cmd, data, 2+(2*200));
  
  // Return the results.
  for (i=0; i<200; i++) result[i] = data[3 + (2*i)];
  return(0);
}

int spi_read1000_local_fifo(int hexbd, int result[1000])
{
  unsigned indx, a2, a1, a0, rw;
  unsigned char page[4], c;
  unsigned spi_read, spi_auto_inc, spi_addr, spi_command;
  unsigned almost_empty_flag, almost_full_flag;
  unsigned char status_cmd[4];
  unsigned char send_cmd[(2*1000)+12];
  unsigned char response_cmd[(2*1000)+12];
  unsigned char data[(2*1000)+12];
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
  
  // Create the SPI command for FIFO status.
  spi_read = 1;
  spi_auto_inc = 0;
  if (indx == 0) spi_addr = ADDR_STATUS0;
  else spi_addr = ADDR_STATUS1;
  spi_command = (spi_read<<31)|(spi_auto_inc<<30)|(spi_addr<<20);
  status_cmd[0] = spi_command >> 24;
  status_cmd[1] = spi_command >> 16;
  status_cmd[2] = spi_command >> 8;
  status_cmd[3] = spi_command >> 0;
  
  // Create the SPI commands for read_local_fifo.
  a2 = 0;
  a1 = 0;
  a0 = 1;
  rw = 1; // Do a read.
  c = 0x00; // unused, since {a2,a1,a0} determine the command
  spi_read = 0;
  spi_auto_inc = 0;
  if (indx == 0) spi_addr = ADDR_PI_TO_HEXA0;
  else spi_addr = ADDR_PI_TO_HEXA1;
  spi_command = (spi_read<<31)|(spi_auto_inc<<30)|(spi_addr<<20)|
                (rw<<11)|(a2<<10)|(a1<<9)|(a0<<8)|(c<<0);
  send_cmd[0] = spi_command >> 24;
  send_cmd[1] = spi_command >> 16;
  send_cmd[2] = spi_command >>  8;
  send_cmd[3] = spi_command >>  0;
  for (i=1; i<1000; i++) send_cmd[2+(2*i)] = send_cmd[2];
  for (i=1; i<1000; i++) send_cmd[3+(2*i)] = send_cmd[3];
  
  // Create the SPI command for the response.
  spi_read = 1;
  spi_auto_inc = 0;
  if (indx == 0) spi_addr = ADDR_HEXA0_TO_PI;
  else spi_addr = ADDR_HEXA1_TO_PI;
  spi_command = (spi_read<<31)|(spi_auto_inc<<30)|(spi_addr<<20);
  response_cmd[0] = spi_command >> 24;
  response_cmd[1] = spi_command >> 16;
  response_cmd[2] = spi_command >> 8;
  response_cmd[3] = spi_command >> 0;
  
  //--------------------------------------------------------------------

  // Wait until the command fifo is not almost_full.
  almost_full_flag = 1;
  while (almost_full_flag == 1) {
    bcm2835_spi_transfernb(status_cmd, data, 4); 
    almost_full_flag = (data[2+indx] >> ALMOST_FULL_FLAG) & 1;
  }
  
  // Since the SPI speed is slower than firmware, proceed 
  // with transmition of all commands.
  bcm2835_spi_transfernb(send_cmd, data, 2+(2*1000));
  
  // Wait while the response fifo is not almost_empty.
  almost_empty_flag = 1;
  while (almost_empty_flag == 1) {
    bcm2835_spi_transfernb(status_cmd, data, 4);
    almost_empty_flag = (data[2+indx] >> ALMOST_EMPTY_FLAG) & 1;
  }
  
  // Since the SPI speed is slower than firmware, proceed 
  // with reception of all responses.
  bcm2835_spi_transfernb(response_cmd, data, 2+(2*1000));
  
  // Return the results.
  for (i=0; i<1000; i++) result[i] = data[3 + (2*i)];
  return(0);
}
