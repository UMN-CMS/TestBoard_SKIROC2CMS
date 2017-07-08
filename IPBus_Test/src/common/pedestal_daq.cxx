#include "uhal/uhal.hpp"
#include "ipbus_common.hpp"

#include <vector>
#include <string>
#include <iostream>

const int RAWSIZE = 30787;

using namespace uhal;

int main(int argc, char *argv[]){

	// argument processing
	int maxevents = 10;


	// initialization
	setLogLevelTo(Error());


	// set up connections
	ConnectionManager manager("file://xml/connections.xml");
	std::vector<std::string> ids = manager.getDevices();

	std::vector<HwInterface> rdouts;
	std::vector<std::string>::const_iterator id_iter, id_end;// if only we could use C++ 11 ... for(auto id : ids)
	for(id_end=ids.end(), id_iter=ids.begin(); id_iter != id_end; ++id_iter) {
		std::string id = *id_iter;

		rdouts.push_back(manager.getDevice(id));
	}


	// loop over events
	for(int event = 0; event < maxevents; event++) {
		// loop over readout boards
		std::vector<HwInterface>::iterator hw_iter, hw_end;// C++ 11 ... for(auto& rdout : rdouts)
		for(hw_end=rdouts.end(), hw_iter=rdouts.begin(); hw_iter != hw_end; ++hw_iter) {
			HwInterface& rdout = *hw_iter;

			std::vector<std::string> fifo_list = rdout->getNodes("FIFO.*");

			// loop over hexaboards (fifos for now)
			for(unsigned int i = 0; i < fifo_list.size(); i++) {
				std::cout << fifo_list[i] << std::endl;
			}

			// trigger, etc...
			// read raw
			// decode raw
			// verify data
			// format channels
			// write to data file

		}// end loop over rdouts
	}// end loop over events


	// closing actions
	return 0;
}
