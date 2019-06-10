#ifndef _AUTOCOMPLETE_
#define _AUTOCOMPLETE_
#include "term.hpp"
#include "binary_search_deluxe.hpp"

class autocomplete {
private:
	std::vector<term> _terms;
public:
	autocomplete(const std::vector<term>&);
	std::vector<term> all_matches(const std::string&);
	int number_of_matches(const std::string&);
};

#endif _AUTOCOMPLETE_
