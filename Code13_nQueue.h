#include <ctime>
#include <functional>
#include <iostream>
#include <memory>
#include <unistd.h>
using namespace std;
// n皇后问题
class Code13_nQueue {
private:
    static int NQueue(int n) {
        // N皇后问题数组解决
        unique_ptr<int[]> path(new int[n]{});           // path[i]表示i行选择的列
        function<int(int)> lambda = [&](int i) -> int { // 表示当前来到i行进行选择
            if (i == n) {
                for (int row = 0; row < n; row++) {
                    for (int col = 0; col < n; col++) {
                        if (col == path[row]) {
                            cout << '$' << ' ';
                        } else {
                            cout << '#' << ' ';
                        }
                    }
                    cout << endl;
                }
                sleep(2);
                cout << endl;
                return 1;
            }
            int ans = 0;
            for (int j = 0; j < n; j++) { //(i,j)位置进行尝试
                bool flag = true;         // 表示(i,j)位置可以选
                for (int col = 0; col < i; col++) {
                    if (j == path[col] || abs(i - col) == abs(j - path[col])) {
                        flag = false;
                        break;
                    }
                }
                if (flag) {
                    path[i] = j;
                    ans += lambda(i + 1);
                }
            }
            return ans;
        };
        return lambda(0);
    }
    // N皇后问题位运算解决
    static int NQueueBit(int n) {
        int all = (1 << n) - 1;
        function<int(int, int, int)> lambda = [&](int col, int left, int right) -> int {
            if (col == all) {
                return 1;
            }
            // 列限制，左下限制，右下限制
            int total = all & (~(col | left | right)); // 为1表示可以选,为0表示不能选
            int ans = 0;
            while (total) {
                int selectBit = total & (~total + 1);
                total &= (total - 1);
                ans += lambda(col | selectBit, (left | selectBit) >> 1, (right | selectBit) << 1);
            }
            return ans;
        };
        return lambda(0, 0, 0);
    }
    static void Test() {
        for (int i = 1; i <= 16; i++) {
            // auto begin = clock();
            // cout << i << "皇后问题的答案是" << NQueue(i) << endl;
            NQueue(i);
            // auto end = clock();
            // cout << "计算" << i << "皇后花费的时间是" << end - begin << "ms" << endl;
        }
    }

public:
    static void Run() {
        Test();
    }
};