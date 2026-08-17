#ifndef SHARPEN_FILTER_H
#define SHARPEN_FILTER_H

#include "Filter.h"

// SharpenFilter：3x3 卷积锐化滤镜。
class SharpenFilter : public Filter {
public:
    SharpenFilter();
    void apply(Image& image) override;
};

#endif