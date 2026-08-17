#include "PPMFileHandler.h"
#include <fstream>
#include <stdexcept>
#include <sstream>
#include <cctype>
#include <cmath>

namespace {
    // 读取 PPM 头部 token，自动跳过空白符和以 # 开头的注释。
    std::string readToken(std::istream& in, char* delimiter = nullptr) {
        if (delimiter != nullptr) {
            *delimiter = '\0';
        }

        std::string token;
        char ch;

        while (in.get(ch)) {
            unsigned char uch = static_cast<unsigned char>(ch);
            if (std::isspace(uch)) {
                continue;
            }
            if (ch == '#') {
                std::string comment;
                std::getline(in, comment);
                continue;
            }
            token.push_back(ch);
            break;
        }

        while (in.get(ch)) {
            unsigned char uch = static_cast<unsigned char>(ch);
            if (std::isspace(uch)) {
                if (delimiter != nullptr) {
                    *delimiter = ch;
                }
                break;
            }
            if (ch == '#') {
                if (delimiter != nullptr) {
                    *delimiter = ch;
                }
                std::string comment;
                std::getline(in, comment);
                break;
            }
            token.push_back(ch);
        }

        if (token.empty()) {
            throw std::runtime_error("PPM 文件头读取失败或文件内容不完整。");
        }
        return token;
    }

    int parseInteger(const std::string& token, const std::string& fieldName) {
        try {
            size_t index = 0;
            int value = std::stoi(token, &index);
            if (index != token.size()) {
                throw std::invalid_argument("存在非数字字符");
            }
            return value;
        } catch (const std::exception&) {
            throw std::runtime_error("PPM 文件中的 " + fieldName + " 不是合法整数。");
        }
    }

    int scaleToByte(int value, int maxValue) {
        if (value < 0 || value > maxValue) {
            throw std::runtime_error("PPM 像素值超出文件声明的颜色范围。");
        }
        if (maxValue == 255) {
            return value;
        }
        return static_cast<int>(std::round(value * 255.0 / maxValue));
    }
}

bool PPMFileHandler::load(const std::string& path, Image& image) {
    std::ifstream in(path, std::ios::binary);
    if (!in) {
        throw std::runtime_error("无法打开文件：" + path);
    }

    std::string magic = readToken(in);
    if (magic != "P3" && magic != "P6") {
        throw std::runtime_error("文件格式错误：仅支持 P3 或 P6 类型的 PPM 文件。");
    }

    int width = parseInteger(readToken(in), "宽度");
    int height = parseInteger(readToken(in), "高度");
    char maxDelimiter = '\0';
    int maxValue = parseInteger(readToken(in, &maxDelimiter), "最大颜色值");

    if (width <= 0 || height <= 0) {
        throw std::runtime_error("PPM 文件宽度或高度非法。");
    }
    if (maxValue <= 0 || maxValue > 255) {
        throw std::runtime_error("当前版本仅支持最大颜色值在 1 到 255 之间的 PPM 文件。");
    }

    // 处理 Windows 文本文件常见的 CRLF 行尾：readToken 已经读掉 \r 时，再读掉紧随其后的 \n。
    if (magic == "P6" && maxDelimiter == '\r' && in.peek() == '\n') {
        in.get();
    }

    Image temp;
    temp.resize(width, height);

    if (magic == "P3") {
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                int r = parseInteger(readToken(in), "红色分量");
                int g = parseInteger(readToken(in), "绿色分量");
                int b = parseInteger(readToken(in), "蓝色分量");
                temp.setPixel(x, y, Pixel(scaleToByte(r, maxValue),
                                         scaleToByte(g, maxValue),
                                         scaleToByte(b, maxValue)));
            }
        }
    } else {
        unsigned char rgb[3];
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                if (!in.read(reinterpret_cast<char*>(rgb), 3)) {
                    throw std::runtime_error("P6 PPM 像素数据不完整。");
                }
                temp.setPixel(x, y, Pixel(scaleToByte(rgb[0], maxValue),
                                         scaleToByte(rgb[1], maxValue),
                                         scaleToByte(rgb[2], maxValue)));
            }
        }
    }

    image = temp;
    return true;
}

bool PPMFileHandler::save(const std::string& path, const Image& image) {
    if (!image.isLoaded()) {
        throw std::runtime_error("保存失败：当前没有加载图像。");
    }

    std::ofstream out(path, std::ios::out);
    if (!out) {
        throw std::runtime_error("无法创建或写入文件：" + path);
    }

    out << "P3\n";
    out << "# Created by C++ ImageFilterTool\n";
    out << image.getWidth() << ' ' << image.getHeight() << "\n";
    out << "255\n";

    for (int y = 0; y < image.getHeight(); ++y) {
        for (int x = 0; x < image.getWidth(); ++x) {
            Pixel p = image.getPixel(x, y);
            out << p.getR() << ' ' << p.getG() << ' ' << p.getB();
            if (x != image.getWidth() - 1) {
                out << "   ";
            }
        }
        out << '\n';
    }

    if (!out) {
        throw std::runtime_error("写入 PPM 文件时发生错误。");
    }
    return true;
}

std::string PPMFileHandler::getFormatName() const {
    return "PPM(P3/P6读取，P3保存)";
}