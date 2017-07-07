#include "uhal/uhal.hpp"
#include "ipbus_common.hpp"

using namespace uhal;


uint32_t get_word(HwInterface *hw, char *name) {
	// returns a word from the node specified in the "name" argument

	ValWord<uint32_t> word = hw->getNode(name).read();
	hw.dispatch();
	return word.value();
}


uint32_t *get_nwords(HwInterface *hw, char *name, size_t N) {
	// returns an array of N words from the node specified in the "name" argument

	uint32_t *retArray[N];

	ValVector<uint32_t> node = hw->getNode(name).readBlock(N);

	hw.dispatch();

	for(unsigned int i = 0; i < N; i++) {
		retArray[i] = node.at(i);
	}

	return retArray;
}
