#include <bcm2835.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>

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


/* define commands for Master */

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



////////////////////////////// LOW LEVEL ROUTINES //////////////////////////////
// converts the programming sequence of 48 bytes into 384 single bytes where the LSB is 
// the bit to be programmed
void ConvertProgrStrBytetoBit(unsigned char * bytes, unsigned char * bits)
{
	int i, j;
	unsigned char b;
	for (i = 0; i < 48; i = i + 1){
		b = *(bytes + sizeof(unsigned char) * i);
		for(j = 0; j < 8; j = j + 1){
			*(bits + sizeof(unsigned char) * j + sizeof(unsigned char) * i * 8) = 1 & (b >> (7-j));	
		}	
	}
}


void ConvertProgrStrBittoByte(unsigned char * bits, unsigned char * bytes)
{
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
int prog384(unsigned char * pNew, unsigned char * pPrevious)
{
	int chip, bit, j, byte_index, bit_index;
	unsigned char bit2, bit1, bit0, bits, cmd;
	unsigned char dout;
	for(chip = 0; chip < 4; chip=chip+1){
		for(bit = 0; bit < 384; bit = bit + 3){
			bit2 = *(pNew + sizeof(unsigned char) * bit + 0);
			bit1 = *(pNew + sizeof(unsigned char) * bit + 1);
			bit0 = *(pNew + sizeof(unsigned char) * bit + 2);
			bits = (bit2 << 2) | (bit1 << 1) | bit0;
			cmd = CMD_WRPRBITS | bits;
			send_command(cmd);
			dout = read_command();
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

int progandverify384(unsigned char * pNew, unsigned char * pPrevious)
{
	prog384(pNew, pPrevious);
	
	prog384(pNew, pPrevious);
	
	return(0);
}


int progandverify48(unsigned char * pConfBytes, unsigned char * pPrevious)
{
	unsigned char *pNewConfBits ;  
	unsigned char *pOldConfBits ;
	pNewConfBits = (unsigned char *) malloc(sizeof(unsigned char) * 384);
	pOldConfBits = (unsigned char *) malloc(sizeof(unsigned char) * 384);
	ConvertProgrStrBytetoBit( pConfBytes, pNewConfBits);
	prog384(pNewConfBits, pOldConfBits);
	prog384(pNewConfBits, pOldConfBits);
	ConvertProgrStrBittoByte(pOldConfBits, pPrevious);
	free(pNewConfBits);
	free(pOldConfBits);
	return(0);
}
