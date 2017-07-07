#ifndef IPBUS_COMMON_HPP
#define IPBUS_COMMON_HPP

#include "uhal/uhal.hpp"

uint32_t get_word(uhal::HwInterface*, const char*);
// reads a single word from a register

std::vector<uint32_t> get_nwords(uhal::HwInterface*, const char*, int N);
// reads N words from a register

std::vector<uint32_t> get_word_multi_nodes(uhal::HwInterface*, std::vector<std::string>);
// reads a single word from multiple registers

std::vector<std::vector<uint32_t>> get_nwords_multi_nodes(uhal::HwInterface*, std::vector<std::string>, std::vector<int>);
// reads multiple words from multiple registers

#endif
