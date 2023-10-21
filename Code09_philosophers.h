#pragma once
// 哲学家就餐问题
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <unistd.h>
#include <vector>
#define NUM 5 // 有NUM个哲学家
using std::cout;
using std::endl;
using std::string;
using std::thread;
using std::vector;
class Chopsticks {
public:
    string name = "木筷子";
    std::mutex mtx; // 互斥锁保护临界资源
};
static Chopsticks chops[NUM]; // NUM个筷子
class Code09Philosophers {
private:
    static void PhilosophersQuestion() {
        vector<thread> vt;
        for (int i = 0; i < NUM; i++) {
            vt.push_back(thread(Eating, i));
        }
        for (int i = 0; i < NUM; i++) {
            vt[i].join();
        }
    }
    static void Eating(int num) { // 参数为哲学家的编号
        // 左边筷子的下标是num,右边筷子的下标是(num+1)%NUM
        if (num & 1) {
            chops[num].mtx.lock();
            chops[(num + 1) % NUM].mtx.lock();
            printf("编号为%d的哲学家吃到餐\n", num);
            usleep(10000);
            chops[num].mtx.unlock();
            chops[(num + 1) % NUM].mtx.unlock();
        } else {
            chops[(num + 1) % NUM].mtx.lock();
            chops[num].mtx.lock();
            printf("编号为%d的哲学家吃到餐\n", num);
            usleep(10000);
            chops[num].mtx.unlock();
            chops[(num + 1) % NUM].mtx.unlock();
        }
    }

public:
    static void Run() {
        PhilosophersQuestion();
    }
};