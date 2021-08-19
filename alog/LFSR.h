#pragma once

#include<iostream>
#include<vector>
#include<string>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;

/* 
 * 序列密码算法
 * LFSR
 * 可以细化到bit，偷懒了只是到byte
 */
namespace LFSR {
	/* 重要参数 */
	static char R0 = 1;
	static char R1 = 0;
	static char R2 = 1;
	static char R3 = 0;
	static char g4 = 1;
	static char g3 = 0;
	static char g2 = 1;
	static char g1 = 1;
	static char g0 = 1;

	/* 线性移位寄存器功能演示 */
	void LinearMoveRegister(vector<int>& keyArray) {
		cout << "Step0 --- " << "R0=" << R0 << " R1=" << R1 << " R2=" << R2 << " R3= " << R3 << endl;
		for (int i = 1; i <= 15; ++i) {
			int outputBit = R0;
			if (g1)	outputBit ^= R1;
			if (g2)	outputBit ^= R2;
			if (g3)	outputBit ^= R3;
			R0 = R1;
			R1 = R2;
			R2 = R3;
			R3 = outputBit;
			keyArray.push_back(outputBit);
			cout << "Step" << i << " --- R0=" << R0 << " R1=" << R1 << " R2=" << R2 << " R3= " << R3 << endl;
		}
	}

	/* 必要的初始化，参考whu张焕国老师 */
	void Initialize() {
		R0 = 1;
		R1 = 1;
		R2 = 1;
		R3 = 1;
		g4 = 1;
		g3 = 0;
		g2 = 0;
		g1 = 1;
		g0 = 1;
	}

	/* 加密 <-> 解密：对合运算 */
	void Encryption(const string& plaintext, string& ciphertext) {
		Initialize();

		for (int i = 0; i < plaintext.size(); ++i) {
			char outputBit = R0;
			if (g1)	outputBit ^= R1;
			if (g2)	outputBit ^= R2;
			if (g3)	outputBit ^= R3;
			R0 = R1;
			R1 = R2;
			R2 = R3;
			R3 = outputBit;
			ciphertext[i] = plaintext[i] ^ outputBit ^ 0x55;
		}
	}

	/* 序列式加解密演示 */
	void DisplayEncryption() {
		string plaintext = "2.054qz,mcjdlkwshdknas%$ad.13#Qeas";
		string ciphertext(plaintext);

		Encryption(plaintext, ciphertext);
		cout << "加密:" << endl;
		for (auto& text : plaintext) {
			cout << text;
		}
		cout << endl;
		for (auto& text : ciphertext) {
			cout << text;
		}
		cout << endl;

		Encryption(ciphertext, plaintext);
		cout << "解密:" << endl;
		for (auto& text : ciphertext) {
			cout << text;
		}
		cout << endl;
		for (auto& text : plaintext) {
			cout << text;
		}
		cout << endl;
	}

	/* 把密码都给我加密咯 */
	void EncryptAndDecryptMyKeys() {
		//ifstream fin;
		//ofstream fout;
		//string plainText;
		//string cypherText;

		/* 加密部分 */
		//fin.open("mykeys.txt");
		//fout.open("encrypted.txt");

		//stringstream buf1;
		//buf1 << fin.rdbuf();
		//plainText = buf1.str();
		//cypherText = plainText;

		//LFSR::Encryption(plainText, cypherText);

		//fout << cypherText;

		//fin.close();
		//fout.close();

		/* 解密部分 */
		//fin.open("encrypted.txt");
		//fout.open("decrypted.txt");

		//stringstream buf2;
		//buf2 << fin.rdbuf();
		//plainText = buf2.str();
		//cypherText = plainText;
		//LFSR::Encryption(plainText, cypherText);

		//fout << cypherText;

		//fin.close();
		//fout.close();
	}
}