#pragma once
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;
// 组成指定面额的方法数
class Code01_currency {
private:
    // arr是货币数组，其中的值都是正数。再给定一个正数aim。每个值都认为是一张货币，
    // 即便是值相同的货币也认为每一张都是不同的，返回组成aim的方法数
    // 例如 : arr = { 1,1,1 }. aim = 2
    // 第0个和第1个能组成2，第1个和第2个能组成2，第0个和第2个能组成2一共就3种方法，所以返回3
    static int MethodCount1(vector<int> &arr, int aim) {
        // 暴力递归：每一个位置都可以选或者不选，从左往右的尝试模型
        return process1(arr, aim, 0, 0); // 从0位置开始的总方法数
    }
    static int process1(vector<int> &arr, int aim, int curIndex, int total) {
        if (total == aim) {
            return 1;
        }
        if (total > aim || curIndex == arr.size()) {
            return 0;
        }
        // 1.选择当前位置
        int p1 = process1(arr, aim, curIndex + 1, total + arr[curIndex]);
        // 2.不选
        int p2 = process1(arr, aim, curIndex + 1, total);
        return p1 + p2;
    }
    static int MethodCount1dp(vector<int> &arr, int aim) {
        // 可变参数为curIndex和total
        // curIndex->[0,arr.size()]
        // total->[0,aim],因为当total>aim时返回0
        vector<vector<int>> dp(arr.size() + 1, vector<int>(aim + 1));
        for (int curIndex = 0; curIndex <= arr.size(); curIndex++) {
            dp[curIndex][aim] = 1;
        }
        for (int curIndex = arr.size() - 1; curIndex >= 0; curIndex--) {
            for (int total = 0; total < aim; total++) {
                int p1 = total + arr[curIndex] > aim ? 0 : dp[curIndex + 1][total + arr[curIndex]];
                int p2 = dp[curIndex + 1][total];
                dp[curIndex][total] = p1 + p2;
            }
        }
        return dp[0][0];
    }
    static void Run1() {
        vector<int> arr = {1, 1, 1, 2};
        int aim = 2;
        cout << "方法数为:" << MethodCount1(arr, aim) << endl;
        cout << "方法数为:" << MethodCount1dp(arr, aim) << endl;
    }

private:
    // arr是面值数组，其中的值都是正数且没有重复。再给定一个正数aim。每个值都认为是一种面值，且认为张数是无限的。
    // 返回组成aim的方法数
    // 例如︰arr = {1,2}， aim = 4
    // 方法如下∶1 + 1 + 1 + 1、1 + 1 + 2、2 + 2一共就3种方法，所以返回3
    static int MethodCount2(vector<int> &arr, int aim) {
        // 暴力递归：每一个位置可以选择多次
        return process2(arr, 0, aim); // 当前在0位置，还需要凑齐aim元的方法
    }
    static int process2(vector<int> &arr, int Index, int rest) {
        if (rest == 0) {
            return 1;
        }
        if (Index == arr.size()) { // 不会出现aim<0的情况，因为在for循环中已经避免
            return 0;
        }
        int ans = 0;
        // 当前位置可以选很多次
        for (int cnt = 0; cnt * arr[Index] <= rest; cnt++) {
            ans += process2(arr, Index + 1, rest - (cnt * arr[Index]));
        }
        return ans;
    }
    static int MethodCount2dp(vector<int> &arr, int aim) {
        // Index->[0,arr.size()]
        // rest->[0,aim]
        vector<vector<int>> dp(arr.size() + 1, vector<int>(aim + 1));
        for (int i = 0; i <= arr.size(); i++) {
            dp[i][0] = 1;
        }
        for (int Index = arr.size() - 1; Index >= 0; Index--) {
            for (int rest = 1; rest <= aim; rest++) {
                int ans = 0;
                for (int cnt = 0; cnt * arr[Index] <= rest; cnt++) {
                    ans += dp[Index + 1][rest - (cnt * arr[Index])];
                }
                dp[Index][rest] = ans;
            }
        }
        return dp[0][aim];
    }
    static int MethodCount2dp2(vector<int> &arr, int aim) {
        vector<vector<int>> dp(arr.size() + 1, vector<int>(aim + 1));
        for (int i = 0; i <= arr.size(); i++) {
            dp[i][0] = 1;
        }
        for (int Index = arr.size() - 1; Index >= 0; Index--) {
            for (int rest = 1; rest <= aim; rest++) {
                // int ans = 0;
                // for (int cnt = 0; cnt * arr[Index] <= rest; cnt++) {
                //	ans += dp[Index + 1][rest - (cnt * arr[Index])];
                // }
                // dp[Index][rest] = ans;
                /*分析位置依赖进行优化*/
                dp[Index][rest] = dp[Index + 1][rest];
                if (rest - arr[Index] >= 0) {
                    dp[Index][rest] += dp[Index][rest - arr[Index]];
                }
            }
        }
        return dp[0][aim];
    }
    static void Run2() {
        vector<int> arr = {1, 2};
        int aim = 4;
        cout << "方法数为:" << MethodCount2(arr, aim) << endl;
        cout << "方法数为:" << MethodCount2dp(arr, aim) << endl;
        cout << "方法数为:" << MethodCount2dp2(arr, aim) << endl;
    }

private:
    // arr是货币数组，其中的值都是正数。再给定一个正数aim。每个值都认为是一张货币，
    // 认为值相同的货币没有任何不同，返回组成aim的方法数
    // 例如 : arr = {1,2,1,1,2,1,2}, aim = 4方法∶1 + 1 + 1 + 1、1 + 1 + 2、2 + 2一共就3种方法，所以返回3
    static int MethodCount3(vector<int> &arr, int aim) {
        vector<int> counts; // 统计张数
        vector<int> money;
        unordered_map<int, int> hashMap;
        for (int m : arr) {
            hashMap[m]++;
        }
        for (auto [m, c] : hashMap) {
            money.push_back(m);
            counts.push_back(c);
        }
        return process3(money, counts, 0, aim);
    }
    static int process3(vector<int> &money, vector<int> &counts, int Index, int rest) {
        if (rest == 0) {
            return 1;
        }
        if (Index == money.size()) {
            return 0; // rest>0
        }
        int ans = 0;
        for (int cnt = 0; cnt <= counts[Index] && rest - cnt * money[Index] >= 0; cnt++) {
            ans += process3(money, counts, Index + 1, rest - cnt * money[Index]);
        }
        return ans;
    }
    static int MethodCount3dp(vector<int> &arr, int aim) {
        vector<int> counts;
        vector<int> money;
        unordered_map<int, int> hashMap;
        for (int m : arr) {
            hashMap[m]++;
        }
        for (auto [m, c] : hashMap) {
            money.push_back(m);
            counts.push_back(c);
        }
        vector<vector<int>> dp(money.size() + 1, vector<int>(aim + 1));
        for (int i = 0; i <= money.size(); i++) {
            dp[i][0] = 1;
        }
        for (int Index = money.size() - 1; Index >= 0; Index--) {
            for (int rest = 0; rest <= aim; rest++) {
                int ans = 0;
                for (int cnt = 0; cnt <= counts[Index] && rest - cnt * money[Index] >= 0; cnt++) {
                    ans += dp[Index + 1][rest - cnt * money[Index]];
                }
                dp[Index][rest] = ans;
            }
        }
        return dp[0][aim];
    }
    static int MethodCount3dp2(vector<int> &arr, int aim) {
        vector<int> counts;
        vector<int> money;
        unordered_map<int, int> hashMap;
        for (int m : arr) {
            hashMap[m]++;
        }
        for (auto [m, c] : hashMap) {
            money.push_back(m);
            counts.push_back(c);
        }
        vector<vector<int>> dp(money.size() + 1, vector<int>(aim + 1));
        for (int i = 0; i <= money.size(); i++) {
            dp[i][0] = 1;
        }
        for (int Index = money.size() - 1; Index >= 0; Index--) {
            for (int rest = 0; rest <= aim; rest++) {
                dp[Index][rest] = dp[Index + 1][rest];
                if (rest - money[Index] >= 0) {
                    dp[Index][rest] += dp[Index][rest - money[Index]];
                }
                if (rest - (counts[Index] + 1) * money[Index] > 0) {
                    dp[Index][rest] -= dp[Index + 1][rest - (counts[Index] + 1) * money[Index]];
                }
            }
        }
        return dp[0][aim];
    }
    static void Run3() {
        vector<int> arr = {1, 2, 1, 1, 2, 1, 2};
        int aim = 4;
        cout << "方法数为:" << MethodCount3(arr, aim) << endl;
        cout << "方法数为:" << MethodCount3dp(arr, aim) << endl;
        cout << "方法数为:" << MethodCount3dp2(arr, aim) << endl;
    }

public:
    static void Run() {
        // Run1();
        // Run2();
        Run3();
    }
};