#ifndef IMAGE_H
#define IMAGE_H

#include <vector>
#include <iostream>
#include "Pixel.h"

// Image 类：封装整张图像，内部组合大量 Pixel 对象。
class Image {
private:
    int width;
    int height;
    std::vector<std::vector<Pixel>> pixels;
    bool loaded;

    void checkBounds(int x, int y) const;

public:
    Image();

    int getWidth() const;
    int getHeight() const;
    bool isLoaded() const;

    Pixel getPixel(int x, int y) const;
    void setPixel(int x, int y, const Pixel& p);

    void resize(int width, int height);
    void showInfo() const;
    void clear();
};

#endif