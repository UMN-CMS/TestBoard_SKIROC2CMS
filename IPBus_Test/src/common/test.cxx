#include "uhal/uhal.hpp"
#include <cstdio>

using namespace uhal;

int main() {

	printf("Initializing connection manager\n");
	ConnectionManager manager("file://xml/connections.xml");
	printf("Getting rdout board\n");
	HwInterface rdout = manager.getDevice("hcal.crate115.slot1");

	printf("Getting FW_VER, CONST0, and CONST1 nodes\n");
	uint32_t fw_ver = get_word(&rdout, "FW_VER");
	uint32_t const0 = get_word(&rdout, "CONST0");
	uint32_t const1 = get_word(&rdout, "CONST1");
	uint32_t rate20 = get_word(&rdout, "RATE20");
	uint32_t rate320b = get_word(&rdout, "RATE320b");
	uint32_t magic = get_word(&rdout, "RDOUT_DONE_MAGIC");

	printf("\n");
	printf("Firmware Version: %i\n", fw_ver, fw_ver);
	printf("Constant 0: %x (%i)\n", const0, const0);
	printf("Constant 1: %x (%i)\n", const1, const1);
	printf("Rate 20: %x (%i)\n", rate20, rate20);
	printf("Rate 320b: %x (%i)\n", rate320b, rate320b);
	printf("Magic: %x (%i)\n", magic, magic);
	printf("\n");

	return 0;
}
