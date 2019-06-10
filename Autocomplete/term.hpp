#ifndef _TERM_
#define _TERM_
#include <string>
#include <ostream>
#include <algorithm>
#include <functional>

class term {
private:
	std::string _data;
	int _weight;
public:
	typedef std::function<bool(const term&, const term&)> Comp;

	term(const std::string&, const int);
	term(const term&) = default;
	term(term&&) = default;
	~term() = default;
	term& operator=(const term&) = default;
	term& operator=(term&&) = default;

	std::string to_string();
	friend std::ostream& operator<<(std::ostream&, const term&);

	friend bool operator>(const term&, const term&);
	friend bool operator<(const term&, const term&);
	friend bool operator>=(const term&, const term&);
	friend bool operator<=(const term&, const term&);
	friend bool operator==(const term&, const term&);
	friend bool operator!=(const term&, const term&);
	static auto by_reverse_weight_order();
	static auto by_prefix_order(int r);
};

auto term::by_reverse_weight_order() {
	return [](const term& t1, const term& t2) {
		if (t1._weight != t2._weight) {
			return t1._weight > t2._weight;
		}
		return t1 < t2;
	};
}

auto term::by_prefix_order(int r) {	
	return [r](const term& t1, const term& t2) {
		size_t pr = r;
		pr = std::min(pr, t1._data.length());
		pr = std::min(pr, t2._data.length());
		for (size_t i = 0; i < pr; i++) {
			if (t1._data[i] != t2._data[i]) {
				return t1._data[i] < t2._data[i];
			}
		}
		return false;
	};
}

#endif _TERM_
