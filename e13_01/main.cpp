#include <iostream>
#include <conio.h>
#include <Windows.h>
using namespace std;
//学生、老师、课程、选课
//项目=主程序+上面四个实体
void showMainMenu() {
    system("cls");
    std::cout<<"1 学生管理"<<std::endl;
    std::cout<<"2 教师管理"<<std::endl;
    std::cout<<"3 课程管理"<<std::endl;
    std::cout<<"4 选课管理"<<std::endl;
    std::cout<<"Esc 退出系统"<<std::endl;
}
int main() {
    while (true) {
        showMainMenu();
        //无回显的获取按键信息
        int nKey=_getch();
        if (nKey==49) {
            std::cout<<"\n 学生管理 \n";
            _getch();
        }
        else if (nKey==50) {
            std::cout<<"\n 教师管理 \n";
            _getch();
        }
        else if (nKey==51) {
            std::cout<<"\n 课程管理 \n";
            _getch();
        }
        else if (nKey==52) {
            std::cout<<"\n 选课管理 \n";
            _getch();
        }
        else if (nKey==27) {
            break;
        }

    }

    return 0;
}