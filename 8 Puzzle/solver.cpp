#include "solver.hpp"
#include <iostream>
#include <queue>
#include <unordered_set>
#include <set>
#include <functional>

solver::solver(const board& board) {
	if (board.is_solvable()) {
		solve(board);
	}
}

void solver::add_next(std::vector<board>& states, std::vector<std::vector<int>>& next, size_t empty_i, size_t empty_j, size_t i, size_t j) {
	std::swap(next[empty_i][empty_j], next[i][j]);
	states.push_back(board(next));
	std::swap(next[empty_i][empty_j], next[i][j]);
}

void solver::possible_next(std::vector<board>& states, const board& current) {
	size_t empty_i = current.empty_i();
	size_t empty_j = current.empty_j();
	std::vector<std::vector<int>> next(current.size());
	for (size_t i = 0; i < current.size(); i++) {
		next[i].resize(current.size());
	}
	for (size_t i = 0; i < current.size(); i++) {
		for (size_t j = 0; j < current.size(); j++) {
			next[i][j] = current[i][j];
		}
	}
	if (empty_i) {
		add_next(states, next, empty_i, empty_j, empty_i - 1, empty_j);
	}
	if (empty_j) {
		add_next(states, next, empty_i, empty_j, empty_i, empty_j - 1);
	}
	if (empty_i < current.size() - 1) {
		add_next(states, next, empty_i, empty_j, empty_i + 1, empty_j);
	}
	if (empty_j < current.size() - 1) {
		add_next(states, next, empty_i, empty_j, empty_i, empty_j + 1);
	}
}

void solver::solve(const board& first) {
	auto cmp = [](const std::vector<board>& f, const std::vector<board>& s) {
		return f.back().manhattan() + f.size() > s.back().manhattan() + s.size();
	};
	auto cmp_board = [](const board& f, const board& s) {
		for (size_t i = 0; i < f.size(); i++) {
			for (size_t j = 0; j < f.size(); j++) {
				if (f[i][j] != s[i][j]) {
					return f[i][j] < s[i][j];
				}
			}
		}
		return false;
	};
	auto hasher = [](const board& f) {
		return f.get_hash();
	};

	std::priority_queue<std::vector<board>, std::vector<std::vector<board>>, decltype(cmp)> queue(cmp);
	std::set<board, decltype(cmp_board)> used(cmp_board);
	//std::unordered_set<board, decltype(hasher)> used(8, hasher);    
	
	used.insert(first);
	std::vector<board> current = { first };
	while (!current.back().is_goal()) {
		std::vector<board> possible;
		std::cout << current.size() << std::endl	;
		possible_next(possible, current.back());
		for (size_t i = 0; i < possible.size(); i++) {		
			if (!used.count(possible[i])) {
				current.push_back(possible[i]);
				queue.push(current);
				current.pop_back();
				used.insert(possible[i]);
			}		
		}
		current = queue.top();
		queue.pop();
	}
	_steps = current;
}

void solver::moves() {
	std::cout << _steps.size();
}

solver::iterator solver::begin() {
	return _steps.begin();
}

solver::iterator solver::end() {
	return _steps.end();
}