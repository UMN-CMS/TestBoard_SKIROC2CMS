#include "uhal/uhal.hpp"
#include "ipbus_common.hpp"

#include <string>
#include <vector>
#include <iostream>

using namespace uhal;


uint32_t get_word(HwInterface *hw, const char *name) {
/* --- reads a single word from a node ---
 *
 * - hw: the hardware interface (must be passed by reference)
 * - name: the name of the node to access
 */

	ValWord<uint32_t> word = hw->getNode(name).read();

	hw->dispatch();

	return word.value();
}


std::vector<uint32_t> get_nwords(HwInterface *hw, const char *name, int N) {
/* --- reads multiple words from a single node ---
 *
 * - hw: the hardware interface (must be passed by reference)
 * - name: the name of the node to access
 * - N: the number of words to read from the node
 */

	std::vector<uint32_t> retArray[N];

	ValVector<uint32_t> node = hw->getNode(name).readBlock(N);

	hw->dispatch();

	for(int i = 0; i < N; i++)
		retArray[i] = node.at(i);

	return retArray;
}


std::vector<uint32_t> get_word_multi_nodes(HwInterface *hw, std::vector<std::string> names) {
/* --- reads a single word from multiple nodes ---
 *
 * - hw: the hardware interface (must be passed by reference)
 * - names: vector containing the names of the nodes to be read from (as strings)
 */

	std::vector<uint32_t> words[names.size()];

	for(int i = 0; i < words.size(); i++)
		words[i] = hw->getNode(names[i].c_str()).read();

	hw->dispatch();

	return words;
}


std::vector<std::vector<uint32_t>> get_nwords_multi_nodes(HwInterface *hw, std::vector<std::string> names, std::vector<int> num_words) {
/* --- reads multiple words from multiple nodes ---
 *
 * - hw: the hardware interface (must be passed by reference)
 * - names: vector containing the names of the nodes to be read from (as strings)
 * - num_words: vector containing the number of words to read from each node
 */

	if(names.size() != num_words.size()) {
		std::cout << "names and num_words do not have the same size" << std::endl;
		exit(0);
	}

	std::vector<std::vector<uint32_t>> words;

	for(int i = 0; i < names.size(); i++)
		words.push_back(hw->getNode(names[i].c_str()).readBlock(num_words[i]));

	hw->dispatch();

	return words;
}
