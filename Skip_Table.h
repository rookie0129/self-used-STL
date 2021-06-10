#pragma once

#include <iostream>
#include <vector>
#include <cstdlib>

using std::vector;
using std::cout;
using std::endl;

// ͨ������random����ֵ����ʾ���ʣ�����һ��50%
static const int SKIPLIST_THRESH = RAND_MAX / 2;
// ����������
static const int MAX_LEVEL = 16;

/* ��������ʵ�������������ϵĿ��ٲ��ҡ����롢ɾ�� */
template<typename T = int>
class Skiplist {
private:
    // ���н����ʵ��ֻ��һ��(physical), ͨ��level����ʹ��ͬһ����ܴ����ڲ�ͬ���(logical)�������ж������Ƶ�
    struct Node {
        T val;
        vector<Node*> level;    // �ڵ� L ��Ľ��� next ָ���� level[L] ����
        Node(T val, int size = MAX_LEVEL) : val(val), level(size) {}
    };

    Node head;          // headҲֻ��һ�ݣ������ִ�����ÿһ�㣬˵��ʲô��˵������ָ��ָ����ÿһ��
    int maxlevel = 1;   // ��ǰ��������

public:
    Skiplist() : head(INT_MIN, MAX_LEVEL) { srand(time(nullptr)); }

    /* ֻҪ��0��� */
    bool search(int target) {
        Node* prev = _search(target)[0];
        return prev->level[0] && prev->level[0]->val == target;
    }

    /* ÿһ��Ķ������ѳ�������prevs�����¼����ע�⣬�����ڲ�ͬ���߼�����ѵ�ͬһ�������� */
    vector<Node*> _search(T key) {
        Node* cur = &head;
        vector<Node*> prevs(MAX_LEVEL);
        // �Զ�����ÿһ�㶼Ҫ��һ�£���Ȼ�������µĲ�β��Ǵ�ͷ��ʼ�����Ǹ�����һ��Ľ����ʼ
        // ���forѭ������down������ƶ�
        for (int i = maxlevel - 1; i >= 0; --i) {
            // �ڵ�ǰ��i���ҵ��Ǹ�ǡС��key�Ľ�㣨������head�����ò�û��С��key�ģ�
            // �ڲ�whileѭ������right������ƶ�
            while (cur->level[i] && cur->level[i]->val < key) {
                cout << "searched in level " << i << ": " << cur->val << endl;
                cur = cur->level[i];
            }
            prevs[i] = cur; // ��¼�µ�i��ǡ��С��key�Ľ�㣨������head�����ò�û��С��key�ģ�
            cout << "searched in level " << i << " " << cur->val << endl;
        }
        return prevs;
    }

    /* ���num */
    void add(T num) {
        cout << "to add: " << num << endl;
        auto prevs = _search(num);
        int level = random_level();
        if (level > maxlevel) {
            // �����¼ӵĲ�Σ�����headΪ���
            for (int i = maxlevel; i < level; ++i) {
                prevs[i] = &head;
            }
            maxlevel = level;
        }

        Node* cur = new Node(num, level);   // ���Կ�����ֻ��һ�������ϵ��½��

        // ͨ��level��������½����뵽��Ӧ����ĸ����У��Ӷ����������߼����
        for (int i = level - 1; i >= 0; --i) {
            cur->level[i] = prevs[i]->level[i];
            prevs[i]->level[i] = cur;
        }
        // if there is backward pointer, need to set both cur and cur.next's back pointer
        // Note that the back poinet of the first valid node is nullptr instead of head
    }

    /* ɾ��num */
    bool erase(T num) {
        auto prevs = _search(num);
        if (!prevs[0]->level[0] || prevs[0]->level[0]->val != num)
            return false;

        Node* del = prevs[0]->level[0];

        for (int i = 0; i < maxlevel; ++i) {
            // prevs[i]�ǵ�i��ǡС��num�Ľ�㣬��������ý��ĺ�̾���num��㣬��Ҫ�ж�һ��
            if (del == prevs[i]->level[i]) {
                prevs[i]->level[i] = del->level[i];
            }
        }
        delete del;

        // ���ܳ���ɾ��num�������������͵����
        while (maxlevel > 1 && !head.level[maxlevel - 1]) {
            --maxlevel;
        }
        // if there is backward poinet, need to set cur.next.back to cur.back
        return true;
    }

    /* չʾ�����ÿһ�� */
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

    /* ����ػ���¼��������߲�� */
    static int random_level() {
        int level = 1;
        while (rand() < SKIPLIST_THRESH && level < MAX_LEVEL) {
            //rand();
            ++level;
        }
        return level;
    }
};

