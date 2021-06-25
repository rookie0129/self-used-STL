#pragma once

#include<iostream>
#include<vector>
#include<tuple>
#include<algorithm>

using std::vector;
using std::tuple;
using std::get;
using std::make_tuple;

namespace UF {
	class UnionFind;
	vector<tuple<int, int, int>> MinSpanTree_Kruskal(vector<tuple<int, int, int>> edges, int nNodes);
	bool UnionFindTest();
}

// 并查集，精巧的数据结构
class UF::UnionFind {
	vector<int> ancestors;
	int nMembers;
public:
	void init_(int n) {
		nMembers = n;
		ancestors.resize(nMembers+1);
		for (int i = 0; i < nMembers; ++i) {
			ancestors[i] = i;
		}
	}

	int find_(int x) {
		if (x == ancestors[x]) {
			return x;
		}
		return find_(ancestors[x]);
	}

	bool union_(int x, int y) {
		x = find_(x);
		y = find_(y);
		if (x == y) {
			return false;
		}
		ancestors[y] = x;
		return true;
	}
};


// 基于并查集的克鲁斯卡尔算法
vector<tuple<int, int, int>>  UF::MinSpanTree_Kruskal(vector<tuple<int, int, int>> edges, int nNodes) {
	std::sort(edges.begin(), edges.end(), [](tuple<int, int, int>& lhs, tuple<int, int, int>& rhs) {
		return get<2>(lhs) < get<2>(rhs); } );
	UnionFind uf;
	uf.init_(nNodes);
	vector<tuple<int, int, int>> minSpanTree;
	for (auto& tup : edges) {
		int leftNode = get<0>(tup);
		int rightNode = get<1>(tup);
		if (uf.union_(leftNode, rightNode)) {
			minSpanTree.push_back(tup);
		}
	}
	return minSpanTree;
}

// 未给出完整的图结构，仅给出图的所有边
bool UF::UnionFindTest() {
	vector<tuple<int, int, int>> edges;
	edges.push_back(make_tuple(1, 2, 6));
	edges.push_back(make_tuple(1, 3, 1));
	edges.push_back(make_tuple(1, 4, 5));
	edges.push_back(make_tuple(2, 3, 5));
	edges.push_back(make_tuple(2, 5, 3));
	edges.push_back(make_tuple(3, 4, 5));
	edges.push_back(make_tuple(3, 5, 6));
	edges.push_back(make_tuple(3, 6, 4));
	edges.push_back(make_tuple(4, 6, 2));
	edges.push_back(make_tuple(5, 6, 6));

	vector<tuple<int, int, int>> t = MinSpanTree_Kruskal(edges, 6);
	int total = 0;
	for (auto& tup : t) {
		total += get<2>(tup);
		std::cout << "[" << get<0>(tup) << "," << get<1>(tup) << "] : " << get<2>(tup) << std::endl;
	}
	std::cout << "MinSpanTree's weight: " << total << std::endl;
	return true;
}