#pragma once

#include<iostream>
#include<vector>
#include<cstdlib>

using std::vector;
using std::swap;

// �������һ����
void arrayGenerator(vector<int>& _arr, int _size) {
	srand(time(nullptr));
	_arr.clear();
	for (int i = 0; i < _size; ++i) {
		_arr.push_back(rand() % 2048 + 1);
	}
}

// �������
void arrayDisplay(vector<int>& _arr) {
	std::cout << std::endl;
	for (int i = 0; i != (int)_arr.size(); ++i) {
		std::cout << _arr[i] << " ";
	}
	std::cout << std::endl;
}

//ʱ�临�Ӷȣ������Ƶ�ȵ��Ͻ������Ĺ���
//�ռ临�Ӷȣ������ڴ�ʹ�ã�ͬ���Ƕ��Ͻ�������
//�ȶ��ԣ�������ͬ�Ĺؼ��ֵļ�¼�����������Щ��¼����Դ����Ա��ֲ���

/**	ð������
*
*	ʱ�䣺��� O(n)��ƽ��O(n^2)���O(n^2) -> ��������������ﵽ��ã�������flag�Ż���
*	�ռ䣺O(1)��ԭ��
*	�ȶ��ԣ��ȶ���ֻ��"ǰ>��"�����ڶ���ǰ�󽻻�
*
*/
template<typename T>
class Bubble_Sort {
public:
	static void BubbleSort(vector<T>& arr) {
		int n = arr.size();
		for (int i = 0; i < n; ++i) {
			bool sorted = true;
			for (int j = 0; j < n - i - 1; ++j) {
				if (arr[j] > arr[j+1]) {
					sorted = false;
					arr[j] ^= arr[j + 1] ^= arr[j] ^= arr[j + 1];
				}
			}
			if(sorted)	return;
		}
	}
};


/**	ѡ������
*
*	ʱ�䣺��� O(n^2) = ƽ��O(n^2) = �O(n^2) -> ��ԭ�����޹أ�n + n-1 + n-2 + ... + 2 + 1 = n*(n+1)/2 �� O(n)
*	�ռ䣺O(1)��ԭ��
*	�ȶ��ԣ����ȶ���ÿ�ν�arr[minIndex]��arr[i]����������{ "5",6,7,5,"2",8 }����һ��5��2���������һ��5��ڶ���5��
*
*/
template<typename T>
class Selection_Sort {
public:
	static void SelectionSort(vector<T>& arr) {
		int n = arr.size();
		int minIndex;
		for (int i = 0; i < n; ++i) {
			minIndex = i;
			for (int j = i + 1; j < n; ++j) {
				if (arr[j] < arr[minIndex]) {
					minIndex = j;
				}
			}
			swap(arr[minIndex], arr[i]);
		}
	}
};


/**	��������
*
*	ʱ�䣺��� O(n)��ƽ��O(n^2)���O(n^2)	-> ��������������ﵽ��ã�ѹ��û�����룩
*	�ռ䣺O(1)��ԭ��
*	�ȶ��ԣ��ȶ�������ʱ������ͬ�ľͲ�������
*
*/
template<typename T>
class Insertion_Sort {
public:
	static void InsertionSort(vector<T>& arr) {
		int n = arr.size();
		for (int i = 1; i < n; ++i) {
			T key = arr[i];
			int j = i - 1;
			while (j >= 0 && arr[j] > key) {
				arr[j + 1] = arr[j];
				--j;
			}
			arr[j + 1] = key;
		}
	}


};


/**	ϣ������
*
*	ʱ�䣺���O(n)��ƽ��O(n^1.3)���O(n^2) -> ��������������ﵽ���
*	�ռ䣺O(1)��ԭ��
*	�ȶ��ԣ����ȶ�����Ϊ�Ǹ���gap�ģ������ƶ�ʱ����gap = 2 { 1,"6",5,"5",8, }��6�͵ڶ���5��������ڶ���5���һ��5
*
*/
template<typename T>
class Shell_Sort {
public:
	static void ShellSort(vector<T>& arr) {
		int n = arr.size();
		for (int gap = n / 2; gap >= 1; gap /= 2) {
			for (int i = gap; i < n; ++i) {
				T key = arr[i];
				int j = i - gap;
				while (j >= 0 && arr[j] > key) {
					arr[j + gap] = arr[j];
					j -= gap;
				}
				arr[j + gap] = key;
			}
		}
	}
};


/**	�鲢����
*
*   ʱ�临�Ӷȷ�����T(n) = 2T(n/2) + n, Ӧ��������������a=b=2��n^logb(a)=n��������T(n) = O(nlogn)
*	ʱ�䣺���O(nlogn) = ƽ��O(nlogn) = �O(nlogn) -> ��ԭ�����޹�
*	�ռ䣺O(n),��ԭ��
*	�ȶ��ԣ�ȫ�ȵģ������index����ֵ = �ұ�index����ֵ��ȡ����ߵģ��ʲ����ƻ��ȶ���
*
*/
template<typename T>
class Merge_Sort {
public:
	static void MergeSort(vector<T>& arr) {
		int n = arr.size();
		divide_and_conquer(arr, 0, n - 1);
	}

	static void divide_and_conquer(vector<T>& arr, int left, int right) {
		if (left >= right) {
			return;
		}
		int mid = (left + right) >> 1;
		/* divide the left part & right part, conquer them separately */
		divide_and_conquer(arr, left, mid);
		divide_and_conquer(arr, mid + 1, right);
		/* merge them */
		int index = left;
		vector<int> LArr(arr.begin() + left, arr.begin() + mid + 1);
		vector<int> RArr(arr.begin() + mid + 1, arr.begin() + right + 1);
		int L = 0;
		int R = 0;
		while (L != LArr.size() && R != RArr.size()) {
			if (LArr[L] <= RArr[R]) {
				arr[index] = LArr[L];
				++index; ++L;
			}
			else {
				arr[index] = RArr[R];
				++index; ++R;
			}
		}
		while (L != LArr.size()) {
			arr[index] = LArr[L];
			++index; ++L;
		}
		while (R != RArr.size()) {
			arr[index] = RArr[R];
			++index; ++R;
		}
	}
};


/**	��������
*
*   ʱ�临�Ӷȷ�����ͨ�������T(n) = 2T(n/2) + n���Ӷ�O(nlogn)��������T(n) = T(n-1) + n���Ӷ�O(n^2)
*	ʱ�䣺���O(nlogn)��ƽ��O(nlogn)���O(n^2) -> ��������������ﵽ���Ĭ��shi��һ��Ϊ��Ŧ������£�
*	�ռ䣺O(1) / O(logn)��ԭ��
*	�ȶ��ԣ����ȣ�������Ŧλ�õĹ������п����ƻ��ȶ���
*
*/
template<typename T>
class Quick_Sort {
public:
	static void QuickSort(vector<T>& arr) {
		_QSort(arr, 0, (int)arr.size() - 1);
	}
	static void _QSort(vector<T>& arr, int low, int high) {
		if (low >= high) {
			return;
		}
		int mid = _Partition(arr, low, high);
		_QSort(arr, low, mid - 1);
		_QSort(arr, mid + 1, high);
	}
	static int _Partition(vector<T>& arr, int low, int high) {
		int pivot = arr[low];
		while (low < high) {
			while (low < high && arr[high] >= pivot)	--high;
			arr[low] = arr[high];
			while (low < high && arr[low] <= pivot)		++low;
			arr[high] = arr[low];
		}
		arr[low] = pivot;
		return low;

		/* stimulation begins */
		{
			// 12 16 86 7 97 26 2 56 5 37 -> pivot = 12 = arr[0]
			// L						R
			/* first round */
			// 5  16 86 7 97 26 2 56 5 37
			// L                       R
			// 5  16 86 7 97 26 2 56 16 37
			//    L                  R
			/* second round */
			// 5  2  86 7 97 26 2 56 16 37
			//    L             R
			// 5  2  86 7 97 26 86 56 16 37
			//       L          R
			/* third round */
			// 5  2  7  7 97 26 86 56 16 37
			//       L  R
			// 5  2  7  7 97 26 86 56 16 37
			//          LR
			/* out of loop */
			// 5  2  7  12 97 26 86 56 16 37 -> arr[L] = pivot
			//          LR
			/* return L */
		}
		/* stimulation ends */

	}

};


/**	������
*
*	ʱ�䣺1.���ѣ�����ȫ�����������з�Ҷ�Ӳ�ĸ߶ȼ����Ҷ�ӽڵ����йأ�O(n)
*         2.�����ܣ������O(nlogn)��ƽ��O(nlogn)���O(nlogn) -> ��ԭ�����޹أ�n���� * ��Ӧ�߶�logn�����ƣ� = nlogn
*	�ռ䣺O(1)��ԭ��
*	�ȶ��ԣ���Ȼ���ȣ����ܳ��֣���Ϊ���ڵ��n����n+1����ֵ��ȣ������ڵ�n�������˽����������ڵ�n+1û������
*
*/
template<typename T>
class Heap_Sort {
	// �� = ��ȫ���������������ʾ
	// �󶥶ѣ�arr[i] >= arr[2i+1] && arr[i] >= arr[2i+2]  
	// С���ѣ�arr[i] <= arr[2i+1] && arr[i] <= arr[2i+2]
public:
	static void heapify(vector<T>& arr, int parent, int end) {
		int maxChild = 2 * parent + 1;	// initially, maxChild is leftChild of initial parent
		while (maxChild < end) {
			if (maxChild + 1 < end && arr[maxChild + 1] > arr[maxChild]) {
				++maxChild;	// maxChild should be the larger one of leftChild and rightChild, if cur parent's rightChild exists
			}
			if (arr[parent] >= arr[maxChild]) {
				return;		// parent is already greater than maxChild, no need to go on
			}
			swap(arr[parent], arr[maxChild]);
			parent = maxChild;			// move on, make maxChild the new cur parent
			maxChild = 2 * parent + 1;	// make maxChild the leftChild of cur parent
		}
	}
	static void HeapSort(vector<T>& arr) {
		int n = arr.size();
		for (int i = n / 2 - 1; i >= 0; --i) {
			heapify(arr, i, n);
		}
		for (int i = n - 1; i > 0; --i) {
			swap(arr[0], arr[i]);	// max elem to the i-pos
			heapify(arr, 0, i);
		}
	}

};

 
/**	��������ÿ��Ͱֻ�洢��һ��ֵ
*
*	ʱ�䣺1.����ֵ+�����������飺O(n+n)
*         2.����O(k)��k = maxVal - minVal + 1����ͬ
*         3.�ܣ����O(n+k) = ƽ��O(n+k) = �O(n+k) -> ��ԭ�����޹أ�n������������һ��
*	�ռ䣺O(k)�������˸������飬��Ȼ����ԭ�ص�
*	�ȶ��ԣ����ȵ�
*   ȱ�ݣ������ֵ����Сֵ��������ռ������ϱ��ֲ��ѣ��������������޷�����
*
*/
class Counting_Sort {
public:
	static void CountSort(vector<int>& arr) {
		if (arr.empty()) {
			return;
		}
		int minV = arr[0];
		int maxV = arr[0];
		for (auto& elem : arr) {
			if (elem < minV)	minV = elem;
			if (elem > maxV)	maxV = elem;
		}
		vector<int> cntr(maxV - minV + 1);
		for (auto& elem : arr) {
			++cntr[elem-minV];
		}
		int index = 0;
		for (int i = 0; i < maxV - minV + 1; ++i) {
			while (cntr[i]--) {
				arr[index++] = i + minV;
			}
		}
	}
};

/**	Ͱ����ÿ��Ͱ�洢һ����Χ����ֵ
*
*	ʱ�䣺���O(n+k)��ƽ��O(n+k)����˻�Ϊ����O(n^2) -> �����ݷֲ��й�
*	�ռ䣺O(n)
*	�ȶ��ԣ���
*	ȱ�ݣ������ݷֲ�����������ֺܲ�����Ǹ��Ż�
* 
*/
class Bucket_Sort {
public:
	static void BucketSort(vector<int>& arr) {
		if (arr.empty()) {
			return;
		}
		int len = arr.size();
		int minv = arr[0];
		int maxv = arr[0];
		for (auto& elem : arr) {
			if (elem > maxv) {
				maxv = elem;
			}
			if (elem < minv) {
				minv = elem;
			}
		}
		int nBuckets = (maxv - minv) / len + 1; // ������ֵ��Դ���г���ȷ��Ͱ���������Ӷ�ȷ����Χ����
		vector<vector<int>> buckets(nBuckets);
		for (auto& elem : arr) {
			int i = (elem - minv) / len;
			buckets[i].push_back(elem);		// ��Ͱ
		}
		int index = 0;
		for (auto& b : buckets) {
			Quick_Sort<int>::QuickSort(b);	// ÿ��Ͱ����������QuickSort
			for (auto& elem : b) {
				arr[index++] = elem;		// ���η��ص�ԭ����
			}
		}
	}
};

/**	�������򣺸��ݼ�ֵ��ÿλ����������Ͱ
*
*	ʱ�䣺1.����ֵ+�󳤶ȣ�O(n+k)��kָ������ֵ��λ������ͬ
*         2.����O(n*k)
*         3.�ܣ����O(n*k) = ƽ��O(n*k) = �O(n*k) -> ��ԭ�����޹أ�n������������k��
*	�ռ䣺O(n)
*	�ȶ��ԣ���
*	ȱ�ݣ�ֻ�����˷Ǹ���������ʵҲ���ԶԸ������򣬵�������δ���ǣ���Ҫ����ŵ�����Ԫ���л����ĸ������
*/
class Radix_Sort {
public:
	static int maxValueLen(const vector<int>& arr) {
		int maxv = arr[0];
		for (auto& elem : arr) {
			if (elem > maxv) {
				maxv = elem;
			}
		}
		if (0 == maxv) {
			return 1;
		}
		int maxlen = 0;
		while (maxv) {
			++maxlen;
			maxv /= 10;
		}
		return maxlen;
	}

	static void RadixSort(vector<int>& arr) {
		int maxLen = maxValueLen(arr);
		int mod = 10;
		int div = 1;
		for (int i = 0; i < maxLen; ++i,div*=10) {
			vector<vector<int>> bucket(10);
			for (auto& elem : arr) {
				bucket[(elem / div) % mod].push_back(elem);
			}
			int index = 0;
			for (int j = 0; j < 10; ++j) {
				for (int k = 0; k != bucket[j].size(); ++k) {
					arr[index++] = bucket[j][k];
				}
			}
		}
	}
};