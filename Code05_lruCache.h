#pragma once
#include <assert.h>
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;
// LRU least recently used
// 最近最少使用到的
// 使用双向链表+哈希表实现LRU
template <typename K, typename V>
class Code05_lru {
private:
    struct ListNode {
        ListNode *next = nullptr;
        ListNode *last = nullptr; // 前一个
        pair<K, V> val;           // val存储k,v键值对
        ListNode(K k = 0, V v = 0) {
            val.first = k;
            val.second = v;
        }
    };
    // 双向链表
    class DoubleList {
    private:
        bool empty() {
            return head->next == tail && tail->last == head;
        }

    public:
        DoubleList() {
            head = new ListNode;
            tail = new ListNode;
            head->next = tail;
            tail->last = head;
        }
        void MoveNodeToTail(ListNode *node) {
            // 将node移动到最后面,表示node最近访问过
            if (node == nullptr || node == head || node == tail) {
                return;
            }
            node->last->next = node->next;
            node->next->last = node->last;
            InsertNodeToTail(node);
        }
        void InsertNodeToTail(ListNode *node) {
            node->next = tail;
            node->last = tail->last;
            tail->last->next = node;
            tail->last = node;
        }
        pair<bool, K> DeleteHead() { // 淘汰长时间没有访问过的节点
            if (empty()) {
                return make_pair(false, K());
            }
            ListNode *next = head->next;
            K k = next->val.first;
            head->next = next->next;
            next->next->last = head;
            delete next;
            return make_pair(true, k);
        }
        ~DoubleList() {
            ListNode *start = head;
            while (start) {
                ListNode *next = start->next;
                delete start;
                start = next;
            }
        }

    private:
        ListNode *head;
        ListNode *tail;
    };

private:
    int cap;               // LRU的容量
    DoubleList listdouble; // 双向链表
    unordered_map<K, ListNode *> hashMap;

private:
    Code05_lru(int capacity = 5) {
        cap = capacity;
    }
    void put(K k, V v) {
        if (hashMap.count(k)) {
            ListNode *node = hashMap[k];
            node->val.second = v;
            listdouble.MoveNodeToTail(node);
            return;
        }
        ListNode *node = new ListNode(k, v);
        hashMap[k] = node;
        listdouble.InsertNodeToTail(node);
        if (hashMap.size() == cap + 1) {
            auto ret = listdouble.DeleteHead();
            if (ret.first == false) {
                return;
            }
            hashMap.erase(ret.second);
        }
    }
    pair<bool, V> get(K k) {
        if (hashMap.count(k) == 0) {
            // 不存在
            return make_pair(false, V());
        }
        V ans = hashMap[k]->val.second;
        listdouble.MoveNodeToTail(hashMap[k]);
        return make_pair(true, ans);
    }

public:
    static void Run() {
        auto ShowRet = [](auto &&ret) {
            if (ret.first == false) {
                cout << "none" << endl;
            } else {
                cout << ret.second << endl;
            }
        };
        //---------------------------------------
        Code05_lru<int, int> lruCache(2);
        cout << "LRU cache capacity = 2" << endl;
        cout << "put(1,1)" << endl;
        lruCache.put(1, 1);
        cout << "put(2,2)" << endl;
        lruCache.put(2, 2);
        cout << "get(1)=";
        ShowRet(lruCache.get(1));
        cout << "put(3,3)" << endl;
        lruCache.put(3, 3);
        cout << "get(2)=";
        ShowRet(lruCache.get(2));
        cout << "put(4,4)" << endl;
        lruCache.put(4, 4);
        cout << "get(1)=";
        ShowRet(lruCache.get(1));
        cout << "get(3)=";
        ShowRet(lruCache.get(3));
        cout << "get(4)=";
        ShowRet(lruCache.get(4));
    }
};