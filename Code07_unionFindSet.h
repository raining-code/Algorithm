#pragma once
#include <initializer_list>
#include <iostream>
#include <queue>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;
// 并查集
template <typename T>
class UnionFindSet {
public:
    template <typename Iter>
    UnionFindSet(Iter start, Iter end) {
        while (start != end) {
            fatherMap[*start] = *start;
            cntMap[*start] = 1;
            start++;
        }
    }
    bool IsSameSet(T left, T right) {
        if (fatherMap.count(left) && fatherMap.count(right) && FindTopFather(left) == FindTopFather(right)) {
            return true;
        }
        return false;
    }
    void Union(T left, T right) {
        if (fatherMap.count(left) && fatherMap.count(right)) {
            T ltop = FindTopFather(left), rtop = FindTopFather(right);
            if (ltop == rtop) {
                return;
            }
            // 将小集合合并到大集合
            T maxSet = size(left) > size(right) ? ltop : rtop;
            T minSet = size(left) <= size(right) ? ltop : rtop;
            fatherMap[minSet] = maxSet;
            cntMap[maxSet] += cntMap[minSet];
            cntMap.erase(minSet);
        }
    }
    size_t size(T val) {
        if (fatherMap.count(val) == 0) {
            return -1;
        }
        return cntMap[FindTopFather(val)];
    }

private:
    T FindTopFather(T val) {
        stack<T> Stack;
        while (fatherMap[val] != val) {
            Stack.push(val);
            val = fatherMap[val];
        }
        while (!Stack.empty()) {
            fatherMap[Stack.top()] = val;
            Stack.pop();
        }
        return val;
    }

private:
    unordered_map<T, T> fatherMap; // 每一个点的父
    unordered_map<T, int> cntMap;  // 以T的最终顶点的集合有多少个元素
};
class Code07_unionFindSet {
public:
    static void Run() {
        auto DisplayCount = [](vector<char>& alphas, UnionFindSet<char>& ufs) {
            for (char c : alphas) {
                cout << c << "所在的集合元素个数为" << ufs.size(c) << endl;
            }
        };

        //---------------------------------------------------------
        vector<char> alphas = {'a', 'b', 'c', 'd', 'e', 'f'};
        UnionFindSet<char> ufs(alphas.begin(), alphas.end());
        DisplayCount(alphas, ufs);
        cout << "将a和b合并" << endl;
        ufs.Union('a', 'b');
        DisplayCount(alphas, ufs);
        cout << "将c和d合并" << endl;
        ufs.Union('c', 'd');
        DisplayCount(alphas, ufs);
        cout << "将a和c合并" << endl;
        ufs.Union('c', 'a');
        DisplayCount(alphas, ufs);
        cout << "a与d是否在一个集合:" << (ufs.IsSameSet('a', 'd') ? "true" : "false") << endl;
        cout << "a与f是否在一个集合:" << (ufs.IsSameSet('a', 'f') ? "true" : "false") << endl;
    }
};