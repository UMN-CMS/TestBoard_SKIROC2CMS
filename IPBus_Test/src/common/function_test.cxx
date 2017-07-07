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
	uint32_t fw_ver = get_word(rdout, "FW_VER");
	printf("Firmware Version: %x (%u)\n", fw_ver, fw_ver);

	// testing get_nwords()
	const size_t N = 256;
	std::vector<uint32_t> fifo = get_nwords(rdout, "FIFO_OO", N);
	for(int i = 0; i < 256; i++) {
		printf("%x (%u)\n", fifo[i], fifo[i]);
	}

	return 0;
}
