#include "InvertFilter.h"
#include <stdexcept>

InvertFilter::InvertFilter() : Filter("颜色反转滤镜") {
}

void InvertFilter::apply(Image& image) {
    if (!image.isLoaded()) {
        throw std::runtime_error("颜色反转失败：当前没有加载图像。");
    }

    for (int y = 0; y < image.getHeight(); ++y) {
        for (int x = 0; x < image.getWidth(); ++x) {
            Pixel p = image.getPixel(x, y);
            image.setPixel(x, y, Pixel(255 - p.getR(), 255 - p.getG(), 255 - p.getB()));
        }
    }
}