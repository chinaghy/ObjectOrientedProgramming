/*
 * 类模板
 */
#include <iostream>

using namespace std;

template<class T>
class MyArray {
private:
    //禁用拷贝构造
    MyArray(const MyArray&src) {
        //需要深拷贝
    }
    //禁用赋值运算
    const T& operator =(const MyArray&src) {}
private:
    T *a;//动态数组
    int nSize;//数组元素个数
    int nLen;//数组空间大小

    public:
    MyArray(){
        nSize=0;
        nLen=1024;
        a=new T[nLen];
    }
    ~MyArray();
    //返回数组元素个数
    int size() const {
        return nSize;
    }
    //往数组中添加一个元素
    void add(const T&item) {
        if (nSize>=nLen) {
            T *buff = new T[nLen+1024];
            //必须使用赋值方式
            for (int i=0;i<nSize;i++) {
                buff[i]=a[i];
            }
            delete[]a;
            a=buff;
            nLen+=1024;
        }
        a[nSize]=item;
        nSize++;
    }
    //一定要是引用值赋值才有效
    T& operator[](int i) {
        if (i>=nSize)throw "“MyArray下标越界”";
        return a[i];
    }

    void display() const;
    void clear() {
        nSize=0;
    }
    //把元素插入在数组的第i个位置
    void insertAt(int i, const T& item) {

    }
};
//模板类的成员函数定义在外部：要进行一次模板申明 要跟<T>
template<class T>
MyArray<T>::~MyArray() {
    delete []a;
}

template<class T>
void MyArray<T>::display() const {
    for (int i=0;i<size();i++) {
        cout<<a[i]<<" ";
    }
}

class Student {
    private:
    int nId;
    char sName[10];
    char sSex[30];
public:
    Student() {
        nId=rand();
        strcpy(sName,"无名氏");
        strcpy(sSex,"沃尔玛塑料袋");
    }
    void display() const {
        cout<<nId<<"\t"<<sName<<sSex<<endl;
    }

};

int main() {
    //创建【模板类】对象，必须给出实际的类型
    MyArray<int> a;
    for (int i=0;i<10;i++) {
        a.add(i);
    }
    a.display();


    MyArray<Student> aStu;
    for (int i=0;i<10;i++) {
        aStu.add(Student());
    }
    for (int i=0;i<aStu.size();i++) {
        aStu[i].display();
    }
    return 0;
}