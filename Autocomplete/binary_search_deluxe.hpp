#ifndef _BINARY_SEARCH_DELUXE_
#define _BINARY_SEARCH_DELUXE_
#include "term.hpp"
#include <functional>
#include <vector>

class binary_search_deluxe {
private:
	binary_search_deluxe() {};
	~binary_search_deluxe() {};
	binary_search_deluxe(const binary_search_deluxe&) = delete;
	binary_search_deluxe& operator=(const binary_search_deluxe&) = delete;
public:
	static int first_index_of(const std::vector<term>&, const term&, term::Comp);
	static int last_index_of(const std::vector<term>&, const term&, term::Comp);
};

#endif _BINARY_SEARCH_DELUXE_
