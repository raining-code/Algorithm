#include <algorithm>
#include <iostream>
#include <random>
#include <vector>
using namespace std;
class Code11_crafsman {
private:
    static void ShowLog() {
        cout << "基尼系数可以反应一个社会的贫富差距" << endl;
        cout << "基尼系数越接近于0,表示这个社会财富越均匀" << endl;
        cout << "基尼系数越接近于1,表示这个社会财富差距越大" << endl;
        cout << "基尼系数等于0时,这个社会上的所有人财富都是相等的" << endl;
        cout << "基尼系数等于1时,有一个人掌握了这个社会所有的财富" << endl;
        cout << "一般认为,基尼系数如果超过0.5,那么这个社会很有可能产生犯罪" << endl;
    }
    static double CalcGiniCoefficient(vector<int>& nums) {
        int sum = 0;    // 财富总和
        int abssum = 0; // 差值的绝对值之和
        for (int i = 0; i < nums.size(); i++) {
            sum += nums[i];
            for (int j = 0; j < nums.size(); j++) {
                abssum += abs(nums[i] - nums[j]);
            }
        }
        return static_cast<double>(abssum) / (2 * sum * nums.size());
    }
    static void Experiment() {
        vector<int> money(100, 100); // 初始时100人,每人有100元
        int round = 0;
        ShowLog();
        cout << "输入实验的轮次" << endl;
        cin >> round;
        mt19937 mt;
        uniform_int_distribution<int> dis(0, 99);
        for (int i = 0; i < round; i++) {
            vector<bool> haveMoney(100, false);
            for (int i = 0; i < 100; i++) {
                if (money[i]) {
                    haveMoney[i] = true;
                }
            }
            for (int i = 0; i < 100; i++) {
                if (haveMoney[i]) {
                    int other = i;
                    do {
                        other = dis(mt);
                    } while (other == i);
                    money[i]--;
                    money[other]++;
                }
            }
        }
        cout << "实验结束后每个人的剩余钱数(从小到大):";
        sort(money.begin(), money.end());
        for (int i = 0; i < 100; i++) {
            if (i % 10 == 0) {
                cout << endl;
            }
            cout << money[i] << ' ';
        }
        cout << "\n基尼系数=" << CalcGiniCoefficient(money) << endl;
    }

public:
    static void Run() {
        Experiment();
    }
};