/*
Vorobyev Dmitriy | st140149@student.spbu.ru
LabWork 1
*/

#ifndef BITMAP_H
#define BITMAP_H

#include "ImageProcessor.h"
#include "BMPHeader.h"

#include <vector>
#include <string>

class BitmapImg : ImageProcessor
{
    public:
    BitmapImg();
    BitmapImg(int w, int h);

    void load_from_file(std::string& file_name);
    void save_to_file(std::string& file_name);

    void rotate_clockwise_90() override;
    void rotate_counter_clockwise_90() override;
    void apply_gaussian_filter() override;

    int get_width();
    int get_height();

    private:
    std::vector<unsigned char> pixels;

    int width_;
    int height_;
    int row_padding_;

    BMPFileHeader file_header;
    BMPInfoHeader info_header;
};

#endif