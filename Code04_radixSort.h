#pragma once
#include <algorithm>
#include <iostream>
#include <queue>
#include <string.h>
#include <vector>
using std::cout;
using std::endl;
using std::queue;
using std::vector;
// 基数排序与计数排序
class Code04_radixSort {
private:
    inline static constexpr int BASE = 16; // 要排序的数是十进制
    inline static int counts[BASE];        // 统计每一个数字出现的次数,前缀分区技巧
    static void DisplayVector(const vector<int> &nums) {
        for (int num : nums) {
            cout << num << ' ';
        }
        cout << endl;
    }
    static void CountSort(vector<int> &nums) {
        int minNum = nums.front();
        int maxNum = nums.front();
        for (int num : nums) {
            minNum = std::min(minNum, num);
            maxNum = std::max(maxNum, num);
        }
        int helpSize = maxNum - minNum + 1;
        int *help = new int[helpSize]{0}; // 例如最大值为10，最小值为5，需要开辟的数组大小是10-5+1
        for (int num : nums) {
            help[num - minNum]++; // 统计次数
        }
        nums.clear();
        for (int i = 0; i < helpSize; i++) {
            while (help[i]--) {
                nums.push_back(i + minNum);
            }
        }
        delete[] help;
    }
    static void RadixSortByQueue(vector<int> &nums, int bits) { // 使用队列作为桶进行基数排序
        // bits表示序列中的最大值的位数
        // BASE表示多少进制
        vector<queue<int>> Queues;
        Queues.resize(BASE);
        int offset = 1;
        for (int offset = 1; bits > 0; bits--, offset *= BASE) { // 例如最大值为156，则进行3轮
            for (int num : nums) {
                int bitNum = (num / offset) % BASE; // 得到个位/十位/百位……的数
                Queues[bitNum].push(num);
            }
            // 按照个位/十位/百位……排好的数已经放入Queues中
            nums.clear();
            for (auto &Queue : Queues) {
                while (!Queue.empty()) {
                    nums.push_back(Queue.front());
                    Queue.pop();
                }
            }
        }
    }
    static void RadixSort(vector<int> &nums, int bits) {
        // bits表示序列中的最大值的位数
        // BASE表示多少进制
        int *help = new int[nums.size()]{0};
        int offset = 1;
        for (int offset = 1; bits > 0; bits--, offset *= BASE) {
            memset(counts, 0, sizeof(int) * BASE);
            for (int num : nums) {
                int bitNum = (num / offset) % BASE;
                counts[bitNum]++; // 先统计个数
            }
            for (int i = 1; i < BASE; i++) {
                counts[i] += counts[i - 1]; // 统计前缀数量
            }
            for (int i = nums.size() - 1; i >= 0; i--) {
                int bitNum = (nums[i] / offset) % BASE;
                help[--counts[bitNum]] = nums[i];
            }
            memcpy(nums.data(), help, sizeof(int) * nums.size());
        }
        delete[] help;
    }
    static void RadixSortContainMinus(vector<int> &nums) {
        int minNum = nums[0];
        for (int num : nums) {
            minNum = std::min(minNum, num);
        }
        int maxNum = 0;
        for (int &num : nums) {
            num -= minNum;
            maxNum = std::max(maxNum, num);
        }
        int bits = 1;
        while (maxNum / BASE) {
            bits++;
            maxNum /= BASE;
        }
        RadixSort(nums, bits);
        for (int &num : nums) {
            num += minNum;
        }
    }

public:
    static void Run() {
        // cout << "计数排序#" << endl;
        // vector<int> nums = { 3,0,1,1,3,3,0,2 };
        // cout << "排序之前:";
        // DisplayVector(nums);
        // cout << "排序之后:";
        // CountSort(nums);
        // DisplayVector(nums);

        // cout << endl << "基数排序#" << endl;
        // nums = { 1,56,26,9999,7 };
        // cout << "排序之前:";
        // DisplayVector(nums);
        // cout << "排序之后:";
        // RadixSort(nums, 4);
        // DisplayVector(nums);

        // cout << endl << "基数排序#" << endl;
        // nums = { 123,-987,23,9853,-2 };
        // cout << "排序之前:";
        // DisplayVector(nums);
        // cout << "排序之后:";
        // RadixSortContainMinus(nums);
        // DisplayVector(nums);

        cout << endl;
        cout << "基数排序#" << endl;
        vector<int> nums = {0xff2, 0x345, 0x1, 0x2, 0xf};
        cout << "排序之前:";
        DisplayVector(nums);
        cout << "排序之后:";
        RadixSortContainMinus(nums);
        DisplayVector(nums);
    }
};