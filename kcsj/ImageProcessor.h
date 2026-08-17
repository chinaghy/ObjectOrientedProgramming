#ifndef IMAGE_PROCESSOR_H
#define IMAGE_PROCESSOR_H

#include <memory>
#include <string>
#include "Image.h"
#include "ImageHistory.h"
#include "ImageFileHandler.h"
#include "Filter.h"

// ImageProcessor：系统核心控制类，统一调度文件读写、滤镜处理和撤销。
class ImageProcessor {
private:
    Image currentImage;
    ImageHistory history;
    std::unique_ptr<ImageFileHandler> fileHandler;

    std::unique_ptr<ImageFileHandler> createFileHandlerByPath(const std::string& path) const;

public:
    void loadImage(const std::string& path);
    void saveImage(const std::string& path);
    void applyFilter(Filter& filter);
    void undo();
    void showImageInfo() const;
    bool hasImage() const;
};

#endif