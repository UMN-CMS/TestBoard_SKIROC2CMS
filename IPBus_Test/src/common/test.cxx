#include "uhal/uhal.hpp"
#include <cstdio>

using namespace uhal;

int main() {

	printf("Initializing connection manager\n");
	ConnectionManager manager("file://xml/connections.xml");
	printf("Getting rdout board\n");
	HwInterface hw = manager.getDevice("hcal.crate115.slot1");

	printf("Getting FW_VER, CONST0, and CONST1 nodes\n");
	ValWord<uint32_t> fw_ver = hw.getNode("FW_VER").read();
	ValWord<uint32_t> const0 = hw.getNode("CONST0").read();
	ValWord<uint32_t> const1 = hw.getNode("CONST1").read();

	printf("Dispatching hardware\n");
	hw.dispatch();

	printf("\n");
	printf("Firmware Version: %i\n", fw_ver.value());
	printf("Constant 0: %x\n", const0.value());
	printf("Constant 1: %x\n", const1.value());
	printf("\n");

	return 0;
}
