/*
 * 虚函数：动态绑定 ，与静态绑定在编译前已经绑定的情况所不同的是，虚函数是在运行时绑定
 *      虚析构可以通过父类指针正确析构到子类
 * 注意 构造函数不能是虚函数
 * 函数重载、函数模板是静态绑定
 */

#include <iostream>
using namespace std;
class A {
public:
    virtual void say() {   //virtual 动态绑定
        cout << "Hello World A" << endl;
    }
    virtual ~A() {
        cout << "析构A" << endl;
    }
};
class B:public A {
public:
    virtual void say() {
        cout << "Hello World B" << endl;
    }
    virtual ~B() {
        cout << "析构B" << endl;
    }
};
class C:public A {
public:
    virtual void say() {
        cout << "Hello World C" << endl;
    }
    virtual ~C() {
        cout << "析构C" << endl;
    }
};
void testsay(A *a[], int size) {
    for (int i = 0; i < size; i++) {
        // on run time
        a[i]->say();
    }
}
void free(A *a[], int size) {
    for (int i = 0; i < size; i++) {
        delete a[i];
    }
}
int main() {
    A *a[5];
    a[0] = new A;
    a[1] = new B;
    a[2] = new C;
    a[3] = new A;
    a[4] = new C;
    testsay(a, 5);
    free (a, 5);
    return 0;
}
