#include "Pixel.h"

Pixel::Pixel(int r, int g, int b) {
    setR(r);
    setG(g);
    setB(b);
}

int Pixel::getR() const {
    return r;
}

int Pixel::getG() const {
    return g;
}

int Pixel::getB() const {
    return b;
}

void Pixel::setR(int value) {
    r = clampValue(value);
}

void Pixel::setG(int value) {
    g = clampValue(value);
}

void Pixel::setB(int value) {
    b = clampValue(value);
}

int Pixel::clampValue(int value) {
    if (value < 0) {
        return 0;
    }
    if (value > 255) {
        return 255;
    }
    return value;
}