#ifndef _DEQUE_
#define _DEQUE_
#include <list>

template<class T>
class deque {
public:
	deque() = default;
	bool empty();
	size_t size();
	void push_back(const T&);
	void push_front(const T&);
	T& front();
	T& back();
	void pop_back();
	void pop_front();

	typedef std::list<T>::iterator iterator;
	typedef std::list<T>::const_iterator const_iterator;

	iterator begin();
	const_iterator cbegin();
	iterator end();
	const_iterator cend();
private:
	std::list<T> _deque;
};

template<class T>
bool deque<T>::empty() {
	return _deque.empty();
}

template<class T>
size_t deque<T>::size() {
	return _deque.size();
}

template<class T>
void deque<T>::push_back(const T& element) {
	_deque.push_back(element);
}

template<class T>
void deque<T>::push_front(const T& element) {
	_deque.push_back(element);
}

template<class T>
T& deque<T>::back() {
	return _deque.back();
}

template<class T>
T& deque<T>::front() {
	return _deque.front();
}

template<class T>
void deque<T>::pop_back() {
	_deque.pop_back();
}

template<class T>
void deque<T>::pop_front() {
	_deque.pop_front();
}

template<class T>
deque<T>::iterator deque<T>::begin() {
	return _deque.begin();
}

template<class T>
deque<T>::iterator deque<T>::end() {
	return _deque.end();
}

template<class T>
deque<T>::const_iterator deque<T>::cbegin() {
	return _deque.cbegin();
}

template<class T>
deque<T>::const_iterator deque<T>::cend() {
	return _deque.cend();
}

#endif _DEQUE_
