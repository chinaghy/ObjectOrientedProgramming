#include "Image.h"
#include <stdexcept>

Image::Image() : width(0), height(0), loaded(false) {
}

int Image::getWidth() const {
    return width;
}

int Image::getHeight() const {
    return height;
}

bool Image::isLoaded() const {
    return loaded;
}

void Image::checkBounds(int x, int y) const {
    if (!loaded) {
        throw std::runtime_error("当前没有加载图像。");
    }
    if (x < 0 || x >= width || y < 0 || y >= height) {
        throw std::out_of_range("像素坐标越界。");
    }
}

Pixel Image::getPixel(int x, int y) const {
    checkBounds(x, y);
    return pixels[y][x];
}

void Image::setPixel(int x, int y, const Pixel& p) {
    checkBounds(x, y);
    pixels[y][x] = p;
}

void Image::resize(int newWidth, int newHeight) {
    if (newWidth <= 0 || newHeight <= 0) {
        throw std::invalid_argument("图像宽度和高度必须为正数。");
    }

    width = newWidth;
    height = newHeight;
    pixels.assign(height, std::vector<Pixel>(width));
    loaded = true;
}

void Image::showInfo() const {
    if (!loaded) {
        std::cout << "当前未加载图像。" << std::endl;
        return;
    }

    long long pixelCount = static_cast<long long>(width) * height;
    std::cout << "图像基本信息：" << std::endl;
    std::cout << "宽度：" << width << std::endl;
    std::cout << "高度：" << height << std::endl;
    std::cout << "像素数量：" << pixelCount << std::endl;
}

void Image::clear() {
    width = 0;
    height = 0;
    pixels.clear();
    loaded = false;
}