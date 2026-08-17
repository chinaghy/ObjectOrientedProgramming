/*
 * 纯虚函数和抽象类
 * 含有纯虚函数的类叫做抽象类 也叫接口类
 * 不能创建抽象类的对象
 * 从抽象类派生出的子类必须实现父类的纯虚函数，否则子类还是抽象类，不能创建对象
 */
#include <iostream>
using namespace std;

class Shape {
    public:
    Shape() {}
    //必须是虚析构
    virtual ~Shape() {}
    //纯虚函数,旨在通过动态绑定正确的求面积
    virtual float Area() = 0;
    //    //虚函数
    //virtual float Area();
};

class Rectangle : public Shape {
    private:
    float w,h;
    public:
    Rectangle(float w,float h):w(w),h(h) {}
    //实现父类的纯虚函数
    virtual float Area() {
        return w*h;
    }
    virtual ~Rectangle() {}
};

class Circle : public Shape {
    private:
    float r;
    public:
    Circle(float r) {this->r = r;}

    virtual float Area() {
        return r*r*3.1415926;
    }
    virtual ~Circle() {}
};

class Point : public Shape {
    private:

public:
    Point() {}
    virtual float Area() {
        return 0;
    }
    virtual ~Point() {}
};

void showArea(Shape *s[],int size) {
    for (int i = 0; i < size; i++) {
        cout << s[i]->Area() << endl;
    }
}

void freeShape(Shape *s[],int size) {
    for (int i=0;i<size;i++) {
        delete s[i];
    }
}

int main() {
    //Shape *p = new Shape;  错误！抽象类不能创建对象
    Shape *a[3];//抽象类的指针数组
    a[0] = new Rectangle(5,5);
    a[1] = new Circle(5);
    a[2] = new Point();

    showArea(a,3);
    freeShape(a,3);
    return 0;
}