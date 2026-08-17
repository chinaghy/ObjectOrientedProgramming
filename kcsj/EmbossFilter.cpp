#include "EmbossFilter.h"
#include <stdexcept>
#include <algorithm>

EmbossFilter::EmbossFilter() : Filter("浮雕滤镜") {
}

void EmbossFilter::apply(Image& image) {
    if (!image.isLoaded()) {
        throw std::runtime_error("浮雕处理失败：当前没有加载图像。");
    }

    const int kernel[3][3] = {
        { -2, -1, 0 },
        { -1,  1, 1 },
        {  0,  1, 2 }
    };

    Image original = image;
    int w = image.getWidth();
    int h = image.getHeight();

    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            int sumR = 128;
            int sumG = 128;
            int sumB = 128;

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