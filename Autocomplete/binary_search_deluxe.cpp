#include "binary_search_deluxe.hpp"

int binary_search_deluxe::first_index_of(const std::vector<term>& arr, const term& key, term::Comp comparator) {
	int left = -1;
	int right = arr.size();
	while (right - left > 1) {
		int med = (left + right) / 2;
		if (comparator(arr[med], key)) {
			left = med;
		} else {
			right = med;
		}
	}
	return right;
}

int binary_search_deluxe::last_index_of(const std::vector<term>& arr, const term& key, term::Comp comparator) {
	int left = -1;
	int right = arr.size();
	while (right - left > 1) {
		int med = (left + right) / 2;		
		if (!comparator(key, arr[med])) {
			left = med;
		} else {
			right = med;
		}
	}
	return left;
}