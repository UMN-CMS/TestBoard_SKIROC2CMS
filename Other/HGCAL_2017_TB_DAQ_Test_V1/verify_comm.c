/*

gcc -c -O verify_comm.c -std=c11;
gcc -c -O spi_fast_read.c -std=c11;
gcc -c -O spi_hexaboard.c -l bcm2835 -std=c11;
gcc verify_comm.o spi_hexaboard.o spi_fast_read.o -l bcm2835 -o verify_comm;

*/

#include <bcm2835.h>
#include <stdio.h>
#include <stdlib.h>

void die(const char *s);
void init_SPI();
void end_SPI();
int spi_verify_hexbd_communication(int hexbd);

int main()
{
   int hexbd, status;
   int use_hexbd[8];

   use_hexbd[0] = 1;
   use_hexbd[1] = 1;
   use_hexbd[2] = 0;
   use_hexbd[3] = 1;
   use_hexbd[4] = 1;
   use_hexbd[5] = 0;
   use_hexbd[6] = 0;
   use_hexbd[7] = 0;

   init_SPI();

   for (hexbd=0; hexbd<8; hexbd++) {

      if (use_hexbd[hexbd]) {
         fprintf(stderr,"\nhexbd = %d\n",(int)hexbd);

         status = spi_verify_hexbd_communication(hexbd);
      }
   }

   end_SPI();
   return(0);    

}// Main ends here

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
//        bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_256);     // 1.5625 MHz
	bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_64);     // 6 MHz
        bcm2835_spi_chipSelect(BCM2835_SPI_CS0);                        // Chip-Select 0
        bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, LOW);        // Value of CS when active


}

void end_SPI()
{
        bcm2835_spi_end();
        bcm2835_close();
}
