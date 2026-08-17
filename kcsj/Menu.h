#ifndef MENU_H
#define MENU_H

#include "ImageProcessor.h"
#include <string>

// Menu：负责控制台菜单交互。
class Menu {
private:
    ImageProcessor processor;

    int readIntInRange(const std::string& prompt, int minValue, int maxValue) const;
    double readDoubleInRange(const std::string& prompt, double minValue, double maxValue) const;
    std::string readPath(const std::string& prompt) const;
    void applyFilterByChoice(int choice);

public:
    void showMainMenu() const;
    void run();
};

#endif