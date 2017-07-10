#include "uhal/uhal.hpp"
#include "ipbus_common.hpp"
#include "daq.hpp"

#include <vector>
#include <string>
#include <iostream>
#include <ctime>
#include <cstdio>// for file writing

using namespace uhal;


int main(int argc, char *argv[]){

	/*************************** argument processing ***************************/
	int runid = (argc < 3) ? 0 : atoi(argv[1]);// for debug
	int maxevents = (argc < 3) ? 1 : atoi(argv[2]);// for debug
	bool saveraw = (argc == 4 && atoi(argv[3]) == 0) ? false : true;

	std::cout << "Run number: " << runid << std::endl;
	std::cout << "Events: " << maxevents << std::endl;
	std::cout << "Save raw: " << saveraw << std::endl;


	/*************************** file naming ***************************/
	char buffer[80];
	char fname[160], raw_fname[160];
	char dirname[] = "data/";
	time_t rawtime;
	struct tm *info;

	// run number and time
	char runNum[8];
	sprintf(runNum, "RUN_%04d", runid);
	time(&rawtime);
	info = localtime(&rawtime);
	strftime(buffer,80,"_%d%m%y_%H%M", info);

	// processed data filename
	strcpy(fname, dirname);
	strcat(fname, runNum);
	strcat(fname, buffer);
	strcat(fname,".txt");
	std::cout << "Filename will be " << fname << std::endl;

	// raw data filename
	strcpy(raw_fname, dirname);
	strcat(raw_fname, runNum);
	strcat(raw_fname, buffer);
	strcat(raw_fname,".raw.txt");
	std::cout << "Raw filename will be " << fname << std::endl;



	/*************************** initialization ***************************/
	setLogLevelTo(Error());



	/*************************** set up connections ***************************/
	ConnectionManager manager("file://xml/connections.xml");// update this file with new connections
	std::vector<std::string> ids = manager.getDevices(".*rdout.*");
	std::vector<HwInterface> rdouts;
	for(unsigned int i = 0; i < ids.size(); i++)
		rdouts.push_back(manager.getDevice(ids[i]));


	/*************************** loop over events ***************************/
	for(int event = 0; event < maxevents; event++) {
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
			std::vector<std::vector<uint32_t> > raw_data = get_nwords_multi_nodes(&rdout, active_fifos, RAWSIZE);
			// do we want a single vector here? And how should it be arranged?

			// TODO
			// verify data
			// format raw
			// decode raw
			// format channels
			// write to data file

			// send readout done signal
			put_done(&rdout);

		}// end loop over rdouts
	}// end loop over events


	/*************************** closing actions ***************************/
	// std::fclose(fraw);
	// std::fclose(fout);
	return 0;
}
