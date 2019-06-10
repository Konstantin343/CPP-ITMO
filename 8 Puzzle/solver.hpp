#ifndef _SOLVER_
#define _SOLVER_
#include "board.hpp"
#include <iterator>

class solver {
private:
	std::vector<board> _steps;
	void add_next(std::vector<board>&, std::vector<std::vector<int>>&, size_t, size_t, size_t, size_t);
	void possible_next(std::vector<board>&, const board&);
	void solve(const board&);
public:
	solver() = default;
	solver(const board&);	
	solver(const solver&) = default;
	solver& operator=(const solver&) = default;

	typedef std::vector<board>::iterator iterator;

	iterator begin();
	iterator end();

	void moves();
};

#endif _SOLVER_
