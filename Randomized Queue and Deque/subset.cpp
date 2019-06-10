#include "randomized_queue.hpp"
#include <string>
#include <iostream>

randomized_queue<std::string> queue;

void read() {
	std::string current;
	while (std::getline(std::cin, current)) {
		queue.enqueue(current);
	}
}

void write(size_t cnt) {
	randomized_queue<std::string>::iterator it = queue.begin();
	for (size_t i = 0; i < cnt; i++) {
		std::cout << *it << '\n';
		++it;
	}
}

int main(int argc, char ** argv) {
	read();
	const size_t cnt = (argc > 1 ? std::atoi(argv[1]) : queue.size());
	write(cnt);
	return 0;
}