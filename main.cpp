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
	DLinkedList(int count, const T& min, const T& max);
	~DLinkedList();

	DLinkedList<T> operator=(const DLinkedList<T>& other);
	T& operator[](int index);
	const T& operator[](int index) const;
	T& rewrite_data(int index,const T& value);
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

	T multiply(DLinkedList<T>& other);
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
	_tail = tmp;
	return tmp;
}

template <typename T>
Node<T>* DLinkedList<T>::push_head(const T& value) {
	Node<T>* tmp = new Node<T>(value);
	tmp->next = _head;
	if (_head != nullptr) {
		_head->prev = tmp;
	}
	if (_tail == nullptr) {
		_tail = _head=tmp;
	}
	_head =tmp;
	++_size;

	return tmp;
}


template <typename T>
DLinkedList<T>::DLinkedList(const DLinkedList<T>& other) {
	_head = _tail = nullptr;
	_size = other.get_size();
	Node<T>* new_head = other._head;
	while (new_head) {
		push_tail(new_head->data);
		new_head = new_head->next;
	}
}

template <typename T>
DLinkedList<T>::DLinkedList(int count, const T& min, const T& max) {
	srand(time(0));
	_head = _tail =nullptr;
	_size = count;
	for (int i = 0; i < _size; ++i) {
		T value = rand() % (max-min+1)+min ;
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
	 return get_data(index)->data;
}


template <typename T>
const T& DLinkedList<T>::operator[](int index) const {
	return get_data(index)->data;
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
	Node<T>* tmp = other._tail;
	while (tmp != nullptr) {
		push_head(tmp->data);
		tmp = tmp->prev;
	}
	return tmp;
}

template <typename T>
Node<T>* DLinkedList<T>::push_tail(const DLinkedList<T>& other) {
	Node<T>* tmp = other._head;
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

template <typename T>
T DLinkedList<T>::multiply(DLinkedList<T>& other)
{
	Node<T>* first = _head;
	Node<T>* second = other._head;
	T N = 1000000000;
	T num1 = 0, num2 = 0;
	while (first || second) {

		if (first) {
			num1 = ((num1) * 10) % N + first->data;
			first = first->next;
		}

		if (second)
		{
			num2 = ((num2) * 10) % N + second->data;
			second = second->next;
		}

	}
	return ((num1 % N) * (num2 % N)) % N;
}

template <typename T>
DLinkedList<T>& sum(DLinkedList<T>& first, DLinkedList<T>& other)
{
	DLinkedList<T>* sumList = new DLinkedList<T>;

	Node<T>* node1 = first.get_tail(); 
	Node<T>* node2 = other.get_tail();

	T sum = 0;
	T carry = 0;
	while (node1 || node2)
	{
		if (node1)
			sum += node1->data;
		if (node2)
			sum += node2->data;
		sum += carry;

		carry = 0;
		sumList->push_head(sum % 10);
		if (sum > 9)
			carry = 1;
		sum = 0;
		node1 = node1->prev; node2 = node2->prev;
	}
	return *sumList;
}



template <typename T>
void print(DLinkedList<T> list) {
	for (Node<T>* ptr = list.get_head(); ptr != nullptr; ptr = ptr->next)
		std::cout << ptr->data << " ";
	std::cout << std::endl;
}

template <typename T>
void print_for_sum(DLinkedList<T> list) {
	for (Node<T>* ptr = list.get_head(); ptr != nullptr; ptr = ptr->next)
		std::cout << ptr->data;
	std::cout << std::endl;
}







int main() {
	SetConsoleOutputCP(1251);


	DLinkedList<double> lst;
	DLinkedList<double> wlst;
	std::cout << "�������� �������" << endl;
	std::cout<<"get_head()"<<lst.get_head() << endl;
	std::cout << "get_tail()" << lst.get_tail()<<endl;
	std::cout << "get_size()" << lst.get_size() << endl;
	
	std::cout << "����������� � ���������� ����������: ";
	DLinkedList<int> ten = DLinkedList<int>(5, 10, 100);
	print(ten);


	
	std::cout << "�������� ��������� =:";
	DLinkedList<int> lst_second;
	DLinkedList<int> lst_third;
	lst_third.push_head(4);
	lst_third.push_head(3);
	lst_third.push_head(2);
	lst_third.push_head(1);

	lst_second = lst_third;
	print(lst_second);

	
	std::cout << "�������� ������������ �����������: ";
	DLinkedList<int> lst_four(lst_third);
	print(lst_four);
	
	std::cout << "������� � ������: " <<endl;
	lst.push_head(4.0);
	lst.push_head(5.0);
	lst.push_head(2.0);
	lst.push_head(8.0);
	print(lst);


	std::cout << "������� � �����: " << endl;
	wlst.push_tail(4.0);
	wlst.push_tail(5.0);
	wlst.push_tail(2.0);
	wlst.push_tail(8.0);
	print(wlst);

	std::cout <<"�������� [ ]: "<< lst[1] << endl;

	lst.insert(0, 9.0);
	std::cout << "������� �� �������  � ������ ������: " << endl;
	std::cout << "����� ����������� ������: ";
	print(lst);

	std::cout << "������� �� ������� � �������� ������: " << endl;
	lst.insert(2, 7.0);
	print(lst);

	std::cout << "������� �� ������� � ����� ������: " <<  endl;
	lst.insert(6, 3.0);
	print(lst);

	std::cout << "�������� �� �������"<< endl;
	lst.remove(4);
	print(lst);

	std::cout << "������� ������ � �����" << endl;
	lst.push_tail(wlst);
	print(lst);

	std::cout << "������� ������ � ������" << endl;
	lst.push_head(wlst);
	print(lst);
	
	std::cout << "�������� ������� ��������" << endl;
	lst.pop_head();
	print(lst);

	std::cout << "�������� ���������� ��������" << endl;
	lst.pop_tail();
	print(lst);

	std::cout << "�������� ���� ��������� � �������� ���������" << endl;
	lst.delete_node(2.0);
	print(lst);

	DLinkedList<int> r;
	r.push_head(4);
	r.push_head(3);
	r.push_head(2);
	r.push_head(1);


	DLinkedList<int> d;
	d.push_head(4);
	d.push_head(9);
	d.push_head(9);
	d.push_head(1);

	std::cout << "�������� ���� ����� �������������� � ���� �������" << std::endl;
	std::cout << "������ ������" << std::endl;
	print(r);
	std::cout << "������ ������" << std::endl;
	print(d);
	DLinkedList<int> c= sum(r,d);
	std::cout << "�����" << std::endl;
	print_for_sum(c);
	std::cout << "��������: 1234+1994=" << 1234 + 1994<< std::endl;
	
	std::cout << "��������� ���� ����� �������������� � ���� �������" << std::endl;
	std::cout << r.multiply(d) << endl;;
	std::cout << "��������: 1234*1994=" << 1234*1994 << std::endl;
	
	DLinkedList<int> t;
	t.push_head(4);
	t.push_head(3);
	
	DLinkedList<int> x;
	x.push_head(4);
	x.push_head(9);
	x.push_head(9);
	x.push_head(1);

	std::cout<<x.multiply(t)<<endl;
	std::cout << "��������: 34*1994=" << 34 * 1994 << std::endl;

	int g = r[2] = 3;
	std::cout << g;


	return 0;
}