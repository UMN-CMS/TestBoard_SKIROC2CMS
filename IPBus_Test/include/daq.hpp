#ifndef DAQ_HPP
#define DAQ_HPP

#include "uhal/uhal.hpp"
#include "ipbus_common.hpp"

#include <vector>
#include <string>
#include <cstdio>

/*** constants ***/
const int SKIROCS_PER_HEXBD = 4;
const int MAXSKIROCS = 32;
const int RAWSIZE = 30787;



/*** functions ***/
std::vector<std::string> get_connected_fifos(uhal::HwInterface *hw) {
	std::vector<std::string> fifo_list;
	char fifo_name[10];

	uint32_t skiroc_mask = get_skiroc_mask(hw);
	for(int i = 0; i < MAXSKIROCS; i++) {
		if(skiroc_mask & (1 << i)) {
			sprintf(fifo_name, "FIFO_%.2i", i);
			fifo_list.push_back(fifo_name);
		}
	}

	return fifo_list;
}


bool check_block_ready(uhal::HwInterface *hw, std::vector<std::string> active_fifos) {
	uint32_t block_ready = get_block_ready(hw);
	int fifo_num;

	for(unsigned int i = 0; i < active_fifos.size(); i++) {
		fifo_num = atoi(active_fifos[i].substr(5).c_str());

		if(block_ready & (1 << fifo_num))
			return false;
	}

	return true;
}

#endif
