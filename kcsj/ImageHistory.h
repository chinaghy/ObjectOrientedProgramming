#ifndef IMAGE_HISTORY_H
#define IMAGE_HISTORY_H

#include <stack>
#include "Image.h"

// ImageHistory：使用 STL stack 保存历史图像，实现撤销功能。
class ImageHistory {
private:
    std::stack<Image> historyStack;

public:
    void saveState(const Image& image);
    bool canUndo() const;
    Image undo();
    void clear();
};

#endif