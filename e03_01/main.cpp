/*
 *  1、类的嵌套（对象成员）,构造函数需要先创建对象型成员
 *  2、内联与外联成员函数
 *      一般情况下 定义在类的内部的成员函数是内联函数
 *      定义在类的外部的成员函数是外联函数
 *      内联函数效率高 （原因是什么？）
 *      如果函数内含有：分支、循环语句，则不是内联函数
 *
 *      定义在外部的成员函数，若左修饰为：inline则表示要求系统把它当成内联函数
 *
 *  3、静态成员（静态数据成员、静态成员函数）
 *      静态成员 不属于对象，而是属于类
 *
 */
#include <iostream>
using namespace std;
class MyDate {
private:
    int Year;
    int Month;
    int Day;
public:
    MyDate(int Y, int M, int D) {
        if (Y<1900||Y>2500) {
            Y= 1900;
        }
        if (M<1||M>12) {
            M= 1;
        }
        if (D<1||D>31) {
            D= 1;
        }
        this->Month=M;
        this->Day=D;
        this->Year=Y;

    }
    void display() const{
        cout << Year << "/" << Month << "/" << Day << "/" << endl;
    }
};
class Student {
public:
    static int nCout;
private:
    int nId;
    char sName[11];
    MyDate birth1;

public:
    Student(int nId=0, const char *sName=NULL,int Y=0,int M=0, int D=0)
        :birth1(Y,M,D) {
            this->nId=nId;
            if (sName==NULL) {
                strcpy(this->sName,"Noname");
            }
            else {
                //strcpy_s(this->sName,11,sName);
                strcpy(this->sName,sName);
            }
    }
    //成员函数定义在类的外部，要用域限制
    inline void display()const;
};

void Student::display() const {
    cout<<nId<<"\t"<<sName<<"\t";
    birth1.display();
    cout<<endl;
}

int main() {
    Student stu(2025000001,NULL,2026,6,6);
    return 0;
}