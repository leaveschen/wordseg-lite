//
// Created by c on 19/11/2017 03:09 PM
//

#ifndef WORDSEG_STRING_HH
#define WORDSEG_STRING_HH

/* include section */

#include <string>
#include <vector>
#include <set>

/* class & function section */

namespace wordseg {

// some string handle methods
class string {
public:
	// type define
	using StrT = std::string;
	using CharT = typename std::string::value_type;

	// strip
	static StrT strip(StrT const& raw, StrT const& str = " \t\n") {
		std::set<CharT> cs(str.begin(), str.end());
		StrT ret;
		bool flag = false;
		bool flagr = false;
		for (auto it = raw.begin(), itr = it+raw.size()-1; it <= itr; ) {
			if (flag and flagr) { ret.insert(ret.begin(), it, itr+1); break; }
			if (!flag) { if (cs.count(*it) == 0) flag = true; else ++it; }
			if (!flagr) { if (cs.count(*itr) == 0) flagr = true; else --itr; }
		}
		return ret;
	}

	// split
	static std::vector<StrT> split(StrT const& raw, StrT const& str) {
		std::vector<StrT> ret;
		size_t pfirst = 0;
		size_t plast = 0;
		while (plast < raw.size()) {
			plast = raw.find_first_of(str, pfirst);
			if (plast == StrT::npos) {
				if (raw.size() > pfirst) ret.push_back(raw.substr(pfirst, raw.size()-pfirst));
				break;
			} else {
				if (plast > pfirst) ret.push_back(raw.substr(pfirst, plast-pfirst));
				pfirst = plast + 1;
			}
		}
		return ret;
	}

	// to vector(for chinese utf8 encoded string)
	static std::vector<StrT> to_vec(StrT const& str) {
		std::vector<StrT> ret;
		size_t nbyte = 0;
		for (size_t i = 0; i < str.size(); ) {
			if ((str[i] & 0xfc) == 0xfc) {
				nbyte = 6;
			} else if ((str[i] & 0xf8) == 0xf8) {
				nbyte = 5;
			} else if ((str[i] & 0xf0) == 0xf0) {
				nbyte = 4;
			} else if ((str[i] & 0xe0) == 0xe0) {
				nbyte = 3;
			} else if ((str[i] & 0xc0) == 0xc0) {
				nbyte = 2;
			} else {
				nbyte = 1;
			}
			ret.push_back(str.substr(i, nbyte));
			i += nbyte;
		}
		return ret;
	}
};

} // namespace wordseg

#endif// WORDSEG_STRING_HH


