#include <iostream>
#include <vector>
#include <algorithm>

void MySort(std::vector<int> &v) {
    for (int i=0;i<v.size();i++) {
        for (int j=i+1;j<v.size();j++) {
            if (v[i]>v[j]) {
                double temp=v[i];
                v[i]=v[j];
                v[j]=temp;

            }
        }
    }
    std::cout<<"排序用时"<<std::endl;//TODO
}

int main() {
    int N=100;
    //srand(GetTickCount());
    std::vector<double> a1;
    std::vector<double> a2;
    double t;
    for (int i=0;i<N;i++) {
        t=(rand()*rand()/100.0);
    }

    std::cout << "Hello, World!" << std::endl;
    return 0;
}