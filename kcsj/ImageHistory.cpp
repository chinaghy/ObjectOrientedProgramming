#include "ImageHistory.h"
#include <stdexcept>

void ImageHistory::saveState(const Image& image) {
    if (image.isLoaded()) {
        historyStack.push(image);
    }
}

bool ImageHistory::canUndo() const {
    return !historyStack.empty();
}

Image ImageHistory::undo() {
    if (!canUndo()) {
        throw std::runtime_error("没有可撤销的历史记录。");
    }
    Image previous = historyStack.top();
    historyStack.pop();
    return previous;
}

void ImageHistory::clear() {
    while (!historyStack.empty()) {
        historyStack.pop();
    }
}