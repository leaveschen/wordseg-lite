//
// Created by c on 08/09/2017 01:28 PM
//

#ifndef WORDSEG_SEGMENTOR_HH
#define WORDSEG_SEGMENTOR_HH

/* include section */

#include <memory>
#include <set>
#include "wordseg/utility.hh"
#include "wordseg/dict.hh"

/* class & function section */

#define MAX_MATCH_SIZE 5

namespace wordseg {
namespace detail {

template<class T>
class CutBySeperator {
public:
	using char_type = typename T::value_type;

private:
	std::set<char_type> _seperators;

public:
	// constructor & destructor
	CutBySeperator() : _seperators() {
		auto tmp = make_string<T>(" \t\n\xEF\xBC\x8C\xE3\x80\x82,.");
		_seperators.insert(tmp.begin(), tmp.end());
	}
	~CutBySeperator() {}

	// interface
	void cut(T const& raw, std::vector<T>& result) {
		result.clear();
		size_t i = 0; size_t n = 0;
		while (i < raw.size()) {
			if (_seperators.count(raw[i])) {
				T s = raw.substr(n, i-n);
				if (i-n > 0) { result.push_back(raw.substr(n, i-n)); }
				n = i+1;
			}
			++i;
		}
		// push last part
		if (i-n > 0) { result.push_back(raw.substr(n, i-n)); }
	}
};

template<class T>
class CutByMaxMatch {
private:
	// type define
	using dict_type = DictWord<T>;

	// members
	std::shared_ptr<dict_type> _p_dict;

public:
	// constructor & destructor
	CutByMaxMatch() : _p_dict(std::make_shared<dict_type>()) {}
	~CutByMaxMatch() {}

	// initial
	void initial(std::string const& dict_path) { _p_dict->read(dict_path); }

	// interface
	void cut(T const& raw, std::vector<T>& result) {
		result.clear();
		auto it_begin = raw.begin();
		auto it_end = raw.end();
		auto it = it_end;
		while (true) {
			it = _p_dict->longest_match_it(it_begin, std::min(it_begin + MAX_MATCH_SIZE, it_end));
			result.emplace_back(T(it_begin, it));
			if (it == it_end) { break; } else { it_begin = it; }
		}
	}
};

template<class T>
class CutByComplexMatch {
private:
	// type define
	using dict_type = DictWord<T>;

	// members
	std::shared_ptr<dict_type> _p_dict;

public:
	// constructor & destructor
	CutByComplexMatch() : _p_dict(std::make_shared<dict_type>()) {}
	~CutByComplexMatch() {}

	// initial
	void initial(std::string const& dict_path) { _p_dict->read(dict_path); }

	// interface
	void cut(T const& raw, std::vector<T>& result) {}
};

} // namespace detail
} // namespace wordseg

#endif// WORDSEG_SEGMENTOR_HH


