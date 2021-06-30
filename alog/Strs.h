#pragma once

#include<vector>
#include<string>
#include<algorithm>

using std::vector;
using std::string;


// 做题过程中碰到的字符串处理相关算法

/* kmp 字符串匹配 */
class KMP_MATCH {
	//public:
	//
	//	static vector<int> CalcNextArray(const string& s) {
	//		int len = s.size();
	//		//vector<int> next{-1,0,0,0,0,1}; // max common prefix_suffix:{0,0,0,0,1,2};
	//		vector<int> next(len, -1);
	//
	//		int i = 0, j = -1;
	//		while (i < len - 1) {
	//			if (-1 == j || s[i] == s[j]) {
	//				++i;
	//				++j;
	//				next[i] = j;
	//			}
	//			else {
	//				j = next[j];
	//			}
	//		}
	//		return next;
	//	}
	//
	//	static int KmpMatch(const string& s, const string& t) {
	//		vector<int> next = CalcNextArray(t);
	//		int m = s.size();
	//		int n = t.size();
	//
	//		int i = 0, j = 0;
	//		while (i < m && j < n) {
	//			if (-1 == j || s[i] == t[j]) {
	//				++i;
	//				++j;
	//			}
	//			else {
	//				j = next[j];
	//			}
	//		}
	//
	//		return j == n ? i - n : -1;
	//	}
};

/* manacher 最长回文子串 */
class Manacher {
	//public:
	//
	//	static string LongestPalindromicSubstr(const string& s) {
	//		/* 预处理 */
	//		int n = s.size();
	//		string str(2 * n + 3, '#'); //例：有"ababa"，处理后为 "@#a#b#a#b#a#$"，此时"#a#b#a#b#a#"为最长回文串
	//									//    其右边界rightBound = 12，对称中点centerIndex = 6
	//									//    其臂长为 rightBound - centerIndex = 6
	//									//    注意右边界不包括在臂长内 out of arm's reach
	//		str.front() = '@';  // dummy head，奇怪的符号，防溢出
	//		str.back()  = '$';  // dummy tail，奇怪的符号，防溢出
	//		for (int i = 0; i < n; ++i) {
	//			str[i * 2 + 2] = s[i];
	//		}
	//		n = str.size();
	//
	//		/* 马拉车 */
	//		vector<int> P(n);        // P[i] = 以i为中心的最长回文串的"臂长"
	//		int palindromeCenter = 0;// 当前对称中心
	//		int rightBound = 0;      // 当前最远右边界
	//		for (int i = 1; i < n - 1; ++i) {
	//			//越界：1，没越界：min（i以palindromeCenter为对称中心的对称点的P值，i到右边界的臂长）
	//			P[i] = i < rightBound ? min(P[palindromeCenter - (i - palindromeCenter)], rightBound - i) : 1;
	//			while (str[i - P[i]] == str[i + P[i]] && ++P[i]);  // 短路原理 && 有dummy，不用担心下标溢出
	//			if (i + P[i] > rightBound) {	// 若超出，更新右边界与对称中心
	//				palindromeCenter = i;
	//				rightBound = i + P[i];
	//			}
	//		}
	//
	//		/* 找答案 */
	//		int longestLen = 0;  // 最长回文串的"臂长"长度
	//		int centerIndex = 0; // 最长回文串的对称点坐标
	//		for (int i = 1; i < n - 1; ++i) {
	//			if (P[i] > longestLen) {
	//				longestLen = P[i];
	//				centerIndex = i;
	//			}
	//		}
	//		// 1.关于长度的讨论
	//		//   因为 2 * longestArmLen - 1 = longestPalindrome_newStr = 2 * longestPalindrome_originStr + 1
	//		//   即有 longestArmLen = longestPalindrome_originStr + 1
	//		//   而此处 longestLen 实为 longestArmLen，故欲求得 longestPalindrome_originStr，longestLen-1即是
	//		// 2.关于下标的讨论
	//		//   注意下标的对应关系，str[i*2+2] = s[i]，即str[(i+1)*2] = s[i]，即str[i/2-1] = s[i]
	//		//   在str中，无论centerIndex处是否为'#'，左右边界必然是'#，而s中并没有'#'
	//		//   故str的左边界不被视为起点，左边界往右1个单位才是，即(centerIndex-longestLen+1)+1
	//		//   从而s的起点对应为(centerIndex-longestLen+2)/2-1 = (centerIndex-longestLen)/2
	//		return s.substr((centerIndex-longestLen)/2, longestLen-1);
	//	}
	//
	//	void test_manacher() {
	//		//string s = "cabaabacczxcz";
	//		//cout << s << " : " << Manacher::LongestPalindromicSubstr(s) << endl;
	//		//s = "zcxzcababac";
	//		//cout << s << " : " << Manacher::LongestPalindromicSubstr(s) << endl;
	//		//s = "dasdsaddsc";
	//		//cout << s << " : " << Manacher::LongestPalindromicSubstr(s) << endl;
	//		//s = "aaaaaaaaaaaaaa";
	//		//cout << s << " : " << Manacher::LongestPalindromicSubstr(s) << endl;
	//		//s = "a";
	//		//cout << s << " : " << Manacher::LongestPalindromicSubstr(s) << endl;
	//		//s = "dasdadasdafzxxv";
	//		//cout << s << " : " << Manacher::LongestPalindromicSubstr(s) << endl;
	//		//s = "asdfgjhgfsdfghjhgfdkjhgf";
	//		//cout << s << " : " << Manacher::LongestPalindromicSubstr(s) << endl;
	//		//s = "eawfgdhgzsx";
	//		//cout << s << " : " << Manacher::LongestPalindromicSubstr(s) << endl;
	//		//s = "zkleouijfkzzioashdlnkda";
	//		//cout << s << " : " << Manacher::LongestPalindromicSubstr(s) << endl;
	//		//s = "dasfdghdgfsd";
	//		//cout << s << " : " << Manacher::LongestPalindromicSubstr(s) << endl;
	//	}
};

/* 下一个字典序更大的排列 && 字符串的所有排列 */
class Permutations {
public:
	// 下一个字典序更大的排列
	bool next_permutation(vector<string>& ans, string& s, int& n) {
		for (int i = n - 2; i >= 0; --i) {
			if (s[i] < s[i + 1]) {
				int k = i + 1;
				for (; k < n && s[i] < s[k]; ++k);
				std::swap(s[i], s[k - 1]);
				sort(s.begin() + i + 1, s.end());
				ans.push_back(s);
				return true;
			}
		}
		return false;
	}
	// 字符串的所有排列(按字符串的字典序排序 / 某一排列中允许重复元素，但排列不允许重复)
	vector<string> permutation(string s) {
		vector<string> ans;
		int n = s.size();
		sort(s.begin(), s.end());
		ans.push_back(s);
		while (next_permutation(ans, s, n));
		return ans;
	}
};

/* 二叉树 <--> 字符串（序列化与反序列化） */
//struct TreeNode {
//    int val;
//    TreeNode* left;
//    TreeNode* right;
//    TreeNode(int x) :val(x), left(nullptr), right(nullptr) {}
//};
//
//class Codec {
//public:
//    string serialize(TreeNode* root) {
//        if (root == nullptr) {
//            return "[]";
//        }
//        queue<TreeNode*> q; // queue - BFS
//        q.push(root);
//        string ans = "[";
//        while (!q.empty()) {
//            int cur = q.size();
//            while (cur--) {
//                TreeNode* node = q.front();
//                q.pop();
//                if (node) {
//                    ans += (to_string(node->val) + ",");    // 非空则"val," 且继续考察其孩子
//                    q.push(node->left);
//                    q.push(node->right);
//                }
//                else {
//                    ans += ("null,");   // 空即"null," 且不再考虑孩子（压根没有
//                }
//            }
//        }
//        int trueEnd = 0;
//        for (int nullsIndex = ans.size() - 5; nullsIndex >= 0; nullsIndex -= 5) {
//            if (ans.substr(nullsIndex, 5) == "null,") {
//                trueEnd = nullsIndex - 1;
//            }
//            else {
//                break;
//            }
//        }
//        return ans.substr(0, trueEnd) + "]";
//    }
//
//    vector<string> string2vecstring(string s) {
//        vector<string> vsTree;
//        int n = s.size() - 1;
//        int left = 1;
//        while (left < n) {
//            int right = left;
//            while (right < n && s[right] != ',') {
//                ++right;
//            }
//            vsTree.push_back(s.substr(left, right - left));
//            left = right + 1;
//        }
//
//        for (const auto& elem : vsTree) {
//            cout << elem << endl;
//        }
//        return vsTree;
//    }
//
//    TreeNode* deserialize(string s) {
//        vector<string> tree(string2vecstring(s));
//        if (tree.empty()) {
//            return nullptr;
//        }
//        queue<TreeNode*> q;
//        TreeNode* root = new TreeNode(stoi(tree[0]));
//        q.push(root);
//        int len = tree.size();
//        int index = 1;
//        while (!q.empty()) {
//            TreeNode* cur = q.front();
//            q.pop();
//            if (index < len && tree[index] != "null") {
//                cur->left = new TreeNode(stoi(tree[index]));
//                q.push(cur->left);
//            }
//            ++index;
//            if (index < len && tree[index] != "null") {
//                cur->right = new TreeNode(stoi(tree[index]));
//                q.push(cur->right);
//            }
//            ++index;
//        }
//
//        return root;
//    }
//
//};
