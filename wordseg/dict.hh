//
// Created by c on 06/09/2017 04:35 PM
//

#ifndef WORDSEG_DICT_HH
#define WORDSEG_DICT_HH

/* include section */

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include "wordseg/string.hh"
#include "wordseg/trie.hh"

/* class & function section */

namespace wordseg {

// word search dict
class DictWord : public detail::NaiveTrie<std::vector<std::string>> {
public:
	// constructor & destructor
	DictWord() : detail::NaiveTrie<std::vector<std::string>>() {}
	~DictWord() {}

	// load from file
	void load(std::string const& src_file) {
		std::fstream fin(src_file, std::ios::in);
		constexpr size_t N = 256;
		char tmp[N];
		while (fin.getline(tmp, N)) {
			auto x = string::split(std::string(tmp), " ");
			this->insert(string::to_vec(x[0]));
		}
	}
};

} // namespace wordseg

#endif// WORDSEG_DICT_HH


