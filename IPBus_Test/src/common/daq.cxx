#include "uhal/uhal.hpp"
#include "ipbus_common.hpp"
#include "daq.hpp"

#include <vector>
#include <string>
#include <iostream>
#include <chrono>

using namespace uhal;


int main(int argc, char *argv[]){

	/************ argument processing ************/
	// if(argc < 3)
		// die("usage: ./bin/pedestal daq [RUN NUMBER] [EVENTS]");
	int RUN_NUMBER = (argc < 3) ? 0 : atoi(argv[1]);
	int MAXEVENTS = (argc < 3) ? 1 : atoi(argv[2]);

	std::cout << "Run number: " << RUN_NUMBER << std::endl;
	std::cout << "Events: " << MAXEVENTS << std::endl;


	/************ initialization ************/
	setLogLevelTo(Error());


	/************ set up connections ************/
	ConnectionManager manager("file://xml/connections.xml");// update this file with new connections
	std::vector<std::string> ids = manager.getDevices();
	std::vector<HwInterface> rdouts;
	for(unsigned int i = 0; i < ids.size(); i++)
		rdouts.push_back(manager.getDevice(ids[i]));


	/************ loop over events ************/
	for(int event = 0; event < MAXEVENTS; event++) {
		// loop over readout boards
		std::vector<HwInterface>::iterator hw_iter, hw_end;// C++ 11 ... for(auto& rdout : rdouts)
		for(hw_end=rdouts.end(), hw_iter=rdouts.begin(); hw_iter != hw_end; ++hw_iter) {
			HwInterface& rdout = *hw_iter;

			// get the hexaboards currently connected to that readout board
			std::vector<std::string> active_fifos = get_connected_fifos(&rdout);

			// wait until the block is ready to be read (syncboard sent a trigger and data is in the fifos)
			while(check_block_ready(&rdout, active_fifos)) {
				std::cout << "Block not ready! Continuing anyway :)" << std::endl;
				break;
			}

			// read data from each hexaboard
			std::vector<std::vector<uint32_t> > data = get_nwords_multi_nodes(&rdout, active_fifos, RAWSIZE);

			// decode raw
			// verify data
			// format channels
			// write to data file

			// send readout done signal
			put_done(&rdout);

		}// end loop over rdouts
	}// end loop over events


	/************ closing actions ************/
	return 0;
}
