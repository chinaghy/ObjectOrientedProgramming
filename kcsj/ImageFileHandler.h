#ifndef IMAGE_FILE_HANDLER_H
#define IMAGE_FILE_HANDLER_H

#include <string>
#include "Image.h"

// ImageFileHandler 抽象基类：定义图像读写接口，便于扩展 PPM、BMP、PNG、JPG 等格式。
class ImageFileHandler {
public:
    virtual bool load(const std::string& path, Image& image) = 0;
    virtual bool save(const std::string& path, const Image& image) = 0;
    virtual std::string getFormatName() const = 0;
    virtual ~ImageFileHandler() {}
};

#endif