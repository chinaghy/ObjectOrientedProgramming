#ifndef BMP_FILE_HANDLER_H
#define BMP_FILE_HANDLER_H

#include "ImageFileHandler.h"

// BMPFileHandler：当前保留扩展接口，后期可实现 24 位 BMP 读写。
class BMPFileHandler : public ImageFileHandler {
public:
    bool load(const std::string& path, Image& image) override;
    bool save(const std::string& path, const Image& image) override;
    std::string getFormatName() const override;
};

#endif