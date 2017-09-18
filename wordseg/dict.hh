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

template<class T>
class DictWord : public detail::NaiveTrie<T> {
private:
	std::unordered_set<T> _words;

public:
	// constructor & destructor
	DictWord() : detail::NaiveTrie<T>(), _words() {}
	~DictWord() {}

public:
	// read from file
	void read(std::string const& file_name) {
		std::fstream fin(file_name, std::ios::in);
		constexpr size_t N = 256;
		char tmp[N];
		while (fin.getline(tmp, N)) {
			auto x = split(std::string(tmp));
			this->insert(make_string<wordseg::string>(x[0]));
		}
	}
};

} // namespace wordseg

#endif// WORDSEG_DICT_HH


