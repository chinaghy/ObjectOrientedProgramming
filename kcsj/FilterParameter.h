#ifndef FILTER_PARAMETER_H
#define FILTER_PARAMETER_H

#include <string>

// FilterParameter 类：封装滤镜参数，提供合法性检查。
class FilterParameter {
private:
    std::string name;
    double value;
    double minValue;
    double maxValue;

public:
    FilterParameter(const std::string& name, double value, double minValue, double maxValue);

    void setValue(double value);
    double getValue() const;
    std::string getName() const;
    double getMinValue() const;
    double getMaxValue() const;
    bool isValid() const;
};

#endif