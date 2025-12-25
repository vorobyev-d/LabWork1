/*
Vorobyev Dmitriy | st140149@student.spbu.ru
LabWork 1
*/

#include "BitmapImg.h"
#include <fstream>
#include <stdexcept>
#include <algorithm>
#include <iostream>
#include <cmath>



BitmapImg::BitmapImg()
{
    file_header = {};
    info_header = {};
}

BitmapImg::BitmapImg(int w, int h, const std::vector<Pixel>& p)
{
    info_header.width_ = w;
    info_header.height_ = h;
    pixels = p;
}

int BitmapImg::get_width() const
{
    return info_header.width_;
}

int BitmapImg::get_height() const
{
    return info_header.height_;
}

int BitmapImg::get_padding(int width) const
{
    return (ROW_ALIGNMENT - (width * sizeof(Pixel)) % ROW_ALIGNMENT) % ROW_ALIGNMENT;
}

void BitmapImg::load_from_file(const std::string& filename)
{
    std::ifstream in(filename, std::ios::binary);
    if (!in) throw std::runtime_error("File not found");

    in.read(reinterpret_cast<char*>(&file_header), sizeof(file_header));
    if (file_header.type_ != BMP_SIGNATURE) throw std::runtime_error("Not a BMP file");

    in.read(reinterpret_cast<char*>(&info_header), sizeof(info_header));
    if (info_header.bit_count_ != BITS_PER_PIXEL) throw std::runtime_error("Only 24-bit BMP supported");

    int w = info_header.width_;
    int h = std::abs(info_header.height_);
    int padding = get_padding(w);

    pixels.resize(w * h);

    in.seekg(file_header.off_bits_, std::ios::beg);

    for (int y = 0; y < h; ++y)
    {
        for (int x = 0; x < w; ++x)
        {
            in.read(reinterpret_cast<char*>(&pixels[y * w + x]), sizeof(Pixel));
        }
        in.ignore(padding);
    }
}

void BitmapImg::save_to_file(const std::string& filename) const
{
    std::ofstream out(filename, std::ios::binary);
    if (!out) throw std::runtime_error("Cannot create file");

    int w = info_header.width_;
    int h = std::abs(info_header.height_);
    int padding = get_padding(w);

    BMPFileHeader outFh = file_header;
    BMPInfoHeader outIh = info_header;

    outFh.type_ = BMP_SIGNATURE;
    outFh.reserved1_ = 0;
    outFh.reserved2_ = 0;
    outFh.off_bits_ = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader);
    uint32_t dataSize = (w * sizeof(Pixel) + padding) * h;
    outFh.size_ = outFh.off_bits_ + dataSize;

    outIh.image_size_ = dataSize;
    outIh.size_ = INFO_HEADER_SIZE;
    outIh.planes_ = 1;
    outIh.bit_count_ = BITS_PER_PIXEL;
    outIh.compression_ = NO_COMPRESSION;

    out.write(reinterpret_cast<const char*>(&outFh), sizeof(outFh));
    out.write(reinterpret_cast<const char*>(&outIh), sizeof(outIh));

    uint8_t padByte = 0;
    for (int y = 0; y < h; ++y)
    {
        for (int x = 0; x < w; ++x)
            out.write(reinterpret_cast<const char*>(&pixels[y * w + x]), sizeof(Pixel));
        for (int k = 0; k < padding; ++k)
            out.write(reinterpret_cast<const char*>(&padByte), 1);
    }
}

void BitmapImg::rotate_clockwise_90()
{
    int w = info_header.width_;
    int h = info_header.height_;
    std::vector<Pixel> newPixels(w * h);

    for (int y = 0; y < h; ++y)
        for (int x = 0; x < w; ++x)
            newPixels[(w - 1 - x) * h + y] = pixels[y * w + x];

    pixels = newPixels;
    std::swap(info_header.width_, info_header.height_);
}

void BitmapImg::rotate_counter_clockwise_90()
{
    int w = info_header.width_;
    int h = info_header.height_;
    std::vector<Pixel> newPixels(w * h);

    for (int y = 0; y < h; ++y)
        for (int x = 0; x < w; ++x)
            newPixels[x * h + (h - 1 - y)] = pixels[y * w + x];

    pixels = newPixels;
    std::swap(info_header.width_, info_header.height_);
}

void BitmapImg::apply_gaussian_filter()
{
    int w = info_header.width_;
    int h = info_header.height_;
    std::vector<Pixel> result = pixels;

    const double kernel[3][3] =
    {
        {0.075, 0.124, 0.075},
        {0.124, 0.204, 0.124},
        {0.075, 0.124, 0.075}
    };

    for (int y = 0; y < h; ++y)
    {
        for (int x = 0; x < w; ++x)
        {
            double r = 0, g = 0, b = 0;

            for (int ky = -1; ky <= 1; ++ky)
            {
                for (int kx = -1; kx <= 1; ++kx)
                {
                    int py = std::clamp(y + ky, 0, h - 1);
                    int px = std::clamp(x + kx, 0, w - 1);

                    Pixel p = pixels[py * w + px];
                    double kVal = kernel[ky + 1][kx + 1];

                    b += p.b * kVal;
                    g += p.g * kVal;
                    r += p.r * kVal;
                }
            }

            result[y * w + x].b = static_cast<uint8_t>(std::clamp(b, 0.0, 255.0));
            result[y * w + x].g = static_cast<uint8_t>(std::clamp(g, 0.0, 255.0));
            result[y * w + x].r = static_cast<uint8_t>(std::clamp(r, 0.0, 255.0));
        }
    }
    pixels = result;
}

Pixel BitmapImg::get_pixel(int x, int y) const
{
    if (x < 0 || x >= info_header.width_ || y < 0 || y >= info_header.height_)
        return {0,0,0};
    return pixels[y * info_header.width_ + x];
}
