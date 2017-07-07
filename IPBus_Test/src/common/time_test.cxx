#include "uhal/uhal.hpp"
#include "ipbus_common.hpp"

#include <vector>
#include <chrono>
#include <cstdio>

using namespace uhal;

int main() {

	ConnectionManager manager("file://xml/connections.xml");
	HwInterface rdout = manager.getDevice("hcal.crate115.slot1");

	const size_t N = 262144;

	/*** BLOCK READ ***/
	std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
	start = std::chrono::high_resolution_clock::now();

	std::vector<uint32_t> fifo_block = get_nwords(rdout, "FIFO_00", N);

	end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed_seconds = end-start;

	printf("%f seconds for block reads\n", elapsed_seconds.count());

	double words_per_sec = (N * 1.) / elapsed_seconds.count();
	printf("%e words read per second\n", words_per_sec);

	return 0;
}
