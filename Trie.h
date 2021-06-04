#pragma once

#include<iostream>
#include<vector>
#include<string>

/* A node in Trie, we select one to be the final root through which we do the CRUD */
class TrieNode
{
private:
	bool ended;
	char data;
	std::vector<TrieNode*> children;
public:
	TrieNode(char c = '\0', bool b = false, std::vector<TrieNode*> vec = std::vector<TrieNode*>()) :ended(b), data(c), children(vec) {}
	TrieNode(const TrieNode& t) :ended(t.ended), data(t.data), children(t.children) {}
	TrieNode(const std::initializer_list<std::string>& list) : ended(false), data('\0'), children(std::vector<TrieNode*>()) { this->create(list); }
	~TrieNode() { std::cout << "TrieNode: " << (this->data=='\0' ? '0' :this->data) <<" destroyed" << std::endl; }
	
	char getData() { return data; }
	char& getDataRef() { return data; }

	std::vector<TrieNode*> getChildren() { return children; }
	std::vector<TrieNode*>& getChildrenRef() { return children; }

	void create(const std::initializer_list<std::string>& list){ for (const std::string& s : list)	this->insert(s); }
	
	//void clear();	// We don't define clear op here, for endless loop may appear between "dtor" and "clear" as follows:
					// in "dtor" we need to call "clear", while in "clear" we do "delete operation" which calls "dtor".
					// So, we choose to state such "clear" operation in another class Trie instead of in TrieNode, 
					// In that case, we don't need to call "clear" in "TrieNode dtor" anymore, we do that in "Trie dtor",
					// meanig that we manage all the TrieNodes through Trie, which is safer and clearer.

	TrieNode* find(const std::string& s);

	void insert(const std::string& s);
	
	void display(std::string word = "");
};

/* The root of the whole Trie, more of a management class of TrieNodes */
class Trie 
{
private:
	TrieNode* root;
public:
	Trie() { this->root = new TrieNode(); }
	Trie(const Trie& rhs) { this->root = new TrieNode(*rhs.root); }
	Trie(const std::initializer_list<std::string>& list) { this->root = new TrieNode(list); }
	~Trie() { this->clear(root); std::cout << "the whole Trie was destroyed completely" << std::endl; }

	TrieNode* getRoot() { return this->root; }
	TrieNode*& getRootRef() { return this->root; }

	TrieNode* find(const std::string& s) { return this->root->find(s); }

	void insert(const std::string& s) { this->root->insert(s); }

	void display(std::string word = "") { this->root->display(word); }

	void clear(TrieNode*& node) {
		if (node->getChildrenRef().empty()) {
			delete node;
			node = nullptr;
		}
		else {
			for (auto& p : node->getChildrenRef()) {
				clear(p);
				delete p;
				p = nullptr;
			}
			node->getChildrenRef().clear();
		}
	}

};


void TrieNode::insert(const std::string& s) {
	TrieNode* root = this;
	TrieNode* cur = nullptr;
	for (int i = 0; i != s.size() - 1; ++i) {
		cur = nullptr;
		for (auto p : root->children) {
			if (p->data == s[i]) {
				cur = p;
				break;
			}
		}
		if (!cur) {
			cur = new TrieNode(s[i]);
			root->children.push_back(cur);
		}
		root = cur;
	}
	cur = nullptr;
	for (auto p : root->children) {
		if (p->data == s[s.size() - 1]) {
			cur = p;
			cur->ended = true;
			break;
		}
	}
	if (!cur) {
		cur = new TrieNode(s[s.size() - 1], true);
		root->children.push_back(cur);
	}

}

TrieNode* TrieNode::find(const std::string& s) {
	TrieNode* root = this;
	TrieNode* cur = nullptr;
	for (auto ch : s) {
		cur = nullptr;
		for (auto p : root->children) {
			if (p->data == ch) {
				cur = p;
				break;
			}
		}
		if (!cur) {
			return cur;
		}
		root = cur;
	}
	return cur;
}

void TrieNode::display(std::string word) {
	TrieNode* root = this;
	if (root->children.empty()) {
		std::cout << word << std::endl;
		return;
	}
	if (root->ended) {
		std::cout << word << std::endl;
	}
	for (auto p : root->children) {
		p->display(word + p->data);
	}
}


//Trie* t = new Trie{ "hello","here","her","hereby","world","word" };
//t->insert("how");
//t->insert("high");
//t->insert("highlight");
//t->insert("his");
//t->insert("what");
//t->insert("who");
//t->display();

////t->clear(t->getRoot());	//虽然可以，但不赞成，想要clear就直接delete掉
////t->display();

//TrieNode* p;
//string prefix = "he";
//if (p = t->find(prefix)) {
//	p->display(prefix);
//}
//else {
//	cout << "can't find word with prefix " << prefix << endl;
//}

//delete t;