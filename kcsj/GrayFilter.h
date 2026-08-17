#ifndef GRAY_FILTER_H
#define GRAY_FILTER_H

#include "Filter.h"

// GrayFilter：灰度化滤镜。
class GrayFilter : public Filter {
public:
    GrayFilter();
    void apply(Image& image) override;
};

#endif