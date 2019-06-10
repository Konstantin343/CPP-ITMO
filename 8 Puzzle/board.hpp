#ifndef _BOARD_
#define _BOARD_
#include <vector>
#include <ostream>
#include <string>

class board {
private:
	std::vector<std::vector<int>> _board;
	int _hamming;
	int _manhattan;
	bool _is_goal;
	bool _is_solvable;
	std::string _string_form;
	size_t _empty_i;
	size_t _empty_j;
	size_t _hash;
public:
	board();
	board(const std::vector<std::vector<int>>&);
	board(const size_t);
	board(const board&) = default;
	board& operator=(const board&) = default;

	size_t size() const;
	size_t empty_i() const;
	size_t empty_j() const;
	size_t get_hash() const;
	int hamming() const;
	int manhattan() const;
	bool is_goal() const;
	bool is_solvable() const;

	friend bool operator==(const board&, const board&);
	friend bool operator!=(const board&, const board&);

	std::string to_string() const;
	std::vector<int> operator[](size_t) const;
	friend std::ostream& operator<<(std::ostream&, const board&);
};

#endif _BOARD_
