#ifndef IPBUS_COMMON_HPP
#define IPBUS_COMMON_HPP

#include "uhal/uhal.hpp"

uint32_t get_word(HwInterface *hw, char *name);
// reads a single word from a register

uint32_t *get_nwords(HwInterface *hw, char *name, size_t N);
// reads N words from a register

std::vector<uint32_t> get_word_multi_nodes(HwInterface *hw, std::vector<std::string> names);
// reads a single word from multiple registers

std::vector<std::vector<uint32_t>> get_nwords_multi_nodes(HwInterface *hw, std::vector<std::string> names, std::vector<int> num_words);
// reads multiple words from multiple registers

#endif
