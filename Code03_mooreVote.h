#pragma once
#include<vector>
#include<iostream>
#include<unordered_map>
using namespace std;
class Code03_mooreVote {
private:
    //摩尔投票问题与超级水王数问题
    static void DisplayNums(const vector<int>& nums) {
        for (int num : nums) {
            cout << num << ' ';
        }
    }
    //给定一个数组nums，nums的长度为n，nums中一定存在一个数，这个数出现的次数大于n/2
    //找出这个数并返回，要求时间复杂度O(n)，额外空间复杂度O(1)，不能使用哈希表统计次数
    static int MooreVote(vector<int>& nums) {
        //找到不同的2个数进行消除，反复执行此过程，最终剩下的数可能是水王数
        int n = nums.size();
        int ans = 0;
        int cnts = 0;
        for (int num : nums) {
            if (!cnts) {
                ans = num;
                cnts++;
            }
            else if (num != ans) {
                cnts--;
            }
            else {
                cnts++;
            }
        }
        if (!cnts) {
            return -1;//表示没有水王数
        }
        cnts = 0;//统计ans出现的次数
        for (int num : nums) {
            if (num == ans) {
                cnts++;
            }
        }
        return cnts > n / 2 ? ans : -1;
    }

    //摩尔投票问题的拓展
    //给定一个数组nums，长度为n，给定一个整数k，统计nums中出现次数大于n/k的数字，并返回
    //例如k=2，统计数组中出现次数大于n/2的数字，并返回（超级水王问题）
    //例如k=3，nums={3,3,3,2,2,1}，n=6，统计出现次数大于2的数字
    //数组的大小为n，出现次数大于n/k的数字最多有k-1个
    static vector<int> MooreVoteExpand(vector<int>& nums, int k) {
        auto AllElementMinusOne = [](unordered_map<int, int>& hashMap) {
            for (auto it = hashMap.begin(); it != hashMap.end();) {
                if (!(--it->second)) {
                    it = hashMap.erase(it);
                }
            }
            };
        auto ClearHashMap = [](unordered_map<int, int>& hashMap) {
            for (auto& [k, v] : hashMap) {
                v = 0;
            }
            };
        //------------------------------------------------------
        int n = nums.size();
        vector<int> ans;
        unordered_map<int, int> hashMap;//统计次数
        for (int num : nums) {
            if (hashMap.count(num)) {
                hashMap[num]++;
            }
            else {
                if (hashMap.size() == k - 1) {
                    AllElementMinusOne(hashMap);//让hashMap中所有元素的次数-1
                }
                else {
                    hashMap[num] = 1;
                }
            }
        }
        //hashMap中的元素是可能符合要求的元素,统计这些元素实际出现的次数
        ClearHashMap(hashMap);
        for (int num : nums) {
            if (hashMap[num] <= n / k) {
                ++hashMap[num];
                if (hashMap[num] > n / k) {
                    ans.push_back(num);
                }
            }
        }
        return ans;
    }
public:
    static void Run() {
        vector<int> nums = { 1,1,1,2,3,1,2 };
        cout << "nums:[ ";
        DisplayNums(nums);
        cout << "]中的水王数是:" << MooreVote(nums) << endl;;

        nums = { 3,3,3,3,2,2,2,2,7,7,5,4 };
        cout << "nums:[ ";
        DisplayNums(nums);
        cout << "]中满足出现次数大于n/k(k==5)的数字有:";
        DisplayNums(MooreVoteExpand(nums, 5));
    }
};