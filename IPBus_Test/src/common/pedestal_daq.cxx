#include "uhal/uhal.hpp"
#include "ipbus_common.hpp"

#include <vector>
#include <string>
#include <iostream>

const int RAWSIZE = 30787;

using namespace uhal;

bool check_block_ready(HwInterface *hw, std::vector<std::string> active_fifos);
std::vector<std::string> hexaboard_to_fifo(std::vector<int>);
std::vector<std::string> hexaboard_to_fifo(int);

int main(int argc, char *argv[]){

	// argument processing
	// if(argc < 3)
		// die("usage: ./bin/pedestal daq [RUN NUMBER] [EVENTS]");
	int RUN_NUMBER = argc < 3 ? 0 : atoi(argv[1]);
	int MAXEVENTS = argc < 3 ? 1 : atoi(argv[2]);

	std::cout << "Run number: " << RUN_NUMBER << std::endl;
	std::cout << "Events: " << MAXEVENTS << std::endl;


	// initialization
	setLogLevelTo(Error());


	// set up connections
	ConnectionManager manager("file://xml/connections.xml");
	std::vector<std::string> ids = manager.getDevices();
	std::vector<HwInterface> rdouts;
	for(unsigned int i = 0; i < ids.size(); i++)
		rdouts.push_back(manager.getDevice(ids[i]));


	// loop over events
	for(int event = 0; event < MAXEVENTS; event++) {
		// loop over readout boards
		std::vector<HwInterface>::iterator hw_iter, hw_end;// C++ 11 ... for(auto& rdout : rdouts)
		for(hw_end=rdouts.end(), hw_iter=rdouts.begin(); hw_iter != hw_end; ++hw_iter) {
			HwInterface& rdout = *hw_iter;

			std::vector<std::string> fifo_list = rdout.getNodes("FIFO.*");
			std::vector<std::string> active_fifos = fifo_list;// all fifos(for now)

			// trigger, etc...
			while(check_block_ready(&rdout, active_fifos)) {
				std::cout << "Block not ready!" << std::endl;
				std::cout << "Continuing anyway :)" << std::endl;
				break;
			}

			// read data from each hexaboard
			std::vector<uint32_t> data = get_word_multi_nodes(&rdout, fifo_list);

			// decode raw
			// verify data
			// format channels
			// write to data file

		}// end loop over rdouts
	}// end loop over events


	// closing actions
	return 0;
}


bool check_block_ready(HwInterface *hw, std::vector<std::string> active_fifos) {
	uint32_t block_ready = get_block_ready(hw);

	for(unsigned int i = 0; i < active_fifos.size(); i++) {
		int fifo_num = atoi(active_fifos[i].substr(5).c_str());

		if(block_ready & (1 << fifo_num))
			return false;
	}

	return true;
}


std::vector<string> hexaboard_to_fifo(int) {

}


std::vector<string> hexaboard_to_fifo(std::vector<int>) {

}
