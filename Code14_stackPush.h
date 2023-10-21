#include <ctime>
#include <functional>
#include <iostream>
#include <list>
#include <memory>
#include <unistd.h>
using namespace std;
class Code14_stackPush { // 已知入栈顺序,打印所有可能的出栈顺序
    static list<string> Solve(string in) {
        list<string> ans;
        int n = in.size();
        function<void(int, string, string)> lambda = [&](int i, string pop, string push) {
            if (i == n - 1) {
                pop += in.back();
                while (!push.empty()) {
                    pop.push_back(push.back());
                    push.pop_back();
                }
                ans.push_back(pop);
                return;
            }
            // i位置立刻入栈出栈
            lambda(i + 1, pop + in[i], push);
            // i位置入栈暂时不出栈
            lambda(i + 1, pop, push + in[i]);
        };
        lambda(0, "", "");
        return ans;
    }
    static void Test() {
        cout << "输入入栈顺序" << endl;
        string in;
        cin >> in;
        auto ans = Solve(in);
        for (auto& s : ans) {
            cout << s << ' ';
        }
        cout << endl;
    }

public:
    static void Run() {
        Test();
    }
};