#pragma once

#include <iostream>
#include <vector>
#include <cstdlib>

using std::vector;
using std::cout;
using std::endl;

// 通过控制random门限值来表示概率，这里一次50%
static const int SKIPLIST_THRESH = RAND_MAX / 2;
// 最大允许层数
static const int MAX_LEVEL = 16;

/* 跳表：辅助实现在有序单链表上的快速查找、插入、删除 */
template<typename T = int>
class Skiplist {
private:
    // 所有结点其实都只有一份(physical), 通过level数组使得同一结点能存在于不同层次(logical)，好像有多个结点似的
    struct Node {
        T val;
        vector<Node*> level;    // 在第 L 层的结点的 next 指针由 level[L] 担任
        Node(T val, int size = MAX_LEVEL) : val(val), level(size) {}
    };

    Node head;          // head也只有一份，但它又存在于每一层，说明什么，说明它的指针指向了每一层
    int maxlevel = 1;   // 当前的最大层数

public:
    Skiplist() : head(INT_MIN, MAX_LEVEL) { srand(time(nullptr)); }

    /* 只要第0层的 */
    bool search(int target) {
        Node* prev = _search(target)[0];
        return prev->level[0] && prev->level[0]->val == target;
    }

    /* 每一层的都给你搜出来（用prevs数组记录），注意，可能在不同的逻辑层次搜到同一个物理结点 */
    vector<Node*> _search(T key) {
        Node* cur = &head;
        vector<Node*> prevs(MAX_LEVEL);
        // 自顶向下每一层都要搜一下，当然，到了新的层次不是从头开始，而是根据上一层的结果开始
        // 外层for循环控制down方向的移动
        for (int i = maxlevel - 1; i >= 0; --i) {
            // 在当前第i层找到那个恰小于key的结点（可能是head，即该层没有小于key的）
            // 内层while循环控制right方向的移动
            while (cur->level[i] && cur->level[i]->val < key) {
                cout << "searched in level " << i << ": " << cur->val << endl;
                cur = cur->level[i];
            }
            prevs[i] = cur; // 记录下第i层恰好小于key的结点（可能是head，即该层没有小于key的）
            cout << "searched in level " << i << " " << cur->val << endl;
        }
        return prevs;
    }

    /* 添加num */
    void add(T num) {
        cout << "to add: " << num << endl;
        auto prevs = _search(num);
        int level = random_level();
        if (level > maxlevel) {
            // 额外新加的层次，均以head为起点
            for (int i = maxlevel; i < level; ++i) {
                prevs[i] = &head;
            }
            maxlevel = level;
        }

        Node* cur = new Node(num, level);   // 可以看到，只有一个物理上的新结点

        // 通过level，把这个新结点插入到它应插入的各层中，从而产生若干逻辑结点
        for (int i = level - 1; i >= 0; --i) {
            cur->level[i] = prevs[i]->level[i];
            prevs[i]->level[i] = cur;
        }
        // if there is backward pointer, need to set both cur and cur.next's back pointer
        // Note that the back poinet of the first valid node is nullptr instead of head
    }

    /* 删除num */
    bool erase(T num) {
        auto prevs = _search(num);
        if (!prevs[0]->level[0] || prevs[0]->level[0]->val != num)
            return false;

        Node* del = prevs[0]->level[0];

        for (int i = 0; i < maxlevel; ++i) {
            // prevs[i]是第i层恰小于num的结点，并不代表该结点的后继就是num结点，需要判断一下
            if (del == prevs[i]->level[i]) {
                prevs[i]->level[i] = del->level[i];
            }
        }
        delete del;

        // 可能出现删掉num结点后最大层数降低的情况
        while (maxlevel > 1 && !head.level[maxlevel - 1]) {
            --maxlevel;
        }
        // if there is backward poinet, need to set cur.next.back to cur.back
        return true;
    }

    /* 展示跳表的每一层 */
    void display() {
        Node* cur = &head;
        // through every level, from top to bottom
        for (int i = maxlevel - 1; i >= 0; --i) {
            cout << "level " << i << ": ";
            Node* tmp = cur->level[i];
            while (tmp){
                cout << tmp->val << " ";
                tmp = tmp->level[i];
            }
            cout << endl;
        }
        cout << endl;
    }

    /* 随机地获得新加入结点的最高层次 */
    static int random_level() {
        int level = 1;
        while (rand() < SKIPLIST_THRESH && level < MAX_LEVEL) {
            //rand();
            ++level;
        }
        return level;
    }
};

