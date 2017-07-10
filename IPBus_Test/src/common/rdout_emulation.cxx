#include "uhal/uhal.hpp"
#include "ipbus_common.hpp"
#include "daq.hpp"

#include <vector>
#include <string>
#include <iostream>

using namespace uhal;


int main(int argc, char *argv[]){

	/*************************** initialization ***************************/
	setLogLevelTo(Error());

	uint32_t header = 0xababcdcd;
	uint32_t padding = 0xffffffff;
	uint32_t crc = 0xccaaccaa;
	std::vector<uint32_t> dummy_data(966);

	dummy_data[0] = header;
	dummy_data[965] = padding;
	dummy_data[963] = padding;
	dummy_data[964] = crc;
	for(unsigned int i = 0; i < 962; i++)
		dummy_data[i+1] = 0xdeadbeef;
	



	/*************************** set up connections ***************************/
	ConnectionManager manager("file://xml/connections.xml");// update this file with new connections
	std::vector<std::string> ids = manager.getDevices(".*dummy.*");
	std::vector<HwInterface> rdouts;
	for(unsigned int i = 0; i < ids.size(); i++)
		rdouts.push_back(manager.getDevice(ids[i]));


	// loop over readout boards
	std::vector<HwInterface>::iterator hw_iter, hw_end;// C++ 11 ... for(auto& rdout : rdouts)
	for(hw_end=rdouts.end(), hw_iter=rdouts.begin(); hw_iter != hw_end; ++hw_iter) {
		HwInterface& rdout = *hw_iter;

		std::vector<std::string> fifos = rdout.getNodes("FIFO.*");
		
		for(unsigned int i = 0; i < fifos.size(); i++)
			rdout.getNode(fifos[i]).writeBlock(dummy_data);

		rdout.dispatch();

	}// end loop over rdouts

	return 0;
}
