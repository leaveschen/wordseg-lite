//
// Created by c on 19/08/2017 01:57 PM
//

#ifndef WORDSEG_STRING_HH
#define WORDSEG_STRING_HH

/* include section */

#include <string>
#include <vector>
#include <set>
#include <algorithm>

/* class & function section */

namespace wordseg {

namespace detail {

// code convert container, singleton
template<class CharT>
class cvt_container {
public:
	using value_type = CharT;
	using facet_t = std::codecvt<value_type, char, std::mbstate_t>;

private:
	// utility wrapper to adapt locale-bound facets for wstring/wbuffer convert
	template<class Facet>
	struct deletable_facet : Facet {
		template<class ...Args>
		deletable_facet(Args&& ...args) : Facet(std::forward<Args>(args)...) {}
		~deletable_facet() {}
	};

public:
	// facet
	using cvt_t = std::wstring_convert<deletable_facet<facet_t>, value_type>;
	cvt_t _cvt;

private:
	// constructor
	cvt_container() {}

public:
	inline static cvt_t* cvt() {
		static cvt_container inst;
		return &inst._cvt;
	}
};

// various converter
// convert from char to CharT
template<class CharT>
inline std::basic_string<CharT> from_bytes(std::string const& str) {
	return detail::cvt_container<CharT>::cvt()->from_bytes(str);
}

// convert from CharT to char
template<class CharT>
inline std::basic_string<char> to_bytes(std::basic_string<CharT> const& str) {
	return detail::cvt_container<CharT>::cvt()->to_bytes(str);
}

} // namespace detail

using char_t = char16_t;
using string = std::basic_string<char_t>;

// make string function
template<class StrT>
StrT make_string(std::string const& str) {
	return detail::from_bytes<typename StrT::value_type>(str);
}
template<>
std::string make_string<std::string>(std::string const& str) { return str; }

// for convenient
string make_string_chs(std::string const& str) { return std::move(make_string<string>(str)); }

// string methods
template<class StrT>
decltype(auto) strip(StrT&& raw, std::string const& str = " \t\n") {
	using CharT = typename StrT::value_type;
	auto cc = make_string<StrT>(str);
	std::set<CharT> cs(cc.begin(), cc.end());
	std::basic_string<CharT> ret;
	bool flag = false, flagr = false;
	for (auto it = raw.begin(), itr = raw.end()-1; it <= itr; ) {
		if (flag and flagr) { ret.insert(ret.begin(), it, itr+1); break; }
		if (!flag) { if (cs.count(*it) == 0) flag = true; else ++it; }
		if (!flagr) { if (cs.count(*itr) == 0) flagr = true; else --itr; }
	}
	return std::forward<StrT>(ret);
}

template<class StrT>
std::vector<StrT> split(StrT&& raw, std::string const& str = " \t\n") {
	using CharT = typename StrT::value_type;
	auto cc = make_string<StrT>(str);
	std::vector<StrT> ret;
	typename StrT::size_type pfirst = 0;
	typename StrT::size_type plast = 0;
	while (plast < raw.size()) {
		plast = raw.find_first_of(cc, pfirst);
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

} // namespace wordseg

// various string type stream output
inline std::ostream& operator<<(std::ostream& os, wordseg::char_t const& str) {
	wordseg::string ss;
	ss.push_back(str);
	return os << wordseg::detail::to_bytes(ss);
}

inline std::ostream& operator<<(std::ostream& os, wordseg::string const& str) {
	return os << wordseg::detail::to_bytes(str);
}

#endif// WORDSEG_STRING_HH


