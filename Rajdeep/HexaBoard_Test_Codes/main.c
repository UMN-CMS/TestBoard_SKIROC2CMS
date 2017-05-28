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


#define MODE_READ 0
#define MODE_WRITE 1
#define MODE_SET   1      // redundant
#define MODE_CLR 2
#define MODE_INPUT_READ 3

#define PULL_UP 0
#define PULL_DOWN 1
#define NO_PULL 2

#define GPIO_BEGIN 0
#define GPIO_END 1
#define NO_ACTION 2

static unsigned char BusMode;         // global to remember status of gpio lines (IN or OUT)

#define STpin RPI_V2_GPIO_P1_12
#define RWpin RPI_V2_GPIO_P1_11
#define AD0pin RPI_V2_GPIO_P1_07
#define AD1pin RPI_V2_GPIO_P1_13
#define AD2pin RPI_V2_GPIO_P1_15
#define D0pin RPI_V2_GPIO_P1_37
#define D1pin RPI_V2_GPIO_P1_36
#define D2pin RPI_V2_GPIO_P1_22
#define D3pin RPI_V2_GPIO_P1_18
#define D4pin RPI_V2_GPIO_P1_38
#define D5pin RPI_V2_GPIO_P1_40
#define D6pin RPI_V2_GPIO_P1_33
#define D7pin RPI_V2_GPIO_P1_35
#define ACKpin RPI_V2_GPIO_P1_16


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


unsigned char prog_string[48] = {  0xda, 0xab, 0xff, 0x32, 0xe0, 0xd5, 0x3f, 0xe7, 0xf8, 0xb0,\
                   	 0x40, 0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x1f, 0xff,\
                   	 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,\
                   	 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,\
					 0xff, 0xff, 0xe9, 0xd5, 0x22, 0x8a, 0x80, 0x25}; 

/*unsigned char prog_string[48] = {0xFF, 0xF0, 0xFF, 0x6C, 0x61, 0xC3, 0x78, 0x61, 0xA5, 0xF0, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F,\
              		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,\
              		0xFF, 0xFF, 0xFF, 0xFF, 0xFB, 0xFF, 0xEF, 0xBF, 0xFE, 0x27};				 
	*/				 
					 
unsigned char return_string[48];
#define MAXEVENTS 100

int set_bus_init();
int set_bus_read_mode();
int set_bus_write_mode();
int send_command(unsigned char);
int read_command(void);
int read_usedwl();
int read_usedwh();
int write_local_fifo(unsigned char );
int read_local_fifo();

#define RAWSIZE 30787

unsigned char raw[RAWSIZE];
unsigned int ev[4][1924];
unsigned int dati[4][128][13];

int read_raw(){
	int i, t;
	
	for (i = 0; i < 30787; i = i+1){
		t =read_local_fifo();
		raw[i] = (unsigned char) (t & 255);
	}
	
}

int decode_raw(){
    int i, j, k, m;
    unsigned char x;
	unsigned int t;
	unsigned int bith, bit11, bit10, bit9, bit8, bit7, bit6, bit5, bit4, bit3, bit2, bit1, bit0;
	for( i = 0; i < 1924; i = i+1){
		for (k = 0; k < 4; k = k + 1){
			ev[k][i] = 0;
		}
   	}
    for( i = 0; i < 1924; i = i+1){
        for (j=0; j < 16; j = j+1){
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
   		for(i = 0; i < 128*13; i = i + 1){
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
    }
}

int format_channels(){
    int chip, hit, ch;
	
    for (chip =0; chip < 4; chip = chip +1 ){
        for (ch = 0; ch < 128; ch = ch +1 ){
            for (hit = 0 ; hit <13 ; hit = hit +1){
                dati[chip][ch][hit] = ev[chip][hit*128+ch] & 0x0FFF;
            }
        }
    }
    return(0);
}
    

////////////////////////////
int main()
{
int res;

int ch, sample, chip;
int i, k, n;
time_t rawtime;
bool saveraw;
struct tm *info;
char buffer[80];
char fname [160];
char dirname[] = "/media/pi/HD/Dati/";	

int maxevents = 10;
char instr [1024];
FILE *fraw;
FILE *fout;
 
/***********************************************************************/
 
printf("How many events ? ");
scanf("%d",&maxevents);

printf("\nSave raw data ? [Y/N] ");
scanf("%s",instr);
saveraw = false;
if(instr[0] == 'y' | instr[0] == 'Y')
	saveraw = true;

/* Make up a file name for data */
	time(&rawtime);
	info = localtime(&rawtime);
	strftime(buffer,80,"RUN_%d%m%y_%H%M", info);
	
	strcpy(fname, dirname);
	strcat(fname, buffer);
	strcat(fname,".txt");
	printf("Filename will be %s\n",fname);

	fout = fopen(fname, "w");
	/* save configuration to be used in data file */
	fprintf(fout,"Configuration used for SK2\n");
	for(i = 0; i < 48; i = i + 1){
		fprintf(fout,"%x ",prog_string[i]);
	}
	fprintf(fout,"\nTotal number of events: %d",maxevents);
	fprintf(fout,"\n%s\n####################################################\n",buffer);
	
    /*	optional save raw data */
	strcpy(fname, dirname);
	strcat(fname, buffer);
	strcat(fname,".raw.txt");
	printf("Raw filename will be %s\n",fname);

	fraw = fopen(fname, "w");
	
	
/*  INITIALIZE RPI */
	if (!bcm2835_init())
        return 1;
    set_bus_init();
    // Set the pin to be an output
    bcm2835_gpio_fsel(RWpin, BCM2835_GPIO_FSEL_OUTP);

    /* empty local fifo by forcing extra reads, ignore results */
    i = 0;
    for(i=0; i < 33000; i = i+1){
    	res = read_local_fifo();	
    }
    /*****************************************************/
    /*             set configuration                     */
    /*****************************************************/
    res = send_command(CMD_RESETPULSE);
    res = send_command(CMD_SETSELECT | 1);
    res = send_command(CMD_RSTBPULSE);
    progandverify48(prog_string, return_string);    
    printf("\nFinished Configuration\n");
	
    /*****************************************************/
    /*                  do the work                     */
    /*****************************************************/
    printf("\nStart events acquisition\n");
    n = 0;
    for(i = 0; i < maxevents; i = i +1){
    	res = send_command(CMD_RESETPULSE);
    	usleep(10);
    	res = send_command(CMD_SETSTARTACQ | 1);
    	usleep(3000);
    	res = send_command(CMD_SETSTARTACQ);  /* <<<+++   THIS IS THE TRIGGER */
    	res = send_command(CMD_STARTCONPUL);
    	usleep(4000);
    	res = send_command(CMD_STARTROPUL);
    	usleep(1);
    	res = read_raw();
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
    		if((ev[chip][k] & 0x7E00 ) != 0x0000){
    			printf("Wrong word at %d %d %x\n", i, k,ev[chip][k] );
    		}
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
    	
    	/*for(ch =0; ch < 2; ch = ch +1){
			for (sample=0; sample < 13; sample = sample +1){
				printf("%d ", dati[0][ch][sample]);
			}
			printf("\n");
			for (sample=0; sample < 13; sample = sample +1){
				printf("%d ", dati[0][ch+64][sample]);
			}
			printf("\n");	
		}*/
        /*****************************************************/
		/*             write event to data file              */
        /*****************************************************/
    	for(chip = 0; chip < 4; chip = chip + 1){
    		fprintf(fout, "Event %d Chip %d RollMask %x \n",i, chip, ev[chip][1920]);
    		for(ch =0; ch < 128; ch = ch +1){
    			for (sample=0; sample < 13; sample = sample +1){
    				fprintf(fout, "%d  ", dati[chip][ch][sample]);
    			}
    			fprintf(fout, "\n");
			}	
		}
	}
	fclose(fout);
	fclose(fraw);
    return(0);     
}
