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
int set_bus_init()
{
  unsigned char lev;
  bcm2835_gpio_fsel(STpin,  BCM2835_GPIO_FSEL_OUTP);     // set pin direction
  bcm2835_gpio_fsel(RWpin,  BCM2835_GPIO_FSEL_OUTP);     // set pin direction
  bcm2835_gpio_fsel(ACKpin, BCM2835_GPIO_FSEL_INPT);     // set pin direction
  bcm2835_gpio_fsel(D7pin, BCM2835_GPIO_FSEL_INPT);
  bcm2835_gpio_fsel(D6pin, BCM2835_GPIO_FSEL_INPT);
  bcm2835_gpio_fsel(D5pin, BCM2835_GPIO_FSEL_INPT);
  bcm2835_gpio_fsel(D4pin, BCM2835_GPIO_FSEL_INPT);
  bcm2835_gpio_fsel(D3pin, BCM2835_GPIO_FSEL_INPT);
  bcm2835_gpio_fsel(D2pin, BCM2835_GPIO_FSEL_INPT);
  bcm2835_gpio_fsel(D1pin, BCM2835_GPIO_FSEL_INPT);
  bcm2835_gpio_fsel(D0pin, BCM2835_GPIO_FSEL_INPT);
  bcm2835_gpio_fsel(AD0pin, BCM2835_GPIO_FSEL_OUTP);
  bcm2835_gpio_fsel(AD1pin, BCM2835_GPIO_FSEL_OUTP);
  bcm2835_gpio_fsel(AD2pin, BCM2835_GPIO_FSEL_OUTP);
  bcm2835_gpio_write(AD0pin, LOW);
  bcm2835_gpio_write(AD1pin, LOW);
  bcm2835_gpio_write(AD2pin, LOW);
  BusMode = MODE_READ;                                // start in Read mode
  lev = bcm2835_gpio_lev(	ACKpin	);	                // check that ACK is HIGH
  if(lev == HIGH) {
    return(0);
  }
  else {
    return(-1);
  }
}

int set_bus_read_mode()
{
  unsigned char lev;
  bcm2835_gpio_write(RWpin, HIGH);
  bcm2835_gpio_write(STpin, HIGH);
  bcm2835_gpio_fsel(D7pin, BCM2835_GPIO_FSEL_INPT);
  bcm2835_gpio_fsel(D6pin, BCM2835_GPIO_FSEL_INPT);
  bcm2835_gpio_fsel(D5pin, BCM2835_GPIO_FSEL_INPT);
  bcm2835_gpio_fsel(D4pin, BCM2835_GPIO_FSEL_INPT);
  bcm2835_gpio_fsel(D3pin, BCM2835_GPIO_FSEL_INPT);
  bcm2835_gpio_fsel(D2pin, BCM2835_GPIO_FSEL_INPT);
  bcm2835_gpio_fsel(D1pin, BCM2835_GPIO_FSEL_INPT);
  bcm2835_gpio_fsel(D0pin, BCM2835_GPIO_FSEL_INPT);
  BusMode = MODE_READ;
  lev = bcm2835_gpio_lev(	ACKpin	);	                // check that ACK is HIGH
  if(lev == HIGH) {
    return(0);
  }
  else {
    return(-1);
  }
}

int set_bus_write_mode()
{
  unsigned char lev;
  bcm2835_gpio_write(RWpin, LOW);
  bcm2835_gpio_write(STpin, HIGH);
  bcm2835_gpio_fsel(D7pin, BCM2835_GPIO_FSEL_OUTP);
  bcm2835_gpio_fsel(D6pin, BCM2835_GPIO_FSEL_OUTP);
  bcm2835_gpio_fsel(D5pin, BCM2835_GPIO_FSEL_OUTP);
  bcm2835_gpio_fsel(D4pin, BCM2835_GPIO_FSEL_OUTP);
  bcm2835_gpio_fsel(D3pin, BCM2835_GPIO_FSEL_OUTP);
  bcm2835_gpio_fsel(D2pin, BCM2835_GPIO_FSEL_OUTP);
  bcm2835_gpio_fsel(D1pin, BCM2835_GPIO_FSEL_OUTP);
  bcm2835_gpio_fsel(D0pin, BCM2835_GPIO_FSEL_OUTP);
  BusMode = MODE_WRITE;
  lev = bcm2835_gpio_lev(	ACKpin	);	                // check that ACK is HIGH
  if(lev == HIGH) {
    return(0);
  }
  else {
    return(-1);
  }
}

int send_command(unsigned char c)
{
  bool NoAck;
  unsigned char lev;
  NoAck = false;
  bcm2835_gpio_write(AD0pin, LOW);
  bcm2835_gpio_write(AD1pin, LOW);
  bcm2835_gpio_write(AD2pin, LOW);
  if(BusMode == MODE_READ)
    set_bus_write_mode();

  bcm2835_gpio_write(D0pin, (c       &1));
  bcm2835_gpio_write(D1pin, ((c >> 1)&1));
  bcm2835_gpio_write(D2pin, ((c >> 2)&1));
  bcm2835_gpio_write(D3pin, ((c >> 3)&1));
  bcm2835_gpio_write(D4pin, ((c >> 4)&1));
  bcm2835_gpio_write(D5pin, ((c >> 5)&1));
  bcm2835_gpio_write(D6pin, ((c >> 6)&1));
  bcm2835_gpio_write(D7pin, ((c >> 7)&1));
  bcm2835_gpio_write(RWpin, LOW);
  bcm2835_gpio_write(STpin, LOW);
  lev = bcm2835_gpio_lev(	ACKpin	);	                // check that ACK is LOW
  if(lev == HIGH) {
    NoAck = true;
  }
  bcm2835_gpio_write(STpin, HIGH);
  bcm2835_gpio_write(RWpin, HIGH);

  lev = bcm2835_gpio_lev(	ACKpin	);	                // check that ACK is HIGH
  if(lev == LOW) {
    NoAck = true;
  }
  if(NoAck){
    return(-1);
  }
  else {
    return(0);
  }
}


int read_command(void)
{
  bool NoAck;
  unsigned char l;
  unsigned char r;
  int result;
  unsigned char lev;
  NoAck = false;
  bcm2835_gpio_write(AD0pin, LOW);
  bcm2835_gpio_write(AD1pin, LOW);
  bcm2835_gpio_write(AD2pin, LOW);
  if(BusMode == MODE_WRITE)
    set_bus_read_mode();

  bcm2835_gpio_write(RWpin, HIGH);
  bcm2835_gpio_write(STpin, LOW);
  lev = bcm2835_gpio_lev(	ACKpin	);	                // check that ACK is LOW
  if(lev == HIGH) {
    NoAck = true;
  }
  r = 0;
  l = bcm2835_gpio_lev(D0pin);
  r = r | l;
  l = bcm2835_gpio_lev(D1pin);
  r = r | (l << 1);
  l = bcm2835_gpio_lev(D2pin);
  r = r | (l << 2);
  l = bcm2835_gpio_lev(D3pin);
  r = r | (l << 3);
  l = bcm2835_gpio_lev(D4pin);
  r = r | (l << 4);
  l = bcm2835_gpio_lev(D5pin);
  r = r | (l << 5);
  l = bcm2835_gpio_lev(D6pin);
  r = r | (l << 6);
  l = bcm2835_gpio_lev(D7pin);
  r = r | (l << 7);

  result = (int) r;
  bcm2835_gpio_write(STpin, HIGH);

  lev = bcm2835_gpio_lev(	ACKpin	);	                // check that ACK is HIGH
  if(lev == LOW) {
    NoAck = true;
  }
  if(NoAck){
    return(-1);
  }
  else {
    return(result);
  }
}

// Read used word counter on Max10 FIFO, low part
int read_usedwl(){
  bool NoAck;
  unsigned char l;
  unsigned char r;
  int result;
  unsigned char lev;
  NoAck = false;
  bcm2835_gpio_write(AD0pin, LOW);
  bcm2835_gpio_write(AD1pin, HIGH);
  bcm2835_gpio_write(AD2pin, LOW);
  if(BusMode == MODE_WRITE)
    set_bus_read_mode();

  bcm2835_gpio_write(RWpin, HIGH);
  bcm2835_gpio_write(STpin, LOW);
  lev = bcm2835_gpio_lev(	ACKpin	);	                // check that ACK is LOW
  if(lev == HIGH) {
    NoAck = true;
  }
  r = 0;
  l = bcm2835_gpio_lev(D0pin);
  r = r | l;
  l = bcm2835_gpio_lev(D1pin);
  r = r | (l << 1);
  l = bcm2835_gpio_lev(D2pin);
  r = r | (l << 2);
  l = bcm2835_gpio_lev(D3pin);
  r = r | (l << 3);
  l = bcm2835_gpio_lev(D4pin);
  r = r | (l << 4);
  l = bcm2835_gpio_lev(D5pin);
  r = r | (l << 5);
  l = bcm2835_gpio_lev(D6pin);
  r = r | (l << 6);
  l = bcm2835_gpio_lev(D7pin);
  r = r | (l << 7);

  result = (int) r;
  bcm2835_gpio_write(STpin, HIGH);

  lev = bcm2835_gpio_lev(	ACKpin	);	                // check that ACK is HIGH
  if(lev == LOW) {
    NoAck = true;
  }
  if(NoAck){
    return(-1);
  }
  else {
    return(result);
  }
}

// Read used word counter on Max10 FIFO, high part
int read_usedwh(){
  bool NoAck;
  unsigned char l;
  unsigned char r;
  int result;
  unsigned char lev;
  NoAck = false;
  bcm2835_gpio_write(AD0pin, HIGH);
  bcm2835_gpio_write(AD1pin, HIGH);
  bcm2835_gpio_write(AD2pin, LOW);
  if(BusMode == MODE_WRITE)
    set_bus_read_mode();

  bcm2835_gpio_write(RWpin, HIGH);
  bcm2835_gpio_write(STpin, LOW);
  lev = bcm2835_gpio_lev(	ACKpin	);	                // check that ACK is LOW
  if(lev == HIGH) {
    NoAck = true;
  }
  r = 0;
  l = bcm2835_gpio_lev(D0pin);
  r = r | l;
  l = bcm2835_gpio_lev(D1pin);
  r = r | (l << 1);
  l = bcm2835_gpio_lev(D2pin);
  r = r | (l << 2);
  l = bcm2835_gpio_lev(D3pin);
  r = r | (l << 3);
  l = bcm2835_gpio_lev(D4pin);
  r = r | (l << 4);
  l = bcm2835_gpio_lev(D5pin);
  r = r | (l << 5);
  l = bcm2835_gpio_lev(D6pin);
  r = r | (l << 6);
  l = bcm2835_gpio_lev(D7pin);
  r = r | (l << 7);

  result = (int) r;
  bcm2835_gpio_write(STpin, HIGH);

  lev = bcm2835_gpio_lev(	ACKpin	);	                // check that ACK is HIGH
  if(lev == LOW) {
    NoAck = true;
  }
  if(NoAck){
    return(-1);
  }
  else {
    return(result);
  }
}


// Write into the local FIFO
int write_local_fifo(unsigned char c){
  bool NoAck;
  unsigned char l;
  unsigned char r;
  NoAck = false;
  unsigned char lev;
  bcm2835_gpio_write(AD0pin, HIGH);
  bcm2835_gpio_write(AD1pin, LOW);
  bcm2835_gpio_write(AD2pin, LOW);
  if(BusMode == MODE_READ)
    set_bus_write_mode();

bcm2835_gpio_write(D0pin, ( c    &1));
  bcm2835_gpio_write(D1pin, ((c >> 1)&1));
  bcm2835_gpio_write(D2pin, ((c >> 2)&1));
  bcm2835_gpio_write(D3pin, ((c >> 3)&1));
  bcm2835_gpio_write(D4pin, ((c >> 4)&1));
  bcm2835_gpio_write(D5pin, ((c >> 5)&1));
  bcm2835_gpio_write(D6pin, ((c >> 6)&1));
  bcm2835_gpio_write(D7pin, ((c >> 7)&1));

  bcm2835_gpio_write(STpin, LOW);
  lev = bcm2835_gpio_lev(	ACKpin	);	                // check that ACK is LOW
  if(lev == HIGH) {
    NoAck = true;
  }

  bcm2835_gpio_write(STpin, HIGH);

  lev = bcm2835_gpio_lev(	ACKpin	);	                // check that ACK is HIGH
  if(lev == LOW) {
    NoAck = true;
  }
  if(NoAck){
    return(-1);
  }
  else {
    return(0);
  }
}

// Read from the local FIFO
int read_local_fifo(){
  bool NoAck;
  unsigned char l;
  unsigned char r;
  int result;
  unsigned char lev;
  NoAck = false;
  bcm2835_gpio_write(AD0pin, HIGH);
  bcm2835_gpio_write(AD1pin, LOW);
  bcm2835_gpio_write(AD2pin, LOW);
  if(BusMode == MODE_WRITE)
    set_bus_read_mode();

  bcm2835_gpio_write(STpin, LOW);
  lev = bcm2835_gpio_lev(	ACKpin	);	                // check that ACK is LOW
  if(lev == HIGH) {
    NoAck = true;
  }
  r = 0;
  l = bcm2835_gpio_lev(D0pin);
  r = r | l;
  l = bcm2835_gpio_lev(D1pin);
  r = r | (l << 1);
  l = bcm2835_gpio_lev(D2pin);
  r = r | (l << 2);
  l = bcm2835_gpio_lev(D3pin);
  r = r | (l << 3);
  l = bcm2835_gpio_lev(D4pin);
  r = r | (l << 4);
  l = bcm2835_gpio_lev(D5pin);
  r = r | (l << 5);
  l = bcm2835_gpio_lev(D6pin);
  r = r | (l << 6);
  l = bcm2835_gpio_lev(D7pin);
  r = r | (l << 7);

  result = (int) r;
  
  bcm2835_gpio_write(STpin, HIGH);

  lev = bcm2835_gpio_lev(	ACKpin	);	                // check that ACK is HIGH
  if(lev == LOW) {
    NoAck = true;
  }

  /*if(NoAck){
    printf("No ack\n");
    return(-1);
  }
  else {
    return(result);
  }*/
  return(result);
}


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

void trigger_gen(){
  bcm2835_gpio_write(AD0pin, HIGH);
  bcm2835_gpio_write(AD1pin, HIGH);
  bcm2835_gpio_write(AD2pin, HIGH);
  bcm2835_gpio_write(RWpin, LOW);
  bcm2835_gpio_write(STpin, LOW);
  bcm2835_gpio_write(STpin, HIGH);
  bcm2835_gpio_write(RWpin, HIGH);
}