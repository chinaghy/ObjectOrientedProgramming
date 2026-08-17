#include "BlurFilter.h"
#include <stdexcept>
#include <iostream>

BlurFilter::BlurFilter(int r)
    : Filter("均值模糊滤镜"), radius("模糊半径", r, 1, 5) {
}

void BlurFilter::apply(Image& image) {
    if (!image.isLoaded()) {
        throw std::runtime_error("模糊处理失败：当前没有加载图像。");
    }

    Image original = image;
    int w = image.getWidth();
    int h = image.getHeight();
    int r = static_cast<int>(radius.getValue());

    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            int sumR = 0;
            int sumG = 0;
            int sumB = 0;
            int count = 0;

            for (int dy = -r; dy <= r; ++dy) {
                for (int dx = -r; dx <= r; ++dx) {
                    int nx = x + dx;
                    int ny = y + dy;
                    if (nx >= 0 && nx < w && ny >= 0 && ny < h) {
                        Pixel p = original.getPixel(nx, ny);
                        sumR += p.getR();
                        sumG += p.getG();
                        sumB += p.getB();
                        ++count;
                    }
                }
            }

            image.setPixel(x, y, Pixel(sumR / count, sumG / count, sumB / count));
        }
    }
}

void BlurFilter::showInfo() const {
    Filter::showInfo();
    std::cout << radius.getName() << "：" << radius.getValue() << std::endl;
}