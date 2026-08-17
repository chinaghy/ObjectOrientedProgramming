#include "Menu.h"
#include <iostream>
#include <exception>

int main() {
    try {
        Menu menu;
        menu.run();
    } catch (const std::exception& e) {
        std::cout << "系统发生严重错误：" << e.what() << std::endl;
        return 1;
    }
    return 0;
}