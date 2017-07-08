#include "uhal/uhal.hpp"
#include "ipbus_common.hpp"

#include <vector>
#include <string>
#include <iostream>

using namespace uhal;

int main(int argc, char *argv[]){
	
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


	// loop over readout boards
	std::vector<HwInterface>::iterator hw_iter, hw_end;// C++ 11 ... for(auto& rdout : rdouts)
	for(hw_end=rdouts.end(), hw_iter=rdouts.begin(); hw_iter != hw_end; ++hw_iter) {
		HwInterface& rdout = *hw_iter;

		// get all fifos and read their values once
		std::cout << "\nReading single values from each fifo\n";
		std::vector<std::string> fifo_ids = rdout.getNodes("FIFO.*");
		std::vector<uint32_t> fifo_vals = get_word_multi_nodes(&rdout, fifo_ids);

		// print values
		for(unsigned int i = 0; i < fifo_vals.size(); i++) {

			std::cout << std::dec << i << " : ";
			std::cout << std::hex << fifo_vals[i] << std::endl;
		}
		std::cout << std::endl << std::endl << std::endl;


		// block reads
		std::cout << "Reading blocks of 256 from each fifo\n";
		int blocksize = 256;// could also be a vector
		std::vector<std::vector<uint32_t> > fifo_vectors = get_nwords_multi_nodes(&rdout, fifo_ids, blocksize);

		// print values
		for(unsigned int i = 0; i < fifo_vectors.size(); i++) {
			std::cout << "---------------------- FIFO " << std::dec << i << std::endl;
			for(unsigned int j = 0; j < fifo_vectors[i].size(); j++) {
				std::cout << std::dec << j << ": " << std::hex << fifo_vectors[i][j] << std::endl;
			}
			std::cout << std::endl;
		}

	}// end loop over rdouts


	// closing actions
	return 0;
}
