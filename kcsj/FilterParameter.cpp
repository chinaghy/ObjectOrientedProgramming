#include "FilterParameter.h"
#include <stdexcept>
#include <sstream>

FilterParameter::FilterParameter(const std::string& name, double value, double minValue, double maxValue)
    : name(name), value(value), minValue(minValue), maxValue(maxValue) {
    if (minValue > maxValue) {
        throw std::invalid_argument("参数最小值不能大于最大值。");
    }
    if (!isValid()) {
        std::ostringstream oss;
        oss << "参数 " << name << " 的初始值 " << value
            << " 超出范围 [" << minValue << ", " << maxValue << "]。";
        throw std::out_of_range(oss.str());
    }
}

void FilterParameter::setValue(double newValue) {
    value = newValue;
    if (!isValid()) {
        std::ostringstream oss;
        oss << "参数 " << name << " 的取值 " << newValue
            << " 超出范围 [" << minValue << ", " << maxValue << "]。";
        throw std::out_of_range(oss.str());
    }
}

double FilterParameter::getValue() const {
    return value;
}

std::string FilterParameter::getName() const {
    return name;
}

double FilterParameter::getMinValue() const {
    return minValue;
}

double FilterParameter::getMaxValue() const {
    return maxValue;
}

bool FilterParameter::isValid() const {
    return value >= minValue && value <= maxValue;
}