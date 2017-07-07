#ifndef IPBUS_COMMON_HPP
#define IPBUS_COMMON_HPP

#include "uhal/uhal.hpp"

uint32_t get_word(HwInterface *hw, char *name);
// returns a word from the node specified in the "name" argument

uint32_t *get_nwords(HwInterface *hw, char *name, size_t N);
// returns an array of N words from the node specified in the "name" argument

#endif
