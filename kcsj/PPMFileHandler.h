#ifndef PPM_FILE_HANDLER_H
#define PPM_FILE_HANDLER_H

#include "ImageFileHandler.h"

// PPMFileHandler：支持 P3 文本 PPM 和 P6 二进制 PPM 的读取，保存为 P3 文本 PPM。
class PPMFileHandler : public ImageFileHandler {
public:
    bool load(const std::string& path, Image& image) override;
    bool save(const std::string& path, const Image& image) override;
    std::string getFormatName() const override;
};

#endif