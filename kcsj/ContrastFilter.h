#ifndef CONTRAST_FILTER_H
#define CONTRAST_FILTER_H

#include "Filter.h"
#include "FilterParameter.h"

// ContrastFilter：对比度调节滤镜，使用 FilterParameter 组合对比度系数参数。
class ContrastFilter : public Filter {
private:
    FilterParameter factor;

public:
    explicit ContrastFilter(double factor = 1.0);
    void apply(Image& image) override;
    void showInfo() const override;
};

#endif