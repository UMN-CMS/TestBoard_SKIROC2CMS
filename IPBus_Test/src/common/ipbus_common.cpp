#include "uhal/uhal.hpp"
#include "ipbus_common.hpp"

#include <string>
#include <vector>
#include <iostream>

using namespace uhal;



/*** GENERAL ***/
void die(const char *s) {
/* --- prints the string and kills the program --- */

	std::cout << s << std::endl;
	exit(1);
}



/*** READ ***/
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

	ValVector<uint32_t> node = hw->getNode(name).readBlock(N);

	hw->dispatch();

	return node.value();
}


std::vector<uint32_t> get_word_multi_nodes(HwInterface *hw, std::vector<std::string> names) {
/* --- reads a single word from multiple nodes ---
 *
 * - hw: the hardware interface (must be passed by reference)
 * - names: vector containing the names of the nodes to be read from (as strings)
 */

	unsigned int i;

	std::vector<ValWord<uint32_t> > words(names.size());
	std::vector<uint32_t> values(names.size());

	for(i = 0; i < names.size(); i++)
		words[i] = hw->getNode(names[i]).read();

	hw->dispatch();

	for(i = 0; i < names.size(); i++)
		values[i] = words[i].value();

	return values;
}


std::vector<std::vector<uint32_t> > get_nwords_multi_nodes(HwInterface *hw, std::vector<std::string> names, int num_words) {
/* --- reads multiple words from multiple nodes ---
 *
 * - hw: the hardware interface (must be passed by reference)
 * - names: vector containing the names of the nodes to be read from (as strings)
 * - num_words: the number of words to read from each node (overloaded with a vector if different block sizes need to be read)
 */

	unsigned int i;

	std::vector<ValVector<uint32_t> > vectors(names.size());
	std::vector<std::vector<uint32_t> > vals(names.size());

	for(i = 0; i < names.size(); i++)
		vectors[i] = hw->getNode(names[i]).readBlock(num_words);

	hw->dispatch();

	for(i = 0; i < names.size(); i++)
		vals[i] = vectors[i].value();

	return vals;
}


std::vector<std::vector<uint32_t> > get_nwords_multi_nodes(HwInterface *hw, std::vector<std::string> names, std::vector<int> num_words) {
/* --- reads multiple words from multiple nodes ---
 *
 * - hw: the hardware interface (must be passed by reference)
 * - names: vector containing the names of the nodes to be read from (as strings)
 * - num_words: vector containing the number of words to read from each node (overloaded with an int if only one block size)
 */

	if(names.size() != num_words.size())
		die("names and num_words do not have the same size");

	unsigned int i;

	std::vector<ValVector<uint32_t> > vectors(names.size());
	std::vector<std::vector<uint32_t> > vals(names.size());

	for(i = 0; i < names.size(); i++)
		vectors[i] = hw->getNode(names[i]).readBlock(num_words[i]);

	hw->dispatch();

	for(i = 0; i < names.size(); i++)
		vals[i] = vectors[i].value();

	return vals;
}




/*** WRITE ***/
void put_word(HwInterface *hw, const char *name, uint32_t word) {
/* --- writes a single word to a node ---
 *
 * - hw: the hardware interface (must be passed by reference)
 * - name: the name of the node to access
 * - word: the value to write
 */

	hw->getNode(name).write(word);
	hw->dispatch();
	return;
}


void put_nwords(HwInterface *hw, const char *name, std::vector<uint32_t> words) {
/* --- writes multiple words to a single node ---
 *
 * - hw: the hardware interface (must be passed by reference)
 * - name: the name of the node to access
 * - words: vector containing the words to write to the node
 */

	hw->getNode(name).writeBlock(words);
	hw->dispatch();
	return;
}


void put_word_multi_nodes(HwInterface *hw, std::vector<std::string> names, std::vector<uint32_t> words) {
/* --- writes a single word to multiple nodes ---
 *
 * - hw: the hardware interface (must be passed by reference)
 * - names: vector containing the names of the nodes to be written to (as strings)
 * - words: vector containing the words to write to each node
 */

	for(unsigned int i = 0; i < words.size(); i++)
		hw->getNode(names[i]).write(words[i]);
	hw->dispatch();
	return;
}


void put_nwords_multi_nodes(HwInterface *hw, std::vector<std::string> names, std::vector<std::vector<uint32_t> > words) {
/* --- writes multiple words to multiple nodes ---
 *
 * - hw: the hardware interface (must be passed by reference)
 * - names: vector containing the names of the nodes to be write to (as strings)
 * - words: vector containing the blocks of words to write to each node
 */

	if(names.size() != words.size())
		die("names and words do not have the same size");

	for(unsigned int i = 0; i < names.size(); i++)
		hw->getNode(names[i]).writeBlock(words[i]);
	hw->dispatch();
	return;
}