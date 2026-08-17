//
// Created by 桂花鱼 on 2026/5/25.
//

#include "Students.h"

// ==============================================
// 静态成员函数实现：保存学生容器数据到文本文件
// ==============================================
void Student::savetofile(vector<Student>& students) {
    const char sFileName[] = "./a.txt";  // 保存的文件名

    // 以输出方式打开文件(会覆盖原有内容)
    ofstream myfile(sFileName);

    // 判断文件是否打开成功
    if (!myfile.is_open()) {
        throw runtime_error("文件打开失败，无法保存数据！");
    }

    // 遍历容器，把每个学生对象写入文件
    for (int i = 0; i < students.size(); i++) {
        myfile << students[i];  // 调用重载的<<运算符
    }

    myfile.close();  // 关闭文件
    cout << "\n数据已成功保存到文件 a.txt" << endl;
}

// ==============================================
// 静态成员函数实现：从文件读取数据到vector容器
// ==============================================
void Student::readData(vector<Student>& students) {
    const char sFileName[] = "./a.txt";

    // 以只读方式打开文件
    ifstream myfile(sFileName);

    // 文件不存在直接返回，不报错
    if (!myfile.is_open()) {
        cout << "未找到历史数据文件，新建空数据列表" << endl;
        return;
    }

    Student stu;
    // 修复原代码BUG：正确的文件读取循环(先读再判断EOF)
    while (myfile >> stu) {
        students.push_back(stu);  // 读取成功就加入容器
    }

    myfile.close();
    cout << "成功从文件读取 " << students.size() << " 条学生记录" << endl;
}

// ==============================================
// 重载输入运算符 >>：用于cin和文件读取
// ==============================================
istream& operator>>(istream& in, Student& stu) {
    // 如果是控制台输入，才打印提示语
    if (&in == &cin) {
        cout << "请输入 学号 姓名 性别 (输入0结束): ";
    }

    // 读取学号
    in >> stu.nId;

    // 学号>0才继续读取姓名和性别
    if (stu.nId > 0) {
        in >> stu.sName >> stu.sSex;
    }

    return in;  // 返回流对象，支持链式调用
}

// ==============================================
// 重载输出运算符 <<：用于cout和文件写入
// ==============================================
ostream& operator<<(ostream& out, const Student& stu) {
    // 统一输出格式：控制台/文件写入都用这个格式
    out << "学号：" << stu.nId << endl;
    out << "姓名：" << stu.sName << endl;
    out << "性别：" << stu.sSex << endl;
    out << "-------------------------" << endl;
    return out;
}
