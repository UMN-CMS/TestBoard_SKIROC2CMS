#include "uhal/uhal.hpp"
#include "ipbus_common.hpp"

#include <vector>
#include <cstdio>

using namespace uhal;

int main() {

	// initializing hardware
	ConnectionManager manager("file://xml/connections.xml");
	HwInterface rdout = manager.getDevice("hcal.crate115.slot1");

	// testing get_word()
	uint32_t fw_ver = get_word(&rdout, "FW_VER");
	uint32_t const0 = get_word(&rdout, "CONST0");
	uint32_t const1 = get_word(&rdout, "CONST1");
	printf("Firmware Version: %x (%u)\n", fw_ver, fw_ver);
	printf("Constant 0: %x (%u)\n", const0, const0);
	printf("Constant 1: %x (%u)\n", const1, const1);

	// testing get_nwords()
	const size_t N = 256;
	std::vector<uint32_t> fifo = get_nwords(&rdout, "FIFO_OO", N);
	printf("Reading from fifo...\n");
	for(int i = 0; i < 256; i++) {
		printf("%x (%u)\n", fifo[i], fifo[i]);
	}

	return 0;
}
