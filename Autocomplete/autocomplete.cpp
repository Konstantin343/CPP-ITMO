#include "autocomplete.hpp"

autocomplete::autocomplete(const std::vector<term>& data) {
	_terms = data;
	std::stable_sort(_terms.begin(), _terms.end());
}

std::vector<term> autocomplete::all_matches(const std::string& prefix) {
	std::vector<term> result;
	int lower_bound = binary_search_deluxe::first_index_of(_terms, term(prefix, 0), term::by_prefix_order(prefix.length()));
	int upper_bound = binary_search_deluxe::last_index_of(_terms, term(prefix, 0), term::by_prefix_order(prefix.length()));
	
	for (int i = lower_bound; i <= upper_bound; i++) {
		result.push_back(_terms[i]);
	}
	std::stable_sort(result.begin(), result.end(), term::by_reverse_weight_order());
	return result;
}

int autocomplete::number_of_matches(const std::string& prefix) {
	int lower_bound = binary_search_deluxe::first_index_of(_terms, term(prefix, 0), term::by_prefix_order(prefix.length()));
	int upper_bound = binary_search_deluxe::last_index_of(_terms, term(prefix, 0), term::by_prefix_order(prefix.length()));

	return upper_bound - lower_bound + 1;
}