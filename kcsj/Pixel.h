#ifndef PIXEL_H
#define PIXEL_H

// Pixel 类：封装一个 RGB 像素点，体现封装思想。
class Pixel {
private:
    int r;
    int g;
    int b;

public:
    Pixel(int r = 0, int g = 0, int b = 0);

    int getR() const;
    int getG() const;
    int getB() const;

    void setR(int value);
    void setG(int value);
    void setB(int value);

    // 将颜色值限制在 0 到 255 之间。
    static int clampValue(int value);
};

#endif