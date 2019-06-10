#ifndef _RANDOMIZED_QUEUE_
#define _RANDOMIZED_QUEUE_
#include <vector>
#include <random>
#include <algorithm>
#include <cassert>

template<class T, size_t N = 10>
class randomized_queue {
public:
	template<class P>
	class queue_iterator : public std::iterator<std::bidirectional_iterator_tag, P> {
	private:
		randomized_queue<T, N>* _container;
		std::vector<size_t> _permutation;
		size_t _pos;	

		void new_perm(size_t);
	public:	
		queue_iterator() = default;
		queue_iterator(randomized_queue<T, N>*, size_t);

		P& operator*() const;
		bool operator==(const queue_iterator&) const;
		bool operator!=(const queue_iterator&) const;
		queue_iterator& operator++();
		queue_iterator operator++(int);
		queue_iterator& operator--();
		queue_iterator operator--(int);
	};

	typedef queue_iterator<T> iterator;
	typedef queue_iterator<const T> const_iterator;
	
	
	randomized_queue();
	bool empty();
	size_t size();
	void enqueue(const T&);
	T& sample();
	T dequeue();

	iterator begin();
	iterator end();
	const_iterator cbegin();
	const_iterator cend();
private:
	size_t _current_size;
	size_t MAX_SIZE;
	std::vector<T> _queue;
	size_t _head;
	size_t _tail;

	std::random_device rd;
	std::mt19937 mt;
	void ensure();
	size_t find_random();
};

template<class T, size_t N>
randomized_queue<T, N>::randomized_queue() : _current_size(0), _queue(N), _head(0), _tail(0), MAX_SIZE(N), mt(rd()) {}

template<class T, size_t N>
bool randomized_queue<T, N>::empty() {
	return _head == _tail;
}

template<class T, size_t N>
size_t randomized_queue<T, N>::size() {
	return _current_size;
}

template<class T, size_t N>
void randomized_queue<T, N>::ensure() {
	std::vector<T> new_queue(2 * MAX_SIZE);
	size_t pos = 0;
	for (size_t i = _head; i < MAX_SIZE; i++) {
		new_queue[pos] = _queue[i];
		pos++;
	}
	for (size_t i = 0; i < _tail; i++) {
		new_queue[pos] = _queue[i];
	}
	_queue = new_queue;
	MAX_SIZE *= 2;
	_head = 0;
	_tail = _current_size;
}

template<class T, size_t N>
void randomized_queue<T, N>::enqueue(const T& element) {
	if (_tail == _head && _current_size == MAX_SIZE) {
		ensure();
	}
	_queue[_tail] = element;
	_tail = (_tail + 1) % MAX_SIZE;
	_current_size++;
	
}

template<class T, size_t N>
size_t randomized_queue<T, N>::find_random() {
	assert(_current_size > 0);
	std::uniform_int_distribution<int> range(0, _current_size - 1);
	return (_head + range(mt)) % MAX_SIZE;
}

template<class T, size_t N>
template<class P>
void randomized_queue<T, N>::queue_iterator<P>::new_perm(size_t size) {
	for (size_t i = 0; i < size; i++) {
		_permutation.push_back(i);
	}
	std::shuffle(_permutation.begin(), _permutation.end(), _container->mt);
}

template<class T, size_t N>
T& randomized_queue<T, N>::sample() {
	return _queue[find_random()];
}

template<class T, size_t N>
T randomized_queue<T, N>::dequeue() {	
	size_t index = find_random();
	std::swap(_queue[index], _queue[_head]);
	T result = _queue[_head];
	_head = (_head + 1) % MAX_SIZE;
	_current_size--;
	return result;
}

template<class T, size_t N>
template<class P>
randomized_queue<T, N>::queue_iterator<P>::queue_iterator(randomized_queue<T, N>* container, size_t index) : _pos(index) {
	_container = container;
	new_perm(_container->size());
}

template<class T, size_t N>
template<class P>
P& randomized_queue<T, N>::queue_iterator<P>::operator*() const {
	assert(_pos < _permutation.size());
	return _container->_queue[(_container->_head + _permutation[_pos]) % _container->MAX_SIZE];
}

template<class T, size_t N>
template<class P>
bool randomized_queue<T, N>::queue_iterator<P>::operator==(const queue_iterator& other) const {
	return (_container == other._container) && (_pos == other._pos);
}

template<class T, size_t N>
template<class P>
bool randomized_queue<T, N>::queue_iterator<P>::operator!=(const queue_iterator& other) const {
	return !(*this == other);
}

template<class T, size_t N>
template<class P>
randomized_queue<T, N>::queue_iterator<P> randomized_queue<T, N>::queue_iterator<P>::operator++(int) {
	queue_iterator<P> old = *this;
	if (_pos < _container->size()) {
		_pos++; 
	}
	return old;
}

template<class T, size_t N>
template<class P>
randomized_queue<T, N>::queue_iterator<P>& randomized_queue<T, N>::queue_iterator<P>::operator++() {
	if (_pos < _container->size()) {
		_pos++; 
	}
	return *this;
}

template<class T, size_t N>
template<class P>
randomized_queue<T, N>::queue_iterator<P> randomized_queue<T, N>::queue_iterator<P>::operator--(int) {
	queue_iterator<P> old = *this;
	_pos--;
	return old;
}

template<class T, size_t N>
template<class P>
randomized_queue<T, N>::queue_iterator<P>& randomized_queue<T, N>::queue_iterator<P>::operator--() {
	_pos--;
	return *this;
}

template<class T, size_t N>
typename randomized_queue<T, N>::iterator randomized_queue<T, N>::begin() {
	return iterator(this, 0);
}

template<class T, size_t N>
typename randomized_queue<T, N>::iterator randomized_queue<T, N>::end() {
	return iterator(this, _current_size);
}

template<class T, size_t N>
typename randomized_queue<T, N>::const_iterator randomized_queue<T, N>::cbegin() {
	return const_iterator(this, 0);
}

template<class T, size_t N>
typename randomized_queue<T, N>::const_iterator randomized_queue<T, N>::cend() {
	return const_iterator(this, _current_size);
}

#endif _RANDOMIZED_QUEUE_
