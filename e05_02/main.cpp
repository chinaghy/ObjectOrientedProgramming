/*
 *多继承下的歧义性问题，及其解决办法
 *解决方法1、同名覆盖 2、域限定 3、虚基类
 *当一类的家族具有虚基类的时候，则子类必须负责
 * ‘最远虚基类’的构造
 */
#include<iostream>
using namespace std;
class A {
    protected:
    int x;
    public:
    A(int x) :x(x){}
    virtual ~A() {
        cout<<"~A()"<<endl;
    }
};
//此种继承方式，表明A是虚基类
class B1 : virtual public A {
    public:
    B1(int x) :A(x){}
    virtual ~B1() {
        cout<<"~B1()"<<endl;
    }
};
class B2 : virtual public A {
    public:
    B2(int x) :A(x){}
    virtual ~B2() {
        cout<<"~B2()"<<endl;
    }
};

//多继承  凡事写了virtual的都有遗传性 父类写了代表子类写了
class C:public B1,public B2 {
private:
    //int x;

public:
    C(int x = 0, int y = 0) :B1(x),B2(y),A(10086) {
        //this->x =x; //同名覆盖，非常糟糕地解决了歧义性
    }
    virtual ~C() {
        cout<<"~C()"<<endl;
    }
    void show() const {
        //B2::x 通过域限定解决歧义性
        //cout<<"show()"<<B2::x<<endl;
        cout<<"x = "<<x<<endl;
    }
};
int main() {
    C c(66,99);
    c.show();
    return 0;
}