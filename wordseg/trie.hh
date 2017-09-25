//
// Created by c on 05/09/2017 11:05 PM
//

#ifndef WORDSEG_TRIE_HH
#define WORDSEG_TRIE_HH

/* include section */

#include <vector>
#include <unordered_map>
#include <iterator>
#include <memory>
#include <utility>
#include <functional>

/* class & function section */

namespace wordseg {
namespace detail {

template<class T>
class NaiveTrie {
public:
	// type define
	using bit_type = typename T::value_type;
	using ptr_type = std::shared_ptr<NaiveTrie<T>>;

protected:
	// members
	T _key;
	bool _is_leaf;
	std::unordered_map<bit_type, ptr_type> _branches;
	size_t _size;

public:
	// constructor & destructor
	NaiveTrie() : _key(), _is_leaf(false), _branches() , _size(0) {}
	~NaiveTrie() {}

	// interface
	void insert(T const& key) {
		auto* node = this;
		for (auto& bit : key) {
			auto it = node->_branches.find(bit);
			if (it == node->_branches.end()) {
				node->_branches[bit] = std::make_shared<NaiveTrie<T>>();
			}
			node = node->_branches[bit].get();
		}
		node->_is_leaf = true;
		node->_key = key;
		++_size;
	}

	size_t size() { return _size; }

	bool is_head(bit_type const& bit) { return !(this->_branches.find(bit) == this->_branches.end()); }

	template<class Iterator>
	bool is_head(Iterator it) { return !(this->_branches.find(*it) == this->_branches.end()); }

protected:
	template<class Iterator, class FnBreak, class FnFinal>
	decltype(auto) _search_impl(Iterator first, Iterator last,
			FnBreak fn_break, FnFinal fn_final) {
		auto* node = this;
		auto curr = first;
		for (auto it = first; it < last; ++it) {
			if (node->_is_leaf) { curr = it; }
			auto itx = node->_branches.find(*it);
			if (itx == node->_branches.end()) {
				return fn_break(node, curr);
			}
			node = node->_branches[*it].get();
		}
		if (node->_is_leaf) { curr = last; }
		return fn_final(node, curr);
	}

public:
	bool has(T const& key) {
		return _search_impl(key.begin(), key.end(),
				[](auto node, auto)->bool { return false; },
				[](auto node, auto)->bool { return node->_is_leaf; });
	}

	template<class Iterator>
	bool has(Iterator first, Iterator last) {
		return _search_impl(first, last,
				[](auto node, auto) { return false; },
				[](auto node, auto) { return node->_is_leaf; });
	}

public:
	T longest_match(T const& key) {
		auto last_it = _search_impl(key.begin(), key.end(),
				[](auto, auto curr) { return curr; },
				[](auto, auto curr) { return curr; });
		return T(key.begin(), last_it);
	}

	template<class Iterator>
	T longest_match(Iterator first, Iterator last) {
		auto last_it = _search_impl(first, last,
				[](auto, auto curr) { return curr; },
				[](auto, auto curr) { return curr; });
		return T(first, last_it);
	}

	template<class Iterator>
	Iterator longest_match_it(Iterator first, Iterator last) {
		return _search_impl(first, last,
				[](auto, auto curr) { return curr; },
				[](auto, auto curr) { return curr; });
	}
};

template<class T>
class DoubleArrayTrie {
public:
	// type define
	using Container = std::vector<T>;
	using bit_type = typename T::value_type;

protected:
	// base & check array
	std::vector<int64_t> _base;
	std::vector<int64_t> _check;

public:
	// constructor & destructor
	DoubleArrayTrie() : _base(), _check() {}
	~DoubleArrayTrie() {}

protected:
	// build impl
	template<class Iterator>
	void _build_impl(Iterator first, Iterator last) {
		// check type
	}

public:
	// build interface
	void build(std::vector<T> const& input) { _build_impl(input.begin(), input.end()); }

	template<class Iterator>
	void build(Iterator first, Iterator last) { _build_impl(first, last); }
};

} // namespace detail
} // namespace wordseg

#endif// WORDSEG_TRIE_HH


