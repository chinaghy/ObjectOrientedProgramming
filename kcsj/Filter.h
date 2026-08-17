#ifndef FILTER_H
#define FILTER_H

#include <string>
#include "Image.h"

// Filter 抽象基类：所有滤镜的统一父类，通过 apply() 实现运行时多态。
class Filter {
protected:
    std::string filterName;

public:
    explicit Filter(const std::string& name);
    virtual void apply(Image& image) = 0;
    virtual void showInfo() const;
    virtual std::string getName() const;
    virtual ~Filter() {}
};

#endif