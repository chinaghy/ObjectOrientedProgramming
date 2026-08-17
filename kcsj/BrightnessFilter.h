#ifndef BRIGHTNESS_FILTER_H
#define BRIGHTNESS_FILTER_H

#include "Filter.h"
#include "FilterParameter.h"

// BrightnessFilter：亮度调节滤镜，使用 FilterParameter 组合亮度参数。
class BrightnessFilter : public Filter {
private:
    FilterParameter brightness;

public:
    explicit BrightnessFilter(int brightness = 0);
    void apply(Image& image) override;
    void showInfo() const override;
};

#endif