#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <functional>
#include <string>
using namespace std;
class Student {
private:
    int nId;
    string sName;
    char sSex[3];
public:
    Student() {
        nId=0;
        sName="无名";
        strcpy(sSex,"??");
    }
    int id() const {
        return nId;
    }
    //重载输入输出流必须用友元函数实现，不能使用成员函数
    //friend int main();
    friend istream &operator>>(istream &in, Student &stu);
    friend ostream &operator<<(ostream &out, const Student &stu);

public:
    static void savetofile(vector<Student> &students);
    static void readData(vector<Student> &students);
    static bool cmpByName(const Student &stu1, const Student &stu2) {
        return stu1.sName < stu2.sName;//小于不交换（升序）
    }
};
//实现静态成员函数
void Student::savetofile(vector<Student> &students) {
    const char sFileName[]="./a.txt";
    ofstream myfile;
    //创建新文件，若文件存在则删除
    myfile.open(sFileName);
    if (!myfile) {
        throw runtime_error("Can't open file");
    }
    for (int i = 0; i < students.size(); i++) {
        myfile << students[i] << endl;
    }
    myfile.close();
}


void Student::readData(vector<Student> &students) {
    const char sFileName[]="./a.txt";
    ifstream myfile; //读文件
    //创建新文件，若文件存在则删除
    myfile.open(sFileName);
    if (!myfile) {
        return;
    }
    Student stu;
    while (true) {
        myfile >> stu;//文件数据输入到学生对象中，格式由重载的运算符确定
        if (myfile.eof()) {
            //读到文件末尾了
            break;
        }
        else {
            //把读到的数据存放在向量容器里
            //容器里存放的对象，push_back将进行拷贝构造
            students.push_back(stu);
        }
    }
    myfile.close();
    cout<<"共读"<<nNum<<"条记录";
}
istream &operator>>(istream &in, Student &stu) {
    if (!dynamic_cast<ifstream *>(&in)) {
        //动态判断&in的文件类型，如果不是文件流...进行以下操作
        cout<<"Enter id name sex (id=0 for end input): ";
    }

    in>>stu.nId;
    if (stu.nId > 0) {
        in>>stu.sName>>stu.sSex;
    }
    return in;
}
ostream &operator<<(ostream &out, const Student &stu) {
    out<<"Student id: "<<stu.nId<<endl;
    out<<"Student name: "<<stu.sName<<endl;
    out<<"Student Sex："<<stu.sSex<<endl;
    return out;
}
int main() {
    vector<Student> a;
    Student::readData(a);
    Student t;
    while(true) {
        cin>>t;
        if (t.id()<=0) break;
        //以下将用t拷贝构造出一个新对象，并放在容器末尾
        a.push_back(t);
    }
    for (int i = 0; i < a.size(); i++) {
        cout<<a[i]<<endl;
    }
    Student::savetofile(a);
    sort(a.begin(),a.end(),Student::cmpByName);
    return 0;
}