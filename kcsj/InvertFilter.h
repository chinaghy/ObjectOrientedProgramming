#ifndef INVERT_FILTER_H
#define INVERT_FILTER_H

#include "Filter.h"

// InvertFilter：颜色反转滤镜。
class InvertFilter : public Filter {
public:
    InvertFilter();
    void apply(Image& image) override;
};

#endif