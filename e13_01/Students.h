//
// Created by 桂花鱼 on 2026/5/25.
//
#pragma once
// 包含需要的头文件
#include <iostream>   // 标准输入输出流(cin/cout)
#include <fstream>    // 文件输入输出流(ifstream/ofstream)
#include <vector>     // 动态数组容器
#include <algorithm>
#include <functional>
#include <string>     // string字符串类
#include <cstring>    // strcpy函数需要的头文件(原代码缺少，会报错)
#include <stdexcept>  // 异常处理runtime_error需要(原代码缺少)

using namespace std;

// 学生类：封装学生的属性和操作
class Student {
    // 私有成员：类外部不能直接访问，体现封装性
private:
    int nId;          // 学号
    string sName;     // 姓名
    char sSex[3];     // 性别(固定2个字符长度，存男/女)

    // 公有成员：外部可以访问，提供对外接口
public:
    // 无参构造函数：初始化对象的默认值
    Student() {
        nId = 0;                // 默认学号0
        sName = "无名";         // 默认姓名
        strcpy(sSex, "??");     // 复制字符串到字符数组(不能直接=赋值)
    }

    // 公有成员函数：获取私有成员nId(只读，const修饰)
    int id() const {
        return nId;
    }

    // 运算符重载声明：
    // 1. 输入流>>重载：友元函数(必须用友元，才能访问类的私有成员)
    friend istream& operator>>(istream& in, Student& stu);
    // 2. 输出流<<重载：友元函数
    friend ostream& operator<<(ostream& out, const Student& stu);

    // 静态成员函数：属于类，不属于某个对象，可直接用类名调用
    // 功能：把学生数据保存到文件
    static void savetofile(vector<Student>& students);
    // 功能：从文件读取学生数据
    static void readData(vector<Student>& students);
};
