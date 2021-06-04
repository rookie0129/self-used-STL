#pragma once

#include<iostream>

#define Ptr2Int(x) reinterpret_cast<int>(x)

#define Int2Ptr(x) reinterpret_cast<ListNode<T>*>(x)

/* 亦或双向链表的结点 */
template<typename T>
class ListNode
{
public:
	T data;
	ListNode<T>* ptrdiff;
public:
	ListNode(const T &e = T(), ListNode<T>* p = nullptr) :data(e), ptrdiff(p) {
		//std::cout << "node reg ctor" << std::endl; 
	}
	ListNode(const ListNode<T>& rhs) {
		this->data = rhs.data; 
		this->ptrdiff = rhs.ptrdiff;
		std::cout << "node copy ctor" << std::endl; 
	}
	~ListNode() {
		std::cout << "node dtor" << std::endl; 
	}
	T getData() const { return data; }
	T& getDataRef() const { return data; }

	ListNode<T>* getPointer() const { return ptrdiff; }
	ListNode<T>*& getPointerRef() const { return ptrdiff; }
};

/* 用于管理亦或双向链表 */
template<typename T>
class DoublyLinkedList_XOR
{
private:
	ListNode<T>* head;
	ListNode<T>* tail;
	size_t length;

public:
	DoublyLinkedList_XOR(ListNode<T>* h = nullptr, ListNode<T>* t = nullptr, size_t len = 0):head(h), tail(t), length(len){}
	DoublyLinkedList_XOR(const std::initializer_list<T>& list) { for (const T& t : list)	this->push_back(t); }
	~DoublyLinkedList_XOR() {
		this->clear();
		std::cout << "list dtor" << std::endl;
	}

	void clear();	/* flawless ? */

	void push_range(const std::initializer_list<T>& list, bool back = true);
	void push_back(const T& t);
	void pop_back();
	void push_front(const T& t);
	void pop_front();
	void insert(size_t index, const T& t);

	void erase_range(size_t start, size_t len);
	void erase_by_value(const T &t);
	void erase_by_index(size_t index);

	ListNode<T>* search_by_value(const T& t, bool seq = true);
	ListNode<T>* search_by_index(size_t index, bool seq = true);
	size_t locate(const T& t);
	ListNode<T>* operator [](size_t index) { return search_by_index(index); }	/* 没有引用噢，只是解解馋，无法通过它直接修改 */

	void seTraverse();
	void reTraverse();
	int countSatisfied(bool (*pf)(const T& t));

	void edit(const T&, const T&);
	void edit(size_t index, const T&);

	void reverse() { ListNode<T>* tmp = head; head = tail; tail = tmp; }
	size_t size() { return this->length; }
	bool empty() { return 0 == this->length; }

	ListNode<T>* getHead() { return this->head; }
	ListNode<T>* getTail() { return this->tail; }

};

template<typename T>
size_t DoublyLinkedList_XOR<T>::locate(const T &t) {
	int nPrev = 0;
	size_t i = 0;
	ListNode<T>* p = head;
	ListNode<T>* q = head;
	while (p) {
		if (t == p->data) {
			return i;
		}
		q = Int2Ptr(Ptr2Int(p->ptrdiff) ^ nPrev);
		nPrev = Ptr2Int(p);
		p = q;
		++i;
	}
	return -1;
}

template<typename T>
ListNode<T>* DoublyLinkedList_XOR<T>::search_by_value(const T &t, bool seq) {
	int nPrev = 0;
	ListNode<T>* p;
	ListNode<T>* q;
	if (seq) {
		p = q = head;
	}
	else {
		p = q = tail;
	}
	while (p) {
		if (t == p->data) {
			return p;
		}
		q = Int2Ptr(Ptr2Int(p->ptrdiff) ^ nPrev);
		nPrev = Ptr2Int(p);
		p = q;
	}
	return nullptr;
}

template<typename T>
ListNode<T>* DoublyLinkedList_XOR<T>::search_by_index(size_t index, bool seq) {
	if (index < 0 || index >= length) {
		std::cerr << "the index is out of range " << std::endl;
		return nullptr;
	}
	int nPrev = 0;
	size_t i = 0;
	ListNode<T>* p;
	ListNode<T>* q;
	if (seq) {
		p = q = head;
	}
	else {
		p = q = tail;
	}
	while (p) {
		if (i == index) {
			return p;
		}
		q = Int2Ptr(Ptr2Int(p->ptrdiff) ^ nPrev);
		nPrev = Ptr2Int(p);
		p = q;
		++i;
	}
	return nullptr;
}

template<typename T>
void DoublyLinkedList_XOR<T>::push_back(const T& t) {
	int nPre = Ptr2Int(tail);
	ListNode<T>* pNode = new ListNode<T>(t);
	if (nullptr == head) {
		head = tail = pNode;
	}
	else {
		pNode->ptrdiff = Int2Ptr(nPre);
		ListNode<T>* tmp = tail;
		tail = pNode;
		tmp->ptrdiff = Int2Ptr(Ptr2Int(tmp->ptrdiff) ^ Ptr2Int(pNode));
	}
	++length;
}

template<typename T>
void DoublyLinkedList_XOR<T>::pop_back() {
	if (tail == nullptr) {
		std::cerr << "nothing to pop" << std::endl;
		return;
	}
	if (tail->ptrdiff == nullptr) {
		ListNode<T>* tmp = tail;
		tail = head = nullptr;
		delete tmp;
		tmp = nullptr;
	}
	else {
		ListNode<T>* newTail = tail->ptrdiff;
		newTail->ptrdiff = Int2Ptr(Ptr2Int(newTail->ptrdiff) ^ Ptr2Int(tail));
		delete tail;
		tail = newTail;
	}
	--length;
}

template<typename T>
void DoublyLinkedList_XOR<T>::push_front(const T& t) {
	int nNext = Ptr2Int(head);
	ListNode<T>* pNode = new ListNode<T>(t);
	if (nullptr == tail) {
		tail = head = pNode;
	}
	else {
		pNode->ptrdiff = Int2Ptr(nNext);
		ListNode<T>* tmp = head;
		head = pNode;
		tmp->ptrdiff = Int2Ptr(Ptr2Int(tmp->ptrdiff) ^ Ptr2Int(pNode));
	}
	++length;
}

template<typename T>
void DoublyLinkedList_XOR<T>::pop_front() {
	if (head == nullptr) {
		std::cerr << "nothing to pop" << std::endl;
		return;
	}
	if (head->ptrdiff == nullptr) {
		ListNode<T>* tmp = head;
		head = tail = nullptr;
		delete tmp;
		tmp = nullptr;
	}
	else {
		ListNode<T>* newHead = head->ptrdiff;
		newHead->ptrdiff = Int2Ptr(Ptr2Int(newHead->ptrdiff) ^ Ptr2Int(head));
		delete head;
		head = newHead;
	}
	--length;
}

template<typename T>
void DoublyLinkedList_XOR<T>::insert(size_t index, const T& t) {
	if (index < 0 || index > length) {
		std::cerr << "out of range, can't insert" << std::endl;
		return;
	}
	if (index == 0) {
		push_front(t);
	}
	else if (index == length) {
		push_back(t);
	}
	else {
		ListNode<T>* pPrev = search_by_index(index-1);
		ListNode<T>* pNext = search_by_index(index);
		ListNode<T>* p = new ListNode<T>(t);
		p->ptrdiff = Int2Ptr(Ptr2Int(pPrev) ^ Ptr2Int(pNext));
		pPrev->ptrdiff = Int2Ptr(Ptr2Int(pPrev->ptrdiff) ^ Ptr2Int(pNext) ^ Ptr2Int(p));
		pNext->ptrdiff = Int2Ptr(Ptr2Int(pNext->ptrdiff) ^ Ptr2Int(pPrev) ^ Ptr2Int(p));
		++length;
	}
}

template<typename T>
void DoublyLinkedList_XOR<T>::erase_range(size_t start, size_t len) {
	if (start < 0 || start >= length) {
		std::cerr << "the start index is out of range " << std::endl;
		return;
	}
	/* TODO: */

}

template<typename T>
void DoublyLinkedList_XOR<T>::erase_by_value(const T& t) {
	size_t i = locate(t);
	if(i != (size_t)-1)
		erase(i);
	else
		std::cout << "that node doesn't exist" << std::endl;
}

template<typename T>
void DoublyLinkedList_XOR<T>::erase_by_index(size_t index) {
	if (index < 0 || index >= length) {
		std::cerr << "out of range, can't delete" << std::endl;
		return;
	}
	if (index == 0) {
		pop_front();
	}
	else if (index == length - 1) {
		pop_back();
	}
	else {
		ListNode<T>* pPrev = search_by_index(index - 1);
		ListNode<T>* pCur = search_by_index(index);
		ListNode<T>* pNext = Int2Ptr(Ptr2Int(pCur->ptrdiff) ^ Ptr2Int(pPrev));
		pPrev->ptrdiff = Int2Ptr(Ptr2Int(pPrev->ptrdiff) ^ Ptr2Int(pCur) ^ Ptr2Int(pNext));
		pNext->ptrdiff = Int2Ptr(Ptr2Int(pNext->ptrdiff) ^ Ptr2Int(pCur) ^ Ptr2Int(pPrev));
		delete pCur;
		pCur = nullptr;
		--length;
	}
}

template<typename T>
void DoublyLinkedList_XOR<T>::edit(const T& old_t, const T& new_t) {
	ListNode<T>* p = search_by_value(old_t);
	if (p)
		p->data = new_t;
	else
		std::cout << "the old value doesn't exist" << std::endl;
}

template<typename T>
void DoublyLinkedList_XOR<T>::edit(size_t index, const T& new_t) {
	ListNode<T>* p = search_by_index(index);
	if (p)
		p->data = new_t;
	else
		std::cout << "can't reach that index" << std::endl;
}

template<typename T>
void DoublyLinkedList_XOR<T>::push_range(const std::initializer_list<T>& list, bool back) {
	if (back) {
		for (const T& t : list) {
			this->push_back(t);
		}
	}
	else{
		for (const T& t : list) {
			this->push_front(t);
		}
	}
}

template<typename T>
void DoublyLinkedList_XOR<T>::clear() {
	ListNode<T>* p = head;
	ListNode<T>* q = head;
	while (p) {
		if (q = p->ptrdiff) {
			q->ptrdiff = Int2Ptr(Ptr2Int(p) ^ Ptr2Int(q->ptrdiff));
		}
		delete p;
		p = q;
	}
	/* 把head和tail给置空咯. */
	head = tail = nullptr;
	/* 长度自然是0 */
	length = 0;
}

template<typename T>
int DoublyLinkedList_XOR<T>::countSatisfied(bool (*pf)(const T& t)) {
	int nPrev = 0;
	int cnt = 0;
	ListNode<T>* p = head;
	ListNode<T>* q = head;
	while (p) {
		if (pf(p->data)) {
			/* TODO: 以计数为例，可以是其它的操作 */
			++cnt;
		}
		q = Int2Ptr(Ptr2Int(p->ptrdiff) ^ nPrev);
		nPrev = Ptr2Int(p);
		p = q;
	}

	return cnt;
}

template<typename T>
void DoublyLinkedList_XOR<T>::seTraverse() {
	int nPrev = 0;
	ListNode<T>* p = head;
	ListNode<T>* q = head;
	while (p) {
		std::cout << "data: " << p->data << std::endl;
		q = Int2Ptr(Ptr2Int(p->ptrdiff) ^ nPrev);
		nPrev = Ptr2Int(p);
		p = q;
	}
}

template<typename T>
void DoublyLinkedList_XOR<T>::reTraverse() {
	int nNext = 0;
	ListNode<T>* p = tail;
	ListNode<T>* q = tail;
	while (p) {
		std::cout << "data: " << p->data << std::endl;
		q = Int2Ptr(Ptr2Int(p->ptrdiff) ^ nNext);
		nNext = Ptr2Int(p);
		p = q;
	}
}

// Test:
//DoublyLinkedList_XOR<int> list{ 6,66,666,555,55,5 };
//list.push_range({ 1,3,9,8,10,6,4 });
//list.push_range({ 9,9,9,9 }, false);
//list.seTraverse();
//cout << endl;
//list.clear();
//list.push_range({ 9,7,5,3,0 }, false);
//list.reTraverse();
//cout << endl;

//DoublyLinkedList_XOR<int> list{ 6,66,666,555,55,5 };
//list.push_range({ 1,3,9,8,10,6,4 });
//list.push_range({ 9,9,9,9 }, false);
//list.seTraverse();
//
//size_t indx = 0;
//while (1) {
//	cout << "search, enter index: ";
//	cin >> indx;
//	if (auto p = list[indx])
//		cout << "index: " << indx << "  data: " << p->data << endl;
//	else
//		cout << "can't find it" << endl;
//
//	cout << "edit, enter index: ";
//	cin >> indx;
//	list.edit(indx, (int)0);
//}

//DoublyLinkedList_XOR<int> list;
//list.erase((size_t)0);
//list.erase((size_t)0);
//list.erase((size_t)10);
//cout << "len:" << list.size() << endl;
//list.seTraverse();
//list.erase((size_t)9);
//list.erase((size_t)8);
//cout << "len:" << list.size() << endl;
//list.seTraverse();
//list.erase((size_t)4);
//list.erase((size_t)4);
//cout << "len:" << list.size() << endl;
//list.seTraverse();

//list.pop_back();
//list.seTraverse();
//list.pop_back();
//list.seTraverse();
//list.pop_back();
//list.pop_back();
//list.pop_back();
//list.pop_back();
//list.pop_back();
//list.seTraverse();

//list.pop_front();
//list.seTraverse();
//list.pop_front();
//list.seTraverse();
//list.pop_front();
//list.pop_front();
//list.pop_front();
//list.pop_front();
//list.pop_front();
//list.seTraverse();

//list.seTraverse();
//list.insert(-1, 88);
//list.insert(99, 88);
//list.insert(6, 88);
//list.seTraverse();
//list.insert(6, 678);
//list.insert(0, 0);
//list.insert(6, 678);
//list.seTraverse();

//cout << "sequential: " << endl;
//list.seTraverse();
//cout << "reverse: " << endl;
//list.reTraverse();
//cout << endl << "reverse " << endl << endl;
//list.reverse();
//cout << "sequential: " << endl;
//list.seTraverse();
//cout << "reverse: " << endl;
//list.reTraverse();

//while (true) {

//size_t indx = 0;
//cout << "search by index: ";	cin >> indx;
//if (auto p = list.search_by_index(indx)) 
//	cout << "index: " << indx << "  data: " << p->data << endl;
//else 
//	cout << "can't find it" << endl;

//cout << "search by index(reverse): ";	cin >> indx;
//if (auto p = list.search_by_index(indx,false)) 
//	cout << "index: " << indx << "  data: " << p->data << endl;
//else 
//	cout << "can't find it" << endl;

//cout << "search by value: ";
//int t = 0;
//cin >> t;
//if (auto p = list.search_by_value(t)) {
//	cout << "  data: " << p->data << endl;
//}
//else {
//	cout << "can't find it" << endl;
//}
//list.edit(t, t + 1);

//cout << "locate by value: ";
//cin >> t;
//size_t ii = list.locate(t);
//if (ii != (size_t)-1) {
//	cout << "index: " << ii << "  data: " << t << endl;
//}
//else {
//	cout << "can't find it" << endl;
//}

//}
