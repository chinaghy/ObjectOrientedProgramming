#include "BMPFileHandler.h"
#include <stdexcept>

bool BMPFileHandler::load(const std::string&, Image&) {
    throw std::runtime_error("当前版本暂不支持 BMP 文件读取，请使用 PPM 格式图片。");
}

bool BMPFileHandler::save(const std::string&, const Image&) {
    throw std::runtime_error("当前版本暂不支持 BMP 文件保存，请保存为 PPM 格式图片。");
}

std::string BMPFileHandler::getFormatName() const {
    return "BMP(扩展接口，当前暂不支持)";
}