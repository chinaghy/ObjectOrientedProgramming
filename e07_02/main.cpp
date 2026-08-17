/*
 *  重载下标运算符[]
 *
 *
 */


#include <iostream>

using namespace std;
//目前数组只能是整数，使用类模板后它可以装任何数据类型
class MyArray {
private:
    //禁用赋值运算
    MyArray operator =(const MyArray &) {
        throw "不可以这样？！";
        return MyArray(1);
    };
    int *a;//别嫌弃。它可以是任意数据类型
    int nSize;

public:
    MyArray(int nSize = 100):nSize(nSize) {
        a = new int[nSize];
        memset(a, 0, nSize * sizeof(int));
    };

    MyArray(const MyArray &src) {
        //深拷贝
        nSize = src.nSize;
        a = new int[nSize];
        memcpy(a,src.a,src.nSize*sizeof(int));
    }
    ~MyArray() {
        delete[] a;
    }

    int &operator[](int i) { //&的意义是？ 保证a可以改 为什么不左修饰const？
        if (i >= nSize) {
            throw "MyArray;下标越界";
        }
        return *(a+i);
    }

    void display() {
        for (int i = 0; i < nSize; i++) {
            cout <<"\t"<< a[i];
            if ((i+1) %8==0) cout<<endl;
        }
    }

    int size() {
        return nSize;
    }

    void resize(int nSize2) {
        if (nSize==nSize2) {
            return;
        }
        int *p = new int[nSize2];
        if (nSize < nSize2) {
            memset(p, 0, nSize * sizeof(int));
            memcpy(p,a,nSize2*sizeof(int));
            delete []a;
            a = p;
        }

    }

};

int main() {
    try {
        MyArray a(30);
        a.display();
        cout<<endl;
        for (int i = 0; i < a.size()+100; i++) {
            a[i]=i*i;
        }
        a.display();
    }
    catch (const char *msg) {
        cout << msg << endl;
    }
    return 0;
}