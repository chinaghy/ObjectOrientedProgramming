cmake_minimum_required(VERSION 4.1)
project(kcsj)

set(CMAKE_CXX_STANDARD 17)

add_executable(kcsj main.cpp
        Pixel.cpp
        Pixel.h
        Image.h
        Image.cpp
        ImageFileHandler.h
        ImageFileHandler.cpp
        PPMFileHandler.h
        PPMFileHandler.cpp
        BMPFileHandler.h
        BMPFileHandler.cpp
        Filter.h
        Filter.cpp
        FilterParameter.h
        FilterParameter.cpp
        GrayFilter.h
        GrayFilter.cpp
        BlurFilter.h
        BlurFilter.cpp
        SharpenFilter.h
        SharpenFilter.cpp
        EmbossFilter.h
        EmbossFilter.cpp
        InvertFilter.h
        InvertFilter.cpp
        BrightnessFilter.cpp
        BrightnessFilter.h
        ContrastFilter.cpp
        ContrastFilter.h
        ImageHistory.cpp
        ImageHistory.h
        ImageProcessor.cpp
        ImageProcessor.h
        Menu.cpp
        Menu.h)
