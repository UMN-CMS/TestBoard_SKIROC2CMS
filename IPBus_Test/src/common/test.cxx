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
	ValWord<uint32_t> rate20 = hw.getNode("RATE20").read();
	ValWord<uint32_t> rate320b = hw.getNode("RATE320b").read();
	ValWord<uint32_t> magic = hw.getNode("RDOUT_DONE_MAGIC").read();

	printf("Dispatching hardware\n");
	hw.dispatch();

	printf("\n");
	printf("Firmware Version: %i\n", fw_ver.value(), fw_ver.value());
	printf("Constant 0: %x (%i)\n", const0.value(), const0.value());
	printf("Constant 1: %x (%i)\n", const1.value(), const1.value());
	printf("Rate 20: %x (%i)\n", rate20.value(), rate20.value());
	printf("Rate 320b: %x (%i)\n", rate320b.value(), rate320b.value());
	printf("Magic: %x (%i)\n", magic.value(), magic.value());
	printf("\n");

	return 0;
}
