/*
 *静态数据成员:必须在类的外部声明
 *静态成员函数
 *常成员
 *常引用
 *友元 破坏了封装性，新兴的面向对象语言不支持友元
 */
#include<iostream>
using namespace std;

class Clock;//类的前向申明




class Clock {
private:
    int H,M,S;
private:
    static int nNum;
public:
    static int objNum() {
        return Clock::nNum;
    }
public:
    Clock(int H=0,int M=0, int S=0) {
        this->H=H;
        this->M=M;
        this->S=S;
        Clock::nNum++;
    }

    //拷贝构造
    Clock(const Clock &c) {
        cout<<"拷贝构造"<<endl;
        H=c.H;
        M=c.M;
        S=c.S;
        Clock::nNum++;
    }
    ~Clock() {
        nNum--;
    }

    //申明【友元】函数，使其可以访问私有成员
    friend void showClock(Clock c);
};


//静态数据成员必须在外部申明并初始化
int Clock::nNum = 0;

// void &showClock(Clock &cl) {  //??
//     cout<<"duixianggeshu"<<Clock::objNum()<<endl;
//     cout<<cl.H<<cl.M<<cl.S<<endl;
//     //返回的对象不是cl，而是用cl拷贝构造出的一个无名对象
//     return cl;
// }

void showClock(Clock cl) {
    cout<<"duixianggeshu"<<Clock::objNum()<<endl;
    cout<<cl.H<<cl.M<<cl.S<<endl;
    //返回的对象不是cl，而是用cl拷贝构造出的一个无名对象
    return cl;
}

int main() {
    Clock c1;
    Clock *p1=NULL;
    Clock c2=c1;
    Clock &c3=c1;
    //以下c3是对c1的引用，并未创建新的对象
    //函数形参是对象，形参传实参 将产生拷贝构造
    showClock(c1);

    cout<<"duixianggeshu"<<Clock::objNum()<<endl;
    p1=new Clock(8,59,45);
    cout<<"duixianggeshu"<<Clock::objNum()<<endl;
    delete p1;
    cout<<"duixianggeshu"<<Clock::objNum()<<endl;

    p1=new Clock[100];
    cout<<"duixianggeshu"<<Clock::objNum()<<endl;
    Clock a[100];
    cout<<"duixianggeshu"<<Clock::objNum()<<endl;

    delete[] p1;
    cout<<"duixianggeshu"<<Clock::objNum()<<endl;
    return 0;
}