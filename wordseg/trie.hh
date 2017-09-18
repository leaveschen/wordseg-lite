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

	bool has(T const& key) {
		auto* node = this;
		for (auto& bit : key) {
			auto it = node->_branches.find(bit);
			if (it == node->_branches.end()) {
				return false;
			}
			node = node->_branches[bit].get();
		}
		return node->_is_leaf;
	}

protected:
	template<class Iterator>
	T _longest_match_impl(Iterator first, Iterator last) {
		auto* node = this;
		for (auto it = first; it < last; ++it) {
			auto itx = node->_branches.find(*it);
			if (itx == node->_branches.end()) {
				return node->_key;
			}
			node = node->_branches[*it].get();
		}
		if (node->_is_leaf) { return node->_key; } else { return T(); }
	}

	template<class Iterator>
	Iterator _longest_match_impl_2(Iterator first, Iterator last) {
		auto* node = this;
		for (auto it = first; it < last; ++it) {
			auto itx = node->_branches.find(*it);
			if (itx == node->_branches.end()) {
				return it;
			}
			node = node->_branches[*it].get();
		}
		if (node->_is_leaf) { return last; } else { return first; }
	}

public:
	T longest_match(T const& key) {
		//return std::move(_longest_match_impl(key.begin(), key.end()));
		return T(key.begin(), _longest_match_impl_2(key.begin(), key.end()));
	}

	template<class Iterator>
	T longest_match(Iterator first, Iterator last) {
		//return std::move(_longest_match_impl(first, last));
		return T(first, _longest_match_impl_2(first, last));
	}

	template<class Iterator>
	Iterator longest_match_it(Iterator first, Iterator last) {
		return _longest_match_impl_2(first, last);
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


