/*
 * 动态矩阵
 *
 */
#include <iostream>
using namespace std;

template<class T>
class MyArray {//定义动态一维数组
private:
    int nSize;
    T *data;
    void _DeepCopy(const MyArray &src) {
        nSize=src.nSize;
        data=new T[nSize];
        for (int i=0;i<nSize;i++) {
            data[i]=src.data[i];
        }
    }
    public:
    MyArray(int n=10) {
        if (n<1) {n=10;cout<<"n小于1，调整为10"<<endl;}
        nSize=n;
        data=new T[nSize];
    }
    MyArray(const MyArray &src) {
        _DeepCopy(src);
    }
    ~MyArray(){
        if (data) {
            delete[] data;
        }
    }
    //重载赋值运算
    const MyArray &operator=(const MyArray &src) {
        if (data) {
            delete[] data;
        }
        _DeepCopy(src);
        return *this;
    }
    T &operator[](int i) {
        if (i<0||i>nSize) {
            throw "MyArray：下标越界";
        }
        else {
            return *(data+i);
            //return data[i];
        }
    }
};

//动态二维数组：都是由若干个一维数组构成
template<class T>
class MyMatrix {
private:
    int nRow;//个一维数组
    int nCol;//一维数组的长度
    //aData里存放的是MyArray的指针
    MyArray<T> **aData;
private:
    void _Free() {
        for (int i=0;i<nRow;i++) {
            delete[] aData[i];
        }
        delete[] aData;
    }
    void _DeepCopy(const MyMatrix &src) {
        nRow=src.nRow;
        nCol=src.nCol;
        aData=new MyArray<T>*[nRow];
        for (int i=0;i<nRow;i++) {
            aData[i]=new MyArray<T>(src.aData[i]);

        }
    }
public:
    MyMatrix(int r=10, int c=10) {
        if (r<1) {
            r=10;
        }
        if (c<1) {
            c=10;
        }
        nRow=r;
        nCol=c;
        aData=new MyArray<T>*[nRow];
        for (int i=0;i<nRow;i++) {
            aData[i]=new MyArray<T>[nCol];
        }

    }
    ~MyMatrix() {
        _Free();
    }
    MyArray<T> &operator[](int i) const{
        if (i<0||i>nRow) {
            throw"行越界";
        }
        else {
            return *aData[i];
        }
    }
    void display() {
        for (int i=0;i<nRow;i++) {
            for (int j=0;j<nCol;j++) {
                cout<<(*this)[i][j]<<" ";
            }
            cout<<endl;
        }
    }
};
int main() {
    //播种一个随机种子
    srand(GetTickCount());
    MyMatrix<double> a(3,5);
    a.display();
    for (int i=0;i<3;i++) {
        for (int j=0;j<5;j++) {
            a[i][j]=rand()/100.0;
        }
    }
    MyMatrix<double> b(a);
    //MyMatrix<double> b=a;
    return 0;
}