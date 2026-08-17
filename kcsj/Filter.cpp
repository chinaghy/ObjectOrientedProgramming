#include "Filter.h"
#include <iostream>

Filter::Filter(const std::string& name) : filterName(name) {
}

void Filter::showInfo() const {
    std::cout << "滤镜名称：" << filterName << std::endl;
}

std::string Filter::getName() const {
    return filterName;
}