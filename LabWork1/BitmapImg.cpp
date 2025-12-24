/*
Vorobyev Dmitriy | st140149@student.spbu.ru
LabWork 1
*/

#include <fstream>

#include "BitmapImg.h"


BitmapImg::BitmapImg() : width_(0), height_(0), row_padding_(0) {}

BitmapImg::BitmapImg(int w, int h) : width_(w), height_(h) {row_padding_ = (4 - (width_ * 3) % 4) % 4; 
pixels.resize((width_ * 3 + row_padding_) * height_, 0);}

void BitmapImg::load_from_file(const std::string& file_name)
{
    std::ifstream file(file_name, std::ios::binary);
    if (!file)
    {
        throw std::runtime_error("Couldnt open file for reading");
    }

    file.read(reinterpret_cast<char*>(&file_header), sizeof(file_header));
    file.read(reinterpret_cast<char*>(&info_header), sizeof(info_header));

    if (file_header.type_ != 0x4D42)
    {
        throw std::runtime_error("not a valid BMP file");
    }

    if (info_header.bit_count_ != 24)
    {
        throw std::runtime_error("not a 24 bit bmp file");
    }

    if (info_header.compression_ != 0)
    {
        throw std::runtime_error("compressed bmp files are not supported");
    }

    width_ = info_header.width_;
    height_ = info_header.height_;
    row_padding_ = (4 - (width_ * 3) % 4) % 4;
    pixels.resize((width_ * 3 + row_padding_) * height_);

    file.seekg(file_header.off_bits_, std::ios::beg);
    file.read(reinterpret_cast<char*>(pixels.data()), pixels.size());
}

void BitmapImg::save_to_file(const std::string& file_name)
{
    file_header.type_ = 0x4D42;
    file_header.off_bits_ = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader);
    info_header.image_size_ = pixels.size();
    file_header.size_ = file_header.off_bits_ + info_header.image_size_;

    std::ofstream file(file_name, std::ios::binary);
    if (!file)
        throw std::runtime_error("Couldnt open file for writing");

    file.write(reinterpret_cast<char*>(&file_header), sizeof(file_header));
    file.write(reinterpret_cast<char*>(&info_header), sizeof(info_header));
    file.write(reinterpret_cast<char*>(pixels.data()), pixels.size());
}


void BitmapImg::rotate_clockwise_90()
{
    std::vector<unsigned char> new_pixels((height_ * 3 + ((4 - (height_ * 3) % 4) % 4)) * width_, 0);
    int new_row_padding = (4 - (height_ * 3) % 4) % 4;

    for (int y = 0; y < height_; ++y)
    {
        for (int x = 0; x < width_; ++x)
        {
            int old_index = y * (width_ * 3 + row_padding_) + x * 3;
            int new_index = (width_ - 1 - x) * (height_ * 3 + new_row_padding) + y * 3;
            
            new_pixels[new_index] = pixels[old_index];
            new_pixels[new_index + 1] = pixels[old_index + 1];
            new_pixels[new_index + 2] = pixels[old_index + 2];
        }
    }

    std::swap(width_, height_);
    row_padding_ = new_row_padding;
    pixels = std::move(new_pixels);

    info_header.width_ = width_;
    info_header.height_ = height_;
    info_header.image_size_ = pixels.size();
    file_header.size_ = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader) + info_header.image_size_;

    
}

void BitmapImg::rotate_counter_clockwise_90()
{
    
    std::vector<unsigned char> new_pixels((height_ * 3 + (4 - (height_ * 3) % 4) % 4) * width_, 0);
    int new_row_padding = (4 - (height_ * 3) % 4) % 4;

    for (int y = 0; y < height_; ++y)
    {
        for (int x = 0; x < width_; ++x)
        {
            int old_index = y * (width_ * 3 + row_padding_) + x * 3;
            int new_index = x * (height_ * 3 + new_row_padding) + (height_ - 1 - y) * 3;
            
            new_pixels[new_index] = pixels[old_index];
            new_pixels[new_index + 1] = pixels[old_index + 1];
            new_pixels[new_index + 2] = pixels[old_index + 2];
        }
    }

    std::swap(width_, height_);
    row_padding_ = new_row_padding;
    pixels = std::move(new_pixels);

    info_header.width_ = width_;
    info_header.height_ = height_;
    info_header.image_size_ = pixels.size();
    file_header.size_ = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader) + info_header.image_size_;
}

void BitmapImg::apply_gaussian_filter()
{
    std::vector<unsigned char> new_pixels = pixels;

    int kernel[3][3] = {
        {1, 2, 1},
        {2, 4, 2},
        {1, 2, 1}
    };
    int kernel_sum = 16;

    for (int y = 0; y < height_; ++y)
    {
        for (int x = 0; x < width_; ++x)
        {
            int sum_r = 0, sum_g = 0, sum_b = 0;

            for (int ky = -1; ky <= 1; ++ky)
            {
                int yy = std::max(0, std::min(y + ky, height_ - 1));
                for (int kx = -1; kx <= 1; ++kx)
                {
                    int xx = std::max(0, std::min(x + kx, width_ - 1));
                    int pixel_index = yy * (width_ * 3 + row_padding_) + xx * 3;
                    sum_b += pixels[pixel_index] * kernel[ky + 1][kx + 1];
                    sum_g += pixels[pixel_index + 1] * kernel[ky + 1][kx + 1];
                    sum_r += pixels[pixel_index + 2] * kernel[ky + 1][kx + 1];
                }
            }

            int new_index = y * (width_ * 3 + row_padding_) + x * 3;
            new_pixels[new_index] = sum_b / kernel_sum;
            new_pixels[new_index + 1] = sum_g / kernel_sum;
            new_pixels[new_index + 2] = sum_r / kernel_sum;
        }
    }
    pixels = std::move(new_pixels);
}


int BitmapImg::get_width()
{
    return width_;
}

int BitmapImg::get_height()
{
    return height_;
}

