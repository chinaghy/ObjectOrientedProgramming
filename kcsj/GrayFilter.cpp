#include "GrayFilter.h"
#include <stdexcept>
#include <cmath>

GrayFilter::GrayFilter() : Filter("灰度化滤镜") {
}

void GrayFilter::apply(Image& image) {
    if (!image.isLoaded()) {
        throw std::runtime_error("灰度化失败：当前没有加载图像。");
    }

    for (int y = 0; y < image.getHeight(); ++y) {
        for (int x = 0; x < image.getWidth(); ++x) {
            Pixel p = image.getPixel(x, y);
            int gray = static_cast<int>(std::round(0.299 * p.getR() + 0.587 * p.getG() + 0.114 * p.getB()));
            image.setPixel(x, y, Pixel(gray, gray, gray));
        }
    }
}