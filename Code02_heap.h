#pragma once
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
class Code02_heap {
    //堆结构和堆排序
private:
    static void DisplayNums(const vector<int>& nums) {
        for (int num : nums) {
            cout << num << ' ';
        }
    }
    static void HeapInsert(vector<int>& nums, int i) {
        //插入数据，进行向上调整，时间复杂度O(logN)
        while (nums[(i - 1) / 2] < nums[i]) {//父节点小于自己
            swap(nums[(i - 1) / 2], nums[i]);
            i = (i - 1) / 2;
        }
    }
    static void HeapIfy(vector<int>& nums, int i, int size) {//向下进行调整
        int left = i * 2 + 1;
        while (left < size) {
            int maxChild = left + 1 < size && nums[left + 1] > nums[left] ? left + 1 : left;//左右孩子中最大的
            int best = nums[i] >= nums[maxChild] ? i : maxChild;
            if (best == i) {
                break;
            }
            swap(nums[i], nums[best]);
            i = best;
            left = i * 2 + 1;
        }
    }
    static void HeapSort1(vector<int>& nums) {
        //在建堆的时候从上往下
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            HeapInsert(nums, i);
        }
        while (n > 1) {
            swap(nums[0], nums[--n]);
            HeapIfy(nums, 0, n);
        }
    }
    static void HeapSort2(vector<int>& nums) {
        //在建堆的时候从下往上
        int n = nums.size();
        for (int i = (n - 2) / 2; i >= 0; i--) {
            HeapIfy(nums, i, n);
        }
        while (n > 1) {
            swap(nums[0], nums[--n]);
            HeapIfy(nums, 0, n);
        }
    }
public:
    static void Run() {
        vector<int> nums = { 3,1,8,5,44,12,9,7 };
        cout << "排序之前nums:";
        DisplayNums(nums);
        cout << endl;
        HeapSort1(nums);
        cout << "排序之后nums:";
        DisplayNums(nums);
        cout << endl;

        cout << endl;

        nums = { 3,1,8,5,44,12,9,7 };
        cout << "排序之前nums:";
        DisplayNums(nums);
        cout << endl;
        HeapSort2(nums);
        cout << "排序之后nums:";
        DisplayNums(nums);
        cout << endl;
    }
};