//类与对象
/*
 *  学生是一个类，我是一个示例化的对象
 *  1、一个类必须有
 *      构造函数:1、初始化【常成员变量】只能在这里赋值
 *      析构函数:当需要释放资源（如：内存）时，应在析构函数里进行
 *      拷贝构造函数（构造函数的特殊形式）:以下情况将调用拷贝构造
 *              1）实参传形参
 *              2）函数返回的是对象
 *              3）显示调用
 *      赋值运算(当需要深拷贝):
 *  2、一些特殊的成员:
 *      常成员：常数据成员必须在函数外部初始化 nTest
 *      静态成员：
 *  3、浅拷贝与深拷贝******
 *  【浅拷贝】 是两个或多个指针指向同一块内存
 *  【深拷贝】 是两个或多个指针指向不同内存 内存中数据一样
 *
 *
 */
#include<iostream>
using namespace std;
//a b是引用型形参，它的改变将影响实参
//引用并不会产生新的对象，他就是实参，是实参的别名
void swap(int &a, int &b) {
    int t = a;
    a = b;
    b = t;
};
class Clock {
    private:
        int H;
        int M;
        int S;
        char *pBuff;
    public:
     /*    //无参构造
        Clock():H(0),M(0),S(0) {
        }
        //带参构造
        //Clock(int H,int M,int S):H(H),M(M),S(S) {//H成员变量（H形参）
        //}
       Clock(int H, int M, int S){
            //构造函数参数值异常，只能抛出异常来应对
            if (H<0 || H>=24) {
                throw "无效的小时值";
                //H=0; M S也是一样的道理
            }
            this->H=H;//进入花括号之后对象诞生了this才有意义
            this->M=M;
            this->S=S;
        }
    */

    //解决aCLock【】 具有【默认值】的带参构造 如果给了参数以给的参数为准，反之有默认值
    Clock(int H=1, int M=2, int S=3,const char *s =NULL){//只能读不能写 要在函数外面初始化
            if (H<0 || H>=24) {
                H=0;
            }
            this->H=H;//进入花括号之后对象诞生了this才有意义
            this->M=M;
            this->S=S;
            cout<<"构造被调用"<<endl;
            if (s==NULL) {
                pBuff=NULL;
            }
            else {
                //申请内存不要使用malloc
                //new 必须对应delete 否则将导致内存泄漏
                //以下先申请独立内存，再把数据拷贝过去，叫做深拷贝；
                pBuff=new char[strlen(s)+1];
                strcpy(pBuff,s);
            }
        }
    //构造函数的形参是该类的引用型对象，则他是拷贝构造函数
    //使用引用但不希望其值被改变，则可左修饰为const，称为常引用
    //优点 不会产生新的对象
    Clock(const Clock& src) {//为什么是& ？
        H=src.H;
        M=src.M;
        S=src.S;

        //指针直接赋予地址，叫【浅拷贝】
        //pBuff=src.pBuff;
        cout<<"拷贝构造"<<endl;

        if (src.pBuff==NULL) {
            pBuff=NULL;
        }
        else {
            //以下是深拷贝
            pBuff=new char[strlen(pBuff)+1];
        }

    }

    //析构函数，当对象被摧毁时，系统自动调用析构函数
    //析构的主要功能是。申请释放的资源
    ~Clock() {
        if (pBuff!=NULL) {
            cout<<"析构将释放："<<pBuff<<endl;
            delete[] pBuff;
            //当new的时候带有中括号[]，则delete也带有中括号[]
        }
        else {
            cout<<"析构，pbuff为空"<<endl;
        }
    }

    public:
        void display() const{ //右修饰const，表示为常成员函数，只读不改的情况下
            //H++; //错的，不能修改
            cout<<H<<":"<<M<<":"<<S<<endl;
        }
};
int main() {
    Clock c1(0,0,0,"sb");
    c1.display();
    //对象数组必须要求 无参构造
    Clock aClock[5];
    Clock c3(11);
    //创建c1c2c3系统自动调用了构造函数
    //对于c4c5 这里不是赋值运算，是【拷贝构造】
    //创建c4c5调用的是拷贝构造函数
    Clock c4=c3;
    //Clock c5(c3);
    c4=c3;//这里是赋值运算，系统默认的赋值运算是【浅拷贝】
          //当需要深拷贝时，必须重载赋值运算
    for(int i=0;i<5;i++) {
        aClock[i].display();
    }
    try {

        Clock c2(33,12,12);
        c2.display();
    }catch(char const* e) {
        cout<<e<<endl;
    }
    int aa=888;
    int &bb=aa;//内存中只有一个aa；
    bb=666666;
    cout<<"aa="<<aa<<endl;
    cout<<"bb="<<bb<<endl;
    return 0;
}//
// Created by 桂花鱼 on 2026/3/16.
//