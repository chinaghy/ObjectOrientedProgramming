/*
 *1.子类对父类的兼容
 *2.多继承下的歧义性
 *3.虚基类
 */
#include <iostream>
using namespace std;
class A1 {
    protected:
        int x; //private子类不能继承 protected可以继承，但是二者不能->和.。
public:
    A1(int x):x(x){ }
    //虚析构函数，析构时可动态绑定，保证通过父类指针可正确析构子类
    //父类析构函数 无脑加virtual
    virtual ~A1() {    //关键virtual 没有的话会内存泄漏
        cout<<"A1 destructor  "<<x<<endl;
    }
};

class A2 {
protected:
    int x;
public:
    A2(int x):x(x){ }
    virtual ~A2() {
        cout<<"A2 destructor"<<endl;
    }
};

class B : public A1 { //B有两个父类，多继承
public:
    //子类的构造函数，要先构造父类
    B(int x = 0) :A1(x){

    }
    ~B() {
        cout<<"B destructor"<<endl;
    }

    void show() const { //理解const 常成员
        cout<<"B show"<<x<<endl;
    }
};  //B派生于A1，B是A1的子类、派生类，A1是B的父类，基类
    //父类先构造后析构
int main() {
    cout << "Hello world!" << endl;
    B b(0);
    b.show();
    B *pb = new B(99);
    pb->show();
    delete pb;
    //右边的子类指针付给了左边的父类指针，这是允许的：子类对父类的兼容（反之不成立）
    A1 *pa1 = new B(88);
    delete pa1;

    return 0;
}