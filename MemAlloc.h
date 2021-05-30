#pragma once

#include<memory>
#include <iostream>

/*  operator new & array new & palcement new  */
//namespace _new_delete_
//{
//class A {
//	int* p;
//	int len;
//public:
//	A() :len(0) {
//		cout << "default constructor:" << this << "  length:" << len << endl;
//	};
//	A(int i) :len(i) {
//		p = new int[len];
//		cout << "real constructor:" << this << "  length:" << len << endl;
//	};
//	~A() {
//		len = 0;
//		if (p != nullptr)	delete[] p;
//		cout << "destructor:" << this << "  length:" << len << endl;
//	};
//};
//
//int main()
//{
//	A* ptr = new A[3];
//	A* tmp = ptr;
//	cout << "ptr:" << ptr << "  tmp:" << tmp << endl;
//	for (int i = 0; i < 3; ++i)
//		new(ptr++)A(i + 1);
//	cout << "ptr:" << ptr << "  tmp:" << tmp << endl;
//	delete[] tmp;
//
//	return 0;
//}
//}


/* override new & delete : version 3 */
//#define CALL_ALLOCATE_DELLOCATE()\
//static void* operator new(size_t size) {\
//	return myAlloc.allocate(size);\
//}\
//static void operator delete(void* p, size_t size) {\
//	return myAlloc.dellocate(p, size);\
//};
//
//#define CONSTRUCT_MYALLOCATOR(class_name)\
//MyAllocator class_name::myAlloc;
//
/* MyAllocator */
//class MyAllocator {
//private:
//	struct obj {
//		struct obj* next;
//	};
//public:
//	void* allocate(size_t size) {
//		obj* p = nullptr;
//		if (!freeMem) {
//			freeMem = p = (obj*)malloc(size * ChunkSize);
//			for (int i = 1; i != ChunkSize; i++) {
//				p->next = (obj*)((char*)p + size);
//				p = p->next;
//			}
//			p->next = nullptr;
//		}
//		p = freeMem;
//		freeMem = freeMem->next;
//		return p;
//	}
//	void dellocate(void* p, size_t size) {
//		((obj*)p)->next = freeMem;
//		freeMem = (obj*)p;
//	}
//	void check(int index) {
//		obj* p = freeMem;
//		while (p != nullptr) {
//			cout << index++ << " : " << p << endl;
//			p = p->next;
//		}
//	}
//private:
//	obj* freeMem = nullptr;
//	const int ChunkSize = 5;
//};
//
/* test class : Student */
//class Student {
//public:
//	Student(int nId, string sName = "default") :id(nId), name(sName) {}
//	Student() = default;
//	~Student() = default;
//	void printIt() {
//		cout << id << " " << name << endl;
//	}
//public:
//	static void* operator new(size_t size) {
//		return myAlloc.allocate(size);
//	}
//	static void operator delete(void* p, size_t size) {
//		return myAlloc.dellocate(p, size);
//	}
//private:
//	int id;
//	string name;
//public:
//	static MyAllocator myAlloc;
//};
//MyAllocator Student::myAlloc;
//
/* test class : Teacher */
//class Teacher {
//public:
//	Teacher(int nPos, Student cStu) :position(nPos), stu(cStu) {}
//	void printIt() {
//		cout << position << endl;
//		stu.printIt();
//	}
//public:
//	CALL_ALLOCATE_DELLOCATE()
//private:
//	int position;
//	Student stu;
//public:
//	static MyAllocator myAlloc;
//};
//CONSTRUCT_MYALLOCATOR(Teacher);
//
/* test function */
//void __to_test_MyAllocator() {
//	Student* pStu[20];
//	for (int i = 0; i != 7; i++) {
//		pStu[i] = new Student(i + 1, "number" + to_string(i + 1));
//		cout << i + 1 << " : " << pStu[i] << "  ";
//		pStu[i]->printIt();
//	}
//	Student::myAlloc.check(8);
//
//	cout << "* - - - - - - - *" << endl;
//
//	for (int i = 0; i != 4; i++) {
//		delete pStu[i];
//	}
//	Student::myAlloc.check(1);
//
//	cout << "* - - - - - - - *" << endl;
//
//	for (int i = 0; i != 4; i++) {
//		pStu[i] = new Student(i * 10 + 10);
//		cout << i + 1 << " : " << pStu[i] << "  ";
//		pStu[i]->printIt();
//	}
//	Student::myAlloc.check(5);
//
//	cout << "* - - - - - - - *" << endl;
//
//	for (int i = 0; i != 7; i++) {
//		delete pStu[i];
//	}
//	Student::myAlloc.check(1);
//
//	cout << "* - - - - - - - *" << endl;
//
//	Student* p = new Student();
//	Teacher* tp1 = new Teacher(0, *p);
//	Teacher::myAlloc.check(1);
//	delete tp1;
//
//	cout << "* - - - - - - - *" << endl;
//
//	Teacher* tp2 = new Teacher(9, *p);
//	Teacher::myAlloc.check(1);
//
//	delete p;	// new�������delete
//	delete tp2;
//}


/* PoolAlloc in single-thread environment */
/* GNU-C v2.9 */
class PoolAlloc {
private:
	enum e1 { MAX_BYTES = 128 };
	enum e2 { AlIGN = 8 };
	enum e3 { MAX_LIST_LEN = MAX_BYTES / AlIGN };
	enum e4 { N_OBJS = 20 };

private:
	// ���϶���Ϊ8�ı���
	inline size_t round_up(size_t size) {	return ((size + AlIGN - 1) & ~(AlIGN - 1));}

	// ��MAX_LIST_LEN���ҵ���Ҫ�õ��������������
	inline int find_list_index(size_t size) {	return (int)size / AlIGN  - 1;}

public:
	// ����size�ֽڵ��ڴ�ռ䣬������ָ��
	void* allocate(size_t size);

	// �ͷ�pָ��ģ���СΪsize�ֽڵ��ڴ�ռ�
	void deallocate(void* p, size_t size);

	// ��ӡ�ڴ���������Ϣ
	void outputInfo();

private:
	// �����ڡ�ս���ء�����һ������ڴ��������allocateû�п����ڴ�ʱ������
	void* refill(size_t size);

	// ���䡰ս���ء�����refill�޼ƿ�ʩʱ������
	char* chunk_alloc(size_t size, int& nObjs);

private:
	// ���ÿ����ڴ��ǰ4 Bytes��Ϊembedded pointer
	struct obj{	struct obj* next;};

	// ָ�����飬MAX_LIST_LEN��ָ��ֱ�ָ�����Ӧ������ͷ��
	obj* free_lists[MAX_LIST_LEN] = {nullptr};

	//��ս���ء���startλ�ã���ByteΪ��λ����char*
	char* start_free = 0;

	//��ս���ء���endλ�ã�Ҳ��ByteΪ��λ
	char* end_free = 0;

private:
	PoolAlloc() {	// ���캯��private��ʹ��ֱ�Ӷ���ķ�ʽʧЧ��ֻ��ͨ��get_instance����ȡʵ��
		std::cout << "Constructor called once" << std::endl;
	}
public:
	~PoolAlloc() {	// ��������public����
		std::cout << "Destructor called once" << std::endl;
		obj** cur_list_head = nullptr;
		obj* p = nullptr, *q = nullptr;
		for (size_t i = AlIGN; i <= MAX_BYTES; i += AlIGN) {
			cur_list_head = free_lists + find_list_index(i);
			p = *cur_list_head;
			while (nullptr != p) {
				q = p->next;
				/* TODO */

				/* �ͷ�p���ڵ�һ�οռ䣬��i���ֽڣ���������� */
				p = q;
			}
		}
	}
	static PoolAlloc& get_instance() {	// ͨ��get_instance��ȡΨһʵ��������ģʽ - ����ģʽ��
		static PoolAlloc instance;		// �ֲ���̬����������C++11��Magic Static���ԣ���������:
										// If control enters the declaration concurrently while the
										// variable is being initialized, the concurrent execution
										// shall wait for completion of the initialization.
		return instance;
	}
};

//PoolAlloc::obj* PoolAlloc::free_lists[PoolAlloc::MAX_LIST_LEN] = { nullptr };
//char* PoolAlloc::start_free = 0;
//char* PoolAlloc::end_free = 0;

void* PoolAlloc::allocate(size_t size) {
	if (size > MAX_BYTES) {
		return malloc(size);
	}
	size = round_up(size);
	obj** cur_listhead = free_lists + find_list_index(size);
	if (nullptr == *cur_listhead) {
		*cur_listhead = (obj*)refill(size);
	}
	obj* res = *cur_listhead;
	*cur_listhead = (*cur_listhead)->next;
	return (void*)res;
}

void PoolAlloc::deallocate(void* p, size_t size) {
	if (size > MAX_BYTES) {
		free(p);
		return;
	}
	size = round_up(size);
	obj** cur_listhead = free_lists + find_list_index(size);
	obj* q = (obj*)p;
	q->next = *cur_listhead;
	*cur_listhead = q;
}

void PoolAlloc::outputInfo(){
	obj** list_head = nullptr;
	obj* cur_node = nullptr;
	for (int i = 0; i < MAX_LIST_LEN; ++i) {
		list_head = free_lists + i;
		if (*list_head) {
			std::cout << "Free List " << i << " : " << std::endl;
			cur_node = *list_head;
			while (cur_node) {
				std::cout << cur_node << std::endl;
				cur_node = cur_node->next;
			}
			std::cout << std::endl;
		}
	}
	std::cout << std::endl << " - - - - - - - - - - " << std::endl;
}

void* PoolAlloc::refill(size_t size) {
	int nObjs = N_OBJS;
	obj** cur_listhead = free_lists + find_list_index(size);
	*cur_listhead = (obj*)chunk_alloc(size, nObjs);
	obj* res = *cur_listhead;
	obj* cur_obj = res;
	obj* next_obj = nullptr;
	for (int i = 1; i < nObjs; ++i) {
		next_obj = (obj*)((char*)cur_obj + size);
		cur_obj->next = next_obj;
		cur_obj = next_obj;
	}
	cur_obj->next = nullptr;
	return res;
}

char* PoolAlloc::chunk_alloc(size_t size, int& nObjs) {
	size_t bytes_need = size * nObjs;
	size_t free_pool_left = end_free - start_free;
	char* res = nullptr;
	if (bytes_need < free_pool_left) {
		res = start_free;
		start_free += bytes_need;
		return res;
	}
	else if (free_pool_left >= size) {
		res = start_free;
		nObjs = free_pool_left / size;
		start_free += nObjs * size;
		return res;
	}
	else {
		if (free_pool_left > 0) {	/*  */
			obj** cur_listhead = free_lists + find_list_index(free_pool_left);
			((obj*)start_free)->next = *cur_listhead;
			*cur_listhead = (obj*)start_free;
		}
		res = (char*) malloc(2 * bytes_need);
		if (nullptr == res) {	/*  */
			obj** cur_listhead = nullptr;
			obj* p = nullptr;
			for (int i = size; i <= MAX_BYTES; i += AlIGN) {
				cur_listhead = free_lists + find_list_index(i);
				p = *cur_listhead;
				if (nullptr != p) {
					*cur_listhead = p->next;
					start_free = (char*)p;
					end_free = start_free + i;
					return chunk_alloc(size, nObjs);
				}
			}
			res = (char*)malloc(2 * bytes_need);
		}
		start_free = res;
		end_free = res + 2 * bytes_need;
		return chunk_alloc(size,nObjs);
	}
}