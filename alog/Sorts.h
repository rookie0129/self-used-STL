#pragma once

#include<iostream>
#include<vector>
#include<cstdlib>

using std::vector;
using std::swap;

// 随机生成一组数
void arrayGenerator(vector<int>& _arr, int _size) {
	srand(time(nullptr));
	_arr.clear();
	for (int i = 0; i < _size; ++i) {
		_arr.push_back(rand() % 2048 + 1);
	}
}

// 输出数组
void arrayDisplay(vector<int>& _arr) {
	std::cout << std::endl;
	for (int i = 0; i != (int)_arr.size(); ++i) {
		std::cout << _arr[i] << " ";
	}
	std::cout << std::endl;
}

//时间复杂度：对语句频度的上界所做的估量
//空间复杂度：额外内存使用，同样是对上界做估量
//稳定性：具有相同的关键字的记录经过排序后，这些记录的相对次序仍保持不变

/**	冒泡排序
*
*	时间：最好 O(n)，平均O(n^2)，最坏O(n^2) -> 若本来就有序，则达到最好（需设置flag优化）
*	空间：O(1)，原地
*	稳定性：稳定，只对"前>后"的相邻对做前后交换
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


/**	选择排序
*
*	时间：最好 O(n^2) = 平均O(n^2) = 最坏O(n^2) -> 和原数列无关，n + n-1 + n-2 + ... + 2 + 1 = n*(n+1)/2 即 O(n)
*	空间：O(1)，原地
*	稳定性：不稳定，每次将arr[minIndex]和arr[i]做交换，如{ "5",6,7,5,"2",8 }，第一个5和2交换，则第一个5变第二个5了
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


/**	插入排序
*
*	时间：最好 O(n)，平均O(n^2)，最坏O(n^2)	-> 若本来就有序，则达到最好（压根没做插入）
*	空间：O(1)，原地
*	稳定性：稳定，插入时碰到相同的就不再移了
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


/**	希尔排序
*
*	时间：最好O(n)，平均O(n^1.3)，最坏O(n^2) -> 若本来就有序，则达到最好
*	空间：O(1)，原地
*	稳定性：不稳定，因为是隔着gap的，进行移动时，如gap = 2 { 1,"6",5,"5",8, }，6和第二个5交换，则第二个5变第一个5
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


/**	归并排序
*
*   时间复杂度分析：T(n) = 2T(n/2) + n, 应用主方法，代入a=b=2，n^logb(a)=n，分析得T(n) = O(nlogn)
*	时间：最好O(nlogn) = 平均O(nlogn) = 最坏O(nlogn) -> 和原数列无关
*	空间：O(n),非原地
*	稳定性：全稳的，当左边index处的值 = 右边index处的值，取了左边的，故不会破坏稳定性
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


/**	快速排序
*
*   时间复杂度分析：通常情况：T(n) = 2T(n/2) + n，从而O(nlogn)；最坏情况：T(n) = T(n-1) + n，从而O(n^2)
*	时间：最好O(nlogn)，平均O(nlogn)，最坏O(n^2) -> 若本来就有序，则达到最坏（默认shi第一个为枢纽的情况下）
*	空间：O(1) / O(logn)，原地
*	稳定性：不稳，调整枢纽位置的过程中有可能破坏稳定性
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


/**	堆排序
*
*	时间：1.建堆：与完全二叉树中所有非叶子层的高度及其非叶子节点数有关，O(n)
*         2.排序（总）：最好O(nlogn)，平均O(nlogn)，最坏O(nlogn) -> 与原数列无关，n个数 * 相应高度logn（近似） = nlogn
*	空间：O(1)，原地
*	稳定性：显然不稳，可能出现：作为父节点的n处和n+1处的值相等，但父节点n向下做了交换，而父节点n+1没做交换
*
*/
template<typename T>
class Heap_Sort {
	// 堆 = 完全二叉树，用数组表示
	// 大顶堆：arr[i] >= arr[2i+1] && arr[i] >= arr[2i+2]  
	// 小顶堆：arr[i] <= arr[2i+1] && arr[i] <= arr[2i+2]
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

 
/**	计数排序：每个桶只存储单一键值
*
*	时间：1.找最值+建立计数数组：O(n+n)
*         2.排序：O(k)，k = maxVal - minVal + 1，下同
*         3.总：最好O(n+k) = 平均O(n+k) = 最坏O(n+k) -> 与原数列无关，n个数都给你来一遍
*	空间：O(k)，借助了辅助数组，显然不是原地的
*	稳定性：很稳的
*   缺陷：若最大值与最小值差距过大，则空间性能上表现不佳；若非整数，则无法计数
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

/**	桶排序：每个桶存储一定范围的数值
*
*	时间：最好O(n+k)，平均O(n+k)，最坏退化为快排O(n^2) -> 与数据分布有关
*	空间：O(n)
*	稳定性：稳
*	缺陷：若数据分布不均，则表现很差，几乎是负优化
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
		int nBuckets = (maxv - minv) / len + 1; // 根据最值和源数列长度确定桶的数量，从而确定范围划分
		vector<vector<int>> buckets(nBuckets);
		for (auto& elem : arr) {
			int i = (elem - minv) / len;
			buckets[i].push_back(elem);		// 分桶
		}
		int index = 0;
		for (auto& b : buckets) {
			Quick_Sort<int>::QuickSort(b);	// 每个桶排序，这里用QuickSort
			for (auto& elem : b) {
				arr[index++] = elem;		// 依次返回到原数组
			}
		}
	}
};

/**	基数排序：根据键值的每位数字来分配桶
*
*	时间：1.找最值+求长度：O(n+k)，k指的是最值的位数，下同
*         2.排序：O(n*k)
*         3.总：最好O(n*k) = 平均O(n*k) = 最坏O(n*k) -> 与原数列无关，n个数都给你来k遍
*	空间：O(n)
*	稳定性：稳
*	缺陷：只考虑了非负整数（其实也可以对负数排序，但这里暂未考虑）；要求待排的序列元素有基数的概念存在
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