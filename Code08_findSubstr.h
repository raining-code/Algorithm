#pragma once
#include <iostream>
#include <memory>
#include <random>
#include <string>
#include <time.h>
#include <vector>
using namespace std;
// 查找子串的算法
class Code08_findSubstr {
private:
    static int FindSubStrBF(const string& str1, const string& str2) {
        // 从str1中找str2首次出现的位置(暴力方法)
        int n1 = str1.size(), n2 = str2.size();
        if (n1 < n2) {
            return -1;
        }
        for (int i = 0; i < n1; i++) {
            // 从str1的i位置开始匹配
            int index1 = i;
            int index2 = 0;
            while (index1 < n1 && index2 < n2 && str1[index1] == str2[index2]) {
                index1++, index2++;
            }
            if (index2 == n2) {
                return i;
            }
        }
        return -1;
    }
    static int KMP(const string& str1, const string& str2) {
        // 从str1中找str2首次出现的位置(KMP算法)
        int n1 = str1.size(), n2 = str2.size();
        if (n1 < n2) {
            return -1;
        }
        // 求str2的next数组
        unique_ptr<int[]> next(new int[n2]{0});
        next[0] = -1;
        for (int i = 2; i < n2; i++) {
            int pos = next[i - 1];
            while (pos != -1 && str2[i] != str2[pos]) {
                pos = next[pos];
            }
            next[i] = pos + 1;
        }
        int i = 0, j = 0; // str1从x位置开始匹配,str2从y位置开始匹配
        while (i < n1 && j < n2) {
            while (i < n1 && j < n2 && str1[i] == str2[j]) {
                i++, j++;
            }
            if (j == n2) {
                return i - n2;
            }
            while (str1[i] != str2[j]) {
                j = next[j];
                if (j == -1) {
                    j++;
                    i++;
                    break;
                }
            }
        }
        return -1;
    }
    static int GetRandomNumber(int L, int R) {
        static random_device rd;
        static mt19937 gen(rd());
        static uniform_int_distribution<int> dis(L, R);
        return dis(gen);
    }
    static string GetRandomString(int length) {
        static mt19937 gen(random_device{}());
        static uniform_int_distribution<int> dis(0, 15);
        string ans;
        for (int i = 0; i < length; i++) {
            ans += 'a' + dis(gen);
        }
        return ans;
    }

public:
    static void Run() {
        // string str1 = "abcdef";
        // string str2 = "cde";
        // string str3 = "cdf";
        // cout << FindSubStrBF(str1, str2) << endl;
        // cout << FindSubStrBF(str1, str3) << endl;

        // string str1 = "abcdef";
        // string str2 = "cde";
        // string str3 = "cdf";
        // cout << KMP(str1, str2) << endl;
        // cout << KMP(str1, str3) << endl;

        vector<string> strs;
        constexpr int num = 1000;
        for (int i = 0; i < num; i++) {
            strs.push_back(GetRandomString(GetRandomNumber(1, 1000)));
        }
        // for (string& s : strs) {
        //     cout << s << endl;
        // }
        vector<int> myfind;
        auto begin = clock();
        for (int i = 0; i < strs.size(); i++) {
            for (int j = 0; j < strs.size(); j++) {
                myfind.push_back(KMP(strs[i], strs[j]));
            }
        }
        auto end = clock();
        cout << "KMP algorithm cost time: " << end - begin << endl;
        vector<int> stlfind;
        begin = clock();
        for (int i = 0; i < strs.size(); i++) {
            for (int j = 0; j < strs.size(); j++) {
                stlfind.push_back(strs[i].find(strs[j]));
            }
        }
        end = clock();
        cout << "STL::string::find algorithm cost time: " << end - begin << endl;
        for (int i = 0; i < myfind.size(); i++) {
            if (myfind[i] != stlfind[i]) {
                cout << "my KMP algorithm error\n";
                break;
            }
        }
    }
};