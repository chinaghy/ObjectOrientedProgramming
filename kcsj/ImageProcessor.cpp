#include "ImageProcessor.h"
#include "PPMFileHandler.h"
#include "BMPFileHandler.h"
#include <algorithm>
#include <cctype>
#include <iostream>
#include <stdexcept>

namespace {
    std::string toLower(std::string s) {
        std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c) {
            return static_cast<char>(std::tolower(c));
        });
        return s;
    }

    std::string getExtension(const std::string& path) {
        size_t pos = path.find_last_of('.');
        if (pos == std::string::npos || pos == path.size() - 1) {
            return "";
        }
        return toLower(path.substr(pos + 1));
    }
}

std::unique_ptr<ImageFileHandler> ImageProcessor::createFileHandlerByPath(const std::string& path) const {
    std::string ext = getExtension(path);
    if (ext == "ppm") {
        return std::make_unique<PPMFileHandler>();
    }
    if (ext == "bmp") {
        return std::make_unique<BMPFileHandler>();
    }
    throw std::invalid_argument("不支持的文件扩展名：" + ext + "。当前建议使用 .ppm 文件。");
}

void ImageProcessor::loadImage(const std::string& path) {
    std::unique_ptr<ImageFileHandler> handler = createFileHandlerByPath(path);
    Image temp;
    handler->load(path, temp);

    currentImage = temp;
    history.clear();
    fileHandler = std::move(handler);

    std::cout << "图像加载成功，文件格式处理器：" << fileHandler->getFormatName() << std::endl;
}

void ImageProcessor::saveImage(const std::string& path) {
    if (!hasImage()) {
        throw std::runtime_error("保存失败：请先加载图像。");
    }

    std::unique_ptr<ImageFileHandler> handler = createFileHandlerByPath(path);
    handler->save(path, currentImage);
    fileHandler = std::move(handler);

    std::cout << "图像保存成功，输出文件：" << path << std::endl;
}

void ImageProcessor::applyFilter(Filter& filter) {
    if (!hasImage()) {
        throw std::runtime_error("滤镜处理失败：请先加载图像。");
    }

    history.saveState(currentImage);
    filter.apply(currentImage);
    std::cout << "已应用滤镜：" << filter.getName() << std::endl;
}

void ImageProcessor::undo() {
    if (!hasImage()) {
        throw std::runtime_error("撤销失败：请先加载图像。");
    }
    if (!history.canUndo()) {
        throw std::runtime_error("撤销失败：没有可撤销的上一步操作。");
    }

    currentImage = history.undo();
    std::cout << "已撤销上一步操作。" << std::endl;
}

void ImageProcessor::showImageInfo() const {
    currentImage.showInfo();
}

bool ImageProcessor::hasImage() const {
    return currentImage.isLoaded();
}