#include <iostream>

using namespace std;

template <typename T>
struct Node {
	T data;
	Node<T>* prev;
	Node<T>* next;

	Node(const T& data) {
		this->data = data;
		this->prev = this->next = nullptr;
	};
};

template <typename T>
class DLinkedList {
	
	Node<T>* _head;
	Node<T>* _tail;
	int _size;

public:
	DLinkedList();
	DLinkedList(const DLinkedList<T>& other);
	DLinkedList(int count);
	~DLinkedList();

	DLinkedList<T> operator=(const DLinkedList<T>& other);
	T& operator[](int index);
	const T& operator[](int index) const;
	void clear();

	Node<T>* get_data(int index);
	bool insert(int index, T& data);
	bool remove(int index);

	Node<T>* push_tail(const T& value);
	Node<T>* push_head(const T& value);
	Node<T>* push_head(const DLinkedList<T>& other);
	Node<T>* push_tail(const DLinkedList<T>& other);

	void pop_head(Node<T>* head);
	void pop_tail(Node<T>* head);
	Node<T>* delete_node(T value);
};

template <typename T>
DLinkedList<T>::DLinkedList() {
	_head = _tail = nullptr;
	_size = 0;
}

template <typename T>
DLinkedList<T>::DLinkedList(const DLinkedList<T>& other) {
	_head = _tail = nullptr;
	_size = other._size;
	Node<T>* new_head = other._head;
	while (new_head) {
		push_tail(new_head->data);
		new_head = new_head->next;
	}
}

template <typename T>
DLinkedList<T>::DLinkedList(int count) {
	_head = _tail =nullptr;
	_size = count;
	for (int i = 0; i < _size; ++i) {
		T value = rand() % 10000;
		push_tail(value);
	}
}

template <typename T>
void DLinkedList<T>:: clear() {
	Node<T>* new_head = _head;
	while (new_head) {
		Node<T>* tmp = new_head;
		new_head = new_head->next;
		delete tmp;
	}
	_head = _tail = nullptr;
	_size = 0;
}

template <typename T>
DLinkedList<T>::~DLinkedList() {
	while (_head) {
		auto ptr = _head;
		_head = _head->next;
		delete ptr;
	}
	_head = _tail=nullptr;
	_size = 0;
}

template <typename T>
DLinkedList<T> DLinkedList<T>::operator=(const DLinkedList<T>& other) {
	if (this != &other)
	{
		clear();
		Node<T>* tmp = other._head;
		while (tmp) {
			push_tail(tmp->data);
			tmp = tmp->next;
		}
	} 
	_size = other._size;
	return *this;
}


template <typename T>
T& DLinkedList<T>::operator[](int index) {
	Node<T>* tmp = _head;
	while (tmp){
		for (int i = 0; i <= index; ++i) {
			tmp = tmp->next;
			if (i == index) {
				return tmp->data;
			}
		}
	}
}

template <typename T>
const T& DLinkedList<T>::operator[](int index) const {
	Node<T>* tmp = _head;
	while (tmp) {
		for (int i = 0; i <= index; ++i) {
			tmp = tmp->next;
			if (i == index) {
				return tmp->data;
			}
		}
	}
}

template <typename T>
Node<T>* DLinkedList<T>::get_data(int index) {
	Node<T>* tmp = _head;
	int n = 0;
	while (n != index) {
		if (tmp == nullptr)
		{
			return tmp;
		}
		else {
			tmp = tmp->next;
			n++;
		}
	}
	return tmp;
}

template <typename T>
bool DLinkedList<T>::insert(int index, T& data) {

}

template <typename T>
bool DLinkedList<T>::remove(int index) {

}

template <typename T>
Node<T>* DLinkedList<T>::push_tail(const T& value){
	Node<T>* tmp = new Node<T>(value);
	if (_tail != nullptr) {
		_tail->next = tmp;
		tmp->next = nullptr;
		tmp->prev = _tail;
	}
	if (_tail == nullptr) {
		_head == tmp;
	}
	++_size;
	return tmp;
}

template <typename T>
Node<T>* DLinkedList<T>::push_head(const T& value) {
	Node<T>* tmp = new Node<T>(value);
	if (_head != nullptr) {
		_head->prev = tmp;
		tmp->next = _head;
		tmp->prev = nullptr;
	}
	if (_head == nullptr) {
		_head == tmp;
	}
	++_size;
	return tmp;
}

template <typename T>
Node<T>* DLinkedList<T>::push_head(const DLinkedList<T>& other) {
	DLinkedList copy= DLinkedList(other);
	if ((copy != nullptr) &&(this!=nullptr)) {
		copy._head = _head->prev;
		copy._head->next = _head;
		copy._size += _size;
		return copy;
	}
	if (copy == nullptr)
		return this;
	
}

template <typename T>
Node<T>* DLinkedList<T>::push_tail(const DLinkedList<T>& other) {
	DLinkedList copy = DLinkedList(other);
	if ((copy != nullptr) && (this != nullptr)) {
		copy._head = _tail->next;
		copy._head->prev = _tail;
		_size += copy._size;
		return this;
	}
	if(copy==nullptr)
		return this;
	
}

template <typename T>
void DLinkedList<T>::pop_head(Node<T>* head) {
	if (_head == nullptr)
		return;
	Node<T>* new_head = _head->next;
	if (new_head != nullptr)
		new_head->prev = nullptr;
	else _tail = nullptr;

	delete _head;
	_head = new_head;
	--_size;
}

template <typename T>
void DLinkedList<T>::pop_tail(Node<T>* head) {
	if (_tail == nullptr)
		return;
	Node<T>* new_tail = _tail->prev;
	if (new_tail != nullptr) {
		new_tail->next = nullptr;
	}
	else
		_head = nullptr;
	delete _tail;
	_tail = new_tail;
	--_size;
}

template <typename T>
Node<T>* DLinkedList<T>::delete_node(T value) {
	if (_head = nullptr)
		return;
	Node<T>* tmp = _head;
	while (tmp) {
		if (tmp->data == value) {
			Node<T> p = tmp;
			tmp = tmp->next;
			if (p->prev != nullptr) {
				p->prev->next = p->next;
			}
			else {
				_head = p->prev;
			}
			if (p->next != nullptr) {
				p->next->prev = p->prev;
			}
			else {
				_tail = p->prev;
			}

			delete p;
			--_size;
		}
		else tmp = tmp->next;
	}
}



int main() {
	return 0;
}