#include "uhal/uhal.hpp"
#include "ipbus_common.hpp"

#include <iostream>
#include <ctime>

using namespace uhal;


int main() {

	setLogLevelTo(Error());
	ConnectionManager manager("file://xml/connections.xml");
	HwInterface hw = manager.getDevice("hcal.crate115.slot1");
	std::vector<std::string> fifos = hw.getNodes("FIFO.*");
	int size = 30787;
	int loops_to_run = 1000;
	int numwords = size * 32;

	std::vector<double> times;

	for(int loop = 0; loop < loops_to_run; loop++) {
		std::clock_t start = std::clock();
		std::vector<std::vector<uint32_t> > data = get_nwords_multi_nodes(&hw, fifos, size);
		std::clock_t end = std::clock();

		double time = (end - start) / (CLOCKS_PER_SEC*1.0);
		double wps = numwords / time;

		times.push_back(wps);
	}

	double avg = 0;
	for(unsigned int i = 0; i < times.size(); i++) {
		avg += times[i];
	}

	avg /= times.size();

	std::cout << "wps: " << avg << std::endl;

	return 0;
}
