#include <iostream>
#include<Windows.h>

using namespace std;

template <typename T>
struct Node {
	T data;
	Node<T>* prev;
	Node<T>* next;

	Node(const T& _data) {
		data = _data;
		prev = next = nullptr;
	};
};

template <typename T>
class DLinkedList {
	
	Node<T>* _head;
	Node<T>* _tail;
	int _size;

public:

	Node<T>* get_head() const;
	Node<T>* get_tail() const;
	int get_size() const;
	DLinkedList();
	DLinkedList(const DLinkedList<T>& other);
	DLinkedList(int count);
	~DLinkedList();

	DLinkedList<T> operator=(const DLinkedList<T>& other);
	Node<T>* operator[](int index);
	const Node<T>* operator[](int index) const;
	void clear();

	Node<T>* get_data(int index);
	Node<T>* insert(int index,const T& value);
	void remove(int index);

	Node<T>* push_tail(const T& value);
	Node<T>* push_head(const T& value);
	Node<T>* push_head(const DLinkedList<T>& other);
	Node<T>* push_tail(const DLinkedList<T>& other);

	void pop_head();
	void pop_tail();
	void delete_node(T value);
};

template<typename T>
Node<T>* DLinkedList<T>::get_head() const
{
	return _head;
}

template<typename T>
Node<T>* DLinkedList<T>::get_tail() const{
	if (_head == nullptr) {
		return nullptr; 
	}
	Node<T>* tmp = _head;

	while (tmp->next != nullptr) {
		tmp = tmp->next;
	}
	return tmp;
	}


template<typename T>
int DLinkedList<T>::get_size() const
{
	return _size;
}

template <typename T>
DLinkedList<T>::DLinkedList() {
	_head = _tail = nullptr;
	_size = 0;
}

template <typename T>
Node<T>* DLinkedList<T>::push_tail(const T& value) {
	Node<T>* tmp = new Node<T>(value);
	if (!_head)
		_head = tmp;
	else
	{
		Node<T>* last = _head;
		while (last->next != nullptr)
			last = last->next;
		last->next = tmp;
		tmp->prev = last;
	}
	return tmp;
}

template <typename T>
Node<T>* DLinkedList<T>::push_head(const T& value) {
	Node<T>* tmp = new Node<T>(value);
	_tail = get_tail();
	tmp->next = _head;
	if (_head != nullptr) {
		_head->prev = tmp;
	}
	if (_tail == nullptr) {
		_tail == tmp;
	}
	_head = tmp;
	++_size;

	return tmp;
}


template <typename T>
DLinkedList<T>::DLinkedList(const DLinkedList<T>& other) {
	_head = _tail = nullptr;
	_size = other.get_size();
	Node<T>* new_head = other.get_head();
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
		T value = rand() % 100;
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
Node<T>* DLinkedList<T>::operator[](int index) {
	 return get_data(index);
}

template <typename T>
const Node<T>* DLinkedList<T>::operator[](int index) const {
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
Node<T>* DLinkedList<T>::insert(int index, const T& value) {
	Node<T>* right = get_data(index);
	if (right == nullptr) {
		++_size;
		return push_tail(value);
	}
	Node<T>* left = right->prev;
	if (left == nullptr) {
		++_size;
		return push_head(value);
	}
	Node<T>* new_el = new Node<T>(value);
	new_el->prev = left;
	new_el->next = right;
	left->next = new_el;
	right->prev = new_el;
	++_size;
	return new_el;
}

template <typename T>
void DLinkedList<T>::remove(int index) {
	Node<T>* del_el = get_data(index);
	if (del_el == nullptr)
		return;
	if (del_el->prev == nullptr) {
		return pop_head();
	}
	if (del_el->next == nullptr) {
		return pop_tail();
	}
	Node<T>* left = del_el->prev;
	Node<T>* right = del_el->next;
	left->next = right;
	right->prev = left;
	delete del_el;
}




template <typename T>
Node<T>* DLinkedList<T>::push_head(const DLinkedList<T>& other) {
	Node<T>* tmp = other.get_tail();
	while (tmp != nullptr) {
		push_head(tmp->data);
		tmp = tmp->prev;
	}
	return tmp;
}

template <typename T>
Node<T>* DLinkedList<T>::push_tail(const DLinkedList<T>& other) {
	Node<T>* tmp = other.get_head();
	while (tmp != nullptr) {
		T r = tmp->data;
		push_tail(r);
		tmp = tmp->next;
	}
	return tmp;
}
	

template <typename T>
void DLinkedList<T>::pop_head() {
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
void DLinkedList<T>::pop_tail() {
	_tail = get_tail();
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
void DLinkedList<T>::delete_node(T value) {
	Node<T>* tmp = _head;
	while (tmp != nullptr) {
		if (tmp->data == value) {
			Node<T>* p = tmp;
			tmp = tmp->next;

			if (p->prev != nullptr) {
				p->prev->next = p->next;
			}
			else {
				_head = p->next;
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
		else {
			tmp = tmp->next;
		}
	}
}


int main() {
	SetConsoleOutputCP(1251);


	DLinkedList<double> lst;
	DLinkedList<double> wlst;
	std::cout << "Проверка гетеров" << endl;
	std::cout<<"get_head()"<<lst.get_head() << endl;
	std::cout << "get_tail()" << lst.get_tail()<<endl;
	std::cout << "get_size()" << lst.get_size() << endl;
	
	std::cout << "Конструктор с рандомными значениями: ";
	DLinkedList<int> ten = DLinkedList<int>(5);
	for (Node<int>* ptr = ten.get_head(); ptr != nullptr; ptr = ptr->next)
		std::cout << ptr->data << " ";
	std::cout << std::endl; 


	
	std::cout << "Проверка оператора = : ";
	DLinkedList<int> lst_second;
	DLinkedList<int> lst_third;
	lst_third.push_head(4);
	lst_third.push_head(3);
	lst_third.push_head(2);
	lst_third.push_head(1);

	lst_second = lst_third;
	for (Node<int>* ptr = lst_second.get_head(); ptr != nullptr; ptr = ptr->next)
		std::cout << ptr->data << " ";
	std::cout << std::endl;

	
	std::cout << "Проверка конструктора копирования : ";
	DLinkedList<int> lst_four(lst_third);
	for (Node<int>* ptr = lst_second.get_head(); ptr != nullptr; ptr = ptr->next)
		std::cout << ptr->data << " ";
	std::cout << std::endl;
	
	lst.push_head(4.0);
	lst.push_head(5.0);
	lst.push_head(2.0);
	lst.push_head(8.0);
	for (Node<double>* ptr = lst.get_head(); ptr != nullptr; ptr = ptr->next)
		std::cout << ptr->data << " ";
	std::cout << std::endl;

	wlst.push_tail(4.0);
	wlst.push_tail(5.0);
	wlst.push_tail(2.0);
	wlst.push_tail(8.0);
	for (Node<double>* ptr = wlst.get_head(); ptr != nullptr; ptr = ptr->next)
		std::cout << ptr->data << " ";
	std::cout << std::endl;

	std::cout <<"Оператор [ ]: "<< lst[1]->data << endl;

	lst.insert(0, 9.0);
	std::cout << "Вставка по индексу  в начало списка: " << endl;
	std::cout << "Вывод измененного списка: ";
	for (Node<double>* ptr = lst.get_head(); ptr != nullptr; ptr = ptr->next)
		std::cout << ptr->data << " ";
	std::cout << std::endl;

	std::cout << "Вставка по индексу в середину списка: " << endl;
	lst.insert(2, 7.0);
	for (Node<double>* ptr = lst.get_head(); ptr != nullptr; ptr = ptr->next)
		std::cout << ptr->data << " ";
	std::cout << std::endl;

	std::cout << "Вставка по индексу в конец списка: " <<  endl;
	lst.insert(6, 3.0);
	for (Node<double>* ptr = lst.get_head(); ptr != nullptr; ptr = ptr->next)
		std::cout << ptr->data << " ";
	std::cout << std::endl;

	std::cout << "Удаление по индексу"<< endl;
	lst.remove(4);
	for (Node<double>* ptr = lst.get_head(); ptr != nullptr; ptr = ptr->next)
		std::cout << ptr->data << " ";
	std::cout << std::endl;

	std::cout << "Вставка списка в конец" << endl;
	lst.push_tail(wlst);
	for (Node<double>* ptr = lst.get_head(); ptr != nullptr; ptr = ptr->next)
		std::cout << ptr->data << " ";
	std::cout << std::endl;

	std::cout << "Вставка списка в начало" << endl;
	lst.push_head(wlst);
	for (Node<double>* ptr = lst.get_head(); ptr != nullptr; ptr = ptr->next)
		std::cout << ptr->data << " ";
	std::cout << std::endl;
	
	std::cout << "Удаление первого элемента" << endl;
	lst.pop_head();
	for (Node<double>* ptr = lst.get_head(); ptr != nullptr; ptr = ptr->next)
		std::cout << ptr->data << " ";
	std::cout << std::endl;

	std::cout << "Удаление последнего элемента" << endl;
	lst.pop_tail();
	for (Node<double>* ptr = lst.get_head(); ptr != nullptr; ptr = ptr->next)
		std::cout << ptr->data << " ";
	std::cout << std::endl;

	std::cout << "Удаление всех элементов с заданным значением" << endl;
	lst.delete_node(2.0);
	for (Node<double>* ptr = lst.get_head(); ptr != nullptr; ptr = ptr->next)
		std::cout << ptr->data << " ";
	std::cout << std::endl;


	return 0;
}