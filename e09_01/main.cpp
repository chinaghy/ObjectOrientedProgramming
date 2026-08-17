/*
 * 模板：函数模板、类模板
 * 模板是静态绑定，在编译时基于调用情况生成对应的函数
 *
 */

#include <iostream>
//模板申明，申明只生效一次，如果还要用就还要生成一次
template<class T> //template<typename T>
void mySwap(T &a,T &b) {
    T t=a;a=b;b=t;
}

using namespace std;
int main() {
    int a=1,b=3;
    //编译到此处时，系统将基于模板函数生成函数：void mySwap(int &a, int &b)
    mySwap(a,b);
    cout<<a<<" "<<b<<endl;
    float c=10.23,d=20.32;
    mySwap(c,d);
    cout<<c<<" "<<d<<endl;
    return 0;
}