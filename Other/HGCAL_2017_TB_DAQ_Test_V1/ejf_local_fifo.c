// gcc ejf_local_fifo.o spi_hexaboard.o spi_fast_read.o -l bcm2835 -o ejf_local_fifo
// gcc -c ejf_local_fifo.c -Wall -std=c11
// gcc -c spi_fast_read.c -Wall -std=c11
// gcc -c spi_hexaboard.c -l bcm2835 -Wall -std=c11

#include <bcm2835.h>
#include <stdio.h>
#include <stdlib.h>

void die(const char *s);
void init_SPI();
void end_SPI();
int spi_local_fifo_empty(int hexbd);
int spi_write_local_fifo(int hexbd, unsigned char c);
int spi_read_local_fifo(int hexbd);
int spi_read200_local_fifo(int hexbd, int result[200]);
int spi_read1000_local_fifo(int hexbd, int result[1000]);

#define MAXIO 30705

int main(int argc, char *argv[]){

   int i, j, hexbd;
   unsigned char c;
   int data[MAXIO];
   int num_done;
   int use_hexbd[8];
   unsigned empty_flag;

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

         // empty the local fifo
         for(i = 0; i < 33000; i = i+1){
            empty_flag = spi_local_fifo_empty(hexbd);
            c = spi_read_local_fifo(hexbd);
         }

         // write values into the local_fifo
         for (i=0; i<MAXIO; i++) {
            c = 5^i;
            spi_write_local_fifo(hexbd, c);
         }

         // read values from the local_fifo
         num_done = 0;
         for (j=0; j<30; j++) {
            spi_read1000_local_fifo(hexbd, &(data[num_done]));
            num_done = num_done + 1000;
         }
         for (j=0; j<3; j++) {
            spi_read200_local_fifo(hexbd, &(data[num_done]));
            num_done = num_done + 200;
         }
         for (i=num_done; i<MAXIO; i++) {
            data[i] = spi_read_local_fifo(hexbd);
         }

         // verify.
         int num_ok, num_bad;
         num_ok = 0;
         num_bad = 0;
         for (i=0; i<MAXIO; i++) {
            //fprintf(stderr,"c=%d, expected=%d\n",(int)data[i], (int)((5^i)&0xFF));
            if (data[i] != ((5^i)&0xFF)) num_bad++;
            if (data[i] == ((5^i)&0xFF)) num_ok++;
         }
         fprintf(stderr,"MAXIO = %d\n",(int)MAXIO);
         fprintf(stderr,"num_ok = %d\n",(int)num_ok);
         fprintf(stderr,"num_bad = %d\n",(int)num_bad);
         fprintf(stderr,"\n");

      }
   }
   end_SPI();
   return(0);    
 
}// Main ends here


void die(const char *s){

        printf(s);
        exit(1);
}


void init_SPI(){

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



void end_SPI(){

        bcm2835_spi_end();
        bcm2835_close();
}
