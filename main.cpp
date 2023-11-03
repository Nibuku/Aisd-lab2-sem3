#include <iostream>

using namespace std;
template <typename T>


class DLinkedList {
	struct Node {
		T data;
		Node* prev;
		Node* next;

		Node(const T& data) {
			this->data = data;
			this->prev = this->next = nullptr;
		};

	};
	
	Node* _head;
	Node* _tail;
	int _size;

public:
	DLinkedList();
	DLinkedList(const DLinkedList<T>& other);
	DLinkedList(int count);
	~DLinkedList();

	DLinkedList<T> operator=(const DLinkedList<T>& other);
	T& operator[](int index);
	const T& operator[](int index) const;

	Node* push_tail(const T& value);
	Node* push_head(const T& value);
	Node* push_head(const DLinkedList<T>& other);
	void pop_head(Node* head);
	void pop_tail(Node* head);
	Node* delete_node(T value);


};

template <typename T>
DLinkedList<T>::DLinkedList() {
	_head = _tail = nullptr;
	_size = 0;
}

template <typename T>
DLinkedList<T>::DLinkedList(const DLinkedList<T>& other) {
	_head = _tail = nullptr;
	_size = 0;
	Node* new_head = other._head;
	while (new_head) {
		push_tail(new_head->data);
		new_head = new_head->next;
	}
}

template <typename T>
DLinkedList<T>::DLinkedList(int count) {
	_head = _tail =nullptr;
	_size = 0;
	for (int i = 0; i < count; ++i) {
		T value = rand() % 10000;
		push_tail(value);
	}
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




int main() {
	return 0;
}