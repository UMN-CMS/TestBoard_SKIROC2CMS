#include "uhal/uhal.hpp"
#include "ipbus_common.hpp"

#include <vector>
#include <string>
#include <iostream>

using namespace uhal;

int main(int argc, char *argv[]){

	int maxevents = 10;

	ConnectionManager manager("file://xml/connections.xml");
	std::vector<string> devices = manager.getDevices();
	std::vector<HwInterface> rdouts;
	for(int i = 0; i < devices.size(); i++) {
		std::cout << devices[i] << std::endl;
		//string name = devices[i];
		//rdouts[i] = manager.getDevice(name);
	}

	return 0;
}
