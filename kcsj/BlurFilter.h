#ifndef BLUR_FILTER_H
#define BLUR_FILTER_H

#include "Filter.h"
#include "FilterParameter.h"

// BlurFilter：简单均值模糊滤镜，使用 FilterParameter 组合半径参数。
class BlurFilter : public Filter {
private:
    FilterParameter radius;

public:
    explicit BlurFilter(int radius = 1);
    void apply(Image& image) override;
    void showInfo() const override;
};

#endif