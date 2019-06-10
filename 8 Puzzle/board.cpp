#include "board.hpp"
#include <algorithm>
#include <random>

board::board() : _hamming(0), _manhattan(0), _hash(0), _is_goal(false), _is_solvable(false) {}

board::board(const std::vector<std::vector<int>>& data) : board() {
	_board = data;
	int inversions = 0;
	for (size_t i = 0; i < size(); i++) {
		for (size_t j = 0; j < size(); j++) {
			_hash += (_board[i][j] << (i + j + 1)) * (i + j + 1);
			if (_board[i][j] == 0) {
				_empty_i = i;
				_empty_j = j;
				continue;
			}
			if (_board[i][j] != i * size() + j + 1) {
				_hamming++;
				_manhattan += (abs((int)(i - (_board[i][j] - 1) / size())) + abs((int)(j - (_board[i][j] - 1) % size())));
			}
			for (size_t k = i; k < size(); k++) {
				for (size_t l = (k == i ? j + 1 : 0); l < size(); l++) {
					if (_board[k][l] && _board[k][l] < _board[i][j]) {
						inversions++;
					}
				}
			}
			_string_form += std::to_string(_board[i][j]) + " ";
		}
		_string_form += '\n';
	}
	_is_solvable = !((inversions + _empty_i + 1 + size()) % 2);
	_is_goal = (_hamming == 0);
}

board::board(size_t n) {
	std::vector<std::vector<int>> data;
	std::vector<int> permutation;
	for (int i = 0; i < n * n; i++) {
		permutation.push_back(i);
	}
	std::random_device rd;
	std::mt19937 mt(rd());
	std::shuffle(permutation.begin(), permutation.end(), mt);

	for (size_t i = 0; i < n; i++) {
		std::vector<int> current;
		for (size_t j = 0; j < n; j++) {
			current.push_back(permutation[i * n + j]);
		}
		data.push_back(current);
	}
	*this = board(data);
}

size_t board::size() const {
	return _board.size();
}

size_t board::empty_i() const {
	return _empty_i;
}

size_t board::empty_j() const {
	return _empty_j;
}

size_t board::get_hash() const {
	return _hash;
}

int board::hamming() const {
	return _hamming;
}

int board::manhattan() const {
	return _manhattan;
}

bool board::is_goal() const {
	return _is_goal;
}

bool board::is_solvable() const {
	return _is_solvable;
}

bool operator==(const board& first, const board& second) {
	if (first.size() != second.size()) {
		return false;
	}
	for (size_t i = 0; i < first.size(); i++) {
		for (size_t j = 0; j < first.size(); j++) {
			if (first[i][j] != second[i][j]) {
				return false;
			}
		}
	}
	return true;
}

bool operator!=(const board& first, const board& second) {
	return !(first == second);
}

std::string board::to_string() const {
	return _string_form;
}

std::vector<int> board::operator[](size_t index) const {
	return _board[index];
}

std::ostream& operator<<(std::ostream& out , const board& board) {
	for (size_t i = 0; i < board.size(); i++) {
		for (size_t j = 0; j < board.size(); j++) {
			out << board[i][j] << ' ';
		}
		out << '\n';
	}
	return out;
}