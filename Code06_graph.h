#pragma once
#include "Code07_unionFindSet.h"
#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;
// 改写的堆：用于Dijikstra
template <typename T, typename Comp>
class HeapMethord {
public:
    HeapMethord(const Comp& c) :
        comp(c) {
        // 比较方法
    }
    void HeapInsert(vector<T>& nums, int i) {
        // 插入数据，进行向上调整，时间复杂度O(logN)
        while (comp(nums[(i - 1) / 2], nums[i])) { // 父节点小于自己
            swap(nums[(i - 1) / 2], nums[i]);
            i = (i - 1) / 2;
        }
    }
    void HeapIfy(vector<T>& nums, int i, int size) { // 向下进行调整
        int left = i * 2 + 1;
        while (left < size) {
            int maxChild = left + 1 < size && !comp(nums[left], nums[left + 1]) ? left + 1 : left; // 左右孩子中最大的
            int best = nums[i] >= nums[maxChild] ? i : maxChild;
            if (best == i) {
                break;
            }
            swap(nums[i], nums[best]);
            i = best;
            left = i * 2 + 1;
        }
    }

private:
    const Comp& comp;
};
// 图的相关算法
template <typename T>
struct Edge;
template <typename T>
struct Node {
    int in = 0;
    int out = 0;                   // 出度和入度
    unordered_set<Node<T>*> nodes; // 相连的顶点
    unordered_set<Edge<T>*> edges; // 相连的边
    T val = T();
};
template <class T>
struct Edge {
    Node<T>* from = nullptr;
    Node<T>* to = nullptr;
    int weight = 0; // 权值
    Edge(Node<T>* f = nullptr, Node<T>* t = nullptr, int w = 0) {
        from = f;
        to = t;
        weight = w;
    }
};
template <class T>
struct Graph {
    unordered_map<T, Node<T>*> nodes;
    unordered_set<Edge<T>*> edges;
};
class Code06_graph {
private:
    static Graph<int> ConstructGraph() {
        vector<vector<int>> matrix = {{1, 2, 2}, {1, 3, 5}, {2, 4, 6}, {3, 5, 8}, {2, 5, 10}, {3, 4, 9}, {5, 6, 3}, {4, 6, 4}};
        // 点1->点2权值为2
        vector<vector<int>> copy = matrix; // 无向图
        for (auto& nums : copy) {
            swap(nums[0], nums[1]);
            matrix.push_back(nums);
        }
        Graph<int> g;
        for (auto& message : matrix) {
            int from = message[0];
            int to = message[1];
            int weight = message[2];
            Node<int>*fnode = nullptr, *tnode = nullptr;
            if (g.nodes.count(from) == 0) {
                fnode = new Node<int>;
                fnode->val = from;
                g.nodes[from] = fnode;
            } else {
                fnode = g.nodes[from];
            }
            if (g.nodes.count(to) == 0) {
                tnode = new Node<int>;
                tnode->val = to;
                g.nodes[to] = tnode;
            } else {
                tnode = g.nodes[to];
            }
            fnode->out++;
            tnode->in++;
            fnode->nodes.insert(tnode);
            Edge<int>* e = new Edge<int>(fnode, tnode, weight);
            g.edges.insert(e);
            fnode->edges.insert(e);
        }
        return g;
    }
    static void GraphDfs(Node<int>* start) {
        unordered_set<Node<int>*> hashSet; // 记录已经遍历过的点
        stack<Node<int>*> Stack;
        cout << start->val << ' ';
        Stack.push(start);
        hashSet.insert(start);
        while (!Stack.empty()) {
            // cout << "Stack size=" << Stack.size() << endl;
            Node<int>* node = Stack.top();
            Stack.pop();
            for (auto n : node->nodes) {
                if (hashSet.count(n) == 0) {
                    cout << n->val << ' ';
                    hashSet.insert(n);
                    Stack.push(node);
                    Stack.push(n);
                    break;
                }
            }
        }
        cout << endl;
    }
    static void GraphBfs(Node<int>* start) {
        queue<Node<int>*> Queue;
        unordered_set<Node<int>*> hashSet;
        hashSet.insert(start);
        Queue.push(start);
        while (!Queue.empty()) {
            auto node = Queue.front();
            Queue.pop();
            cout << node->val << ' ';
            for (auto n : node->nodes) {
                if (hashSet.count(n) == 0) {
                    hashSet.insert(n);
                    Queue.push(n);
                }
            }
        }
        cout << endl;
    }
    static void TopologicalSorting(const Graph<int>& g) {
        unordered_map<Node<int>*, int> hashMap; // 存储点和它的入度
        unordered_set<Node<int>*> zeroSet;      // 存储入度为0的点
        for (auto [val, node] : g.nodes) {
            if (node->in == 0) {
                cout << val << ' ';
                zeroSet.insert(node);
            } else {
                hashMap[node] = node->in;
            }
        }
        while (!zeroSet.empty()) {
            unordered_set<Node<int>*> nextZeroSet;
            for (auto node : zeroSet) {
                for (auto n : node->nodes) {
                    if (!--n->in) {
                        cout << n->val << ' ';
                        nextZeroSet.insert(n);
                    }
                }
            }
            zeroSet = move(nextZeroSet);
        }
    }
    static vector<Edge<int>*> Kruskal(const Graph<int>& g) {
        auto EdgeComp = [](const Edge<int>* left, const Edge<int>* right) {
            return left->weight > right->weight;
        };
        //-----------------------------------------------------
        // Kruskal算法求最小生成树,需要使用并查集
        vector<Edge<int>*> ans;
        vector<Node<int>*> nodes;
        for (auto [val, node] : g.nodes) {
            nodes.push_back(node);
        }
        priority_queue<Edge<int>*, vector<Edge<int>*>, decltype(EdgeComp)> heap(g.edges.begin(), g.edges.end(), EdgeComp);
        UnionFindSet<Node<int>*> ufs(nodes.begin(), nodes.end());
        while (!heap.empty()) {
            auto edge = heap.top();
            heap.pop();
            if (!ufs.IsSameSet(edge->from, edge->to)) {
                ans.push_back(edge);
                ufs.Union(edge->from, edge->to);
            }
        }
        return ans;
    }
    static vector<Edge<int>*> Prim(const Graph<int>& g) {
        auto EdgeComp = [](const Edge<int>* left, const Edge<int>* right) {
            return left->weight > right->weight;
        };
        //-------------------------------------------

        // Prim算法从顶点的角度出发
        vector<Edge<int>*> ans;
        unordered_set<Node<int>*> hashSet;
        auto start = g.nodes.begin()->second;
        hashSet.insert(start);
        priority_queue<Edge<int>*, vector<Edge<int>*>, decltype(EdgeComp)> heap(EdgeComp);
        for (auto e : start->edges) {
            heap.push(e);
        }
        while (!heap.empty()) {
            auto e = heap.top();
            heap.pop();
            if (hashSet.count(e->to) == 0) {
                ans.push_back(e);
                hashSet.insert(e->to);
                for (auto edge : e->to->edges) {
                    heap.push(edge);
                }
            }
        }
        return ans;
    }
    static unordered_map<Node<int>*, pair<int, list<Node<int>*>>> Dijikstra(Node<int>* start) {
        // key表示start->node
        // pair->first表示start->node的最短距离
        // pair->second表示start->node的最短路径
        unordered_map<Node<int>*, int> distanceMap;          // 记录距离
        unordered_map<Node<int>*, list<Node<int>*>> pathMap; // 记录路径
        distanceMap[start] = 0;
        pathMap[start].push_back(start);
        vector<pair<Node<int>*, int>> nums;      // 充当堆的作用,从左往右依次是node 距离 下标
        unordered_map<Node<int>*, int> indexMap; // 记录node与下标之间的关系
        nums.push_back(make_pair(start, 0));
        indexMap[start] = 0;
        while (!nums.empty()) {
            auto [node, dis] = nums.front();
            swap(nums.front(), nums.back());
            nums.pop_back();
            if (!nums.empty()) {
                indexMap.erase(node);
                indexMap[nums.front().first] = 0;
            }
            int i = 0, size = nums.size();
            int left = i * 2 + 1;
            while (left < size) {
                // 左右孩子中最小的
                int maxChild = left + 1 < size && nums[left + 1].second < nums[left].second ? left + 1 : left;
                int best = nums[i].second <= nums[maxChild].second ? i : maxChild;
                if (best == i) {
                    break;
                }
                // 下标发生变化
                swap(indexMap[nums[i].first], indexMap[nums[best].first]);
                swap(nums[i].first, nums[best].first);
                i = best;
                left = i * 2 + 1;
            }
            for (auto edge : node->edges) {
                if (distanceMap.count(edge->to) == 0 || distanceMap[edge->to] > distanceMap[edge->from] + edge->weight) {
                    bool flag = distanceMap.count(edge->to) == 0;
                    // 以前没有路，现在找到了一条路||以前有路，但是以前的路距离长
                    distanceMap[edge->to] = distanceMap[edge->from] + edge->weight;
                    pathMap[edge->to] = pathMap[edge->from];
                    pathMap[edge->to].push_back(edge->to);
                    int i = 0;
                    if (flag) {
                        // 表示以前没有路
                        nums.push_back(make_pair(edge->to, distanceMap[edge->to]));
                        indexMap[edge->to] = nums.size() - 1;
                        i = nums.size() - 1;
                    } else {
                        // 表示以前有路，堆中一个数忽然改小,进行类似heapInsert的过程
                        i = indexMap[edge->to];
                    }
                    // 插入数据，进行向上调整，时间复杂度O(logN)
                    while (nums[(i - 1) / 2].second > nums[i].second) { // 父节点大于自己
                        swap(nums[(i - 1) / 2], nums[i]);
                        swap(indexMap[nums[(i - 1) / 2].first], indexMap[nums[i].first]); // 下标
                        i = (i - 1) / 2;
                    }
                }
            }
        }
        unordered_map<Node<int>*, pair<int, list<Node<int>*>>> ans;
        for (auto it : distanceMap) {
            ans[it.first].first = it.second;
        }
        for (auto it : pathMap) {
            ans[it.first].second = move(it.second);
        }
        return ans;
    }

public:
    static void Run() {
        auto Verify = [](vector<Edge<int>*>& ans) {
            cout << "通过Kruskal/Prim算法选出来的边为:" << endl;
            for (auto edge : ans) {
                cout << edge->from->val << "->" << edge->to->val << "(权值:" << edge->weight << ")" << endl;
            }
        };
        auto dijikstra = [](unordered_map<Node<int>*, pair<int, list<Node<int>*>>>& hashMap, int start) {
            for (auto&& [end, pairmsg] : hashMap) {
                cout << "从点" << start << "到点" << end->val << "的最短距离是:" << pairmsg.first << endl;
                cout << "路径为:";
                auto endit = pairmsg.second.end();
                endit--;
                auto it = pairmsg.second.begin();
                for (; it != endit; it++) {
                    cout << (*it)->val << "->";
                }
                cout << (*it)->val;
                cout << endl
                     << endl;
            }
        };
        //--------------------------------------------------
        Graph<int> g = ConstructGraph();
        // cout << "深度优先遍历的结果为:";
        // GraphDfs(g.nodes.find(1)->second);
        // cout << endl;

        // cout << "宽度优先遍历的结果为:";
        // GraphBfs(g.nodes.find(1)->second);
        // cout << endl;

        // cout << "拓扑排序的结果为:";
        // TopologicalSorting(g);
        // cout << endl;

        // auto kru = Kruskal(g);
        // Verify(kru);

        // auto pri = Prim(g);
        // Verify(pri);
        int start = 3;
        auto ans = Dijikstra(g.nodes.find(start)->second);
        dijikstra(ans, start);
    }
};