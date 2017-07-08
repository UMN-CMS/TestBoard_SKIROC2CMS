#ifndef IPBUS_COMMON_HPP
#define IPBUS_COMMON_HPP

#include "uhal/uhal.hpp"
#include <vector>
#include <string>
#include <cstdio>


#define RDOUT_DONE_MAGIC     (0xABCD4321)



/*** GENERAL ***/
void die(const char*);
// prints the string and exits the program



/*** READ ***/
uint32_t get_word(uhal::HwInterface*, const char*);
// reads a single word from a register

std::vector<uint32_t> get_nwords(uhal::HwInterface*, const char*, int N);
// reads N words from a register

std::vector<uint32_t> get_word_multi_nodes(uhal::HwInterface*, std::vector<std::string>);
// reads a single word from multiple registers

std::vector<std::vector<uint32_t> > get_nwords_multi_nodes(uhal::HwInterface*, std::vector<std::string>, int);
std::vector<std::vector<uint32_t> > get_nwords_multi_nodes(uhal::HwInterface*, std::vector<std::string>, std::vector<int>);
// reads multiple words from multiple registers



/*** WRITE ***/
void put_word(uhal::HwInterface*, const char*, uint32_t);
// writes a single word to a register

void put_nwords(uhal::HwInterface*, const char*, std::vector<uint32_t>);
// writes N words to a register

void put_word_multi_nodes(uhal::HwInterface*, std::vector<std::string>, uint32_t);
void put_word_multi_nodes(uhal::HwInterface*, std::vector<std::string>, std::vector<uint32_t>);
// writes a single word to multiple registers

void put_nwords_multi_nodes(uhal::HwInterface*, std::vector<std::string>, std::vector<std::vector<uint32_t> >);
// writes multiple words to multiple registers



/*** SPECIALIZED FUNCTIONS ***/
uint32_t get_rate20(uhal::HwInterface *hw)
{ return(get_word(hw, "RATE20")); }

uint32_t get_rate40(uhal::HwInterface *hw)
{ return(get_word(hw, "RATE40")); }

uint32_t get_rate80(uhal::HwInterface *hw)
{ return(get_word(hw, "RATE80")); }

uint32_t get_rate160(uhal::HwInterface *hw)
{ return(get_word(hw, "RATE160")); }

uint32_t get_rate320(uhal::HwInterface *hw)
{ return(get_word(hw, "RATE320")); }

uint32_t get_rate320b(uhal::HwInterface *hw)
{ return(get_word(hw, "RATE320b")); }

uint32_t get_rate25(uhal::HwInterface *hw)
{ return(get_word(hw, "RATE25")); }

uint32_t get_rate50(uhal::HwInterface *hw)
{ return(get_word(hw, "RATE50")); }

uint32_t get_rate100(uhal::HwInterface *hw)
{ return(get_word(hw, "RATE100")); }

uint32_t get_rate125(uhal::HwInterface *hw)
{ return(get_word(hw, "RATE125")); }

uint32_t get_firmware_version(uhal::HwInterface *hw)
{ return(get_word(hw, "FW_VER")); }

uint32_t get_constant0(uhal::HwInterface *hw)
{ return(get_word(hw, "CONST0")); }

uint32_t get_constant1(uhal::HwInterface *hw)
{ return(get_word(hw, "CONST1")); }

uint32_t get_disable_debug(uhal::HwInterface *hw)
{ return(get_word(hw, "DISABLE_DEBUG")); }

uint32_t get_skiroc_mask(uhal::HwInterface *hw)
{ return(get_word(hw, "SKIROC_MASK")); }

uint32_t get_date_stamp(uhal::HwInterface *hw)
{ return(get_word(hw, "DATE_STAMP")); }

uint32_t get_block_size(uhal::HwInterface *hw)
{ return(get_word(hw, "BLOCK_SIZE")); }

uint32_t get_pedestal_mode(uhal::HwInterface *hw)
{ return(get_word(hw, "PEDESTAL_MODE")); }

uint32_t get_trig_count(uhal::HwInterface *hw)
{ return(get_word(hw, "TRIG_COUNT")); }

uint32_t get_usec_count0(uhal::HwInterface *hw)
{ return(get_word(hw, "USEC_COUNT0")); }

uint32_t get_usec_count1(uhal::HwInterface *hw)
{ return(get_word(hw, "USEC_COUNT1")); }

uint32_t get_block_ready(uhal::HwInterface *hw)
{ return(get_word(hw, "BLOCK_READY")); }

uint32_t get_half_empty(uhal::HwInterface *hw)
{ return(get_word(hw, "HALF_EMPTY")); }

uint32_t get_empty(uhal::HwInterface *hw)
{ return(get_word(hw, "EMPTY")); }

/*uint32_t get_fifo(uhal::HwInterface *hw, int index)
{ 
	if(index < 0) die("You tried to read a negative fifo");

	char fifo[10];
	sprintf(fifo, "FIFO_%.2i", index);
	return(get_word(hw, fifo));
}*/

void put_done(uhal::HwInterface *hw)
{ put_word(hw, "RDOUT_DONE", RDOUT_DONE_MAGIC); }


#endif
