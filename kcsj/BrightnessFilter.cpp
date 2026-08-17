#include "BrightnessFilter.h"
#include <stdexcept>
#include <iostream>
#include <cmath>

BrightnessFilter::BrightnessFilter(int value)
    : Filter("亮度调节滤镜"), brightness("亮度变化值", value, -255, 255) {
}

void BrightnessFilter::apply(Image& image) {
    if (!image.isLoaded()) {
        throw std::runtime_error("亮度调节失败：当前没有加载图像。");
    }

    int delta = static_cast<int>(std::round(brightness.getValue()));
    for (int y = 0; y < image.getHeight(); ++y) {
        for (int x = 0; x < image.getWidth(); ++x) {
            Pixel p = image.getPixel(x, y);
            image.setPixel(x, y, Pixel(p.getR() + delta, p.getG() + delta, p.getB() + delta));
        }
    }
}

void BrightnessFilter::showInfo() const {
    Filter::showInfo();
    std::cout << brightness.getName() << "：" << brightness.getValue() << std::endl;
}