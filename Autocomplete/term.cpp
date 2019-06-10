#include "term.hpp"

term::term(const std::string& new_data, const int new_weight) : _data(new_data),_weight(new_weight) { }

std::string term::to_string() {
	return std::to_string(_weight) + ' ' + _data;
}

std::ostream& operator<<(std::ostream& out, const term& term) {
	out << term._weight << ' ' << term._data;
	return out;
}

bool operator<(const term& first, const term& second) {
	for (size_t i = 0; i < std::min(first._data.length(), second._data.length()); i++) {
		if (first._data[i] != second._data[i]) {
			return first._data[i] < second._data[i];
		}
	}
	if (first._data.length() != second._data.length()) {
		return first._data.length() < second._data.length();
	}
	return first._weight < second._weight;
}

bool operator==(const term& first, const term& second) {
	if (first._weight != second._weight || first._data.length() != second._data.length()) {
		return false;
	}
	bool is_equal = true;
	for (size_t i = 0; i < first._data.length(); i++) {
		if (first._data[i] != second._data[i]) {
			is_equal = false;
		}
	}
	return is_equal;
}

bool operator>(const term& first, const term& second) {
	return !(first <= second);
}

bool operator>=(const term& first, const term& second) {
	return second == first || first > second;
}

bool operator<=(const term& first, const term& second) {
	return second == first || first < second;
}

bool operator!=(const term& first, const term& second) {
	return !(first == second);
}


