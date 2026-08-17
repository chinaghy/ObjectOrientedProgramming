#ifndef EMBOSS_FILTER_H
#define EMBOSS_FILTER_H

#include "Filter.h"

// EmbossFilter：3x3 卷积浮雕滤镜。
class EmbossFilter : public Filter {
public:
    EmbossFilter();
    void apply(Image& image) override;
};

#endif