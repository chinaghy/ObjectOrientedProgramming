#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <ctime>    // 替代 Windows.h 用于计时
#include <cstdlib>  // 用于 rand() srand()

using namespace std;

// 自己写的排序（选择排序）
void mySort1(vector<double> &a) {
    // 跨平台计时（代替 GetTickCount）
    clock_t time1 = clock();

    double t;
    //vector是顺序容器 因此a[i]效率极高 所以不需要迭代器
    //顺序容器直接下标访问 如果是链式结构或者其他结构可能需要使用迭代器
    for (int i = 0; i+1 < a.size(); i++) {
        for (int j = i+1; j < a.size(); j++) {
            if (a[i] > a[j]) {
                t = a[i];
                a[i] = a[j];
                a[j] = t;
            }
        }
    }

    clock_t time2 = clock();
    // clock() 单位是时钟周期，转毫秒
    cout << "Time Self-Created elapsed: " << (time2 - time1) * 1000 / CLOCKS_PER_SEC << "ms\n";
}

bool cmpDouble(const double &a, const double &b) {
    return a < b;
}
// 标准库排序
void mySort2(vector<double> &a) {
    clock_t time1 = clock();

    // 降序排序 sort(a.begin(), a.end(), less<double>());
    sort(a.begin(), a.end(), cmpDouble);

    clock_t time2 = clock();
    cout << "Time algorithm elapsed: " << (time2 - time1) * 1000 / CLOCKS_PER_SEC << "ms\n";
}

void showData(const vector<double> &a) {
    for (int i = 0; i < a.size(); i++) {
        cout << a[i] <<"\t"<<endl;
        if (i>100) break;
    }
}

int main() {
    vector<double> a;
    // 跨平台随机种子
    srand((unsigned int)time(nullptr));
    // 测试：生成 10000 个随机数
    int n = 10000;
    for (int i = 0; i < n; ++i) {
        a.push_back((double)rand() / RAND_MAX * 10000);//把数放在容器的末尾
    }

    // 拷贝一份，保证两个排序用相同数据
    vector<double> b = a;
    // 测试自己写的排序
    //mySort1(a);
    // 测试标准库排序
    mySort2(b);

    return 0;
}