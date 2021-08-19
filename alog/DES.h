#pragma once

#include<iostream>
#include<iomanip>
#include<vector>
#include<string>
#include<bitset>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::bitset;

/*
 * 分组密码算法
 * DES
 * 细化到bit，每64bit为一组做加解密
 */
namespace DES {
	/* 密钥的C部分 */
	const static int C_Table[28] = {
		57, 49, 41, 33, 25, 17, 9,
		1, 58, 50, 42, 34, 26, 18,
		10, 2, 59, 51, 43, 35, 27,
		19, 11, 3, 60, 52, 44, 36
	};

	/* 密钥的D部分 */
	const static int D_Table[28] = {
		63, 55, 47, 39, 31, 23, 15,
		7, 62, 54, 46, 38, 30, 22,
		14, 6, 61, 53, 45, 37, 29,
		21, 13, 5, 28, 20, 12, 4
	};

	/* 需循环左移的位数 */
	const static int Moves[16] = { 1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1 };

	/* K */
	const static int K_Table[48] = {
		14,17,11,24,1,5,3,28,15,6,21,10,
		23,19,12,4,26,8,16,7,27,20,13,2,
		41,52,31,37,47,55,30,40,51,45,33,48,
		44,49,39,56,34,53,46,42,50,36,29,32
	};

	/* 初始IP置换 */
	const static int IP[64] = {
		58,50,42,34,26,18,10,2,
		60,52,44,36,28,20,12,4,
		62,54,46,38,30,22,14,6,
		64,56,48,40,32,24,16,8,
		57,49,41,33,25,17,9,1,
		59,51,43,35,27,19,11,3,
		61,53,45,37,29,21,13,5,
		63,55,47,39,31,23,15,7
	};

	/* 选择运算E */
	const static int E_Table[48] = {
		32,1,2,3,4,5,4,5,6,7,8,9,
		8,9,10,11,12,13,12,13,14,15,16,17,
		16,17,18,19,20,21,20,21,22,23,24,25,
		24,25,26,27,28,29,28,29,30,31,32,1
	};

	/* 逆IP置换 */
	const static int revIP[64] = {
		40,8,48,16,56,24,64,32,
		39,7,47,15,55,23,63,31,
		38,6,46,14,54,22,62,30,
		37,5,45,13,53,21,61,29,
		36,4,44,12,52,20,60,28,
		35,3,43,11,51,19,59,27,
		34,2,42,10,50,18,58,26,
		33,1,41,9,49,17,57,25
	};

	/* S盒 */
	const static int SBox[8][4][16] = {
		{	// S1
			{14,  4, 13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7},
			{ 0, 15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8},
			{ 4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0},
			{15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13}
		},
		{	// S2
			{15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10},
			{ 3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5},
			{ 0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2, 15},
			{13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9}
		},
		{	// S3
			{10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8},
			{13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1},
			{13,  6,  4,  9,  8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7},
			{ 1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12}
		},
		{	// S4
			{ 7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15},
			{13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9},
			{10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4},
			{ 3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14}
		},
		{	// S5
			{ 2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9},
			{14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6},
			{ 4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14},
			{11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3}
		},
		{	// S6
			{12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11},
			{10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8},
			{ 9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6},
			{ 4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13}
		},
		{	// S7
			{ 4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1},
			{13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6},
			{ 1,  4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2},
			{ 6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12}
		},
		{	// S8
			{13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7},
			{ 1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2},
			{ 7, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8},
			{ 2,  1, 14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11}
		}
	};

	/* P置换 */
	const static int P_Table[32] = {
		16,7,20,21,29,12,28,17,
		1,15,23,26,5,18,31,10,
		2,8,24,14,32,27,3,9,
		19,13,30,6,22,11,4,25
	};

	/* 常用参数 */
	constexpr size_t KeyLen = 64;
	constexpr size_t MsgLen = 64;
	constexpr size_t EncLen = 64;
	constexpr size_t CDLen = (KeyLen - 8) / 2;
	constexpr size_t LRLen = KeyLen / 2;
	constexpr size_t SubKeyLen = 48;
	constexpr int SubKeyNum = 16;
	static string strOutput;
	constexpr bool ENCRYPTION = true;
	constexpr bool DECRYPTION = false;

	/* 生成子密钥组 */
	void GenerateSubKeys(const bitset<KeyLen>& key, vector<bitset<SubKeyLen>>& subKeys) {
		bitset<CDLen> C;
		bitset<CDLen> D;
		for (int i = 0; i < CDLen; ++i) {	// 置换选择1
			//C[CDLen-i-1] = key[KeyLen - C_Table[i]];
			C[i] = key[C_Table[i] - 1];
			//D[CDLen-i-1] = key[KeyLen - D_Table[i]];
			D[i] = key[D_Table[i] - 1];
		}
		// debug info
		strOutput = key.to_string();
		reverse(strOutput.begin(), strOutput.end());
		cout << "密钥：" << strOutput << endl;
		cout << "置换选择1: " << endl;
		strOutput = C.to_string();
		reverse(strOutput.begin(), strOutput.end());
		cout << "C0: " << strOutput << endl;
		strOutput = D.to_string();
		reverse(strOutput.begin(), strOutput.end());
		cout << "D0: " << strOutput << endl;
		//

		for (int i = 1; i <= 16; ++i) {
			//C = C << Moves[i - 1] | C >> (CDLen - Moves[i - 1]);	// 循环移位
			//D = D << Moves[i - 1] | D >> (CDLen - Moves[i - 1]);	// 循环移位
			C = C >> Moves[i - 1] | C << (CDLen - Moves[i - 1]);	// 循环移位
			D = D >> Moves[i - 1] | D << (CDLen - Moves[i - 1]);	// 循环移位

			bitset<SubKeyLen> curSubKey;
			for (int j = 0; j < SubKeyLen; ++j) {	// 置换选择2
				if (j < SubKeyLen / 2) {
					//tmpSubKey[SubKeyLen - j - 1] = C[CDLen - K_Table[j]];
					curSubKey[j] = C[K_Table[j] - 1];
				}
				else {
					//tmpSubKey[SubKeyLen - j - 1] = D[CDLen - K_Table[j] + 28];
					curSubKey[j] = D[K_Table[j] - 28 - 1];
				}
			}
			subKeys[i - 1] = curSubKey;
			// debug info
			cout << "N=" << i << endl;
			strOutput = C.to_string();
			reverse(strOutput.begin(), strOutput.end());
			cout << "C" << i << ": " << strOutput << endl;
			strOutput = D.to_string();
			reverse(strOutput.begin(), strOutput.end());
			cout << "D" << i << ": " << strOutput << endl;
			strOutput = curSubKey.to_string();
			reverse(strOutput.begin(), strOutput.end());
			cout << "子密钥" << i << ": " << strOutput << endl;
			//
		}
	}

	/* 初始IP置换 */
	void InitialPemute(bitset<MsgLen>& msg, bool flag = ENCRYPTION) {
		bitset<MsgLen> tmp = msg;
		for (int i = 0; i < MsgLen; ++i) {
			//msg[MsgLen - i - 1] = tmp[MsgLen - IP[i]];
			msg[i] = tmp[IP[i] - 1];
		}
		// debug info
		strOutput = tmp.to_string();
		reverse(strOutput.begin(), strOutput.end());
		if (flag == ENCRYPTION) {
			cout << "明文：" << strOutput << endl;
		}
		else if (flag == DECRYPTION) {
			cout << "密文：" << strOutput << endl;
		}
		strOutput = msg.to_string();
		reverse(strOutput.begin(), strOutput.end());
		cout << "初始IP置换：" << strOutput << endl;
		//
	}

	/* 逆初始IP置换 */
	void RevInitialPemute(bitset<EncLen>& ecp, bool flag = ENCRYPTION) {
		bitset<EncLen> tmp = ecp;
		for (int i = 0; i < EncLen; ++i) {
			//ecp[EncLen - i - 1] = tmp[EncLen - revIP[i]];
			ecp[i] = tmp[revIP[i] - 1];
		}
		// debug info
		strOutput = ecp.to_string();
		reverse(strOutput.begin(), strOutput.end());
		cout << "逆IP置换：" << strOutput << endl;
		strOutput = ecp.to_string();
		reverse(strOutput.begin(), strOutput.end());
		if (flag == ENCRYPTION) {
			cout << "密文：" << strOutput << endl;
		}
		else if (flag == DECRYPTION) {
			cout << "明文：" << strOutput << endl;
		}
		//
	}

	/* 输入分割为L和R */
	void SplitLeftRight(const bitset<MsgLen>& msg, bitset<LRLen>& L, bitset<LRLen>& R) {
		for (int i = 0; i < MsgLen / 2; ++i) {
			R[i] = msg[i + MsgLen / 2];
			L[i] = msg[i];
		}
		// debug info
		//strOutput = L.to_string();
		//reverse(strOutput.begin(), strOutput.end());
		//cout << "L: " << strOutput << endl;
		//strOutput = R.to_string();
		//reverse(strOutput.begin(), strOutput.end());
		//cout << "R: " << strOutput << endl;
		//
	}

	/* L和R合并为输出 */
	void MergeLeftRight(bitset<KeyLen>& msg, const bitset<LRLen>& L, const bitset<LRLen>& R) {
		for (int i = 0; i < LRLen; ++i) {
			msg[i] = L[i];
			msg[i + LRLen] = R[i];
		}
		// debug info

		//
	}

	/* 扩展LR，由32位到48位 */
	void ExtendLeftRight(const bitset<LRLen>& original, bitset<SubKeyLen>& ext) {
		for (int i = 0; i < SubKeyLen; ++i) {
			ext[i] = original[E_Table[i] - 1];
		}
	}

	/* 基本轮函数f */
	void RoundFunction(bitset<LRLen>& L, bitset<LRLen>& R, const bitset<SubKeyLen>& subKey, int seq) {
		// debug info
		//cout << "N=" << seq << endl;
		//cout << "轮F函数：" << endl;
		//strOutput = R.to_string();
		//reverse(strOutput.begin(), strOutput.end());
		//cout << "32位输入：" << strOutput << endl;
		//

		bitset<SubKeyLen> ext;
		ExtendLeftRight(R, ext);
		// debug info
		//strOutput = ext.to_string();
		//reverse(strOutput.begin(), strOutput.end());
		//cout << "选择运算：" << strOutput << endl;
		//

		for (int i = 0; i < SubKeyLen; ++i) {	// 按位亦或
			ext[i] = ((ext[i] && subKey[i]) ? 0 : (ext[i] ? 1 : subKey[i]));
		}
		// debug info
		//strOutput = subKey.to_string();
		//reverse(strOutput.begin(), strOutput.end());
		//cout << "子密钥K：" << strOutput << endl;
		//strOutput = ext.to_string();
		//reverse(strOutput.begin(), strOutput.end());
		//cout << "子密钥加：" << strOutput << endl;
		//

		bitset<32> tmpRes;
		for (int i = 0, a = 0; i < 48; i += 6, a += 4) {
			int j = ext[i] * 2 + ext[i + 5];	// b1b6
			int k = ext[i + 1] * 8 + ext[i + 2] * 4 + ext[i + 3] * 2 + ext[i + 4];	// b2b3b4b5
			int boxElem = SBox[i / 6][j][k];
			for (int index = 0; index < 4; ++index) {
				tmpRes[a + index] = (true && (boxElem & (1 << (3 - index))));	// 注意是反着来的
			}
		}
		// debug info
		//strOutput = tmpRes.to_string();
		//reverse(strOutput.begin(), strOutput.end());
		//cout << "S盒：" << strOutput << endl;
		//

		bitset<32> res;
		for (int i = 0; i < 32; ++i) {
			res[i] = tmpRes[P_Table[i] - 1];
		}
		// debug info
		//strOutput = res.to_string();
		//reverse(strOutput.begin(), strOutput.end());
		//cout << "P置换：" << strOutput << endl;
		//

		bitset<LRLen> tmpL(L);
		L = R;
		for (int i = 0; i < LRLen; ++i) {	// 按位亦或
			tmpL[i] = ((tmpL[i] && res[i]) ? 0 : (tmpL[i] ? 1 : res[i]));
		}
		R = tmpL;
		// debug info
		//strOutput = L.to_string();
		//reverse(strOutput.begin(), strOutput.end());
		//cout << "L: " << strOutput << endl;
		//strOutput = R.to_string();
		//reverse(strOutput.begin(), strOutput.end());
		//cout << "R: " << strOutput << endl;
		//

	}

	/* 对合运算，加密和解密算法一致 */
	void EncryptionDecryption(bitset<KeyLen>& key, bitset<MsgLen>& msg, bitset<EncLen>& ecp, const vector<bitset<SubKeyLen>>& subKeys, bool flag = ENCRYPTION) {
		InitialPemute(msg, flag);

		bitset<LRLen> L, R;
		SplitLeftRight(msg, L, R);

		for (int i = 1; i <= 16; ++i) {
			RoundFunction(L, R, subKeys[i - 1], i);
		}

		MergeLeftRight(ecp, R, L);

		RevInitialPemute(ecp, flag);
	}

	/* 加密解密的运行过程展示 */
	void DisplayEncryptionDecryption() {// 王焕国老师给的例子比较特殊，认为前面先看到的为低位，为此，需要逆反一下
		string s("0011000100110010001100110011010000110101001101100011011100111000");
		std::reverse(s.begin(), s.end());
		bitset<KeyLen> key(s);	// key，由用户选择

		s = string("0011000000110001001100100011001100110100001101010011011000110111");
		std::reverse(s.begin(), s.end());
		bitset<MsgLen> msg(s);	// message，由用户给出

		bitset<EncLen> ecp;		// currently unknown encrypted code

		vector<bitset<SubKeyLen>> subKeys(SubKeyNum);
		GenerateSubKeys(key, subKeys);

		EncryptionDecryption(key, msg, ecp, subKeys, ENCRYPTION);

		std::reverse(subKeys.begin(), subKeys.end());

		EncryptionDecryption(key, ecp, msg, subKeys, DECRYPTION);
	}
}