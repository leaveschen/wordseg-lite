//
// Created by c on 19/11/2017 02:44 PM
//

/* include section */

#include <iostream>
#include <string>
#include <vector>
#include "wordseg/trie.hh"
#include "wordseg/string.hh"
#include "wordseg/dict.hh"

using std::cout;
using std::endl;

/* class & function section */

void test_trie() {
	wordseg::detail::NaiveTrie<std::vector<std::string>> tr;
	std::vector<std::string> v1 = {"h", "e", "h", "e"};
	std::vector<std::string> v2 = {"h", "e", "h", "x", "a", "b"};
	std::vector<std::string> v3 = {"h", "e", "h", "e", "x"};
	tr.insert(v1);
	tr.insert(v2);
	tr.insert(v3);

	std::vector<std::string> v = {"h", "e", "h", "e", "x", "h"};
	for (auto& x : tr.search_all(v.begin(), v.end())) {
		cout << x << endl;
	}
}

void test_string() {
	std::string s1 = "毛病养成\t习惯\n";
	auto s2 = wordseg::string::strip(s1);
	cout << s2 << endl;
	auto v2 = wordseg::string::split(s2, "\t");
	for (auto& x : v2) cout << x << endl;
	auto v3 = wordseg::string::to_vec(v2[0]);
	for (auto& x : v3) cout << x << endl;
}

void test_dict() {
	wordseg::DictWord dw;
	dw.load("./words.dict");
	std::vector<std::string> v1 = {"h", "e", "h", "e"};
	auto v2 = wordseg::string::to_vec("习惯");
	cout << dw.has(v1) << endl;
	cout << dw.has(v2) << endl;
}

int main() {
	test_dict();
	return 0;
}


