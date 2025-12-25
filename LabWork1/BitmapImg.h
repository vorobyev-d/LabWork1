/*
Vorobyev Dmitriy | st140149@student.spbu.ru
LabWork 1
*/

#ifndef BITMAPIMG_H
#define BITMAPIMG_H

#include "BMPHeader.h"
#include "ImageProcessor.h"

#include <vector>
#include <string>

class BitmapImg : public ImageProcessor
{
public:
    BitmapImg();
    BitmapImg(int w, int h, const std::vector<Pixel>& p = {});

    void load_from_file(const std::string& filename) override;
    void save_to_file(const std::string& filename) const override;

    void rotate_clockwise_90() override;
    void rotate_counter_clockwise_90() override;
    void apply_gaussian_filter() override;

    int get_width() const;
    int get_height() const;
    Pixel get_pixel(int x, int y) const;

private:
    static const int ROW_ALIGNMENT = 4;
    static const unsigned short BMP_SIGNATURE = 0x4D42;
    static const unsigned short BITS_PER_PIXEL = 24;
    static const unsigned int NO_COMPRESSION = 0;
    static const unsigned int INFO_HEADER_SIZE = 40;

    BMPFileHeader file_header;
    BMPInfoHeader info_header;
    std::vector<Pixel> pixels;

    int get_padding(int width) const;
};

#endif