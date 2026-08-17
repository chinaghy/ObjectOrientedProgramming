#include "SharpenFilter.h"
#include <stdexcept>
#include <algorithm>

SharpenFilter::SharpenFilter() : Filter("锐化滤镜") {
}

void SharpenFilter::apply(Image& image) {
    if (!image.isLoaded()) {
        throw std::runtime_error("锐化处理失败：当前没有加载图像。");
    }

    const int kernel[3][3] = {
        { 0, -1,  0 },
        { -1, 5, -1 },
        { 0, -1,  0 }
    };

    Image original = image;
    int w = image.getWidth();
    int h = image.getHeight();

    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            int sumR = 0;
            int sumG = 0;
            int sumB = 0;

            for (int ky = -1; ky <= 1; ++ky) {
                for (int kx = -1; kx <= 1; ++kx) {
                    int nx = std::clamp(x + kx, 0, w - 1);
                    int ny = std::clamp(y + ky, 0, h - 1);
                    int weight = kernel[ky + 1][kx + 1];
                    Pixel p = original.getPixel(nx, ny);
                    sumR += p.getR() * weight;
                    sumG += p.getG() * weight;
                    sumB += p.getB() * weight;
                }
            }

            image.setPixel(x, y, Pixel(sumR, sumG, sumB));
        }
    }
}