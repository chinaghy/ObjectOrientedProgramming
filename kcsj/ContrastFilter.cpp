#include "ContrastFilter.h"
#include <stdexcept>
#include <iostream>
#include <cmath>

ContrastFilter::ContrastFilter(double value)
    : Filter("对比度调节滤镜"), factor("对比度系数", value, 0.0, 5.0) {
}

void ContrastFilter::apply(Image& image) {
    if (!image.isLoaded()) {
        throw std::runtime_error("对比度调节失败：当前没有加载图像。");
    }

    double f = factor.getValue();
    for (int y = 0; y < image.getHeight(); ++y) {
        for (int x = 0; x < image.getWidth(); ++x) {
            Pixel p = image.getPixel(x, y);
            int r = static_cast<int>(std::round((p.getR() - 128) * f + 128));
            int g = static_cast<int>(std::round((p.getG() - 128) * f + 128));
            int b = static_cast<int>(std::round((p.getB() - 128) * f + 128));
            image.setPixel(x, y, Pixel(r, g, b));
        }
    }
}

void ContrastFilter::showInfo() const {
    Filter::showInfo();
    std::cout << factor.getName() << "：" << factor.getValue() << std::endl;
}