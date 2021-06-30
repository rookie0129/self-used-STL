#pragma once

#include<vector>
#include<string>
#include<algorithm>

using std::vector;
using std::string;


// ����������������ַ�����������㷨

/* kmp �ַ���ƥ�� */
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

/* manacher ������Ӵ� */
class Manacher {
	//public:
	//
	//	static string LongestPalindromicSubstr(const string& s) {
	//		/* Ԥ���� */
	//		int n = s.size();
	//		string str(2 * n + 3, '#'); //������"ababa"�������Ϊ "@#a#b#a#b#a#$"����ʱ"#a#b#a#b#a#"Ϊ����Ĵ�
	//									//    ���ұ߽�rightBound = 12���Գ��е�centerIndex = 6
	//									//    ��۳�Ϊ rightBound - centerIndex = 6
	//									//    ע���ұ߽粻�����ڱ۳��� out of arm's reach
	//		str.front() = '@';  // dummy head����ֵķ��ţ������
	//		str.back()  = '$';  // dummy tail����ֵķ��ţ������
	//		for (int i = 0; i < n; ++i) {
	//			str[i * 2 + 2] = s[i];
	//		}
	//		n = str.size();
	//
	//		/* ������ */
	//		vector<int> P(n);        // P[i] = ��iΪ���ĵ�����Ĵ���"�۳�"
	//		int palindromeCenter = 0;// ��ǰ�Գ�����
	//		int rightBound = 0;      // ��ǰ��Զ�ұ߽�
	//		for (int i = 1; i < n - 1; ++i) {
	//			//Խ�磺1��ûԽ�磺min��i��palindromeCenterΪ�Գ����ĵĶԳƵ��Pֵ��i���ұ߽�ı۳���
	//			P[i] = i < rightBound ? min(P[palindromeCenter - (i - palindromeCenter)], rightBound - i) : 1;
	//			while (str[i - P[i]] == str[i + P[i]] && ++P[i]);  // ��·ԭ�� && ��dummy�����õ����±����
	//			if (i + P[i] > rightBound) {	// �������������ұ߽���Գ�����
	//				palindromeCenter = i;
	//				rightBound = i + P[i];
	//			}
	//		}
	//
	//		/* �Ҵ� */
	//		int longestLen = 0;  // ����Ĵ���"�۳�"����
	//		int centerIndex = 0; // ����Ĵ��ĶԳƵ�����
	//		for (int i = 1; i < n - 1; ++i) {
	//			if (P[i] > longestLen) {
	//				longestLen = P[i];
	//				centerIndex = i;
	//			}
	//		}
	//		// 1.���ڳ��ȵ�����
	//		//   ��Ϊ 2 * longestArmLen - 1 = longestPalindrome_newStr = 2 * longestPalindrome_originStr + 1
	//		//   ���� longestArmLen = longestPalindrome_originStr + 1
	//		//   ���˴� longestLen ʵΪ longestArmLen��������� longestPalindrome_originStr��longestLen-1����
	//		// 2.�����±������
	//		//   ע���±�Ķ�Ӧ��ϵ��str[i*2+2] = s[i]����str[(i+1)*2] = s[i]����str[i/2-1] = s[i]
	//		//   ��str�У�����centerIndex���Ƿ�Ϊ'#'�����ұ߽��Ȼ��'#����s�в�û��'#'
	//		//   ��str����߽粻����Ϊ��㣬��߽�����1����λ���ǣ���(centerIndex-longestLen+1)+1
	//		//   �Ӷ�s������ӦΪ(centerIndex-longestLen+2)/2-1 = (centerIndex-longestLen)/2
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

/* ��һ���ֵ����������� && �ַ������������� */
class Permutations {
public:
	// ��һ���ֵ�����������
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
	// �ַ�������������(���ַ������ֵ������� / ĳһ�����������ظ�Ԫ�أ������в������ظ�)
	vector<string> permutation(string s) {
		vector<string> ans;
		int n = s.size();
		sort(s.begin(), s.end());
		ans.push_back(s);
		while (next_permutation(ans, s, n));
		return ans;
	}
};

/* ������ <--> �ַ��������л��뷴���л��� */
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
//                    ans += (to_string(node->val) + ",");    // �ǿ���"val," �Ҽ��������亢��
//                    q.push(node->left);
//                    q.push(node->right);
//                }
//                else {
//                    ans += ("null,");   // �ռ�"null," �Ҳ��ٿ��Ǻ��ӣ�ѹ��û��
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
