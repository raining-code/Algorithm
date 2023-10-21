#pragma once
#include <algorithm>
#include <iostream>
#include <random>
#include <stack>
#include <thread>
#include <vector>
using std::cout;
using std::endl;
using std::vector;
class Code10_QuickSort {
private:
    static void ShowVector(vector<int>& nums) {
        std::for_each(nums.begin(), nums.end(), [](int n) {
            cout << n << ' ';
        });
        cout << endl;
    }
    static vector<int> getALenRandomVector(int len, int left, int right) {
        vector<int> nums;
        std::mt19937 mt;
        std::uniform_int_distribution<int> dis(left, right);
        for (int i = 0; i < len; i++) {
            nums.push_back(dis(mt));
        }
        return nums;
    }
    static std::pair<int, int> Partition(vector<int>& nums, int left, int right) {
        // 荷兰国旗问题,区间划分
        static std::mt19937 mt;
        std::uniform_int_distribution<int> dis(left, right);
        int target = nums[dis(mt)]; //<target target >target
        // target = 3;                 // TestPartition
        int L = left, R = right, i = left;
        while (i <= R) {
            if (nums[i] == target) {
                i++;
            } else if (nums[i] < target) {
                std::swap(nums[i++], nums[L++]);
            } else {
                std::swap(nums[i], nums[R--]);
            }
        }
        return {L, R};
    }
    static void TestPartition() {
        vector<int> nums = {6, 3, 3, 1, 2, 7, 8, 8, 5, 3};
        auto p = Partition(nums, 0, nums.size() - 1);
        cout << p.first << ' ' << p.second << endl;
        ShowVector(nums);
    }
    static void QuickSort(vector<int>& nums, int begin, int end) {
        if (nums.size() <= 1) {
            return;
        }
        std::stack<int> st;
        st.push(end);
        st.push(begin);
        while (!st.empty()) {
            int left = st.top();
            st.pop();
            int right = st.top();
            st.pop();
            auto p = Partition(nums, left, right);
            if (left < p.first - 1) {
                st.push(p.first - 1);
                st.push(left);
            }
            if (p.second + 1 < right) {
                st.push(right);
                st.push(p.second + 1);
            }
        }
    }
    static void TestQuickSort() {
        // auto nums = getALenRandomVector(20, 1, 20);
        // ShowVector(nums);
        // QuickSort(nums);
        // ShowVector(nums);
        std::mt19937 mt;
        std::uniform_int_distribution<int> dis(1, 1000);
        vector<vector<int>> matrix;
        constexpr int CNT = 20000;
        constexpr int n = 1000000;
        for (int i = 0; i < CNT; i++) {
            matrix.push_back(getALenRandomVector(dis(mt), 0 - n, n));
        }
        auto copy = matrix;
        int begin = clock();
        for (auto& v : matrix) {
            std::sort(v.begin(), v.end());
        }
        int end = clock();
        int stdsortcost = end - begin;
        begin = clock();
        for (auto& v : copy) {
            QuickSort(v, 0, v.size() - 1);
        }
        end = clock();
        int mysortcost = end - begin;
        bool flag = true;
        for (int i = 0; i < CNT; i++) {
            int size = matrix[i].size();
            for (int j = 0; j < size; j++) {
                if (matrix[i][j] != copy[i][j]) {
                    flag = false;
                    goto ENDWHILE;
                }
            }
        }
    ENDWHILE:
        if (flag) {
            cout << "排序结果正确" << endl;
            cout << "my sort cost time: " << mysortcost << endl;
            cout << "std sort cost time: " << stdsortcost << endl;
        }
    }
    static void ThreadSort() {
        constexpr int arrSize = 10000000;
        auto nums = getALenRandomVector(arrSize, 0, 30);
        auto copy = nums;
        constexpr int threadNum = 2;
        int begin = clock();
        for (int i = 0; i < threadNum; i++) {
            QuickSort(nums, i * (arrSize / threadNum), (i + 1) * (arrSize / threadNum) - 1);
        }
        int end = clock();
        int stdsortcost = end - begin;
        begin = clock();
        vector<std::thread> vt(threadNum);
        for (int i = 0; i < threadNum; i++) {
            vt[i] = std::thread(QuickSort, std::ref(copy), i * (arrSize / threadNum), (i + 1) * (arrSize / threadNum) - 1);
        }
        for (int i = 0; i < threadNum; i++) {
            vt[i].join();
        }
        end = clock();
        int mysortcost = end - begin;
        bool flag = true;
        for (int j = 0; j < arrSize; j++) {
            if (nums[j] != copy[j]) {
                flag = false;
                cout << j << endl;
                break;
            }
        }
        if (flag) {
            cout << "排序结果正确" << endl;
            cout << "my sort cost time: " << mysortcost << endl;
            cout << "std sort cost time: " << stdsortcost << endl;
        } else {
            ShowVector(nums);
            ShowVector(copy);
            cout << "排序结果错误" << endl;
        }
    }

public:
    static void Run() {
        // TestPartition();
        // TestQuickSort();
        ThreadSort();
    }
};