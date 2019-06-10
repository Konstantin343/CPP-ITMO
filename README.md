# CPP-ITMO
*Some homeworks from CPP courses in ITMO.*

### 1. 8 Puzzles
A program that solves the puzzle 8 Puzzle (and its generalizations) using the A* algorithm.

* Class `board` is an immutable board that stores a state, and has methods that allow you to get information about that state.
Methods:
`is_goal`, `is_solvable`, `manhattan`, `hamming`, `size`, `operator[]`

* Class `solver` is an interface to get the chains of boards that lead to the solution. 
Methods:
`moves`, `solver::iterator`
### 2. Autocomplete
The implementation of auto-completion for N strings and positive weights.
At the output of the program you need to give all the lines that begin with a given prefix in descending order of weights.

* Class `term` stores string and weight.
Methods:
`to_string`, 'by_reverse_weight_order`, `by_prefix_order`, `operator==`, 'operator>`, `operator<` and others.

* Class `binary_search_deluxe` is binary search for term's array, that used any comparators.
Methods:
`first_index_of`, `last_index_of`

* Class `autocomplete` use two previous classes and give you information about words, that starts with given prefix.
Methods:
`all_matches`, `number_of_matches`
### 3. Randomized queue and deque
Implementation of randomized queue and deck with iterators using templates. 
Subset utility, which returns a random K of the N rows with a uniform distribution.

* Class `deque` is standard template implementation using `std::list<T>`
Methods:
`empty`, `size`, `push_back`, `pop_back`, `push_front`, `pop_front`, `begin`, `end`, `cbegin`, `cend`

* Class `randomized_queue` is implementation of queue, that add elements in the end, but remove from random place of container.
Methods:
`empty`, `size`, `enqueue`, `sample`, `dequeue`, `begin`, `end`, `cbegin`, `cend`

* Utility `subset` get *K* and strings and make uniform distribution using `randomized_queue`
