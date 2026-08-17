/*
 *多态：运算符重载 几乎所有的运算符都可以重载
 *运算符重载可以通过友元函数或成员函数实现
 *注意 输入输出流只能用友元函数实现
 *不能重载的： .（对象？） *（通过指针取对象） ::(域限定符)  sizeof（）   ？（）
 *实例：+、-、++、--、[]（下标运算符）
 * ++a  a++
 *
 *
 */
#include <iostream>
using namespace std;

class Complex {
private:
    float real;
    float image;
public:
    Complex(float r=0.0f, float i=0.0f)
        :real(r), image(i){
    };

    //function1
    Complex operator - (const Complex &a) {
        //非必要不要激活拷贝构造 所以是&a 并非Complex a
        return Complex(real - a.real, image - a.image);//this->可以不写
    };
    friend Complex operator +(const  Complex &a1, const Complex &c2);

    //左++ 前置运算 表达式的值就是变化后的值
    const Complex &operator ++ () {
        real += 1.0f;
        image += 1.0f;
        return *this;
    }

    //右++ 后置运算
    const Complex operator ++ (int) { //不可以加&（引用） 因为temp是局部值 如果加& 要加static Complex temp
        Complex temp= *this;
        real += 1.0f;
        image += 1.0f;
        return temp;
    }

    void display() const {
        cout<<real<<" + "<<image<<"i"<<endl;
    };
};

Complex operator + (const  Complex &c1, const Complex &c2) {
    return Complex(c1.real+c2.real,c1.image+c2.image);
}

int main() {
    Complex a1(1.6,2.3);
    Complex a2(1.6,6.6);
    Complex c;
    //运算符重载本质上还是调用函数
    c=a1.operator-(a2);
    c= a1 - a2;
    c.display();

    c=a1 + a2;
    //c=operator+(a1,a2);
    c.display();
    a1.display();
    (++a1).display();
    a2.display();
    (a2++).display();

    return 0;
}