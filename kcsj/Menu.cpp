#include "Menu.h"
#include "GrayFilter.h"
#include "BlurFilter.h"
#include "SharpenFilter.h"
#include "EmbossFilter.h"
#include "InvertFilter.h"
#include "BrightnessFilter.h"
#include "ContrastFilter.h"
#include <iostream>
#include <sstream>
#include <memory>
#include <limits>
#include <stdexcept>
#include <cctype>

namespace {
    std::string trim(const std::string& s) {
        size_t start = 0;
        while (start < s.size() && std::isspace(static_cast<unsigned char>(s[start]))) {
            ++start;
        }

        size_t end = s.size();
        while (end > start && std::isspace(static_cast<unsigned char>(s[end - 1]))) {
            --end;
        }

        return s.substr(start, end - start);
    }
}

void Menu::showMainMenu() const {
    std::cout << "\n========== 基于 C++ 的图像滤镜处理工具 ==========" << std::endl;
    std::cout << "1. 加载图片" << std::endl;
    std::cout << "2. 保存图片" << std::endl;
    std::cout << "3. 显示图片信息" << std::endl;
    std::cout << "4. 应用灰度滤镜" << std::endl;
    std::cout << "5. 应用模糊滤镜" << std::endl;
    std::cout << "6. 应用锐化滤镜" << std::endl;
    std::cout << "7. 应用浮雕滤镜" << std::endl;
    std::cout << "8. 应用颜色反转滤镜" << std::endl;
    std::cout << "9. 应用亮度调节" << std::endl;
    std::cout << "10. 应用对比度调节" << std::endl;
    std::cout << "11. 撤销上一步" << std::endl;
    std::cout << "0. 退出系统" << std::endl;
    std::cout << "================================================" << std::endl;
}

int Menu::readIntInRange(const std::string& prompt, int minValue, int maxValue) const {
    while (true) {
        std::cout << prompt;
        std::string line;
        if (!std::getline(std::cin, line)) {
            throw std::runtime_error("输入流结束。");
        }

        std::stringstream ss(line);
        int value;
        char extra;
        if ((ss >> value) && !(ss >> extra) && value >= minValue && value <= maxValue) {
            return value;
        }
        std::cout << "输入无效，请输入范围 [" << minValue << ", " << maxValue << "] 内的整数。" << std::endl;
    }
}

double Menu::readDoubleInRange(const std::string& prompt, double minValue, double maxValue) const {
    while (true) {
        std::cout << prompt;
        std::string line;
        if (!std::getline(std::cin, line)) {
            throw std::runtime_error("输入流结束。");
        }

        std::stringstream ss(line);
        double value;
        char extra;
        if ((ss >> value) && !(ss >> extra) && value >= minValue && value <= maxValue) {
            return value;
        }
        std::cout << "输入无效，请输入范围 [" << minValue << ", " << maxValue << "] 内的数字。" << std::endl;
    }
}

std::string Menu::readPath(const std::string& prompt) const {
    while (true) {
        std::cout << prompt;
        std::string path;
        if (!std::getline(std::cin, path)) {
            throw std::runtime_error("输入流结束。");
        }
        path = trim(path);
        if (!path.empty()) {
            return path;
        }
        std::cout << "路径不能为空，请重新输入。" << std::endl;
    }
}

void Menu::applyFilterByChoice(int choice) {
    std::unique_ptr<Filter> filter;

    switch (choice) {
    case 4:
        filter = std::make_unique<GrayFilter>();
        break;
    case 5: {
        int radius = readIntInRange("请输入模糊半径 [1, 5]：", 1, 5);
        filter = std::make_unique<BlurFilter>(radius);
        break;
    }
    case 6:
        filter = std::make_unique<SharpenFilter>();
        break;
    case 7:
        filter = std::make_unique<EmbossFilter>();
        break;
    case 8:
        filter = std::make_unique<InvertFilter>();
        break;
    case 9: {
        int brightness = readIntInRange("请输入亮度变化值 [-255, 255]：", -255, 255);
        filter = std::make_unique<BrightnessFilter>(brightness);
        break;
    }
    case 10: {
        double factor = readDoubleInRange("请输入对比度系数 [0.0, 5.0]，1.0 表示不变：", 0.0, 5.0);
        filter = std::make_unique<ContrastFilter>(factor);
        break;
    }
    default:
        throw std::invalid_argument("未知滤镜选项。");
    }

    // 这里使用 Filter 基类指针统一调用 applyFilter，体现多态。
    processor.applyFilter(*filter);
}

void Menu::run() {
    bool running = true;

    while (running) {
        showMainMenu();

        int choice;
        try {
            choice = readIntInRange("请输入菜单编号：", 0, 11);
        } catch (const std::exception& e) {
            std::cout << "输入结束，系统退出。" << std::endl;
            break;
        }

        try {
            switch (choice) {
            case 1: {
                std::string path = readPath("请输入要加载的图片路径，建议使用 .ppm：");
                processor.loadImage(path);
                break;
            }
            case 2: {
                std::string path = readPath("请输入保存路径，建议使用 .ppm：");
                processor.saveImage(path);
                break;
            }
            case 3:
                processor.showImageInfo();
                break;
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
            case 10:
                applyFilterByChoice(choice);
                break;
            case 11:
                processor.undo();
                break;
            case 0:
                running = false;
                std::cout << "系统已退出。" << std::endl;
                break;
            default:
                std::cout << "未知菜单项。" << std::endl;
                break;
            }
        } catch (const std::exception& e) {
            std::cout << "错误：" << e.what() << std::endl;
        }
    }
}