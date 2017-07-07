#ifndef IPBUS_COMMON_HPP
#define IPBUS_COMMON_HPP

#include "uhal/uhal.hpp"
#include <vector>
#include <string>


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

std::vector<std::vector<uint32_t>> get_nwords_multi_nodes(uhal::HwInterface*, std::vector<std::string>, std::vector<int>);
// reads multiple words from multiple registers


/*** WRITE ***/
void send_word(uhal::HwInterface*, const char*, uint32_t);
// writes a single word to a register

void send_nwords(uhal::HwInterface*, const char*, std::vector<uint32_t>);
// writes N words to a register

void send_word_multi_nodes(uhal::HwInterface*, std::vector<std::string>, std::vector<uint32_t>);
// writes a single word to multiple registers

void send_nwords_multi_nodes(uhal::HwInterface*, std::vector<std::string>, std::vector<std::vector<uint32_t>>);
// writes multiple words to multiple registers


#endif
