#include <bcm2835.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>
#include <math.h>
#include <string.h>
#include <time.h>


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


/*
unsigned char prog_string[48] = {  0xda, 0xab, 0xff, 0x32, 0xe0, 0xd5, 0x3f, 0xe7, 0xf8, 0xb0,\
                   	 0x40, 0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x1f, 0xff,\
                   	 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,\
                   	 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,\
					 0xff, 0xff, 0xe9, 0xd5, 0x22, 0x8a, 0x80, 0x25}; 
*/
/*
unsigned char prog_string[48] = {  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,\
                          0xff, 0xf,  0xf,  0xf,  0xf,  0xf,  0xf,  0xf,  0xff, 0xff,\
                          0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,\
                          0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,\
                                          0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
*/

/*
unsigned char prog_string[48] = {  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,\
                           0x00, 0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x00, 0x00,\
                           0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,\
                           0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,\
                                           0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
*/

/*unsigned char prog_string[48] = {0xFF, 0xF0, 0xFF, 0x6C, 0x61, 0xC3, 0x78, 0x61, 0xA5, 0xF0, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F,\
              		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,\
              		0xFF, 0xFF, 0xFF, 0xFF, 0xFB, 0xFF, 0xEF, 0xBF, 0xFE, 0x27};				 
	*/

/* new prog string to try:
 0xDA, 0xA0, 0xF9, 0x32, 0xE0, 0xC1, 0x2E, 0x10, 0x98, 0xB0, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xE9, 0xD7, 0xAE, 0xBA, 0x80, 0x25
*/
unsigned char prog_string[48] = { 0xDA, 0xA0, 0xF9, 0x32, 0xE0, 0xC1, 0x2E, 0x10, 0x98, 0xB0, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xE9, 0xD7, 0xAE, 0xBA, 0x80, 0x25}; 


					 
unsigned char return_string[48];
#define MAXEVENTS 100
#define MAXHEXBDS 1
#define nSCA 15

#define NUM_HEXBDS 2
const int Hexbd_Indices[NUM_HEXBDS] = {2,3};

void die(const char *s);
void init_SPI();
void end_SPI();
int spi_send_test(int);
int spi_send_command(int , unsigned char);
int spi_read_command(int);
int spi_read_usedwl(int);
int spi_read_usedwh(int);
int spi_write_local_fifo(int, unsigned char );
int spi_read_local_fifo(int);
int spi_read200_local_fifo(int , int []);
int spi_read1000_local_fifo(int , int []);
int spi_local_fifo_empty(int);
int spi_next_trigger();

/////////////////////Various delays///////////////
unsigned int delay1 = 100;
unsigned int delay2 = 100;
unsigned int delay3 = 3000;
unsigned int delay4 = 100;
//unsigned int delay5 = 0;
/////////////////////////////////////////////////


#define RAWSIZE 30787

unsigned char raw[RAWSIZE];
unsigned int ev[4][1924];
unsigned int data[4][128][nSCA];

int read_raw(int hexbd){

	int i, t;

	for (i = 0; i < RAWSIZE; i = i+1){
		t = spi_read_local_fifo(hexbd);
		raw[i] = (unsigned char) (t & 255);
	}

}


int read_raw_faster(int hexbd) {
   int i, j, num_done, status, t, num_leftovers;
   int result[1000];

   num_done=0;

   for (i=0; i<30; i=i+1) { // Get 30000 values
      status = spi_read1000_local_fifo(hexbd, &(result[0]));
      for (j=0; j<1000; j++) raw[num_done++] = (unsigned char) (result[j] & 255);
   }

   for (i=0; i<3; i=i+1) { // Get 600 values.
      status = spi_read200_local_fifo(hexbd, &(result[0]));
      for (j=0; j<200; j++) raw[num_done++] = (unsigned char) (result[j] & 255);
   }

   // Clean up the last stragglers.
   num_leftovers = RAWSIZE - num_done;
   for (i=0; i<num_leftovers; i=i+1) {
	   t = spi_read_local_fifo(hexbd);
	   raw[num_done++] = (unsigned char) (t & 255);
   }
   return(0);
}

int decode_raw(){

	int i, j, k;
	unsigned char x;
	unsigned int t;
	unsigned int bith, bit11, bit10, bit9, bit8, bit7, bit6, bit5, bit4, bit3, bit2, bit1, bit0;

	for(i = 0; i < 1924; i = i+1){
		for (k = 0; k < 4; k = k + 1){
			ev[k][i] = 0;
		}
   	}

	for(i = 0; i < 1924; i = i+1){
        	for (j = 0; j < 16; j = j+1){
        		x = raw[1 + i*16 + j];
        		x = x & 15;
        		for (k = 0; k < 4; k = k + 1){
            			ev[k][i] = ev[k][i] | (unsigned int) (((x >> (3 - k) ) & 1) << (15 - j));
            		}
        	}
   	}
    
    /*****************************************************/
    /*    Gray to binary conversion                      */
    /*****************************************************/
	for(k = 0; k < 4 ; k = k +1 ){
   		for(i = 0; i < 128*nSCA; i = i + 1){
   			bith = ev[k][i] & 0x8000;
   			t = ev[k][i] & 0x7fff;
   			bit11 = (t >> 11) & 1;
        		bit10 = bit11 ^ ((t >>10) &1);
        		bit9 = bit10 ^ ((t >>9) &1);
        		bit8 = bit9 ^ ((t >>8) &1);
        		bit7 = bit8 ^ ((t >>7) &1);
   		     	bit6 = bit7 ^ ((t >>6) &1);
        		bit5 = bit6 ^ ((t >>5) &1);
        		bit4 = bit5 ^ ((t >>4) &1);
        		bit3 = bit4 ^ ((t >>3) &1);
        		bit2 = bit3 ^ ((t >>2) &1);
        		bit1 = bit2 ^ ((t >>1) &1);
        		bit0 = bit1 ^ ((t >>0) &1);
        		ev[k][i] =  bith | ((bit11 << 11) + (bit10 << 10) + (bit9 << 9) + (bit8 << 8) + (bit7 << 7) + (bit6 << 6) + (bit5 << 5) + (bit4 << 4) + (bit3  << 3) + (bit2 << 2) + (bit1  << 1) + bit0);
        	}
	}// IMPLEMENT GRAY_TO_BINARY convertion as a separate routine

}// The function decode_raw() ends here

int format_channels(){

	int chip, ch, hit; 
	for (chip = 0; chip < 4; chip = chip +1 ){
        	for (ch = 0; ch < 128; ch = ch +1 ){
        		for (hit = 0 ; hit < nSCA ; hit = hit +1){
                		data[chip][ch][hit] = ev[chip][hit*128+ch] & 0x0FFF;
            		}
        	}
    	}

    return(0);

}
    

//////////////////Programming the SKIROCs on the hexaboards///////////////////////////////////////////

void ConvertProgrStrBytetoBit(unsigned char * bytes, unsigned char * bits){

	int i, j;
        unsigned char b;
        for (i = 0; i < 48; i = i + 1){
                b = *(bytes + sizeof(unsigned char) * i);
                for(j = 0; j < 8; j = j + 1){
                        *(bits + sizeof(unsigned char) * j + sizeof(unsigned char) * i * 8) = 1 & (b >> (7-j));
                }
        }
}

void ConvertProgrStrBittoByte(unsigned char * bits, unsigned char * bytes){

	int i, j;
        unsigned char b;
        for (i = 0; i < 48; i = i + 1){
                b = 0;
                for(j = 0; j < 8; j = j + 1){
                        b = b | ( *(bits + sizeof(unsigned char) * i*8 + sizeof(unsigned char) * j) << (7 - j));
                }
                *(bytes + sizeof(unsigned char) * i) = b;
        }
}

// program the 48 bytes configuration string into the SK2 3 bits at a time
// for all 4 chips on Hexaboard
// and return pointer to previous configuration string, assumes pointing to bit sequence
int prog384(int hexbd, unsigned char * pNew, unsigned char * pPrevious){

	int chip, bit;
        unsigned char bit0, bit1, bit2, bits, cmd;
        unsigned char dout;
        for(chip = 0; chip < 4; chip = chip+1){
                for(bit = 0; bit < 384; bit = bit + 3){
                        bit2 = *(pNew + sizeof(unsigned char) * bit + 0);
                        bit1 = *(pNew + sizeof(unsigned char) * bit + 1);
                        bit0 = *(pNew + sizeof(unsigned char) * bit + 2);
                        bits = (bit2 << 2) | (bit1 << 1) | bit0;
                        cmd = CMD_WRPRBITS | bits;
//			cmd = CMD_LOOPBACK | bits;
			printf("Command Sent %2x \n", cmd);
			spi_send_command(hexbd, cmd);
                        dout = spi_read_command(hexbd);
			printf("Command Read Back %2x \n", dout);
                        bits = dout & 7;
                        bit2 = (bits >> 2) & 1;
                        bit1 = (bits >> 1) & 1;
                        bit0 = bits & 1;
                        *(pPrevious + sizeof(unsigned char) * bit + 0) = bit2;
                        *(pPrevious + sizeof(unsigned char) * bit + 1) = bit1;
                        *(pPrevious + sizeof(unsigned char) * bit + 2) = bit0;
                }
        }
        return(0);
}

 int progandverify384(int hexbd, unsigned char * pNew, unsigned char * pPrevious){

        prog384(hexbd, pNew, pPrevious);
        prog384(hexbd, pNew, pPrevious);

        return(0);
}


int progandverify48(int hexbd, unsigned char * pConfBytes, unsigned char * pPrevious){

        unsigned char *pNewConfBits ;
        unsigned char *pOldConfBits ;
        pNewConfBits = (unsigned char *) malloc(sizeof(unsigned char) * 384);
        pOldConfBits = (unsigned char *) malloc(sizeof(unsigned char) * 384);
        ConvertProgrStrBytetoBit( pConfBytes, pNewConfBits);
        prog384(hexbd, pNewConfBits, pOldConfBits);
        prog384(hexbd, pNewConfBits, pOldConfBits);
        ConvertProgrStrBittoByte(pOldConfBits, pPrevious);
        free(pNewConfBits);
        free(pOldConfBits);
        return(0);
}




//////////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[]){

	
	int res;
	int ch, sample, chip;
	int i, k;
	time_t rawtime;
	bool saveraw;
	struct tm *info;
	char buffer[80];
	char fname [160];
	char dirname[] = "/home/pi/HGCAL_2017_TB_DAQ/data/";//Change

	int maxevents = 10;
	char instr [1024];
	FILE *fraw;
	FILE *fout;
 
///////////////////////////Setting up number of run events, file name, etc////////////////////////////////// 

        int runid = 0;
	
	if( argc < 3 ){
	  printf("You need to provide more arguments: <RunNumber> <Number of Events> \n");
	  return(0);
	}

	
	printf("We are here. argc = %d", argc);
	
	runid = atoi(argv[1]);
	char runNum[8];
	sprintf (runNum, "RUN_%04d", runid);

	maxevents = atoi(argv[2]);

	saveraw = true;
       	if (argc == 4 && atoi(argv[3]) == 0)
	    saveraw = false;

	printf("The run number is: %s, Number of events: %d. Save Raw: %d \n \n", runNum, maxevents, (int)saveraw);
	
	//printf("How many events ? ");
	//scanf("%d",&maxevents);

	//printf("\nSave raw data ? [Y/N] ");
	//scanf("%s",instr);
	//saveraw = false;
	//if(instr[0] == 'y' || instr[0] == 'Y')
	//	saveraw = true;

///////////////////////////////Make up a file name for data/////////////////////////
	time(&rawtime);
	info = localtime(&rawtime);
	strftime(buffer,80,"_%d%m%y_%H%M", info);
	
	strcpy(fname, dirname);
	strcat(fname, runNum);
	strcat(fname, buffer);
	strcat(fname,".txt");
	printf("Filename will be %s\n",fname);

	// Just for pause:
	//scanf("%s",instr);
	//
	
	fout = fopen(fname, "w");
	/////////////////////save configuration to be used in data file////////////////
	fprintf(fout,"Configuration used for SK2\n");
	for(i = 0; i < 48; i = i + 1){
		fprintf(fout,"%x ",prog_string[i]);
	}
	fprintf(fout,"\nTotal number of events: %d",maxevents);
	fprintf(fout,"\n%s\n####################################################\n",buffer);
	
    /////////////////////////optional save raw data////////////////////////////
	strcpy(fname, dirname);
	strcat(fname, runNum);
	strcat(fname, buffer);
	strcat(fname,".raw.txt");
	printf("Raw filename will be %s\n",fname);

	fraw = fopen(fname, "w");
///////////////////////////////////////////////////////////////////////////////////////////////	
	
	init_SPI();
	//hexbd = 2;//Current work with one hexaboard, generalize later
	//hexbd = 1;//Current work with one hexaboard, generalize later


//////////////// empty local fifo by forcing extra reads, ignore results////////////////////////////
	unsigned empty_flag;
	for(i = 0; i < 33000; i = i+1){
		for(k = 0; k < NUM_HEXBDS; k++) {
			int hexbd = Hexbd_Indices[k];
//			empty_flag = spi_local_fifo_empty(hexbd);
//			if (empty_flag) break;
			res = spi_read_local_fifo(hexbd);
		}
	}
//////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////Set Configuration////////////////////////
	for(i = 0; i < NUM_HEXBDS; i++) {
		int hexbd = Hexbd_Indices[i];
		res = spi_send_command(hexbd, CMD_RESETPULSE);
		res = spi_send_command(hexbd, CMD_SETSELECT | 1);
		res = spi_send_command(hexbd, CMD_RSTBPULSE);
		progandverify48(hexbd, prog_string, return_string);    
		res = spi_send_command(hexbd, CMD_SETSELECT | 0);// Run with this config
		printf("\nFinished Configuration of Hexaboard %i \n", hexbd);
	}

// Delay the start of "data taking" post configuration to stabilize the state of the chip
	usleep(10000);

	spi_next_trigger();
	spi_next_trigger();
	spi_next_trigger();

////////////////////////////////////////////////////////////////////////
         printf("\nStart events acquisition\n");
         for(i = 0; i < maxevents; i = i +1){

		 for(k = 0; k < NUM_HEXBDS; k++) {
			 int hexbd = Hexbd_Indices[k];

			 res = spi_send_command(hexbd, CMD_RESETPULSE);
			 usleep(delay1);// Can be reduced to 1 MuS cross-check if this speeds things up
			 res = spi_send_command(hexbd, CMD_SETSTARTACQ | 1);
			 usleep(delay2);// Can be reduced to 1 MuS cross-check if this speeds things up

//                 	 res = spi_send_command(hexbd, CMD_SETSTARTACQ);  // <<<+++   SOFTWARE TRIGGER
			 spi_next_trigger(); // <<<<<<< Hardware trigger

			 res = spi_send_command(hexbd, CMD_STARTCONPUL);
			 usleep(delay3);// Can be reduced to 3 milliseconds cross-check if this speeds things up
			 res = spi_send_command(hexbd, CMD_STARTROPUL);
			 usleep(delay4);

//                	 res = read_raw(hexbd);
			 res = read_raw_faster(hexbd);
			 if(saveraw)
				 fwrite(raw, 1, sizeof(raw), fraw);
 
		 /*****************************************************/
		 /*         convert raw to readable data             */
		 /*****************************************************/
			 res = decode_raw();

		 /*****************************************************/
		 /* do some verification that data look OK on one chip*/
		 /*****************************************************/
			 chip= 1;
			 for(k = 0; k < 1664; k = k + 1){
				 if((ev[chip][k] & 0x8000 ) == 0){
					 printf("Wrong MSB at %d %x \n",k,ev[chip][k]);
				 }
/*
				 if((ev[chip][k] & 0x7E00 ) != 0x0000){
					 printf("Wrong word at %d %d %x\n", i, k,ev[chip][k] );
				 }
*/

			 }
 
			 if(ev[chip][1923] != 0xc099){
				 printf("Wrong Trailer is %x \n",ev[chip][1923]);
			 }

		 /*****************************************************/
		 /*           final convert to readable stuff         */
		 /*****************************************************/
			 res = format_channels();
			 printf("*");
			 fflush(stdout);
		 /*****************************************************/
                 /*             write event to data file              */
		 /*****************************************************/
			 for(chip = 0; chip < 4; chip = chip + 1){
				 fprintf(fout, "Event %d Chip %d RollMask %x \n",i, chip, ev[chip][1920]);
				 for(ch = 0; ch < 128; ch = ch +1){
					 for (sample = 0; sample < nSCA; sample = sample +1){
						 fprintf(fout, "%d  ", data[chip][ch][sample]);
					 }
					 fprintf(fout, "\n");
				 }
			 }
//usleep(delay5) 
		}// Loop over hexaboard ends here

         }// Loop over Maxevents ends here


	fclose(fout);
	fclose(fraw);
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
